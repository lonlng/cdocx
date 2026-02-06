#include <cdocx.h>
#include <iostream>
#include <zip.h>

int main() {
    std::cout << "Testing ZIP read..." << std::endl;
    
    zip_t* zip = zip_open("test_data/template.docx", 0, 'r');
    if (!zip) {
        std::cout << "Failed to open zip" << std::endl;
        return 1;
    }
    
    ssize_t count = zip_entries_total(zip);
    std::cout << "Total entries: " << count << std::endl;
    
    // Try to read document.xml
    if (zip_entry_open(zip, "word/document.xml") == 0) {
        void* buf = nullptr;
        size_t bufsize = 0;
        ssize_t result = zip_entry_read(zip, &buf, &bufsize);
        
        std::cout << "document.xml - result: " << result << ", size: " << bufsize << std::endl;
        
        if (buf) {
            std::cout << "First 50 bytes: ";
            char* cbuf = static_cast<char*>(buf);
            for (size_t i = 0; i < 50 && i < bufsize; i++) {
                std::cout << cbuf[i];
            }
            std::cout << std::endl;
            free(buf);
        }
        zip_entry_close(zip);
    } else {
        std::cout << "Failed to open word/document.xml" << std::endl;
    }
    
    // Try to read a media file
    if (zip_entry_open(zip, "word/media/image1.png") == 0) {
        void* buf = nullptr;
        size_t bufsize = 0;
        ssize_t result = zip_entry_read(zip, &buf, &bufsize);
        
        std::cout << "image1.png - result: " << result << ", size: " << bufsize << std::endl;
        
        if (buf) {
            free(buf);
        }
        zip_entry_close(zip);
    } else {
        std::cout << "Failed to open word/media/image1.png" << std::endl;
    }
    
    zip_close(zip);
    return 0;
}
