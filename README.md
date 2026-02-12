# CDocx

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)

**CDocx** is a modern C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. It provides a clean, iterator-based API with comprehensive document manipulation capabilities.

## Features

- **📄 Complete Document Operations**: Read, write, create DOCX files with full structure preservation
- **🔄 Template System**: Placeholder replacement with customizable patterns (`{{key}}`)
- **📑 Document Insertion**: Merge documents at specific positions
- **📐 Section Support**: Page setup, margins, orientation (v0.5.0+)
- **📋 List/Numbering**: Bulleted, numbered, and Chinese numbering lists (v0.5.0+)
- **🧩 Node Hierarchy**: Unified document model with Visitor pattern (v0.6.0+)
- **🎨 Rich Formatting**: Paragraph and character formatting with colors, borders, shading (v0.6.0+)
- **🔖 Bookmark Management**: Replace bookmarks with text or images
- **🖼️ Media Management**: Add, delete, replace images
- **🌳 XML Parts API**: Direct access to all DOCX internal components
- **⚡ Modern C++17**: Iterator-based API with range-based for loop support
- **✅ Cross-Platform**: Linux, Windows (MSVC/MinGW), macOS

## Quick Start

### Prerequisites

- CMake 3.14+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git

### Build

**Linux/macOS:**
```bash
git clone https://github.com/lonlng/CDocx.git
cd CDocx
./scripts/build-linux.sh Release
```

**Windows:**
```cmd
git clone https://github.com/lonlng/CDocx.git
cd CDocx
scripts\build-windows.bat Release x64
```

### Example Usage

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    // Read existing document
    cdocx::Document doc("input.docx");
    doc.open();
    
    // Iterate through paragraphs
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

### Creating a New Document

```cpp
#include <cdocx.h>

int main() {
    // Create empty document
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // Add formatted paragraph
    auto& para = doc.paragraphs();
    para.add_run("Hello, ", cdocx::bold);
    para.add_run("World!", cdocx::italic | cdocx::underline);
    
    // Create a table
    auto* table = doc.tables().add(3, 2);
    auto* cell = table->rows().first()->cells().first();
    cell->paragraphs().add_run("Cell content");
    
    doc.save();
    return 0;
}
```

### Using Sections (v0.5.0+)

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // Configure section
    Section* section = doc.get_first_section();
    section->properties().orientation = SectionProperties::Orientation::Landscape;
    section->properties().pageSize.width = 15840;   // A4 landscape width
    section->properties().pageSize.height = 12240;
    
    // Add content to section
    section->add_paragraph("Landscape content", cdocx::bold);
    
    doc.save();
    return 0;
}
```

### Using Lists (v0.5.0+)

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // Create list definitions
    NumberingId bullet = doc.add_bulleted_list_definition();
    NumberingId number = doc.add_numbered_list_definition(NumberStyle::Decimal);
    
    // Add list items
    auto& p1 = doc.paragraphs();
    p1.add_run("First bullet item");
    p1.set_numbering(bullet, 0);
    
    auto& p2 = doc.paragraphs();
    p2.add_run("Second bullet item");
    p2.set_numbering(bullet, 0);
    
    doc.save();
    return 0;
}
```

### Using Format Attributes (v0.6.0+)

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // Configure paragraph format
    ParagraphFormat format;
    format.set_alignment(ParagraphAlignment::Center);
    format.set_line_spacing(360, LineSpacingRule::Auto);  // 1.5x spacing
    format.set_space_before(12);      // 12 points before
    format.set_first_line_indent(24); // 24 points indent
    
    // Set border and shading
    Border border(BorderType::Single, Color(0, 0, 0), 4);
    format.borders().set_all(border);
    format.shading().set_solid_fill(Color(240, 240, 240));
    
    // Apply to paragraph
    auto& para = doc.paragraphs();
    para.set_format(format);
    
    // Configure font
    Font font;
    font.set_name("Arial");
    font.set_size(14);
    font.set_bold(true);
    font.set_color(Color(255, 0, 0));
    
    auto* run = para.add_run("Formatted text");
    run->set_font(font);
    
    doc.save();
    return 0;
}
```

### Using Visitor Pattern (v0.6.0+)

```cpp
#include <cdocx.h>
#include <iostream>

class TextExtractor : public cdocx::DocumentVisitor {
public:
    VisitorAction visit_run(cdocx::Run& run) override {
        std::cout << run.get_text();
        return VisitorAction::Continue;
    }
    
    VisitorAction visit_paragraph_end(cdocx::Paragraph&) override {
        std::cout << std::endl;
        return VisitorAction::Continue;
    }
};

int main() {
    cdocx::Document doc("input.docx");
    doc.open();
    
    TextExtractor extractor;
    doc.accept(&extractor);
    
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
    GIT_TAG v0.6.0
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
│       ├── base.h           # Paragraph, Run, Table
│       ├── template.h       # Template replacement
│       ├── section.h        # Section support (v0.5.0+)
│       ├── numbering.h      # List/Numbering (v0.5.0+)
│       ├── node.h           # Node hierarchy (v0.6.0+)
│       └── format.h         # Format attributes (v0.6.0+)
├── src/                     # Implementation files
├── test/                    # Test suite (Google Test)
├── examples/                # Example programs (14 examples)
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

- **v0.6.0** - Node hierarchy with Visitor pattern, Format attributes (Font, Color, Border, etc.)
- **v0.5.0** - Section support, List/Numbering system
- **v0.4.0** - Bookmark replacement, Caption generation
- **v0.3.0** - Template system, Document insertion, XML Parts API
- **v0.2.0** - Media management, DocumentBuilder, Search/Replace
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
