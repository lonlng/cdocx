#include <sstream>
#include <gtest/gtest.h>
#include <cdocx.h>

TEST(IteratorTest, CheckContentsOfMyTestDocxWithIterator) {
    cdocx::Document doc("data/my_test.docx");
    doc.open();

    // Skip test if document cannot be opened
    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    std::ostringstream ss;

    cdocx::Paragraph p = doc.paragraphs();
    while (p.has_next()) {
        p.next();
        cdocx::Run r = p.runs();
        while (r.has_next()) {
            r.next();
            ss << r.get_text() << std::endl;
        }
    }
    std::puts(ss.str().c_str());
    EXPECT_EQ("This is a test\nokay?\n", ss.str());
}

TEST(IteratorTest, ParagraphIteratorEquality) {
    cdocx::Document doc("data/my_test.docx");
    doc.open();

    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    cdocx::Paragraph p1 = doc.paragraphs();
    cdocx::Paragraph p2 = doc.paragraphs();
    EXPECT_EQ(p1.get_text(), p2.get_text());
}
