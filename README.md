# CDocx

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)

**CDocx** is a C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. It provides a stable legacy iterator-based API and is transitioning toward a DOM-style architecture.

## Features

- **📄 Complete Document Operations**: Read, write, create DOCX files with full structure preservation
- **🔄 Template System**: Placeholder replacement with customizable patterns (`{{key}}`)
- **📑 Document Insertion**: Merge documents at specific positions
- **📐 Section Support**: Page setup, margins, orientation
- **📋 List/Numbering**: Bulleted, numbered, and Chinese numbering lists
- **✏️ Text Formatting**: Run and paragraph formatting (bold, italic, color, alignment, spacing)
- **🔖 Bookmark Management**: Replace same-paragraph bookmarks with text or images
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

### Using Sections

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // Configure section
    Section* section = doc.get_first_section();
    section->properties().orientation = SectionProperties::Orientation::Landscape;
    section->properties().pageSize.width = 15840;
    section->properties().pageSize.height = 12240;
    
    // Add content
    section->add_paragraph("Landscape content", cdocx::bold);
    
    doc.save();
    return 0;
}
```

### Using Lists

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // Create list definitions
    NumberingId bullet = doc.add_bulleted_list_definition();
    
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

### Using Color

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    auto& para = doc.paragraphs();
    auto* run = para.add_run("Red text");
    run->set_color(cdocx::Color(255, 0, 0));
    
    // Hex color
    auto* run2 = para.add_run(" Blue text");
    run2->set_color(cdocx::Color::from_hex("0000FF"));
    
    doc.save();
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
│       ├── node.h           # Node hierarchy (in transition)
│       ├── body.h           # Body class
│       ├── paragraph.h      # Paragraph class
│       ├── base.h           # Run, legacy iterators
│       ├── table.h          # Table, Row, Cell
│       ├── section.h        # Section support
│       ├── numbering.h      # List/Numbering
│       ├── template.h       # Template replacement
│       ├── inserter.h       # Document insertion
│       ├── advanced.h       # Bookmark, Builder, Search
│       ├── bookmark_replacer.h # Bookmark replacement
│       ├── caption_generator.h # Caption generation
│       ├── format.h         # Format attributes
│       ├── properties.h     # Property structures
│       ├── enums.h          # Enumerations
│       ├── constants.h      # Constants
│       └── iterator.h       # Iterator support
├── src/                     # Implementation files
├── test/                    # Test suite (Google Test)
├── examples/                # Example programs
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

- **v0.7.0** - DOM architecture transition (in progress): `Node`/`CompositeNode` hierarchy introduced, basic DOM-XML sync, `Color` implementation
- **v0.5.0** - Section support, List/Numbering system
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
