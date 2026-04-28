# CDocx API 使用示例

> **版本说明**：本文档基于 **v0.8.0** 实际已实现 API 编写，所有标注为"可用"的接口均已在 `.cpp` 中有完整实现，可直接使用。
>
> **已实现的 DOM API（v0.8.0）**：`Document::open/save/clone`、`CDocx::create_document/load_document/save_document`、`get_body`、`append_paragraph`、`append_run`、`append_table`、`get_rows/get_cells`、`set_text`、`Section::add_header/footer/ensure_header/ensure_footer/clone`、`Paragraph::clone`、`Paragraph::append_hyperlink` / `append_page_number` / `append_date` / `append_time` / `append_merge_field`、`Table::clone`、`Row::clone`、`Cell::clone`、`BookmarkStart/End`、`Field`（序列化/反序列化）、`Hyperlink`（序列化/反序列化）、`Node::get_next_node_in_document` / `get_previous_node_in_document`、`HeaderFooter::append_paragraph` / `append_table` / `get_paragraphs`、基础 `Font`/`ParagraphFormat` 设置、`DocumentSearch::find` / `find_all` / `replace` / `replace_all` / `replace_with_formatting` / `find_and_process`、`Table::auto_fit` / `insert_column` / `delete_column`、`TableOperations` 静态辅助方法、`TemplateEngine` 统一模板引擎、`DocumentBuilder`（含 `insert_hyperlink`、`insert_image`、`start_bookmark`/`end_bookmark`）、`CommentCollection`、`MailMerge`、`Watermark`、`StyleCollection`。

## 概述

CDocx v2.0 采用全新的 DOM 风格 API，灵感来自 Aspose.Words，更加直观易用。

---

## 1. 文档操作

### 创建新文档

```cpp
#include <cdocx.h>

// 方式1: 使用 CDocx 工厂方法 (推荐，v0.8.0+)
auto doc = cdocx::CDocx::create_document();

// 方式2: 直接构造并创建空文档
cdocx::Document doc;
doc.create_empty("output.docx");

// 方式3: 从文件加载
cdocx::Document doc("input.docx");
doc.open();

// 方式4: 使用 CDocx 工厂加载
auto doc = cdocx::CDocx::load_document("input.docx");
```

### 保存文档

```cpp
// 保存到新文件
doc->save("output.docx");

// 覆盖原文件
doc->save();

// 使用 CDocx 工厂保存
cdocx::CDocx::save_document(*doc, "output.docx");
```

---

## 2. 段落操作

### 创建段落

```cpp
// 添加段落
auto para = doc->get_body()->append_paragraph();

// 添加带文本的段落
auto para = doc->get_body()->append_paragraph("Hello, World!");

// 添加多个段落
for (int i = 0; i < 5; ++i) {
    doc->get_body()->append_paragraph("Paragraph " + std::to_string(i));
}
```

### 段落格式

```cpp
auto para = doc->get_body()->append_paragraph("Formatted paragraph");

// 对齐方式
para->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;

// 缩进
para->get_paragraph_format().left_indent = 36;      // 0.5 inch
para->get_paragraph_format().first_line_indent = 24; // 首行缩进

// 间距
para->get_paragraph_format().space_before = 12;  // points
para->get_paragraph_format().space_after = 12;

// 行距
para->get_paragraph_format().set_line_spacing(1.5);  // 1.5倍行距
para->get_paragraph_format().set_line_spacing(20, cdocx::LineSpacingRule::Exact); // 固定20磅

// 分页控制
para->get_paragraph_format().keep_with_next = true;
para->get_paragraph_format().page_break_before = true;
```

### 遍历段落

```cpp
// 遍历所有段落
for (auto& para : doc->get_paragraphs()) {
    std::cout << para.get_text() << std::endl;
}

// 遍历正文中的段落
for (auto& para : doc->get_body()->get_paragraphs()) {
    // 处理段落
}

// 使用索引
auto paras = doc->get_paragraphs();
if (paras.get_count() > 0) {
    auto first = paras[0];
    auto last = paras.last();
}
```

### 段落便捷方法 (v0.8.0+)

```cpp
auto para = doc->get_body()->append_paragraph();

// 插入超链接
para->append_hyperlink("访问示例", "https://example.com");

// 插入书签链接
para->append_hyperlink("跳转到第一章", "chapter1", true);

// 插入页码字段
para->append_page_number("\\* ROMAN");

// 插入日期字段（带格式开关）
para->append_date("\\@ \"yyyy-MM-dd\"");

// 插入时间字段
para->append_time("\\@ \"HH:mm:ss\"");

// 插入 MERGEFIELD
para->append_merge_field("Name", "\\* Upper");
```

---

## 3. 文本格式 (Run)

### 创建格式化的文本

```cpp
auto para = doc->get_body()->append_paragraph();

// 普通文本
para->append_run("Normal text");

// 粗体
para->append_run(" Bold text")
    ->set_bold(true);

// 链式调用
para->append_run(" Bold and red")
    ->set_bold(true)
    .set_color(cdocx::Color::red());

// 多种格式
auto run = para->append_run(" Complex formatting");
run->set_bold(true)
    .set_italic(true)
    .set_underline(cdocx::UnderlineType::Single)
    .set_size(14)
    .set_name("Arial")
    .set_color(cdocx::Color::from_hex("0070C0"));
```

### 字体设置

```cpp
auto run = para->append_run("Text");
auto& font = run->get_font();

// 字体名称
font.name = "Times New Roman";
font.set_names("Arial", "微软雅黑");  // ASCII, 中文

// 字号 (points)
font.size = 12;
font.size = 14.5;

// 颜色
font.color = cdocx::Color::red();
font.color = cdocx::Color::from_hex("FF0000");
font.color = cdocx::Color(255, 0, 0);

// 格式
font.bold = true;
font.italic = true;
font.set_underline(cdocx::UnderlineType::Single);
font.strike = cdocx::StrikeType::Single;
font.double_strike = true;

// 脚本位置
font.script_type = cdocx::ScriptType::Superscript;
font.script_type = cdocx::ScriptType::Subscript;

// 高亮
font.highlight = cdocx::HighlightColor::Yellow;

// 小型大写字母
font.small_caps = true;
font.all_caps = true;
```

---

## 4. 表格操作

### 创建表格

```cpp
// 简单表格
auto table = doc->get_body()->append_table(3, 4);  // 3行4列

// 带表头的表格
auto table = doc->get_body()->append_table(4, 3);
table->get_row(0)->get_row_format().set_heading(true);
```

### 填充数据

```cpp
auto table = doc->get_body()->append_table(3, 3);

// 填充表头
auto header_row = table->get_row(0);
header_row->get_cell(0)->set_text("Name");
header_row->get_cell(1)->set_text("Age");
header_row->get_cell(2)->set_text("City");

// 设置表头格式
for (auto& cell : header_row->get_cells()) {
    cell->get_first_paragraph()
        ->append_run(cell->get_text())
        ->set_bold(true);
    cell->get_cell_format()
        .set_shading(cdocx::Shading().set_solid_fill(cdocx::Color::light_gray()));
}

// 填充数据
std::vector<std::vector<std::string>> data = {
    {"John", "30", "New York"},
    {"Jane", "25", "London"}
};

for (size_t row = 0; row < data.size(); ++row) {
    for (size_t col = 0; col < data[row].size(); ++col) {
        table->get_cell(row + 1, col)->set_text(data[row][col]);
    }
}
```

### 表格格式

```cpp
auto table = doc->get_body()->append_table(3, 3);

// 对齐
table->get_table_format().alignment = cdocx::TableAlignment::Center;

// 自动调整 (v0.8.0+)
table->auto_fit(cdocx::AutoFitBehavior::AutoFitToWindow);
table->auto_fit(cdocx::AutoFitBehavior::AutoFitToContents);
table->auto_fit(cdocx::AutoFitBehavior::FixedColumnWidth);

// 边框 (通过 TableFormat)
cdocx::TableFormat fmt;
fmt.borders.set_all(cdocx::Border(cdocx::BorderType::Single, cdocx::Color::black(), 4));
table->set_table_format(fmt);

// 单元格边框
auto cell = table->get_cell(0, 0);
cell->get_cell_format().borders.set_all(
    cdocx::Border(cdocx::BorderType::Double, cdocx::Color::red(), 6)
);
```

### 合并单元格

```cpp
auto table = doc->get_body()->append_table(4, 4);

// 水平合并
table->merge_cells(0, 0, 0, 1);  // 合并第0行第0-1列

// 垂直合并
table->merge_cells(1, 0, 2, 0);  // 合并第1-2行第0列

// 合并区域
table->merge_cells(1, 1, 2, 2);  // 合并从(1,1)到(2,2)的区域

// 拆分已合并的单元格
table->split_cell(table->get_cell(0, 0), 1, 2);  // 拆为1行2列

// 通过单元格合并
auto cell1 = table->get_cell(0, 0);
auto cell2 = table->get_cell(0, 1);
cell1->merge_with(cell2);
```

### 行列操作

```cpp
auto table = doc->get_body()->append_table(3, 3);

// 插入列 (v0.8.0+)
table->insert_column(1);

// 删除列 (v0.8.0+)
table->delete_column(2);

// 使用 TableOperations 静态辅助方法
#include <cdocx/advanced.h>
cdocx::TableOperations::insert_row(*table, 1);   // 在第1行前插入行
cdocx::TableOperations::append_row(*table);       // 末尾添加行
cdocx::TableOperations::delete_row(*table, 0);    // 删除第0行
cdocx::TableOperations::set_cell_text(*table->get_cell(0, 0), "Hello");
```

### 遍历表格

```cpp
// 遍历所有表格
for (auto& table : doc->get_tables()) {
    std::cout << "Table: " << table.get_row_count() 
              << "x" << table.get_column_count() << std::endl;
}

// 遍历行和单元格
for (auto& row : table->get_rows()) {
    for (auto& cell : row->get_cells()) {
        std::cout << cell->get_text() << "\t";
    }
    std::cout << std::endl;
}
```

---

## 5. 字段 (Fields)

### 页码

```cpp
// 在页脚添加页码
auto footer = doc->get_first_section()->add_footer(
    cdocx::HeaderFooterType::Primary
);
auto para = footer->append_paragraph();
para->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;

para->append_run("Page ");

// 使用 DocumentBuilder 插入页码字段
#include <cdocx/advanced.h>
cdocx::DocumentBuilder builder(doc.get());
builder.move_to_header_footer(cdocx::HeaderFooterType::Primary);
builder.insert_page_number();
```

### 日期和时间

```cpp
// 使用 DocumentBuilder 插入日期/时间字段
#include <cdocx/advanced.h>
cdocx::DocumentBuilder builder(doc.get());

// 日期
builder.insert_date("yyyy-MM-dd");

// 时间
builder.insert_time("HH:mm:ss");

// 页数
builder.insert_num_pages();
```

### 超链接

```cpp
auto para = doc->get_body()->append_paragraph();

// 方式1: 使用 DocumentBuilder (推荐)
#include <cdocx/advanced.h>
cdocx::DocumentBuilder builder(doc.get());
builder.insert_hyperlink("Visit Example.com", "https://example.com");

// 方式2: 直接创建 Hyperlink 节点并添加到段落
auto link_para = doc->get_body()->append_paragraph();
auto hyperlink = std::make_shared<cdocx::Hyperlink>();
hyperlink->set_result("Click here");
hyperlink->set_address("https://example.com");
link_para->append_child(hyperlink);
```

---

## 6. 书签

### 创建书签

```cpp
// 方式1: 使用 DocumentBuilder (推荐)
#include <cdocx/advanced.h>
cdocx::DocumentBuilder builder(doc.get());
builder.start_bookmark("Section1");
builder.writeln("This is section 1");
builder.end_bookmark("Section1");

// 方式2: 手动添加书签节点
auto para = doc->get_body()->append_paragraph();

auto bm_start = std::make_shared<cdocx::BookmarkStart>();
bm_start->set_name("Section2");
para->append_child(bm_start);

para->append_run("This is section 2");

auto bm_end = std::make_shared<cdocx::BookmarkEnd>();
bm_end->set_name("Section2");
para->append_child(bm_end);
```

### 书签替换

```cpp
#include <cdocx/bookmark_replacer.h>

cdocx::BookmarkReplacer replacer(doc.get());

// 检查书签是否存在
if (replacer.has_bookmark("TITLE")) {
    // 简单文本替换（保留原格式）
    replacer.replace_text("TITLE", "New Title");

    // 带自定义格式的替换
    cdocx::BookmarkFormat fmt;
    fmt.bold = true;
    fmt.font_size = 36;
    fmt.color = "0066CC";
    replacer.replace_text_with_format("TITLE", "Formatted Title", fmt);

    // 图片替换
    replacer.replace_with_image("LOGO", "logo.png", "Company Logo");
}

// 批量替换
std::map<std::string, std::string> data = {
    {"NAME", "John Doe"},
    {"DATE", "2024-01-15"}
};
replacer.replace_text_batch(data);
```

### 在现有文本周围插入书签

```cpp
#include <cdocx/bookmark_inserter.h>

// 在已打开的文档中，围绕匹配的文本插入书签
cdocx::BookmarkInserter inserter(doc.get());
inserter.insert("AUTHOR", "John Smith");
inserter.insert("SIGNATURE", "__SIGN__");

// BookmarkInserter 直接修改物理 XML，保存前需要同步
doc->sync_from_physical_tree();
doc->save("output.docx");
```

---

## 7. 分节和页面设置

### 添加分节

```cpp
// 添加新节
auto section = doc->add_section();

// 添加内容到新节
section->get_body()->append_paragraph("Content in new section");
```

### 页面设置

```cpp
auto section = doc->get_first_section();
auto& props = section->get_properties();

// 页面大小
props.page_size.width = 12240;   // A4 width in twips
props.page_size.height = 15840;  // A4 height in twips

// 方向
props.orientation = cdocx::SectionProperties::Orientation::Landscape;

// 边距 (单位: twips, 1 inch = 1440 twips)
props.page_margins.top = 1440;
props.page_margins.bottom = 1440;
props.page_margins.left = 1440;
props.page_margins.right = 1440;
```

### 页眉页脚

```cpp
auto section = doc->get_first_section();

// 添加页眉
auto header = section->add_header(cdocx::HeaderFooterType::Primary);
header->append_paragraph("Header Text");

// 添加页脚
auto footer = section->add_footer(cdocx::HeaderFooterType::Primary);
footer->append_paragraph("Footer Text");

// 确保页眉存在（存在则返回，不存在则创建）
auto h = section->ensure_header();  // 等价于 get_header() ?? add_header()
h->append_paragraph("Safe header");

// 确保页脚存在
auto f = section->ensure_footer();
f->append_paragraph("Safe footer");

// 链接到前一节（取消独立页眉页脚）
section->link_to_previous(cdocx::HeaderFooterType::Primary, true);
```

---

## 8. 样式

### 应用样式

```cpp
auto para = doc->get_body()->append_paragraph("Heading 1");
para->set_style(cdocx::StyleIdentifier::Heading1);

// 或使用样式名称
para->set_style("Heading1");
```

### 样式集合管理

```cpp
// 获取样式集合
auto& styles = doc->styles();

// 遍历所有样式
for (auto& style : styles) {
    std::cout << style->get_name() << std::endl;
}

// 按名称查找样式
auto style = styles.get_by_name("Normal");
if (style) {
    std::cout << "Found style: " << style->get_name() << std::endl;
}
```

---

## 9. 遍历和搜索

### 使用访问者模式

```cpp
class TextExtractor : public cdocx::DocumentVisitor {
    std::string text_;
public:
    void visit_run(cdocx::Run& run) override {
        text_ += run.get_text();
    }

    void visit_paragraph_end(cdocx::Paragraph& para) override {
        text_ += "\n";
    }

    std::string get_text() const { return text_; }
};

TextExtractor extractor;
doc->accept(&extractor);
std::cout << extractor.get_text() << std::endl;
```

### 查找文本

```cpp
#include <cdocx/advanced.h>

// 查找第一次出现
auto range = cdocx::DocumentSearch::find(*doc, "search term");
if (range) {
    std::cout << "Found: " << range->get_text() << std::endl;
}

// 查找所有出现位置
auto ranges = cdocx::DocumentSearch::find_all(*doc, "search term");
std::cout << "Found " << ranges.size() << " occurrence(s)" << std::endl;

// 替换第一次出现
bool replaced = cdocx::DocumentSearch::replace(*doc, "old", "new");

// 替换所有出现
int count = cdocx::DocumentSearch::replace_all(*doc, "old", "new");

// 替换并应用格式（粗体）
cdocx::DocumentSearch::replace_with_formatting(
    *doc, "warning", "WARNING",
    static_cast<cdocx::FormattingFlag>(cdocx::kBold)
);

// 查找并处理（回调）
cdocx::DocumentSearch::find_and_process(*doc, "TODO",
    [](const std::string& found_text, cdocx::Range& range) {
        std::cout << "Found task: " << range.get_text() << std::endl;
        return true; // 返回 false 可提前终止搜索
    }
);
```

---

## 10. 完整示例

### 生成报告

```cpp
#include <cdocx.h>
#include <cdocx/advanced.h>
#include <iostream>

int main() {
    // 创建文档
    auto doc = cdocx::CDocx::create_document();
    auto body = doc->get_first_section()->get_body();

    // 添加标题
    auto title = body->append_paragraph("Sales Report 2024");
    title->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Center;
    title->get_first_run()->get_font().size = 36;  // 18pt
    title->get_first_run()->get_font().bold = true;

    // 添加说明段落
    auto intro = body->append_paragraph(
        "This report summarizes the sales performance for the year 2024. "
        "It includes data from all regional offices and product categories."
    );
    intro->get_paragraph_format().first_line_indent = 480;  // 0.5 inch in twips
    intro->get_paragraph_format().space_after = 240;       // 12pt in twips

    // 添加小标题
    auto section_title = body->append_paragraph("Quarterly Sales");
    section_title->get_first_run()->get_font().bold = true;
    section_title->get_first_run()->get_font().size = 28;  // 14pt

    // 创建数据表格
    auto table = body->append_table(5, 4);
    table->get_table_format().alignment = cdocx::TableAlignment::Center;

    // 表头
    std::vector<std::string> headers = {"Quarter", "Revenue", "Expenses", "Profit"};
    for (size_t i = 0; i < headers.size(); ++i) {
        auto cell = table->get_cell(0, i);
        cell->set_text(headers[i]);
        cell->get_cell_format().shading.background_color = cdocx::Color(68, 114, 196);
        auto run = cell->get_first_paragraph()->append_run(headers[i]);
        run->get_font().bold = true;
        run->get_font().color = cdocx::Color::white();
    }

    // 数据行
    std::vector<std::vector<std::string>> data = {
        {"Q1", "$100,000", "$60,000", "$40,000"},
        {"Q2", "$120,000", "$65,000", "$55,000"},
        {"Q3", "$110,000", "$62,000", "$48,000"},
        {"Q4", "$140,000", "$70,000", "$70,000"}
    };

    for (size_t row = 0; row < data.size(); ++row) {
        for (size_t col = 0; col < data[row].size(); ++col) {
            table->get_cell(row + 1, col)->set_text(data[row][col]);
        }
    }

    // 添加页眉
    auto header = doc->get_first_section()->add_header(
        cdocx::HeaderFooterType::Primary
    );
    auto header_para = header->append_paragraph("Confidential - Sales Report");
    header_para->get_paragraph_format().alignment = cdocx::ParagraphAlignment::Right;

    // 添加页脚（使用 DocumentBuilder 插入页码字段）
    auto footer = doc->get_first_section()->add_footer(
        cdocx::HeaderFooterType::Primary
    );
    cdocx::DocumentBuilder builder(doc.get());
    builder.move_to_header_footer(cdocx::HeaderFooterType::Primary);
    // 注意：需要区分 header/footer 上下文，此处展示基本用法

    // 保存
    cdocx::CDocx::save_document(*doc, "sales_report.docx");
    std::cout << "Report generated successfully!" << std::endl;

    return 0;
}
```

---

## 11. TemplateEngine 模板引擎（推荐）

`TemplateEngine` 是 CDocx 提供的统一字典风格模板 API，支持占位符（`{{key}}`）和书签两种目标类型，可配置格式化、作用域和行为模式。

### 基础文本替换

```cpp
#include <cdocx.h>

int main() {
    cdocx::Document doc("template.docx");
    doc.open();

    cdocx::TemplateEngine engine(&doc);

    // 字典风格赋值
    engine["company"] = cdocx::TemplateValue::text("Acme Inc.");
    engine["date"]    = "2026-04-24";
    engine["title"]   = cdocx::TemplateValue::text("年度报告")
        .with_format(cdocx::TemplateFormat().bold().size(24));

    // 执行替换
    auto result = engine.apply();
    // result.success = 成功替换数
    // result.failed  = 失败数
    // result.skipped = 跳过数

    doc.save("output.docx");
    return 0;
}
```

### 图片替换

```cpp
engine["logo"] = cdocx::TemplateValue::image("logo.png")
    .sized(200, 100)
    .centered();
```

### 书签替换

```cpp
// TemplateEngine 会自动检测目标类型：
// - 如果文档中存在同名书签，则替换书签内容
// - 否则查找 {{key}} 占位符
engine["AUTHOR"]    = cdocx::TemplateValue::text("张三");
engine["SIGNATURE"] = cdocx::TemplateValue::text("已批准");
```

### 批量设置

```cpp
// 批量设置文本值
std::map<std::string, std::string> data = {
    {"company", "Acme Inc."},
    {"address", "北京市朝阳区"},
    {"phone",   "010-12345678"}
};
engine.set_batch(data);

// 批量设置包含图片的混合值
std::map<std::string, cdocx::TemplateValue> mixed = {
    {"company", cdocx::TemplateValue::text("Acme Inc.")},
    {"logo",    cdocx::TemplateValue::image("logo.png").sized(200, 100)}
};
engine.set_batch(mixed);
```

### 高级配置

```cpp
auto result = engine
    .with_action(cdocx::TemplateAction::Replace)      // Replace（替换内容）或 Insert（插入内容）
    .with_scope(cdocx::TemplateScope::All)             // All（全部）或 First（仅首个）
    .with_format_policy(cdocx::FormatPolicy::Preserve) // Preserve（保留原格式）/ Override / Custom
    .with_delimiters("{{", "}}")                        // 自定义占位符分隔符
    .apply();
```

### 使用模板分析器自动生成代码

CDocx 提供 Python 工具 `tools/template_analyzer/analyze_template.py`，可自动分析 `.docx` 文件中的模板元素并生成**可直接编译运行的 C++ 程序**。

**生成完整程序（默认）：**

```bash
python tools/template_analyzer/analyze_template.py template.docx -o fill_template.cpp
```

生成的 `fill_template.cpp` 是一个完整的 C++17 程序，包含 `main()` 函数和所有模板替换代码。只需修改其中的字符串值，编译运行即可：

```cpp
// 生成的代码示例
int main() {
    cdocx::Document doc("template.docx");
    doc.open();

    cdocx::TemplateEngine engine(&doc);

    // ===== 直接在这里修改数据 =====
    engine[TemplateKeys::company_name] = cdocx::TemplateValue::text("Acme Inc.");
    engine[TemplateKeys::date]        = cdocx::TemplateValue::text("2026-04-24");
    engine[TemplateKeys::title]       = cdocx::TemplateValue::text("年度报告");
    // =============================

    auto result = engine.apply();
    doc.save("output.docx");
    return 0;
}
```

**使用步骤：**
1. 运行分析器生成 `.cpp`
2. 修改 `.cpp` 中的赋值字符串
3. 编译：`g++ -std=c++17 fill_template.cpp -lcdocx -o fill_template`
4. 运行：`./fill_template`

**生成头文件模式（可选）：**

```bash
python tools/template_analyzer/analyze_template.py template.docx -o template_keys.h --mode header
```

生成只含常量的头文件，适合集成到现有项目中：

```cpp
#pragma once
#include <cdocx.h>

namespace TemplateKeys {
    inline constexpr const char* company_name = "company_name";
    inline constexpr const char* date         = "date";
    inline constexpr const char* title        = "title";
}
```

完整工具文档请见 `tools/template_analyzer/README.md`。

---

## API 对比：旧版 vs 新版

| 操作 | 旧版 API (Legacy Iterator) | 新版 API (DOM) |
|-----|---------|---------|
| 创建文档 | `Document doc("file.docx"); doc.create_empty();` | `auto doc = cdocx::CDocx::create_document();` |
| 添加段落 | `doc.paragraphs().add_run("text");` | `doc->get_body()->append_paragraph("text");` |
| 设置对齐 | `para.set_alignment("center");` | `para->get_paragraph_format().alignment = ParagraphAlignment::Center;` |
| 设置字体 | `run.set_font_name("Arial");` | `run->get_font().name = "Arial";` |
| 添加表格 | `doc.tables().add(3, 4);` | `doc->get_body()->append_table(3, 4);` |
| 获取单元格 | `table.cell_at(row, col)` | `table->get_cell(row, col)` |
| 保存 | `doc.save();` | `cdocx::CDocx::save_document(*doc, "file.docx");` |

新版 API 更加类型安全、直观，并且支持链式调用。

## 12. 其他高级功能

### 文档插入 (DocumentInserter)

```cpp
#include <cdocx/inserter.h>

cdocx::DocumentInserter inserter(doc.get());
inserter.insert_document_at_end("other.docx");
```

### 邮件合并 (MailMerge)

```cpp
#include <cdocx/mail_merge.h>

cdocx::MailMerge merger(doc.get());
merger.set_field("Name", "John Doe");
merger.set_field("Date", "2024-01-15");
merger.execute();
```

### 水印 (Watermark)

```cpp
#include <cdocx/watermark.h>

// 文字水印
cdocx::Watermark::add_text_watermark(*doc, "CONFIDENTIAL", cdocx::Color::gray(), 72);

// 图片水印
cdocx::Watermark::add_image_watermark(*doc, "watermark.png");
```

### 批注 (CommentCollection)

```cpp
// 添加批注
auto comment = doc->get_comments()->add("Author Name", "This needs revision.");

// 遍历批注
for (auto& c : *doc->get_comments()) {
    std::cout << c->get_author() << ": " << c->get_text() << std::endl;
}
```

### 脚注和尾注 (FootnoteCollection / EndnoteCollection)

```cpp
// 添加脚注
auto footnotes = doc->footnotes();
auto fn = footnotes.add("This is a footnote text.");

// 添加带自定义引用标记的脚注
auto fn2 = footnotes.add("See also page 12.", "*");

// 遍历脚注
for (const auto& f : footnotes) {
    std::cout << "[" << f->get_id() << "] " << f->get_text() << std::endl;
}

// 删除脚注
footnotes.remove(fn->get_id());

// 尾注与脚注 API 完全一致
auto endnotes = doc->endnotes();
auto en = endnotes.add("This is an endnote.");
```

### 表单字段 (FormField)

```cpp
#include <cdocx/advanced.h>

cdocx::DocumentBuilder builder(doc.get());

// 文本输入框
builder.write("姓名: ");
builder.insert_text_input("Name", cdocx::TextFormFieldType::Regular,
                          "", "请输入姓名", 50);
builder.writeln();

// 数字输入框
builder.write("年龄: ");
builder.insert_text_input("Age", cdocx::TextFormFieldType::Number,
                          "", "0", 10);
builder.writeln();

// 复选框
builder.write("同意条款: ");
builder.insert_check_box("Agree", true, 10);
builder.writeln();

// 下拉框
std::vector<std::string> options = {"选项 A", "选项 B", "选项 C"};
builder.write("选择: ");
builder.insert_combo_box("Selection", options, 0);
builder.writeln();
```
