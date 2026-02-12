# CDocx v2.0 API 使用示例

## 概述

CDocx v2.0 采用全新的 DOM 风格 API，灵感来自 Aspose.Words，更加直观易用。

---

## 1. 文档操作

### 创建新文档

```cpp
#include <cdocx.h>

// 方式1: 使用工厂方法
auto doc = cdocx::Document::create();

// 方式2: 直接构造
cdocx::Document doc;

// 方式3: 从文件加载
auto doc = cdocx::Document::load_from_file("input.docx");
```

### 保存文档

```cpp
// 保存到新文件
doc->save("output.docx");

// 覆盖原文件
doc->save();

// 保存到流
std::ofstream stream("output.docx", std::ios::binary);
doc->save(stream);
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
para->get_paragraph_format().set_alignment(cdocx::ParagraphAlignment::Center);

// 缩进
para->get_paragraph_format().set_left_indent(36);      // 0.5 inch
para->get_paragraph_format().set_first_line_indent(24); // 首行缩进

// 间距
para->get_paragraph_format().set_space_before(12);  // points
para->get_paragraph_format().set_space_after(12);

// 行距
para->get_paragraph_format().set_line_spacing(1.5);  // 1.5倍行距
para->get_paragraph_format().set_line_spacing(20, cdocx::LineSpacingRule::Exact); // 固定20磅

// 分页控制
para->get_paragraph_format().set_keep_with_next(true);
para->get_paragraph_format().set_page_break_before(true);
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

---

## 3. 文本格式 (Run)

### 创建格式化的文本

```cpp
auto para = doc->get_body()->append_paragraph();

// 普通文本
para->append_run("Normal text");

// 粗体
para->append_run(" Bold text")
    ->get_font()
    .set_bold(true);

// 链式调用
para->append_run(" Bold and red")
    ->get_font()
    .set_bold(true)
    .set_color(cdocx::Color::red());

// 多种格式
auto run = para->append_run(" Complex formatting");
run->get_font()
    .set_bold(true)
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
font.set_name("Times New Roman");
font.set_names("Arial", "微软雅黑");  // ASCII, 中文

// 字号 (points)
font.set_size(12);
font.set_size(14.5);

// 颜色
font.set_color(cdocx::Color::red());
font.set_color(cdocx::Color::from_hex("FF0000"));
font.set_color(cdocx::Color(255, 0, 0));

// 格式
font.set_bold(true);
font.set_italic(true);
font.set_underline(cdocx::UnderlineType::Single);
font.set_strike(cdocx::StrikeType::Single);
font.set_double_strike(true);

// 脚本位置
font.set_script_type(cdocx::ScriptType::Superscript);
font.set_script_type(cdocx::ScriptType::Subscript);

// 高亮
font.set_highlight(cdocx::HighlightColor::Yellow);

// 小型大写字母
font.set_small_caps(true);
font.set_all_caps(true);
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
        ->get_font()
        .set_bold(true);
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
table->get_table_format().set_alignment(cdocx::TableAlignment::Center);

// 自动调整
table->auto_fit(cdocx::AutoFitBehavior::AutoFitToWindow);
table->auto_fit(cdocx::AutoFitBehavior::AutoFitToContents);
table->auto_fit(cdocx::AutoFitBehavior::FixedColumnWidth);

// 边距
table->get_table_format().set_padding(5);  // 所有边
table->get_table_format().set_padding(10, 5);  // 上下, 左右

// 边框
cdocx::Borders borders;
borders.set_all(cdocx::Border::single(cdocx::Color::black(), 1));
table->get_table_format().set_borders(borders);

// 单元格边框
auto cell = table->get_cell(0, 0);
cell->get_cell_format().get_borders().set_outside(
    cdocx::Border::double_border(cdocx::Color::red(), 1.5)
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

// 通过单元格合并
auto cell1 = table->get_cell(0, 0);
auto cell2 = table->get_cell(0, 1);
cell1->merge_with(cell2);
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
auto footer = doc->get_first_section()->ensure_footer(
    cdocx::HeaderFooterType::Primary
);
auto para = footer->append_paragraph();
para->get_paragraph_format().set_alignment(cdocx::ParagraphAlignment::Center);

para->append_run("Page ");
para->append_page_number();
para->append_run(" of ");
para->append_num_pages();
```

### 日期和时间

```cpp
auto para = doc->get_body()->append_paragraph("Created: ");

// 日期
para->append_date("yyyy-MM-dd");

// 时间
para->append_run(" at ");
para->append_time("HH:mm:ss");

// 创建日期 (文档属性)
para->append_run("\nDocument created: ");
para->append_field(cdocx::FieldType::CreateDate);
```

### 超链接

```cpp
auto para = doc->get_body()->append_paragraph();

// 网页链接
para->append_hyperlink("Visit Example.com", "https://example.com");

// 书签链接
para->append_hyperlink("Go to Summary", "SummaryBookmark", true);

// 格式化链接
auto hyperlink = para->append_hyperlink("Click here", "https://example.com");
hyperlink->get_font()
    .set_color(cdocx::Color::blue())
    .set_underline(cdocx::UnderlineType::Single);
```

### 文档属性字段

```cpp
auto para = doc->get_body()->append_paragraph();

para->append_run("Author: ");
para->append_field(cdocx::FieldType::Author);

para->append_run("\nTitle: ");
para->append_field(cdocx::FieldType::Title);

para->append_run("\nSubject: ");
para->append_field(cdocx::FieldType::Subject);
```

---

## 6. 书签

### 创建书签

```cpp
auto para = doc->get_body()->append_paragraph();

// 书签开始
para->append_bookmark_start("Section1");

// 书签内容
para->append_run("This is section 1");

// 书签结束
para->append_bookmark_end("Section1");

// 便捷方法：包含文本的书签
para->append_bookmark_range("Section2", "This is section 2");
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
auto& page_setup = section->get_page_setup();

// 页面大小
page_setup.set_a4();
page_setup.set_letter();
page_setup.set_page_size(612, 792);  // Letter in points

// 方向
page_setup.orientation = cdocx::PageSetup::Orientation::Landscape;

// 边距
page_setup.set_margins(72);  // 1 inch all around
page_setup.set_margins(72, 54);  // 上下, 左右
page_setup.left_margin = 90;
page_setup.right_margin = 90;

// 页眉页脚距离
page_setup.header_distance = 36;
page_setup.footer_distance = 36;
```

### 页眉页脚

```cpp
auto section = doc->get_first_section();

// 添加页眉
auto header = section->ensure_header(cdocx::HeaderFooterType::Primary);
header->append_paragraph("Header Text");

// 添加页脚
auto footer = section->ensure_footer(cdocx::HeaderFooterType::Primary);
footer->append_paragraph("Footer Text");

// 删除页眉页脚
section->remove_header(cdocx::HeaderFooterType::Primary);
section->remove_footer(cdocx::HeaderFooterType::Primary);
```

---

## 8. 样式

### 应用样式

```cpp
auto para = doc->get_body()->append_paragraph("Heading 1");
para->get_paragraph_format().set_style_name("Heading1");

// 使用枚举
para->get_paragraph_format().set_style(cdocx::StyleIdentifier::Heading1);
```

### 创建自定义样式

```cpp
// 获取或创建样式
auto style = doc->get_style("CustomHeading");
if (!style) {
    style = std::make_shared<cdocx::Style>("CustomHeading", cdocx::StyleType::Paragraph);
    doc->add_style(style);
}

// 配置样式
style->get_font()
    .set_name("Arial")
    .set_size(16)
    .set_bold(true)
    .set_color(cdocx::Color::blue());

style->get_paragraph_format()
    .set_space_before(12)
    .set_space_after(6);

// 应用样式
para->get_paragraph_format().set_style_name("CustomHeading");
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
// 查找所有包含特定文本的段落
auto paras = doc->get_paragraphs();
for (auto& para : paras) {
    if (para.get_text().find("search term") != std::string::npos) {
        // 找到匹配
    }
}

// 查找并替换
for (auto& para : doc->get_paragraphs()) {
    std::string text = para.get_text();
    size_t pos = 0;
    while ((pos = text.find("old", pos)) != std::string::npos) {
        text.replace(pos, 3, "new");
        pos += 3;
    }
    para.set_text(text);
}
```

---

## 10. 完整示例

### 生成报告

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    // 创建文档
    auto doc = cdocx::Document::create();
    
    // 设置文档属性
    doc->get_built_in_properties().title = "Sales Report";
    doc->get_built_in_properties().author = "John Doe";
    
    // 添加标题
    auto title = doc->get_body()->append_paragraph("Sales Report 2024");
    title->get_paragraph_format()
        .set_alignment(cdocx::ParagraphAlignment::Center)
        .set_style(cdocx::StyleIdentifier::Title);
    
    // 添加日期
    auto date_para = doc->get_body()->append_paragraph("Report Date: ");
    date_para->append_date("MMMM dd, yyyy");
    date_para->get_paragraph_format().set_alignment(cdocx::ParagraphAlignment::Center);
    
    // 添加说明段落
    auto intro = doc->get_body()->append_paragraph(
        "This report summarizes the sales performance for the year 2024. "
        "It includes data from all regional offices and product categories."
    );
    intro->get_paragraph_format()
        .set_first_line_indent(24)
        .set_space_after(12);
    
    // 添加小标题
    auto section_title = doc->get_body()->append_paragraph("Quarterly Sales");
    section_title->get_paragraph_format()
        .set_style(cdocx::StyleIdentifier::Heading1);
    
    // 创建数据表格
    auto table = doc->get_body()->append_table(5, 4);
    table->get_table_format().set_alignment(cdocx::TableAlignment::Center);
    
    // 表头
    std::vector<std::string> headers = {"Quarter", "Revenue", "Expenses", "Profit"};
    for (size_t i = 0; i < headers.size(); ++i) {
        auto cell = table->get_cell(0, i);
        cell->set_text(headers[i]);
        cell->get_cell_format()
            .set_shading(cdocx::Shading().set_solid_fill(cdocx::Color(68, 114, 196)));
        cell->get_first_paragraph()->append_run(headers[i])
            ->get_font()
            .set_bold(true)
            .set_color(cdocx::Color::white());
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
    auto header = doc->get_first_section()->ensure_header(
        cdocx::HeaderFooterType::Primary
    );
    header->append_paragraph("Confidential - Sales Report")
        ->get_paragraph_format()
        .set_alignment(cdocx::ParagraphAlignment::Right);
    
    // 添加页脚
    auto footer = doc->get_first_section()->ensure_footer(
        cdocx::HeaderFooterType::Primary
    );
    auto footer_para = footer->append_paragraph();
    footer_para->get_paragraph_format().set_alignment(cdocx::ParagraphAlignment::Center);
    footer_para->append_run("Page ");
    footer_para->append_page_number();
    footer_para->append_run(" of ");
    footer_para->append_num_pages();
    
    // 保存
    doc->save("sales_report.docx");
    std::cout << "Report generated successfully!" << std::endl;
    
    return 0;
}
```

---

## API 对比：旧版 vs 新版

| 操作 | 旧版 API | 新版 API |
|-----|---------|---------|
| 创建文档 | `Document doc("file.docx"); doc.create_empty();` | `auto doc = Document::create();` |
| 添加段落 | `doc.paragraphs().add_run("text");` | `doc->get_body()->append_paragraph("text");` |
| 设置对齐 | `para.set_alignment("center");` | `para->get_paragraph_format().set_alignment(ParagraphAlignment::Center);` |
| 设置字体 | `run.set_font_name("Arial");` | `run->get_font().set_name("Arial");` |
| 添加表格 | `doc.tables().add(3, 4);` | `doc->get_body()->append_table(3, 4);` |
| 获取单元格 | `table.cellAt(row, col)` | `table->get_cell(row, col)` |
| 保存 | `doc.save();` | `doc->save("file.docx");` |

新版 API 更加类型安全、直观，并且支持链式调用。
