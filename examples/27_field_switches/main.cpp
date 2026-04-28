/**
 * @file main.cpp
 * @brief Field switches and advanced field configuration demonstration
 * @since 0.8.0
 */

#include <cdocx.h>
#include <cdocx/advanced.h>
#include <iostream>

int main() {
    auto doc = cdocx::CDocx::create_document();
    cdocx::DocumentBuilder builder(doc.get());

    builder.move_to_document_start();

    // ------------------------------------------------------------------------
    // Page number with format switch
    // ------------------------------------------------------------------------
    auto page_field = builder.insert_page_number("\\* ROMAN");
    std::cout << "Page number field:\n";
    std::cout << "  Code:      " << page_field->get_field_code() << "\n";
    std::cout << "  Switches:  " << page_field->get_switches_text() << "\n";
    std::cout << "  Full code: " << page_field->get_full_field_code() << "\n\n";

    // ------------------------------------------------------------------------
    // Date field with custom format switch
    // ------------------------------------------------------------------------
    builder.insert_paragraph();
    auto date_field = builder.insert_date("\\@ \"yyyy-MM-dd\"");
    std::cout << "Date field:\n";
    std::cout << "  Code:      " << date_field->get_field_code() << "\n";
    std::cout << "  Switches:  " << date_field->get_switches_text() << "\n\n";

    // ------------------------------------------------------------------------
    // Time field with format switch
    // ------------------------------------------------------------------------
    builder.insert_paragraph();
    auto time_field = builder.insert_time("\\@ \"HH:mm\"");
    std::cout << "Time field:\n";
    std::cout << "  Code:      " << time_field->get_field_code() << "\n";
    std::cout << "  Switches:  " << time_field->get_switches_text() << "\n\n";

    // ------------------------------------------------------------------------
    // Merge field with text-transform switch
    // ------------------------------------------------------------------------
    builder.insert_paragraph();
    auto merge_field = builder.insert_merge_field("CustomerName", "\\* Upper");
    std::cout << "Merge field:\n";
    std::cout << "  Code:      " << merge_field->get_field_code() << "\n";
    std::cout << "  Switches:  " << merge_field->get_switches_text() << "\n\n";

    // ------------------------------------------------------------------------
    // Table of contents with outline level and hyperlink switches
    // ------------------------------------------------------------------------
    builder.insert_paragraph();
    auto toc_field = builder.insert_table_of_contents("\\o \"1-3\" \\h \\z");
    std::cout << "TOC field:\n";
    std::cout << "  Code:      " << toc_field->get_field_code() << "\n";
    std::cout << "  Switches:  " << toc_field->get_switches_text() << "\n\n";

    // ------------------------------------------------------------------------
    // Manual field creation with multiple switches
    // ------------------------------------------------------------------------
    builder.insert_paragraph();
    auto manual_field = std::make_shared<cdocx::Field>();
    manual_field->set_field_code("PAGE");
    manual_field->add_switch("\\* MERGEFORMAT");
    manual_field->add_switch("\\# \"0\"");
    manual_field->set_result("1");

    std::cout << "Manual field:\n";
    std::cout << "  Code:       " << manual_field->get_field_code() << "\n";
    std::cout << "  Switches:   " << manual_field->get_switches_text() << "\n";
    std::cout << "  Full code:  " << manual_field->get_full_field_code() << "\n";
    std::cout << "  Result:     " << manual_field->get_result() << "\n";
    std::cout << "  Switch count: " << manual_field->get_switches().size() << "\n\n";

    // ------------------------------------------------------------------------
    // Field properties
    // ------------------------------------------------------------------------
    std::cout << "Field properties:\n";
    std::cout << "  Locked: " << (manual_field->is_locked() ? "yes" : "no") << "\n";
    std::cout << "  Dirty:  " << (manual_field->is_dirty() ? "yes" : "no") << "\n\n";

    // ------------------------------------------------------------------------
    // Clone a field (preserves switches and result)
    // ------------------------------------------------------------------------
    auto cloned = std::dynamic_pointer_cast<cdocx::Field>(manual_field->clone(true));
    std::cout << "Cloned field:\n";
    std::cout << "  Code:    " << cloned->get_field_code() << "\n";
    std::cout << "  Switches:" << cloned->get_switches_text() << "\n";
    std::cout << "  Result:  " << cloned->get_result() << "\n\n";

    // ------------------------------------------------------------------------
    // Unlink: replace field with its static result text
    // ------------------------------------------------------------------------
    auto unlink_field = std::make_shared<cdocx::Field>(cdocx::FieldType::MergeField);
    unlink_field->set_field_code("MERGEFIELD Name");
    unlink_field->set_result("Alice");
    unlink_field->unlink();
    std::cout << "After unlink:\n";
    std::cout << "  Text: " << unlink_field->get_text() << "\n\n";

    // Save the document
    doc->save("field_switches_demo.docx");
    std::cout << "Saved: field_switches_demo.docx\n";

    return 0;
}
