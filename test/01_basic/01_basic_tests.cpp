#include <sstream>
#include "cdocx.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("checks contents of my_test.docx") {
    cdocx::Document doc("my_test.docx");
    doc.open();

    std::ostringstream ss;

    for (cdocx::Paragraph p = doc.paragraphs(); p.has_next(); p.next()) {
        for (cdocx::Run r = p.runs(); r.has_next(); r.next()) {
            ss << r.get_text() << std::endl;
        }
    }

    CHECK_EQ("This is a test\nokay?\n", ss.str());
}
