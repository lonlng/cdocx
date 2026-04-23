/**
 * @file cdocx.cpp
 * @brief CDocx factory implementation
 * @since 0.7.0
 */

#include <cdocx.h>
#include <cdocx/advanced.h>
#include <cdocx/document.h>
#include <cdocx/paragraph_builder.h>
#include <cdocx/table_builder.h>

#include <filesystem>

namespace cdocx {

std::shared_ptr<Document> CDocx::create_document() {
    auto doc = std::make_shared<Document>("");
    doc->create_empty();
    return doc;
}

std::shared_ptr<Document> CDocx::load_document(const std::string& path) {
    auto doc = std::make_shared<Document>(path);
    doc->open(path);
    if (!doc->is_open()) {
        return nullptr;
    }
    return doc;
}

bool CDocx::save_document(const std::shared_ptr<Document>& doc, const std::string& path) {
    if (!doc || !doc->is_open()) {
        return false;
    }
    doc->save(path);
    namespace fs = std::filesystem;
    return fs::exists(path);
}

std::shared_ptr<DocumentBuilder> CDocx::document() {
    auto doc = create_document();
    return std::make_shared<DocumentBuilder>(doc);
}

std::shared_ptr<ParagraphBuilder> CDocx::paragraph() {
    return std::make_shared<ParagraphBuilder>();
}

std::shared_ptr<ParagraphBuilder> CDocx::paragraph(const std::string& text) {
    return std::make_shared<ParagraphBuilder>(text);
}

std::shared_ptr<TableBuilder> CDocx::table() {
    return std::make_shared<TableBuilder>(0, 0);
}

std::shared_ptr<TableBuilder> CDocx::table(size_t rows, size_t columns) {
    return std::make_shared<TableBuilder>(static_cast<int>(rows), static_cast<int>(columns));
}

std::string CDocx::version() {
    return CDOCX_VERSION;
}

std::string CDocx::version_string() {
    return "CDocx v" + std::string(CDOCX_VERSION);
}

}  // namespace cdocx
