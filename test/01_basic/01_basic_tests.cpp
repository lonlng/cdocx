#include <sstream>
#include <gtest/gtest.h>
#include "cdocx.h"

TEST(BasicTest, CheckContentsOfMyTestDocx) {
    cdocx::Document doc("data/my_test.docx");
    doc.open();

    // Skip test if document cannot be opened
    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    std::ostringstream ss;

    for (cdocx::Paragraph p = doc.paragraphs(); p.has_next(); p.next()) {
        for (cdocx::Run r = p.runs(); r.has_next(); r.next()) {
            ss << r.get_text() << std::endl;
        }
    }

    EXPECT_EQ("This is a test\nokay?\n", ss.str());
}
