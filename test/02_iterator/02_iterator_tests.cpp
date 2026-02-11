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

    for (cdocx::Paragraph p : doc.paragraphs()) {
        for (cdocx::Run r : p.runs()) {
            ss << r.get_text() << std::endl;
        }
    }
    std::puts(ss.str().c_str());
    EXPECT_EQ("This is a test\nokay?\n", ss.str());
}

namespace cdocx {
struct MyTestObject final {
    int current = 42;
    int parent = 1;
    int j = 86;
    MyTestObject(int parent, int current) : parent(parent), current(current) {}
    MyTestObject() = default;
    MyTestObject& next() { ++current; return *this; }
    bool has_next() const { return current != j; }
    bool operator== (MyTestObject const& other) const { return other.current == current && other.j == j; }
};
// Entry point
auto begin(MyTestObject const& obj) -> Iterator<MyTestObject, int> {
    return Iterator<MyTestObject, int, int>(obj.parent, obj.current);
}

auto end(MyTestObject const& obj) -> Iterator<MyTestObject, int> {
    return Iterator<MyTestObject, int, int>(obj.parent, static_cast<decltype(obj.current)>(0));
}
}  // namespace cdocx

TEST(IteratorTest, CheckEqualityIn) {
    auto const testObject = cdocx::MyTestObject{};
    auto p1 = begin(testObject);
    auto p2 = begin(testObject);
    EXPECT_EQ(p1, p2);
    cdocx::Document doc("data/my_test.docx");
    doc.open();

    if (!doc.is_open()) {
        GTEST_SKIP() << "Could not open data/my_test.docx, skipping test";
    }

    EXPECT_EQ(begin(doc.paragraphs()), begin(doc.paragraphs()));
}
