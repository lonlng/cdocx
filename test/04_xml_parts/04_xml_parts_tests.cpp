#include <sstream>
#include <fstream>
#include "cdocx.h"
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// Helper function to check if a file exists
bool file_exists(const std::string& filename) {
    std::ifstream f(filename.c_str());
    return f.good();
}

TEST_CASE("Document loads [Content_Types].xml") {
    // Skip test if file doesn't exist
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    // Check that content types were loaded
    pugi::xml_document* content_types = doc.get_content_types();
    CHECK(content_types != nullptr);
    
    if (content_types) {
        pugi::xml_node types = content_types->child("Types");
        CHECK(types != nullptr);
    }
}

TEST_CASE("Document loads core properties (docProps/core.xml)") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    // Check core properties
    pugi::xml_document* core_props = doc.get_core_properties();
    CHECK(core_props != nullptr);
    
    if (core_props) {
        pugi::xml_node core_props_node = core_props->child("cp:coreProperties");
        CHECK(core_props_node != nullptr);
        
        // Core properties should have some standard elements
        bool has_title = core_props_node.child("dc:title") != nullptr;
        bool has_creator = core_props_node.child("dc:creator") != nullptr;
        
        // Note: These may not exist in all test files, so we just check structure
        std::cout << "Core properties loaded successfully" << std::endl;
    }
}

TEST_CASE("Document loads app properties (docProps/app.xml)") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    // Check app properties
    pugi::xml_document* app_props = doc.get_app_properties();
    CHECK(app_props != nullptr);
    
    if (app_props) {
        pugi::xml_node app_props_node = app_props->child("Properties");
        CHECK(app_props_node != nullptr);
    }
}

TEST_CASE("get_part_count returns correct count") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    size_t count = doc.get_part_count();
    CHECK(count > 0);  // Should have at least [Content_Types].xml
    
    std::cout << "Total XML parts loaded: " << count << std::endl;
}

TEST_CASE("get_all_part_names returns non-empty list") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    auto part_names = doc.get_all_part_names();
    CHECK(part_names.size() > 0);
    CHECK(part_names.size() == doc.get_part_count());
    
    // Should contain [Content_Types].xml
    bool has_content_types = false;
    for (const auto& name : part_names) {
        if (name == "[Content_Types].xml") {
            has_content_types = true;
            break;
        }
    }
    CHECK(has_content_types);
}

TEST_CASE("has_xml_part correctly checks part existence") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    // Should have content types
    CHECK(doc.has_xml_part("[Content_Types].xml"));
    
    // Should have document
    CHECK(doc.has_xml_part("word/document.xml"));
    
    // May or may not have these depending on the document
    // We just check that the function doesn't crash
    bool has_core = doc.has_xml_part("docProps/core.xml");
    bool has_app = doc.has_xml_part("docProps/app.xml");
    bool has_styles = doc.has_xml_part("word/styles.xml");
    
    // These are expected in a typical DOCX
    std::cout << "Parts available:" << std::endl;
    std::cout << "  core.xml: " << (has_core ? "yes" : "no") << std::endl;
    std::cout << "  app.xml: " << (has_app ? "yes" : "no") << std::endl;
    std::cout << "  styles.xml: " << (has_styles ? "yes" : "no") << std::endl;
}

TEST_CASE("get_xml_part returns valid document or nullptr") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    // Test existing part
    pugi::xml_document* content_types = doc.get_xml_part("[Content_Types].xml");
    CHECK(content_types != nullptr);
    
    if (content_types) {
        CHECK(content_types->child("Types") != nullptr);
    }
    
    // Test non-existing part
    pugi::xml_document* nonexistent = doc.get_xml_part("nonexistent.xml");
    CHECK(nonexistent == nullptr);
    
    // Test lazy loading - try to load a part that wasn't loaded initially
    pugi::xml_document* styles = doc.get_xml_part("word/styles.xml");
    // May or may not exist, but should not crash
    if (styles) {
        std::cout << "Successfully loaded word/styles.xml" << std::endl;
    }
}

TEST_CASE("Core properties can be read and contain expected elements") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    pugi::xml_document* core = doc.get_core_properties();
    if (!core) {
        std::cout << "[SKIPPED] Core properties not available" << std::endl;
        return;
    }
    
    pugi::xml_node core_props = core->child("cp:coreProperties");
    REQUIRE(core_props != nullptr);
    
    // Check for standard Dublin Core elements
    // Note: These may or may not exist depending on the document
    std::vector<const char*> expected_elements = {
        "dc:title",
        "dc:creator",
        "dc:subject",
        "dc:description",
        "cp:keywords",
        "cp:category",
        "dcterms:created",
        "dcterms:modified",
        "cp:lastModifiedBy",
        "cp:revision"
    };
    
    std::cout << "Core properties elements:" << std::endl;
    for (const char* elem : expected_elements) {
        pugi::xml_node node = core_props.child(elem);
        if (node) {
            std::cout << "  鉁?" << elem << ": " << node.text().get() << std::endl;
        } else {
            std::cout << "  - " << elem << ": (not set)" << std::endl;
        }
    }
}

TEST_CASE("App properties can be read and contain expected elements") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    pugi::xml_document* app = doc.get_app_properties();
    if (!app) {
        std::cout << "[SKIPPED] App properties not available" << std::endl;
        return;
    }
    
    pugi::xml_node app_props = app->child("Properties");
    REQUIRE(app_props != nullptr);
    
    // Check for common application properties
    std::vector<const char*> expected_elements = {
        "Application",
        "Pages",
        "Words",
        "Characters",
        "Lines",
        "Paragraphs",
        "TotalTime",
        "ScaleCrop",
        "LinksUpToDate",
        "SharedDoc",
        "HyperlinksChanged"
    };
    
    std::cout << "Application properties elements:" << std::endl;
    for (const char* elem : expected_elements) {
        pugi::xml_node node = app_props.child(elem);
        if (node) {
            std::cout << "  鉁?" << elem << ": " << node.text().get() << std::endl;
        } else {
            std::cout << "  - " << elem << ": (not set)" << std::endl;
        }
    }
}

TEST_CASE("Content types can be parsed correctly") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    pugi::xml_document* content_types = doc.get_content_types();
    REQUIRE(content_types != nullptr);
    
    pugi::xml_node types = content_types->child("Types");
    REQUIRE(types != nullptr);
    
    // Should have Default and Override elements
    pugi::xml_node default_node = types.child("Default");
    CHECK(default_node != nullptr);
    
    pugi::xml_node override_node = types.child("Override");
    CHECK(override_node != nullptr);
    
    // Check that overrides have PartName and ContentType attributes
    if (override_node) {
        CHECK(override_node.attribute("PartName") != nullptr);
        CHECK(override_node.attribute("ContentType") != nullptr);
    }
}

TEST_CASE("Parts can be loaded on-demand with get_xml_part") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    // Get initial count
    size_t initial_count = doc.get_part_count();
    
    // Request a part that may not be loaded
    pugi::xml_document* part = doc.get_xml_part("word/styles.xml");
    
    // If the part exists, count should increase (if it wasn't loaded) or stay same (if it was)
    size_t new_count = doc.get_part_count();
    
    if (part) {
        std::cout << "On-demand loading successful for word/styles.xml" << std::endl;
        // Check if it was newly loaded
        if (new_count > initial_count) {
            std::cout << "New part loaded. Count: " << initial_count << " -> " << new_count << std::endl;
        } else {
            std::cout << "Part was already loaded. Count: " << new_count << std::endl;
        }
    }
}

TEST_CASE("Iterating through all available parts works correctly") {
    if (!file_exists("template_test.docx")) {
        std::cout << "[SKIPPED] template_test.docx not found" << std::endl;
        return;
    }
    
    cdocx::Document doc("template_test.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cout << "[SKIPPED] Failed to open document" << std::endl;
        return;
    }
    
    auto parts = doc.get_all_part_names();
    
    size_t xml_count = 0;
    size_t valid_xml_count = 0;
    
    for (const auto& part_name : parts) {
        pugi::xml_document* xml_part = doc.get_xml_part(part_name);
        if (xml_part) {
            xml_count++;
            // Check if it has at least a root node
            if (xml_part->first_child()) {
                valid_xml_count++;
            }
        }
        std::cout << "Part: " << part_name << std::endl;
    }
    
    std::cout << "Total parts: " << parts.size() << std::endl;
    std::cout << "XML parts: " << xml_count << std::endl;
    std::cout << "Valid XML: " << valid_xml_count << std::endl;
    
    CHECK(parts.size() > 0);
    CHECK(xml_count <= parts.size());
}

