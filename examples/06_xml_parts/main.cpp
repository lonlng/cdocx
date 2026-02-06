/**
 * Example 06: XML Parts API
 * 
 * This example demonstrates how to:
 * 1. Access all XML parts in a DOCX package
 * 2. Read document metadata (core properties)
 * 3. Access application properties
 * 4. Analyze content types
 * 5. Check for specific XML parts
 */

#include <cdocx.h>
#include <iostream>
#include <iomanip>
#include <set>
#include "../example_utils.h"

void print_part_info(const std::string& path, pugi::xml_document* doc) {
    if (!doc) {
        std::cout << "  [Missing] " << path << std::endl;
        return;
    }
    
    pugi::xml_node root = doc->first_child();
    std::cout << "  [OK] " << std::left << std::setw(30) << path 
              << " Root: " << root.name() << std::endl;
}

void demonstrate_core_properties(pugi::xml_document* core_doc) {
    if (!core_doc) {
        std::cout << "  Core properties not available" << std::endl;
        return;
    }
    
    std::cout << "\n  Core Properties:" << std::endl;
    pugi::xml_node coreProps = core_doc->child("cp:coreProperties");
    if (!coreProps) return;
    
    auto print_prop = [&](const char* label, const char* name) {
        pugi::xml_node node = coreProps.child(name);
        if (node && node.text()) {
            std::cout << "    " << std::left << std::setw(18) << label 
                      << ": " << node.text().get() << std::endl;
        }
    };
    
    print_prop("Title", "dc:title");
    print_prop("Creator", "dc:creator");
    print_prop("Subject", "dc:subject");
    print_prop("Created", "dcterms:created");
    print_prop("Modified", "dcterms:modified");
}

void demonstrate_content_types(pugi::xml_document* ct_doc) {
    if (!ct_doc) return;
    
    std::cout << "\n  Content Types Analysis:" << std::endl;
    pugi::xml_node types = ct_doc->child("Types");
    if (!types) return;
    
    int defaults = 0, overrides = 0;
    std::set<std::string> content_types;
    
    for (auto def = types.child("Default"); def; def = def.next_sibling("Default")) {
        defaults++;
        content_types.insert(def.attribute("ContentType").value());
    }
    
    for (auto ov = types.child("Override"); ov; ov = ov.next_sibling("Override")) {
        overrides++;
        content_types.insert(ov.attribute("ContentType").value());
    }
    
    std::cout << "    Default entries:  " << defaults << std::endl;
    std::cout << "    Override entries: " << overrides << std::endl;
}

int main() {
    std::cout << "=== XML Parts API Example ===" << std::endl;
    
    // Get path to document
    std::string doc_path = example_utils::get_resource_path("06_xml_parts_sample.docx");
    std::cout << "Opening: " << doc_path << std::endl;
    
    // Open document
    cdocx::Document doc(doc_path);
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document: " << doc_path << std::endl;
        return 1;
    }
    
    std::cout << "\n1. Loaded XML Parts:" << std::endl;
    std::cout << "   Total parts: " << doc.get_part_count() << std::endl;
    
    auto parts = doc.get_all_part_names();
    for (const auto& name : parts) {
        print_part_info(name, doc.get_xml_part(name));
    }
    
    // Core properties
    std::cout << "\n2. Document Metadata:" << std::endl;
    demonstrate_core_properties(doc.get_core_properties());
    
    // Content types
    demonstrate_content_types(doc.get_content_types());
    
    // Check specific parts
    std::cout << "\n3. Checking Specific Parts:" << std::endl;
    const char* test_parts[] = {
        "word/styles.xml",
        "word/settings.xml",
        "word/numbering.xml",
        "word/fontTable.xml"
    };
    
    for (const char* part : test_parts) {
        bool exists = doc.has_xml_part(part);
        std::cout << "   " << (exists ? "[OK]" : "[Missing]") 
                  << " " << part << std::endl;
    }
    
    std::cout << "\n=== Example Completed ===" << std::endl;
    return 0;
}
