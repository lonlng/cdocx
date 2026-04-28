/**
 * Example 12: Figure Caption Generation
 * 
 * This example demonstrates how to:
 * 1. Create figure captions in Chinese format "图 X [description]"
 * 2. Count existing figures in a document
 * 3. Generate auto-numbered captions
 * 4. Use proper Chinese formatting (SimSun font, 10.5pt)
 * 
 * @since 0.3.0
 */

#include <cdocx.h>
#include <cdocx/caption_generator.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Forward declaration
bool create_document_with_images(const std::string& doc_path);

int main() {
    std::string doc_path = "data/12_caption_template.docx";
    std::string output_path = "data/12_caption_output.docx";
    
    // Create data directory if needed
    fs::create_directories("data");
    
    std::cout << "=== CDocx Caption Generation Example ===" << std::endl;
    std::cout << std::endl;
    
    // Create template document if it doesn't exist
    if (!fs::exists(doc_path)) {
        std::cout << "Creating template document with images..." << std::endl;
        if (!create_document_with_images(doc_path)) {
            std::cerr << "Failed to create template document" << std::endl;
            return 1;
        }
    }
    
    // Open the document
    std::cout << std::endl << "Opening document: " << doc_path << std::endl;
    cdocx::Document doc(doc_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document: " << doc_path << std::endl;
        return 1;
    }
    
    // Example 1: Count existing figures
    std::cout << std::endl << "--- Example 1: Count Existing Figures ---" << std::endl;
    int existing_count = cdocx::CaptionGenerator::count_existing_figures(&doc);
    std::cout << "Existing figures in document: " << existing_count << std::endl;
    
    // Example 2: Get next figure number
    std::cout << std::endl << "--- Example 2: Get Next Figure Number ---" << std::endl;
    int next_number = cdocx::CaptionGenerator::get_next_figure_number(&doc);
    std::cout << "Next figure number would be: " << next_number << std::endl;
    
    // Example 3: Add captions after image paragraphs
    std::cout << std::endl << "--- Example 3: Add Figure Captions ---" << std::endl;
    
    // Get document body
    pugi::xml_document* doc_xml = doc.get_document_xml();
    if (!doc_xml) {
        std::cerr << "Failed to get document XML" << std::endl;
        return 1;
    }
    
    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    if (!body) {
        std::cerr << "Failed to get document body" << std::endl;
        return 1;
    }
    
    // Find paragraphs that contain images and add captions
    int caption_count = 0;
    std::vector<std::string> captions_to_add = {
        "GPR Detection Result",
        "TEM Data Analysis",
        "Comprehensive Geological Survey",
        "Final Recommendation"
    };
    
    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        // Check if paragraph contains an image placeholder
        std::string para_text;
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            pugi::xml_node t = run.child("w:t");
            if (t && t.text()) {
                para_text += t.text().get();
            }
        }
        
        // If this is an image placeholder paragraph, add caption after it
        if (para_text.find("[IMAGE") != std::string::npos && caption_count < static_cast<int>(captions_to_add.size())) {
            std::cout << "Adding caption '" << captions_to_add[caption_count] 
                      << "' after image paragraph..." << std::endl;
            
            cdocx::CaptionGenerator::insert_figure_caption(&doc, para, 
                                                            captions_to_add[caption_count],
                                                            0);  // Auto-number
            caption_count++;
        }
    }
    
    std::cout << "Added " << caption_count << " captions" << std::endl;
    
    // Example 4: Add caption at end of document
    std::cout << std::endl << "--- Example 4: Add Caption at Document End ---" << std::endl;
    std::cout << "Adding summary caption at end of document..." << std::endl;
    
    cdocx::CaptionGenerator::insert_figure_caption_at_end(&doc, 
                                                          "Summary of All Detections",
                                                          0);  // Auto-number
    std::cout << "Caption added at end" << std::endl;
    
    // Example 5: Verify captions
    std::cout << std::endl << "--- Example 5: Verify Captions ---" << std::endl;
    int final_count = cdocx::CaptionGenerator::count_existing_figures(&doc);
    std::cout << "Total figures after adding captions: " << final_count << std::endl;
    
    // Example 6: Check specific paragraphs for caption format
    std::cout << std::endl << "--- Example 6: Check Caption Format ---" << std::endl;
    int caption_para_count = 0;
    for (pugi::xml_node para = body.child("w:p"); para; para = para.next_sibling("w:p")) {
        if (cdocx::CaptionGenerator::is_figure_caption(para)) {
            caption_para_count++;
            std::string text = cdocx::CaptionGenerator::extract_caption_text(para);
            std::cout << "  Caption " << caption_para_count << ": " << text << std::endl;
        }
    }
    
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
 * Create a document with image placeholders
 */
bool create_document_with_images(const std::string& doc_path) {
    cdocx::Document doc;
    if (!doc.create_empty(doc_path)) {
        std::cerr << "Failed to create empty document" << std::endl;
        return false;
    }
    
    // Title
    auto title = doc.paragraphs().insert_paragraph_after("Geological Survey Report");
    title.set_bold(true);
    title.set_font_size(36);  // 18pt
    
    doc.paragraphs().insert_paragraph_after("");
    
    // Introduction
    auto intro = doc.paragraphs().insert_paragraph_after(
        "This report contains multiple figures demonstrating different detection methods.");
    
    doc.paragraphs().insert_paragraph_after("");
    
    // Image 1: GPR
    auto p1 = doc.paragraphs().insert_paragraph_after("1. GPR Detection");
    p1.set_bold(true);
    
    auto img1 = doc.paragraphs().insert_paragraph_after("[IMAGE_1_PLACEHOLDER]");
    img1.set_color("FF0000");
    
    doc.paragraphs().insert_paragraph_after("");
    
    // Image 2: TEM
    auto p2 = doc.paragraphs().insert_paragraph_after("2. TEM Analysis");
    p2.set_bold(true);
    
    auto img2 = doc.paragraphs().insert_paragraph_after("[IMAGE_2_PLACEHOLDER]");
    img2.set_color("FF0000");
    
    doc.paragraphs().insert_paragraph_after("");
    
    // Image 3: Survey
    auto p3 = doc.paragraphs().insert_paragraph_after("3. Geological Survey");
    p3.set_bold(true);
    
    auto img3 = doc.paragraphs().insert_paragraph_after("[IMAGE_3_PLACEHOLDER]");
    img3.set_color("FF0000");
    
    doc.paragraphs().insert_paragraph_after("");
    
    // Image 4: Recommendation
    auto p4 = doc.paragraphs().insert_paragraph_after("4. Final Recommendation");
    p4.set_bold(true);
    
    auto img4 = doc.paragraphs().insert_paragraph_after("[IMAGE_4_PLACEHOLDER]");
    img4.set_color("FF0000");
    
    doc.paragraphs().insert_paragraph_after("");
    
    // Conclusion
    auto conclusion = doc.paragraphs().insert_paragraph_after(
        "The above figures demonstrate the comprehensive analysis performed.");
    
    doc.save(doc_path);
    std::cout << "  Created: " << doc_path << std::endl;
    return true;
}
