/**
 * @file main.cpp
 * @brief Example: Edit an existing Word document with images
 * @details This example demonstrates how to:
 *          1. Open an existing DOCX file (with images)
 *          2. Delete specific text content
 *          3. Add new text content
 *          4. Save the modified document (images remain unchanged)
 * 
 *          The document structure (including images) is preserved.
 * 
 * @author CDocx Example
 * @date 2026
 */

#include <cdocx.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace cdocx;

// ============================================================================
// Helper Functions
// ============================================================================

/**
 * @brief Check if text contains a substring (case-insensitive)
 */
bool contains_ignore_case(const std::string& text, const std::string& search) {
    if (search.empty() || text.empty()) return false;
    auto it = std::search(
        text.begin(), text.end(),
        search.begin(), search.end(),
        [](char ch1, char ch2) { return std::tolower(ch1) == std::tolower(ch2); }
    );
    return it != text.end();
}

/**
 * @brief Count paragraphs in document
 */
int count_paragraphs(Document& doc) {
    int count = 0;
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        count++;
    }
    return count;
}

/**
 * @brief Get all paragraph texts
 */
std::vector<std::string> get_all_paragraph_texts(Document& doc) {
    std::vector<std::string> texts;
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        std::string text = para.get_text();
        if (!text.empty()) {
            texts.push_back(text);
        }
    }
    return texts;
}

// ============================================================================
// Edit Operations
// ============================================================================

/**
 * @brief Delete all text in paragraphs containing specific keyword
 * @param doc The document to edit
 * @param keyword The keyword to search for
 * @return Number of paragraphs cleared
 */
int delete_paragraphs_with_keyword(Document& doc, const std::string& keyword) {
    std::cout << "[DELETE] Looking for paragraphs containing: \"" << keyword << "\"" << std::endl;
    
    int deleted = 0;
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        std::string para_text = para.get_text();
        
        if (contains_ignore_case(para_text, keyword)) {
            std::cout << "  Found: \"" << para_text.substr(0, 50) 
                      << (para_text.length() > 50 ? "..." : "") << "\"" << std::endl;
            
            // Clear all runs in this paragraph
            for (auto run = para.runs(); run.has_next(); run.next()) {
                run.set_text("");
            }
            deleted++;
        }
    }
    
    std::cout << "  Deleted " << deleted << " paragraph(s)" << std::endl;
    return deleted;
}

/**
 * @brief Replace text in all paragraphs
 * @param doc The document to edit
 * @param old_text Text to find
 * @param new_text Text to replace with
 * @return Number of replacements made
 */
int replace_text(Document& doc, const std::string& old_text, const std::string& new_text) {
    std::cout << "[REPLACE] \"" << old_text << "\" -> \"" << new_text << "\"" << std::endl;
    
    int replacements = 0;
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        for (auto run = para.runs(); run.has_next(); run.next()) {
            std::string current_text = run.get_text();
            
            size_t pos = current_text.find(old_text);
            if (pos != std::string::npos) {
                std::string new_content = current_text;
                if ((pos = new_content.find(old_text)) != std::string::npos) {
                    new_content.replace(pos, old_text.length(), new_text);
                    replacements++;
                }
                run.set_text(new_content);
                std::cout << "  Replaced in: \"" << current_text << "\"" << std::endl;
            }
        }
    }
    
    std::cout << "  Total replacements: " << replacements << std::endl;
    return replacements;
}

/**
 * @brief Add a new paragraph at the end of the document
 * @param doc The document to edit
 * @param text Text content for the new paragraph
 * @param flags Formatting flags (bold, italic, etc.)
 */
void add_paragraph_at_end(Document& doc, const std::string& text, FormattingFlag flags = kNone) {
    std::cout << "[ADD] Adding paragraph at end: \"" << text << "\"" << std::endl;
    
    // Find the last paragraph
    Paragraph* last_para = nullptr;
    Paragraph current = doc.paragraphs();
    
    while (current.has_next()) {
        last_para = &current;
        current.next();
    }
    
    if (last_para) {
        last_para->insert_paragraph_after(text, flags);
        std::cout << "  Added successfully" << std::endl;
    } else {
        std::cout << "  Warning: No paragraphs found" << std::endl;
    }
}

/**
 * @brief Add multiple paragraphs with different formatting
 * @param doc The document to edit
 */
void add_formatted_paragraphs(Document& doc) {
    std::cout << "[ADD] Adding formatted paragraphs..." << std::endl;
    
    // Find the last paragraph
    Paragraph* last_para = nullptr;
    Paragraph current = doc.paragraphs();
    
    while (current.has_next()) {
        last_para = &current;
        current.next();
    }
    
    if (!last_para) {
        std::cout << "  Warning: No paragraphs found" << std::endl;
        return;
    }
    
    // Add a separator paragraph
    auto& sep = last_para->insert_paragraph_after("", kNone);
    
    // Add bold paragraph
    Paragraph* current_ptr = &sep;
    current_ptr = &(current_ptr->insert_paragraph_after(
        "=== This is a BOLD paragraph added by CDocx ===", kBold));
    std::cout << "  Added bold paragraph" << std::endl;
    
    // Add italic paragraph
    current_ptr = &(current_ptr->insert_paragraph_after(
        "=== This is an ITALIC paragraph added by CDocx ===", kItalic));
    std::cout << "  Added italic paragraph" << std::endl;
    
    // Add underlined paragraph
    current_ptr->insert_paragraph_after(
        "=== This is an UNDERLINED paragraph added by CDocx ===", kUnderline);
    std::cout << "  Added underlined paragraph" << std::endl;
}

/**
 * @brief Modify text formatting for specific content
 * @param doc The document to edit
 * @param search_text Text to find
 * @param flags Formatting to apply
 */
void apply_formatting_to_text(Document& doc, const std::string& search_text, FormattingFlag flags) {
    std::cout << "[FORMAT] Applying formatting to text containing: \"" << search_text << "\"" << std::endl;
    
    int formatted = 0;
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        for (auto run = para.runs(); run.has_next(); run.next()) {
            std::string text = run.get_text();
            
            if (contains_ignore_case(text, search_text)) {
                // Apply formatting based on flags
                if (flags & kBold) {
                    run.set_bold(true);
                    std::cout << "  Applied BOLD to: \"" << text << "\"" << std::endl;
                }
                if (flags & kItalic) {
                    run.set_italic(true);
                    std::cout << "  Applied ITALIC to: \"" << text << "\"" << std::endl;
                }
                formatted++;
            }
        }
    }
    
    std::cout << "  Formatted " << formatted << " run(s)" << std::endl;
}

// ============================================================================
// Display Functions
// ============================================================================

/**
 * @brief Display document statistics
 */
void display_document_stats(Document& doc) {
    std::cout << "\n========== Document Statistics ==========" << std::endl;
    
    int para_count = 0;
    int run_count = 0;
    int total_chars = 0;
    
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        para_count++;
        std::string para_text = para.get_text();
        total_chars += static_cast<int>(para_text.length());
        
        for (auto run = para.runs(); run.has_next(); run.next()) {
            run_count++;
        }
    }
    
    std::cout << "  Paragraphs: " << para_count << std::endl;
    std::cout << "  Runs: " << run_count << std::endl;
    std::cout << "  Total characters: " << total_chars << std::endl;
    std::cout << "==========================================\n" << std::endl;
}

/**
 * @brief Display all paragraph content
 */
void display_content(Document& doc, const std::string& title) {
    std::cout << "\n========== " << title << " ==========" << std::endl;
    
    int index = 0;
    for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
        std::string text = para.get_text();
        if (!text.empty()) {
            // Truncate long text for display
            std::string display_text = text;
            if (display_text.length() > 80) {
                display_text = display_text.substr(0, 77) + "...";
            }
            std::cout << "[" << index << "] " << display_text << std::endl;
            index++;
        }
    }
    
    if (index == 0) {
        std::cout << "(No text content)" << std::endl;
    }
    
    std::cout << "========================================\n" << std::endl;
}

/**
 * @brief List all media files in the document
 */
void list_media_files(Document& doc) {
    std::cout << "\n========== Media Files ==========" << std::endl;
    
    std::vector<std::string> media = doc.list_media();
    if (media.empty()) {
        std::cout << "  No media files found" << std::endl;
    } else {
        for (const auto& file : media) {
            std::cout << "  - " << file << std::endl;
        }
    }
    
    std::cout << "==================================\n" << std::endl;
}

// ============================================================================
// Main Function
// ============================================================================

int main(int argc, char* argv[]) {
    try {
        // Default file paths
        std::string input_file = "data/10_example.docx";
        std::string output_file = "data/10_example_edited.docx";
        
        // Allow command line override
        if (argc > 1) {
            input_file = argv[1];
        }
        if (argc > 2) {
            output_file = argv[2];
        }
        
        std::cout << "╔════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║     CDocx Document Editor Example (with Images)            ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << std::endl;
        
        // Step 1: Open the document
        std::cout << "[OPEN] Opening document: " << input_file << std::endl;
        Document doc(input_file);
        doc.open();
        
        if (!doc.is_open()) {
            std::cerr << "[ERROR] Failed to open document: " << input_file << std::endl;
            std::cerr << "        Make sure the file exists and is a valid .docx file" << std::endl;
            return 1;
        }
        
        std::cout << "       Document opened successfully!" << std::endl;
        std::cout << std::endl;
        
        // Display original document info
        display_document_stats(doc);
        list_media_files(doc);
        display_content(doc, "Original Content");
        
        // Step 2: Perform edit operations
        std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                EDIT OPERATIONS                             ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << std::endl;
        
        // Edit 1: Delete paragraphs containing "TestBlue"
        std::cout << "┌─ Operation 1: Delete Text ─────────────────────────────────┐" << std::endl;
        int deleted = delete_paragraphs_with_keyword(doc, "TestBlue");
        std::cout << "└────────────────────────────────────────────────────────────┘" << std::endl;
        std::cout << std::endl;
        
        // Edit 2: Replace "TestRed" with "TestRed (MODIFIED)"
        std::cout << "┌─ Operation 2: Replace Text ────────────────────────────────┐" << std::endl;
        int replaced = replace_text(doc, "TestRed", "TestRed (MODIFIED)");
        std::cout << "└────────────────────────────────────────────────────────────┘" << std::endl;
        std::cout << std::endl;
        
        // Edit 3: Make "TestGreen" text bold
        std::cout << "┌─ Operation 3: Format Text ─────────────────────────────────┐" << std::endl;
        apply_formatting_to_text(doc, "TestGreen", kBold);
        std::cout << "└────────────────────────────────────────────────────────────┘" << std::endl;
        std::cout << std::endl;
        
        // Edit 4: Add new formatted paragraphs
        std::cout << "┌─ Operation 4: Add New Paragraphs ──────────────────────────┐" << std::endl;
        add_formatted_paragraphs(doc);
        std::cout << "└────────────────────────────────────────────────────────────┘" << std::endl;
        std::cout << std::endl;
        
        // Step 3: Display modified content
        std::cout << "╔════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                MODIFIED DOCUMENT                           ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
        display_document_stats(doc);
        display_content(doc, "Modified Content");
        
        // Step 4: Save the modified document
        std::cout << "[SAVE] Saving to: " << output_file << std::endl;
        doc.save(output_file);
        
        if (doc.is_open()) {
            std::cout << "       Document saved successfully!" << std::endl;
        } else {
            std::cerr << "[ERROR] Failed to save document" << std::endl;
            return 1;
        }
        
        // Close the document
        doc.close();
        
        // Summary
        std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                     SUMMARY                                ║" << std::endl;
        std::cout << "╠════════════════════════════════════════════════════════════╣" << std::endl;
        std::cout << "║  Input file:  " << input_file << std::endl;
        std::cout << "║  Output file: " << output_file << std::endl;
        std::cout << "║  Paragraphs deleted: " << deleted << std::endl;
        std::cout << "║  Text replacements:  " << replaced << std::endl;
        std::cout << "║  Images preserved:   Yes (unchanged)" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════╝" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return 1;
    }
}
