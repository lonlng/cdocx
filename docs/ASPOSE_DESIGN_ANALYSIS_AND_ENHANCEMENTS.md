# Aspose.Words C++ 设计分析与 CDocx 增强优化建议

**文档版本**: v1.0  
**日期**: 2026-02-12  
**分析目标**: 基于 Aspose.Words C++ 的优秀设计，为 CDocx 提供架构增强建议

---

## 目录

1. [概述](#概述)
2. [架构设计对比](#架构设计对比)
3. [详细增强建议](#详细增强建议)
4. [优先级与实施路线图](#优先级与实施路线图)

---

## 概述

### Aspose.Words C++ 设计特点

Aspose.Words C++ 是一个成熟的商业文档处理库，其设计遵循了多种经典设计模式，提供了强大而灵活的 API。主要特点包括：

- **完整的 DOM (Document Object Model) 实现**
- **广泛的 Visitor 模式应用**
- **清晰的命名空间组织**
- **精细的属性分离**
- **丰富的集合类设计**

### CDocx 当前状态

CDocx 已实现基本的 DOCX 读写功能，包括：

- 基本文档结构（Document, Paragraph, Run, Table）
- 迭代器模式遍历
- 模板替换功能
- 书签操作
- 段落和字符格式

---

## 架构设计对比

### 1. 节点层次结构 (Node Hierarchy)

#### Aspose.Words 设计

```
System::Object
    └── Node (抽象基类)
            ├── CompositeNode (可包含子节点)
            │       ├── Document
            │       ├── Section
            │       ├── Body / HeaderFooter
            │       ├── Paragraph
            │       ├── Table
            │       ├── Row
            │       └── Cell
            │
            └── Inline (内联元素基类)
                    ├── Run
                    ├── BookmarkStart / BookmarkEnd
                    ├── FieldStart / FieldSeparator / FieldEnd
                    └── Shape
```

**关键设计点**:
- `Node` 提供统一的 `Accept(Visitor)` 接口
- `CompositeNode` 继承 `IEnumerable<Node>` 和 `INodeCollection`
- 每个节点类型有明确的 `NodeType` 枚举值
- 支持父子关系导航：`ParentNode`, `PreviousSibling`, `NextSibling`

#### CDocx 当前设计

```
cdocx::Document
    ├── Paragraph (通过迭代器访问)
    ├── Table (通过迭代器访问)
    └── Section (v0.5.0+)

Paragraph
    └── Run (通过迭代器访问)
```

**差距分析**:
- 缺乏统一的 `Node` 基类
- 节点间导航能力有限
- 没有明确的节点类型标识
- 父子关系维护不完整

---

### 2. Visitor 模式 (Document Visitor)

#### Aspose.Words 设计

```cpp
class DocumentVisitor {
public:
    virtual VisitorAction VisitDocumentStart(Document* doc);
    virtual VisitorAction VisitDocumentEnd(Document* doc);
    virtual VisitorAction VisitSectionStart(Section* section);
    virtual VisitorAction VisitSectionEnd(Section* section);
    virtual VisitorAction VisitParagraphStart(Paragraph* paragraph);
    virtual VisitorAction VisitParagraphEnd(Paragraph* paragraph);
    virtual VisitorAction VisitTableStart(Table* table);
    virtual VisitorAction VisitTableEnd(Table* table);
    virtual VisitorAction VisitRowStart(Row* row);
    virtual VisitorAction VisitRowEnd(Row* row);
    virtual VisitorAction VisitCellStart(Cell* cell);
    virtual VisitorAction VisitCellEnd(Cell* cell);
    virtual VisitorAction VisitRun(Run* run);
    // ... 更多 Visit 方法
};
```

**优势**:
- 统一的遍历机制
- 易于扩展新操作而不修改节点类
- 支持遍历控制（Continue, Skip, Stop）
- 内部用于保存、查找等操作

#### CDocx 当前设计

```cpp
// 目前只有迭代器模式
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    // 处理段落
}
```

**差距分析**:
- 仅支持迭代器模式
- 无法优雅地处理复杂遍历逻辑
- 缺乏统一的遍历控制机制

---

### 3. Range 概念

#### Aspose.Words 设计

```cpp
class Range : public IEnumerable<Node> {
public:
    String get_Text();
    BookmarkCollection* get_Bookmarks();
    FieldCollection* get_Fields();
    FormFieldCollection* get_FormFields();
    
    // 查找替换
    int Replace(const String& oldText, const String& newText, 
                const FindReplaceOptions& options);
};

// 每个节点都有 Range 属性
class Node {
public:
    Range* get_Range();
};
```

**优势**:
- 提供"平面"文本视图
- 简化查找替换操作
- 统一的子元素访问接口

#### CDocx 当前设计

```cpp
// 有限的查找替换支持
class DocumentSearch {
public:
    static std::optional<Range> find(Document& doc, const std::string& text);
    static bool replace(Document& doc, const std::string& old_text, 
                        const std::string& new_text);
};
```

**差距分析**:
- Range 功能不完整
- 查找替换选项有限
- 缺乏统一的子元素集合访问

---

### 4. 属性分离设计

#### Aspose.Words 设计

格式属性完全分离到独立类：

```cpp
class Paragraph {
public:
    ParagraphFormat* get_ParagraphFormat();  // 段落格式
    ListFormat* get_ListFormat();            // 列表格式
};

class ParagraphFormat {
public:
    // 对齐
    ParagraphAlignment get_Alignment();
    void set_Alignment(ParagraphAlignment value);
    
    // 缩进
    double get_LeftIndent();
    double get_RightIndent();
    double get_FirstLineIndent();
    
    // 间距
    double get_SpaceBefore();
    double get_SpaceAfter();
    LineSpacingRule get_LineSpacingRule();
    
    // 分页控制
    bool get_KeepTogether();
    bool get_KeepWithNext();
    bool get_PageBreakBefore();
    
    // 边框
    BorderCollection* get_Borders();
    
    // 底纹
    Shading* get_Shading();
};

class Run {
public:
    Font* get_Font();  // 字符格式
};

class Font {
public:
    String get_Name();
    void set_Name(const String& value);
    double get_Size();
    void set_Size(double value);
    bool get_Bold();
    void set_Bold(bool value);
    bool get_Italic();
    void set_Italic(bool value);
    Underline get_Underline();
    void set_Underline(Underline value);
    Color get_Color();
    void set_Color(Color value);
    // ... 更多字体属性
};
```

**优势**:
- 属性组织结构清晰
- 易于批量复制格式
- 支持格式继承和样式引用

#### CDocx 当前设计

```cpp
class BookmarkFormat {
public:
    std::string alignment;
    int line_spacing;
    int space_before;
    int space_after;
    // ... 混合在结构体中
};

class Paragraph {
public:
    void set_alignment(const std::string& align);
    // 直接在段落上设置
};
```

**差距分析**:
- 格式类与内容类未分离
- 不支持格式对象复用
- 样式引用机制不完整

---

### 5. 集合类设计

#### Aspose.Words 设计

```cpp
// 统一的集合接口
template<typename T>
class NodeCollection : public IEnumerable<T> {
public:
    int32_t get_Count();
    T* idx_get(int32_t index);  // 支持负数索引
    void Add(T* node);
    void Remove(T* node);
    void RemoveAt(int32_t index);
    void Clear();
    IEnumerator<T>* GetEnumerator();
    
    // 查找
    T* First();  // 首个元素
    T* Last();   // 最后一个元素
};

// 专门的集合类
class BookmarkCollection : public IEnumerable<Bookmark> {
public:
    int32_t get_Count();
    Bookmark* idx_get(int32_t index);
    Bookmark* idx_get(const String& name);  // 按名称索引
    void Remove(const String& name);
    void RemoveAt(int32_t index);
    void Clear();
};

class FieldCollection : public IEnumerable<Field> { ... };
class SectionCollection : public IEnumerable<Section> { ... };
```

**优势**:
- 统一的集合接口
- 支持索引器访问（包括名称索引）
- 支持负数索引（-1 表示最后一个）
- 集合变更自动同步到文档

#### CDocx 当前设计

```cpp
class BookmarkCollection {
public:
    size_t count() const;
    Bookmark get(size_t index) const;
    std::optional<Bookmark> get(const std::string& name) const;
    bool remove(const std::string& name);
    std::vector<std::string> get_names() const;
};
```

**差距分析**:
- 未实现标准迭代器接口
- 缺乏负数索引支持
- 集合变更机制不完整

---

### 6. DocumentBuilder 模式

#### Aspose.Words 设计

```cpp
class DocumentBuilder {
public:
    // 光标位置
    void MoveTo(Node* node);
    void MoveToBookmark(const String& bookmarkName);
    void MoveToParagraph(int32_t paragraphIndex, int32_t characterIndex);
    void MoveToCell(int32_t tableIndex, int32_t rowIndex, int32_t cellIndex);
    void MoveToDocumentStart();
    void MoveToDocumentEnd();
    
    // 内容插入
    void Write(const String& text);
    void Writeln(const String& text);
    void InsertBreak(BreakType breakType);
    void InsertImage(const String& fileName);
    void InsertImage(Stream* stream);
    void InsertHtml(const String& html);
    
    // 表格构建
    Table* StartTable();
    Row* EndRow();
    Cell* EndCell();
    void InsertCell();
    
    // 格式属性
    Font* get_Font();
    ParagraphFormat* get_ParagraphFormat();
    PageSetup* get_PageSetup();
    RowFormat* get_RowFormat();
    CellFormat* get_CellFormat();
};
```

**优势**:
- 流式 API 设计
- 光标导航灵活
- 格式属性上下文感知
- 支持 HTML 直接插入

#### CDocx 当前设计

```cpp
class DocumentBuilder {
public:
    void move_to_document_start();
    void move_to_document_end();
    void move_to_paragraph(size_t index);
    void write(const std::string& text);
    void writeln(const std::string& text);
    void insert_break();
    void start_table();
    void insert_row();
    void insert_cell();
    void end_table();
    void set_bold(bool value);
    void set_italic(bool value);
    // ... 格式设置
};
```

**差距分析**:
- 光标位置管理不精确
- 缺乏 MoveToBookmark、MoveToCell 等方法
- 不支持 HTML 插入
- 格式属性不自动同步

---

### 7. 命名空间组织

#### Aspose.Words 设计

```
Aspose::Words
├── Tables
│   ├── Table
│   ├── Row
│   ├── Cell
│   ├── RowCollection
│   └── CellCollection
├── Fields
│   ├── Field
│   ├── FieldStart
│   ├── FieldEnd
│   └── FormField
├── Drawing
│   ├── Shape
│   ├── ImageData
│   └── Charts
├── Lists
│   ├── List
│   └── ListFormat
├── Saving
│   ├── SaveOptions
│   ├── DocSaveOptions
│   └── PdfSaveOptions
├── Loading
│   └── LoadOptions
└── Fonts
    └── FontSettings
```

**优势**:
- 功能模块清晰分离
- 避免命名冲突
- 便于扩展新功能模块

#### CDocx 当前设计

```
cdocx
├── Document
├── Paragraph
├── Table
├── Bookmark
├── Template
└── DocumentBuilder
```

**差距分析**:
- 所有类在同一命名空间
- 功能模块未分离
- 未来扩展可能导致命名冲突

---

### 8. 保存选项层次结构

#### Aspose.Words 设计

```cpp
// 抽象基类
class SaveOptions {
public:
    virtual SaveFormat get_SaveFormat() = 0;
    bool get_PrettyFormat();
    bool get_ExportGeneratorName();
    String get_TempFolder();
};

// 具体选项类
class DocSaveOptions : public SaveOptions {
public:
    SaveFormat get_SaveFormat() override { return SaveFormat::Doc; }
    bool get_AlwaysCompressMetafiles();
    bool get_SavePictureBullet();
};

class PdfSaveOptions : public SaveOptions {
public:
    SaveFormat get_SaveFormat() override { return SaveFormat::Pdf; }
    PdfCompliance get_Compliance();
    bool get_ExportDocumentStructure();
    IImageCompressionOptions* get_ImageCompression();
};

class HtmlSaveOptions : public SaveOptions {
public:
    SaveFormat get_SaveFormat() override { return SaveFormat::Html; }
    HtmlVersion get_HtmlVersion();
    bool get_ExportImagesAsBase64();
    String get_CssStyleSheetFileName();
};
```

**优势**:
- 统一的保存接口
- 格式特定选项分离
- 易于添加新格式支持

#### CDocx 当前设计

```cpp
class Document {
public:
    void save();  // 保存到原文件
    void save(const std::string& filepath);  // 另存为
};
```

**差距分析**:
- 缺乏保存选项支持
- 不支持不同格式的特定选项
- 无法导出为 PDF、HTML 等格式

---

## 详细增强建议

### 高优先级 (P1)

#### 1. 实现统一的 Node 基类层次结构

**建议实现**:

```cpp
namespace cdocx {

enum class NodeType {
    Document,
    Section,
    Body,
    HeaderFooter,
    Paragraph,
    Table,
    Row,
    Cell,
    Run,
    BookmarkStart,
    BookmarkEnd,
    FieldStart,
    FieldEnd,
    Shape,
    // ...
};

class Node {
public:
    virtual ~Node() = default;
    
    // 类型识别
    virtual NodeType node_type() const = 0;
    
    // 文档归属
    virtual Document* document() const = 0;
    
    // 父子导航
    virtual CompositeNode* parent_node() const { return parent_; }
    virtual Node* previous_sibling() const { return prev_sibling_; }
    virtual Node* next_sibling() const { return next_sibling_; }
    
    // Visitor 支持
    virtual bool accept(DocumentVisitor* visitor) = 0;
    
    // 克隆
    virtual std::shared_ptr<Node> clone(bool deep) = 0;
    
    // 文本内容
    virtual std::string get_text() const = 0;
    
    // Range 访问
    Range* range();
    
protected:
    CompositeNode* parent_ = nullptr;
    Node* prev_sibling_ = nullptr;
    Node* next_sibling_ = nullptr;
};

class CompositeNode : public Node {
public:
    bool is_composite() const override { return true; }
    
    // 子节点访问
    Node* first_child() const;
    Node* last_child() const;
    size_t child_count() const;
    
    // 子节点操作
    void append_child(std::shared_ptr<Node> node);
    void insert_before(std::shared_ptr<Node> new_node, Node* ref_node);
    void insert_after(std::shared_ptr<Node> new_node, Node* ref_node);
    void remove_child(Node* node);
    
    // 类型筛选的子节点集合
    NodeCollection get_child_nodes(NodeType type, bool deep);
    Node* get_child(NodeType type, int index, bool deep);
    
    // 迭代器支持
    class iterator { ... };
    iterator begin();
    iterator end();
    
protected:
    std::vector<std::shared_ptr<Node>> children_;
};

} // namespace cdocx
```

**收益**:
- 统一的节点处理接口
- 支持通用的树操作
- 为 Visitor 模式奠定基础

---

#### 2. 实现 DocumentVisitor 模式

**建议实现**:

```cpp
namespace cdocx {

enum class VisitorAction {
    Continue,   // 继续遍历
    Skip,       // 跳过当前节点的子节点
    Stop        // 停止遍历
};

class DocumentVisitor {
public:
    virtual ~DocumentVisitor() = default;
    
    // 文档级别
    virtual VisitorAction visit_document_start(Document& doc);
    virtual VisitorAction visit_document_end(Document& doc);
    
    // 节级别
    virtual VisitorAction visit_section_start(Section& section);
    virtual VisitorAction visit_section_end(Section& section);
    
    // 正文/页眉页脚
    virtual VisitorAction visit_body_start(Body& body);
    virtual VisitorAction visit_body_end(Body& body);
    virtual VisitorAction visit_header_footer_start(HeaderFooter& hf);
    virtual VisitorAction visit_header_footer_end(HeaderFooter& hf);
    
    // 段落
    virtual VisitorAction visit_paragraph_start(Paragraph& para);
    virtual VisitorAction visit_paragraph_end(Paragraph& para);
    
    // 表格
    virtual VisitorAction visit_table_start(Table& table);
    virtual VisitorAction visit_table_end(Table& table);
    virtual VisitorAction visit_row_start(TableRow& row);
    virtual VisitorAction visit_row_end(TableRow& row);
    virtual VisitorAction visit_cell_start(TableCell& cell);
    virtual VisitorAction visit_cell_end(TableCell& cell);
    
    // 内联元素
    virtual VisitorAction visit_run(Run& run);
    virtual VisitorAction visit_bookmark_start(BookmarkStart& bm);
    virtual VisitorAction visit_bookmark_end(BookmarkEnd& bm);
    virtual VisitorAction visit_field_start(FieldStart& field);
    virtual VisitorAction visit_field_separator(FieldSeparator& field);
    virtual VisitorAction visit_field_end(FieldEnd& field);
};

} // namespace cdocx
```

**使用示例**:

```cpp
// 统计文档字数
class WordCounterVisitor : public cdocx::DocumentVisitor {
public:
    int word_count = 0;
    
    VisitorAction visit_run(Run& run) override {
        word_count += count_words(run.get_text());
        return VisitorAction::Continue;
    }
};

// 使用
WordCounterVisitor counter;
doc.accept(&counter);
std::cout << "Word count: " << counter.word_count << std::endl;
```

---

#### 3. 分离格式属性类

**建议实现**:

```cpp
namespace cdocx {

// 段落格式
class ParagraphFormat {
public:
    // 对齐
    ParagraphAlignment alignment() const;
    void set_alignment(ParagraphAlignment value);
    
    // 缩进（单位：磅）
    double left_indent() const;
    void set_left_indent(double value);
    double right_indent() const;
    void set_right_indent(double value);
    double first_line_indent() const;
    void set_first_line_indent(double value);
    
    // 间距
    double space_before() const;
    void set_space_before(double value);
    double space_after() const;
    void set_space_after(double value);
    LineSpacingRule line_spacing_rule() const;
    double line_spacing() const;
    void set_line_spacing(double value, LineSpacingRule rule);
    
    // 分页控制
    bool keep_together() const;
    void set_keep_together(bool value);
    bool keep_with_next() const;
    void set_keep_with_next(bool value);
    bool page_break_before() const;
    void set_page_break_before(bool value);
    
    // 边框和底纹
    BorderCollection* borders();
    Shading* shading();
    
    // 大纲级别
    OutlineLevel outline_level() const;
    void set_outline_level(OutlineLevel value);
    
    // 复制格式
    std::shared_ptr<ParagraphFormat> clone() const;
    void copy_from(const ParagraphFormat& source);
    
private:
    ParagraphFormatImpl* impl_;
};

// 字符格式
class Font {
public:
    // 字体名称
    std::string name() const;
    void set_name(const std::string& value);
    std::string name_far_east() const;  // 中文字体
    void set_name_far_east(const std::string& value);
    
    // 字号
    double size() const;
    void set_size(double value);
    
    // 样式
    bool bold() const;
    void set_bold(bool value);
    bool italic() const;
    void set_italic(bool value);
    Underline underline() const;
    void set_underline(Underline value);
    StrikeType strike() const;
    void set_strike(StrikeType value);
    
    // 颜色
    Color color() const;
    void set_color(Color value);
    
    // 效果
    bool double_strike() const;
    void set_double_strike(bool value);
    bool hidden() const;
    void set_hidden(bool value);
    int position() const;  // 上下标位移
    void set_position(int value);
    int spacing() const;   // 字符间距
    void set_spacing(int value);
    int kerning() const;   // 字距调整
    void set_kerning(int value);
    
    // 复制格式
    std::shared_ptr<Font> clone() const;
    void copy_from(const Font& source);
    
private:
    FontImpl* impl_;
};

} // namespace cdocx
```

---

### 中优先级 (P2)

#### 4. 实现 Range 概念

**建议实现**:

```cpp
namespace cdocx {

class Range {
public:
    // 构造函数
    Range(Node* start_node, Node* end_node);
    explicit Range(Node* node);  // 单个节点的范围
    
    // 文本访问
    std::string text() const;
    
    // 子元素集合
    BookmarkCollection bookmarks();
    FieldCollection fields();
    
    // 查找替换
    int replace(const std::string& old_text, const std::string& new_text);
    int replace(const std::regex& pattern, const std::string& replacement);
    
    // 删除内容
    void delete_content();
    
    // 格式化
    void apply_format(const ParagraphFormat& format);
    void apply_font_format(const Font& font);
    
    // 迭代器
    class iterator;
    iterator begin();
    iterator end();
    
private:
    Node* start_node_;
    Node* end_node_;
};

} // namespace cdocx
```

---

#### 5. 增强 DocumentBuilder

**建议实现**:

```cpp
namespace cdocx {

class DocumentBuilder {
public:
    explicit DocumentBuilder(Document* doc);
    
    // ========== 光标导航 ==========
    void move_to(Node* node);
    void move_to(const Bookmark& bookmark);
    void move_to_bookmark(const std::string& name);
    void move_to_bookmark(const std::string& name, bool is_start);
    void move_to_cell(int table_index, int row_index, int cell_index);
    void move_to_field(const Field& field);
    void move_to_header_footer(HeaderFooterType type);
    void move_to_merge_field(const std::string& field_name);
    void move_to_paragraph(int paragraph_index, int character_index);
    void move_to_section(int section_index);
    void move_to_document_start();
    void move_to_document_end();
    
    // ========== 内容插入 ==========
    // 文本
    void write(const std::string& text);
    void writeln(const std::string& text);
    void writeln();
    
    // 特殊字符
    void insert_break(BreakType break_type);
    void insert_field(const std::string& field_code);
    void insert_field(const std::string& field_code, const std::string& field_value);
    void insert_hyperlink(const std::string& display_text, const std::string& url);
    
    // 图片
    void insert_image(const std::string& file_name);
    void insert_image(const std::string& file_name, double width, double height);
    void insert_image(const std::vector<uint8_t>& image_data);
    void insert_image(const std::vector<uint8_t>& image_data, 
                      RelativeHorizontalPosition horz_pos,
                      double left, 
                      RelativeVerticalPosition vert_pos,
                      double top,
                      double width, 
                      double height,
                      WrapType wrap_type);
    
    // HTML
    void insert_html(const std::string& html);
    void insert_html(const std::string& html, const HtmlInsertOptions& options);
    
    // 书签
    BookmarkStart* start_bookmark(const std::string& name);
    BookmarkEnd* end_bookmark(const std::string& name);
    
    // ========== 表格构建 ==========
    Table* start_table();
    void end_table();
    void insert_cell();
    void end_row();
    
    // 单元格格式（影响后续插入的单元格）
    CellFormat* cell_format();
    RowFormat* row_format();
    
    // ========== 格式属性（上下文感知） ==========
    Font* font();  // 影响后续文本
    ParagraphFormat* paragraph_format();  // 影响后续段落
    PageSetup* page_setup();  // 影响当前节
    
    // ========== 当前位置信息 ==========
    Node* current_node() const;
    Paragraph* current_paragraph() const;
    Section* current_section() const;
    
private:
    Document* doc_;
    Node* current_node_;
    
    // 格式状态
    std::shared_ptr<Font> font_state_;
    std::shared_ptr<ParagraphFormat> para_format_state_;
};

} // namespace cdocx
```

---

#### 6. 实现标准集合类

**建议实现**:

```cpp
namespace cdocx {

// 模板化的节点集合
template<typename T>
class NodeCollection {
public:
    using value_type = std::shared_ptr<T>;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;
    
    // 容量
    size_t count() const;
    bool empty() const;
    
    // 元素访问（支持负数索引）
    std::shared_ptr<T> at(int index) const;
    std::shared_ptr<T> operator[](int index) const;
    std::shared_ptr<T> first() const;
    std::shared_ptr<T> last() const;
    
    // 修改
    void add(std::shared_ptr<T> item);
    void insert(int index, std::shared_ptr<T> item);
    void remove(std::shared_ptr<T> item);
    void remove_at(int index);
    void clear();
    
    // 查找
    template<typename Predicate>
    std::shared_ptr<T> find(Predicate pred) const;
    
    // 迭代器
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    
private:
    std::vector<std::shared_ptr<T>> items_;
    CompositeNode* parent_;
};

// 书签集合
class BookmarkCollection {
public:
    // 基本操作
    size_t count() const;
    
    // 索引访问
    std::shared_ptr<Bookmark> at(int index) const;
    std::shared_ptr<Bookmark> operator[](int index) const;
    std::shared_ptr<Bookmark> operator[](const std::string& name) const;
    
    // 查找
    std::shared_ptr<Bookmark> find(const std::string& name) const;
    bool contains(const std::string& name) const;
    
    // 修改
    void remove(std::shared_ptr<Bookmark> bookmark);
    void remove(const std::string& name);
    void remove_at(int index);
    void clear();
    
    // 迭代器支持
    class iterator;
    iterator begin();
    iterator end();
};

} // namespace cdocx
```

---

### 低优先级 (P3)

#### 7. 命名空间重构

**建议结构**:

```
cdocx::          // 核心类
  - Document
  - Node
  - CompositeNode
  - Range
  - DocumentVisitor
  - DocumentBuilder

cdocx::nodes     // 具体节点类型
  - Paragraph
  - Table
  - Run
  - Section
  - BookmarkStart/End

cdocx::tables    // 表格相关
  - Table
  - Row
  - Cell
  - RowCollection
  - CellCollection

cdocx::fields    // 域相关
  - Field
  - FieldStart/End/Separator
  - FormField
  - FieldCollection

cdocx::drawing   // 图形相关
  - Shape
  - ImageData
  - WrapType

cdocx::saving    // 保存相关
  - SaveOptions
  - DocxSaveOptions
  - PdfSaveOptions (未来)
  - HtmlSaveOptions (未来)

cdocx::loading   // 加载相关
  - LoadOptions

cdocx::replacing // 查找替换
  - FindReplaceOptions
  - IReplacingCallback
```

---

#### 8. 实现 SaveOptions 层次结构

**建议实现**:

```cpp
namespace cdocx {

enum class SaveFormat {
    Docx,
    Doc,
    Pdf,      // 未来
    Html,     // 未来
    Rtf,      // 未来
    Txt,
    Odt
};

class SaveOptions {
public:
    virtual ~SaveOptions() = default;
    
    // 保存格式
    virtual SaveFormat save_format() const = 0;
    
    // 通用选项
    bool pretty_format() const;
    void set_pretty_format(bool value);
    
    // 生成器名称（嵌入到文件中）
    bool export_generator_name() const;
    void set_export_generator_name(bool value);
    
    // 临时文件夹
    std::string temp_folder() const;
    void set_temp_folder(const std::string& value);
    
    // 进度回调
    void set_progress_callback(SaveProgressCallback* callback);
    
    // 创建具体选项的工厂方法
    static std::shared_ptr<SaveOptions> create(SaveFormat format);
};

class DocxSaveOptions : public SaveOptions {
public:
    SaveFormat save_format() const override { return SaveFormat::Docx; }
    
    // OOXML 合规性
    OoxmlCompliance compliance() const;
    void set_compliance(OoxmlCompliance value);
    
    // 压缩级别
    CompressionLevel compression_level() const;
    void set_compression_level(CompressionLevel value);
};

class HtmlSaveOptions : public SaveOptions {
public:
    SaveFormat save_format() const override { return SaveFormat::Html; }
    
    // HTML 版本
    HtmlVersion html_version() const;
    void set_html_version(HtmlVersion value);
    
    // 图片处理
    bool export_images_as_base64() const;
    void set_export_images_as_base64(bool value);
    std::string images_folder() const;
    void set_images_folder(const std::string& value);
    
    // CSS
    CssStyleSheetType css_style_sheet_type() const;
    void set_css_style_sheet_type(CssStyleSheetType value);
    std::string css_style_sheet_file_name() const;
    void set_css_style_sheet_file_name(const std::string& value);
    
    // 字体
    bool export_fonts_as_base64() const;
    void set_export_fonts_as_base64(bool value);
};

} // namespace cdocx
```

---

#### 9. 事件和回调机制

**建议实现**:

```cpp
namespace cdocx {

// 保存进度回调
class SaveProgressCallback {
public:
    virtual ~SaveProgressCallback() = default;
    virtual void on_progress(int percent_done) = 0;
    virtual bool is_canceled() const { return false; }
};

// 资源加载回调（用于加载 HTML 等）
class ResourceLoadingCallback {
public:
    virtual ~ResourceLoadingCallback() = default;
    virtual ResourceLoadingAction on_resource_loading(
        const std::string& original_uri,
        std::vector<uint8_t>& data) = 0;
};

// 查找替换回调
class IReplacingCallback {
public:
    virtual ~IReplacingCallback() = default;
    virtual ReplaceAction on_replacing(const ReplacingArgs& args) = 0;
};

struct ReplacingArgs {
    std::string match_text;
    std::string replacement_text;
    Node* match_node;
    int match_offset;
    bool is_match_found;
};

enum class ReplaceAction {
    Replace,      // 执行替换
    Skip,         // 跳过此匹配
    Break         // 停止查找
};

// 节点变更通知
class INodeChangingCallback {
public:
    virtual ~INodeChangingCallback() = default;
    virtual void on_node_inserting(const Node& node, const CompositeNode& parent) {}
    virtual void on_node_inserted(const Node& node, const CompositeNode& parent) {}
    virtual void on_node_removing(const Node& node, const CompositeNode& parent) {}
    virtual void on_node_removed(const Node& node, const CompositeNode& parent) {}
};

} // namespace cdocx
```

---

#### 10. 文档比较和修订功能

**建议实现**:

```cpp
namespace cdocx {

class CompareOptions {
public:
    // 比较粒度
    Granularity granularity() const;  // CharLevel, WordLevel
    void set_granularity(Granularity value);
    
    // 忽略选项
    bool ignore_case_changes() const;
    bool ignore_tables() const;
    bool ignore_fields() const;
    bool ignore_comments() const;
    bool ignore_textboxes() const;
    bool ignore_formatting() const;
    bool ignore_headers_and_footers() const;
};

class DocumentComparer {
public:
    // 比较文档
    static void compare(Document& doc1, const Document& doc2, 
                        const CompareOptions& options);
    static void compare(Document& doc1, const Document& doc2,
                        const std::string& author, 
                        const DateTime& date_time);
};

class Revision {
public:
    RevisionType type() const;  // Insertion, Deletion, FormatChange
    std::string author() const;
    DateTime date_time() const;
    Node* parent_node() const;
    std::string text() const;
    
    void accept();
    void reject();
};

class RevisionCollection {
public:
    size_t count() const;
    std::shared_ptr<Revision> at(int index) const;
    
    void accept_all();
    void reject_all();
    void accept_all(const std::string& author);
    void reject_all(const std::string& author);
};

} // namespace cdocx
```

---

## 优先级与实施路线图

### Phase 1: 核心架构重构 (2-3 个月)

| 优先级 | 功能 | 工作量 | 依赖 |
|--------|------|--------|------|
| P1 | Node 基类层次结构 | 大 | 无 |
| P1 | DocumentVisitor 模式 | 中 | Node 基类 |
| P1 | 格式属性分离 | 大 | 无 |

**目标**: 建立坚实的架构基础

---

### Phase 2: API 增强 (2 个月)

| 优先级 | 功能 | 工作量 | 依赖 |
|--------|------|--------|------|
| P2 | Range 概念实现 | 中 | Node 基类 |
| P2 | DocumentBuilder 增强 | 中 | 无 |
| P2 | 标准集合类 | 中 | Node 基类 |

**目标**: 提供更便捷的 API

---

### Phase 3: 高级功能 (3 个月)

| 优先级 | 功能 | 工作量 | 依赖 |
|--------|------|--------|------|
| P3 | 命名空间重构 | 中 | 无 |
| P3 | SaveOptions 层次结构 | 中 | 无 |
| P3 | 事件回调机制 | 小 | 无 |
| P3 | 文档比较功能 | 大 | 修订追踪 |

**目标**: 支持高级用例

---

## 参考对比表

| 功能类别 | Aspose.Words | CDocx 当前 | 建议增强 |
|----------|--------------|------------|----------|
| **DOM 架构** | 完整 Node 层次 | 扁平结构 | 统一 Node 基类 |
| **Visitor 模式** | 完整支持 | 无 | 实现 DocumentVisitor |
| **Range 概念** | 完整支持 | 部分支持 | 增强 Range 功能 |
| **格式分离** | 属性类分离 | 混合设计 | 分离 ParagraphFormat/Font |
| **集合类** | 标准接口 | 自定义 | 实现标准集合接口 |
| **Builder 模式** | 强大的 DocumentBuilder | 基本实现 | 增强导航和插入 |
| **命名空间** | 功能分离 | 单一命名空间 | 重构命名空间 |
| **保存选项** | 层次结构 | 无 | 实现 SaveOptions |
| **事件机制** | 丰富回调 | 无 | 添加回调支持 |
| **文档比较** | 完整支持 | 无 | 添加比较功能 |

---

## 总结

通过借鉴 Aspose.Words C++ 的优秀设计，CDocx 可以在以下方面获得显著提升：

1. **架构层面**: 建立统一的 Node 基类和 Visitor 模式，为复杂操作奠定基础
2. **API 设计**: 提供更便捷、更一致的 API 接口
3. **功能扩展**: 支持更多高级功能如文档比较、批量处理等
4. **可维护性**: 通过更好的模块化和命名空间组织提高代码质量

建议按优先级逐步实施，确保每个阶段的稳定性和向后兼容性。

---

*文档结束*
