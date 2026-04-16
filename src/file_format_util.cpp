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

static std::string ToLower(std::string s) {
    for (auto& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

static bool StartsWith(const std::vector<uint8_t>& data, const char* prefix, size_t len) {
    if (data.size() < len) return false;
    return std::memcmp(data.data(), prefix, len) == 0;
}

static bool StartsWithString(const std::vector<uint8_t>& data, const char* prefix) {
    size_t len = std::strlen(prefix);
    if (data.size() < len) return false;
    return std::memcmp(data.data(), prefix, len) == 0;
}

static bool Contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

static std::string ReadZipEntry(zip_t* za, const std::string& entry_name) {
    if (zip_entry_open(za, entry_name.c_str()) != 0) {
        return "";
    }
    void* buf = nullptr;
    size_t bufsize = 0;
    ssize_t read = zip_entry_read(za, &buf, &bufsize);
    zip_entry_close(za);
    if (read <= 0 || !buf) {
        return "";
    }
    std::string result(static_cast<const char*>(buf), static_cast<size_t>(read));
    free(buf);  // NOLINT: zip_entry_read allocates with malloc
    return result;
}

static std::shared_ptr<FileFormatInfo> DetectFromZip(zip_t* za) {
    auto info = std::make_shared<FileFormatInfo>();

    std::string content_types = ReadZipEntry(za, "[Content_Types].xml");
    if (content_types.empty()) {
        info->set_load_format(LoadFormat::Unknown);
        return info;
    }

    std::string ct_lower = ToLower(content_types);

    // Detect macros
    if (Contains(ct_lower, "macros") || Contains(ct_lower, "vnd.ms-office.vba")) {
        info->set_has_macros(true);
    }

    // Detect digital signatures
    if (Contains(ct_lower, "digital-signature") || Contains(ct_lower, "office.digitalsignature")) {
        info->set_has_digital_signature(true);
    }

    // Detect encryption
    if (Contains(ct_lower, "encrypted-package") || Contains(ct_lower, "encryption")) {
        info->set_is_encrypted(true);
    }

    // Determine exact Word format
    if (Contains(ct_lower, "wordprocessingml.document.macroenabled.main+xml")) {
        info->set_load_format(LoadFormat::Docm);
    } else if (Contains(ct_lower, "wordprocessingml.template.macroenabled.main+xml")) {
        info->set_load_format(LoadFormat::Dotm);
    } else if (Contains(ct_lower, "wordprocessingml.template.main+xml")) {
        info->set_load_format(LoadFormat::Dotx);
    } else if (Contains(ct_lower, "wordprocessingml.document.main+xml")) {
        info->set_load_format(LoadFormat::Docx);
    } else if (Contains(ct_lower, "spreadsheetml") || Contains(ct_lower, "presentationml")) {
        info->set_load_format(LoadFormat::Unknown);
    } else {
        // Could be ODT - check mimetype
        std::string mimetype = ReadZipEntry(za, "mimetype");
        std::string mime_lower = ToLower(mimetype);
        if (Contains(mime_lower, "application/vnd.oasis.opendocument.text")) {
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

std::shared_ptr<FileFormatInfo> FileFormatUtil::DetectFileFormat(const std::string& file_name) {
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        return std::make_shared<FileFormatInfo>();
    }
    return DetectFileFormat(file);
}

std::shared_ptr<FileFormatInfo> FileFormatUtil::DetectFileFormat(std::istream& stream) {
    auto info = std::make_shared<FileFormatInfo>();

    // Remember position
    auto start_pos = stream.tellg();

    // Read first 8KB for sniffing
    std::vector<uint8_t> buffer(8192);
    stream.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(buffer.size()));
    std::streamsize bytes_read = stream.gcount();
    buffer.resize(static_cast<size_t>(bytes_read));

    // Restore position
    stream.seekg(start_pos);

    if (buffer.empty()) {
        return info;
    }

    // ZIP-based formats (DOCX, DOTX, DOCM, DOTM, ODT)
    if (StartsWith(buffer, "PK\x03\x04", 4) || StartsWith(buffer, "PK\x05\x06", 4)) {
        zip_t* za = zip_stream_open(reinterpret_cast<const char*>(buffer.data()),
                                    buffer.size(), 0, 'r');
        if (za) {
            info = DetectFromZip(za);
            zip_stream_close(za);
        }
        return info;
    }

    // RTF
    if (StartsWithString(buffer, "{\\rtf")) {
        info->set_load_format(LoadFormat::Rtf);
        return info;
    }

    // HTML
    {
        std::string head(buffer.begin(),
                         buffer.begin() + std::min(static_cast<size_t>(256), buffer.size()));
        std::string lower = ToLower(head);
        if (StartsWithString(buffer, "<!doctype html") ||
            Contains(lower, "<html") ||
            Contains(lower, "<head")) {
            info->set_load_format(LoadFormat::Html);
            // Try to detect encoding from meta tag
            size_t charset_pos = lower.find("charset=");
            if (charset_pos != std::string::npos) {
                size_t start = charset_pos + 8;
                if (start < lower.size() && (lower[start] == '"' || lower[start] == '\'')) {
                    char quote = lower[start];
                    size_t end = lower.find(quote, start + 1);
                    if (end != std::string::npos) {
                        info->set_encoding(head.substr(start + 1, end - start - 1));
                    }
                } else {
                    size_t end = lower.find_first_of(" ;\">\r\n", start);
                    if (end != std::string::npos) {
                        info->set_encoding(head.substr(start, end - start));
                    }
                }
            }
            return info;
        }
    }

    // XML
    if (StartsWithString(buffer, "<?xml")) {
        info->set_load_format(LoadFormat::Xml);
        return info;
    }

    // Markdown - look for common markers in first few lines
    {
        std::string head(buffer.begin(),
                         buffer.begin() + std::min(static_cast<size_t>(512), buffer.size()));
        std::string lower = ToLower(head);
        if (Contains(lower, "# ") || Contains(lower, "## ") ||
            Contains(lower, "**") || Contains(lower, "__") ||
            Contains(lower, "-") || Contains(lower, "|")) {
            info->set_load_format(LoadFormat::Markdown);
            return info;
        }
    }

    // Plain text - if no null bytes and mostly printable
    bool has_null = false;
    size_t printable = 0;
    for (uint8_t b : buffer) {
        if (b == 0) has_null = true;
        if (b >= 32 && b <= 126) printable++;
        if (b == '\n' || b == '\r' || b == '\t') printable++;
    }
    if (!has_null && printable > buffer.size() * 0.8) {
        info->set_load_format(LoadFormat::Text);
        return info;
    }

    return info;
}

std::shared_ptr<FileFormatInfo> FileFormatUtil::DetectFileFormat(const std::vector<uint8_t>& data) {
    std::stringstream ss(std::string(data.begin(), data.end()));
    return DetectFileFormat(ss);
}

std::string FileFormatUtil::LoadFormatToExtension(LoadFormat load_format) {
    switch (load_format) {
        case LoadFormat::Docx: return ".docx";
        case LoadFormat::Docm: return ".docm";
        case LoadFormat::Dotx: return ".dotx";
        case LoadFormat::Dotm: return ".dotm";
        case LoadFormat::FlatOpc: return ".fopc";
        case LoadFormat::Rtf: return ".rtf";
        case LoadFormat::Html: return ".html";
        case LoadFormat::Odt: return ".odt";
        case LoadFormat::Text: return ".txt";
        case LoadFormat::Markdown: return ".md";
        case LoadFormat::Xml: return ".xml";
        default: return "";
    }
}

std::string FileFormatUtil::SaveFormatToExtension(SaveFormat save_format) {
    switch (save_format) {
        case SaveFormat::Docx: return ".docx";
        case SaveFormat::Docm: return ".docm";
        case SaveFormat::Dotx: return ".dotx";
        case SaveFormat::Dotm: return ".dotm";
        case SaveFormat::FlatOpc: return ".fopc";
        case SaveFormat::Rtf: return ".rtf";
        case SaveFormat::Html: return ".html";
        case SaveFormat::Odt: return ".odt";
        case SaveFormat::Text: return ".txt";
        case SaveFormat::Markdown: return ".md";
        case SaveFormat::Xml: return ".xml";
        default: return "";
    }
}

SaveFormat FileFormatUtil::ExtensionToSaveFormat(const std::string& extension) {
    std::string ext = ToLower(extension);
    if (!ext.empty() && ext[0] != '.') {
        ext = "." + ext;
    }
    if (ext == ".docx") return SaveFormat::Docx;
    if (ext == ".docm") return SaveFormat::Docm;
    if (ext == ".dotx") return SaveFormat::Dotx;
    if (ext == ".dotm") return SaveFormat::Dotm;
    if (ext == ".fopc" || ext == ".flatopc") return SaveFormat::FlatOpc;
    if (ext == ".rtf") return SaveFormat::Rtf;
    if (ext == ".html" || ext == ".htm") return SaveFormat::Html;
    if (ext == ".odt") return SaveFormat::Odt;
    if (ext == ".txt" || ext == ".text") return SaveFormat::Text;
    if (ext == ".md" || ext == ".markdown") return SaveFormat::Markdown;
    if (ext == ".xml" || ext == ".wordml" || ext == ".wml") return SaveFormat::Xml;
    return SaveFormat::Unknown;
}

LoadFormat FileFormatUtil::SaveFormatToLoadFormat(SaveFormat save_format) {
    switch (save_format) {
        case SaveFormat::Docx: return LoadFormat::Docx;
        case SaveFormat::Docm: return LoadFormat::Docm;
        case SaveFormat::Dotx: return LoadFormat::Dotx;
        case SaveFormat::Dotm: return LoadFormat::Dotm;
        case SaveFormat::FlatOpc: return LoadFormat::FlatOpc;
        case SaveFormat::Rtf: return LoadFormat::Rtf;
        case SaveFormat::Html: return LoadFormat::Html;
        case SaveFormat::Odt: return LoadFormat::Odt;
        case SaveFormat::Text: return LoadFormat::Text;
        case SaveFormat::Markdown: return LoadFormat::Markdown;
        case SaveFormat::Xml: return LoadFormat::Xml;
        default: return LoadFormat::Unknown;
    }
}

SaveFormat FileFormatUtil::LoadFormatToSaveFormat(LoadFormat load_format) {
    switch (load_format) {
        case LoadFormat::Docx: return SaveFormat::Docx;
        case LoadFormat::Docm: return SaveFormat::Docm;
        case LoadFormat::Dotx: return SaveFormat::Dotx;
        case LoadFormat::Dotm: return SaveFormat::Dotm;
        case LoadFormat::FlatOpc: return SaveFormat::FlatOpc;
        case LoadFormat::Rtf: return SaveFormat::Rtf;
        case LoadFormat::Html: return SaveFormat::Html;
        case LoadFormat::Odt: return SaveFormat::Odt;
        case LoadFormat::Text: return SaveFormat::Text;
        case LoadFormat::Markdown: return SaveFormat::Markdown;
        case LoadFormat::Xml: return SaveFormat::Xml;
        default: return SaveFormat::Unknown;
    }
}

} // namespace cdocx
