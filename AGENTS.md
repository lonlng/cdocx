# CDocx - C++ DOCX Library

## Project Overview

CDocx is a modern C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. It provides an iterator-based API with comprehensive document manipulation capabilities.

**Key Facts:**
- **Language**: C++17 (C99 for zip library component)
- **License**: MIT
- **Build System**: CMake (minimum version 3.14)
- **Namespace**: `cdocx`
- **Version**: 0.6.0
- **Dependencies** (auto-fetched via CMake FetchContent):
  - [pugixml](https://gitee.com/lonlng/pugixml) (v1.15) - XML parsing
  - [zip](https://gitee.com/lonlng/zip) (v0.3.6) - ZIP archive handling
  - [Google Test](https://gitee.com/lonlng/googletest) (v1.17.0) - Testing framework

---

## Project Structure

```
cdocx/
├── CMakeLists.txt              # Main CMake configuration
├── .clang-format               # Code formatting rules (LLVM style, 4-space indent)
├── .clang-tidy                 # Static analysis configuration
├── README.md                   # User-facing documentation
├── AGENTS.md                   # This file - complete technical reference
├── LICENSE                     # MIT License
├── CONTRIBUTING.md             # Contribution guidelines
├── SECURITY.md                 # Security policy
│
├── cmake/
│   └── modules/
│       └── CDocxHelpers.cmake  # CMake helper functions
│
├── include/                    # Public API headers
│   ├── cdocx.h                 # Main aggregated header
│   └── cdocx/                  # Modular headers
│       ├── fwd.h               # Forward declarations
│       ├── constants.h         # Formatting flags
│       ├── iterator.h          # Iterator helpers
│       ├── base.h              # Run, Paragraph, Table classes
│       ├── document.h          # Document class
│       ├── template.h          # Template replacement
│       ├── inserter.h          # Document insertion
│       ├── advanced.h          # Bookmark, DocumentBuilder, Search
│       ├── bookmark_replacer.h # Bookmark replacement API
│       ├── caption_generator.h # Figure caption generation
│       ├── format_context.h    # Text formatting context
│       ├── properties.h        # Property structures
│       ├── section.h           # Section support (v0.5.0)
│       ├── numbering.h         # List/Numbering system (v0.5.0)
│       ├── node.h              # Node hierarchy (v0.6.0)
│       └── format.h            # Format attributes (v0.6.0)
│
├── src/                        # Implementation files
│   ├── base_content.cpp
│   ├── document.cpp
│   ├── template.cpp
│   ├── inserter.cpp
│   ├── tree.cpp
│   ├── impl.cpp
│   ├── advanced.cpp
│   ├── bookmark_replacer.cpp
│   ├── caption_generator.cpp
│   ├── format_context.cpp
│   ├── properties.cpp
│   ├── section.cpp
│   ├── numbering.cpp
│   ├── node.cpp                # Node implementation (v0.6.0)
│   └── format.cpp              # Format implementation (v0.6.0)
│
├── include/detail/
│   └── impl.h                  # Private implementation (PIMPL)
│
├── test/                       # Test suite (Google Test)
│   ├── 01_basic/               # Basic functionality tests
│   ├── 02_iterator/            # Iterator tests
│   ├── 03_template/            # Template tests
│   ├── 04_xml_parts/           # XML Parts API tests
│   ├── 05_complete_structure/  # Complete structure tests
│   ├── 06_create_empty/        # Empty document creation
│   ├── 07_text_formatting/     # Text formatting tests
│   ├── 08_bookmark_replacement/# Bookmark replacement tests
│   └── 09_section_and_list/    # Section and list tests
│
├── examples/                   # Example programs (14 examples)
│   ├── 01_basic_read/
│   ├── 02_basic_create/
│   ├── 03_template_basic/
│   ├── 04_template_advanced/
│   ├── 05_document_insert/
│   ├── 06_xml_parts/
│   ├── 07_media_management/
│   ├── 08_create_empty/
│   ├── 09_text_formatting/
│   ├── 10_advanced_crud/
│   ├── 11_bookmark_replacement/
│   ├── 12_caption_generation/
│   ├── 13_section_and_list/
│   └── 14_node_hierarchy/      # v0.6.0 example
│
└── scripts/                    # Build scripts
    ├── build-linux.sh
    ├── build-windows.bat
    └── code-quality.sh
```

---

## Architecture

### Core Design Principles

1. **Complete Structure Support**: Loads entire DOCX package into memory including all XML parts, media files, and relationships
2. **Tree-Based Storage**: Internal tree structure mirrors ZIP file organization with O(1) path lookup
3. **PIMPL Pattern**: Implementation details hidden to ensure ABI stability
4. **Iterator-Based API**: Modern C++17 iterator pattern supporting range-based for loops
5. **Zero External Dependencies**: All dependencies fetched automatically via CMake FetchContent

### Internal Tree Structure

```cpp
// Internal node types (in detail/impl.h)
enum class DocxNodeType {
    Root,       // Root node (represents the package)
    Directory,  // Directory/folder
    XmlFile,    // XML file (parsed into pugi::xml_document)
    MediaFile,  // Media file (binary data)
    BinaryFile  // Other binary files
};

// Tree node structure
struct DocxTreeNode {
    std::string name;
    std::string full_path;
    DocxNodeType type;
    std::shared_ptr<pugi::xml_document> xml_doc;
    FileDataStorage file_storage;
    std::string content_type;
    bool is_modified = false;
    bool is_new = false;
    bool is_deleted = false;
};
```

### DOCX Package Structure

```
document.docx
├── [Content_Types].xml          # Content type definitions
├── _rels/.rels                  # Package relationships
├── docProps/
│   ├── app.xml                  # Extended properties
│   ├── core.xml                 # Core properties
│   └── custom.xml               # Custom properties
└── word/
    ├── _rels/document.xml.rels  # Document relationships
    ├── document.xml             # Main document content
    ├── styles.xml               # Style definitions
    ├── settings.xml             # Document settings
    ├── fontTable.xml            # Font table
    ├── numbering.xml            # Numbering definitions
    ├── footnotes.xml            # Footnotes
    ├── endnotes.xml             # Endnotes
    ├── footer1.xml              # Footer (multiple)
    ├── header1.xml              # Header (multiple)
    ├── theme/theme1.xml         # Theme definitions
    └── media/                   # Images and media
```

---

## Core Components

### 1. Document Class (`cdocx::Document`)
Entry point for all DOCX operations with complete structure support.

```cpp
// Construction and file operations
cdocx::Document doc("file.docx");
doc.open();                           // Open the document
doc.save();                           // Save changes
doc.save("new_name.docx");            // Save with new name
bool is_open = doc.is_open();         // Check status

// Access content
auto& paragraphs = doc.paragraphs();  // Get paragraphs iterator
auto& tables = doc.tables();          // Get tables iterator

// Section support (v0.5.0)
Section* section = doc.add_section();
Section* first = doc.get_first_section();
auto sections = doc.sections();

// List/Numbering (v0.5.0)
NumberingId bullet = doc.add_bulleted_list_definition();
NumberingId number = doc.add_numbered_list_definition(NumberStyle::Decimal);
NumberingId chinese = doc.add_chinese_numbered_list_definition();

// XML Parts API
pugi::xml_document* styles = doc.get_styles();
pugi::xml_document* numbering = doc.get_numbering();
pugi::xml_document* header1 = doc.get_header(1);
pugi::xml_document* footer1 = doc.get_footer(1);

// Media management
doc.add_media("image.jpg");
auto media = doc.list_media();
doc.export_media("image.jpg", "output/path.jpg");
```

### 2. Paragraph Class (`cdocx::Paragraph`)
Represents document paragraphs with run-based text storage.

```cpp
// Text manipulation
std::string text = para.get_text();

// Add formatted runs
Run* run = para.add_run("Hello", cdocx::bold | cdocx::italic);

// List support (v0.5.0)
para.set_numbering(bullet_list_id, 0);  // Level 0
para.remove_numbering();

// Iteration
for (auto& r : para.runs()) {
    std::cout << r.get_text() << std::endl;
}
```

### 3. Run Class (`cdocx::Run`)
Represents formatted text segments.

```cpp
// Text access
std::string text = run.get_text();
run.set_text("new text");

// Formatting flags supported:
// bold, italic, underline, strikethrough, 
// superscript, subscript, smallcaps, shadow
```

### 4. Table Classes (`cdocx::Table`, `cdocx::TableRow`, `cdocx::TableCell`)
Full table manipulation with hierarchical structure.

```cpp
// Hierarchical: Table → Row → Cell → Paragraph
for (auto& row : table.rows()) {
    for (auto& cell : row.cells()) {
        for (auto& p : cell.paragraphs()) {
            // Process cell content
        }
    }
}
```

### 5. Section Class (`cdocx::Section`) (v0.5.0)
Document section management with page setup.

```cpp
// Section properties
SectionProperties prop;
prop.orientation = SectionProperties::Orientation::Landscape;
prop.pageSize.width = 15840;    // twips
prop.pageSize.height = 12240;
prop.pageMargins.top = 1440;    // 1 inch
prop.pageMargins.bottom = 1440;
prop.pageMargins.left = 1440;
prop.pageMargins.right = 1440;

// Add content
Section* sect = doc.get_first_section();
Paragraph* para = sect->add_paragraph("Text", cdocx::bold);
Table* table = sect->add_table(3, 4);
```

### 6. Node Hierarchy (v0.6.0)
Unified node base class with visitor pattern support.

```cpp
// Node types
enum class NodeType {
    Document, Section, Body, HeaderFooter,
    Paragraph, Table, TableRow, TableCell,
    Run, BookmarkStart, BookmarkEnd,
    FieldStart, FieldSeparator, FieldEnd,
    Shape, Comment, Footnote, Endnote
};

// Base Node class
class Node : public std::enable_shared_from_this<Node> {
public:
    virtual NodeType node_type() const = 0;
    virtual bool is_composite() const = 0;
    virtual VisitorAction accept(DocumentVisitor* visitor) = 0;
    
    // Navigation
    CompositeNode* parent_node() const;
    Node* previous_sibling() const;
    Node* next_sibling() const;
    
    // Content
    virtual std::string get_text() const = 0;
    virtual std::shared_ptr<Node> clone(bool deep = true) const = 0;
};

// Visitor pattern
class DocumentVisitor {
public:
    virtual VisitorAction visit_document_start(Document& doc);
    virtual VisitorAction visit_paragraph_start(Paragraph& para);
    virtual VisitorAction visit_run(Run& run);
    // ... more visit methods
};
```

### 7. Format Attributes (v0.6.0)
Comprehensive formatting system.

```cpp
// Color
Color red(255, 0, 0);
Color blue = Color::from_hex("0000FF");
std::string hex = red.to_hex();  // "FF0000"

// Paragraph Format
ParagraphFormat format;
format.set_alignment(ParagraphAlignment::Center);
format.set_line_spacing(360, LineSpacingRule::Auto);  // 1.5x
format.set_space_before(12);      // 12 points
format.set_first_line_indent(24); // 24 points

// Border and Shading
Border border(BorderType::Single, Color(0, 0, 0), 4);
format.borders().set_all(border);
format.shading().set_solid_fill(Color(240, 240, 240));

// Font
Font font;
font.set_name("Arial");
font.set_name_far_east("微软雅黑");
font.set_size(14);
font.set_bold(true);
font.set_underline(UnderlineStyle::Single);
font.set_color(Color(255, 0, 0));

// Tab stops
TabStopCollection tabs;
tabs.add(1.0 * 72, TabStop::Alignment::Left);
tabs.add(2.5 * 72, TabStop::Alignment::Center, TabStop::Leader::Dots);
```

### 8. Template Class (`cdocx::Template`)
Template-based document generation with placeholder replacement.

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

### 9. DocumentInserter Class (`cdocx::DocumentInserter`)
Insert content from one document into another.

```cpp
cdocx::DocumentInserter inserter(&target_doc);
inserter.insert_document(&source_doc);  // Insert at end
inserter.insert_document(&source_doc, InsertPosition::Beginning);
```

### 10. BookmarkReplacer Class (`cdocx::BookmarkReplacer`)
High-level API for bookmark-based replacement.

```cpp
cdocx::BookmarkReplacer replacer(&doc);
replacer.replace_text("bookmark_name", "replacement text");
replacer.replace_with_image("image_bookmark", "path/to/image.png", 
                           ImageAlignment::Center);
```

---

## Build System

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_SHARED_LIBS` | OFF | Build shared instead of static library |
| `BUILD_EXAMPLES` | ON | Build example programs |
| `BUILD_TESTING` | ON | Build test suite |
| `BUILD_DOCS` | OFF | Build documentation with Doxygen |
| `ENABLE_COVERAGE` | OFF | Enable code coverage (GCC/Clang) |
| `ENABLE_WERROR` | OFF | Treat warnings as errors |
| `USE_SYSTEM_GTEST` | OFF | Use system Google Test |

### Build Commands

**Windows (Visual Studio):**
```cmd
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release --parallel
ctest -C Release --output-on-failure
```

**Windows (MinGW):**
```cmd
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
```

**Linux/macOS:**
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
ctest --output-on-failure
```

**Using Build Scripts:**
```bash
# Linux/macOS
./scripts/build-linux.sh Release

# Windows (Visual Studio Developer Command Prompt)
scripts\build-windows.bat Release x64
```

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
    GIT_REPOSITORY https://github.com/lonlng/CDocx.git
    GIT_TAG v0.6.0
)
FetchContent_MakeAvailable(cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)
```

---

## Testing

### Test Structure
Tests organized in numbered directories under `test/`:
- `01_basic/` - Basic functionality tests
- `02_iterator/` - Iterator tests
- `03_template/` - Template system tests
- `04_xml_parts/` - XML Parts API tests
- `05_complete_structure/` - Complete structure tests
- `06_create_empty/` - Empty document creation
- `07_text_formatting/` - Text formatting tests
- `08_bookmark_replacement/` - Bookmark replacement tests
- `09_section_and_list/` - Section and list tests

### Running Tests

```bash
# Run all tests
ctest

# Run with verbose output
ctest -V

# Run specific categories
ctest -L core           # Core functionality
ctest -L template       # Template system
ctest -L advanced       # Advanced features

# Using CMake targets
cmake --build . --target test_all
cmake --build . --target test_core
cmake --build . --target test_quick
```

---

## Code Style Guidelines

### Formatting
- **Tool**: clang-format with LLVM base style
- **Indent**: 4 spaces
- **Line width**: 100 characters
- **Command**: `clang-format -i src/*.cpp include/*.h include/**/*.h`

### Naming Conventions

| Element | Convention | Examples |
|---------|------------|----------|
| Classes | PascalCase | `Document`, `Paragraph` |
| Methods | CamelCase | `GetText()`, `SetText()` |
| Constants | kCamelCase | `kMaxBufferSize` |
| Namespace | lowercase | `cdocx` |
| Private members | trailing underscore | `filepath_`, `impl_` |

### Header Files
All public headers use `#pragma once`:

```cpp
/**
 * @file filename.h
 * @brief Brief description
 * @details Detailed description
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.6.0
 */

#pragma once

// Includes here
```

### Code Quality Tools

```bash
# Format all code
cmake --build build --target format

# Check formatting
cmake --build build --target format-check

# Static analysis
cmake --build build --target tidy

# Run all quality checks
./scripts/code-quality.sh all
```

---

## API Quick Reference

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

// Combine flags
p.add_run("bold italic", cdocx::bold | cdocx::italic);
```

### Iterator Pattern

```cpp
// Traditional iteration
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    for (auto r = p.runs(); r.has_next(); r.next()) {
        std::string text = r.get_text();
    }
}

// Range-based for (C++11)
for (auto& p : doc.paragraphs()) {
    for (auto& r : p.runs()) {
        std::cout << r.get_text() << std::endl;
    }
}
```

---

## Version History

### v0.6.0 (Current)
- **Node Hierarchy**: Unified Node base class with DocumentVisitor pattern
- **Format Attributes**: Comprehensive formatting system (ParagraphFormat, Font, Color, Border, etc.)
- **Enhanced Architecture**: Better separation of concerns with format attribute classes

### v0.5.0
- **Section Support**: Document section management with page setup
- **List/Numbering System**: Bulleted, numbered, Chinese numbering support
- **Outline Lists**: Multi-level outline format support

### v0.4.0
- **Bookmark Replacement**: High-level API with format preservation
- **Caption Generation**: Automatic figure caption generation
- **Enhanced Properties**: Document property structures

### v0.3.0
- **Template System**: Placeholder replacement with custom patterns
- **Document Insertion**: Merge documents at specific positions
- **XML Parts API**: Direct access to all DOCX internal components

### v0.2.0
- **Media Management**: Add, delete, replace images
- **DocumentBuilder**: Fluent document construction API
- **Search and Replace**: Find and replace functionality

### v0.1.0
- **Core Document Operations**: Read, write, edit DOCX files
- **Paragraph and Run**: Basic text manipulation
- **Table Support**: Basic table creation and manipulation
- **Iterator-Based API**: Modern C++17 iterator pattern

---

## Roadmap

### Current Features (v0.6.0)
- ✅ Complete document operations (open, create, save DOCX)
- ✅ Paragraph and Run manipulation with formatting
- ✅ Table creation and manipulation
- ✅ Template-based placeholder replacement
- ✅ Document insertion/merging
- ✅ Media file management (images)
- ✅ XML Parts API access
- ✅ Bookmark management with format preservation
- ✅ Image insertion with alignment
- ✅ Figure caption generation
- ✅ DocumentBuilder for fluent construction
- ✅ Find and replace
- ✅ Section support (page setup, margins, orientation)
- ✅ List/Numbering system (bulleted, numbered, Chinese)
- ✅ Node hierarchy with Visitor pattern
- ✅ Format attributes (ParagraphFormat, Font, Color, Border, Shading, TabStop)

### Planned Features

**Phase 2: Export Formats**
- PDF export (libharu)
- HTML export
- Image rendering (PNG/JPG)

**Phase 3: Advanced Features**
- Field support (page numbers, TOC, hyperlinks)
- Comments/annotations
- Footnotes and endnotes
- Styles system enhancement

**Phase 4: Professional Features**
- Enhanced mail merge
- Document comparison
- Chart support
- Formula (OMML) support

---

## Security Considerations

- Input validation on file paths and image formats
- ZIP extraction limits prevent zip bomb attacks
- XML parsing uses pugixml's secure defaults
- File size validation via `validate_image_size()`

## Platform Support

| Platform | Compiler | Status |
|----------|----------|--------|
| Linux | GCC 7+ | ✅ Fully Supported |
| Linux | Clang 5+ | ✅ Fully Supported |
| Windows | MSVC 2017+ | ✅ Fully Supported |
| Windows | MinGW-w64 | ✅ Supported |
| macOS | Xcode 10+ | ✅ Supported |

---

## Contributing

1. Discuss changes via issue or email before starting
2. Make focused PRs that handle one specific topic
3. Follow code style (run clang-format)
4. Add tests for new functionality
5. Update documentation

---

## License

MIT License - see [LICENSE](LICENSE) file for details.

---

*This file is intended for AI coding agents. For user documentation, see [README.md](README.md).*
