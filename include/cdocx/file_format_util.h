/**
 * @file file_format_util.h
 * @brief File format detection and conversion utilities
 * @version 0.7.0
 *
 * Provides utility methods for working with file formats, such as detecting
 * file format or converting file extensions to/from file format enums.
 *
 * @par Usage Example:
 * @code
 * auto info = cdocx::FileFormatUtil::DetectFileFormat("document.docx");
 * if (info->load_format() == cdocx::LoadFormat::Docx) {
 *     std::cout << "It's a DOCX file!" << std::endl;
 * }
 * @endcode
 */

#pragma once

#include <cdocx/enums.h>

#include <istream>
#include <memory>
#include <string>
#include <vector>

namespace cdocx {

// ============================================================================
// FileFormatInfo
// ============================================================================

/**
 * @brief Contains data returned by FileFormatUtil document format detection
 */
class FileFormatInfo {
  public:
    FileFormatInfo();

    /// Gets the detected document format
    LoadFormat load_format() const { return load_format_; }
    void set_load_format(LoadFormat value) { load_format_ = value; }

    /// Returns true if the document is encrypted and requires a password
    bool is_encrypted() const { return is_encrypted_; }
    void set_is_encrypted(bool value) { is_encrypted_ = value; }

    /// Returns true if this document contains a digital signature
    bool has_digital_signature() const { return has_digital_signature_; }
    void set_has_digital_signature(bool value) { has_digital_signature_ = value; }

    /// Returns true if this document contains VBA macros
    bool has_macros() const { return has_macros_; }
    void set_has_macros(bool value) { has_macros_ = value; }

    /// Gets the detected encoding if applicable (e.g., HTML)
    const std::string& encoding() const { return encoding_; }
    void set_encoding(const std::string& value) { encoding_ = value; }

  private:
    LoadFormat load_format_ = LoadFormat::Unknown;
    bool is_encrypted_ = false;
    bool has_digital_signature_ = false;
    bool has_macros_ = false;
    std::string encoding_;
};

// ============================================================================
// FileFormatUtil
// ============================================================================

/**
 * @brief Provides utility methods for working with file formats
 */
class FileFormatUtil {
  public:
    FileFormatUtil() = delete;

    /**
     * @brief Detects and returns information about a format of a document file
     * @param file_name Path to the file
     * @return FileFormatInfo containing detected information
     */
    static std::shared_ptr<FileFormatInfo> DetectFileFormat(const std::string& file_name);

    /**
     * @brief Detects and returns information about a format from a stream
     * @param stream Input stream positioned at the beginning
     * @return FileFormatInfo containing detected information
     */
    static std::shared_ptr<FileFormatInfo> DetectFileFormat(std::istream& stream);

    /**
     * @brief Detects and returns information about a format from a byte buffer
     * @param data Byte buffer containing document data
     * @return FileFormatInfo containing detected information
     */
    static std::shared_ptr<FileFormatInfo> DetectFileFormat(const std::vector<uint8_t>& data);

    /// Converts a load format enumerated value into a file extension
    static std::string LoadFormatToExtension(LoadFormat load_format);

    /// Converts a save format enumerated value into a file extension
    static std::string SaveFormatToExtension(SaveFormat save_format);

    /// Converts a file name extension into a SaveFormat value
    static SaveFormat ExtensionToSaveFormat(const std::string& extension);

    /// Converts a SaveFormat value to a LoadFormat value if possible
    static LoadFormat SaveFormatToLoadFormat(SaveFormat save_format);

    /// Converts a LoadFormat value to a SaveFormat value if possible
    static SaveFormat LoadFormatToSaveFormat(LoadFormat load_format);
};

}  // namespace cdocx
