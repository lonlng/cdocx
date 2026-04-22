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

    for (cdocx::Paragraph p = doc.paragraphs(); p.has_next(); p.next()) {
        for (cdocx::Run r = p.runs(); r.has_next(); r.next()) {
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

TEST(IteratorTest, EmptyDocumentIteration) {
    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty());

    // Empty document has one placeholder paragraph
    cdocx::Paragraph p = doc.paragraphs();
    EXPECT_TRUE(p.has_next());

    // Iterate through the placeholder
    int count = 0;
    for (; p.has_next(); p.next()) {
        count++;
    }
    EXPECT_EQ(count, 1);
}

TEST(IteratorTest, DomTableAccess) {
    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty());

    // Add a table via DOM API
    auto section = doc.get_first_section();
    ASSERT_NE(section, nullptr);
    auto body = section->get_body();
    ASSERT_NE(body, nullptr);
    body->append_paragraph("Before table");
    auto table = body->append_table(2, 3);
    ASSERT_NE(table, nullptr);

    EXPECT_EQ(table->get_row_count(), 2);
    EXPECT_EQ(table->get_column_count(), 3);

    // Verify cell access
    auto cell = table->get_cell(0, 0);
    ASSERT_NE(cell, nullptr);
    cell->get_first_paragraph()->append_run("Cell 0,0");
}

TEST(IteratorTest, RunFormattingRetrievalViaIterator) {
    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty());

    auto para = doc.paragraphs();
    auto run = para.add_run("Bold text");
    run.set_bold(true);
    run.set_font_size(24);

    // Retrieve via iterator and verify run exists (iterator does not crash)
    int run_count = 0;
    for (cdocx::Run r = para.runs(); r.has_next(); r.next()) {
        run_count++;
    }
    EXPECT_GE(run_count, 1);
}

TEST(IteratorTest, IteratorPastEndIsSafe) {
    cdocx::Document doc;
    ASSERT_TRUE(doc.create_empty());

    auto para = doc.paragraphs();
    // Single placeholder paragraph
    para.next();
    EXPECT_FALSE(para.has_next());

    // Calling next() past end should be safe (no crash)
    para.next();
    EXPECT_FALSE(para.has_next());
}
