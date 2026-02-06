# CDocx - C++ DOCX Library

## Project Overview

CDocx is a C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. The library provides a simple, iterator-based API for document manipulation with support for text formatting, paragraphs, tables, template-based document generation, document insertion, and advanced XML parts access.

**Key Facts:**
- **Language**: C++17 (C99 for zip library component)
- **License**: MIT
- **Build System**: CMake (minimum version 3.10)
- **Namespace**: `cdocx`
- **Version**: 0.2.0
- **External Dependencies**: 
  - pugixml (Git submodule for XML parsing)
  - zip library (bundled from kuba--/zip for archive handling)
- **Test Framework**: doctest (header-only)

## Quick Start

### Prerequisites

- CMake 3.10+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Git (for submodules)

### Build Instructions

```bash
# Clone and initialize
git clone https://github.com/amiremohamadi/CDocx.git
cd CDocx
git submodule update --init --recursive

# Build
mkdir build && cd build
cmake ..
cmake --build .

# Run tests
ctest
```

## Architecture

### Core Components

#### 1. Document Class (`cdocx::Document`)
- Entry point for all DOCX operations
- **Complete Structure Support**: Loads entire DOCX package into memory including all XML parts, media files, and relationships
- **Tree-Based Storage**: Internal tree structure mirrors ZIP file organization
- Handles file I/O and ZIP archive management using zip library
- Provides access to paragraphs and tables
- Manages XML document structure using pugixml
- **Advanced Feature**: XML Parts API for accessing all document components
- **Media Management**: Complete in-memory media management - add, delete, replace, list images in `word/media/`
- **Relationship Management**: Full support for `_rels/*.rels` files

#### 2. Paragraph Class (`cdocx::Paragraph`)
- Represents document paragraphs
- Contains runs (text segments with formatting)
- Supports insertion and text manipulation
- Iterator-based traversal with `has_next()` and `next()` methods
- Compatible with C++11 range-based for loops via iterator system

#### 3. Run Class (`cdocx::Run`)
- Represents formatted text segments
- Supports various formatting flags (bold, italic, underline, etc.)
- Text manipulation with `get_text()` and `set_text()` methods

#### 4. Table Classes (`cdocx::Table`, `cdocx::TableRow`, `cdocx::TableCell`)
- Full table manipulation support
- Row and cell iteration
- Hierarchical structure: Table → Row → Cell → Paragraph

#### 5. Template Class (`cdocx::Template`)
- Template-based document generation
- Placeholder replacement with custom patterns (default: `{{` and `}}`)
- Supports text and image placeholders
- FSM-based (Finite State Machine) placeholder processing

#### 6. DocumentInserter Class (`cdocx::DocumentInserter`)
- Insert content from one document into another
- Position-based insertion (beginning, specific location, end)
- Support for paragraphs only, tables only, or complete documents

### File Organization

```
cdocx/
├── include/
│   ├── cdocx.h                 # Public API header (simplified interface)
│   ├── constants.h             # Formatting flags
│   ├── cdocxIterator.h         # Iterator helpers
│   └── detail/
│       └── cdocx_impl.h        # Private implementation (internal use)
├── src/
│   ├── cdocx_document.cpp      # Document class main implementation (PIMPL)
│   ├── cdocx_impl.cpp          # DocumentImpl implementation
│   ├── cdocx_tree.cpp          # Tree structure (DocxTree, DocxTreeNode)
│   ├── cdocx_content.cpp       # Content classes (Run, Paragraph, Table)
│   └── cdocx_template.cpp      # Template and DocumentInserter
├── examples/                # Example programs
│   ├── sample1.cpp
│   ├── sample2.cpp
│   ├── sample3.cpp
│   ├── advanced_template_example.cpp
│   ├── simple_insert_example.cpp
│   ├── image_management_demo.cpp
│   └── 45_xml_parts_api.cpp
├── test/                    # Test suite
│   ├── basic_tests.cpp
│   ├── iterator_tests.cpp
│   ├── advanced_features_test.cpp
│   └── xml_parts_tests.cpp
├── thirdparty/
│   ├── pugixml/             # XML parsing (Git submodule)
│   └── zip/                 # ZIP handling
├── CMakeLists.txt
└── README.md
```

## Technical Implementation

### Internal Tree Structure

CDocx uses a tree-based internal structure to represent the DOCX package:

```cpp
// Internal node types (in detail/cdocx_impl.h)
enum class DocxNodeType {
    Root,       // Root node (represents the package)
    Directory,  // Directory/folder
    XmlFile,    // XML file (parsed into pugi::xml_document)
    MediaFile,  // Media file (binary data)
    BinaryFile  // Other binary files
};

// Tree node structure
struct DocxTreeNode {
    std::string name;                           // File/directory name
    std::string full_path;                      // Full path in ZIP
    DocxNodeType type;                          // Node type
    std::shared_ptr<pugi::xml_document> xml_doc;     // For XmlFile
    std::vector<uint8_t> binary_data;                // For Media/Binary
    std::string content_type;                        // MIME type
    bool is_modified = false;
    bool is_new = false;
    bool is_deleted = false;
};
```

**Implementation Details:**
- Tree structure is **completely hidden** from public API (in `detail/cdocx_impl.h`)
- Uses PIMPL pattern: `Document` class contains `std::unique_ptr<DocumentImpl> impl_`
- Path mapping provides O(1) lookup performance
- Supports iteration, search, and filter operations

### DOCX Package Structure

A DOCX file is a ZIP archive containing:

```
document.docx
├── [Content_Types].xml          # Content type definitions
├── _rels/
│   └── .rels                    # Package relationships
├── docProps/
│   ├── app.xml                  # Extended properties
│   ├── core.xml                 # Core properties (title, author, etc.)
│   └── custom.xml               # Custom properties
├── word/
│   ├── _rels/
│   │   └── document.xml.rels    # Document relationships
│   ├── document.xml             # Main document content
│   ├── styles.xml               # Style definitions
│   ├── settings.xml             # Document settings
│   ├── fontTable.xml            # Font table
│   ├── numbering.xml            # Numbering definitions
│   ├── footnotes.xml            # Footnotes
│   ├── endnotes.xml             # Endnotes
│   ├── footer1.xml              # Footer (can be multiple)
│   ├── header1.xml              # Header (can be multiple)
│   ├── theme/
│   │   └── theme1.xml           # Theme definitions
│   └── media/                   # Images and other media
│       ├── image1.png
│       ├── image2.jpg
│       └── ...
└── customXml/                   # Custom XML data
```

### Loading Process

1. **Open ZIP file**: Use zip library to open the DOCX file
2. **Iterate entries**: For each entry in the ZIP:
   - XML files (`.xml`, `.rels`): Parse into tree nodes
   - Media files (`word/media/*`): Store binary data
   - Other files: Store as binary entries
3. **Parse relationships**: Load all `_rels/*.rels` files
4. **Load content types**: Parse `[Content_Types].xml`

### Saving Process

1. **Update relationships**: Serialize modified relationship files
2. **Update content types**: Ensure `[Content_Types].xml` is current
3. **Traverse tree**: Write all non-deleted nodes to ZIP
4. **Atomic replace**: Replace original file with temp file

## API Reference

### Document Operations

```cpp
// Construction and file operations
cdocx::Document doc("file.docx");     // Create document object
doc.open();                           // Open the document (void return)
doc.save();                           // Save changes
doc.save("new_name.docx");            // Save with new name
bool open = doc.is_open();            // Check if document is open

// Access content
Paragraph& paragraphs();              // Get paragraphs iterator
Table& tables();                      // Get tables iterator
```

### Paragraph Operations

```cpp
// Iterate paragraphs
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    // Process paragraph
}

// Modern C++11 range-based for loop
for (auto& p : doc.paragraphs()) {
    for (auto& r : p.runs()) {
        std::cout << r.get_text() << std::endl;
    }
}

// Insert and modify
Paragraph& insert_paragraph_after(const std::string& text, 
                                   formatting_flag flag = none);
Run& add_run(const std::string& text, formatting_flag flag = none);
```

### Text Formatting Flags

```cpp
namespace cdocx {
    formatting_flag none = 0;
    formatting_flag bold = 1 << 0;
    formatting_flag italic = 1 << 1;
    formatting_flag underline = 1 << 2;
    formatting_flag strikethrough = 1 << 3;
    formatting_flag superscript = 1 << 4;
    formatting_flag subscript = 1 << 5;
    formatting_flag smallcaps = 1 << 6;
    formatting_flag shadow = 1 << 7;
}

// Combine flags with bitwise OR
p.add_run("bold italic", cdocx::bold | cdocx::italic);
```

### Template Replacement

```cpp
// Basic usage
cdocx::Template tmpl(&doc);
tmpl.set("name", "John Doe");
tmpl.set("date", "2024-01-15");
tmpl.replace_all();

// Custom pattern
cdocx::Template tmpl(&doc, "<%", "%>");  // Use <%key%> pattern

// Image placeholders
tmpl.set_image("logo", "path/to/logo.png");
```

### Document Insertion

```cpp
// Insert entire document
cdocx::DocumentInserter inserter(&target_doc);
inserter.insert_document(&source_doc);

// Insert after specific paragraph
inserter.insert_document_after(&source_doc, paragraph);

// Insert at specific position
inserter.insert_document_at(&source_doc, 2);  // After 2nd block

// Insert only paragraphs or tables
inserter.insert_paragraphs(&source_doc, position);
inserter.insert_tables(&source_doc, position);
```

### XML Parts API

```cpp
// Access any XML part
pugi::xml_document* part = doc.get_xml_part("word/styles.xml");
const pugi::xml_document* part_const = doc.get_xml_part("word/styles.xml");

// Create or replace XML part
pugi::xml_document& new_part = doc.create_xml_part("word/custom.xml");

// Remove XML part
doc.remove_xml_part("word/custom.xml");

// Mark part as modified (for incremental save)
doc.mark_modified("word/document.xml");

// List all loaded parts
std::vector<std::string> names = doc.get_all_part_names();
size_t count = doc.get_part_count();

// Check if part exists
bool exists = doc.has_xml_part("word/numbering.xml");

// Convenience methods for common parts
pugi::xml_document* doc_xml = doc.get_document_xml();
pugi::xml_document* core = doc.get_core_properties();
pugi::xml_document* app = doc.get_app_properties();
pugi::xml_document* types = doc.get_content_types();
pugi::xml_document* styles = doc.get_styles();
pugi::xml_document* settings = doc.get_settings();
pugi::xml_document* font_table = doc.get_font_table();
pugi::xml_document* numbering = doc.get_numbering();
pugi::xml_document* footnotes = doc.get_footnotes();
pugi::xml_document* endnotes = doc.get_endnotes();
pugi::xml_document* doc_rels = doc.get_document_rels();
pugi::xml_document* pkg_rels = doc.get_package_rels();

// Header/Footer access
pugi::xml_document* footer1 = doc.get_footer(1);
pugi::xml_document* header1 = doc.get_header(1);
std::vector<std::string> footer_names = doc.get_footer_names();
std::vector<std::string> header_names = doc.get_header_names();
```

### Media Management

Complete in-memory media management:

```cpp
// Add media from file
doc.add_media("path/to/image.jpg");  // Auto-detect name
doc.add_media("path/to/image.jpg", "custom_name.jpg");

// Add media from memory
std::vector<uint8_t> image_data = ...;
doc.add_media_from_memory("image.png", image_data, "image/png");

// Delete media
doc.delete_media("image_name.jpg");

// Replace media
doc.replace_media("old.jpg", "path/to/new.jpg");
doc.replace_media_from_memory("old.jpg", new_data, "image/png");

// List all media
std::vector<std::string> media = doc.list_media();

// Check if media exists
bool exists = doc.has_media("image.jpg");

// Export media from DOCX
doc.export_media("image.jpg", "output/path.jpg");

// Get media data from memory
std::vector<uint8_t> data = doc.get_media_data("image.jpg");

// Add media with automatic relationship creation
std::string rel_id = doc.add_media_with_rel("path/to/image.jpg");
std::string rel_id2 = doc.add_media_from_memory_with_rel("image.png", data);

// Batch operations
doc.add_media_batch({{"path1.jpg", "name1.jpg"}, {"path2.jpg", "name2.jpg"}});
doc.delete_media_batch({"name1.jpg", "name2.jpg"});

// Utilities
std::string unique_name = doc.generate_unique_image_name("image.png");
std::string rel_id = doc.get_media_relationship_id("image.jpg");
bool valid = doc.validate_image_format("image.jpg");
```

### Relationship Management

```cpp
// Get relationships from a rels file
std::vector<cdocx::Relationship> rels = doc.get_relationships("word/_rels/document.xml.rels");

// Add relationship
std::string new_id = doc.add_relationship("word/_rels/document.xml.rels", 
    "http://schemas.../image", "media/image1.png");

// Remove relationship
doc.remove_relationship("word/_rels/document.xml.rels", "rId5");

// Find relationship ID
std::string rel_id = doc.find_relationship_id("word/_rels/document.xml.rels", "media/image1.png");

// Image relationship helpers
std::string img_rel = doc.add_image_relationship("image1.png");
doc.remove_image_relationship("image1.png");
```

## Build System

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_SHARED_LIBS` | OFF | Build shared library |
| `BUILD_SAMPLES` | ON | Build sample programs |
| `BUILD_TESTING` | ON | Build test suite |
| `ENABLE_ADVANCED_FEATURES` | ON | Enable advanced features |

### CMake Integration

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
    GIT_REPOSITORY https://github.com/amiremohamadi/CDocx.git
    GIT_TAG v0.2.0
)
FetchContent_MakeAvailable(cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)
```

## Usage Examples

### Complete Structure Support

The Document class loads the entire DOCX package into memory:

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("template.docx");
    doc.open();
    
    // All XML parts are loaded into memory
    auto parts = doc.get_all_part_names();
    std::cout << "Loaded " << parts.size() << " XML parts" << std::endl;
    // Output: Loaded 20 XML parts
    
    // All media files are loaded into memory
    auto media = doc.list_media();
    std::cout << "Loaded " << media.size() << " media files" << std::endl;
    // Output: Loaded 17 media files
    
    // Access any part
    pugi::xml_document* styles = doc.get_styles();
    pugi::xml_document* settings = doc.get_settings();
    
    // Get media data directly from memory
    std::vector<uint8_t> image_data = doc.get_media_data("image1.png");
    
    // Modify any XML part
    doc.mark_modified("word/styles.xml");
    
    // Save entire structure back to DOCX
    doc.save("output.docx");
    // All XML parts, media files, and relationships are preserved
    
    return 0;
}
```

### Reading a Document

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc("file.docx");
    doc.open();
    
    // Traditional iterator
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        for (auto r = p.runs(); r.has_next(); r.next()) {
            std::cout << r.get_text() << std::endl;
        }
    }
    
    return 0;
}
```

### Creating a Document

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("output.docx");
    doc.open();
    
    // Insert paragraph with formatting
    cdocx::Paragraph p = doc.paragraphs().insert_paragraph_after("Hello ");
    p.add_run("World", cdocx::bold);
    p.add_run("!", cdocx::italic | cdocx::underline);
    
    doc.save();
    return 0;
}
```

### Template Processing

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return 1;
    }
    
    cdocx::Template tmpl(&doc);
    tmpl.set("name", "John Doe");
    tmpl.set("department", "Engineering");
    tmpl.replace_all();
    
    doc.save("output.docx");
    return 0;
}
```

### Document Insertion

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document target("main.docx");
    target.open();
    
    cdocx::Document source("content.docx");
    source.open();
    
    cdocx::DocumentInserter inserter(&target);
    inserter.insert_document(&source);
    
    target.save("combined.docx");
    return 0;
}
```

## Testing

```bash
# Run all tests
ctest

# Run with verbose output
ctest -V

# Run specific categories
ctest -L core       # Core functionality tests
ctest -L template   # Template system tests

# Using CMake targets
cmake --build . --target test_all
```

## Code Style

### Naming Conventions

| Element | Convention | Examples |
|---------|------------|----------|
| Classes | PascalCase | `Document`, `Paragraph`, `Template` |
| Methods | snake_case | `get_text()`, `set_text()`, `replace_all()` |
| Constants | snake_case | `bold`, `italic`, `underline` |
| Namespace | lowercase | `cdocx` |

### Formatting

- **Tool**: clang-format with LLVM base style
- **Indent**: 4 spaces
- **Command**: `clang-format -i src/*.cpp include/*.h`

## Contributing

### Pull Request Process

1. Discuss changes via issue or email before starting
2. Make focused PRs that handle one specific topic
3. Follow existing code style (run clang-format)
4. Add tests for new functionality
5. Update documentation if needed

### Code of Conduct

- Use welcoming and inclusive language
- Be respectful of differing viewpoints
- Gracefully accept constructive criticism
- Focus on what is best for the community

## Troubleshooting

### Common Issues

**"pugixml.hpp not found"**
- Solution: Run `git submodule update --init --recursive`

**CMake errors**
- Ensure CMake 3.10+
- Check that submodules are initialized

**Build fails**
- Ensure C++17 compatible compiler
- Check that all dependencies are available

### Important Notes

1. `Document::open()` returns `void`, not `bool`. Use `is_open()` to check status.
2. Media management methods use `*_media` naming (e.g., `add_media`, `list_media`).
3. Always check `is_open()` before operations:
   ```cpp
   doc.open();
   if (!doc.is_open()) {
       // Handle error
   }
   ```

## License

MIT License - see LICENSE file for details.
