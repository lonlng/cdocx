#pragma once

#include <cdocx.h>
#include <gtest/gtest.h>
#include <filesystem>
#include <string>

namespace cdocx {
namespace test {

namespace fs = std::filesystem;

// ============================================================================
// RAII Temp File Guard
// ============================================================================

class TempDoc {
public:
    explicit TempDoc(const std::string& path) : path_(path) {
        if (fs::exists(path_)) {
            fs::remove(path_);
        }
    }

    ~TempDoc() {
        if (fs::exists(path_)) {
            fs::remove(path_);
        }
    }

    // Disallow copy, allow move
    TempDoc(const TempDoc&) = delete;
    TempDoc& operator=(const TempDoc&) = delete;
    TempDoc(TempDoc&&) = default;
    TempDoc& operator=(TempDoc&&) = default;

    const std::string& path() const { return path_; }

private:
    std::string path_;
};

// ============================================================================
// Skip Helpers
// ============================================================================

inline void skip_if_not_open(const Document& doc, const std::string& filepath) {
    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open " << filepath << ", skipping test";
    }
}

// ============================================================================
// Safe DOM Navigation Helpers
// ============================================================================

inline std::shared_ptr<Body> get_body(Document& doc) {
    auto sect = doc.get_first_section();
    EXPECT_NE(sect, nullptr) << "Document has no sections";
    if (!sect) return nullptr;

    auto body = sect->get_body();
    EXPECT_TRUE(body != nullptr) << "Section has no body";
    return body;
}

inline std::shared_ptr<Paragraph> get_first_paragraph(Document& doc) {
    auto body = get_body(doc);
    if (!body) return nullptr;

    auto paras = body->get_paragraphs();
    EXPECT_FALSE(paras.empty()) << "Body has no paragraphs";
    if (paras.empty()) return nullptr;

    return paras.front();
}

inline std::shared_ptr<Table> get_first_table(Document& doc) {
    auto body = get_body(doc);
    if (!body) return nullptr;

    auto tables = body->get_tables();
    EXPECT_FALSE(tables.empty()) << "Body has no tables";
    if (tables.empty()) return nullptr;

    return tables.front();
}

// ============================================================================
// Document Setup Helpers
// ============================================================================

inline std::shared_ptr<Body> create_empty_doc(Document& doc) {
    EXPECT_TRUE(doc.create_empty());
    return get_body(doc);
}

}  // namespace test
}  // namespace cdocx
