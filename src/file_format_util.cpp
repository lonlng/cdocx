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

// ============================================================================
// Format lookup table (shared between LoadFormat and SaveFormat)
// ============================================================================

struct FormatMapping {
    std::uint8_t value;
    const char* extension;
};

static const FormatMapping kFormatMappings[] = {
    {20, ".docx"},
    {21, ".docm"},
    {22, ".dotx"},
    {23, ".dotm"},
    {24, ".fopc"},
    {30, ".rtf"},
    {50, ".html"},
    {60, ".odt"},
    {62, ".txt"},
    {63, ".md"},
    {65, ".xml"},
};

static const char* format_value_to_extension(std::uint8_t value) {
    for (const auto& m : kFormatMappings) {
        if (m.value == value) {
            return m.extension;
        }
    }
    return "";
}

static std::uint8_t extension_to_format_value(const std::string& ext) {
    for (const auto& m : kFormatMappings) {
        if (ext == m.extension) {
            return m.value;
        }
    }
    return 255;  // Unknown
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
    return format_value_to_extension(static_cast<std::uint8_t>(load_format));
}

std::string FileFormatUtil::save_format_to_extension(SaveFormat save_format) {
    return format_value_to_extension(static_cast<std::uint8_t>(save_format));
}

SaveFormat FileFormatUtil::extension_to_save_format(const std::string& extension) {
    std::string ext = to_lower(extension);
    if (!ext.empty() && ext[0] != '.') {
        ext = "." + ext;
    }
    // Handle alias extensions
    if (ext == ".flatopc") {
        ext = ".fopc";
    } else if (ext == ".htm") {
        ext = ".html";
    } else if (ext == ".text") {
        ext = ".txt";
    } else if (ext == ".markdown") {
        ext = ".md";
    } else if (ext == ".wordml" || ext == ".wml") {
        ext = ".xml";
    }
    const std::uint8_t value = extension_to_format_value(ext);
    return static_cast<SaveFormat>(value);
}

LoadFormat FileFormatUtil::save_format_to_load_format(SaveFormat save_format) {
    return static_cast<LoadFormat>(static_cast<std::uint8_t>(save_format));
}

SaveFormat FileFormatUtil::load_format_to_save_format(LoadFormat load_format) {
    return static_cast<SaveFormat>(static_cast<std::uint8_t>(load_format));
}

}  // namespace cdocx
