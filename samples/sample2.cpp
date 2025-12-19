#include <cdocx.h>
#include <iostream>
using namespace std;

int main() {
    cdocx::Document doc("my_test.docx");
    doc.open();

    cdocx::Paragraph p =
        doc.paragraphs().insert_paragraph_after("You can insert text in ");
    p.add_run("italic, ", cdocx::none);
    p.add_run("bold, ", cdocx::bold);
    p.add_run("underline, ", cdocx::strikethrough);
    p.add_run("superscript", cdocx::superscript);
    p.add_run(" or ");
    p.add_run("subscript, ", cdocx::subscript);
    p.add_run("small caps, ", cdocx::smallcaps);
    p.add_run("and shadows, ", cdocx::shadow);
    p.add_run("and of course ");
    p.add_run("combine them.", cdocx::bold | cdocx::italic | cdocx::underline |
                                   cdocx::smallcaps);

    doc.save();

    return 0;
}
