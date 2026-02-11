# Minidocx 分析与 CDocx 优化建议

## 目录
1. [项目概览对比](#1-项目概览对比)
2. [架构设计对比](#2-架构设计对比)
3. [Minidocx 优秀功能详解](#3-minidocx-优秀功能详解)
4. [优化建议](#4-优化建议)
5. [实施路线图](#5-实施路线图)

---

## 1. 项目概览对比

### 1.1 基本属性

| 特性 | CDocx | Minidocx |
|------|-------|----------|
| **语言标准** | C++17 | C++20 |
| **CMake 版本** | 3.10+ | 3.28+ |
| **主要用途** | 读写 DOCX 文件 | 生成 DOCX 文件 |
| **设计重点** | 完整的文档操作 | 简洁的文档创建 |
| **当前版本** | 0.4.0 | 1.0 Beta |
| **许可证** | MIT | MIT |

### 1.2 功能对比矩阵

| 功能 | CDocx | Minidocx | 状态 |
|------|-------|----------|------|
| **基础功能** |
| 创建文档 | ✅ | ✅ | 都有 |
| 读取文档 | ✅ | ⚠️ | CDocx 更强 |
| 段落操作 | ✅ | ✅ | 都有 |
| 文本格式 | ✅ | ✅ | 都有 |
| 表格 | ✅ | ✅ | 都有 |
| 图片插入 | ✅ | ✅ | 都有 |
| **高级功能** |
| 模板替换 | ✅ | ❌ | CDocx 独有 |
| 文档合并 | ✅ | ❌ | CDocx 独有 |
| 书签管理 | ✅ | ❌ | CDocx 独有 |
| XML Parts API | ✅ | ❌ | CDocx 独有 |
| 媒体管理 | ✅ | ❌ | CDocx 独有 |
| **格式化功能** |
| 分节(Section) | ⚠️ | ✅ | Minidocx 更强 |
| 样式系统 | ⚠️ | ✅ | Minidocx 更强 |
| 列表(编号/项目符号) | ⚠️ | ✅ | Minidocx 更强 |
| 页面设置 | ✅ | ✅ | 都有 |
| **文档属性** |
| 文档元数据 | ✅ | ✅ | 都有 |
| 标题/作者/主题 | ✅ | ✅ | 都有 |

---

## 2. 架构设计对比

### 2.1 CDocx 架构

```
Document (PIMPL模式)
├── DocumentImpl (内部实现)
│   ├── DocxTree (树结构存储)
│   ├── XML Parts (所有XML部件)
│   └── Media Files (媒体文件)
├── Paragraph (迭代器)
│   └── Run (格式化文本)
├── Table (迭代器)
│   ├── TableRow
│   └── TableCell
│       └── Paragraph
├── Template (模板替换)
└── DocumentInserter (文档插入)
```

**特点：**
- 使用 PIMPL 模式隐藏实现细节
- 树形结构存储整个 DOCX 包
- 支持完整的读写操作
- 迭代器模式遍历内容

### 2.2 Minidocx 架构

```
Document (继承自 Package)
├── Package (ZIP 包管理)
│   ├── Parts (XML部件)
│   └── Relationships
├── Section (容器)
│   ├── Paragraph (块级)
│   │   ├── RichText (行内)
│   │   └── Picture (行内)
│   └── Table (块级)
│       └── Cell (容器)
│           └── Paragraph
├── Styles (样式定义)
└── Numbering (列表定义)
```

**特点：**
- 清晰的文档对象模型 (DOM)
- Section 作为内容容器
- 使用 shared_ptr 管理对象生命周期
- 属性结构体公开，便于设置

---

## 3. Minidocx 优秀功能详解

### 3.1 🌟 Section (分节) 支持

**为什么重要：**
- 分节是 Word 文档的核心概念
- 不同节可以有独立的页面设置
- 支持页眉页脚的不同设置

**Minidocx 的实现：**
```cpp
Document doc;
SectionPointer sect = doc.addSection();
sect->prop_.landscape_ = true;  // 横向页面
sect->prop_.size_.width_ = A3_W; // A3 纸张
```

**CDocx 现状：**
- 缺乏明确的 Section 概念
- 页面设置分散在 document.xml 中

**优化建议：**
```cpp
// 建议添加的 API
class Section {
public:
    SectionProperties prop_;
    
    ParagraphPointer addParagraph();
    TablePointer addTable(rows, cols);
};

class Document {
    SectionPointer addSection();
    std::list<SectionPointer> sections() const;
};
```

### 3.2 🌟 属性结构体设计

**Minidocx 的优秀设计：**
```cpp
// 公开的结构体属性
struct ParagraphProperties {
    std::optional<Alignment> align_;
    OutlineLevel outlineLevel_;
    std::optional<Indentation> indent_;
    std::optional<Spacing> spacing_;
};

class Paragraph {
public:
    ParagraphProperties prop_;  // 公开的属性结构体
};

// 使用方式非常直观
para->prop_.align_ = Alignment::Centered;
para->prop_.outlineLevel_ = ParagraphProperties::OutlineLevel::Level1;
```

**优点：**
1. **直观易用**：属性一目了然
2. **类型安全**：编译时检查
3. **可扩展**：添加新属性不影响现有代码
4. **可选值**：使用 `std::optional` 表示未设置

**CDocx 现状：**
- 使用单独的方法设置每个属性
- 已经借鉴了 minidocx 的设计，添加了 properties.h

### 3.3 🌟 富文本属性 (RichTextProperties)

**Minidocx 的详细属性：**
```cpp
struct RichTextProperties {
    // 字体设置（支持四种字符集）
    struct Font {
        std::string ascii_ = "Courier New";      // 西文
        std::string eastAsia_ = "Simsun";        // 中日韩
        std::string hAnsi_ = "Times New Roman";  // 高 ANSI
        std::string cs_ = "Times New Roman";     // 复杂文种
    };
    
    // 丰富的下划线样式
    enum class UnderlineStyle {
        None, Single, Double, Thick,
        Dotted, DottedHeavy, Dash, DashedHeavy,
        DashLong, DashLongHeavy,
        DotDash, DashDotHeavy,
        DotDotDash, DashDotDotHeavy,
        Wave, WavyDouble, WavyHeavy
    };
    
    // 高亮颜色
    enum class Highlight {
        None, Black, White, Red, Green, Blue,
        Yellow, Cyan, Magenta, ...
    };
    
    // 字符缩放和间距
    size_t scale_ = 100;  // 1-600%
    Spacing spacing_;
    Position position_;
};
```

**CDocx 可以借鉴：**
- 已部分借鉴，添加在 properties.h 中

### 3.4 🌟 列表系统 (Numbering)

**Minidocx 的完整列表支持：**
```cpp
// 创建列表定义
const NumberingId numId1 = doc.addBulletedListDefinition();
const NumberingId numId2 = doc.addNumberedListDefinition();

// 应用到段落
ParagraphPointer para = sect->addParagraph();
para->addRichText("Level one");
para->numId_ = numId1;  // 列表 ID
para->level_ = NumberingLevel::Level2;  // 级别
```

**支持的列表样式：**
- 项目符号 (Bullet)
- 数字 (Decimal)
- 罗马数字 (Upper/Lower Roman)
- 字母 (Upper/Lower Letter)
- 序数文本 (Ordinal Text)

**CDocx 现状：**
- 缺乏列表系统的 API

### 3.5 🌟 样式系统 (Styles)

**Minidocx 的样式定义：**
```cpp
// 定义段落样式
ParagraphStyle paraStyle;
paraStyle.name_ = "My Heading 1";
paraStyle.align_ = Alignment::Centered;
paraStyle.outlineLevel_ = ParagraphProperties::OutlineLevel::Level1;
paraStyle.fontSize_ = 32;
paraStyle.color_ = "FF0000";
doc.addParagraphStyle(paraStyle);

// 应用样式
ParagraphPointer para = sect->addParagraph();
para->prop_.style_ = "My Heading 1";
```

**优点：**
1. 可以预定义样式
2. 样式继承（ParagraphStyle 继承 CharacterStyle）
3. 样式复用，减少重复代码

### 3.6 🌟 表格操作

**Minidocx 的表格 API：**
```cpp
// 创建表格
TablePointer tbl = sect->addTable(5, 7);
tbl->prop_.width_.type_ = TableProperties::WidthType::Percent;

// 访问单元格
tbl->cellAt(0, 0)->addParagraph()->addRichText("AAA");

// 合并单元格
tbl->merge(1, 1, 2, 3);  // row, col, rows, cols
tbl->cellAt(1, 1)->addParagraph()->addRichText("BBB");

// 调试输出
tbl->dumpStructure();
```

**内部实现：**
```cpp
class Table {
    std::vector<std::vector<size_t>> grid_;  // 单元格映射网格
    std::vector<CellPointer> cells_;          // 实际单元格
    std::vector<Rect> merged_;                // 合并区域记录
    
    CellPointer merge(const Rect rect);       // 合并
    void split(const size_t row, const size_t col);  // 拆分
};
```

**CDocx 可以借鉴：**
- 内部网格结构更清晰
- 合并/拆分操作更直观

### 3.7 🌟 异常处理

**Minidocx 的统一异常：**
```cpp
try {
    Document doc;
    doc.load("file.docx");
    // ...
}
catch (const Exception& ex) {
    std::cerr << ex.what() << std::endl;
}
```

**优点：**
- 统一的异常基类
- 简化的错误处理

### 3.8 🌟 单头文件包含

**Minidocx 的设计：**
```cpp
#include "minidocx/minidocx.hpp"
// 包含所有功能
```

**CDocx 现状：**
```cpp
#include <cdocx.h>
// 包含所有功能
```
- 两者都做到了这一点

---

## 4. 优化建议

### 4.1 高优先级：Section (分节) 支持

**为什么重要：**
1. Word 文档的核心概念
2. 页面设置的基础
3. 页眉页脚的控制单元

**建议实现：**
```cpp
// include/cdocx/section.h
namespace cdocx {

class Section {
private:
    pugi::xml_node sectPr_node_;  // section properties
    pugi::xml_node body_node_;    // section content
    
public:
    Section();
    Section(pugi::xml_node sectPr, pugi::xml_node body);
    
    // Properties
    SectionProperties prop_;
    
    // Content operations
    ParagraphPointer addParagraph();
    TablePointer addTable(size_t rows, size_t cols);
    
    // Iterator support
    std::list<Paragraph> paragraphs();
    std::list<Table> tables();
};

} // namespace cdocx
```

### 4.2 高优先级：列表系统完善

**建议实现：**
```cpp
// include/cdocx/numbering.h
namespace cdocx {

class Document {
public:
    // 创建列表定义
    NumberingId addBulletedListDefinition();
    NumberingId addNumberedListDefinition(NumberStyle style = NumberStyle::Decimal);
    
    // 自定义列表
    NumberingId addAbstractNumDefinition(const AbstractNumberingDefinition& def);
    NumberingId addNumDefinition(NumberingId abstractId);
};

class Paragraph {
public:
    // 列表设置
    void setNumbering(NumberingId numId, NumberingLevel level = NumberingLevel::Level1);
    void removeNumbering();
};

} // namespace cdocx
```

### 4.3 中优先级：样式系统增强

**建议实现：**
```cpp
// include/cdocx/styles.h
namespace cdocx {

class Document {
public:
    // 添加样式
    void addParagraphStyle(const ParagraphStyle& style);
    void addCharacterStyle(const CharacterStyle& style);
    void addTableStyle(const TableStyle& style);
    
    // 获取样式
    ParagraphStyle getParagraphStyle(const std::string& name) const;
    
    // 应用样式
    void applyStyle(const std::string& styleName);
};

} // namespace cdocx
```

### 4.4 中优先级：表格操作增强

**建议实现：**
```cpp
// 增强 Table 类
class Table {
public:
    // 直接访问单元格（已有）
    TableCell cellAt(size_t row, size_t col) const;
    
    // 合并单元格（已有）
    TableCell merge(size_t startRow, size_t startCol, 
                    size_t rowCount, size_t colCount);
    
    // 拆分单元格（已有）
    void split(size_t row, size_t col);
    
    // 新增：批量操作
    void mergeCells(const std::vector<std::pair<size_t, size_t>>& cells);
    
    // 新增：表格属性设置
    void setWidth(int value, TableProperties::WidthType type);
    void setAlignment(ParagraphProperties::Alignment align);
    void setBorders(const TableBorders& borders);
};
```

### 4.5 低优先级：API 风格统一

**现状：**
```cpp
// 当前 CDocx 风格
doc.paragraphs().add_run("text", cdocx::bold);
para.set_alignment("center");
```

**建议统一（可选）：**
```cpp
// 保留原有风格的同时，添加类似 minidocx 的风格
ParagraphPointer para = sect->addParagraph();
para->prop_.align_ = Alignment::Centered;
para->addRichText("text")->prop_.fontStyle_.bold_ = true;
```

---

## 5. 实施路线图

### Phase 1: 核心功能增强 (v0.5.0)
- [ ] Section (分节) 支持
- [ ] 完善的页面设置 API
- [ ] 列表系统 (Numbering)

### Phase 2: 样式系统 (v0.6.0)
- [ ] 段落样式定义
- [ ] 字符样式定义
- [ ] 样式继承机制

### Phase 3: 表格增强 (v0.7.0)
- [ ] 表格属性完善
- [ ] 单元格合并/拆分优化
- [ ] 表格样式支持

### Phase 4: 文档完善 (v0.8.0)
- [ ] 更多示例代码
- [ ] 完整 API 文档
- [ ] 性能基准测试

---

## 总结

### CDocx 的优势
1. ✅ 完整的 DOCX 读写能力
2. ✅ XML Parts API 提供底层访问
3. ✅ 模板替换系统
4. ✅ 文档合并功能
5. ✅ 书签管理
6. ✅ 媒体文件管理

### Minidocx 的优势
1. 🌟 Section (分节) 概念清晰
2. 🌟 属性结构体设计直观
3. 🌟 完善的列表系统
4. 🌟 样式系统支持
5. 🌟 简洁的 API 设计

### 推荐优先实现的改进
1. **Section 支持** - 这是 Word 文档的核心概念
2. **列表系统** - 常用功能，缺失明显
3. **样式系统** - 提高代码复用性

通过借鉴 minidocx 的优秀设计，同时保持 CDocx 的读写能力和高级功能，可以使 CDocx 成为更完善的 DOCX 处理库。
