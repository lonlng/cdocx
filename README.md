# CDocx

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)

C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files.

## Features

- **📄 Document Operations**: Read, write, and edit DOCX files with complete structure support
- **🔄 Template System**: Placeholder replacement with `{{key}}` pattern
- **📑 Document Insertion**: Merge documents at specific positions
- **🔧 XML Parts API**: Direct access to all DOCX internal components
- **🖼️ Media Management**: Add, delete, replace images in `word/media/`
- **🌳 Tree-Based Storage**: Internal tree structure mirrors ZIP organization
- **⚡ Modern C++17**: Iterator-based API with range-based for loop support

## Quick Start

### Prerequisites

- CMake 3.10+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git

### Build

```bash
git clone https://github.com/amiremohamadi/CDocx.git
cd CDocx
git submodule update --init --recursive

mkdir build && cd build
cmake ..
cmake --build .
ctest
```

### Example

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    // Read document
    cdocx::Document doc("file.docx");
    doc.open();
    
    for (auto& p : doc.paragraphs()) {
        for (auto& r : p.runs()) {
            std::cout << r.get_text() << std::endl;
        }
    }
    
    // Template replacement
    cdocx::Template tmpl(&doc);
    tmpl.set("name", "John Doe");
    tmpl.replace_all();
    
    doc.save("output.docx");
    return 0;
}
```

## Project Structure

```
cdocx/
├── include/
│   ├── cdocx.h              # Public API (simplified interface)
│   ├── constants.h          # Formatting flags
│   ├── cdocxIterator.h      # Iterator helpers
│   └── detail/
│       └── cdocx_impl.h     # Private implementation
├── src/
│   ├── cdocx_document.cpp   # Document class (PIMPL)
│   ├── cdocx_tree.cpp       # Tree structure implementation
│   ├── cdocx_content.cpp    # Content classes
│   └── cdocx_template.cpp   # Template and inserter
├── examples/                # Example programs
├── test/                    # Test suite
└── thirdparty/              # Dependencies (pugixml, zip)
```

**Key Design:** Tree-based internal structure completely hidden from public API using PIMPL pattern. All DOCX components (XML parts, media files, relationships) are loaded into memory and preserved on save.

## API Overview

```cpp
// Document operations
cdocx::Document doc("file.docx");
doc.open();
if (doc.is_open()) {
    // Process document
    doc.save();
}

// Paragraph iteration
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    for (auto r = p.runs(); r.has_next(); r.next()) {
        std::string text = r.get_text();
    }
}

// Template processing
cdocx::Template tmpl(&doc);
tmpl.set("key", "value");
tmpl.replace_all();

// Document insertion
cdocx::DocumentInserter inserter(&target);
inserter.insert_document(&source);

// XML Parts access
pugi::xml_document* styles = doc.get_styles();
pugi::xml_document* settings = doc.get_settings();

// Media management
doc.add_media("image.jpg");
doc.export_media("image.jpg", "output/path.jpg");
```

## Documentation

See [AGENTS.md](AGENTS.md) for complete API documentation, technical implementation details, build instructions, and examples.

## Dependencies

- [pugixml](https://github.com/zeux/pugixml) - XML parsing
- [zip](https://github.com/kuba--/zip) - ZIP archive handling

## License

MIT License - see [LICENSE](LICENSE) file.
