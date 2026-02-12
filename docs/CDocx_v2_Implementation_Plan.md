# CDocx v2.0 实现计划

## 目标

基于 Aspose.Words 的设计模式和 TestWord.docx 的实际结构，重构 CDocx 的核心 API，提供更好的类型安全、链式调用支持和 DOM 风格操作。

**不做导出功能**：只专注于 DOCX 格式的读写操作。

---

## 已完成设计

### 头文件结构

```
include/cdocx/
├── enums.h          # 所有枚举类型
├── format.h         # 格式属性类 (Font, ParagraphFormat, TableFormat, etc.)
├── node.h           # Node/CompositeNode/NodeCollection/DocumentVisitor
├── document.h       # Document/Section/Body/HeaderFooter
├── paragraph.h      # Paragraph/Run/Bookmark/Field
└── table.h          # Table/Row/Cell

include/
└── cdocx.h          # 主头文件
```

---

## 实现优先级

### Phase 1: 基础设施 (核心)

| 优先级 | 文件 | 类/功能 | 工作量 |
|-------|------|--------|-------|
| P0 | `src/format.cpp` | Color, Border, Shading, Font, ParagraphFormat, TableFormat, CellFormat, RowFormat, PageSetup | 2天 |
| P0 | `src/node.cpp` | Node, CompositeNode, NodeCollection, DocumentVisitor | 2天 |
| P0 | `src/enums.cpp` | 枚举到字符串的转换 | 0.5天 |

**Phase 1 小计: 4.5天**

### Phase 2: 文档结构

| 优先级 | 文件 | 类/功能 | 工作量 |
|-------|------|--------|-------|
| P0 | `src/document.cpp` | Document, 文件操作, 属性 | 3天 |
| P0 | `src/section.cpp` | Section, Body, HeaderFooter | 2天 |
| P1 | `src/style.cpp` | Style, StyleCollection | 1天 |

**Phase 2 小计: 6天**

### Phase 3: 内容操作

| 优先级 | 文件 | 类/功能 | 工作量 |
|-------|------|--------|-------|
| P0 | `src/paragraph.cpp` | Paragraph, Run, SpecialChar, RunCollection | 3天 |
| P0 | `src/table.cpp` | Table, Row, Cell, RowCollection, CellCollection, TableBuilder | 3天 |
| P1 | `src/field.cpp` | Field, Hyperlink, 字段更新 | 2天 |
| P1 | `src/bookmark.cpp` | BookmarkStart, BookmarkEnd | 1天 |

**Phase 3 小计: 9天**

### Phase 4: XML 序列化

| 优先级 | 文件 | 类/功能 | 工作量 |
|-------|------|--------|-------|
| P0 | `src/xml/serializer.cpp` | 文档序列化为 XML | 3天 |
| P0 | `src/xml/deserializer.cpp` | XML 解析为文档 | 3天 |
| P1 | `src/xml/format_serializer.cpp` | 格式属性序列化 | 2天 |

**Phase 4 小计: 8天**

### Phase 5: 与旧版兼容层

| 优先级 | 文件 | 类/功能 | 工作量 |
|-------|------|--------|-------|
| P2 | `src/compat/legacy.cpp` | 旧版 API 适配器 | 2天 |

**Phase 5 小计: 2天**

### 总计工作量

| Phase | 内容 | 天数 |
|-------|------|------|
| 1 | 基础设施 | 4.5 |
| 2 | 文档结构 | 6 |
| 3 | 内容操作 | 9 |
| 4 | XML 序列化 | 8 |
| 5 | 兼容层 | 2 |
| **总计** | | **~30天** |

---

## 文件实现细节

### 1. src/format.cpp

实现所有格式属性类：

```cpp
// Color
std::string Color::to_hex() const;
std::string Color::to_hex_rgb() const;
Color Color::from_hex(const std::string& hex);

// Border
// (主要是数据结构，无需复杂实现)

// ParagraphFormat
// (主要是数据结构，提供一些便捷方法)

// Font
// (主要是数据结构)

// TableFormat, CellFormat, RowFormat
// (主要是数据结构)

// PageSetup
void PageSetup::set_a4();
void PageSetup::set_letter();
void PageSetup::set_page_size(double width, double height);
```

### 2. src/node.cpp

```cpp
// Node
void Node::remove();
int Node::get_index() const;
bool Node::is_descendant_of(const Node* ancestor) const;
std::shared_ptr<Node> Node::get_previous_node() const;
std::shared_ptr<Node> Node::get_next_node() const;

// CompositeNode
std::shared_ptr<Node> CompositeNode::get_first_child() const;
std::shared_ptr<Node> CompositeNode::get_last_child() const;
std::shared_ptr<Node> CompositeNode::get_child(int index) const;
std::shared_ptr<Node> CompositeNode::append_child(std::shared_ptr<Node> child);
std::shared_ptr<Node> CompositeNode::insert_child(int index, std::shared_ptr<Node> child);
std::shared_ptr<Node> CompositeNode::insert_before(std::shared_ptr<Node> new_node, std::shared_ptr<Node> ref_node);
std::shared_ptr<Node> CompositeNode::insert_after(std::shared_ptr<Node> new_node, std::shared_ptr<Node> ref_node);
void CompositeNode::remove_child(std::shared_ptr<Node> child);
void CompositeNode::remove_child(int index);
void CompositeNode::remove_all_children();
std::string CompositeNode::get_text() const;
std::shared_ptr<Node> CompositeNode::clone(bool deep) const;
NodeCollection CompositeNode::get_child_nodes() const;
NodeCollection CompositeNode::get_child_nodes(NodeType type) const;

// NodeCollection
NodeCollection NodeCollection::of_type(NodeType type) const;
std::shared_ptr<Node> NodeCollection::find(const std::string& text) const;
std::vector<std::shared_ptr<Node>> NodeCollection::find_all(const std::string& text) const;
void NodeCollection::add(std::shared_ptr<Node> node);
void NodeCollection::remove(std::shared_ptr<Node> node);
void NodeCollection::clear();
```

### 3. src/document.cpp

```cpp
// Document
Document::Document();
Document::Document(const std::string& filepath);
Document::Document(Document&&) noexcept;
Document& Document::operator=(Document&&) noexcept;
Document::~Document();

static std::shared_ptr<Document> Document::create();
static std::shared_ptr<Document> Document::load_from_file(const std::string& filepath);

void Document::load(const std::string& filepath);
void Document::save(const std::string& filepath);
void Document::save(std::ostream& stream);

SectionCollection Document::get_sections();
std::shared_ptr<Section> Document::get_first_section();
std::shared_ptr<Section> Document::get_last_section();
std::shared_ptr<Section> Document::add_section();
void Document::remove_section(std::shared_ptr<Section> section);

std::shared_ptr<Body> Document::get_body();
ParagraphCollection Document::get_paragraphs();
TableCollection Document::get_tables();

std::shared_ptr<Paragraph> Document::append_paragraph(const std::string& text);
std::shared_ptr<Table> Document::append_table(int rows, int cols);

void Document::accept(DocumentVisitor* visitor);
std::shared_ptr<Node> Document::clone(bool deep) const;

// Section
Section::Section(Document* doc);
std::shared_ptr<Body> Section::get_body();
std::shared_ptr<HeaderFooter> Section::get_header(HeaderFooterType type);
std::shared_ptr<HeaderFooter> Section::get_footer(HeaderFooterType type);
std::shared_ptr<HeaderFooter> Section::ensure_header(HeaderFooterType type);
std::shared_ptr<HeaderFooter> Section::ensure_footer(HeaderFooterType type);
void Section::accept(DocumentVisitor* visitor);

// Body
Body::Body(Document* doc);
Body::Body(Section* section);
ParagraphCollection Body::get_paragraphs();
TableCollection Body::get_tables();
std::shared_ptr<Paragraph> Body::append_paragraph(const std::string& text);
std::shared_ptr<Table> Body::append_table(int rows, int cols);
void Body::accept(DocumentVisitor* visitor);
```

### 4. src/paragraph.cpp

```cpp
// SpecialChar
SpecialChar::SpecialChar(char16_t char_code);
std::shared_ptr<SpecialChar> SpecialChar::paragraph_break();
std::shared_ptr<SpecialChar> SpecialChar::line_break();
std::shared_ptr<SpecialChar> SpecialChar::page_break();
std::shared_ptr<SpecialChar> SpecialChar::tab();
std::string SpecialChar::get_text() const;
void SpecialChar::accept(DocumentVisitor* visitor);

// Run
Run::Run();
Run::Run(Document* doc);
Run::Run(Document* doc, const std::string& text);
void Run::accept(DocumentVisitor* visitor);
std::shared_ptr<Node> Run::clone(bool deep) const;

// Paragraph
Paragraph::Paragraph();
Paragraph::Paragraph(Document* doc);
std::string Paragraph::get_text() const;
void Paragraph::set_text(const std::string& text);
void Paragraph::append_text(const std::string& text);
void Paragraph::prepend_text(const std::string& text);
RunCollection Paragraph::get_runs();
std::shared_ptr<Run> Paragraph::append_run(const std::string& text);
std::shared_ptr<Run> Paragraph::insert_run(int index, const std::string& text);
std::shared_ptr<SpecialChar> Paragraph::append_break(BreakType break_type);
std::shared_ptr<SpecialChar> Paragraph::append_tab();
std::shared_ptr<Field> Paragraph::append_field(FieldType type);
std::shared_ptr<Field> Paragraph::append_page_number();
std::shared_ptr<Field> Paragraph::append_hyperlink(const std::string& text, const std::string& url);
std::shared_ptr<BookmarkStart> Paragraph::append_bookmark_start(const std::string& name);
std::shared_ptr<BookmarkEnd> Paragraph::append_bookmark_end(const std::string& name);
bool Paragraph::is_in_cell() const;
bool Paragraph::is_empty() const;
void Paragraph::accept(DocumentVisitor* visitor);
std::shared_ptr<Node> Paragraph::clone(bool deep) const;
```

### 5. src/table.cpp

```cpp
// Cell
Cell::Cell();
Cell::Cell(Document* doc);
CellFormat& Cell::get_cell_format();
ParagraphCollection Cell::get_paragraphs();
std::shared_ptr<Paragraph> Cell::get_first_paragraph();
std::shared_ptr<Paragraph> Cell::ensure_minimum();
std::shared_ptr<Paragraph> Cell::append_paragraph(const std::string& text);
void Cell::set_text(const std::string& text);
std::string Cell::get_text() const;
void Cell::merge_with(std::shared_ptr<Cell> other);
bool Cell::is_merged() const;
void Cell::accept(DocumentVisitor* visitor);
std::shared_ptr<Node> Cell::clone(bool deep) const;

// Row
Row::Row();
Row::Row(Document* doc);
RowFormat& Row::get_row_format();
CellCollection Row::get_cells();
std::shared_ptr<Cell> Row::get_first_cell();
std::shared_ptr<Cell> Row::get_last_cell();
std::shared_ptr<Cell> Row::get_cell(int index);
std::shared_ptr<Cell> Row::append_cell();
std::shared_ptr<Cell> Row::insert_cell(int index);
std::shared_ptr<Cell> Row::ensure_minimum();
std::string Row::get_text() const;
void Row::accept(DocumentVisitor* visitor);
std::shared_ptr<Node> Row::clone(bool deep) const;

// Table
Table::Table();
Table::Table(Document* doc);
Table::Table(Document* doc, int rows, int cols);
TableFormat& Table::get_table_format();
RowCollection Table::get_rows();
std::shared_ptr<Row> Table::get_first_row();
std::shared_ptr<Row> Table::get_last_row();
std::shared_ptr<Row> Table::get_row(int index);
std::shared_ptr<Row> Table::append_row();
std::shared_ptr<Row> Table::insert_row(int index);
std::shared_ptr<Row> Table::append_row(const std::vector<std::string>& cell_texts);
void Table::remove_row(std::shared_ptr<Row> row);
void Table::remove_row(int index);
std::shared_ptr<Cell> Table::get_cell(int row, int col);
int Table::get_row_count() const;
int Table::get_column_count() const;
void Table::auto_fit(AutoFitBehavior behavior);
void Table::ensure_minimum();
std::shared_ptr<Cell> Table::merge_cells(int start_row, int start_col, int end_row, int end_col);
void Table::split_cell(std::shared_ptr<Cell> cell, int row_count, int col_count);
std::string Table::get_text() const;
void Table::accept(DocumentVisitor* visitor);
std::shared_ptr<Node> Table::clone(bool deep) const;

// TableBuilder
TableBuilder::TableBuilder(Document* doc);
TableBuilder& TableBuilder::with_rows(int count);
TableBuilder& TableBuilder::with_columns(int count);
TableBuilder& TableBuilder::with_alignment(TableAlignment align);
TableBuilder& TableBuilder::with_borders(const Borders& borders);
TableBuilder& TableBuilder::with_auto_fit(AutoFitBehavior behavior);
TableBuilder& TableBuilder::add_row(const std::vector<std::string>& cells);
std::shared_ptr<Table> TableBuilder::build();
std::shared_ptr<Table> TableBuilder::append_to(std::shared_ptr<Body> body);
```

### 6. src/xml/serializer.cpp

将文档模型序列化为 OpenXML 格式：

```cpp
class XmlSerializer {
public:
    void serialize(const Document& doc, const std::string& filepath);
    void serialize(const Document& doc, std::ostream& stream);
    
private:
    void write_document_xml(const Document& doc, std::ostream& out);
    void write_styles_xml(const Document& doc, std::ostream& out);
    void write_content_types(const Document& doc, std::ostream& out);
    void write_rels(const Document& doc, std::ostream& out);
    
    void serialize_node(const Node& node, pugi::xml_node& parent);
    void serialize_paragraph(const Paragraph& para, pugi::xml_node& parent);
    void serialize_run(const Run& run, pugi::xml_node& parent);
    void serialize_table(const Table& table, pugi::xml_node& parent);
    void serialize_row(const Row& row, pugi::xml_node& parent);
    void serialize_cell(const Cell& cell, pugi::xml_node& parent);
    void serialize_field(const Field& field, pugi::xml_node& parent);
    
    void serialize_paragraph_format(const ParagraphFormat& format, pugi::xml_node& parent);
    void serialize_font(const Font& font, pugi::xml_node& parent);
    void serialize_table_format(const TableFormat& format, pugi::xml_node& parent);
    void serialize_cell_format(const CellFormat& format, pugi::xml_node& parent);
};
```

### 7. src/xml/deserializer.cpp

从 OpenXML 解析文档模型：

```cpp
class XmlDeserializer {
public:
    std::shared_ptr<Document> deserialize(const std::string& filepath);
    std::shared_ptr<Document> deserialize(std::istream& stream);
    
private:
    void parse_document_xml(Document& doc, pugi::xml_document& xml);
    void parse_styles_xml(Document& doc, pugi::xml_document& xml);
    
    std::shared_ptr<Node> parse_node(const pugi::xml_node& xml_node, Document& doc);
    std::shared_ptr<Paragraph> parse_paragraph(const pugi::xml_node& xml_node, Document& doc);
    std::shared_ptr<Run> parse_run(const pugi::xml_node& xml_node, Document& doc);
    std::shared_ptr<Table> parse_table(const pugi::xml_node& xml_node, Document& doc);
    std::shared_ptr<Row> parse_row(const pugi::xml_node& xml_node, Document& doc);
    std::shared_ptr<Cell> parse_cell(const pugi::xml_node& xml_node, Document& doc);
    
    void parse_paragraph_format(ParagraphFormat& format, const pugi::xml_node& xml);
    void parse_font(Font& font, const pugi::xml_node& xml);
    void parse_table_format(TableFormat& format, const pugi::xml_node& xml);
    void parse_cell_format(CellFormat& format, const pugi::xml_node& xml);
};
```

---

## 向后兼容性

### 保留旧版 API

在 `include/cdocx/legacy.h` 中提供旧版 API 的适配：

```cpp
namespace cdocx {
namespace legacy {

// 旧版 Document 包装器
class Document {
    std::shared_ptr<new_api::Document> impl_;
public:
    void open() { impl_->load(filepath_); }
    void save() { impl_->save(); }
    // ... 其他旧方法
};

// 旧版 Paragraph 包装器
class Paragraph {
    std::shared_ptr<new_api::Paragraph> impl_;
public:
    void add_run(const std::string& text, formatting_flag flag = none);
    bool set_alignment(const std::string& alignment);
    // ... 其他旧方法
};

} // namespace legacy
} // namespace cdocx
```

### 迁移示例

```cpp
// 旧代码
cdocx::Document doc("file.docx");
doc.open();
auto para = doc.paragraphs();
para.add_run("Hello", cdocx::bold);
doc.save();

// 新代码（等效）
auto doc = cdocx::Document::load_from_file("file.docx");
auto para = doc->get_body()->append_paragraph();
para->append_run("Hello")->get_font().set_bold(true);
doc->save();

// 或使用兼容层
#include <cdocx/legacy.h>
cdocx::legacy::Document doc("file.docx");
doc.open();
// ... 旧代码无需修改
```

---

## 测试计划

### 单元测试

```cpp
// test_format.cpp
TEST(Color, HexConversion) {
    auto color = Color::from_hex("FF0000");
    EXPECT_EQ(color.r, 255);
    EXPECT_EQ(color.g, 0);
    EXPECT_EQ(color.b, 0);
}

// test_node.cpp
TEST(CompositeNode, AppendChild) {
    auto doc = Document::create();
    auto para = std::make_shared<Paragraph>(doc.get());
    auto run = std::make_shared<Run>(doc.get(), "text");
    para->append_child(run);
    EXPECT_EQ(para->get_child_count(), 1);
}

// test_paragraph.cpp
TEST(Paragraph, TextContent) {
    auto para = std::make_shared<Paragraph>();
    para->append_run("Hello ");
    para->append_run("World");
    EXPECT_EQ(para->get_text(), "Hello World");
}

// test_table.cpp
TEST(Table, MergeCells) {
    auto table = std::make_shared<Table>(nullptr, 3, 3);
    auto merged = table->merge_cells(0, 0, 0, 1);
    EXPECT_EQ(merged->get_cell_format().get_horizontal_merge_span(), 2);
}
```

### 集成测试

```cpp
// test_roundtrip.cpp
TEST(RoundTrip, SimpleDocument) {
    // 创建文档
    auto doc = Document::create();
    doc->get_body()->append_paragraph("Test");
    doc->save("test.docx");
    
    // 重新加载
    auto loaded = Document::load_from_file("test.docx");
    EXPECT_EQ(loaded->get_body()->get_paragraphs()[0]->get_text(), "Test");
}

// TestWord 兼容性测试
TEST(Compatibility, TestWordStructure) {
    auto doc = Document::load_from_file("TestWord.docx");
    
    // 验证表格
    EXPECT_EQ(doc->get_tables().get_count(), 2);
    
    // 验证段落
    EXPECT_GT(doc->get_paragraphs().get_count(), 0);
    
    // 验证样式
    // ...
}
```

---

## 目录结构

```
cdocx/
├── include/
│   ├── cdocx.h
│   └── cdocx/
│       ├── enums.h
│       ├── format.h
│       ├── node.h
│       ├── document.h
│       ├── paragraph.h
│       ├── table.h
│       └── legacy.h          # 旧版 API 兼容层
├── src/
│   ├── enums.cpp
│   ├── format.cpp
│   ├── node.cpp
│   ├── document.cpp
│   ├── section.cpp
│   ├── paragraph.cpp
│   ├── run.cpp
│   ├── field.cpp
│   ├── bookmark.cpp
│   ├── table.cpp
│   ├── row.cpp
│   ├── cell.cpp
│   ├── style.cpp
│   ├── xml/
│   │   ├── serializer.cpp
│   │   ├── deserializer.cpp
│   │   ├── format_serializer.cpp
│   │   └── utils.cpp
│   └── compat/
│       └── legacy.cpp        # 旧版 API 实现
├── test/
│   ├── test_format.cpp
│   ├── test_node.cpp
│   ├── test_document.cpp
│   ├── test_paragraph.cpp
│   ├── test_table.cpp
│   └── test_roundtrip.cpp
└── examples/
    ├── basic_usage.cpp
    ├── table_operations.cpp
    └── complete_report.cpp
```

---

## 里程碑

| 里程碑 | 日期 | 内容 | 验收标准 |
|-------|------|------|---------|
| M1 | Week 1 | Phase 1 完成 | format.cpp, node.cpp 编译通过，单元测试通过 |
| M2 | Week 2-3 | Phase 2 完成 | document.cpp, section.cpp 编译通过，可创建空文档 |
| M3 | Week 4-5 | Phase 3 完成 | paragraph.cpp, table.cpp 编译通过，可读写简单文档 |
| M4 | Week 6-7 | Phase 4 完成 | XML 序列化/反序列化完成，可读写 TestWord.docx |
| M5 | Week 8 | Phase 5 完成 | 兼容层完成，旧测试用例通过 |
| Release | Week 9 | 发布 v2.0 | 所有测试通过，文档完整 |

---

## 风险与缓解

| 风险 | 影响 | 缓解措施 |
|-----|------|---------|
| XML 序列化复杂度高 | 延迟 | 先实现核心功能，逐步完善 |
| 向后兼容性破坏 | 用户不满 | 提供完整兼容层 |
| 性能问题 | 用户体验差 | 使用 pugixml，避免不必要的拷贝 |
| 内存占用高 | 大文档处理困难 | 实现流式处理，延迟加载 |

---

## 总结

CDocx v2.0 将实现：

1. **清晰的类层次结构** - Node/CompositeNode 模式
2. **类型安全的集合** - NodeCollection 替代原始迭代器
3. **流畅的 API** - 支持链式调用
4. **完整的格式支持** - Font, ParagraphFormat, TableFormat 等
5. **字段支持** - 页码、日期、超链接
6. **向后兼容** - 旧版 API 继续使用

**预计总工作量：9周（30天开发 + 3周缓冲）**
