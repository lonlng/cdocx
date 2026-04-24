# CDocx

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)

**CDocx** is a C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. It provides a stable legacy iterator-based API and is transitioning toward a DOM-style architecture.

## Features

- **📄 Complete Document Operations**: Read, write, create DOCX files with full structure preservation
- **🏭 CDocx Factory**: Convenient factory methods for document creation (`create_document`, `load_document`, `save_document`)
- **🌳 DOM API**: Modern DOM-style architecture with `Node`/`CompositeNode` hierarchy for intuitive document manipulation
- **🔄 Template System**: Placeholder replacement with customizable patterns (`{{key}}`)
- **⚙️ TemplateEngine** (Recommended): Unified dictionary-style template API supporting text/image placeholders and bookmarks with format policies
- **🔍 Template Analyzer** (Python tool): Auto-detect placeholders, bookmarks, and MERGEFIELDs, generate ready-to-use C++ headers
- **📑 Document Insertion**: Merge documents at specific positions
- **🛠️ DocumentBuilder**: Fluent API for programmatic document construction with hyperlinks, images, tables, bookmarks, and fields
- **🔍 DocumentSearch**: Find, replace, and process text across the entire document with formatting support
- **📐 Section Support**: Page setup, margins, orientation, headers/footers with link-to-previous
- **📋 List/Numbering**: Bulleted, numbered, outline, and Chinese numbering lists
- **✏️ Text Formatting**: Run and paragraph formatting (bold, italic, color, alignment, spacing, shading, drop caps)
- **🔖 Bookmark Management**: Replace same-paragraph bookmarks with text or images; insert bookmarks around existing text
- **🖼️ Media Management**: Add, delete, replace, export images
- **📊 Table Operations**: Merge/split cells, insert/delete rows and columns, auto-fit behaviors
- **🎨 Style Collection**: Manage and apply paragraph/table styles
- **✉️ Mail Merge**: Simple field replacement with cleanup options
- **💬 Comments**: Add, get, and remove document comments
- **💧 Watermark**: Text and image watermarks in headers
- **🌳 XML Parts API**: Direct access to all DOCX internal components
- **⚡ Modern C++17**: Iterator-based API with range-based for loop support
- **✅ Cross-Platform**: Linux, Windows (MSVC/MinGW), macOS

## Quick Start

### Prerequisites

- CMake 3.14+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git

### Build

```bash
git clone https://github.com/lonlng/CDocx.git
cd CDocx
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTING=ON
cmake --build . --parallel
ctest --output-on-failure
```

### Example Usage

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    // Read existing document
    cdocx::Document doc("input.docx");
    doc.open();

    // Iterate through paragraphs (legacy API)
    for (auto& p : doc.paragraphs()) {
        for (auto& r : p.runs()) {
            std::cout << r.get_text() << std::endl;
        }
    }

    // Template replacement
    cdocx::Template tmpl(&doc);
    tmpl.set("name", "John Doe");
    tmpl.set("date", "2024-01-15");
    tmpl.replace_all();

    doc.save("output.docx");
    return 0;
}
```

### Creating a New Document (CDocx Factory)

```cpp
#include <cdocx.h>

int main() {
    // Create empty document using factory method
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    // Add formatted paragraph using DOM API
    auto para = body->append_paragraph("Hello, ");
    para->append_run("World!")
        ->get_font()
        .set_bold(true)
        .set_color(cdocx::Color::red());

    // Create a table
    auto table = body->append_table(3, 2);
    table->get_cell(0, 0)->set_text("Cell content");

    cdocx::CDocx::save_document(*doc, "output.docx");
    return 0;
}
```

### Template Engine (Recommended)

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc("template.docx");
    doc.open();

    // Dictionary-style template replacement
    cdocx::TemplateEngine engine(&doc);
    engine["company"] = cdocx::TemplateValue::text("Acme Inc.");
    engine["date"]    = "2024-01-15";
    engine["title"]   = cdocx::TemplateValue::text("Annual Report")
        .with_format(cdocx::TemplateFormat().bold().size(24));

    auto result = engine.apply();
    std::cout << "Replaced: " << result.success << " items\n";

    doc.save("output.docx");
    return 0;
}
```

**Auto-generate a ready-to-compile program** with the Python analyzer:

```bash
python tools/template_analyzer/analyze_template.py template.docx -o fill_template.cpp
```

Generated `fill_template.cpp` contains a complete `main()` with all template placeholders pre-filled — just edit the string values and compile.
```

### Using Sections

```cpp
#include <cdocx.h>

int main() {
    auto doc = cdocx::CDocx::create_document();
    auto section = doc->get_first_section();

    // Configure section
    section->get_properties().orientation = cdocx::SectionProperties::Orientation::Landscape;
    section->get_properties().page_size.width = 15840;
    section->get_properties().page_size.height = 12240;

    // Add content
    section->get_body()->append_paragraph("Landscape content")
        ->append_run("Bold text")
        ->get_font().bold = true;

    // Add header
    auto header = section->add_header(cdocx::HeaderFooterType::Primary);
    header->append_paragraph("Document Header");

    cdocx::CDocx::save_document(*doc, "output.docx");
    return 0;
}
```

### Using Lists

```cpp
#include <cdocx.h>

int main() {
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    // Create list definitions
    auto bullet = doc->add_bulleted_list_definition();

    // Add list items
    auto p1 = body->append_paragraph("First bullet item");
    p1->set_numbering(bullet, cdocx::NumberingLevel::Level1);

    auto p2 = body->append_paragraph("Second bullet item");
    p2->set_numbering(bullet, cdocx::NumberingLevel::Level1);

    // Nested item
    auto p3 = body->append_paragraph("Nested item");
    p3->set_numbering(bullet, cdocx::NumberingLevel::Level2);

    cdocx::CDocx::save_document(*doc, "output.docx");
    return 0;
}
```

### DocumentBuilder (Fluent API)

```cpp
#include <cdocx.h>
#include <cdocx/advanced.h>

int main() {
    auto doc = cdocx::CDocx::create_document();
    cdocx::DocumentBuilder builder(doc.get());

    builder.writeln("DocumentBuilder Demo");
    builder.clear_formatting();

    // Hyperlink
    builder.write("Visit ");
    builder.insert_hyperlink("CDocx Project", "https://github.com/lonlng/cdocx");
    builder.writeln(" for more information.");

    // Table
    builder.start_table();
    for (int row = 0; row < 3; ++row) {
        builder.insert_row();
        for (int col = 0; col < 3; ++col) {
            builder.insert_cell();
            builder.write("R" + std::to_string(row + 1) + "C" + std::to_string(col + 1));
        }
        builder.end_row();
    }
    builder.end_table();

    // Image
    builder.insert_image("logo.png", 200, 100);

    // Bookmark
    builder.start_bookmark("SUMMARY");
    builder.writeln("This is the summary section.");
    builder.end_bookmark("SUMMARY");

    cdocx::CDocx::save_document(*doc, "output.docx");
    return 0;
}
```

### Document Search and Replace

```cpp
#include <cdocx.h>
#include <cdocx/advanced.h>
#include <iostream>

int main() {
    cdocx::Document doc("input.docx");
    doc.open();

    // Find first occurrence
    auto range = cdocx::DocumentSearch::find(doc, "search term");
    if (range) {
        std::cout << "Found: " << range->get_text() << std::endl;
    }

    // Replace all occurrences
    int count = cdocx::DocumentSearch::replace_all(doc, "old", "new");
    std::cout << "Replaced " << count << " occurrence(s)" << std::endl;

    // Replace with formatting
    cdocx::DocumentSearch::replace_with_formatting(
        doc, "warning", "WARNING",
        static_cast<cdocx::FormattingFlag>(cdocx::kBold)
    );

    // Find and process with callback
    cdocx::DocumentSearch::find_and_process(doc, "TODO",
        [](const std::string& found_text, cdocx::Range& range) {
            std::cout << "Found task: " << range.get_text() << std::endl;
            return true; // continue searching
        }
    );

    doc.save("output.docx");
    return 0;
}
```

### Table Operations

```cpp
#include <cdocx.h>
#include <cdocx/advanced.h>

int main() {
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    // Create and populate table
    auto table = body->append_table(4, 3);
    table->get_cell(0, 0)->set_text("Name");
    table->get_cell(0, 1)->set_text("Age");
    table->get_cell(0, 2)->set_text("City");

    // Merge cells (title row)
    auto title = table->merge_cells(0, 0, 0, 2);
    title->set_text("Employee Information");

    // Insert/delete columns
    table->insert_column(1);
    table->delete_column(3);

    // Auto-fit
    table->auto_fit(cdocx::AutoFitBehavior::AutoFitToWindow);

    // Static helpers
    cdocx::TableOperations::set_cell_text(*table->get_cell(1, 0), "Alice");
    cdocx::TableOperations::append_row(*table);

    cdocx::CDocx::save_document(*doc, "output.docx");
    return 0;
}
```

### Using Color

```cpp
#include <cdocx.h>

int main() {
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    auto para = body->append_paragraph();
    auto* run = para->append_run("Red text");
    run->get_font().set_color(cdocx::Color(255, 0, 0));

    // Hex color
    auto* run2 = para->append_run(" Blue text");
    run2->get_font().set_color(cdocx::Color::from_hex("0000FF"));

    cdocx::CDocx::save_document(*doc, "output.docx");
    return 0;
}
```

## CMake Integration

```cmake
# Method 1: After installation
find_package(cdocx REQUIRED)
target_link_libraries(your_target PRIVATE cdocx::cdocx)

# Method 2: As subdirectory
add_subdirectory(path/to/cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)

# Method 3: FetchContent
include(FetchContent)
FetchContent_Declare(
    cdocx
    GIT_REPOSITORY https://github.com/lonlng/CDocx.git
    GIT_TAG v0.7.0
)
FetchContent_MakeAvailable(cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)
```

## Documentation

- **[AGENTS.md](AGENTS.md)** - Complete API documentation, architecture details, and development guide

## Project Structure

```
cdocx/
├── include/
│   ├── cdocx.h              # Main public API header
│   └── cdocx/               # Modular headers
│       ├── document.h       # Document class
│       ├── node.h           # Node hierarchy (DOM API)
│       ├── body.h           # Body class
│       ├── paragraph.h      # Paragraph, Run, Field, Hyperlink
│       ├── paragraph_builder.h # ParagraphBuilder fluent API
│       ├── base.h           # Run, legacy iterators
│       ├── table.h          # Table, Row, Cell
│       ├── table_builder.h  # TableBuilder fluent API
│       ├── section.h        # Section, HeaderFooter
│       ├── numbering.h      # List/Numbering
│       ├── template.h       # Template replacement (legacy FSM)
│       ├── template_engine.h # TemplateEngine (recommended)
│       ├── inserter.h       # Document insertion
│       ├── advanced.h       # DocumentBuilder, DocumentSearch, TableOperations
│       ├── document_builder.h # DocumentBuilder fluent API
│       ├── document_search.h # DocumentSearch find/replace
│       ├── bookmark.h       # Bookmark collection
│       ├── bookmark_replacer.h # Bookmark replacement
│       ├── bookmark_inserter.h # Bookmark insertion
│       ├── caption_generator.h # Caption generation
│       ├── comment.h        # Comment collection
│       ├── mail_merge.h     # Mail merge
│       ├── watermark.h      # Watermark
│       ├── style.h          # Style collection
│       ├── format.h         # Format attributes (Font, ParagraphFormat, etc.)
│       ├── properties.h     # Property structures
│       ├── enums.h          # Enumerations
│       ├── constants.h      # Constants
│       ├── convert_util.h   # Unit conversions
│       ├── control_char.h   # Control character constants
│       ├── file_format_util.h # File format detection
│       └── iterator.h       # Iterator support
├── src/                     # Implementation files
├── test/                    # Test suite (Google Test)
├── examples/                # Example programs
├── tools/                   # Developer tools
│   └── template_analyzer/   # Docx template analyzer (Python)
└── scripts/                 # Build scripts
```

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_SHARED_LIBS` | OFF | Build shared library |
| `BUILD_EXAMPLES` | ON | Build example programs |
| `BUILD_TESTING` | ON | Build test suite |
| `BUILD_DOCS` | OFF | Build documentation |
| `ENABLE_COVERAGE` | OFF | Enable code coverage |

## Supported Platforms

| Platform | Compiler | Status |
|----------|----------|--------|
| Linux | GCC 7+ | ✅ Fully Supported |
| Linux | Clang 5+ | ✅ Fully Supported |
| Windows | MSVC 2017+ | ✅ Fully Supported |
| Windows | MinGW-w64 | ✅ Supported |
| macOS | Xcode 10+ | ✅ Supported |

## Version History

- **v0.8.0** - `TemplateEngine` unified dictionary-style template API, `BookmarkInserter`, `CommentCollection`, `MailMerge`, `Watermark`, `StyleCollection`, table column insert/delete, auto-fit behaviors, field switches support
- **v0.7.0** - DOM architecture transition: `Node`/`CompositeNode` hierarchy, DOM-XML sync, `Color`, `DocumentBuilder` enhancements, `DocumentSearch`, `TableOperations`, `Range`, `ParagraphBuilder`, `TableBuilder`
- **v0.5.0** - Section support, List/Numbering system, `HeaderFooter` link-to-previous
- **v0.4.0** - Bookmark replacement (same-paragraph), Caption generation
- **v0.3.0** - Template system, Document insertion, XML Parts API
- **v0.2.0** - Media management, Cursor-based DocumentBuilder
- **v0.1.0** - Initial release with core document operations

## Dependencies

- [pugixml](https://github.com/zeux/pugixml) - XML parsing
- [zip](https://github.com/kuba--/zip) - ZIP archive handling
- [Google Test](https://github.com/google/googletest) - Testing framework (auto-fetched)

All dependencies are automatically fetched via CMake FetchContent.

## License

MIT License - see [LICENSE](LICENSE) file.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

---

*For complete technical documentation, see [AGENTS.md](AGENTS.md).*
