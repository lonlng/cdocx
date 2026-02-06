/**
 * @file main.cpp
 * @brief Example 09: Text Formatting Features
 * @version 0.2.0
 * 
 * @defgroup example_09_text_formatting Example 09: Text Formatting
 * @brief Demonstrates font color, size, font name, and paragraph formatting
 * @{
 */

/**
 * Example 09: Text Formatting Features
 * 
 * This example demonstrates the new text and paragraph formatting features:
 * 1. Font color (red, blue, green, custom hex colors)
 * 2. Font size (various sizes from small to large)
 * 3. Font name (Times New Roman, Arial, Verdana, etc.)
 * 4. Paragraph alignment (left, center, right, justified)
 * 5. Paragraph styles (Heading 1-3, Normal)
 * 6. Paragraph spacing (before/after)
 * 7. Line spacing (single, 1.5, double)
 * 8. Indentation (left, right, first line, hanging)
 * 
 * Output: 09_text_formatting_output.docx
 */

#include <cdocx.h>
#include <iostream>

int main() {
    std::cout << "Example 09: Text Formatting Features" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // Create a new empty document
    cdocx::Document doc("09_text_formatting_output.docx");
    
    if (!doc.create_empty("09_text_formatting_output.docx")) {
        std::cerr << "Failed to create document!" << std::endl;
        return 1;
    }
    
    // =========================================================================
    // 1. Font Color Demo
    // =========================================================================
    std::cout << "Adding font color examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("1. Font Colors");
        title.set_style("1");
        
        auto p = doc.paragraphs().insert_paragraph_after(
            "Text can be displayed in various colors: "
        );
        
        auto r1 = p.add_run("Red ", cdocx::bold);
        r1.set_color("FF0000");
        
        auto r2 = p.add_run("Blue ", cdocx::bold);
        r2.set_color("0070C0");
        
        auto r3 = p.add_run("Green ", cdocx::bold);
        r3.set_color("00B050");
        
        auto r4 = p.add_run("Orange ");
        r4.set_color("FFA500");
        
        auto r5 = p.add_run("Purple");
        r5.set_color("800080");
    }
    
    // =========================================================================
    // 2. Font Size Demo
    // =========================================================================
    std::cout << "Adding font size examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n2. Font Sizes");
        title.set_style("1");
        
        auto p1 = doc.paragraphs().insert_paragraph_after("");
        auto r1 = p1.add_run("Small text (10pt)");
        r1.set_font_size(20);
        
        auto p2 = doc.paragraphs().insert_paragraph_after("");
        auto r2 = p2.add_run("Normal text (12pt)");
        r2.set_font_size(24);
        
        auto p3 = doc.paragraphs().insert_paragraph_after("");
        auto r3 = p3.add_run("Large text (18pt)");
        r3.set_font_size(36);
        
        auto p4 = doc.paragraphs().insert_paragraph_after("");
        auto r4 = p4.add_run("Very Large text (24pt)");
        r4.set_font_size(48);
        
        auto p5 = doc.paragraphs().insert_paragraph_after("");
        auto r5 = p5.add_run("Huge text (36pt)");
        r5.set_font_size(72);
    }
    
    // =========================================================================
    // 3. Font Name Demo
    // =========================================================================
    std::cout << "Adding font name examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n3. Font Names");
        title.set_style("1");
        
        auto p = doc.paragraphs().insert_paragraph_after("Different fonts: ");
        
        auto r1 = p.add_run("Times New Roman ");
        r1.set_font_name("Times New Roman");
        
        auto r2 = p.add_run("Arial ");
        r2.set_font_name("Arial");
        
        auto r3 = p.add_run("Verdana ");
        r3.set_font_name("Verdana");
        
        auto r4 = p.add_run("Courier New");
        r4.set_font_name("Courier New");
    }
    
    // =========================================================================
    // 4. Paragraph Alignment Demo
    // =========================================================================
    std::cout << "Adding paragraph alignment examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n4. Paragraph Alignment");
        title.set_style("1");
        
        auto p1 = doc.paragraphs().insert_paragraph_after(
            "This paragraph is left-aligned (default)."
        );
        p1.set_alignment("left");
        
        auto p2 = doc.paragraphs().insert_paragraph_after(
            "This paragraph is center-aligned."
        );
        p2.set_alignment("center");
        
        auto p3 = doc.paragraphs().insert_paragraph_after(
            "This paragraph is right-aligned."
        );
        p3.set_alignment("right");
        
        auto p4 = doc.paragraphs().insert_paragraph_after(
            "This paragraph is justified. When you have a longer text, "
            "it will be aligned to both left and right margins, creating "
            "a clean, even appearance on both sides of the paragraph."
        );
        p4.set_alignment("both");
    }
    
    // =========================================================================
    // 5. Paragraph Styles Demo
    // =========================================================================
    std::cout << "Adding paragraph style examples..." << std::endl;
    
    {
        auto p0 = doc.paragraphs().insert_paragraph_after("\n5. Paragraph Styles");
        p0.set_style("1");
        
        auto p1 = doc.paragraphs().insert_paragraph_after("Heading 2 Style");
        p1.set_style("2");
        
        auto p2 = doc.paragraphs().insert_paragraph_after("Heading 3 Style");
        p2.set_style("3");
        
        auto p3 = doc.paragraphs().insert_paragraph_after(
            "This is a normal paragraph with the default 'Normal' style."
        );
        p3.set_style("Normal");
    }
    
    // =========================================================================
    // 6. Paragraph Spacing Demo
    // =========================================================================
    std::cout << "Adding paragraph spacing examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n6. Paragraph Spacing");
        title.set_style("1");
        
        auto p1 = doc.paragraphs().insert_paragraph_after(
            "This paragraph has spacing BEFORE it (200 twips)."
        );
        p1.set_spacing_before(200);
        
        auto p2 = doc.paragraphs().insert_paragraph_after(
            "This paragraph has spacing AFTER it (200 twips)."
        );
        p2.set_spacing_after(200);
        
        auto p3 = doc.paragraphs().insert_paragraph_after(
            "This paragraph has spacing both BEFORE and AFTER (100 twips each)."
        );
        p3.set_spacing_before(100);
        p3.set_spacing_after(100);
    }
    
    // =========================================================================
    // 7. Line Spacing Demo
    // =========================================================================
    std::cout << "Adding line spacing examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n7. Line Spacing");
        title.set_style("1");
        
        auto p1 = doc.paragraphs().insert_paragraph_after(
            "Single line spacing. "
            "This is a longer paragraph to demonstrate the line spacing effect. "
            "The text continues on multiple lines with the specified spacing."
        );
        p1.set_line_spacing(240);
        
        auto p2 = doc.paragraphs().insert_paragraph_after(
            "1.5 line spacing. "
            "This is a longer paragraph to demonstrate the line spacing effect. "
            "The text continues on multiple lines with the specified spacing."
        );
        p2.set_line_spacing(360);
        
        auto p3 = doc.paragraphs().insert_paragraph_after(
            "Double line spacing. "
            "This is a longer paragraph to demonstrate the line spacing effect. "
            "The text continues on multiple lines with the specified spacing."
        );
        p3.set_line_spacing(480);
    }
    
    // =========================================================================
    // 8. Indentation Demo
    // =========================================================================
    std::cout << "Adding indentation examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n8. Indentation");
        title.set_style("1");
        
        auto p1 = doc.paragraphs().insert_paragraph_after(
            "This paragraph has a LEFT indent of 720 twips (0.5 inch)."
        );
        p1.set_indent(720, -1, -1);
        
        auto p2 = doc.paragraphs().insert_paragraph_after(
            "This paragraph has a FIRST LINE indent of 720 twips. "
            "The first line is indented while subsequent lines start at the left margin."
        );
        p2.set_indent(-1, -1, 720);
        
        auto p3 = doc.paragraphs().insert_paragraph_after(
            "This paragraph has a HANGING indent (-720 twips). "
            "The first line starts at the margin while subsequent lines are indented."
        );
        p3.set_indent(-1, -1, -720);
    }
    
    // =========================================================================
    // 9. Combined Formatting Demo
    // =========================================================================
    std::cout << "Adding combined formatting examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n9. Combined Formatting");
        title.set_style("1");
        
        auto p = doc.paragraphs().insert_paragraph_after("");
        p.set_alignment("center");
        p.set_spacing_before(200);
        p.set_spacing_after(200);
        
        auto r = p.add_run("Bold, Red, Large, Arial, Centered");
        r.set_bold(true);
        r.set_color("FF0000");
        r.set_font_size(48);
        r.set_font_name("Arial");
    }
    
    // =========================================================================
    // 10. Dynamic Formatting Demo
    // =========================================================================
    std::cout << "Adding dynamic formatting examples..." << std::endl;
    
    {
        auto title = doc.paragraphs().insert_paragraph_after("\n10. Dynamic Formatting");
        title.set_style("1");
        
        auto p = doc.paragraphs().insert_paragraph_after(
            "You can modify existing runs: "
        );
        
        // Add a normal run
        auto r1 = p.add_run("Normal ");
        
        // Now make it bold and red
        r1.set_bold(true);
        r1.set_color("CC0000");
        
        // Add another run and modify it
        auto r2 = p.add_run("Big Blue ");
        r2.set_font_size(36);
        r2.set_color("0066CC");
    }
    
    // Save the document
    doc.save();
    
    std::cout << std::endl;
    std::cout << "Document saved: 09_text_formatting_output.docx" << std::endl;
    std::cout << "All formatting examples completed!" << std::endl;
    
    return 0;
}

/** @} */
