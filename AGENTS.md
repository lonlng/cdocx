# CDocx - C++ DOCX Library

## Project Overview

CDocx is a C++17 library for creating, reading, and writing Microsoft Office Word (.docx) files. It currently provides a stable legacy iterator-based API and is transitioning toward a DOM-style architecture.

**Key Facts:**
- **Language**: C++17 (C99 for zip library component)
- **License**: MIT
- **Build System**: CMake (minimum version 3.14)
- **Namespace**: `cdocx`
- **Version**: 0.8.0
- **Dependencies** (auto-fetched via CMake FetchContent):
  - [pugixml](https://gitee.com/lonlng/pugixml) (v1.15) - XML parsing
  - [zip](https://gitee.com/lonlng/zip) (v0.3.6) - ZIP archive handling
  - [Google Test](https://gitee.com/lonlng/googletest) (v1.17.0) - Testing framework

---

## Project Structure

```
cdocx/
├── CMakeLists.txt              # Main CMake configuration
├── .clang-format               # Code formatting rules
├── .clang-tidy                 # Static analysis configuration
├── README.md                   # User-facing documentation
├── AGENTS.md                   # This file
├── LICENSE                     # MIT License
├── CONTRIBUTING.md             # Contribution guidelines
├── SECURITY.md                 # Security policy
│
├── cmake/
│   └── modules/
│       └── CDocxHelpers.cmake  # CMake helper functions for examples/tests
│
├── include/                    # Public API headers
│   ├── cdocx.h                 # Main aggregated header
│   └── cdocx/                  # Modular headers
│       ├── document.h          # Document class (DOM root)
│       ├── cdocx.h             # CDocx factory methods
│       ├── node.h              # Node/CompositeNode hierarchy
│       ├── body.h              # Body class
│       ├── paragraph.h         # Paragraph, Run, Field, Hyperlink
│       ├── paragraph_builder.h # ParagraphBuilder fluent API
│       ├── table.h             # Table, Row, Cell
│       ├── table_builder.h     # TableBuilder fluent API
│       ├── section.h           # Section, HeaderFooter
│       ├── numbering.h         # List/Numbering
│       ├── template.h          # Template replacement (legacy FSM)
│       ├── template_engine.h   # TemplateEngine unified API
│       ├── inserter.h          # Document insertion
│       ├── advanced.h          # DocumentBuilder, DocumentSearch, TableOperations
│       ├── document_builder.h  # DocumentBuilder declarations
│       ├── document_search.h   # DocumentSearch declarations
│       ├── bookmark.h          # Bookmark collection
│       ├── bookmark_replacer.h # Bookmark replacement
│       ├── bookmark_inserter.h # Bookmark insertion
│       ├── caption_generator.h # Caption generation
│       ├── comment.h           # CommentCollection
│       ├── mail_merge.h        # Mail merge
│       ├── watermark.h         # Watermark
│       ├── style.h             # Style / StyleCollection
│       ├── range.h             # Range operations
│       ├── footnote.h          # Footnote / FootnoteReference
│       ├── formfield.h         # Form field support
│       ├── format.h            # Format attributes
│       ├── format_context.h    # Format context
│       ├── properties.h        # Property structures
│       ├── enums.h             # Enumerations
│       ├── constants.h         # Constants
│       ├── control_char.h      # Control character constants
│       ├── convert_util.h      # Unit conversions
│       ├── file_format_util.h  # File format detection
│       ├── fwd.h               # Forward declarations
│       ├── iterator.h          # Iterator support
│       └── base.h              # Legacy iterators
│
├── include/detail/
│   └── impl.h                  # Private implementation (PIMPL)
│
├── src/                        # Implementation files
│   ├── advanced.cpp            # DocumentBuilder, DocumentSearch, TableOperations
│   ├── base_content.cpp
│   ├── body.cpp
│   ├── bookmark.cpp            # Bookmark collection DOM
│   ├── bookmark_inserter.cpp   # Bookmark inserter (physical XML)
│   ├── bookmark_replacer.cpp   # Bookmark replacement
│   ├── caption_generator.cpp
│   ├── cdocx.cpp               # CDocx factory class
│   ├── comment.cpp             # CommentCollection
│   ├── convert_util.cpp        # Unit conversions
│   ├── document.cpp            # Document core + media/relationships
│   ├── document_builder.cpp    # DocumentBuilder fluent API
│   ├── document_io.cpp         # Document load/save
│   ├── document_media.cpp      # Media management
│   ├── document_relationships.cpp # Relationship handling
│   ├── document_search.cpp     # DocumentSearch find/replace
│   ├── document_sync.cpp       # DOM-XML sync (legacy monolithic)
│   ├── file_format_util.cpp    # File format detection
│   ├── footnote.cpp            # Footnote / endnote DOM
│   ├── format.cpp              # Color implementation
│   ├── format_context.cpp
│   ├── formfield.cpp           # Form field support
│   ├── impl.cpp                # PIMPL internals
│   ├── inserter.cpp            # DocumentInserter
│   ├── mail_merge.cpp          # Mail merge
│   ├── node.cpp                # Node/CompositeNode tree ops
│   ├── numbering.cpp           # List/Numbering
│   ├── paragraph.cpp           # Paragraph, Run, Field, Hyperlink
│   ├── paragraph_builder.cpp   # ParagraphBuilder fluent API
│   ├── properties.cpp
│   ├── range.cpp               # Range operations
│   ├── section.cpp             # Section, HeaderFooter
│   ├── style.cpp               # Style / StyleCollection
│   ├── sync_comment.cpp        # Comment XML sync
│   ├── sync_common.cpp/.h      # Common sync utilities
│   ├── sync_deserialize.cpp    # XML-to-DOM deserialization
│   ├── sync_footnote.cpp       # Footnote XML sync
│   ├── sync_properties.cpp     # Property XML sync
│   ├── sync_serialize.cpp      # DOM-to-XML serialization
│   ├── sync_style.cpp          # Style XML sync
│   ├── table.cpp               # Table, Row, Cell
│   ├── table_builder.cpp       # TableBuilder fluent API
│   ├── template.cpp            # Template replacement (legacy FSM)
│   ├── template_engine.cpp     # TemplateEngine unified API
│   ├── tree.cpp                # DocxTree physical model
│   └── watermark.cpp           # Text/image watermarks
│
├── test/                       # Test suite (Google Test)
│   ├── 01_basic/
│   ├── 02_iterator/
│   ├── 03_template/
│   ├── 04_xml_parts/
│   ├── 05_complete_structure/
│   ├── 06_create_empty/
│   ├── 07_text_formatting/
│   ├── 08_bookmark_replacement/
│   ├── 09_section_and_list/
│   ├── 10_dom_sync/
│   ├── 11_table_merge/
│   ├── 12_document_search/
│   ├── 13_document_builder/
│   ├── 14_style_collection/
│   ├── 15_mail_merge/
│   ├── 16_comment_collection/
│   ├── 17_footnote_collection/
│   ├── 18_field_switches/
│   ├── 19_template_engine/
│   └── CMakeLists.txt
│
├── examples/                   # Example programs
│   ├── 01_basic_read/
│   ├── 02_basic_create/
│   ├── 03_template_basic/
│   ├── 04_template_advanced/
│   ├── 05_document_insert/
│   ├── 06_xml_parts/
│   ├── 07_media_management/
│   ├── 08_create_empty/
│   ├── 09_text_formatting/
│   ├── 10_edit_document/
│   ├── 10_advanced_crud/       # Needs ENABLE_ADVANCED_FEATURES=ON
│   ├── 11_bookmark_replacement/
│   ├── 12_caption_generation/
│   ├── 13_enhanced_properties/
│   ├── 13_section_and_list/
│   ├── 14_table_merge/
│   ├── 15_document_search/
│   ├── 16_document_builder/
│   ├── 17_style_collection/
│   ├── 18_new_features/
│   ├── 19_mail_merge/
│   ├── 21_template_engine/
│   ├── test_dom_sync/
│   └── CMakeLists.txt
│
├── scripts/
│   ├── README.md
│   ├── code-quality.bat        # Windows code quality script
│   ├── code-quality.sh         # Linux/macOS code quality script
│   └── install.sh
│
├── docs/                       # Architecture docs and roadmaps
│   ├── 文档索引.md
│   ├── 架构设计.md
│   ├── API示例.md
│   ├── 增强路线图.md
│   └── 项目进度报告.md
│
└── .github/
    ├── workflows/
    │   ├── cmake.yml           # CI: Build and test on Linux/Windows/macOS
    │   ├── code-quality.yml    # CI: clang-format and cppcheck
    │   └── docs.yml            # CI: Doxygen docs to GitHub Pages
    ├── ISSUE_TEMPLATE/
    ├── FUNDING.yml
    ├── PULL_REQUEST_TEMPLATE.md
    └── dependabot.yml
```

---

## Build and Test Commands

### Quick Build

```bash
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTING=ON
cmake --build . --parallel
ctest --output-on-failure
```

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_SHARED_LIBS` | OFF | Build shared instead of static library |
| `BUILD_EXAMPLES` | ON | Build example programs |
| `BUILD_TESTING` | ON | Build tests |
| `BUILD_DOCS` | OFF | Build Doxygen docs |
| `ENABLE_COVERAGE` | OFF | Code coverage (GCC/Clang Debug only) |
| `ENABLE_WERROR` | OFF | Warnings as errors |
| `USE_SYSTEM_GTEST` | OFF | Use system Google Test instead of fetching |

### Test Commands

```bash
# Run all tests
ctest --output-on-failure

# Run via custom targets
cmake --build build --target test_all      # All tests
cmake --build build --target test_core     # Core tests only
cmake --build build --target test_quick    # Quick smoke tests
cmake --build build --target test_advanced # Advanced feature tests
```

### Code Quality Commands

```bash
# Format all code
cmake --build build --target format

# Check formatting (CI)
cmake --build build --target format-check

# Run clang-tidy
cmake --build build --target tidy

# Auto-fix clang-tidy issues
cmake --build build --target tidy-fix

# Run all quality checks
cmake --build build --target code-quality

# Or use scripts
./scripts/code-quality.sh all       # Linux/macOS
scripts\code-quality.bat all       # Windows
```

---

## Code Style Guidelines

This project uses a **customized Google C++ Style Guide**.

### Customizations from Google Style

| Aspect | Google Standard | Our Customization |
|--------|-----------------|-------------------|
| Indentation | 2 spaces | **4 spaces** |
| Column limit | 80 chars | **100 chars** |
| Header guards | `#ifndef` | **`#pragma once`** (allowed) |

### Naming Conventions

| Type | Convention | Example |
|------|------------|---------|
| Types | `CamelCase` | `Document`, `Paragraph`, `SectionProperties` |
| Functions/Methods | `CamelCase` | `Open()`, `GetText()`, `IsOpen()` |
| Variables | `snake_case` | `file_path`, `paragraph_count` |
| Member variables | `snake_case_` | `impl_`, `filepath_` |
| Constants | `kCamelCase` | `kMaxSize`, `kDefaultValue`, `kBold` |
| Macros | `UPPER_CASE` | `CDOCX_API`, `DISALLOW_COPY_AND_ASSIGN` |
| Files | `snake_case` | `document.h`, `base_content.cpp` |
| Namespaces | `snake_case` | `cdocx` |

### Formatting Rules

- **Indentation**: 4 spaces (no tabs)
- **Line length**: 100 characters
- **Braces**: K&R style (opening brace on same line)
- **Header guards**: `#pragma once`
- **Pointer alignment**: Left (`int* ptr`)
- **Include sorting**: Enabled, with specific priority groups (C system, C++ std, third-party, project)

### Tools

- **Formatter**: `clang-format` with `.clang-format`
- **Linter**: `clang-tidy` with `.clang-tidy`
- **Additional static analysis**: `cppcheck` (used in CI)

---

## Architecture

### Core Design Principles

1. **Complete Structure Support**: Loads entire DOCX package into memory
2. **Tree-Based Storage**: Internal `DocxTree` mirrors ZIP file organization
3. **Dual API Design**: Legacy iterator API coexists with emerging DOM API
4. **PIMPL Pattern**: Implementation details hidden for ABI stability
5. **Zero External Dependencies**: All deps fetched via CMake FetchContent

### DOM Architecture (In Transition)

The library is transitioning to a DOM architecture where major classes inherit from `Node` or `CompositeNode`, but several critical methods remain unimplemented.

```cpp
// Target hierarchy (partially implemented)
Node (abstract)
├── CompositeNode
│   ├── Document      (contains Sections)
│   ├── Section       (contains Body, HeaderFooter refs)
│   ├── Body          (contains Paragraphs, Tables)
│   ├── Paragraph     (contains Runs)
│   ├── Table         (contains Rows)
│   ├── Row           (contains Cells)
│   └── Cell          (contains Paragraphs)
└── Leaf nodes
    ├── Run           (fully supported)
    └── SpecialChar   (basic support)
```

**Implementation status (as of code audit):**
- `clone()` is **implemented** on all major DOM nodes (`Document`, `Section`, `Body`, `Paragraph`, `Table`, `Row`, `Cell`, `HeaderFooter`, `Run`, `BookmarkStart/End`, `Hyperlink`, `Field`, `SpecialChar`) with full deep-copy support for children
- Document-order traversal (`get_previous_node_in_document`, `get_next_node_in_document`, `get_previous_logical`, `get_next_logical`) is **implemented** in `node.cpp`
- DOM-to-XML serialization handles **bookmarks, hyperlinks, and fields** (both serialization and deserialization); basic field round-tripping works
- `HeaderFooter` DOM content methods (`append_paragraph`, `append_table`, `get_paragraphs`) are **implemented**
- `DocumentBuilder` fluent API is **fully implemented** (text, hyperlinks, images, tables, bookmarks, fields)
- `CDocx` factory class (`create_document`, `load_document`, `save_document`) is **fully implemented**
- `DocumentSearch` (`find`, `replace`, `replace_all`, `replace_with_formatting`, `find_and_process`) is **fully implemented**
- `TableOperations` static helpers are **fully implemented**
- `TemplateEngine` unified dictionary-style API is **fully implemented**

### Physical Structure

The `DocxTree` and `DocxTreeNode` classes represent the ZIP package structure. Every XML part, media file, and relationship is loaded into this tree and synchronized with the DOM layer on demand.

---

## Feature Tiers and API Paths

CDocx provides **three API paths** to the same underlying DOCX package:

1. **DOM API** (recommended): Work with `Node`/`CompositeNode` objects. No XML knowledge required.
2. **XML Parts API** (power user): Direct `pugi::xml_document*` access to any Open XML part.
3. **Legacy Iterator API** (compatibility): Cursor-style iteration over raw XML nodes (`has_next()`/`next()`).

### Tier 1 — Basic Features (Complete)

| Feature | API | Status |
|---------|-----|--------|
| Open / create / save DOCX | `Document::open`, `save`, `create_empty` | Complete |
| DOM tree manipulation | `Node` / `CompositeNode` hierarchy | Complete |
| Paragraph / Run / Table / Cell CRUD | `append_paragraph`, `append_run`, `append_table`, etc. | Complete |
| Basic formatting (bold, italic, color, font, alignment) | `Run::set_bold`, `set_color`, `ParagraphFormat` | Complete |
| Special characters (tab, break, page break) | `SpecialChar` | Complete |
| Sections, headers/footers, page setup | `Section`, `HeaderFooter`, `PageSetup` | Complete |
| Lists and numbering | `add_bulleted_list_definition`, `NumberingManager` | Complete |

### Tier 2 — Intermediate Features (Mostly Complete)

| Feature | API | Status |
|---------|-----|--------|
| Template placeholder replacement | `Template` | Complete |
| Bookmark text / image replacement | `BookmarkReplacer` | Partial (same-paragraph only) |
| Document insertion / merging | `DocumentInserter` | Complete |
| Media management (images) | `Document::add_media`, `replace_media`, `export_media` | Complete |
| Table fluent building | `TableBuilder` | Complete |
| DOM ↔ XML synchronization | `document_sync.cpp` (auto on save) | Complete (Run, Para, Table, Section, Bookmark, Hyperlink, Field) |
| Node deep copy and document-order traversal | `Node::clone`, `get_next_node_in_document` | Complete |

### Tier 3 — Advanced Features (Complete)

| Feature | API | Status |
|---------|-----|--------|
| Table merge/split | `Table::merge_cells`, `split_cell` | **Complete** |
| Document-wide search/replace | `DocumentSearch`, `Range::replace` | **Complete** |
| DocumentBuilder bookmarks, images, hyperlinks, fields | `DocumentBuilder` | **Complete** |
| Style manager | `StyleCollection` | **Complete** |
| Comment collection | `CommentCollection` | **Complete** |
| Mail merge | `MailMerge` | **Complete** |
| Watermark | `Watermark` | **Complete** |
| Complex fields (page numbers, dates, TOC) | `Field` DOM class | **Basic** (structure works; deep customization roadmap) |
| Footnote / endnote DOM wrappers | `Footnote`, `FootnoteReference` | **Basic** (DOM classes exist; collection API roadmap) |
| Export to PDF / HTML / Markdown | — | Roadmap (v0.9.0+) |

### Recommended API Selection

- **Creating or editing document content** → DOM API (`Paragraph::append_run`, `Body::append_table`, etc.)
- **Replacing placeholders in existing documents** → `Template` or `BookmarkReplacer`
- **Merging documents** → `DocumentInserter`
- **Modifying styles, settings, or raw XML** → XML Parts API (`doc.get_styles()`, `doc.get_settings()`)
- **Legacy code maintenance only** → Iterator API (`doc.paragraphs()`, `para.runs()`)

---

## Core Components

### 1. Document Class (`cdocx::Document`)
Entry point for all DOCX operations.

```cpp
// File operations
cdocx::Document doc("file.docx");
doc.open();
doc.save("new_name.docx");

// DOM API: Section access
auto sections = doc.get_sections();
auto first_section = doc.get_first_section();
auto new_section = doc.append_section();

// Legacy API: iterators
auto& para_iter = doc.paragraphs();
auto& table_iter = doc.tables();

// List/Numbering
NumberingId bullet = doc.add_bulleted_list_definition();
NumberingId number = doc.add_numbered_list_definition(NumberStyle::Decimal);

// XML Parts API
pugi::xml_document* styles = doc.get_styles();
pugi::xml_document* numbering = doc.get_numbering_xml();

// Media management
doc.add_media("image.jpg");
auto media = doc.list_media();
doc.export_media("image.jpg", "output/path.jpg");
```

### 2. Paragraph Class (`cdocx::Paragraph`)

```cpp
// DOM API
std::shared_ptr<Run> run = para.append_run("Hello");
run->set_bold(true);

// Legacy API
Run& r = para.add_run("Hello", cdocx::kBold | cdocx::kItalic);
bool ok = para.set_numbering(bullet_list_id, NumberingLevel::Level1);
```

### 3. Run Class (`cdocx::Run`)

```cpp
std::string text = run.get_text();
run.set_text("new text");
Font font;
font.set_bold(true);
run.set_font(font);
```

### 4. Table Classes (`cdocx::Table`, `cdocx::Row`, `cdocx::Cell`)
Full table manipulation including merge/split, column insert/delete, and auto-fit behaviors.

```cpp
auto table = std::make_shared<Table>(doc, 3, 4);
body->append_child(table);

for (auto& row : table->get_rows()) {
    for (auto& cell : row->get_cells()) {
        cell->set_text("A1");
    }
}

// Merge cells
auto merged = table->merge_cells(0, 0, 0, 1);
table->split_cell(merged, 1, 2);
```

### 5. Section Class (`cdocx::Section`)

```cpp
auto section = doc.append_section();
section->get_properties().orientation = PageOrientation::Landscape;
auto body = section->get_body();
body->append_paragraph("Landscape content");
```

### 6. Format Attributes
**`Color` is fully implemented.** `Font`, `ParagraphFormat`, `Border`, `Shading` are header-only struct declarations without a `.cpp` implementation. They work as data containers.

```cpp
// Color (fully implemented)
Color red(255, 0, 0);
Color blue = Color::from_hex("0000FF");

// Font / ParagraphFormat (header-only structs)
Font font;
font.set_name("Arial");
font.set_size(14);
font.set_bold(true);
```

### 7. Template Class (`cdocx::Template`)
Placeholder replacement with custom patterns.

```cpp
cdocx::Template tmpl(&doc);
tmpl.set("name", "John Doe");
tmpl.replace_all();
```

### 8. BookmarkReplacer Class
Bookmark-based replacement. **Same-paragraph bookmarks work reliably.**

```cpp
cdocx::BookmarkReplacer replacer(&doc);
replacer.replace_text("bookmark_name", "replacement text");
```

### 8.1 BookmarkInserter Class (`bookmark_inserter.h`)
**Status: Implemented (v0.7.0).** Programmatically wraps existing text with bookmark markers. Handles text that spans multiple adjacent `<w:r>` runs within a single paragraph.

```cpp
cdocx::BookmarkInserter inserter(&doc);
inserter.insert("COMPANY", "Acme Inc.");          // first occurrence only
inserter.insert_all("DATE", "2024-01-15");        // all occurrences
inserter.insert_batch({{"NAME", "John"}, {"AGE", "30"}});
```

**Important:** Because `BookmarkInserter` manipulates the physical XML tree directly, callers must invoke `doc.sync_from_physical_tree()` before `doc.save()` if the DOM and physical tree are out of sync.

### 9. DocumentBuilder (`document_builder.h` / `document_builder.cpp`)
Fully implemented fluent cursor-based builder:
- Cursor movement (`move_to_document_start`, `move_to_paragraph`, `move_to_bookmark`, `move_to_header_footer`)
- Text insertion (`write`, `writeln`, `insert_paragraph`)
- Formatting setters (`set_bold`, `set_font_size`, `set_color`, `set_italic`, `set_underline`, `set_alignment`, etc.)
- Table building (`start_table`, `insert_row`, `insert_cell`, `end_row`, `end_table`)
- Bookmark creation (`start_bookmark`, `end_bookmark`)
- Hyperlink insertion (`insert_hyperlink`)
- Image insertion (`insert_image` with auto-size and explicit size)
- Field insertion (`insert_page_number`, `insert_date`, `insert_time`, `insert_num_pages`, `insert_merge_field`, `insert_table_of_contents`)
- Form field insertion (`insert_text_input`, `insert_check_box`, `insert_combo_box`)
- Footnote/endnote insertion (`insert_footnote`, `insert_endnote`)

### 10. DocumentSearch (`advanced.h`)
**Status: Implemented.** `find`, `find_all`, `replace`, `replace_all`, `replace_with_formatting`, and `find_and_process` are functional. The implementation operates at the paragraph level using the DOM. `Range` has a DOM fallback for paragraphs that do not have an XML node binding (common for pure DOM-created paragraphs).

### 11. TableOperations (`advanced.h`)
**Status: Fully implemented.** Static helper methods for common table operations:
- `insert_row`, `append_row`, `delete_row`
- `insert_cell`, `delete_cell`
- `merge_cells_horizontal`
- `set_cell_text`, `get_cell_text`

**Note:** These complement the instance methods on `Table::merge_cells` and `Table::split_cell`.

### 12. CDocx Factory Class (`cdocx.h` / `cdocx.cpp`)
**Status: Fully implemented.** Provides convenient static factory methods:
- `create_document()` — create empty document
- `load_document(path)` — load from file
- `save_document(doc, path)` — save to file
- `paragraph()` / `table()` — standalone node factories

---

## Testing

Test framework: **Google Test**, integrated with **CTest**.

### Test Suites

| Suite | Focus | Data Files | Timeout |
|-------|-------|------------|---------|
| `01_basic` | Basic functionality | `my_test.docx` | 30s |
| `02_iterator` | Iterator tests | `my_test.docx` | 30s |
| `03_template` | Template system | `template.docx`, `main.docx` | 45s |
| `04_xml_parts` | XML Parts API | `my_test.docx` | 30s |
| `05_complete_structure` | Round-trip load/save | `template.docx` | 45s |
| `06_create_empty` | Empty document creation | - | 30s |
| `07_text_formatting` | Formatting tests | - | 30s |
| `08_bookmark_replacement` | Bookmark replacement | - | 60s |
| `09_section_and_list` | Sections and numbering | - | 60s |
| `10_dom_sync` | DOM-XML synchronization | - | 60s |
| `11_table_merge` | Table merge/split/operations | - | 60s |
| `12_document_search` | Document search and replace | - | 60s |
| `13_document_builder` | DocumentBuilder fluent API | - | 60s |
| `14_style_collection` | Style collection management | - | 60s |
| `15_mail_merge` | Mail merge | - | 60s |
| `16_comment_collection` | Comment collection | - | 60s |
| `17_footnote_collection` | Footnote/endnote collection | - | 60s |
| `18_field_switches` | Field switches | - | 60s |
| `19_template_engine` | TemplateEngine unified API | - | 60s |

### Test Labels

Tests are tagged with CTest labels: `core`, `basic`, `iterator`, `advanced`, `template`, `xml`, `formatting`, `section`, `list`, `numbering`.

### Test Helper Macros

The `test/CMakeLists.txt` defines `add_test_suite()` macro that auto-discovers tests. Tests can be either:
- A single `<suite_name>_tests.cpp` file in the suite directory, or
- A `CMakeLists.txt` in the suite directory for multi-file tests

Data files are expected in `<suite>/data/` and copied to the build directory automatically.

---

## CI/CD

GitHub Actions workflows in `.github/workflows/`:

### `cmake.yml`
Builds and tests on every push/PR to `main`/`master`/`develop`:
- **Linux** (ubuntu-latest): GCC and Clang, both Debug and Release
- **Windows** (windows-latest): MSVC 2022, x64, both Debug and Release
- **macOS** (macos-latest): Apple Clang, both Debug and Release

### `code-quality.yml`
Runs on every push/PR:
- **clang-format**: Checks formatting with `--dry-run --Werror`
- **cppcheck**: Static analysis with `--enable=all --error-exitcode=1`

### `docs.yml`
Builds Doxygen documentation on pushes to `main`/`master` that touch `include/`, `src/`, `Doxyfile`, or the workflow itself. Deploys HTML output to GitHub Pages.

---

## Security Considerations

- The library parses user-provided DOCX (ZIP + XML) files. Input validation is performed during ZIP loading and XML parsing.
- `LoadConfig` supports partial loads with `allow_partial_load` and `skip_corrupted_files` for robustness.
- On Windows, `NOMINMAX` and `WIN32_LEAN_AND_MEAN` are defined to minimize Windows.h surface area.
- `_CRT_SECURE_NO_WARNINGS` is defined for portability with C-style file operations in the `zip` dependency.
- No network operations are performed by the library itself.

---

## API Quick Reference

### Legacy Iterator (Fully Working)

```cpp
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    for (auto r = p.runs(); r.has_next(); r.next()) {
        std::string text = r.get_text();
    }
}
```

### DOM Pattern (Complete)

```cpp
auto doc = cdocx::CDocx::create_document();
auto body = doc->get_first_section()->get_body();
auto para = body->append_paragraph("Hello, World!");
para->append_run(" Bold text")
    ->get_font()
    .set_bold(true);
cdocx::CDocx::save_document(*doc, "output.docx");
```

---

## Version History

### v0.8.0 (Current)
- `TemplateEngine` unified dictionary-style template API with text/image placeholders, bookmarks, format policies, action/scope modes
- `BookmarkInserter` for wrapping existing text with bookmarks
- `CommentCollection` for add/get/remove document comments
- `MailMerge` simple field replacement with cleanup options
- `Watermark` text and image watermarks in headers
- `StyleCollection` style management via `doc.styles()`
- Table column insert/delete and `auto_fit` behaviors (`AutoFitToContents`, `AutoFitToWindow`, `FixedColumnWidth`)
- `DocumentBuilder` enhancements: `move_to_bookmark`, `insert_hyperlink`, `insert_image` (auto-size and explicit size), `insert_footnote`/`insert_endnote`
- `FileFormatUtil` file format detection and conversion
- `Section::link_to_previous` / `is_linked_to_previous`
- Field switches support (`FieldSwitch` enum, `parse_field_code_and_switches`)
- Run property default elision (skip writing default `<w:rPr>` to reduce file size)
- `ParagraphBuilder` and `TableBuilder` fluent APIs

### v0.7.0 (Transition)
- DOM class hierarchy introduced (`Node`/`CompositeNode`)
- `document_sync.cpp` handles DOM-XML serialization (paragraphs, tables, sections, bookmarks, fields, hyperlinks)
- `Color` fully implemented; other format classes are header-only structs
- `DocumentSearch` find/replace/find_all/find_and_process
- `TableOperations` static helpers
- `Range` operations
- `CDocx` factory class

### v0.5.0
- Section support (fully working)
- List/Numbering system (fully working)

### v0.4.0
- Bookmark replacement (same-paragraph works)
- Caption generation

### v0.3.0
- Template system
- Document insertion
- XML Parts API

### v0.2.0
- Media management
- Cursor-based DocumentBuilder
- `DocumentSearch` declared (stubs)

### v0.1.0
- Core DOCX operations
- Iterator-based API

---

## Feature Implementation Status

| Feature | Status | Notes |
|---------|--------|-------|
| DOCX open/save/create | Complete | Fully tested |
| Legacy iterator API | Complete | |
| Run/Paragraph formatting | Complete | |
| Template replacement | Complete | `Template` (legacy FSM) and `TemplateEngine` (recommended) |
| Document insertion | Complete | |
| Media management | Complete | Add/delete/replace/export images |
| XML Parts API | Complete | Direct `pugi::xml_document*` access |
| Section support | Complete | Page setup, margins, orientation, headers/footers |
| List/Numbering | Complete | Bulleted, numbered, outline, Chinese numbering |
| Bookmark replacement | Complete | Same-paragraph via `BookmarkReplacer`; multi-run via `BookmarkInserter` |
| DOM node hierarchy | Complete | `clone()`, traversal, append/remove on all major nodes |
| DOM-XML sync | Complete | Run, Para, Table, Section, Bookmark, Hyperlink, Field, Footnote, Comment, Style |
| Table merge/split | Complete | `merge_cells`, `split_cell`, column insert/delete, auto-fit |
| DocumentSearch | Complete | `find`, `find_all`, `replace`, `replace_all`, `replace_with_formatting`, `find_and_process` |
| DocumentBuilder | Complete | Cursor-based API; hyperlinks, images, tables, bookmarks, fields, footnotes |
| TableOperations | Complete | Static helpers for row/cell operations |
| CDocx factory class | Complete | `create_document`, `load_document`, `save_document` |
| StyleCollection | Complete | Style get/create/update |
| CommentCollection | Complete | Add/get/remove comments |
| MailMerge | Complete | Simple field replacement with cleanup |
| Watermark | Complete | Text and image watermarks |
| Footnote/endnote DOM | Basic | `Footnote`/`FootnoteReference` classes exist; collection API roadmap |

---

## License

MIT License - see [LICENSE](LICENSE) file for details.

*This file is intended for AI coding agents. For user documentation, see [README.md](README.md).*
