/**
 * @file main.cpp
 * @brief Example: CommentCollection API
 * @version 0.8.0
 *
 * Demonstrates how to:
 * 1. Add comments to document text
 * 2. Iterate and inspect comments
 * 3. Reply to comments
 * 4. Remove comments by index or ID
 * 5. Clear all comments
 */

#include <cdocx.h>
#include <iostream>

int main() {
    std::cout << "=== CDocx CommentCollection Example ===" << std::endl;

    cdocx::Document doc;
    if (!doc.create_empty("comments_demo.docx")) {
        std::cerr << "Failed to create document" << std::endl;
        return 1;
    }

    auto body = doc.get_first_section()->get_body();

    // ------------------------------------------------------------------------
    // Example 1: Add a simple comment on a paragraph
    // ------------------------------------------------------------------------
    std::cout << "\n1. Adding comments..." << std::endl;

    auto para1 = body->append_paragraph(
        "This paragraph contains important findings from the survey.");

    // Wrap the entire paragraph in a comment range
    auto comment_start = std::make_shared<cdocx::CommentRangeStart>(&doc, 0);
    auto comment_end = std::make_shared<cdocx::CommentRangeEnd>(&doc, 0);
    para1->insert_child(0, comment_start);
    para1->append_child(comment_end);

    // Add the actual comment text
    auto comment = doc.add_comment("Alice", "Please verify these findings with the source data.");
    comment->set_initial("A");
    std::cout << "   Added comment by Alice (id=" << comment->get_id() << ")" << std::endl;

    // ------------------------------------------------------------------------
    // Example 2: Add a comment on a specific run
    // ------------------------------------------------------------------------
    auto para2 = body->append_paragraph("Revenue increased by 25% compared to last year.");
    auto runs = para2->get_runs();
    if (runs.get_count() > 0) {
        auto run = runs[0];

        auto cs2 = std::make_shared<cdocx::CommentRangeStart>(&doc, 1);
        auto ce2 = std::make_shared<cdocx::CommentRangeEnd>(&doc, 1);

        // Insert range start before the run, end after
        para2->CompositeNode::insert_before(cs2, run);
        para2->append_child(ce2);

        auto comment2 = doc.add_comment("Bob", "Double-check the percentage calculation.");
        comment2->set_initial("B");
        std::cout << "   Added comment by Bob (id=" << comment2->get_id() << ")" << std::endl;
    }

    // ------------------------------------------------------------------------
    // Example 3: Iterate over all comments
    // ------------------------------------------------------------------------
    std::cout << "\n2. Iterating comments via CommentCollection..." << std::endl;

    auto collection = doc.get_comments();
    std::cout << "   Total comments: " << collection.count() << std::endl;

    for (size_t i = 0; i < collection.count(); ++i) {
        auto c = collection.get(i);
        std::cout << "   [" << i << "] " << c->get_author()
                  << " (" << c->get_initial() << "): \""
                  << c->get_text() << "\"" << std::endl;
    }

    // ------------------------------------------------------------------------
    // Example 4: Lookup by ID
    // ------------------------------------------------------------------------
    std::cout << "\n3. Looking up comment by ID..." << std::endl;

    auto found = collection.get_by_id(0);
    if (found) {
        std::cout << "   Found comment 0: \"" << found->get_text() << "\"" << std::endl;
    }

    bool has_it = collection.contains(1);
    std::cout << "   Contains comment 1: " << (has_it ? "yes" : "no") << std::endl;

    // ------------------------------------------------------------------------
    // Example 5: Add a reply comment
    // ------------------------------------------------------------------------
    std::cout << "\n4. Adding a reply comment..." << std::endl;

    auto reply = collection.add("Alice", "Confirmed: source data matches.");
    reply->set_parent_comment_id(0);
    std::cout << "   Added reply to comment 0 (id=" << reply->get_id() << ")" << std::endl;

    // ------------------------------------------------------------------------
    // Example 6: Remove a comment
    // ------------------------------------------------------------------------
    std::cout << "\n5. Removing comment by index..." << std::endl;

    collection.remove_at(1);
    std::cout << "   Remaining comments: " << collection.count() << std::endl;

    // ------------------------------------------------------------------------
    // Example 7: Save
    // ------------------------------------------------------------------------
    doc.save();
    std::cout << "\nSaved: comments_demo.docx" << std::endl;
    std::cout << "=== Example Complete ===" << std::endl;

    return 0;
}
