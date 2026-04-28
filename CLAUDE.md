# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CDocx is a C++17 library for creating, reading, and writing Microsoft Word (.docx) files. It provides a stable legacy iterator-based API and is transitioning toward a DOM-style architecture.

- **Version**: 0.8.0
- **Namespace**: `cdocx`
- **License**: MIT
- **Dependencies**: pugixml (XML), zip (ZIP archives), Google Test (testing) — all auto-fetched via CMake FetchContent from Gitee mirrors

### Workspace Layout

This repository is `cdocx/`. The sibling directory `../tmplateWord/` is an executable application that consumes `cdocx` as a subdirectory dependency for template-based Word document editing.

## Capability Model

When deciding how to implement a feature, use this quick reference.

### Fully Implemented and Stable

- DOCX open/save/create
- Legacy iterator API (`doc.paragraphs()`, `para.runs()`, `doc.tables()`)
- Template replacement (`cdocx::Template`, including headers/footers) via FSM-based processing
- Document insertion (`cdocx::DocumentInserter`)
- Media management (add/delete/replace/export images)
- XML Parts API (`doc.get_styles()`, `doc.get_numbering_xml()`, etc.)
- Section support and List/Numbering (bulleted, numbered, Chinese-numbered, outline)
- Bookmark replacement (same-paragraph bookmarks only) via `cdocx::BookmarkReplacer`
- Bookmark insertion around existing text via `cdocx::BookmarkInserter` (handles text spanning multiple runs in a single paragraph; `insert_batch` sorts by text length descending to prevent substring hiding)
- Run/Paragraph basic and advanced formatting (indentation, spacing, keep together, shading, drop caps)
- DOM node cloning (`clone()`) and document-order traversal (`get_next_node_in_document`, `get_previous_node_in_document`)
- `HeaderFooter` DOM content manipulation (`append_paragraph`, `append_table`, `get_paragraphs`)
- DOM-to-XML serialization/deserialization for runs, paragraphs, tables, sections, bookmarks, hyperlinks, fields, shading, and drop caps
- `DocumentBuilder` fluent chaining, navigation, tables, bookmarks, `move_to_bookmark`, `insert_hyperlink`, `insert_image` (auto-size and explicit size), `insert_footnote` / `insert_endnote`
- `CDocx` factory methods (`create_document`, `load_document`, `save_document`, `document()`, `paragraph()`, `table()`)
- `Document::get_range()` and `Document::ensure_minimum()`
- `ParagraphBuilder` fluent API
- `TableBuilder` fluent API
- `TableOperations` static helpers (`insert_row`, `append_row`, `delete_row`, `insert_cell`, `delete_cell`, `merge_cells_horizontal`, `set_cell_text`, `get_cell_text`)
- Table cell merge/split (`Table::merge_cells`, `split_cell`)
- Table column insert/delete and `auto_fit` behaviors (`AutoFitToContents`, `AutoFitToWindow`, `FixedColumnWidth`)
- `Color` class and hex/RGB conversions
- `ConvertUtil` (points, inches, mm, cm, pixels, twips)
- `ControlChar` constants
- `FileFormatUtil` (file format detection and conversion)
- Section `HeaderFooter` Link-to-Previous (`Section::link_to_previous`, `is_linked_to_previous`)
- `StyleCollection` management via `doc.styles()`
- `DocumentSearch` (find/replace/replace_all at paragraph level)
- `MailMerge` simple field replacement with cleanup options
- `Watermark` text and image watermarks in headers
- `CommentCollection` (add/get/remove comments)
- `FootnoteCollection` / `EndnoteCollection` document-level managers with DOM ↔ XML round-trip sync, including custom reference mark preservation
- `TemplateEngine` unified dictionary-style template API (`engine["key"] = value`, `set()`, `apply()`) supporting text/image placeholders and bookmarks, with format policies, action modes (replace/insert), and scope modes (first/all)

### Stubs / Roadmap Only

Do not assume these are fully implemented:

- Advanced field configuration (custom date formats, page number formats, formula evaluation, etc.) — basic `Field` DOM class and `DocumentBuilder::insert_page_number` / `insert_date` / `insert_time` / `insert_merge_field` / `insert_table_of_contents` exist, but deep customization and DOM ↔ XML round-trip for all field types are limited
- PDF / HTML / Markdown export

### Which API to Use

| Task | Recommended API |
|------|-----------------|
| Build a document from scratch or edit existing content | **DOM API** (`append_paragraph`, `append_run`, `append_table`) |
| Replace placeholders in an existing template | **`TemplateEngine`** (recommended) or **`Template`** / **`BookmarkReplacer`** |
| Merge two documents | **`DocumentInserter`** |
| Modify raw styles, settings, or relationships | **XML Parts API** (`doc.get_styles()`, `doc.get_document_xml()`) |
| Maintain legacy code | **Legacy Iterator API** (`doc.paragraphs()`, `para.runs()`) — do not use for new features |

### TemplateEngine Quick Reference

The `TemplateEngine` class provides a unified, dictionary-style API for template-based document generation. It supports both placeholders (`{{key}}`) and bookmarks, with configurable formatting and action modes.

```cpp
cdocx::TemplateEngine engine(&doc);

// Dictionary-style assignment (supports text, images, and format chains)
engine["name"] = cdocx::TemplateValue::text("John Doe").with_format(
cdocx::TemplateFormat().bold().size(24));
engine["logo"] = cdocx::TemplateValue::image("logo.png").sized(200, 100).centered();
engine["date"] = cdocx::TemplateValue::text("2024-01-15");

// Batch set with shared configuration
engine.set_batch({
    {"company", cdocx::TemplateValue::text("Acme Inc.")},
    {"address", cdocx::TemplateValue::text("123 Main St")}
});

// Configure default behavior
engine.with_action(cdocx::TemplateAction::Replace)   // Replace (default) or Insert
    .with_scope(cdocx::TemplateScope::All)            // All (default) or First
    .with_format_policy(cdocx::FormatPolicy::Preserve) // Preserve, Override, or Custom
    .with_delimiters("{{", "}}");

// Execute all replacements
auto result = engine.apply();
// result.success = count of successful replacements
// result.failed  = count of failed replacements
```

**Action modes:**
- `Replace` — replaces the placeholder/bookmark content (default)
- `Insert` — inserts content before the placeholder (keeps marker) or after the bookmark start (preserves existing content)

**Scope modes:**
- `All` — replaces all occurrences (default)
- `First` — stops after the first successful replacement

**Format policies:**
- `Preserve` — keeps the original format of the bookmarked text
- `Override` — applies the format specified in `TemplateValue`
- `Custom` — uses `TemplateFormat` builders; falls back to `Preserve` if empty

**Target auto-resolution:**
When a key is set without an explicit target, `TemplateEngine` auto-detects whether it should be treated as a bookmark or placeholder based on whether a matching bookmark exists in the document.

## Build, Test, and Quality Commands

### CDocx (Library)

```bash
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTING=ON
cmake --build . --parallel
```

Build options: `BUILD_SHARED_LIBS`, `BUILD_EXAMPLES`, `BUILD_TESTING`, `BUILD_DOCS`, `ENABLE_COVERAGE`, `ENABLE_WERROR`, `USE_SYSTEM_GTEST`.

### tmplateWord (Application)

```bash
cd ../tmplateWord
mkdir build && cd build
cmake ..
cmake --build .
```

`tmplateWord` adds `cdocx` as a subdirectory dependency automatically. Template and data files are copied to the build directory at configure time.

### Test

```bash
# Run all tests
ctest --output-on-failure

# Run labeled subsets
cmake --build build --target test_all      # all tests
cmake --build build --target test_core     # core only
cmake --build build --target test_quick    # quick smoke tests
cmake --build build --target test_template # template tests
cmake --build build --target test_advanced # advanced features
```

Tests live in `test/01_basic/` through `test/19_template_engine/`. The `test/CMakeLists.txt` macro `add_test_suite()` auto-discovers either a single `<suite>_tests.cpp` or a subdirectory `CMakeLists.txt`. Data files go in `<suite>/data/` and are copied to the build directory automatically.

| Suite | Description |
|-------|-------------|
| `01_basic` | Base read/write |
| `02_iterator` | Legacy iterator API |
| `03_template` | Template replacement |
| `04_xml_parts` | XML Parts API |
| `05_complete_structure` | Full structure validation |
| `06_create_empty` | Empty document creation |
| `07_text_formatting` | Text/paragraph formatting (includes DropCap) |
| `08_bookmark_replacement` | Bookmark replacement |
| `09_section_and_list` | Section / List / Link-to-Previous |
| `10_dom_sync` | DOM/XML synchronization |
| `11_table_merge` | Table merge/split/operations |
| `12_document_search` | Document search and replace |
| `13_document_builder` | DocumentBuilder (includes FileFormatUtil / Shading) |
| `14_style_collection` | Style collection |
| `15_mail_merge` | Mail merge |
| `16_comment_collection` | Comment collection |
| `17_footnote_collection` | Footnote/endnote collection |
| `18_field_switches` | Field switches |
| `19_template_engine` | TemplateEngine (placeholder + bookmark, text + image, replace/insert, first/all scope) |

### Code Quality

```bash
# Format (in-place)
cmake --build build --target format

# Format check (CI)
cmake --build build --target format-check

# Static analysis
cmake --build build --target tidy

# Auto-fix tidy issues
cmake --build build --target tidy-fix

# Run all checks
cmake --build build --target code-quality
```

A convenience wrapper is also available: `scripts/code-quality.sh [format|format-check|tidy|tidy-fix|all]`.

## Code Style

Customized Google C++ Style Guide:

- **Indentation**: 4 spaces
- **Line width**: 100 characters
- **Header guards**: `#pragma once`
- **Types**: `CamelCase`
- **Functions/Methods**: `snake_case`
- **Variables**: `snake_case`
- **Member variables**: `snake_case_`
- **Constants**: `kCamelCase`

## High-Level Architecture

### Two Coexisting APIs

1. **Legacy Iterator API** (fully working): `doc.paragraphs()`, `para.runs()`, `doc.tables()` — cursor-style iteration with `has_next()` / `next()`.
2. **DOM API** (in transition): `Node` / `CompositeNode` hierarchy with `append_child()`, `get_body()`, `append_paragraph()`, etc.

### Core Layers

- **Public headers**: `include/cdocx.h` (aggregated), `include/cdocx/*.h` (modular)
- **Implementation**: `src/*.cpp` — notably `document.cpp`, `document_sync.cpp` (DOM-to-XML serialization), `impl.cpp` (PIMPL internals), `paragraph.cpp`, `table.cpp`, `section.cpp`
- **Private detail**: `include/detail/impl.h` holds `DocumentImpl` (PIMPL)
- **Physical model**: `DocxTree` / `DocxTreeNode` (in `document.h`) mirrors the ZIP package structure. XML parts are parsed into `pugi::xml_document` nodes inside the tree.
- **Whitespace preservation**: All XML load sites use `pugi::parse_ws_pcdata` in addition to `pugi::parse_default` so that whitespace-only `<w:t>` nodes (e.g. `xml:space="preserve"> </w:t>`) are not dropped. This is critical for accurate text reconstruction in `BookmarkInserter` and for preserving document formatting across open/save cycles.
- **Property preservation for round-trip fidelity**: DOM nodes preserve raw XML fragments that are not fully modeled by the DOM:
  - `Inline::preserved_rPr_` — preserves the complete `<w:rPr>` of each run, including properties not mapped to `Font` fields (e.g. `w:noProof`, `w:bCs`, `w:position`).
  - `Paragraph::preserved_p_pr_` — preserves the complete `<w:pPr>`.
  - `Table::preserved_tbl_pr_` / `Table::preserved_tbl_grid_` — preserves table properties and column grid.
  - `Style::preserved_style_xml_` — preserves style metadata outside the DOM model.
  When serializing back to XML, these preserved fragments are used as the base instead of regenerating properties from scratch. This ensures that documents opened and saved by cdocx retain properties that Word authored but cdocx does not yet model.
- **Whitespace text node filtering**: When parsing runs from XML (`parse_run_from_xml`), whitespace text nodes (`node_pcdata`) inside `<w:r>` are skipped when collecting preserved children. This prevents pretty-printed indentation from being incorrectly preserved as run children, which would break run-merging logic downstream.

### DOM Hierarchy

```
Node (abstract)
├── CompositeNode
│   ├── Document → contains Sections
│   ├── Section  → contains Body, HeaderFooter refs
│   ├── Body     → contains Paragraphs, Tables
│   ├── Paragraph → contains Runs
│   ├── Table    → contains Rows
│   ├── Row      → contains Cells
│   └── Cell     → contains Paragraphs
└── Leaf nodes (Run, SpecialChar, etc.)
```

### Adding a New Source File

Source files in `src/` are auto-collected via `file(GLOB_RECURSE)` in `CMakeLists.txt`; you do not need to edit the build file to add a `.cpp` in `src/`. However, new public headers in `include/cdocx/` may need to be included in `include/cdocx.h` if they are part of the aggregated API.

Examples in `examples/` and tests in `test/` are also auto-discovered by their respective `CMakeLists.txt` files. `cmake/modules/CDocxHelpers.cmake` provides macros such as `add_cdocx_test`, `add_cdocx_example`, and `add_cdocx_executable`.

### Examples

Example programs live in `examples/`. Each subdirectory should contain `main.cpp` and optionally a `data/` directory. Build all examples with `cmake --build build --target examples`.

## Common Implementation Patterns

When refactoring or extending cdocx, prefer these established patterns:

### Enum↔String Mapping via Lookup Tables

Replace large `switch` / `if-else` chains with static lookup arrays. Examples across the codebase:
- `src/properties.cpp`: `kBorderTypeMappings[]`, `kUnderlineStyleMappings[]`, `kFontHintMappings[]`, `kVertAlignMappings[]`
- `src/base_content.cpp`: `kPositionTypeMappings[]`, `kSpacingSignMappings[]`, `kPositionScriptMappings[]`
- `src/sync_common.cpp`: `kParagraphAlignmentMappings[]`, `kTableAlignmentMappings[]`, `kHighlightMappings[]`
- `src/document_builder.cpp`: `kBreakTypeMappings[]`
- `src/paragraph.cpp`: `kBreakCharMappings[]`
- `src/section.cpp`: `kOrientationMappings[]`
- `src/sync_style.cpp`: `kStyleTypeMappings[]`, `kFontBoolFlagMappings[]`

This reduces code volume and makes additions a single-line change.

### Extract Static Helpers in Anonymous Namespaces

Recurring patterns across the codebase are extracted as file-local static functions or templates:
- `parse_content_children()` in `document_sync.cpp` — unifies paragraph/table parsing loops for body, header/footer, and table cells.
- `get_settings_root()` in `document.cpp` — centralizes `word/settings.xml` root node access for `protect`, `unprotect`, `is_protected`, `get/set_default_tab_stop`.
- `collect_text_from_runs()` in `advanced.cpp` — centralizes text extraction from `<w:r>` runs within a paragraph, used by `Bookmark`, `Range`, and `DocumentBuilder`.
- `apply_formatting_flags()` in `paragraph.cpp` — unifies formatting flag application for `add_run` and `add_run_with_bookmark`.
- `append_id_node<T>()` in `sync_deserialize.cpp` — template helper for creating DOM nodes with `w:id` assignment (BookmarkEnd, CommentRangeStart, CommentRangeEnd, FootnoteReference, EndnoteReference).
- `serialize_id_node_to_xml<T>()` in `sync_serialize.cpp` — template helper for serializing id-only DOM nodes to XML.
- `serialize_footnote_reference_to_xml()` / `serialize_endnote_reference_to_xml()` in `sync_serialize.cpp` — dedicated serializers extracted from inline XML generation.
- `create_empty_*` helpers in `document.cpp` — each XML part for an empty DOCX (`[Content_Types].xml`, `_rels/.rels`, `word/document.xml`, etc.) has its own static helper. `create_empty_document()` reads as a 13-line recipe.
- `link_hf_to_previous()` in `section.cpp` — unifies header and footer `link_to_previous` logic by parameterizing over refs vector, collection vector, XML tag names, part prefix, relationship type, and `is_header` flag.

### Field Sequence Walking

Field parsing (bookmarks, form fields, regular fields) follows a uniform walker pattern: `walk_field_sequence()` advances from `w:fldChar[begin]` through `w:fldChar[separate]` to `w:fldChar[end]`, collecting `instrText` before the separator and `result` text after it. Switch extraction is handled by `parse_field_code_and_switches()`.

### `Document::get_bookmarks()` Performance

`get_bookmarks()` syncs the DOM to the physical XML tree but **no longer rebuilds the DOM** on every call. This means:
- DOM references (`Paragraph*`, `Section*`, etc.) remain valid across `get_bookmarks()` calls.
- If you modified the physical XML directly (e.g., via `BookmarkInserter`), call `sync_from_physical_tree()` before DOM operations so the DOM sees those changes.
- `BookmarkCollection::add()` still handles its own sync internally.

### Empty Paragraph Placeholder Removal

`create_empty()` creates a minimal DOCX with a single empty paragraph placeholder (one `<w:p>` containing one empty `<w:r>`). This placeholder exists so that the legacy iterator API has an initial paragraph to work with.

`Body::append_paragraph()` automatically removes this placeholder when it is the sole unmodified content in the body:
- Trigger: body has exactly 1 child, it is a Paragraph, that paragraph has exactly 1 child which is a Run, and the paragraph's text is empty.
- Effect: the placeholder is removed before the new paragraph is appended.
- This means DOM users get clean documents with no leading empty paragraph, while legacy API users still have a paragraph to iterate on when no content has been added yet.

### Physical XML Manipulation Lifecycle

Some APIs modify the physical XML tree directly instead of going through the DOM:
- `BookmarkInserter` — inserts `w:bookmarkStart` / `w:bookmarkEnd` into physical XML.
- Direct `pugi::xml_node` manipulation via `doc.get_document_xml()`.

Because `Document::save()` calls `sync_to_physical_tree()`, which regenerates the physical body from the DOM, any physical-only changes will be **lost** unless the DOM is rebuilt first. After using physical manipulation APIs, call `sync_from_physical_tree()` before `save()` to capture the changes into the DOM.

```cpp
cdocx::BookmarkInserter inserter(&doc);
inserter.insert("NAME", "value");
doc.sync_from_physical_tree();  // Required before save()
doc.save("output.docx");
```

### Property Preservation during DOM Round-Trip

When adding new DOM-modeled properties, always preserve the original XML fragment (e.g. `preserved_rPr_`, `preserved_p_pr_`) so that unmodeled sibling attributes survive serialization. Remove only the explicitly managed children before re-adding them from DOM state. See `serialize_run_formatting_to_xml` for the canonical pattern.

### Run Property Default Elision

`serialize_run_formatting_to_xml` skips writing `<w:rPr>` entirely when a run's font matches the document defaults (`size=12`, `name="Times New Roman"`, `color=black`). Empty `<w:rPr/>` nodes are also removed after serialization. This prevents the ~200 bytes of redundant default rPr that previously appeared on every unformatted run.
