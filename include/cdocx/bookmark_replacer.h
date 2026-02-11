/**
 * @file bookmark_replacer.h
 * @brief High-level bookmark replacement API
 * @details Provides BookmarkReplacer class for easy bookmark-based content
 *          replacement including text and images with format preservation.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 * 
 * @par Usage Example:
 * @code
 * #include <cdocx/bookmark_replacer.h>
 * 
 * cdocx::Document doc("template.docx");
 * doc.open();
 * 
 * cdocx::BookmarkReplacer replacer(&doc);
 * 
 * // Simple text replacement (preserves format)
 * replacer.replace_text("NAME", "John Doe");
 * replacer.replace_text("DATE", "2024-06-15");
 * 
 * // Batch replacement
 * std::map<std::string, std::string> replacements = {
 *     {"COMPANY", "Acme Corp"},
 *     {"ADDRESS", "123 Main St"}
 * };
 * replacer.replace_text_batch(replacements);
 * 
 * // Image replacement with caption
 * replacer.replace_with_image("LOGO", "logo.png", "Company Logo");
 * 
 * // Advanced image replacement
 * cdocx::ImageSize size(400, 300);  // 400x300 points
 * replacer.replace_with_image_advanced("CHART", "chart.png", size, 
 *                                      "Sales Chart", cdocx::ImageAlignment::Center);
 * 
 * // Check statistics
 * auto stats = replacer.get_stats();
 * std::cout << "Success: " << stats.success_count << std::endl;
 * 
 * doc.save("output.docx");
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/advanced.h>
#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace cdocx {

// Forward declaration
class Bookmark;

/**
 * @typedef ReplaceCallback
 * @brief Callback function type for conditional replacement
 * @param bookmark_name Name of the bookmark being processed
 * @param old_text Current text content
 * @param new_text Output parameter for new text
 * @return true to proceed with replacement, false to skip
 */
using ReplaceCallback = std::function<bool(const std::string& bookmark_name,
                                            const std::string& old_text,
                                            std::string& new_text)>;

/**
 * @struct ReplacementStats
 * @brief Statistics for replacement operations
 * @since 0.3.0
 */
struct ReplacementStats {
    int success_count = 0;  ///< Number of successful replacements
    int fail_count = 0;     ///< Number of failed replacements
    int skip_count = 0;     ///< Number of skipped replacements
    
    /**
     * @brief Reset all counters to zero
     */
    void reset() {
        success_count = 0;
        fail_count = 0;
        skip_count = 0;
    }
    
    /**
     * @brief Get total operations count
     * @return Sum of success, fail, and skip
     */
    int total() const {
        return success_count + fail_count + skip_count;
    }
};

/**
 * @class BookmarkReplacer
 * @brief High-level API for bookmark-based content replacement
 * @details Provides a convenient interface for replacing bookmark content
 *          with text or images while preserving or controlling formatting.
 * 
 * @par Features:
 * - Text replacement with format preservation
 * - Batch text replacement
 * - Image insertion with automatic caption generation
 * - Alignment control for images
 * - Conditional replacement via callbacks
 * - Detailed statistics tracking
 * 
 * @since 0.3.0
 */
class BookmarkReplacer {
public:
    /**
     * @brief Construct replacer for a document
     * @param[in] doc Target document (must remain valid during replacer lifetime)
     */
    explicit BookmarkReplacer(Document* doc);
    
    /**
     * @brief Destructor
     */
    ~BookmarkReplacer() = default;
    
    // Disable copy, enable move
    BookmarkReplacer(const BookmarkReplacer&) = delete;
    BookmarkReplacer& operator=(const BookmarkReplacer&) = delete;
    BookmarkReplacer(BookmarkReplacer&&) = default;
    BookmarkReplacer& operator=(BookmarkReplacer&&) = default;

    // ========================================================================
    // Text Replacement
    // ========================================================================

    /**
     * @brief Replace bookmark text (preserves original format)
     * @param[in] bookmark_name Name of the bookmark to replace
     * @param[in] new_text New text content
     * @return true if replacement was successful
     */
    bool replace_text(const std::string& bookmark_name,
                      const std::string& new_text);

    /**
     * @brief Replace multiple bookmarks in batch
     * @param[in] replacements Map of bookmark_name -> new_text
     * @return Number of successful replacements
     */
    int replace_text_batch(const std::map<std::string, std::string>& replacements);

    /**
     * @brief Replace text with explicit format control
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] new_text New text content
     * @param[in] format Format specification to apply
     * @return true if replacement was successful
     */
    bool replace_text_with_format(const std::string& bookmark_name,
                                   const std::string& new_text,
                                   const BookmarkFormat& format);

    // ========================================================================
    // Image Replacement
    // ========================================================================

    /**
     * @brief Replace bookmark with image (simple version)
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] image_path Path to image file (PNG, JPG, etc.)
     * @param[in] caption Optional caption text (generates "图 X caption" format)
     * @return true if replacement was successful
     * @details Image is centered by default. Caption is auto-generated if provided.
     */
    bool replace_with_image(const std::string& bookmark_name,
                            const std::string& image_path,
                            const std::string& caption = "");

    /**
     * @brief Replace bookmark with image (advanced version)
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] image_path Path to image file
     * @param[in] size Image dimensions in points
     * @param[in] caption Optional caption text
     * @param[in] align Image alignment (Left, Center, Right)
     * @return true if replacement was successful
     */
    bool replace_with_image_advanced(const std::string& bookmark_name,
                                      const std::string& image_path,
                                      const ImageSize& size,
                                      const std::string& caption = "",
                                      ImageAlignment align = ImageAlignment::Center);

    /**
     * @brief Replace bookmark with image from memory
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] image_data Binary image data
     * @param[in] image_name Name for the image in document
     * @param[in] size Image dimensions
     * @param[in] caption Optional caption
     * @param[in] align Image alignment
     * @return true if replacement was successful
     */
    bool replace_with_image_from_memory(const std::string& bookmark_name,
                                        const std::vector<uint8_t>& image_data,
                                        const std::string& image_name,
                                        const ImageSize& size,
                                        const std::string& caption = "",
                                        ImageAlignment align = ImageAlignment::Center);

    // ========================================================================
    // Advanced Features
    // ========================================================================

    /**
     * @brief Replace using callback for conditional logic
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] callback Function to determine replacement
     * @return true if callback returned true and replacement succeeded
     */
    bool replace_if(const std::string& bookmark_name, ReplaceCallback callback);

    /**
     * @brief Replace text and remove bookmark markers
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] new_text New text content
     * @return true if successful
     */
    bool replace_and_remove(const std::string& bookmark_name,
                            const std::string& new_text);

    /**
     * @brief Replace with image and remove bookmark
     * @param[in] bookmark_name Name of the bookmark
     * @param[in] image_path Path to image file
     * @param[in] caption Optional caption
     * @return true if successful
     */
    bool replace_with_image_and_remove(const std::string& bookmark_name,
                                        const std::string& image_path,
                                        const std::string& caption = "");

    // ========================================================================
    // Query Methods
    // ========================================================================

    /**
     * @brief Check if bookmark exists in document
     * @param[in] bookmark_name Name to check
     * @return true if bookmark exists
     */
    bool has_bookmark(const std::string& bookmark_name) const;

    /**
     * @brief Get all bookmark names in document
     * @return Vector of bookmark names
     */
    std::vector<std::string> list_bookmarks() const;

    /**
     * @brief Get bookmark text content
     * @param[in] bookmark_name Name of the bookmark
     * @return Text content, or empty string if not found
     */
    std::string get_bookmark_text(const std::string& bookmark_name) const;

    // ========================================================================
    // Statistics
    // ========================================================================

    /**
     * @brief Get replacement statistics
     * @return Statistics structure
     */
    ReplacementStats get_stats() const { return stats_; }

    /**
     * @brief Reset statistics counters
     */
    void reset_stats() { stats_.reset(); }

private:
    Document* doc_;                      ///< Target document
    ReplacementStats stats_;             ///< Operation statistics
    mutable int next_image_id_ = 1;      ///< Counter for image IDs

    /**
     * @brief Get bookmark by name
     * @param[in] name Bookmark name
     * @return Bookmark object, or std::nullopt if not found
     */
    std::optional<Bookmark> get_bookmark(const std::string& name) const;

    /**
     * @brief Clear bookmark content (remove runs between markers)
     * @param[in,out] bookmark Bookmark to clear
     * @return true if successful
     */
    bool clear_bookmark_content(Bookmark& bookmark);

    /**
     * @brief Generate unique image ID for document
     * @return Unique ID string
     */
    int generate_image_id() const { return next_image_id_++; }

    /**
     * @brief Insert image at bookmark location
     * @param[in,out] bookmark Target bookmark
     * @param[in] image_path Image file path
     * @param[in] size Image dimensions
     * @param[in] align Alignment
     * @param[in] rel_id Relationship ID for the image
     * @return true if successful
     */
    bool insert_image_at_bookmark(Bookmark& bookmark,
                                   const std::string& image_path,
                                   const ImageSize& size,
                                   ImageAlignment align,
                                   const std::string& rel_id);

    /**
     * @brief Get file extension from path
     * @param[in] path File path
     * @return Extension without dot, or empty string
     */
    std::string get_file_extension(const std::string& path) const;

    /**
     * @brief Get content type from file extension
     * @param[in] ext File extension
     * @return MIME content type
     */
    std::string get_content_type(const std::string& ext) const;
};

} // namespace cdocx
