# CDocx 功能增强实现计划

## 1. 阶段 1: 核心功能完善

### 1.1 页面设置模块

#### 设计目标
实现完整的页面设置功能，包括页面大小、方向、边距、页眉页脚距离等。

#### API 设计
```cpp
// include/cdocx/page_setup.h
#pragma once

#include <cdocx/fwd.h>
#include <string>

namespace cdocx {

enum class PageSize {
    LETTER,      // 8.5" x 11"
    LEGAL,       // 8.5" x 14"
    A4,          // 210mm x 297mm
    A5,          // 148mm x 210mm
    B4,          // 250mm x 353mm
    B5,          // 176mm x 250mm
    CUSTOM
};

enum class Orientation {
    PORTRAIT,
    LANDSCAPE
};

struct Margins {
    double left = 1440;    // twips (1 inch = 1440 twips)
    double right = 1440;
    double top = 1440;
    double bottom = 1440;
    double header = 720;   // 0.5 inch
    double footer = 720;
    double gutter = 0;
};

class PageSetup {
public:
    // Page size
    void set_page_size(PageSize size);
    PageSize get_page_size() const;
    void set_page_width(double width);   // in points
    void set_page_height(double height); // in points
    double get_page_width() const;
    double get_page_height() const;
    
    // Orientation
    void set_orientation(Orientation orientation);
    Orientation get_orientation() const;
    
    // Margins (in points)
    void set_margins(const Margins& margins);
    Margins get_margins() const;
    void set_left_margin(double margin);
    void set_right_margin(double margin);
    void set_top_margin(double margin);
    void set_bottom_margin(double margin);
    
    // Header/Footer distance
    void set_header_distance(double distance);
    void set_footer_distance(double distance);
    
    // Page borders
    void set_page_borders(const BorderCollection& borders);
    
    // Section settings
    void set_different_first_page(bool value);
    void set_different_odd_even_pages(bool value);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace cdocx
```

#### 使用示例
```cpp
#include <cdocx.h>
#include <cdocx/page_setup.h>

int main() {
    cdocx::Document doc;
    doc.create_empty("output.docx");
    
    // Get page setup
    auto& page_setup = doc.get_page_setup();
    
    // Set A4 landscape
    page_setup.set_page_size(cdocx::PageSize::A4);
    page_setup.set_orientation(cdocx::Orientation::LANDSCAPE);
    
    // Set custom margins (in points: 72 points = 1 inch)
    cdocx::Margins margins;
    margins.left = 72 * 1.5;    // 1.5 inches
    margins.right = 72 * 1.5;
    margins.top = 72 * 1.0;     // 1 inch
    margins.bottom = 72 * 1.0;
    page_setup.set_margins(margins);
    
    doc.save();
    return 0;
}
```

### 1.2 列表支持

#### API 设计
```cpp
// include/cdocx/lists.h
#pragma once

#include <cdocx/fwd.h>
#include <string>
#include <vector>

namespace cdocx {

enum class ListType {
    BULLET,           // •
    NUMBER,           // 1, 2, 3
    LETTER_LOWER,     // a, b, c
    LETTER_UPPER,     // A, B, C
    ROMAN_LOWER,      // i, ii, iii
    ROMAN_UPPER,      // I, II, III
    CUSTOM
};

enum class NumberAlignment {
    LEFT,
    CENTER,
    RIGHT
};

class ListLevel {
public:
    void set_number_format(ListType type);
    void set_start_number(int start);
    void set_number_alignment(NumberAlignment alignment);
    void set_text_indent(double indent);      // in points
    void set_number_position(double position); // in points
    void set_tab_position(double position);    // in points
    void set_font(const Font& font);
    void set_number_style(const std::string& style);  // "%1." or "(%1)" etc.
};

class List {
public:
    ListType get_type() const;
    
    // Level management (0-8 levels supported)
    ListLevel& get_level(int level);
    void set_level(int level, const ListLevel& list_level);
    
    // Apply to paragraph
    void apply_to(Paragraph& paragraph, int level = 0);
};

class ListCollection {
public:
    List& add(ListType type);
    List& add_bullet(const std::string& character = "•");
    List& add_numbered(int start = 1);
    void remove(List& list);
    
    List& get(int index);
    size_t count() const;
};

// Paragraph extension
class Paragraph {
public:
    // Existing methods...
    
    // List methods
    void set_list_format(List& list, int level = 0);
    void remove_list_format();
    bool is_in_list() const;
    int get_list_level() const;
    
    // Increment/Decrement list level
    void increase_indent();
    void decrease_indent();
};

} // namespace cdocx
```

#### 使用示例
```cpp
#include <cdocx.h>
#include <cdocx/lists.h>

int main() {
    cdocx::Document doc;
    doc.create_empty("list_demo.docx");
    
    // Create a bullet list
    auto& lists = doc.get_lists();
    auto& bullet_list = lists.add_bullet("•");
    
    // Create numbered list
    auto& numbered_list = lists.add_numbered(1);
    
    // Add paragraphs with list formatting
    auto para = doc.paragraphs();
    
    // Item 1
    para.insert_paragraph_after("First bullet item");
    para.set_list_format(bullet_list, 0);
    para.next();
    
    // Item 2 (nested)
    para.insert_paragraph_after("Nested item");
    para.set_list_format(bullet_list, 1);
    para.next();
    
    // Item 3
    para.insert_paragraph_after("Second bullet item");
    para.set_list_format(bullet_list, 0);
    
    doc.save();
    return 0;
}
```

### 1.3 表格增强

#### API 设计
```cpp
// include/cdocx/tables_enhanced.h
#pragma once

#include <cdocx/fwd.h>
#include <string>

namespace cdocx {

enum class AutoFitBehavior {
    AUTO_FIT_TO_WINDOW,   // Fit to window width
    AUTO_FIT_TO_CONTENTS, // Fit to cell contents
    FIXED_COLUMN_WIDTH    // Fixed column widths
};

enum class CellMerge {
    NONE,
    FIRST,  // First cell in merge
    PREVIOUS  // Continuation of merge
};

enum class VerticalMerge {
    NONE,
    FIRST,
    PREVIOUS
};

class TableBorders {
public:
    void set_top(const Border& border);
    void set_bottom(const Border& border);
    void set_left(const Border& border);
    void set_right(const Border& border);
    void set_inside_horizontal(const Border& border);
    void set_inside_vertical(const Border& border);
    void set_all(const Border& border);
};

class Shading {
public:
    void set_color(const std::string& hex_color);     // Background color
    void set_pattern(const std::string& pattern);      // Clear, solid, etc.
    void set_pattern_color(const std::string& hex_color);
};

class CellFormat {
public:
    // Margins
    void set_left_padding(double padding);
    void set_right_padding(double padding);
    void set_top_padding(double padding);
    void set_bottom_padding(double padding);
    
    // Vertical alignment
    void set_vertical_alignment(CellVerticalAlignment alignment);
    
    // Merge
    void set_horizontal_merge(CellMerge merge);
    void set_vertical_merge(VerticalMerge merge);
    
    // Borders
    void set_borders(const TableBorders& borders);
    
    // Shading
    void set_shading(const Shading& shading);
    
    // Preferred width
    void set_preferred_width(double width, bool is_percent = false);
    
    // Text direction
    void set_text_direction(TextDirection direction);
};

class Table {
public:
    // Existing methods...
    
    // Merge cells
    Cell& merge_cells(Cell& start_cell, Cell& end_cell);
    void unmerge_cells(Cell& cell);
    
    // Auto fit
    void set_auto_fit(AutoFitBehavior behavior);
    void auto_fit_to_window();
    void auto_fit_to_contents();
    void set_fixed_column_widths();
    
    // Borders
    void set_borders(const TableBorders& borders);
    TableBorders get_borders() const;
    
    // Shading
    void set_shading(const Shading& shading);
    
    // Table properties
    void set_alignment(TableAlignment alignment);
    void set_allow_auto_fit(bool allow);
    void set_repeat_header_rows(int count);  // Repeat header on each page
    
    // Table style
    void set_style(const TableStyle& style);
};

class Cell {
public:
    // Existing methods...
    
    // Format
    CellFormat& get_format();
    
    // Merge
    bool is_merged() const;
    bool is_first_merged() const;
    Cell& get_merge_start();
    
    // Split
    std::vector<Cell> split(int rows, int columns);
};

} // namespace cdocx
```

## 2. 阶段 2: 导出功能

### 2.1 PDF 导出

#### 技术选型
推荐方案：**libharu** (开源) 或 **wkhtmltopdf** (HTML 中间转换)

#### API 设计
```cpp
// include/cdocx/export/pdf_export.h
#pragma once

#include <cdocx/fwd.h>
#include <string>

namespace cdocx {

enum class PdfCompliance {
    PDF_1_4,
    PDF_1_5,
    PDF_1_6,
    PDF_1_7,
    PDF_A_1A,
    PDF_A_1B,
    PDF_A_2A,
    PDF_A_2B
};

enum class PdfCompression {
    NONE,
    NORMAL,
    HIGH
};

class PdfSaveOptions {
public:
    // PDF version
    void set_compliance(PdfCompliance compliance);
    PdfCompliance get_compliance() const;
    
    // Fonts
    void set_embed_fonts(bool embed);
    void set_embed_standard_fonts(bool embed);
    void set_subset_fonts(bool subset);
    
    // Compression
    void set_compression(PdfCompression compression);
    void set_compress_images(bool compress);
    void set_jpeg_quality(int quality);  // 0-100
    
    // Security
    void set_password(const std::string& password);
    void set_owner_password(const std::string& password);
    void set_permissions(uint32_t permissions);
    
    // Page settings
    void set_page_range(int start_page, int end_page);
    void set_export_page_setup(bool export_setup);
    
    // Metadata
    void set_export_document_properties(bool export_props);
    void set_export_custom_properties(bool export_props);
    
    // Bookmarks
    void set_create_bookmarks(bool create);
    void set_headings_bookmarks(bool use_headings);
};

class PdfExporter {
public:
    static bool export_to(const Document& doc, 
                          const std::string& output_path,
                          const PdfSaveOptions& options = PdfSaveOptions());
    
    static std::vector<uint8_t> export_to_memory(
                          const Document& doc,
                          const PdfSaveOptions& options = PdfSaveOptions());
};

// Document extension
class Document {
public:
    // Existing methods...
    
    // Save as PDF
    void save(const std::string& path, const PdfSaveOptions& options);
    
    // Export methods
    bool export_to_pdf(const std::string& path, 
                       const PdfSaveOptions& options = PdfSaveOptions());
};

} // namespace cdocx
```

### 2.2 HTML 导出

#### API 设计
```cpp
// include/cdocx/export/html_export.h
#pragma once

#include <cdocx/fwd.h>
#include <string>
#include <functional>

namespace cdocx {

enum class HtmlVersion {
    HTML_4_01,
    HTML_5,
    XHTML
};

enum class CssStyleSheetType {
    INLINE,       // style="..."
    EMBEDDED,     // <style>...</style>
    EXTERNAL      // <link rel="stylesheet">
};

enum class ImageExportMode {
    EMBEDDED_BASE64,  // data:image/png;base64,...
    EXTERNAL_FILES,   // Separate image files
    CUSTOM_HANDLER    // Custom callback
};

class HtmlSaveOptions {
public:
    // HTML version
    void set_html_version(HtmlVersion version);
    
    // CSS handling
    void set_css_style_sheet_type(CssStyleSheetType type);
    void set_css_class_name_prefix(const std::string& prefix);
    
    // Image handling
    void set_image_export_mode(ImageExportMode mode);
    void set_image_folder(const std::string& folder);
    void set_image_handler(std::function<std::string(const ImageData&)> handler);
    
    // Content options
    void set_export_headers_footers(bool export);
    void set_export_page_setup(bool export_setup);
    void set_export_relative_font_size(bool relative);
    void set_export_text_box_as_svg(bool as_svg);
    
    // Font handling
    void set_export_font_resources(bool export_fonts);
    void set_font_resources_subfolder(const std::string& subfolder);
    
    // Table of contents
    void set_update_toc_page_numbers(bool update);
};

class HtmlExporter {
public:
    static bool export_to(const Document& doc,
                          const std::string& output_path,
                          const HtmlSaveOptions& options = HtmlSaveOptions());
    
    static std::string export_to_string(
                          const Document& doc,
                          const HtmlSaveOptions& options = HtmlSaveOptions());
};

} // namespace cdocx
```

## 3. 阶段 3: 高级功能

### 3.1 域 (Field) 系统

#### API 设计
```cpp
// include/cdocx/fields.h
#pragma once

#include <cdocx/fwd.h>
#include <string>
#include <chrono>

namespace cdocx {

enum class FieldType {
    // Page reference
    PAGE,           // Current page number
    NUM_PAGES,      // Total pages
    PAGE_REF,       // Reference to bookmarked page
    
    // Date/Time
    DATE,           // Current date
    TIME,           // Current time
    CREATE_DATE,    // Document creation date
    SAVE_DATE,      // Last save date
    PRINT_DATE,     // Last print date
    
    // Document properties
    AUTHOR,
    TITLE,
    SUBJECT,
    KEYWORDS,
    COMMENTS,
    
    // Links
    HYPERLINK,      // URL or bookmark link
    REF,            // Bookmark reference
    
    // Table of contents
    TOC,            // Table of contents
    TC,             // TOC entry
    
    // Mail merge
    MERGEFIELD,
    NEXT,
    NEXT_IF,
    SKIPIF,
    
    // Index
    INDEX,
    XE,             // Index entry
    
    // Other
    IF,
    COMPARE,
    FILENAME,
    FILESIZE,
    MACRO_BUTTON,
    
    UNKNOWN
};

class Field {
public:
    FieldType get_type() const;
    std::string get_type_name() const;
    
    // Field code
    std::string get_field_code() const;
    void set_field_code(const std::string& code);
    
    // Field result
    std::string get_result() const;
    void set_result(const std::string& result);
    
    // Update
    void update();
    bool is_locked() const;
    void set_locked(bool locked);
};

class FieldPage : public Field {
public:
    void set_number_format(const std::string& format);
};

class FieldHyperlink : public Field {
public:
    void set_url(const std::string& url);
    void set_bookmark_name(const std::string& name);
    void set_sub_address(const std::string& sub_address);
    void set_screen_tip(const std::string& tip);
    void set_target_frame(const std::string& frame);
};

class FieldDate : public Field {
public:
    void set_date_format(const std::string& format);
    std::chrono::system_clock::time_point get_date() const;
};

class FieldToc : public Field {
public:
    // TOC options
    void set_heading_levels(int min_level, int max_level);
    void set_show_page_numbers(bool show);
    void set_right_align_page_numbers(bool align);
    void set_leader_type(const std::string& leader);  // "-", ".", "_"
    void set_hide_in_web_layout(bool hide);
    
    // Update TOC
    void update();
};

class FieldCollection {
public:
    size_t count() const;
    Field& get(int index);
    
    template<typename T>
    T& get_as(int index) { return dynamic_cast<T&>(get(index)); }
    
    void remove(Field& field);
    void update_all();
    void unlink_all();  // Convert to static text
};

// DocumentBuilder extension
class DocumentBuilder {
public:
    // Existing methods...
    
    // Insert fields
    Field& insert_field(FieldType type);
    Field& insert_field(const std::string& field_code);
    
    // Specific field types
    FieldPage& insert_page_number();
    FieldPage& insert_num_pages();
    FieldDate& insert_date(const std::string& format = "MM/dd/yyyy");
    FieldDate& insert_time(const std::string& format = "HH:mm:ss");
    
    FieldHyperlink& insert_hyperlink(const std::string& text,
                                      const std::string& url);
    FieldHyperlink& insert_bookmark_link(const std::string& text,
                                          const std::string& bookmark);
    
    FieldToc& insert_table_of_contents();
    FieldToc& insert_table_of_contents(const std::string& switches);
    
    // Document property fields
    Field& insert_doc_property(FieldType type);
};

// Document extension
class Document {
public:
    // Existing methods...
    
    FieldCollection& get_fields();
    void update_fields();
    
    // Evaluate all IF fields
    void evaluate_if_fields();
};

} // namespace cdocx
```

### 3.2 注释/批注

#### API 设计
```cpp
// include/cdocx/comments.h
#pragma once

#include <cdocx/fwd.h>
#include <string>
#include <chrono>
#include <vector>

namespace cdocx {

class Comment {
public:
    int get_id() const;
    
    // Author info
    void set_author(const std::string& author);
    std::string get_author() const;
    void set_author_initials(const std::string& initials);
    std::string get_author_initials() const;
    
    // Content
    void set_text(const std::string& text);
    std::string get_text() const;
    void add_paragraph(const std::string& text);
    
    // Timestamp
    void set_date_time(const std::chrono::system_clock::time_point& time);
    std::chrono::system_clock::time_point get_date_time() const;
    
    // Range
    Range get_range() const;
    void set_range(const Range& range);
    
    // Done state
    void set_done(bool done);
    bool is_done() const;
    
    // Replies
    Comment& add_reply(const std::string& text);
    std::vector<Comment> get_replies() const;
    Comment& get_parent_comment() const;
    bool is_reply() const;
    
    // Remove
    void remove();
};

class CommentCollection {
public:
    Comment& add(const Range& range, const std::string& text);
    Comment& add(const Range& range, const std::string& text, 
                 const std::string& author);
    Comment& add(const Range& range, const std::string& text,
                 const std::string& author, const std::string& initials);
    
    Comment& get(int index);
    Comment& get_by_id(int id);
    
    size_t count() const;
    void remove(Comment& comment);
    void remove_all();
    
    // Filter
    std::vector<Comment> get_by_author(const std::string& author);
};

// Document extension
class Document {
public:
    // Existing methods...
    
    CommentCollection& get_comments();
    
    // Show/hide comments
    void show_comments(bool show);
    bool are_comments_shown() const;
};

} // namespace cdocx
```

## 4. 实现时间表

### 4.1 开发计划

| 阶段 | 功能 | 估计工时 | 开始时间 | 完成时间 |
|------|------|----------|----------|----------|
| **阶段 1** | 核心功能完善 | | | |
| 1.1 | 页面设置 (PageSetup) | 40h | Week 1 | Week 2 |
| 1.2 | 列表支持 (Lists) | 60h | Week 2 | Week 4 |
| 1.3 | 表格增强 (Table enhancements) | 80h | Week 3 | Week 6 |
| 1.4 | 页眉页脚 (Headers/Footers) | 60h | Week 5 | Week 7 |
| **阶段 2** | 导出功能 | | | |
| 2.1 | PDF 导出 (PDF export) | 120h | Week 7 | Week 11 |
| 2.2 | HTML 导出 (HTML export) | 80h | Week 10 | Week 13 |
| 2.3 | 图片渲染 (Image rendering) | 60h | Week 12 | Week 15 |
| **阶段 3** | 高级功能 | | | |
| 3.1 | 域系统 (Fields) | 100h | Week 15 | Week 19 |
| 3.2 | 超链接 (Hyperlinks) | 40h | Week 18 | Week 20 |
| 3.3 | 注释/批注 (Comments) | 60h | Week 19 | Week 22 |
| 3.4 | 脚注/尾注 (Footnotes) | 60h | Week 21 | Week 24 |
| **阶段 4** | 专业功能 | | | |
| 4.1 | 样式系统 (Styles) | 100h | Week 24 | Week 28 |
| 4.2 | 邮件合并增强 (Mail merge) | 80h | Week 27 | Week 31 |
| 4.3 | 目录生成 (TOC) | 60h | Week 30 | Week 33 |
| 4.4 | 文档比较 (Document comparison) | 80h | Week 32 | Week 36 |

### 4.2 依赖关系图

```
PageSetup
    └── Headers/Footers
        └── PDF Export
            └── HTML Export

Lists
    └── TOC (Table of Contents)

Table Enhancements
    └── PDF Export
    └── HTML Export

Fields
    ├── Hyperlinks
    ├── Page Numbers
    └── TOC

Styles
    ├── Table Styles
    ├── Paragraph Styles
    └── TOC
```

## 5. 测试策略

### 5.1 单元测试

每个功能模块需要以下测试：

```cpp
TEST_CASE("PageSetup - Set page size") {
    Document doc;
    doc.create_empty();
    
    auto& page_setup = doc.get_page_setup();
    page_setup.set_page_size(PageSize::A4);
    page_setup.set_orientation(Orientation::LANDSCAPE);
    
    CHECK(page_setup.get_page_size() == PageSize::A4);
    CHECK(page_setup.get_orientation() == Orientation::LANDSCAPE);
}

TEST_CASE("Lists - Create bullet list") {
    Document doc;
    doc.create_empty();
    
    auto& lists = doc.get_lists();
    auto& list = lists.add_bullet("•");
    
    auto para = doc.paragraphs();
    para.insert_paragraph_after("Item 1");
    para.set_list_format(list, 0);
    
    CHECK(para.is_in_list());
    CHECK(para.get_list_level() == 0);
}

TEST_CASE("PDF Export - Export simple document") {
    Document doc;
    doc.create_empty();
    
    auto para = doc.paragraphs();
    para.insert_paragraph_after("Hello PDF");
    
    PdfSaveOptions options;
    options.set_compliance(PdfCompliance::PDF_1_5);
    
    CHECK_NOTHROW(doc.save("output.pdf", options));
    CHECK(std::filesystem::exists("output.pdf"));
}
```

### 5.2 集成测试

- 完整文档流程测试
- 跨格式往返测试 (DOCX → PDF → 验证)
- 大文件性能测试

## 6. 文档计划

每个功能需要同步更新：

1. **API 文档** (Doxygen 注释)
2. **使用指南** (Markdown)
3. **示例代码** (examples/)
4. **单元测试** (test/)

---

## 附录: 推荐第三方库

| 功能 | 库 | 许可证 | 链接 |
|------|----|----|------|
| PDF 生成 | libharu | Zlib | https://github.com/libharu/libharu |
| PDF 解析 | PoDoFo | LGPL | https://github.com/podofo/podofo |
| 图像处理 | stb_image | Public Domain | https://github.com/nothings/stb |
| 字体渲染 | FreeType | FTL | https://freetype.org/ |
| HTML/CSS | Gumbo | Apache 2.0 | https://github.com/google/gumbo-parser |
| 正则表达式 | RE2 | BSD | https://github.com/google/re2 |
| 日期/时间 | date | MIT | https://github.com/HowardHinnant/date |
