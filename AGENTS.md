# CDocx - C++ DOCX Library

## Project Overview

CDocx is a C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. The library provides a modern, iterator-based API for document manipulation with support for text formatting, paragraphs, tables, template-based document generation, document insertion, bookmarks, sections, lists, and advanced XML parts access.

**Key Facts:**
- **Language**: C++17 (C99 for zip library component)
- **License**: MIT
- **Build System**: CMake (minimum version 3.14)
- **Namespace**: `cdocx`
- **Version**: 0.5.0
- **External Dependencies** (fetched via CMake FetchContent):
  - [pugixml](https://gitee.com/lonlng/pugixml) (v1.15) - XML parsing
  - [zip](https://gitee.com/lonlng/zip) (v0.3.6) - ZIP archive handling
  - [Google Test](https://gitee.com/lonlng/googletest) (v1.17.0) - Testing framework

## Project Structure

```
cdocx/
├── CMakeLists.txt              # Main CMake configuration
├── .clang-format               # Code formatting rules (LLVM style, 4-space indent)
├── README.md                   # User-facing documentation
├── AGENTS.md                   # This file - agent-focused documentation
├── LICENSE                     # MIT License
├── CONTRIBUTING.md             # Contribution guidelines
├── SECURITY.md                 # Security policy
│
├── cmake/
│   └── modules/
│       └── CDocxHelpers.cmake  # CMake helper functions for examples/tests
│
├── include/                    # Public API headers
│   ├── cdocx.h                 # Main aggregated header (includes all modules)
│   └── cdocx/                  # Modular headers
│       ├── fwd.h               # Forward declarations
│       ├── constants.h         # Formatting flags (bold, italic, etc.)
│       ├── iterator.h          # Iterator helpers
│       ├── base.h              # Base content classes (Run, Paragraph, Table)
│       ├── document.h          # Document class (main entry point)
│       ├── template.h          # Template replacement
│       ├── inserter.h          # Document insertion
│       ├── advanced.h          # Advanced features (Bookmark, DocumentBuilder, Search)
│       ├── bookmark_replacer.h # Bookmark replacement API
│       ├── caption_generator.h # Figure caption generation
│       ├── format_context.h    # Text formatting context
│       ├── properties.h        # Property structures (v0.4.0+)
│       ├── section.h           # Section support (v0.5.0)
│       └── numbering.h         # List/Numbering system (v0.5.0)
│
├── src/                        # Implementation files
│   ├── base_content.cpp        # Content classes implementation
│   ├── document.cpp            # Document class implementation
│   ├── template.cpp            # Template implementation
│   ├── inserter.cpp            # Document inserter implementation
│   ├── tree.cpp                # Tree structure (DocxTree, DocxTreeNode)
│   ├── impl.cpp                # DocumentImpl implementation
│   ├── advanced.cpp            # Advanced features implementation
│   ├── bookmark_replacer.cpp   # Bookmark replacement implementation
│   ├── caption_generator.cpp   # Caption generation implementation
│   ├── format_context.cpp      # Format context implementation
│   ├── properties.cpp          # Properties implementation
│   ├── section.cpp             # Section implementation (v0.5.0)
│   └── numbering.cpp           # Numbering implementation (v0.5.0)
│
├── include/detail/
│   └── impl.h                  # Private implementation details (PIMPL)
│
├── test/                       # Test suite (Google Test)
│   ├── CMakeLists.txt          # Test configuration
│   ├── 01_basic/               # Basic functionality tests
│   ├── 02_iterator/            # Iterator tests
│   ├── 03_template/            # Template tests
│   ├── 04_xml_parts/           # XML Parts API tests
│   ├── 05_complete_structure/  # Complete structure tests
│   ├── 06_create_empty/        # Empty document creation tests
│   ├── 07_text_formatting/     # Text formatting tests
│   ├── 08_bookmark_replacement/# Bookmark replacement tests
│   └── 09_section_and_list/    # Section and list tests (v0.5.0)
│
├── examples/                   # Example programs
│   ├── CMakeLists.txt          # Examples configuration
│   ├── 01_basic_read/          # Basic document reading
│   ├── 02_basic_create/        # Basic document creation
│   ├── 03_template_basic/      # Basic template usage
│   ├── 04_template_advanced/   # Advanced template features
│   ├── 05_document_insert/     # Document insertion
│   ├── 06_xml_parts/           # XML Parts API usage
│   ├── 07_media_management/    # Media file management
│   ├── 08_create_empty/        # Empty document creation
│   ├── 09_text_formatting/     # Text formatting examples
│   ├── 10_advanced_crud/       # Advanced CRUD operations
│   ├── 10_edit_document/       # Document editing
│   ├── 11_bookmark_replacement/# Bookmark replacement demo
│   ├── 12_caption_generation/  # Figure caption generation
│   ├── 13_enhanced_properties/ # Enhanced properties demo
│   └── 13_section_and_list/    # Section and list demo (v0.5.0)
│
├── docs/                       # Documentation
│   ├── INDEX.md                # Documentation index
│   ├── INSTALL.md              # Installation instructions
│   ├── REFACTORING_SUMMARY.md  # Code structure documentation
│   ├── OPTIMIZATION_UPGRADE_PLAN.md  # Optimization roadmap
│   ├── ASPOSE_COMPARISON_AND_ROADMAP.md  # Feature comparison
│   ├── V0.5.0_IMPLEMENTATION_SUMMARY.md  # v0.5.0 implementation details
│   └── archive/                # Archived design documents
│
├── scripts/                    # Build scripts
│   ├── install.sh              # Installation script
│   └── README.md               # Scripts documentation
│
└── build/                      # Build directory (created by CMake)
```

## Architecture

### Core Components

#### 1. Document Class (`cdocx::Document`)
- Entry point for all DOCX operations
- **Complete Structure Support**: Loads entire DOCX package into memory including all XML parts, media files, and relationships
- **Tree-Based Storage**: Internal tree structure mirrors ZIP file organization
- Uses PIMPL idiom: `std::unique_ptr<DocumentImpl> impl_` hides implementation details
- Handles file I/O and ZIP archive management
- Provides access to paragraphs, tables, sections, and lists
- Manages XML document structure using pugixml

#### 2. Paragraph Class (`cdocx::Paragraph`)
- Represents document paragraphs
- Contains runs (text segments with formatting)
- Supports insertion and text manipulation
- Iterator-based traversal with `has_next()` and `next()` methods
- Compatible with C++11 range-based for loops
- List/Numbering support via `set_numbering()` method (v0.5.0)

#### 3. Run Class (`cdocx::Run`)
- Represents formatted text segments
- Supports various formatting flags (bold, italic, underline, etc.)
- Text manipulation with `get_text()` and `set_text()` methods

#### 4. Table Classes (`cdocx::Table`, `cdocx::TableRow`, `cdocx::TableCell`)
- Full table manipulation support
- Row and cell iteration
- Hierarchical structure: Table → Row → Cell → Paragraph

#### 5. Section Class (`cdocx::Section`) (v0.5.0)
- Document section management
- Page setup (size, orientation, margins)
- Header/Footer references
- Content addition (paragraphs, tables)

#### 6. Numbering System (`cdocx::NumberingManager`, etc.) (v0.5.0)
- List definition management
- Bulleted and numbered lists
- Chinese numbering support
- Outline list support

#### 7. Template Class (`cdocx::Template`)
- Template-based document generation
- Placeholder replacement with custom patterns (default: `{{` and `}}`)
- Supports text and image placeholders

#### 8. DocumentInserter Class (`cdocx::DocumentInserter`)
- Insert content from one document into another
- Position-based insertion (beginning, specific location, end)
- Support for paragraphs only, tables only, or complete documents

#### 9. BookmarkReplacer Class (`cdocx::BookmarkReplacer`)
- High-level API for bookmark-based replacement
- Format preservation during replacement
- Image insertion with alignment support
- Figure caption generation

### Internal Tree Structure

CDocx uses a tree-based internal structure to represent the DOCX package:

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
    std::string name;                           // File/directory name
    std::string full_path;                      // Full path in ZIP
    DocxNodeType type;                          // Node type
    std::shared_ptr<pugi::xml_document> xml_doc;     // For XmlFile
    FileDataStorage file_storage;                    // Unified file data storage
    std::string content_type;                        // MIME type
    bool is_modified = false;
    bool is_new = false;
    bool is_deleted = false;
};
```

**Key Design Points:**
- Tree structure is **completely hidden** from public API (in `detail/impl.h`)
- All data stored directly in memory (simplified from earlier versions)
- Path mapping provides O(1) lookup performance
- Thread-safe read operations via shared_mutex

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
│   ├── numbering.xml            # Numbering definitions (v0.5.0)
│   ├── footnotes.xml            # Footnotes
│   ├── endnotes.xml             # Endnotes
│   ├── footer1.xml              # Footer (can be multiple)
│   ├── header1.xml              # Header (can be multiple)
│   ├── theme/
│   │   └── theme1.xml           # Theme definitions
│   └── media/                   # Images and other media
│       ├── image1.png
│       └── ...
└── customXml/                   # Custom XML data
```

## Build System

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_SHARED_LIBS` | OFF | Build shared instead of static library |
| `BUILD_EXAMPLES` | ON | Build example programs |
| `BUILD_TESTING` | ON | Build test suite |
| `BUILD_DOCS` | OFF | Build documentation with Doxygen |
| `ENABLE_COVERAGE` | OFF | Enable code coverage (GCC/Clang only) |
| `ENABLE_WERROR` | OFF | Treat warnings as errors |
| `USE_SYSTEM_GTEST` | OFF | Use system Google Test instead of fetching |

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

# Windows (in Visual Studio Developer Command Prompt)
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
    GIT_TAG v0.5.0
)
FetchContent_MakeAvailable(cdocx)
target_link_libraries(your_target PRIVATE cdocx::cdocx)
```

## Testing

### Test Structure
Tests are organized in numbered directories under `test/`:
- `01_basic/` - Basic functionality tests
- `02_iterator/` - Iterator tests
- `03_template/` - Template system tests
- `04_xml_parts/` - XML Parts API tests
- `05_complete_structure/` - Complete structure tests
- `06_create_empty/` - Empty document creation tests
- `07_text_formatting/` - Text formatting tests
- `08_bookmark_replacement/` - Bookmark replacement tests
- `09_section_and_list/` - Section and list tests (v0.5.0)

### Running Tests

```bash
# Run all tests
ctest

# Run with verbose output
ctest -V

# Run specific test categories
ctest -L core           # Core functionality tests
ctest -L template       # Template system tests
ctest -L advanced       # Advanced feature tests

# Using CMake targets
cmake --build . --target test_all
cmake --build . --target test_core
cmake --build . --target test_quick
cmake --build . --target test_template
cmake --build . --target test_advanced
```

### Test Utilities (CDocxHelpers.cmake)

The `add_cdocx_test()` function provides:
- Automatic executable creation with proper settings
- Data file copying from `data/` subdirectory
- CTest registration with labels and timeouts
- Google Test linking

```cmake
add_cdocx_test(test_name test.cpp
    DATA file1.docx file2.docx    # Data files to copy
    LABELS "core;basic"           # CTest labels
    TIMEOUT 30                    # Test timeout in seconds
)
```

## Code Style Guidelines

### Formatting
- **Tool**: clang-format with LLVM base style
- **Indent**: 4 spaces
- **Command**: `clang-format -i src/*.cpp include/*.h include/**/*.h`

### Naming Conventions

| Element | Convention | Examples |
|---------|------------|----------|
| Classes | PascalCase | `Document`, `Paragraph`, `Template` |
| Methods | snake_case | `get_text()`, `set_text()`, `replace_all()` |
| Constants | snake_case | `bold`, `italic`, `underline` |
| Namespace | lowercase | `cdocx` |
| Private members | trailing underscore | `filepath_`, `impl_` |
| Type aliases | PascalCase | `formatting_flag`, `NumberingId` |

### Header Files
All public headers must use `#pragma once` and include appropriate documentation:

```cpp
/**
 * @file filename.h
 * @brief Brief description
 * @details Detailed description
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.5.0
 */

#pragma once

// Includes here
```

### Implementation Files
- Implementation files correspond to headers (e.g., `document.h` → `document.cpp`)
- Use PIMPL idiom for implementation hiding
- Private implementation details in `include/detail/impl.h`

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

// Section support (v0.5.0)
Section* add_section();
Section* get_first_section();
SectionCollection sections();
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

### XML Parts API

```cpp
// Access any XML part
pugi::xml_document* part = doc.get_xml_part("word/styles.xml");

// Convenience methods for common parts
pugi::xml_document* doc_xml = doc.get_document_xml();
pugi::xml_document* styles = doc.get_styles();
pugi::xml_document* numbering = doc.get_numbering();

// Header/Footer access
pugi::xml_document* footer1 = doc.get_footer(1);
pugi::xml_document* header1 = doc.get_header(1);
```

### Media Management

```cpp
// Add media from file
doc.add_media("path/to/image.jpg");
doc.add_media_from_memory("image.png", image_data, "image/png");

// List and check media
std::vector<std::string> media = doc.list_media();
bool exists = doc.has_media("image.jpg");

// Export media
doc.export_media("image.jpg", "output/path.jpg");
```

### List/Numbering (v0.5.0)

```cpp
// Create list definitions
NumberingId bullet_list = doc.add_bulleted_list_definition();
NumberingId numbered_list = doc.add_numbered_list_definition(NumberStyle::Decimal);
NumberingId chinese_list = doc.add_chinese_numbered_list_definition();

// Apply to paragraph (declaration, implementation pending)
paragraph.set_numbering(bullet_list, 0);  // Level 0
```

## Development Conventions

### Adding New Features

1. **Headers**: Add public declarations to `include/cdocx/*.h`
2. **Implementation**: Add implementations to `src/*.cpp`
3. **Update Main Header**: Add include to `include/cdocx.h` if new public API
4. **Tests**: Add tests in `test/XX_feature_name/`
5. **Examples**: Add example in `examples/XX_feature_name/`
6. **Documentation**: Update relevant docs in `docs/`

### PIMPL Pattern Usage

All public classes use the PIMPL idiom:

```cpp
// In public header (document.h)
class Document {
private:
    std::unique_ptr<DocumentImpl> impl_;
public:
    // Public API only, no implementation details
};

// In private header (detail/impl.h)
class DocumentImpl {
    // All implementation details
};
```

### Iterator Pattern

Classes that need iteration expose iterator methods:

```cpp
// Traditional iteration
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    // Process paragraph
}

// Range-based for (C++11)
for (auto& p : doc.paragraphs()) {
    for (auto& r : p.runs()) {
        std::cout << r.get_text() << std::endl;
    }
}
```

## Security Considerations

- Input validation is performed on file paths and image formats
- ZIP extraction limits prevent zip bomb attacks
- XML parsing uses pugixml's secure defaults
- File size validation available via `validate_image_size()`

## Platform-Specific Notes

### Windows
- MSVC Runtime Library is set globally to ensure consistency
- Default: Static runtime (/MT, /MTd)
- Use `BUILD_SHARED_LIBS=ON` for dynamic runtime (/MD, /MDd)
- UTF-8 source and execution character set enforced

### Linux/macOS
- UTF-8 character set support via compiler flags
- Code coverage support via `ENABLE_COVERAGE` option

## Troubleshooting

### Common Issues

**"pugixml.hpp not found"**
- Dependencies are fetched automatically via CMake FetchContent
- Ensure network connectivity for initial build

**LNK2038: Runtime library mismatch**
- All targets use consistent runtime library settings
- Check `CMAKE_MSVC_RUNTIME_LIBRARY` if customizing

**CMake errors**
- Ensure CMake 3.14+
- Delete build directory and reconfigure if issues persist

## Contributing

1. Discuss changes via issue or email before starting
2. Make focused PRs that handle one specific topic
3. Follow existing code style (run clang-format)
4. Add tests for new functionality
5. Update documentation if needed

## Roadmap

### Current Features (v0.5.0)
- ✅ Document operations (open, create, save DOCX)
- ✅ Paragraph and Run manipulation
- ✅ Basic text formatting (bold, italic, underline, etc.)
- ✅ Table creation and basic manipulation
- ✅ Template-based placeholder replacement
- ✅ Document insertion/merging
- ✅ Media file management (images)
- ✅ XML Parts API access
- ✅ Bookmark management with format preservation
- ✅ BookmarkReplacer class
- ✅ Image insertion with alignment
- ✅ Figure caption generation
- ✅ DocumentBuilder for fluent document construction
- ✅ Find and replace
- ✅ **Section support** (page setup, margins, orientation)
- ✅ **List/Numbering system** (bulleted, numbered, Chinese)

### Planned Features
See [docs/ASPOSE_COMPARISON_AND_ROADMAP.md](docs/ASPOSE_COMPARISON_AND_ROADMAP.md) for detailed roadmap.

**Phase 2: Export Formats**
- PDF export
- HTML export
- Image rendering (PNG/JPG)

**Phase 3: Advanced Features**
- Field support (page numbers, TOC, hyperlinks)
- Comments/annotations
- Footnotes and endnotes
- Styles system

**Phase 4: Professional Features**
- Enhanced mail merge
- Document comparison
- Chart support
- Formula (OMML) support

## License

MIT License - see [LICENSE](LICENSE) file for details.

---

*This file is intended for AI coding agents. For user documentation, see [README.md](README.md).*
