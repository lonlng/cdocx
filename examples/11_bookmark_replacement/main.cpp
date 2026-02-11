/**
 * Example 11: Bookmark Replacement
 * 
 * This example demonstrates how to:
 * 1. Open a document with bookmarks
 * 2. Use BookmarkReplacer for text and image replacement
 * 3. Preserve formatting during text replacement
 * 4. Insert images with captions at bookmark locations
 * 5. Use batch replacement for multiple bookmarks
 * 
 * @since 0.3.0
 */

#include <cdocx.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/caption_generator.h>
#include <iostream>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

// Forward declaration
bool create_template_with_bookmarks(const std::string& doc_path);
bool create_sample_image(const std::string& image_path);

int main() {
    std::string doc_path = "data/11_bookmark_template.docx";
    std::string output_path = "data/11_bookmark_output.docx";
    std::string image_path = "data/sample_image.png";
    
    // Create data directory if needed
    fs::create_directories("data");
    
    std::cout << "=== CDocx Bookmark Replacement Example ===" << std::endl;
    std::cout << std::endl;
    
    // Create template document if it doesn't exist
    if (!fs::exists(doc_path)) {
        std::cout << "Creating template document with bookmarks..." << std::endl;
        if (!create_template_with_bookmarks(doc_path)) {
            std::cerr << "Failed to create template document" << std::endl;
            return 1;
        }
    }
    
    // Create sample image if it doesn't exist
    if (!fs::exists(image_path)) {
        std::cout << "Note: Sample image not found at " << image_path << std::endl;
        std::cout << "      Image replacement will be skipped." << std::endl;
        image_path.clear();
    }
    
    // Open the template document
    std::cout << std::endl << "Opening template: " << doc_path << std::endl;
    cdocx::Document doc(doc_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document: " << doc_path << std::endl;
        return 1;
    }
    
    // Create BookmarkReplacer
    cdocx::BookmarkReplacer replacer(&doc);
    
    // Display existing bookmarks
    std::cout << std::endl << "--- Existing Bookmarks ---" << std::endl;
    auto bookmarks = replacer.list_bookmarks();
    if (bookmarks.empty()) {
        std::cout << "  (none found)" << std::endl;
    } else {
        for (const auto& name : bookmarks) {
            std::cout << "  - " << name << std::endl;
        }
    }
    std::cout << "Total: " << bookmarks.size() << " bookmarks" << std::endl;
    
    // Example 1: Simple text replacement (preserves original format)
    std::cout << std::endl << "--- Example 1: Simple Text Replacement ---" << std::endl;
    if (replacer.has_bookmark("REPORT_NO")) {
        std::cout << "Replacing REPORT_NO with 'BGP-2024-BJ-001'..." << std::endl;
        if (replacer.replace_text("REPORT_NO", "BGP-2024-BJ-001")) {
            std::cout << "  Success!" << std::endl;
        } else {
            std::cout << "  Failed!" << std::endl;
        }
    }
    
    // Example 2: Batch text replacement
    std::cout << std::endl << "--- Example 2: Batch Text Replacement ---" << std::endl;
    std::map<std::string, std::string> replacements = {
        {"DATE", "2024-06-15"},
        {"COMPANY", "Beijing Geological Research Institute"},
        {"ADDRESS", "123 Main Street, Beijing"}
    };
    
    std::cout << "Replacing multiple bookmarks:" << std::endl;
    for (const auto& pair : replacements) {
        std::cout << "  " << pair.first << " -> '" << pair.second << "'" << std::endl;
    }
    
    int replaced_count = replacer.replace_text_batch(replacements);
    std::cout << "Successfully replaced " << replaced_count << " bookmarks" << std::endl;
    
    // Example 3: Replacement with custom format
    std::cout << std::endl << "--- Example 3: Replacement with Custom Format ---" << std::endl;
    if (replacer.has_bookmark("TITLE")) {
        std::cout << "Replacing TITLE with custom formatting..." << std::endl;
        
        cdocx::BookmarkFormat format;
        format.font_ascii = "Arial";
        format.font_far_east = "SimHei";
        format.font_size = 36;  // 18pt
        format.bold = true;
        format.color = "0066CC";  // Blue
        
        if (replacer.replace_text_with_format("TITLE", "Geological Survey Report", format)) {
            std::cout << "  Success!" << std::endl;
        } else {
            std::cout << "  Failed!" << std::endl;
        }
    }
    
    // Example 4: Image replacement (if image exists)
    std::cout << std::endl << "--- Example 4: Image Replacement ---" << std::endl;
    if (!image_path.empty() && replacer.has_bookmark("RESULT_IMAGE")) {
        std::cout << "Replacing RESULT_IMAGE with '" << image_path << "'..." << std::endl;
        
        // Simple replacement with caption
        if (replacer.replace_with_image("RESULT_IMAGE", image_path, "GPR Detection Result")) {
            std::cout << "  Success! Image inserted with caption." << std::endl;
        } else {
            std::cout << "  Failed!" << std::endl;
        }
    } else {
        std::cout << "  Skipped (no image file or bookmark not found)" << std::endl;
    }
    
    // Example 5: Advanced image replacement with alignment
    std::cout << std::endl << "--- Example 5: Advanced Image Replacement ---" << std::endl;
    if (!image_path.empty() && replacer.has_bookmark("CHART_IMAGE")) {
        std::cout << "Replacing CHART_IMAGE with custom size and alignment..." << std::endl;
        
        cdocx::ImageSize size(400, 300);  // 400x300 points
        
        if (replacer.replace_with_image_advanced("CHART_IMAGE", image_path, size,
                                                  "Analysis Chart",
                                                  cdocx::ImageAlignment::Center)) {
            std::cout << "  Success! Image inserted with center alignment." << std::endl;
        } else {
            std::cout << "  Failed!" << std::endl;
        }
    } else {
        std::cout << "  Skipped (no image file or bookmark not found)" << std::endl;
    }
    
    // Example 6: Caption generation
    std::cout << std::endl << "--- Example 6: Figure Caption Generation ---" << std::endl;
    int next_fig = cdocx::CaptionGenerator::get_next_figure_number(&doc);
    std::cout << "Next figure number would be: " << next_fig << std::endl;
    
    // Example 7: Conditional replacement
    std::cout << std::endl << "--- Example 7: Conditional Replacement ---" << std::endl;
    if (replacer.has_bookmark("STATUS")) {
        std::cout << "Performing conditional replacement on STATUS..." << std::endl;
        
        bool replaced = replacer.replace_if("STATUS", 
            [](const std::string& name, const std::string& old_text, std::string& new_text) {
                // Only replace if old text contains "[PLACEHOLDER]"
                if (old_text.find("[PLACEHOLDER]") != std::string::npos) {
                    new_text = "Completed";
                    return true;  // Proceed with replacement
                }
                std::cout << "  Condition not met (no placeholder found)" << std::endl;
                return false;  // Skip replacement
            });
        
        if (replaced) {
            std::cout << "  Success! Conditional replacement performed." << std::endl;
        } else {
            std::cout << "  Skipped (condition not met)" << std::endl;
        }
    }
    
    // Display statistics
    std::cout << std::endl << "--- Replacement Statistics ---" << std::endl;
    auto stats = replacer.get_stats();
    std::cout << "  Success: " << stats.success_count << std::endl;
    std::cout << "  Failed:  " << stats.fail_count << std::endl;
    std::cout << "  Skipped: " << stats.skip_count << std::endl;
    std::cout << "  Total:   " << stats.total() << std::endl;
    
    // Save document
    std::cout << std::endl << "Saving to: " << output_path << std::endl;
    doc.save(output_path);
    
    if (fs::exists(output_path)) {
        std::cout << "Document saved successfully!" << std::endl;
    } else {
        std::cerr << "Failed to save document!" << std::endl;
        return 1;
    }
    
    std::cout << std::endl << "=== Example Complete ===" << std::endl;
    return 0;
}

/**
 * Create a template document with sample bookmarks
 */
bool create_template_with_bookmarks(const std::string& doc_path) {
    cdocx::Document doc;
    if (!doc.create_empty(doc_path)) {
        std::cerr << "Failed to create empty document" << std::endl;
        return false;
    }
    
    // Create a document with various bookmarks
    
    // Title bookmark
    auto p1 = doc.paragraphs().insert_paragraph_after("");
    auto r1 = p1.add_run("[TITLE]", cdocx::bold);
    r1.set_font_size(36);  // 18pt
    
    // Empty paragraph
    doc.paragraphs().insert_paragraph_after("");
    
    // Report info section
    auto p2 = doc.paragraphs().insert_paragraph_after("Report Number: ");
    auto r2 = p2.add_run("[REPORT_NO]");
    
    auto p3 = doc.paragraphs().insert_paragraph_after("Date: ");
    auto r3 = p3.add_run("[DATE]");
    
    // Empty paragraph
    doc.paragraphs().insert_paragraph_after("");
    
    // Company info section
    auto p4 = doc.paragraphs().insert_paragraph_after("Company: ");
    auto r4 = p4.add_run("[COMPANY]");
    
    auto p5 = doc.paragraphs().insert_paragraph_after("Address: ");
    auto r5 = p5.add_run("[ADDRESS]");
    
    // Empty paragraph
    doc.paragraphs().insert_paragraph_after("");
    
    // Status section
    auto p6 = doc.paragraphs().insert_paragraph_after("Status: ");
    auto r6 = p6.add_run("[STATUS_PLACEHOLDER]");
    
    // Empty paragraph
    doc.paragraphs().insert_paragraph_after("");
    
    // Image placeholders
    auto p7 = doc.paragraphs().insert_paragraph_after("Result Image:");
    p7.set_bold(true);
    
    auto p8 = doc.paragraphs().insert_paragraph_after("");
    auto r8 = p8.add_run("[RESULT_IMAGE]");
    r8.set_color("FF0000");  // Red color to indicate placeholder
    
    // Empty paragraph
    doc.paragraphs().insert_paragraph_after("");
    
    auto p9 = doc.paragraphs().insert_paragraph_after("Chart Image:");
    p9.set_bold(true);
    
    auto p10 = doc.paragraphs().insert_paragraph_after("");
    auto r10 = p10.add_run("[CHART_IMAGE]");
    r10.set_color("FF0000");  // Red color to indicate placeholder
    
    // Note: In a real template, you would use DocumentBuilder::start_bookmark() 
    // and end_bookmark() to create actual bookmarks. For this example, we create
    // a document with placeholder text that simulates bookmarks.
    
    doc.save(doc_path);
    std::cout << "  Created: " << doc_path << std::endl;
    return true;
}

/**
 * Create a sample PNG image (placeholder implementation)
 * In a real scenario, this would create an actual image file.
 * For this example, we just note that an external image should be provided.
 */
bool create_sample_image(const std::string& image_path) {
    // Note: Creating actual image files requires external libraries
    // For this example, users should provide their own sample images
    (void)image_path;
    return false;  // Indicate that no image was created
}
