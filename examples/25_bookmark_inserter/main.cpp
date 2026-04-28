/**
 * @file main.cpp
 * @brief Example: BookmarkInserter API
 * @version 0.8.0
 *
 * Demonstrates how to:
 * 1. Insert bookmarks around existing text in a document
 * 2. Use insert_all to bookmark every occurrence
 * 3. Use insert_batch for multiple bookmarks at once
 * 4. Verify inserted bookmarks via Document::get_bookmarks()
 */

#include <cdocx.h>
#include <cdocx/bookmark_inserter.h>
#include <iostream>
#include <map>

int main() {
    std::cout << "=== CDocx BookmarkInserter Example ===" << std::endl;

    // ------------------------------------------------------------------------
    // Create a document with plain text (no bookmarks yet)
    // ------------------------------------------------------------------------
    std::cout << "\n1. Creating source document with plain text..." << std::endl;

    cdocx::Document doc;
    doc.create_empty("bookmark_inserter_demo.docx");

    auto body = doc.get_first_section()->get_body();
    body->append_paragraph("Project: Alpha Survey 2024");
    body->append_paragraph("Client: Beijing Geological Research Institute");
    body->append_paragraph("Date: 2024-06-15");
    body->append_paragraph("Contact: Dr. Li Wei");

    doc.save();
    std::cout << "   Created source document." << std::endl;

    // ------------------------------------------------------------------------
    // Reopen and insert bookmarks around existing text
    // ------------------------------------------------------------------------
    std::cout << "\n2. Inserting bookmarks around existing text..." << std::endl;

    cdocx::Document doc2("bookmark_inserter_demo.docx");
    doc2.open();
    if (!doc2.is_open()) {
        std::cerr << "Failed to open document" << std::endl;
        return 1;
    }

    // Sync DOM to physical tree so BookmarkInserter can work with raw XML
    doc2.sync_to_physical_tree();

    cdocx::BookmarkInserter inserter(&doc2);

    // Insert single bookmark around first occurrence
    bool ok1 = inserter.insert("PROJECT", "Alpha Survey 2024");
    std::cout << "   Insert 'PROJECT': " << (ok1 ? "success" : "failed") << std::endl;

    bool ok2 = inserter.insert("CLIENT", "Beijing Geological Research Institute");
    std::cout << "   Insert 'CLIENT': " << (ok2 ? "success" : "failed") << std::endl;

    bool ok3 = inserter.insert("DATE", "2024-06-15");
    std::cout << "   Insert 'DATE': " << (ok3 ? "success" : "failed") << std::endl;

    bool ok4 = inserter.insert("CONTACT", "Dr. Li Wei");
    std::cout << "   Insert 'CONTACT': " << (ok4 ? "success" : "failed") << std::endl;

    // Rebuild DOM from physical tree so bookmarks survive save/sync cycle
    doc2.sync_from_physical_tree();
    doc2.save();
    std::cout << "   Saved bookmarked document." << std::endl;

    // ------------------------------------------------------------------------
    // Verify bookmarks were created
    // ------------------------------------------------------------------------
    std::cout << "\n3. Verifying inserted bookmarks..." << std::endl;

    auto bookmarks = doc2.get_bookmarks();
    std::cout << "   Total bookmarks: " << bookmarks.count() << std::endl;

    auto names = bookmarks.get_names();
    for (const auto& name : names) {
        auto bm = bookmarks.get(name);
        if (bm.has_value()) {
            std::cout << "   - " << name << ": \"" << bm->get_text() << "\"" << std::endl;
        }
    }

    // ------------------------------------------------------------------------
    // Example 4: Batch insert on a fresh document
    // ------------------------------------------------------------------------
    std::cout << "\n4. Batch inserting multiple bookmarks..." << std::endl;

    cdocx::Document doc3;
    doc3.create_empty("bookmark_batch_demo.docx");

    auto body3 = doc3.get_first_section()->get_body();
    body3->append_paragraph("Invoice #INV-2024-001");
    body3->append_paragraph("Total Amount: $1,299.00");
    body3->append_paragraph("Due Date: 2024-07-15");

    doc3.sync_to_physical_tree();

    cdocx::BookmarkInserter batch_inserter(&doc3);
    std::map<std::string, std::string> fields = {
        {"INVOICE_NO", "INV-2024-001"},
        {"AMOUNT", "$1,299.00"},
        {"DUE_DATE", "2024-07-15"},
    };

    int inserted = batch_inserter.insert_batch(fields);
    std::cout << "   Batch inserted " << inserted << " / " << fields.size()
              << " bookmarks." << std::endl;

    doc3.sync_from_physical_tree();
    doc3.save();

    auto batch_bookmarks = doc3.get_bookmarks();
    std::cout << "   Verified bookmarks: " << batch_bookmarks.count() << std::endl;

    std::cout << "\n=== Example Complete ===" << std::endl;
    return 0;
}
