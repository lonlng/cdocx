# CDocx 架构重构设计文档

## 设计原则

基于 Aspose.Words.C++ 的设计理念和 TestWord.docx 的实际结构，重构 CDocx 架构：

1. **清晰的节点层次结构** - 统一 Node 基类
2. **属性封装** - 将格式属性封装为独立类
3. **集合类** - 提供类型安全的节点集合
4. **现代 C++ 特性** - 使用 C++17/20 特性
5. **DOM 风格 API** - 类似浏览器 DOM 的操作方式

---

## 核心架构

### 1. 节点层次结构 (Node Hierarchy)

```
Node (抽象基类)
├── Document
├── Section
│   ├── Body
│   └── HeaderFooter
├── Paragraph (CompositeNode)
│   ├── Run
│   ├── BookmarkStart/BookmarkEnd
│   ├── FieldStart/FieldSeparator/FieldEnd
│   └── Picture
└── Table (CompositeNode)
    ├── Row
    └── Cell
        └── Paragraph
```

### 2. 关键设计模式

#### 2.1 CompositeNode 模式

```cpp
class Node : public std::enable_shared_from_this<Node> {
public:
    virtual ~Node() = default;
    virtual NodeType node_type() const = 0;
    virtual std::string get_text() const = 0;
    
    // 树结构操作
    Document* get_document() const;
    Node* get_parent() const;
    Node* get_previous_sibling() const;
    Node* get_next_sibling() const;
    
    // 克隆
    virtual std::shared_ptr<Node> clone(bool deep = true) const = 0;
    
    // 访问者
    virtual void accept(DocumentVisitor* visitor) = 0;
};

class CompositeNode : public Node {
public:
    // 子节点操作
    NodeCollection get_child_nodes();
    NodeCollection get_child_nodes(NodeType type);
    
    std::shared_ptr<Node> append_child(std::shared_ptr<Node> child);
    std::shared_ptr<Node> insert_before(std::shared_ptr<Node> new_node, std::shared_ptr<Node> ref_node);
    std::shared_ptr<Node> insert_after(std::shared_ptr<Node> new_node, std::shared_ptr<Node> ref_node);
    void remove_child(std::shared_ptr<Node> child);
    void remove_all_children();
    
    // 类型安全访问
    template<typename T>
    std::shared_ptr<T> first_child() const;
    
    template<typename T>
    std::shared_ptr<T> last_child() const;
};
```

#### 2.2 NodeCollection 集合类

```cpp
class NodeCollection {
public:
    using iterator = std::vector<std::shared_ptr<Node>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Node>>::const_iterator;
    
    // 基本操作
    size_t get_count() const;
    std::shared_ptr<Node> get_item(size_t index) const;
    
    // 迭代器支持
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    
    // 类型过滤
    NodeCollection of_type(NodeType type) const;
    
    template<typename T>
    std::vector<std::shared_ptr<T>> of_type() const;
    
    // 添加/删除
    void add(std::shared_ptr<Node> node);
    void remove(std::shared_ptr<Node> node);
    void clear();
    
    // 查找
    std::shared_ptr<Node> find(const std::string& text) const;
    std::vector<std::shared_ptr<Node>> find_all(const std::string& text) const;
};
```

---

## 3. Document 类重构

```cpp
class Document : public CompositeNode {
public:
    // 构造与加载
    Document();
    explicit Document(const std::string& filepath);
    
    // 文件操作
    void load(const std::string& filepath);
    void save(const std::string& filepath = "");
    bool is_loaded() const;
    std::string get_filepath() const;
    
    // 文档创建
    static std::shared_ptr<Document> create();
    
    // 内容访问 - 新的 API 风格
    SectionCollection get_sections();
    std::shared_ptr<Section> get_first_section();
    std::shared_ptr<Section> get_last_section();
    std::shared_ptr<Section> add_section();
    
    // 便捷访问正文
    std::shared_ptr<Body> get_body();
    ParagraphCollection get_paragraphs();
    TableCollection get_tables();
    
    // 样式
    StyleCollection get_styles();
    std::shared_ptr<Style> get_style(const std::string& name);
    
    // 内置属性
    BuiltInDocumentProperties get_built_in_properties();
    CustomDocumentProperties get_custom_properties();
    
    // 访问者模式
    void accept(DocumentVisitor* visitor) override;
    
    // 节点类型
    NodeType node_type() const override { return NodeType::Document; }
};
```

---

## 4. Section 类重构

```cpp
class Section : public CompositeNode {
public:
    // 正文访问
    std::shared_ptr<Body> get_body();
    std::shared_ptr<HeaderFooter> get_header(HeaderFooterType type);
    std::shared_ptr<HeaderFooter> get_footer(HeaderFooterType type);
    
    // 页面设置
    PageSetup& get_page_setup();
    const PageSetup& get_page_setup() const;
    
    // 便捷访问
    ParagraphCollection get_paragraphs();
    TableCollection get_tables();
    
    NodeType node_type() const override { return NodeType::Section; }
};
```

---

## 5. Paragraph 类重构

```cpp
class Paragraph : public CompositeNode {
public:
    // 构造
    Paragraph();
    explicit Paragraph(Document* doc);
    
    // 段落格式
    ParagraphFormat& get_paragraph_format();
    const ParagraphFormat& get_paragraph_format() const;
    
    // 列表格式
    ListFormat& get_list_format();
    const ListFormat& get_list_format() const;
    
    // 内容访问
    RunCollection get_runs();
    
    // 便捷文本操作
    std::string get_text() const override;
    void set_text(const std::string& text);
    void append_text(const std::string& text);
    void prepend_text(const std::string& text);
    
    // 添加 Run
    std::shared_ptr<Run> append_run(const std::string& text = "");
    std::shared_ptr<Run> insert_run(int index, const std::string& text = "");
    
    // 书签
    std::shared_ptr<BookmarkStart> append_bookmark_start(const std::string& name);
    std::shared_ptr<BookmarkEnd> append_bookmark_end(const std::string& name);
    
    // 字段
    std::shared_ptr<Field> append_field(FieldType type);
    std::shared_ptr<Field> append_page_number();
    std::shared_ptr<Field> append_date_field(const std::string& format = "");
    
    // 检查状态
    bool is_in_cell() const;
    bool is_end_of_cell() const;
    bool is_end_of_section() const;
    bool is_empty() const;
    
    // 插入位置
    void insert_break(BreakType break_type);
    
    NodeType node_type() const override { return NodeType::Paragraph; }
};
```

---

## 6. Run 类重构

```cpp
class Run : public Node {
public:
    // 构造
    Run();
    explicit Run(Document* doc);
    explicit Run(Document* doc, const std::string& text);
    
    // 文本
    std::string get_text() const override;
    void set_text(const std::string& text);
    
    // 字体格式
    Font& get_font();
    const Font& get_font() const;
    
    // 便捷方法
    void set_bold(bool value);
    void set_italic(bool value);
    void set_underline(UnderlineType value);
    void set_font_size(double size);  // points
    void set_font_name(const std::string& name);
    void set_color(const Color& color);
    void set_highlight(HighlightColor color);
    
    NodeType node_type() const override { return NodeType::Run; }
};
```

---

## 7. Table 类重构

```cpp
class Table : public CompositeNode {
public:
    // 构造
    Table();
    explicit Table(Document* doc);
    
    // 行操作
    RowCollection get_rows();
    std::shared_ptr<Row> get_first_row();
    std::shared_ptr<Row> get_last_row();
    
    // 添加行
    std::shared_ptr<Row> append_row();
    std::shared_ptr<Row> insert_row(int index);
    
    // 便捷创建
    std::shared_ptr<Row> append_row(const std::vector<std::string>& cell_texts);
    
    // 表格属性
    TableFormat& get_table_format();
    const TableFormat& get_table_format() const;
    
    // 尺寸
    int get_row_count() const;
    int get_column_count() const;
    
    // 单元格访问
    std::shared_ptr<Cell> get_cell(int row, int col);
    
    // 自动调整
    void auto_fit(AutoFitBehavior behavior);
    
    // 表格样式
    void set_style(const std::string& style_name);
    void set_style_identifier(StyleIdentifier style);
    
    // 便捷方法
    void ensure_minimum();  // 确保至少有一行
    
    NodeType node_type() const override { return NodeType::Table; }
};

class Row : public CompositeNode {
public:
    // 单元格操作
    CellCollection get_cells();
    std::shared_ptr<Cell> get_first_cell();
    std::shared_ptr<Cell> get_last_cell();
    
    // 添加单元格
    std::shared_ptr<Cell> append_cell();
    std::shared_ptr<Cell> insert_cell(int index);
    
    // 行属性
    RowFormat& get_row_format();
    const RowFormat& get_row_format() const;
    
    // 便捷方法
    bool is_last_row() const;
    bool is_first_row() const;
    
    NodeType node_type() const override { return NodeType::Row; }
};

class Cell : public CompositeNode {
public:
    // 内容访问
    ParagraphCollection get_paragraphs();
    std::shared_ptr<Paragraph> get_first_paragraph();
    
    // 确保有段落
    std::shared_ptr<Paragraph> ensure_minimum();
    
    // 单元格属性
    CellFormat& get_cell_format();
    const CellFormat& get_cell_format() const;
    
    // 合并单元格
    void merge_with(std::shared_ptr<Cell> other);
    bool is_merged() const;
    bool is_first_merged_cell() const;
    bool is_vertical_merge_start() const;
    bool is_vertical_merge_continue() const;
    
    // 父行
    std::shared_ptr<Row> get_parent_row();
    
    NodeType node_type() const override { return NodeType::Cell; }
};
```

---

## 8. 格式属性类

### 8.1 ParagraphFormat

```cpp
class ParagraphFormat {
public:
    // 对齐
    ParagraphAlignment get_alignment() const;
    void set_alignment(ParagraphAlignment value);
    
    // 缩进
    double get_left_indent() const;      // points
    void set_left_indent(double value);
    double get_right_indent() const;
    void set_right_indent(double value);
    double get_first_line_indent() const;
    void set_first_line_indent(double value);
    double get_space_before() const;     // points
    void set_space_before(double value);
    double get_space_after() const;
    void set_space_after(double value);
    
    // 行距
    LineSpacingRule get_line_spacing_rule() const;
    void set_line_spacing_rule(LineSpacingRule value);
    double get_line_spacing() const;     // points or multiple
    void set_line_spacing(double value);
    
    // 分页控制
    bool get_keep_together() const;
    void set_keep_together(bool value);
    bool get_keep_with_next() const;
    void set_keep_with_next(bool value);
    bool get_page_break_before() const;
    void set_page_break_before(bool value);
    bool get_widow_control() const;
    void set_widow_control(bool value);
    
    // 大纲级别
    OutlineLevel get_outline_level() const;
    void set_outline_level(OutlineLevel value);
    
    // 样式
    std::string get_style_name() const;
    void set_style_name(const std::string& value);
    
    // 其他属性...
};
```

### 8.2 Font

```cpp
class Font {
public:
    // 字体名称
    std::string get_name() const;
    void set_name(const std::string& value);
    std::string get_name_ascii() const;
    void set_name_ascii(const std::string& value);
    std::string get_name_far_east() const;
    void set_name_far_east(const std::string& value);
    
    // 字号
    double get_size() const;  // points
    void set_size(double value);
    
    // 颜色
    Color get_color() const;
    void set_color(const Color& value);
    
    // 格式
    bool get_bold() const;
    void set_bold(bool value);
    bool get_italic() const;
    void set_italic(bool value);
    UnderlineType get_underline() const;
    void set_underline(UnderlineType value);
    StrikeType get_strike() const;
    void set_strike(StrikeType value);
    bool get_double_strike() const;
    void set_double_strike(bool value);
    
    // 上下标
    ScriptType get_script_type() const;
    void set_script_type(ScriptType value);
    
    // 高亮
    HighlightColor get_highlight() const;
    void set_highlight(HighlightColor value);
    
    // 其他属性...
};
```

### 8.3 TableFormat

```cpp
class TableFormat {
public:
    // 对齐
    TableAlignment get_alignment() const;
    void set_alignment(TableAlignment value);
    
    // 缩进
    double get_left_indent() const;  // points
    void set_left_indent(double value);
    
    // 自动调整
    bool get_allow_auto_fit() const;
    void set_allow_auto_fit(bool value);
    
    // 边距
    double get_cell_spacing() const;
    void set_cell_spacing(double value);
    double get_top_padding() const;
    void set_top_padding(double value);
    double get_bottom_padding() const;
    void set_bottom_padding(double value);
    double get_left_padding() const;
    void set_left_padding(double value);
    double get_right_padding() const;
    void set_right_padding(double value);
    
    // 边框
    Borders& get_borders();
    const Borders& get_borders() const;
    
    // 文字环绕
    TextWrapping get_text_wrapping() const;
    void set_text_wrapping(TextWrapping value);
};
```

---

## 9. 字段支持

```cpp
class Field : public Node {
public:
    FieldType get_type() const;
    std::string get_code() const;
    std::string get_result() const;
    
    bool is_locked() const;
    void set_locked(bool value);
    
    void update();
    void unlink();
    
    NodeType node_type() const override { return NodeType::FieldStart; }
};

// 便捷字段类型
class PageField : public Field {
public:
    PageField();
};

class NumPagesField : public Field {
public:
    NumPagesField();
};

class DateField : public Field {
public:
    DateField();
    void set_date_format(const std::string& format);
};

class HyperlinkField : public Field {
public:
    HyperlinkField();
    void set_address(const std::string& url);
    void set_bookmark_name(const std::string& name);
};
```

---

## 10. 使用示例

### 10.1 创建文档

```cpp
#include <cdocx.h>

int main() {
    // 创建新文档
    auto doc = cdocx::Document::create();
    
    // 添加段落
    auto para = doc->get_body()->append_paragraph();
    para->append_run("Hello, World!")
        ->get_font()
        .set_bold(true)
        .set_size(14);
    
    // 添加格式化段落
    auto para2 = doc->get_body()->append_paragraph();
    para2->get_paragraph_format()
        .set_alignment(ParagraphAlignment::Center)
        .set_space_before(12)
        .set_space_after(12);
    para2->append_run("居中显示");
    
    // 保存
    doc->save("output.docx");
    return 0;
}
```

### 10.2 操作表格

```cpp
// 创建表格
auto table = doc->get_body()->append_table(3, 3);  // 3行3列

// 设置表头
auto header_row = table->get_first_row();
header_row->get_row_format().set_heading(true);
for (auto& cell : header_row->get_cells()) {
    cell->get_first_paragraph()
        ->append_run("Header")
        ->get_font()
        .set_bold(true);
}

// 填充数据
for (int row = 1; row < table->get_row_count(); ++row) {
    for (int col = 0; col < table->get_column_count(); ++col) {
        auto cell = table->get_cell(row, col);
        cell->get_first_paragraph()->append_run(
            "Cell " + std::to_string(row) + "," + std::to_string(col)
        );
    }
}

// 合并单元格
table->get_cell(0, 0)->merge_with(table->get_cell(0, 1));

// 自动调整
table->auto_fit(AutoFitBehavior::AutoFitToWindow);
```

### 10.3 遍历内容

```cpp
// 遍历所有段落
for (auto& para : doc->get_paragraphs()) {
    std::cout << para.get_text() << std::endl;
}

// 遍历表格
for (auto& table : doc->get_tables()) {
    std::cout << "Table: " << table.get_row_count() 
              << " rows, " << table.get_column_count() << " cols" << std::endl;
}

// 使用访问者模式
class TextExtractor : public DocumentVisitor {
public:
    void visit_run(Run& run) override {
        text_ += run.get_text();
    }
    void visit_paragraph_end(Paragraph& para) override {
        text_ += "\n";
    }
    std::string get_text() const { return text_; }
private:
    std::string text_;
};

TextExtractor extractor;
doc->accept(&extractor);
std::cout << extractor.get_text() << std::endl;
```

### 10.4 字段操作

```cpp
// 添加页码
auto footer = doc->get_first_section()->get_footer(HeaderFooterType::Primary);
auto para = footer->append_paragraph();
para->get_paragraph_format().set_alignment(ParagraphAlignment::Center);
para->append_run("Page ");
para->append_page_number();
para->append_run(" of ");
para->append_num_pages();

// 添加超链接
auto link_para = doc->get_body()->append_paragraph();
auto hyperlink = link_para->append_hyperlink("Visit Example", "https://example.com");
hyperlink->get_font().set_color(Color::Blue);
hyperlink->get_font().set_underline(UnderlineType::Single);
```

---

## 11. 与旧 API 的兼容性

为了保持向后兼容，提供适配层：

```cpp
namespace compat {
    // 旧版 API 包装
    class Document {
        std::shared_ptr<new_api::Document> impl_;
    public:
        void open() { impl_->load(filepath_); }
        Paragraph& paragraphs() { /* 包装 */ }
        // ... 其他旧方法
    };
}
```

---

## 12. 实现优先级

### Phase 1: 核心架构
1. Node/CompositeNode 基类
2. NodeCollection 集合类
3. Document 类重构
4. 基本树操作

### Phase 2: 内容类
1. Section/Body
2. Paragraph + ParagraphFormat
3. Run + Font
4. 文本操作

### Phase 3: 表格
1. Table/Row/Cell
2. TableFormat/CellFormat
3. 合并单元格
4. 表格迭代

### Phase 4: 字段
1. Field 基类
2. PageField/NumPagesField
3. DateField
4. HyperlinkField

### Phase 5: 高级功能
1. 书签
2. 样式系统
3. 访问者模式
4. 文档属性

---

## 总结

新架构的特点：

1. **清晰的继承层次** - Node -> CompositeNode -> 具体类
2. **强类型集合** - NodeCollection 提供类型安全访问
3. **属性封装** - 格式属性独立成类
4. **现代 C++** - shared_ptr, 迭代器, 范围 for
5. **链式调用** - 支持方法链式调用
6. **DOM 风格** - 类似浏览器 DOM 的 API
7. **访问者模式** - 支持复杂遍历操作

这个设计将大幅提升 CDocx 的可用性和可维护性。
