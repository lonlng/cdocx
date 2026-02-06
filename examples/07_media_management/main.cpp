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
#include "../example_utils.h"

// Helper to create a minimal test image
void create_test_image(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file) {
        // Minimal JPEG header
        unsigned char jpeg_header[] = {
            0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
            0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
            0x00, 0x01, 0x00, 0x00, 0xFF, 0xD9
        };
        file.write(reinterpret_cast<char*>(jpeg_header), sizeof(jpeg_header));
    }
}

int main() {
    std::cout << "=== Media Management Example ===" << std::endl;
    
    // Get path to document
    std::string doc_path = example_utils::get_resource_path("07_media_management_sample.docx");
    std::string output_path = example_utils::get_output_path("output_07_media_management.docx");
    std::string temp_image_path = example_utils::get_output_path("temp_test_image.jpg");
    
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
    create_test_image(temp_image_path);
    
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
