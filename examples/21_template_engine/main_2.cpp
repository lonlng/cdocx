/**
 * @file main_2.cpp
 * @brief TemplateEngine usage with an existing template document
 * @details Demonstrates loading a pre-built DOCX template that contains
 *          both placeholders ({{key}}) and bookmarks, then replacing them
 *          with text and images via the dictionary-style TemplateEngine API.
 *
 *          Highlights of this example:
 *          - Text placeholders and bookmarks with custom formatting
 *          - Image replacement with automatic captions
 *          - TemplateEngine / DOM interoperability
 *
 * @par TemplateEngine and DOM Interoperability
 * TemplateEngine operates at a higher level than the raw DOM. During
 * `apply()`, it internally calls `sync_to_physical_tree()` after DOM
 * modifications and `sync_from_physical_tree()` after physical-XML
 * modifications (e.g., BookmarkReplacer). This means:
 * - You can use DOM APIs **before** calling `apply()`.
 * - After `apply()`, the DOM is fully in sync with the physical tree.
 * - If you then use physical-XML APIs (e.g., BookmarkInserter), call
 *   `sync_from_physical_tree()` before further DOM operations or `save()`.
 *
 * @since 0.8.0
 */

#include <cdocx.h>
#include <cdocx/template_engine.h>

#include <filesystem>
#include <iostream>

int main() {
    // =====================================================================
    // Phase 1: Load the pre-built template document
    // =====================================================================
    cdocx::Document doc("data/template_engine.docx");
    doc.open();
    if (!doc.is_open()) {
        std::cerr << "Failed to open data/template_engine.docx\n";
        return 1;
    }

    std::cout << "Template loaded: template_engine.docx\n";

    // =====================================================================
    // Phase 2: Configure TemplateEngine and set replacement values
    // =====================================================================
    cdocx::TemplateEngine engine(&doc);

    // --- Plain text placeholders ({{key}}) ---
    engine["标题"] = cdocx::TemplateValue::Text("替换后的标题");
    engine["正文"] = cdocx::TemplateValue::Text("这是替换后的正文内容。");
    engine["带格式正文"] = cdocx::TemplateValue::Text("带格式的替换正文内容。");
    engine["自定义格式正文"] = cdocx::TemplateValue::Text("自定义格式的替换正文内容。");

    // --- Text bookmarks (auto-detected by TemplateEngine) ---
    engine["bookmark1"] = cdocx::TemplateValue::Text("替换后的书签标题");
    engine["bookmark2"] = cdocx::TemplateValue::Text("替换后的书签正文");
    engine["bookmark3"] = cdocx::TemplateValue::Text("替换后的带格式书签正文");

    // Bookmark with explicit custom formatting
    engine["bookmark4"] = cdocx::TemplateValue::Text("替换后的自定义格式书签正文")
        .with_format(cdocx::TemplateFormat()
                         .bold()
                         .italic()
                         .Size(28)
                         .color("0000FF")
                         .font("SimSun"));

    // --- Image placeholders ---
    if (std::filesystem::exists("data/image2.jpg")) {
        engine["图片2"] = cdocx::TemplateValue::Image("data/image2.jpg")
            .sized(200, 150)
            .centered();
    }

    // --- Image bookmarks (with caption) ---
    // Note: Captions are supported for bookmark-based image replacement.
    // The caption is inserted below the image as a standard figure caption.
    if (std::filesystem::exists("data/image1.jpg")) {
        engine["image1"] = cdocx::TemplateValue::Image("data/image1.jpg")
            .sized(300, 200)
            .centered()
            .with_caption("图1 示例图片");
    }

    // =====================================================================
    // Phase 3: Apply replacements
    // =====================================================================
    auto result = engine
        .with_scope(cdocx::TemplateScope::All)
        .with_target(cdocx::TemplateTarget::Auto)
        .with_format_policy(cdocx::FormatPolicy::Custom)
        .apply();

    std::cout << "\n=== Results ===\n";
    std::cout << "Success: " << result.success << "\n";
    std::cout << "Failed:  " << result.failed << "\n";
    std::cout << "Skipped: " << result.skipped << "\n";

    // =====================================================================
    // Phase 4: Post-process with DOM API (demonstrates interoperability)
    // =====================================================================
    // After apply(), the DOM is in sync with physical XML. We can safely
    // use DOM APIs to add content that is not part of the template.
    auto sections = doc.get_sections();
    if (!sections.is_empty()) {
        auto body = sections[0]->get_body();
        body->append_paragraph("--- 文档生成完毕 ---");
    }

    // =====================================================================
    // Phase 5: Save output
    // =====================================================================
    doc.save("template_engine_output_2.docx");
    std::cout << "\nOutput: template_engine_output_2.docx\n";

    return 0;
}
