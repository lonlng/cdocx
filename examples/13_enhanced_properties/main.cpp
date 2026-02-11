/**
 * Example 13: Enhanced Properties (v0.4.0)
 * 
 * This example demonstrates the enhanced property system inspired by minidocx:
 * 1. TextProperties - comprehensive text formatting
 * 2. ParagraphProperties - advanced paragraph formatting
 * 3. New formatting options: highlight, underline styles, character spacing, etc.
 * 
 * @since 0.4.0
 */

#include <cdocx.h>
#include <iostream>

int main() {
    std::cout << "=== CDocx Enhanced Properties Example (v0.4.0) ===" << std::endl;
    
    cdocx::Document doc;
    if (!doc.create_empty("output_enhanced.docx")) {
        std::cerr << "Failed to create document" << std::endl;
        return 1;
    }
    
    // ===================================================================
    // Example 1: TextProperties - Comprehensive Text Formatting
    // ===================================================================
    std::cout << "\n1. Creating text with TextProperties..." << std::endl;
    
    auto para1 = doc.paragraphs().insert_paragraph_after("");
    
    // Create rich text with TextProperties
    cdocx::TextProperties rich_props;
    rich_props.font = cdocx::TextProperties::Font{"Arial", "SimHei"};
    rich_props.fontSize = 36;  // 18pt
    rich_props.color = "FF0000";  // Red
    rich_props.fontStyle.bold = true;
    rich_props.highlight = cdocx::TextProperties::Highlight::Yellow;
    
    auto run1 = para1.add_run("Bold Red Text with Yellow Highlight");
    run1.set_properties(rich_props);
    
    // ===================================================================
    // Example 2: Advanced Underline Styles
    // ===================================================================
    std::cout << "2. Demonstrating underline styles..." << std::endl;
    
    auto para2 = doc.paragraphs().insert_paragraph_after("");
    
    // Single underline
    auto run2a = para2.add_run("Single Underline ");
    run2a.set_underline_style(cdocx::TextProperties::UnderlineStyle::Single);
    
    // Double underline
    auto run2b = para2.add_run("Double Underline ");
    run2b.set_underline_style(cdocx::TextProperties::UnderlineStyle::Double);
    
    // Wave underline with color
    auto run2c = para2.add_run("Wave Underline");
    run2c.set_underline_style(cdocx::TextProperties::UnderlineStyle::Wave, "0000FF");
    
    // ===================================================================
    // Example 3: Character Spacing and Position
    // ===================================================================
    std::cout << "3. Character spacing and position..." << std::endl;
    
    auto para3 = doc.paragraphs().insert_paragraph_after("");
    
    // Expanded spacing
    auto run3a = para3.add_run("Expanded Spacing ");
    run3a.set_spacing(cdocx::TextProperties::SpacingType::Expanded, 40);  // 2pt
    
    // Condensed spacing
    auto run3b = para3.add_run("Condensed Spacing ");
    run3b.set_spacing(cdocx::TextProperties::SpacingType::Condensed, 10);  // 0.5pt
    
    // Raised text
    auto run3c = para3.add_run("Raised Text");
    run3c.set_position(cdocx::TextProperties::PositionType::Raised, 6);  // 3pt
    
    // ===================================================================
    // Example 4: Character Scale
    // ===================================================================
    std::cout << "4. Character scaling..." << std::endl;
    
    auto para4 = doc.paragraphs().insert_paragraph_after("");
    
    auto run4a = para4.add_run("Normal ");
    run4a.set_scale(100);
    
    auto run4b = para4.add_run("Expanded 150% ");
    run4b.set_scale(150);
    
    auto run4c = para4.add_run("Compressed 80%");
    run4c.set_scale(80);
    
    // ===================================================================
    // Example 5: Strikethrough Styles
    // ===================================================================
    std::cout << "5. Strikethrough styles..." << std::endl;
    
    auto para5 = doc.paragraphs().insert_paragraph_after("");
    
    auto run5a = para5.add_run("Single Strikethrough ");
    run5a.set_strike(cdocx::TextProperties::StrikeStyle::Single);
    
    auto run5b = para5.add_run("Double Strikethrough");
    run5b.set_strike(cdocx::TextProperties::StrikeStyle::Double);
    
    // ===================================================================
    // Example 6: ParagraphProperties - Outline Level
    // ===================================================================
    std::cout << "6. Paragraph outline levels..." << std::endl;
    
    // Heading 1
    auto para6a = doc.paragraphs().insert_paragraph_after("Heading 1 (Level 1)");
    para6a.set_outline_level(cdocx::ParagraphProperties::OutlineLevel::Level1);
    
    // Heading 2
    auto para6b = doc.paragraphs().insert_paragraph_after("Heading 2 (Level 2)");
    para6b.set_outline_level(cdocx::ParagraphProperties::OutlineLevel::Level2);
    
    // Heading 3
    auto para6c = doc.paragraphs().insert_paragraph_after("Heading 3 (Level 3)");
    para6c.set_outline_level(cdocx::ParagraphProperties::OutlineLevel::Level3);
    
    // ===================================================================
    // Example 7: ParagraphProperties - Page Break Control
    // ===================================================================
    std::cout << "7. Page break control..." << std::endl;
    
    auto para7a = doc.paragraphs().insert_paragraph_after("This paragraph has keepNext enabled");
    para7a.set_keep_next(true);
    
    auto para7b = doc.paragraphs().insert_paragraph_after("This paragraph has keepLines enabled");
    para7b.set_keep_lines(true);
    
    auto para7c = doc.paragraphs().insert_paragraph_after("This paragraph has pageBreakBefore");
    para7c.set_page_break_before(true);
    
    // ===================================================================
    // Example 8: ParagraphProperties - Comprehensive Properties
    // ===================================================================
    std::cout << "8. Comprehensive paragraph properties..." << std::endl;
    
    cdocx::ParagraphProperties para_props;
    para_props.align = cdocx::ParagraphProperties::Alignment::Centered;
    para_props.outlineLevel = cdocx::ParagraphProperties::OutlineLevel::Level1;
    
    // Indentation
    cdocx::ParagraphProperties::Indentation indent;
    indent.left.value = 720;  // 0.5 inch
    indent.special.kind = cdocx::ParagraphProperties::Indentation::Special::Kind::FirstLine;
    indent.special.value = 200;  // 2 characters
    para_props.indent = indent;
    
    // Spacing
    cdocx::ParagraphProperties::Spacing spacing;
    spacing.before.value = 240;  // 0.5 inch
    spacing.after.value = 120;   // 0.25 inch
    spacing.lineSpacing.type = cdocx::ParagraphProperties::Spacing::LineSpacingType::Lines;
    spacing.lineSpacing.value = 360;  // 1.5 lines
    para_props.spacing = spacing;
    
    auto para8 = doc.paragraphs().insert_paragraph_after("Paragraph with comprehensive properties");
    para8.set_properties(para_props);
    
    // ===================================================================
    // Example 9: Highlight Colors
    // ===================================================================
    std::cout << "9. Various highlight colors..." << std::endl;
    
    auto para9 = doc.paragraphs().insert_paragraph_after("");
    
    auto run9a = para9.add_run("Yellow ");
    run9a.set_highlight(cdocx::TextProperties::Highlight::Yellow);
    
    auto run9b = para9.add_run("Green ");
    run9b.set_highlight(cdocx::TextProperties::Highlight::Green);
    
    auto run9c = para9.add_run("Cyan ");
    run9c.set_highlight(cdocx::TextProperties::Highlight::Cyan);
    
    auto run9d = para9.add_run("Magenta");
    run9d.set_highlight(cdocx::TextProperties::Highlight::Magenta);
    
    // ===================================================================
    // Example 10: Using set_properties with existing formatting
    // ===================================================================
    std::cout << "10. Combining properties with existing formatting..." << std::endl;
    
    auto para10 = doc.paragraphs().insert_paragraph_after("");
    
    // First apply some basic formatting
    auto run10 = para10.add_run("Combined Formatting", cdocx::bold | cdocx::italic);
    
    // Then apply TextProperties for advanced features
    cdocx::TextProperties combined_props;
    combined_props.highlight = cdocx::TextProperties::Highlight::LightGray;
    combined_props.underline.style = cdocx::TextProperties::UnderlineStyle::Wave;
    combined_props.scale = 110;
    run10.set_properties(combined_props);
    
    // ===================================================================
    // Save document
    // ===================================================================
    doc.save();
    std::cout << "\nDocument saved to: output_enhanced.docx" << std::endl;
    std::cout << "=== Example Complete ===" << std::endl;
    
    return 0;
}
