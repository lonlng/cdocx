/**
 * Example 07: Media Management
 * 
 * This example demonstrates how to:
 * 1. List all media files in a DOCX package
 * 2. Check if a media file exists
 * 3. Export media files from the document
 * 4. Add new media files
 * 5. Replace media files
 * 6. Delete media files
 */

#include <cdocx.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

// Minimal 1x1 pixel JPEG image data (for embedding)
const unsigned char MINIMAL_JPEG[] = {
    0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
    0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
};

// Minimal PNG image (1x1 pixel transparent)
const unsigned char MINIMAL_PNG[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4,
    0x89, 0x00, 0x00, 0x00, 0x0A, 0x49, 0x44, 0x41,
    0x54, 0x78, 0x9C, 0x63, 0x60, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x01, 0xE2, 0x21, 0xBC, 0x33, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE,
    0x42, 0x60, 0x82
};

void save_binary_file(const std::string& path, const unsigned char* data, size_t size) {
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data), size);
}

// Forward declaration
bool create_sample_document(const std::string& doc_path,
                            const std::string& image1_path,
                            const std::string& image2_path);

int main() {
    std::cout << "=== Media Management Example ===" << std::endl;
    
    std::string doc_path = "data/07_media_management_sample.docx";
    std::string image1_path = "data/07_sample_image1.jpg";
    std::string image2_path = "data/07_sample_image2.png";
    std::string output_path = "output_07_media_management.docx";
    std::string temp_image_path = "temp_test_image.jpg";
    
    // Create data directory if needed
    std::filesystem::create_directories("data");
    
    // Create sample document and images if they don't exist
    if (!std::filesystem::exists(doc_path)) {
        std::cout << "Creating sample document and images..." << std::endl;
        if (!create_sample_document(doc_path, image1_path, image2_path)) {
            std::cerr << "Failed to create sample document" << std::endl;
            return 1;
        }
    }
    
    std::cout << "Opening: " << doc_path << std::endl;
    
    // Open a document that contains media
    cdocx::Document doc(doc_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document: " << doc_path << std::endl;
        return 1;
    }
    
    std::cout << "\n1. List Media Files:" << std::endl;
    std::vector<std::string> media = doc.list_media();
    if (media.empty()) {
        std::cout << "   No media files found" << std::endl;
    } else {
        std::cout << "   Found " << media.size() << " media file(s):" << std::endl;
        for (const auto& m : media) {
            std::cout << "   - " << m << std::endl;
        }
    }
    
    std::cout << "\n2. Check Media Existence:" << std::endl;
    if (!media.empty()) {
        std::cout << "   '" << media[0] << "' exists: " 
                  << (doc.has_media(media[0]) ? "Yes" : "No") << std::endl;
    }
    std::cout << "   'nonexistent.jpg' exists: " 
              << (doc.has_media("nonexistent.jpg") ? "Yes" : "No") << std::endl;
    
    // Create test image for add/replace operations
    save_binary_file(temp_image_path, MINIMAL_JPEG, sizeof(MINIMAL_JPEG));
    
    std::cout << "\n3. Add New Media:" << std::endl;
    std::string new_image_name = "my_new_image.jpg";
    if (doc.add_media(temp_image_path, &new_image_name)) {
        std::cout << "   Successfully added 'my_new_image.jpg'" << std::endl;
    } else {
        std::cout << "   Failed to add media" << std::endl;
    }
    
    std::cout << "\n4. Replace Media:" << std::endl;
    if (!media.empty()) {
        if (doc.replace_media(media[0], temp_image_path)) {
            std::cout << "   Successfully replaced '" << media[0] << "'" << std::endl;
        }
    }
    
    // Save document with changes
    doc.save(output_path);
    std::cout << "\n5. Document saved: " << output_path << std::endl;
    
    // Cleanup
    std::remove(temp_image_path.c_str());
    
    std::cout << "\n=== Example Completed ===" << std::endl;
    return 0;
}

// Create the sample document and images used by this example
bool create_sample_document(const std::string& doc_path,
                            const std::string& image1_path,
                            const std::string& image2_path) {
    // Create sample images
    save_binary_file(image1_path, MINIMAL_JPEG, sizeof(MINIMAL_JPEG));
    save_binary_file(image2_path, MINIMAL_PNG, sizeof(MINIMAL_PNG));
    std::cout << "  Created: " << image1_path << std::endl;
    std::cout << "  Created: " << image2_path << std::endl;
    
    cdocx::Document doc(doc_path);
    
    if (!doc.create_empty()) {
        std::cerr << "Failed to create empty document" << std::endl;
        return false;
    }
    
    auto p1 = doc.paragraphs().insert_paragraph_after("Media Management Sample Document");
    auto p2 = doc.paragraphs().insert_paragraph_after("This document contains embedded images for media management demonstration.");
    auto p3 = doc.paragraphs().insert_paragraph_after("");
    auto p4 = doc.paragraphs().insert_paragraph_after("Images in this document:");
    auto p5 = doc.paragraphs().insert_paragraph_after("  - sample_image1.jpg (JPEG)");
    auto p6 = doc.paragraphs().insert_paragraph_after("  - sample_image2.png (PNG)");
    
    // Add images
    doc.add_media_with_rel(image1_path);
    doc.add_media_with_rel(image2_path);
    
    doc.save(doc_path);
    std::cout << "  Created: " << doc_path << std::endl;
    return true;
}
