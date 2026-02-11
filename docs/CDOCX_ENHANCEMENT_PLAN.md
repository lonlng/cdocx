# CDocx 增强计划 - 借鉴 minidocx (C++17 兼容)

## 目标
借鉴 minidocx 的优秀设计，在保持 C++17 标准的前提下，增强 CDocx 的功能和API设计。

## Phase 1: 属性结构体系统

### 1.1 文本属性 (TextProperties)

```cpp
namespace cdocx {

struct TextProperties {
    // 字体设置
    struct Font {
        std::string ascii = "Times New Roman";
        std::string eastAsia = "SimSun";  // 中文字体
        std::string hAnsi = "Times New Roman";
        std::string cs = "Times New Roman";
        
        enum class Hint { Default, EastAsia, ComplexScript };
        Hint hint = Hint::Default;
    };
    std::optional<Font> font;
    
    // 字体样式
    struct FontStyle {
        bool bold = false;
        bool italic = false;
    } fontStyle;
    
    // 字号 (以半点为单位，24 = 12pt)
    int fontSize = 0;
    
    // 字体颜色 (RRGGBB 或 "auto")
    std::string color;
    
    // 下划线样式
    enum class UnderlineStyle {
        None,
        Single,          // 单实线
        Double,          // 双实线
        Thick,           // 粗单实线
        Dotted,          // 点虚线
        DottedHeavy,     // 粗点虚线
        Dash,            // 短划线
        DashedHeavy,     // 粗短划线
        DashLong,        // 长划线
        DashLongHeavy,   // 粗长划线
        DotDash,         // 点划线
        DashDotHeavy,    // 粗点划线
        DotDotDash,      // 点点划线
        DashDotDotHeavy, // 粗点点划线
        Wave,            // 波浪线
        WavyDouble,      // 双波浪线
        WavyHeavy        // 粗波浪线
    };
    struct Underline {
        UnderlineStyle style = UnderlineStyle::None;
        std::string color = "auto";
    } underline;
    
    // 删除线样式
    enum class StrikeStyle { None, Single, Double };
    StrikeStyle strike = StrikeStyle::None;
    
    // 垂直对齐
    enum class VertAlign { None, Superscript, Subscript };
    VertAlign vertAlign = VertAlign::None;
    
    // 高亮颜色
    enum class Highlight {
        None, Black, White, Red, Green, Blue, Yellow, Cyan, Magenta,
        DarkRed, DarkGreen, DarkBlue, DarkYellow, DarkCyan, DarkMagenta,
        DarkGray, LightGray
    } highlight = Highlight::None;
    
    // 字符缩放 (1-600，100 = 正常)
    int scale = 100;
    
    // 字符间距
    enum class SpacingType { Normal, Expanded, Condensed };
    struct Spacing {
        SpacingType type = SpacingType::Normal;
        int value = 20;  // 20 = 1pt
    } spacing;
    
    // 位置调整
    enum class PositionType { Normal, Raised, Lowered };
    struct Position {
        PositionType type = PositionType::Normal;
        int value = 2;  // 2 = 1pt
    } position;
    
    // 应用到 Run 的方法
    void applyTo(Run& run) const;
    void applyTo(pugi::xml_node run_node) const;  // 直接应用到XML节点
};

} // namespace cdocx
```

### 1.2 段落属性 (ParagraphProperties)

```cpp
namespace cdocx {

struct ParagraphProperties {
    // 样式ID
    std::string styleId;
    
    // 对齐方式
    enum class Alignment { Left, Centered, Right, Justified, Distributed };
    std::optional<Alignment> align;
    
    // 大纲级别
    enum class OutlineLevel { Level1, Level2, Level3, Level4, Level5, 
                              Level6, Level7, Level8, Level9, BodyText };
    OutlineLevel outlineLevel = OutlineLevel::BodyText;
    
    // 缩进
    struct Indentation {
        enum class Type { Character, Absolute };
        
        struct Indent {
            Type type = Type::Absolute;
            int value = 0;  // Character: 100 = 1 char, Absolute: 1440 = 1 inch
        };
        Indent left;
        Indent right;
        
        struct Special {
            enum class Kind { None, FirstLine, Hanging };
            Kind kind = Kind::None;
            Type type = Type::Character;
            int value = 0;
        } special;
    };
    std::optional<Indentation> indent;
    
    // 间距
    struct Spacing {
        enum class Type { Auto, Lines, Absolute };
        
        struct ParaSpacing {
            Type type = Type::Auto;
            int value = 0;  // Lines: 100 = 1 line, Absolute: 1440 = 1 inch
        };
        ParaSpacing before;
        ParaSpacing after;
        
        enum class LineSpacingType { Lines, AtLeast, Exactly };
        struct LineSpacing {
            LineSpacingType type = LineSpacingType::Lines;
            int value = 240;  // 240 = 1 line = 12pt
        } lineSpacing;
    };
    std::optional<Spacing> spacing;
    
    // 分页控制
    bool keepNext = false;      // 与下段同页
    bool keepLines = false;     // 段中不分页
    bool pageBreakBefore = false;  // 段前分页
    bool pageBreakAfter = false;   // 段后分页
    
    // 段落边框
    struct Border {
        enum class Style { None, Single, Double, Thick, Dotted, Dash, DotDash };
        Style style = Style::None;
        int size = 4;  // 1/8 point, 4 = 1/2 point
        std::string color = "auto";
        int space = 1;  // point
    };
    struct Borders {
        std::optional<Border> top;
        std::optional<Border> left;
        std::optional<Border> bottom;
        std::optional<Border> right;
    };
    std::optional<Borders> borders;
    
    // 应用到 Paragraph 的方法
    void applyTo(Paragraph& para) const;
    void applyTo(pugi::xml_node para_node) const;
};

} // namespace cdocx
```

### 1.3 Run 类新增属性支持

```cpp
class Run {
public:
    // 现有方法...
    
    // 新的属性方法
    void setProperties(const TextProperties& props);
    TextProperties getProperties() const;
    
    // 便捷方法 - 高亮
    bool setHighlight(TextProperties::Highlight color);
    
    // 便捷方法 - 字符间距
    bool setSpacing(TextProperties::SpacingType type, int value);
    
    // 便捷方法 - 位置调整
    bool setPosition(TextProperties::PositionType type, int value);
    
    // 便捷方法 - 字符缩放
    bool setScale(int percent);
    
    // 便捷方法 - 扩展下划线
    bool setUnderline(TextProperties::UnderlineStyle style, const std::string& color = "auto");
    
    // 便捷方法 - 删除线
    bool setStrike(TextProperties::StrikeStyle style);
};
```

### 1.4 Paragraph 类新增属性支持

```cpp
class Paragraph {
public:
    // 现有方法...
    
    // 新的属性方法
    void setProperties(const ParagraphProperties& props);
    ParagraphProperties getProperties() const;
    
    // 便捷方法 - 大纲级别
    bool setOutlineLevel(ParagraphProperties::OutlineLevel level);
    
    // 便捷方法 - 分页控制
    bool setKeepNext(bool value);
    bool setKeepLines(bool value);
    bool setPageBreakBefore(bool value);
    bool setPageBreakAfter(bool value);
    
    // 便捷方法 - 段落边框
    bool setBorders(const ParagraphProperties::Borders& borders);
};
```

---

## Phase 2: 表格功能增强

### 2.1 直接单元格访问

```cpp
class Table {
public:
    // 现有方法...
    
    // 直接访问单元格（带边界检查）
    TableCell cellAt(size_t row, size_t col) const;
    
    // 不安全访问（性能优先）
    TableCell cellAtUnsafe(size_t row, size_t col) const;
    
    // 获取表格尺寸
    size_t getRowCount() const;
    size_t getColumnCount() const;
    
    // 合并单元格
    TableCell merge(size_t startRow, size_t startCol, 
                    size_t rowCount, size_t colCount);
    
    // 拆分单元格
    void split(size_t row, size_t col);
    
    // 调试输出
    void dumpStructure() const;
};
```

### 2.2 表格属性

```cpp
struct TableProperties {
    // 表格宽度
    enum class WidthType { Auto, Percent, Absolute };
    struct Width {
        WidthType type = WidthType::Auto;
        int value = 0;  // Percent: 5000 = 100%, Absolute: 1440 = 1 inch
    } width;
    
    // 对齐方式
    ParagraphProperties::Alignment alignment = ParagraphProperties::Alignment::Left;
    
    // 表格边框
    ParagraphProperties::Borders borders;
    
    // 单元格边距
    struct CellMargin {
        int top = 0;
        int left = 0;
        int bottom = 0;
        int right = 0;
    } cellMargin;
    
    // 应用到 Table
    void applyTo(Table& table) const;
};
```

---

## Phase 3: 节(Section)支持

### 3.1 Section 类

```cpp
class Section {
public:
    Section();
    explicit Section(pugi::xml_node sectPr_node);
    
    // 页面设置
    struct PageSize {
        int width = 12240;   // 默认 A4 宽度 (twips, 12240 = 8.5 inch)
        int height = 15840;  // 默认 A4 高度 (twips, 15840 = 11 inch)
    };
    void setPageSize(const PageSize& size);
    PageSize getPageSize() const;
    
    // 页面方向
    enum class Orientation { Portrait, Landscape };
    void setOrientation(Orientation orient);
    Orientation getOrientation() const;
    
    // 页边距
    struct PageMargins {
        int top = 1440;     // 1 inch
        int right = 1440;   // 1 inch
        int bottom = 1440;  // 1 inch
        int left = 1440;    // 1 inch
        int header = 720;   // 0.5 inch
        int footer = 720;   // 0.5 inch
    };
    void setPageMargins(const PageMargins& margins);
    PageMargins getPageMargins() const;
    
    // 分栏
    struct Columns {
        int count = 1;
        int space = 720;  // 0.5 inch
        bool separator = false;
    };
    void setColumns(const Columns& cols);
    Columns getColumns() const;
    
    // 应用属性
    void applyProperties();
};
```

### 3.2 Document 类新增方法

```cpp
class Document {
public:
    // 现有方法...
    
    // 节操作
    Section& sections();
    Section addSection();
    void deleteSection(const Section& section);
    void clearSections();
};
```

---

## Phase 4: 列表/编号系统

### 4.1 抽象编号定义

```cpp
struct AbstractNumbering {
    int id;
    
    enum class Type { Decimal, LowerLetter, UpperLetter, 
                      LowerRoman, UpperRoman, Bullet, None };
    
    struct Level {
        int level = 0;  // 0-8
        Type type = Type::Decimal;
        std::string format;  // 例如: "%1." "%1.%2." "\u2022" (bullet)
        TextProperties textProps;
        ParagraphProperties paraProps;
        int start = 1;
        int indent = 720;  // 悬挂缩进
    };
    std::array<std::optional<Level>, 9> levels;
    
    // 创建预定义列表类型
    static AbstractNumbering makeNumberedList(int id);
    static AbstractNumbering makeBulletedList(int id, const std::string& bullet = "\u2022");
};
```

### 4.2 编号实例

```cpp
struct NumberingInstance {
    int id;
    int abstractId;  // 关联的 AbstractNumbering ID
};
```

### 4.3 Document 类新增方法

```cpp
class Document {
public:
    // 添加抽象编号定义
    int addAbstractNumbering(const AbstractNumbering& def);
    
    // 添加编号实例
    int addNumberingInstance(int abstractId);
    
    // 便捷方法
    int addNumberedListDefinition();
    int addBulletedListDefinition(const std::string& bullet = "\u2022");
};
```

### 4.4 Paragraph 类新增方法

```cpp
class Paragraph {
public:
    // 设置列表
    void setNumbering(int numId, int level = 0);
    void clearNumbering();
};
```

---

## Phase 5: 样式系统

### 5.1 样式定义

```cpp
struct Style {
    enum class Type { Paragraph, Character, Table };
    
    Type type;
    std::string styleId;
    std::string name;
    std::string basedOn;  // 基于的样式ID
    std::string next;     // 下一个段落样式
    
    // 属性（根据类型使用）
    ParagraphProperties paraProps;
    TextProperties textProps;
    
    // 是否为默认样式
    bool isDefault = false;
    bool isCustom = true;
};
```

### 5.2 Document 类新增方法

```cpp
class Document {
public:
    // 添加样式
    void addStyle(const Style& style);
    
    // 获取样式
    std::optional<Style> getStyle(const std::string& styleId) const;
    
    // 检查样式是否存在
    bool hasStyle(const std::string& styleId) const;
    
    // 删除样式
    bool deleteStyle(const std::string& styleId);
    
    // 列出所有样式
    std::vector<std::string> getStyleNames() const;
};
```

### 5.3 Paragraph 类增强

```cpp
class Paragraph {
public:
    // 应用样式
    bool applyStyle(const std::string& styleId);
    
    // 获取当前样式
    std::string getStyleId() const;
};
```

---

## 实施顺序

1. **Phase 1**: 属性结构体系统（文本+段落属性）- 基础架构
2. **Phase 2**: 增强现有类的方法（Run, Paragraph）- 立即可用
3. **Phase 3**: 表格功能增强 - 常用功能
4. **Phase 4**: 节(Section)支持 - 页面布局
5. **Phase 5**: 列表/编号系统 - 文档结构
6. **Phase 6**: 样式系统 - 高级功能

---

## API 兼容性

所有新增功能均为增量添加：
- 现有 API 保持不变
- 新属性结构体作为可选方案
- 新方法作为现有方法的补充
- 完全向后兼容
