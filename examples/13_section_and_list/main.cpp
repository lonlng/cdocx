/**
 * @file main.cpp
 * @brief Example demonstrating Section and List features (v0.5.0+)
 * @version 0.5.0
 */

#include <cdocx.h>
#include <iostream>

int main() {
    try {
        std::cout << "CDocx v" << CDOCX_VERSION << " - Section and List Demo" << std::endl;
        std::cout << "================================================" << std::endl;
        
        // ================================================================
        // Example 1: Basic Section Usage
        // ================================================================
        std::cout << "\n[Example 1] Creating document with sections..." << std::endl;
        
        cdocx::Document doc("section_example.docx");
        doc.create_empty();
        
        // Get the default section and set page properties
        auto sect1 = doc.get_first_section();
        if (sect1) {
            std::cout << "  - Found default section" << std::endl;
            
            // Set A4 portrait
            sect1->get_properties().page_size.width = 12240;
            sect1->get_properties().page_size.height = 15840;
            sect1->get_properties().orientation = cdocx::SectionProperties::Orientation::Portrait;
            
            // Set margins (1 inch)
            sect1->get_properties().page_margins.top = 1440;
            sect1->get_properties().page_margins.right = 1440;
            sect1->get_properties().page_margins.bottom = 1440;
            sect1->get_properties().page_margins.left = 1440;
            
            std::cout << "  - Section configured with A4 portrait" << std::endl;
            
            // Add content
            auto* para = sect1->add_paragraph("First Section Content", cdocx::kBold);
            if (para) {
                std::cout << "  - Added paragraph to section" << std::endl;
            }
        }
        
        // Add a new section
        auto sect2 = doc.add_section();
        if (sect2) {
            std::cout << "  - Added new section (total: " << doc.get_section_count() << ")" << std::endl;
            
            // Set landscape
            sect2->get_properties().orientation = cdocx::SectionProperties::Orientation::Landscape;
            sect2->get_properties().page_size.width = 15840;
            sect2->get_properties().page_size.height = 12240;
            
            sect2->add_paragraph("Second Section - Landscape");
            std::cout << "  - Second section set to landscape" << std::endl;
        }
        
        doc.save();
        std::cout << "  ✓ Document saved: section_example.docx" << std::endl;
        
        // ================================================================
        // Example 2: Bulleted List
        // ================================================================
        std::cout << "\n[Example 2] Creating bulleted list document..." << std::endl;
        
        cdocx::Document doc2("bullet_list_example.docx");
        doc2.create_empty();
        
        // Create a bulleted list
        auto bullet_list = doc2.add_bulleted_list_definition();
        std::cout << "  - Created bulleted list definition (ID: " << bullet_list << ")" << std::endl;
        
        // Add list items using paragraphs and apply numbering
        auto para = doc2.paragraphs();
        
        para.add_run("Project Goals:", cdocx::kBold);
        para.next();  // Move to next paragraph
        
        auto p1 = para.insert_paragraph_after("Define project scope");
        p1.set_numbering(bullet_list, cdocx::NumberingLevel::Level1);
        
        auto p2 = p1.insert_paragraph_after("Create timeline");
        p2.set_numbering(bullet_list, cdocx::NumberingLevel::Level1);
        
        auto p3 = p2.insert_paragraph_after("Assign team members");
        p3.set_numbering(bullet_list, cdocx::NumberingLevel::Level1);
        
        // Add nested item
        auto p4 = p3.insert_paragraph_after("Developers");
        p4.set_numbering(bullet_list, cdocx::NumberingLevel::Level2);
        
        std::cout << "  - Added 4 list items (3 level 1, 1 level 2)" << std::endl;
        
        doc2.save();
        std::cout << "  ✓ Document saved: bullet_list_example.docx" << std::endl;
        
        // ================================================================
        // Example 3: Numbered List
        // ================================================================
        std::cout << "\n[Example 3] Creating numbered list document..." << std::endl;
        
        cdocx::Document doc3("numbered_list_example.docx");
        doc3.create_empty();
        
        // Create different types of numbered lists
        auto decimal_list = doc3.add_numbered_list_definition(cdocx::NumberStyle::Decimal);
        auto roman_list = doc3.add_numbered_list_definition(cdocx::NumberStyle::UpperRoman);
        auto letter_list = doc3.add_numbered_list_definition(cdocx::NumberStyle::LowerLetter);
        
        std::cout << "  - Created decimal list (ID: " << decimal_list << ")" << std::endl;
        std::cout << "  - Created roman list (ID: " << roman_list << ")" << std::endl;
        std::cout << "  - Created letter list (ID: " << letter_list << ")" << std::endl;
        
        // Add decimal list items
        auto para3 = doc3.paragraphs();
        para3.add_run("Installation Steps:", cdocx::kBold);
        
        auto d1 = para3.insert_paragraph_after("Download the software");
        d1.set_numbering(decimal_list, cdocx::NumberingLevel::Level1);
        
        auto d2 = d1.insert_paragraph_after("Run the installer");
        d2.set_numbering(decimal_list, cdocx::NumberingLevel::Level1);
        
        auto d3 = d2.insert_paragraph_after("Configure settings");
        d3.set_numbering(decimal_list, cdocx::NumberingLevel::Level1);
        
        auto d4 = d3.insert_paragraph_after("Complete setup");
        d4.set_numbering(decimal_list, cdocx::NumberingLevel::Level1);
        
        std::cout << "  - Added 4 decimal numbered items" << std::endl;
        
        doc3.save();
        std::cout << "  ✓ Document saved: numbered_list_example.docx" << std::endl;
        
        // ================================================================
        // Example 4: Outline List
        // ================================================================
        std::cout << "\n[Example 4] Creating outline list document..." << std::endl;
        
        cdocx::Document doc4("outline_list_example.docx");
        doc4.create_empty();
        
        auto outline_list = doc4.add_outline_list_definition();
        std::cout << "  - Created outline list (ID: " << outline_list << ")" << std::endl;
        
        // Get the definition to show structure
        auto* def = doc4.get_numbering_definition(outline_list);
        if (def) {
            std::cout << "  - Abstract definition ID: " << def->abstract_id << std::endl;
        }
        
        // Create outline structure
        auto para4 = doc4.paragraphs();
        para4.add_run("Document Outline:", cdocx::kBold);
        
        auto o1 = para4.insert_paragraph_after("Introduction");
        o1.set_numbering(outline_list, cdocx::NumberingLevel::Level1);
        
        auto o2 = o1.insert_paragraph_after("Background");
        o2.set_numbering(outline_list, cdocx::NumberingLevel::Level2);
        
        auto o3 = o2.insert_paragraph_after("Objectives");
        o3.set_numbering(outline_list, cdocx::NumberingLevel::Level2);
        
        auto o4 = o3.insert_paragraph_after("Methodology");
        o4.set_numbering(outline_list, cdocx::NumberingLevel::Level1);
        
        auto o5 = o4.insert_paragraph_after("Data Collection");
        o5.set_numbering(outline_list, cdocx::NumberingLevel::Level2);
        
        auto o6 = o5.insert_paragraph_after("Analysis");
        o6.set_numbering(outline_list, cdocx::NumberingLevel::Level3);
        
        auto o7 = o6.insert_paragraph_after("Results");
        o7.set_numbering(outline_list, cdocx::NumberingLevel::Level1);
        
        std::cout << "  - Created 3-level outline structure" << std::endl;
        
        doc4.save();
        std::cout << "  ✓ Document saved: outline_list_example.docx" << std::endl;
        
        // ================================================================
        // Example 5: Chinese Numbered List
        // ================================================================
        std::cout << "\n[Example 5] Creating Chinese numbered list..." << std::endl;
        
        cdocx::Document doc5("chinese_list_example.docx");
        doc5.create_empty();
        
        auto chinese_list = doc5.add_chinese_numbered_list_definition();
        std::cout << "  - Created Chinese numbered list (ID: " << chinese_list << ")" << std::endl;
        
        auto para5 = doc5.paragraphs();
        para5.add_run("工作计划:", cdocx::kBold);
        
        auto c1 = para5.insert_paragraph_after("需求分析");
        c1.set_numbering(chinese_list, cdocx::NumberingLevel::Level1);
        
        auto c2 = c1.insert_paragraph_after("系统设计");
        c2.set_numbering(chinese_list, cdocx::NumberingLevel::Level1);
        
        auto c3 = c2.insert_paragraph_after("开发实现");
        c3.set_numbering(chinese_list, cdocx::NumberingLevel::Level1);
        
        auto c4 = c3.insert_paragraph_after("测试验收");
        c4.set_numbering(chinese_list, cdocx::NumberingLevel::Level1);
        
        std::cout << "  - Added 4 Chinese numbered items" << std::endl;
        
        doc5.save();
        std::cout << "  ✓ Document saved: chinese_list_example.docx" << std::endl;
        
        // ================================================================
        // Example 6: List Level Manipulation
        // ================================================================
        std::cout << "\n[Example 6] Creating multi-level list with level changes..." << std::endl;
        
        cdocx::Document doc6("level_change_example.docx");
        doc6.create_empty();
        
        auto multi_list = doc6.add_numbered_list_definition();
        
        auto para6 = doc6.paragraphs();
        para6.add_run("Multi-level List Demo:", cdocx::kBold);
        
        // Create list and manipulate levels
        auto l1 = para6.insert_paragraph_after("Main Topic 1");
        l1.set_numbering(multi_list, cdocx::NumberingLevel::Level1);
        
        auto l2 = l1.insert_paragraph_after("Sub Topic 1.1");
        l2.set_numbering(multi_list, cdocx::NumberingLevel::Level2);
        
        auto l3 = l2.insert_paragraph_after("Sub Topic 1.2");
        l3.set_numbering(multi_list, cdocx::NumberingLevel::Level2);
        
        auto l4 = l3.insert_paragraph_after("Back to Main Topic 2");
        l4.set_numbering(multi_list, cdocx::NumberingLevel::Level1);
        
        auto l5 = l4.insert_paragraph_after("Sub Topic 2.1");
        l5.set_numbering(multi_list, cdocx::NumberingLevel::Level2);
        
        auto l6 = l5.insert_paragraph_after("Detail 2.1.1");
        l6.set_numbering(multi_list, cdocx::NumberingLevel::Level3);
        
        std::cout << "  - Created list with level manipulation" << std::endl;
        
        doc6.save();
        std::cout << "  ✓ Document saved: level_change_example.docx" << std::endl;
        
        // ================================================================
        // Summary
        // ================================================================
        std::cout << "\n================================================" << std::endl;
        std::cout << "All examples completed successfully!" << std::endl;
        std::cout << "\nFeatures demonstrated:" << std::endl;
        std::cout << "  ✓ Section management (add, get, count)" << std::endl;
        std::cout << "  ✓ Section properties (orientation, size, margins)" << std::endl;
        std::cout << "  ✓ List definition creation (bullet, numbered)" << std::endl;
        std::cout << "  ✓ Multiple numbering styles (decimal, roman, letter)" << std::endl;
        std::cout << "  ✓ Outline lists with multi-level structure" << std::endl;
        std::cout << "  ✓ Chinese numbered lists" << std::endl;
        std::cout << "  ✓ Paragraph numbering application" << std::endl;
        std::cout << "  ✓ List level manipulation" << std::endl;
        std::cout << "\nGenerated documents:" << std::endl;
        std::cout << "  1. section_example.docx" << std::endl;
        std::cout << "  2. bullet_list_example.docx" << std::endl;
        std::cout << "  3. numbered_list_example.docx" << std::endl;
        std::cout << "  4. outline_list_example.docx" << std::endl;
        std::cout << "  5. chinese_list_example.docx" << std::endl;
        std::cout << "  6. level_change_example.docx" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
