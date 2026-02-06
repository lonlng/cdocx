#include <cdocx.h>
#include <iostream>
#include <zip.h>

int main() {
    std::cout << "Testing ZIP read with index iteration..." << std::endl;
    
    zip_t* zip = zip_open("test_data/template.docx", 0, 'r');
    if (!zip) {
        std::cout << "Failed to open zip" << std::endl;
        return 1;
    }
    
    ssize_t count = zip_entries_total(zip);
    std::cout << "Total entries: " << count << std::endl;
    
    int xml_count = 0;
    int media_count = 0;
    
    for (ssize_t i = 0; i < count; i++) {
        if (zip_entry_openbyindex(zip, i) != 0) {
            std::cout << "Failed to open entry " << i << std::endl;
            continue;
        }
        
        const char* name = zip_entry_name(zip);
        if (!name) {
            zip_entry_close(zip);
            continue;
        }
        
        std::string entry_name(name);
        
        // Skip directories
        if (entry_name.empty() || entry_name.back() == '/') {
            zip_entry_close(zip);
            continue;
        }
        
        void* buf = nullptr;
        size_t bufsize = 0;
        ssize_t result = zip_entry_read(zip, &buf, &bufsize);
        
        if (entry_name.find("document.xml") != std::string::npos) {
            std::cout << "document.xml - result: " << result << ", size: " << bufsize << std::endl;
        }
        
        if (entry_name.substr(0, 11) == "word/media/") {
            media_count++;
            if (media_count == 1) {
                std::cout << "First media file: " << entry_name << " - result: " << result << ", size: " << bufsize << std::endl;
            }
        }
        
        bool is_xml = entry_name.size() > 4 && entry_name.substr(entry_name.size() - 4) == ".xml";
        bool is_rels = entry_name.size() > 5 && entry_name.substr(entry_name.size() - 5) == ".rels";
        
        if (is_xml || is_rels) {
            xml_count++;
        }
        
        if (buf) free(buf);
        zip_entry_close(zip);
    }
    
    std::cout << "Total XML files found: " << xml_count << std::endl;
    std::cout << "Total media files found: " << media_count << std::endl;
    
    zip_close(zip);
    return 0;
}
