/**
 * @file file_format_util.cpp
 * @brief FileFormatUtil implementation
 * @since 0.7.0
 */

#include <cdocx/file_format_util.h>
#include <zip.h>

#include <cctype>
#include <cstring>
#include <fstream>
#include <sstream>

namespace cdocx {

// ============================================================================
// FileFormatInfo
// ============================================================================

FileFormatInfo::FileFormatInfo() = default;

// ============================================================================
// Helpers
// ============================================================================

static std::string to_lower(std::string s) {
    for (auto& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

static bool starts_with(const std::vector<uint8_t>& data, const char* prefix, size_t len) {
    if (data.size() < len) {
        return false;
    }
    return std::memcmp(data.data(), prefix, len) == 0;
}

static bool starts_with_string(const std::vector<uint8_t>& data, const char* prefix) {
    const size_t len = std::strlen(prefix);
    if (data.size() < len) {
        return false;
    }
    return std::memcmp(data.data(), prefix, len) == 0;
}

static bool contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

static std::string read_zip_entry(zip_t* za, const std::string& entry_name) {
    if (zip_entry_open(za, entry_name.c_str()) != 0) {
        return "";
    }
    void* buf = nullptr;
    size_t bufsize = 0;
    const ssize_t read = zip_entry_read(za, &buf, &bufsize);
    zip_entry_close(za);
    if (read <= 0 || !buf) {
        return "";
    }
    std::string result(static_cast<const char*>(buf), static_cast<size_t>(read));
    free(buf);  // NOLINT: zip_entry_read allocates with malloc
    return result;
}

static std::shared_ptr<FileFormatInfo> detect_from_zip(zip_t* za) {
    auto info = std::make_shared<FileFormatInfo>();

    const std::string content_types = read_zip_entry(za, "[Content_Types].xml");
    if (content_types.empty()) {
        info->set_load_format(LoadFormat::Unknown);
        return info;
    }

    const std::string ct_lower = to_lower(content_types);

    // Detect macros
    if (contains(ct_lower, "macros") || contains(ct_lower, "vnd.ms-office.vba")) {
        info->set_has_macros(true);
    }

    // Detect digital signatures
    if (contains(ct_lower, "digital-signature") || contains(ct_lower, "office.digitalsignature")) {
        info->set_has_digital_signature(true);
    }

    // Detect encryption
    if (contains(ct_lower, "encrypted-package") || contains(ct_lower, "encryption")) {
        info->set_is_encrypted(true);
    }

    // Determine exact Word format
    if (contains(ct_lower, "wordprocessingml.document.macroenabled.main+xml")) {
        info->set_load_format(LoadFormat::Docm);
    } else if (contains(ct_lower, "wordprocessingml.template.macroenabled.main+xml")) {
        info->set_load_format(LoadFormat::Dotm);
    } else if (contains(ct_lower, "wordprocessingml.template.main+xml")) {
        info->set_load_format(LoadFormat::Dotx);
    } else if (contains(ct_lower, "wordprocessingml.document.main+xml")) {
        info->set_load_format(LoadFormat::Docx);
    } else if (contains(ct_lower, "spreadsheetml") || contains(ct_lower, "presentationml")) {
        info->set_load_format(LoadFormat::Unknown);
    } else {
        // Could be ODT - check mimetype
        const std::string mimetype = read_zip_entry(za, "mimetype");
        const std::string mime_lower = to_lower(mimetype);
        if (contains(mime_lower, "application/vnd.oasis.opendocument.text")) {
            info->set_load_format(LoadFormat::Odt);
        } else {
            info->set_load_format(LoadFormat::Unknown);
        }
    }

    return info;
}

// ============================================================================
// FileFormatUtil
// ============================================================================

std::shared_ptr<FileFormatInfo> FileFormatUtil::detect_file_format(const std::string& file_name) {
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        return std::make_shared<FileFormatInfo>();
    }
    return detect_file_format(file);
}

std::shared_ptr<FileFormatInfo> FileFormatUtil::detect_file_format(std::istream& stream) {
    auto info = std::make_shared<FileFormatInfo>();

    // Remember position
    auto start_pos = stream.tellg();

    // Read first 8KB for sniffing
    std::vector<uint8_t> buffer(8192);
    stream.read(reinterpret_cast<char*>(buffer.data()),  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
                static_cast<std::streamsize>(buffer.size()));
    const std::streamsize bytes_read = stream.gcount();
    buffer.resize(static_cast<size_t>(bytes_read));

    // Restore position
    stream.seekg(start_pos);

    if (buffer.empty()) {
        return info;
    }

    // ZIP-based formats (DOCX, DOTX, DOCM, DOTM, ODT)
    if (starts_with(buffer, "PK\x03\x04", 4) || starts_with(buffer, "PK\x05\x06", 4)) {
        zip_t* za =
            zip_stream_open(reinterpret_cast<const char*>(buffer.data()),  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
                            buffer.size(), 0, 'r');
        if (za) {
            info = detect_from_zip(za);
            zip_stream_close(za);
        }
        return info;
    }

    // RTF
    if (starts_with_string(buffer, "{\\rtf")) {
        info->set_load_format(LoadFormat::Rtf);
        return info;
    }

    // HTML
    {
        auto count = std::min(static_cast<std::ptrdiff_t>(buffer.size()),
                              static_cast<std::ptrdiff_t>(256));
        const std::string head(buffer.begin(), buffer.begin() + count);
        std::string lower = to_lower(head);
        if (starts_with_string(buffer, "<!doctype html") || contains(lower, "<html") ||
            contains(lower, "<head")) {
            info->set_load_format(LoadFormat::Html);
            // Try to detect encoding from meta tag
            const size_t charset_pos = lower.find("charset=");
            if (charset_pos != std::string::npos) {
                const size_t start = charset_pos + 8;
                if (start < lower.size() && (lower[start] == '"' || lower[start] == '\'')) {
                    const char quote = lower[start];
                    const size_t end = lower.find(quote, start + 1);
                    if (end != std::string::npos) {
                        info->set_encoding(head.substr(start + 1, end - start - 1));
                    }
                } else {
                    const size_t end = lower.find_first_of(" ;\">\r\n", start);
                    if (end != std::string::npos) {
                        info->set_encoding(head.substr(start, end - start));
                    }
                }
            }
            return info;
        }
    }

    // XML
    if (starts_with_string(buffer, "<?xml")) {
        info->set_load_format(LoadFormat::Xml);
        return info;
    }

    // Markdown - look for common markers in first few lines
    {
        auto count = std::min(static_cast<std::ptrdiff_t>(buffer.size()),
                              static_cast<std::ptrdiff_t>(512));
        const std::string head(buffer.begin(), buffer.begin() + count);
        const std::string lower = to_lower(head);
        if (contains(lower, "# ") || contains(lower, "## ") || contains(lower, "**") ||
            contains(lower, "__") || contains(lower, "-") || contains(lower, "|")) {
            info->set_load_format(LoadFormat::Markdown);
            return info;
        }
    }

    // Plain text - if no null bytes and mostly printable
    bool has_null = false;
    size_t printable = 0;
    for (const uint8_t b : buffer) {
        if (b == 0) {
            has_null = true;
        }
        if (b >= 32 && b <= 126) {
            printable++;
        }
        if (b == '\n' || b == '\r' || b == '\t') {
            printable++;
        }
    }
    if (!has_null && static_cast<double>(printable) > static_cast<double>(buffer.size()) * 0.8) {
        info->set_load_format(LoadFormat::Text);
        return info;
    }

    return info;
}

std::shared_ptr<FileFormatInfo> FileFormatUtil::detect_file_format(const std::vector<uint8_t>& data) {
    std::stringstream ss(std::string(data.begin(), data.end()));
    return detect_file_format(ss);
}

std::string FileFormatUtil::load_format_to_extension(LoadFormat load_format) {
    switch (load_format) {
        case LoadFormat::Docx:
            return ".docx";
        case LoadFormat::Docm:
            return ".docm";
        case LoadFormat::Dotx:
            return ".dotx";
        case LoadFormat::Dotm:
            return ".dotm";
        case LoadFormat::FlatOpc:
            return ".fopc";
        case LoadFormat::Rtf:
            return ".rtf";
        case LoadFormat::Html:
            return ".html";
        case LoadFormat::Odt:
            return ".odt";
        case LoadFormat::Text:
            return ".txt";
        case LoadFormat::Markdown:
            return ".md";
        case LoadFormat::Xml:
            return ".xml";
        default:
            return "";
    }
}

std::string FileFormatUtil::save_format_to_extension(SaveFormat save_format) {
    switch (save_format) {
        case SaveFormat::Docx:
            return ".docx";
        case SaveFormat::Docm:
            return ".docm";
        case SaveFormat::Dotx:
            return ".dotx";
        case SaveFormat::Dotm:
            return ".dotm";
        case SaveFormat::FlatOpc:
            return ".fopc";
        case SaveFormat::Rtf:
            return ".rtf";
        case SaveFormat::Html:
            return ".html";
        case SaveFormat::Odt:
            return ".odt";
        case SaveFormat::Text:
            return ".txt";
        case SaveFormat::Markdown:
            return ".md";
        case SaveFormat::Xml:
            return ".xml";
        default:
            return "";
    }
}

SaveFormat FileFormatUtil::extension_to_save_format(const std::string& extension) {
    std::string ext = to_lower(extension);
    if (!ext.empty() && ext[0] != '.') {
        ext = "." + ext;
    }
    if (ext == ".docx") {
        return SaveFormat::Docx;
    }
    if (ext == ".docm") {
        return SaveFormat::Docm;
    }
    if (ext == ".dotx") {
        return SaveFormat::Dotx;
    }
    if (ext == ".dotm") {
        return SaveFormat::Dotm;
    }
    if (ext == ".fopc" || ext == ".flatopc") {
        return SaveFormat::FlatOpc;
    }
    if (ext == ".rtf") {
        return SaveFormat::Rtf;
    }
    if (ext == ".html" || ext == ".htm") {
        return SaveFormat::Html;
    }
    if (ext == ".odt") {
        return SaveFormat::Odt;
    }
    if (ext == ".txt" || ext == ".text") {
        return SaveFormat::Text;
    }
    if (ext == ".md" || ext == ".markdown") {
        return SaveFormat::Markdown;
    }
    if (ext == ".xml" || ext == ".wordml" || ext == ".wml") {
        return SaveFormat::Xml;
    }
    return SaveFormat::Unknown;
}

LoadFormat FileFormatUtil::save_format_to_load_format(SaveFormat save_format) {
    switch (save_format) {
        case SaveFormat::Docx:
            return LoadFormat::Docx;
        case SaveFormat::Docm:
            return LoadFormat::Docm;
        case SaveFormat::Dotx:
            return LoadFormat::Dotx;
        case SaveFormat::Dotm:
            return LoadFormat::Dotm;
        case SaveFormat::FlatOpc:
            return LoadFormat::FlatOpc;
        case SaveFormat::Rtf:
            return LoadFormat::Rtf;
        case SaveFormat::Html:
            return LoadFormat::Html;
        case SaveFormat::Odt:
            return LoadFormat::Odt;
        case SaveFormat::Text:
            return LoadFormat::Text;
        case SaveFormat::Markdown:
            return LoadFormat::Markdown;
        case SaveFormat::Xml:
            return LoadFormat::Xml;
        default:
            return LoadFormat::Unknown;
    }
}

SaveFormat FileFormatUtil::load_format_to_save_format(LoadFormat load_format) {
    switch (load_format) {
        case LoadFormat::Docx:
            return SaveFormat::Docx;
        case LoadFormat::Docm:
            return SaveFormat::Docm;
        case LoadFormat::Dotx:
            return SaveFormat::Dotx;
        case LoadFormat::Dotm:
            return SaveFormat::Dotm;
        case LoadFormat::FlatOpc:
            return SaveFormat::FlatOpc;
        case LoadFormat::Rtf:
            return SaveFormat::Rtf;
        case LoadFormat::Html:
            return SaveFormat::Html;
        case LoadFormat::Odt:
            return SaveFormat::Odt;
        case LoadFormat::Text:
            return SaveFormat::Text;
        case LoadFormat::Markdown:
            return SaveFormat::Markdown;
        case LoadFormat::Xml:
            return SaveFormat::Xml;
        default:
            return SaveFormat::Unknown;
    }
}

}  // namespace cdocx
