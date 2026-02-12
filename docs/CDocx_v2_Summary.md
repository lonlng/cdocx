# CDocx v2.0 架构重构总结

## 概述

基于对 Aspose.Words.C++ 设计模式和 TestWord.docx 实际结构的深入分析，完成了 CDocx v2.0 的全新架构设计。

---

## 核心设计改进

### 1. 类层次结构重构

**旧版设计问题：**
- 迭代器模式不够直观
- 缺乏统一的节点基类
- 父子关系管理不清晰

**新版设计：**

```
Node (基类)
├── CompositeNode (可包含子节点)
│   ├── Document
│   ├── Section
│   ├── Body
│   ├── HeaderFooter
│   ├── Paragraph
│   ├── Table
│   ├── Row
│   └── Cell
└── 叶子节点
    ├── Run
    ├── SpecialChar
    ├── Field
    ├── BookmarkStart/End
    └── Picture
```

**关键改进：**
- 统一使用 `std::shared_ptr` 管理对象生命周期
- 清晰的父子关系管理
- 支持克隆和访问者模式

### 2. 集合类设计

**旧版：**
```cpp
// 迭代器模式，需要手动遍历
for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
    // 处理段落
}
```

**新版：**
```cpp
// 现代 C++ 范围 for
for (auto& para : doc->get_paragraphs()) {
    // 处理段落
}

// 或索引访问
auto paras = doc->get_paragraphs();
auto first = paras[0];
auto last = paras.last();
```

### 3. 格式属性封装

**旧版：**
```cpp
para.set_alignment("center");
para.set_line_spacing(360);
para.set_indent(720, 0, 0);
```

**新版：**
```cpp
para->get_paragraph_format()
    .set_alignment(ParagraphAlignment::Center)
    .set_line_spacing(1.5)  // 倍数
    .set_first_line_indent(24);  // points
```

**优势：**
- 类型安全的枚举替代字符串
- 自动完成支持更好
- 单位清晰（points 而非 twips）

### 4. 链式调用支持

```cpp
// 创建并格式化段落
auto para = doc->get_body()->append_paragraph();
para->get_paragraph_format()
    .set_alignment(ParagraphAlignment::Center)
    .set_space_before(12)
    .set_space_after(12);

// 创建格式化文本
para->append_run("Bold Red Text")
    ->get_font()
    .set_bold(true)
    .set_color(Color::red())
    .set_size(14);
```

### 5. 表格操作增强

**旧版：**
```cpp
table.cellAt(row, col);
table.merge(startRow, startCol, rowCount, colCount);
```

**新版：**
```cpp
// 更自然的 API
table->get_cell(row, col);
table->merge_cells(start_row, start_col, end_row, end_col);

// 便捷构造
table->append_row({"Cell1", "Cell2", "Cell3"});

// Builder 模式
TableBuilder builder(doc);
auto table = builder
    .with_columns(3)
    .with_alignment(TableAlignment::Center)
    .add_header_row({"Name", "Age", "City"})
    .add_row({"John", "30", "NYC"})
    .build();
```

---

## 参考 Aspose 设计的核心特性

### 1. 访问者模式

```cpp
class MyVisitor : public DocumentVisitor {
public:
    void visit_paragraph_start(Paragraph& para) override {
        std::cout << "Entering paragraph" << std::endl;
    }
    
    void visit_run(Run& run) override {
        text_ += run.get_text();
    }
    
    std::string get_text() const { return text_; }
    
private:
    std::string text_;
};

MyVisitor visitor;
doc->accept(&visitor);
```

### 2. 字段系统

```cpp
// 页码
para->append_page_number();
para->append_num_pages();

// 日期
para->append_date("yyyy-MM-dd");

// 超链接
para->append_hyperlink("Click here", "https://example.com");
```

### 3. 节和页面设置

```cpp
auto section = doc->get_first_section();

// 页面设置
section->get_page_setup()
    .set_a4()
    .set_margins(72);  // 1 inch

// 页眉页脚
auto header = section->ensure_header(HeaderFooterType::Primary);
header->append_paragraph("Header Text");
```

---

## 从 TestWord.docx 学到的结构

### 1. 段落格式详细

```xml
<w:p>
    <w:pPr>
        <w:jc w:val="both"/>           <!-- 两端对齐 -->
        <w:ind w:firstLine="420"/>     <!-- 首行缩进 -->
        <w:rPr>                         <!-- 默认文本格式 -->
            <w:rFonts w:ascii="Verdana" w:eastAsia="宋体"/>
            <w:sz w:val="24"/>          <!-- 12pt -->
        </w:rPr>
    </w:pPr>
    <w:r>
        <w:rPr>
            <w:b/>                      <!-- 粗体 -->
            <w:color w:val="FF0000"/>  <!-- 红色 -->
        </w:rPr>
        <w:t>文本内容</w:t>
    </w:r>
</w:p>
```

**对应 API：**
```cpp
para->get_paragraph_format()
    .set_alignment(ParagraphAlignment::Justify)
    .set_first_line_indent(21);  // 约 0.74cm

auto run = para->append_run("文本内容");
run->get_font()
    .set_bold(true)
    .set_color(Color::red());
```

### 2. 表格结构

```xml
<w:tbl>
    <w:tblPr>
        <w:tblBorders>                  <!-- 边框 -->
            <w:top w:val="single" w:sz="4"/>
        </w:tblBorders>
    </w:tblPr>
    <w:tblGrid>                         <!-- 列宽定义 -->
        <w:gridCol w:w="2840"/>
    </w:tblGrid>
    <w:tr>                              <!-- 行 -->
        <w:tc>                          <!-- 单元格 -->
            <w:tcPr>
                <w:gridSpan w:val="2"/> <!-- 合并列 -->
                <w:vMerge w:val="restart"/> <!-- 合并行开始 -->
            </w:tcPr>
            <w:p>...</w:p>
        </w:tc>
    </w:tr>
</w:tbl>
```

**对应 API：**
```cpp
table->get_table_format()
    .get_borders()
    .set_top(Border::single(Color::black(), 0.5));

// 合并单元格
table->merge_cells(start_row, start_col, end_row, end_col);
```

### 3. 图片嵌入

```xml
<w:drawing>
    <wp:inline>
        <wp:extent cx="4829175" cy="3867150"/>  <!-- 尺寸 (EMU) -->
        <a:graphic>
            <pic:pic>
                <pic:blipFill>
                    <a:blip r:embed="rId4"/>      <!-- 关系 ID -->
                </pic:blipFill>
            </pic:pic>
        </a:graphic>
    </wp:inline>
</w:drawing>
```

**注：** 图片支持在 v2.0 中暂不实现，预留接口。

---

## 文件清单

### 新增/修改的头文件

| 文件 | 内容 | 状态 |
|-----|------|------|
| `include/cdocx/enums.h` | 所有枚举定义 | ✅ 已创建 |
| `include/cdocx/format.h` | Color, Border, Shading, Font, ParagraphFormat, TableFormat, CellFormat, RowFormat, PageSetup | ✅ 已创建 |
| `include/cdocx/node.h` | Node, CompositeNode, NodeCollection, DocumentVisitor | ✅ 已创建 |
| `include/cdocx/document.h` | Document, Section, Body, HeaderFooter, 集合类 | ✅ 已创建 |
| `include/cdocx/paragraph.h` | Paragraph, Run, SpecialChar, RunCollection, Field, Bookmark | ✅ 已创建 |
| `include/cdocx/table.h` | Table, Row, Cell, TableBuilder, 集合类 | ✅ 已创建 |
| `include/cdocx.h` | 主头文件 | ✅ 已更新 |

### 需要实现的源文件

| 文件 | 内容 | 预估工作量 |
|-----|------|-----------|
| `src/format.cpp` | 格式类方法实现 | 2天 |
| `src/node.cpp` | 节点树操作 | 2天 |
| `src/document.cpp` | 文档操作 | 3天 |
| `src/section.cpp` | 节和页面设置 | 2天 |
| `src/paragraph.cpp` | 段落和文本 | 3天 |
| `src/table.cpp` | 表格操作 | 3天 |
| `src/xml/*.cpp` | XML 序列化/反序列化 | 8天 |

---

## 迁移指南

### 主要 API 变化

| 旧 API | 新 API | 说明 |
|-------|-------|------|
| `Document doc("file.docx"); doc.open();` | `auto doc = Document::load_from_file("file.docx");` | 工厂方法 |
| `doc.paragraphs().add_run("text");` | `doc->get_body()->append_paragraph("text");` | 明确层级 |
| `para.set_alignment("center");` | `para->get_paragraph_format().set_alignment(ParagraphAlignment::Center);` | 类型安全 |
| `run.set_font_name("Arial");` | `run->get_font().set_name("Arial");` | 属性封装 |
| `table.cellAt(row, col)` | `table->get_cell(row, col)` | 更自然的命名 |
| `for (auto p = doc.paragraphs(); p.has_next(); p.next())` | `for (auto& p : doc->get_paragraphs())` | 现代 C++ |

### 向后兼容

提供 `include/cdocx/legacy.h` 兼容层：

```cpp
#include <cdocx/legacy.h>  // 旧代码无需修改

// 或使用新 API
#include <cdocx.h>         // 新代码推荐
```

---

## 下一步工作

1. **实现核心类** (Phase 1-3)
   - 格式类实现
   - 节点树操作
   - 段落和表格操作

2. **XML 序列化** (Phase 4)
   - OpenXML 格式写入
   - OpenXML 格式读取
   - 与 TestWord.docx 兼容

3. **测试和优化** (Phase 5)
   - 单元测试
   - 集成测试
   - 性能优化

4. **文档和示例**
   - API 文档
   - 使用示例
   - 迁移指南

---

## 总结

CDocx v2.0 新架构带来的价值：

1. **更直观的 API** - DOM 风格，类似浏览器开发
2. **更好的类型安全** - 枚举替代字符串
3. **现代 C++ 特性** - shared_ptr, 范围 for, 链式调用
4. **可扩展性** - 清晰的继承层次，易于添加新节点类型
5. **向后兼容** - 旧代码可以继续使用

**预计开发周期：6-8 周** (30天开发 + 测试)

**主要参考：**
- Aspose.Words.C++ 设计模式
- TestWord.docx 实际 XML 结构
- 现代 C++ 最佳实践
