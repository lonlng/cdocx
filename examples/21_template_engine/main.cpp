/**
 * @file main.cpp
 * @brief TemplateEngine comprehensive usage demonstration
 * @since 0.8.0
 */

#include <cdocx.h>
#include <cdocx/bookmark_inserter.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/template_engine.h>

#include <filesystem>
#include <iostream>

int main() {
    // =====================================================================
    // Phase 1: Create a document with both placeholders and bookmarks
    // =====================================================================
    auto doc = cdocx::CDocx::create_document();
    auto sections = doc->get_sections();
    auto body = sections[0]->get_body();

    body->append_paragraph("Company: {{company}}  Date: {{date}}");
    body->append_paragraph("Report: {{title}}");
    body->append_paragraph("Author: John Smith");
    body->append_paragraph("Signature: __SIGN__");
    body->append_paragraph("Logo: {{logo}}");

    doc->save("template_engine_demo.docx");
    std::cout << "Template created: template_engine_demo.docx\n";

    // =====================================================================
    // Phase 2: Insert bookmarks around known text
    // =====================================================================
    cdocx::Document bookmarked("template_engine_demo.docx");
    bookmarked.open();

    cdocx::BookmarkInserter inserter(&bookmarked);
    inserter.insert("AUTHOR", "John Smith");
    inserter.insert("SIGNATURE", "__SIGN__");

    bookmarked.sync_from_physical_tree();
    bookmarked.save("template_engine_bookmarked.docx");
    std::cout << "Bookmarked template: template_engine_bookmarked.docx\n";

    // Debug: check bookmarks exist
    {
        cdocx::Document dbg("template_engine_bookmarked.docx");
        dbg.open();
        cdocx::BookmarkReplacer replacer(&dbg);
        std::cout << "\n=== Bookmark check ===\n";
        std::cout << "Has AUTHOR:    " << replacer.has_bookmark("AUTHOR") << "\n";
        std::cout << "Has SIGNATURE: " << replacer.has_bookmark("SIGNATURE") << "\n";
        auto bms = replacer.list_bookmarks();
        std::cout << "All bookmarks: " << bms.size() << "\n";
        for (const auto& n : bms) {
            std::cout << "  - " << n << "\n";
        }
    }

    // =====================================================================
    // Phase 3: Use TemplateEngine to fill everything
    // =====================================================================
    cdocx::Document filled("template_engine_bookmarked.docx");
    filled.open();

    cdocx::TemplateEngine engine(&filled);

    // --- Dictionary style ---
    engine["company"] = cdocx::TemplateValue::Text("Acme Inc.");
    engine["date"]    = "2025-04-21";

    // --- Custom format ---
    engine["title"] = cdocx::TemplateValue::Text("Annual Report")
        .with_format(cdocx::TemplateFormat().bold().Size(24).color("FF0000"));

    // --- Bookmark targets (Auto mode will find these) ---
    engine["AUTHOR"]    = cdocx::TemplateValue::Text("Jane Doe");
    engine["SIGNATURE"] = cdocx::TemplateValue::Text("APPROVED");

    // --- Image placeholder (if sample image exists) ---
    if (std::filesystem::exists("sample_logo.png")) {
        engine["logo"] = cdocx::TemplateValue::Image("sample_logo.png")
            .sized(200, 100)
            .centered();
    }

    // --- Batch from map ---
    std::map<std::string, std::string> extras = {
        {"footer", "Confidential"},
    };
    engine.set_batch(extras);

    // --- Apply with Auto target (bookmark first, then placeholder) ---
    auto result = engine
        .with_scope(cdocx::TemplateScope::All)
        .with_target(cdocx::TemplateTarget::Auto)
        .apply();

    std::cout << "\n=== Results ===\n";
    std::cout << "Success: " << result.success << "\n";
    std::cout << "Failed:  " << result.failed << "\n";
    std::cout << "Skipped: " << result.skipped << "\n";

    filled.save("template_engine_output.docx");
    std::cout << "\nOutput: template_engine_output.docx\n";

    return 0;
}
