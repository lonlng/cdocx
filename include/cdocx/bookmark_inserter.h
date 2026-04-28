#pragma once

#include <cdocx/document.h>

#include <map>
#include <string>

namespace cdocx {

/**
 * @class BookmarkInserter
 * @brief Programmatically insert bookmarks around existing text in a document.
 * @details Searches for the first occurrence of a text string in the document
 *          and wraps it with <w:bookmarkStart> / <w:bookmarkEnd> markers.
 *          Handles text that spans multiple adjacent runs within a paragraph.
 *
 * @par Usage Example:
 * @code
 * cdocx::Document doc("report.docx");
 * doc.open();
 *
 * cdocx::BookmarkInserter inserter(&doc);
 * inserter.insert("COMPANY", "Acme Inc.");
 * inserter.insert("DATE", "2024-01-15");
 * doc.save("template.docx");
 * @endcode
 *
 * @since 0.8.0
 */
class BookmarkInserter {
  public:
    /**
     * @brief Construct inserter for a document.
     * @param[in] doc Target document (must remain valid during inserter lifetime)
     */
    explicit BookmarkInserter(Document* doc);

    ~BookmarkInserter() = default;

    // Disable copy, enable move
    BookmarkInserter(const BookmarkInserter&) = delete;
    BookmarkInserter& operator=(const BookmarkInserter&) = delete;
    BookmarkInserter(BookmarkInserter&&) = default;
    BookmarkInserter& operator=(BookmarkInserter&&) = default;

    /**
     * @brief Insert a bookmark around the first occurrence of text.
     * @param[in] bookmark_name Name for the new bookmark.
     * @param[in] text Text to search for and wrap.
     * @return true if the bookmark was inserted successfully.
     */
    bool insert(const std::string& bookmark_name, const std::string& text);

    /**
     * @brief Insert bookmarks around ALL occurrences of text in the document.
     * @param[in] bookmark_name Name for the new bookmarks.
     * @param[in] text Text to search for and wrap.
     * @return Number of bookmarks inserted.
     */
    int insert_all(const std::string& bookmark_name, const std::string& text);

    /**
     * @brief Insert multiple bookmarks in one call.
     * @param[in] mappings Map of bookmark_name -> text_to_find.
     * @return Number of successful insertions.
     */
    int insert_batch(const std::map<std::string, std::string>& mappings);

  private:
    Document* doc_ = nullptr;
    int next_bookmark_id_ = 1;

    int allocate_bookmark_id();
    bool insert_in_paragraph(pugi::xml_node paragraph,
                             const std::string& bookmark_name,
                             const std::string& text);
};

}  // namespace cdocx
