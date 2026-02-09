# CDocx 高级 CRUD 功能

本文档描述了基于 Aspose.Words C++ 分析结果，为 cdocx 项目添加的高级增删改查功能。

## 功能概述

基于对 `thirdparty/asposeWordsCpp` 的分析，我们在 cdocx 中独立实现了以下功能类别：

### 1. Create (创建)

#### DocumentBuilder 类
一个简化文档构建的类，类似于 Aspose.Words 的 DocumentBuilder：

```cpp
cdocx::DocumentBuilder builder(&doc);

// 文本插入
builder.write("Hello ");
builder.set_bold(true);
builder.write("World");
builder.writeln();  // 换行

// 表格创建
builder.start_table();
builder.insert_row();
builder.insert_cell();
builder.write("Cell 1");
builder.insert_cell();
builder.write("Cell 2");
builder.end_row();
builder.end_table();

// 超链接
builder.insert_hyperlink("Click here", "https://example.com");

// 书签
builder.start_bookmark("Section1");
builder.write("Bookmarked content");
builder.end_bookmark("Section1");

// 图片
builder.insert_image("path/to/image.png", 200, 100);
```

#### 段落和 Run 增强
- `Paragraph::insert_before()` - 在当前段落前插入新段落
- `Paragraph::clone()` - 克隆段落
- `Run` 的格式设置方法：
  - `set_color(hex_color)` - 设置文字颜色
  - `set_font_size(size)` - 设置字体大小
  - `set_font_name(name)` - 设置字体名称
  - `set_bold(bool)` - 设置粗体
  - `set_italic(bool)` - 设置斜体
  - `set_underline(bool)` - 设置下划线

### 2. Read (读取)

#### Bookmark/BookmarkCollection 类
```cpp
// 获取所有书签
BookmarkCollection bookmarks(&doc);
std::cout << "Total bookmarks: " << bookmarks.count() << std::endl;

// 通过名称获取书签
auto bm = bookmarks.get("BookmarkName");
if (bm) {
    std::string text = bm->get_text();
}

// 遍历所有书签
for (const auto& bm : bookmarks) {
    std::cout << bm.get_name() << ": " << bm.get_text() << std::endl;
}
```

#### Range 类
表示文档的一个范围，用于获取和操作文本：

```cpp
// 获取文档范围的文本
Range range(&doc, start_node, end_node);
std::string text = range.get_text();
```

#### 段落文本获取
```cpp
// 获取段落中的所有文本
std::string text = paragraph.get_text();
```

### 3. Update (更新)

#### 文本替换
```cpp
// 简单替换（第一个匹配）
DocumentSearch::replace(doc, "old text", "new text");

// 替换所有匹配
int count = DocumentSearch::replace_all(doc, "old", "new");

// 带格式替换
DocumentSearch::replace_with_formatting(doc, "text", "replacement", 
                                        cdocx::bold | cdocx::italic);
```

#### Range 替换
```cpp
Range range(&doc, start_para, end_para);
range.replace("search", "replace");     // 替换第一个
range.replace_all("search", "replace"); // 替换所有
```

#### 段落格式设置
```cpp
paragraph.set_alignment("center");  // left, right, center, justify
paragraph.set_style("Heading1");
paragraph.set_line_spacing(360);    // 1.5 倍行距（以 twips 为单位）
paragraph.set_spacing_before(120);  // 段前间距
paragraph.set_spacing_after(120);   // 段后间距
paragraph.set_indent(720, -1, 360); // 左缩进、右缩进、首行缩进
```

### 4. Delete (删除)

#### 书签删除
```cpp
// 删除书签但保留内容
BookmarkCollection bookmarks(&doc);
bookmarks.remove("BookmarkName");

// 删除书签及其内容
auto bm = bookmarks.get("BookmarkName");
bm->remove_with_content();
```

#### 段落删除
```cpp
paragraph.remove();     // 删除整个段落
paragraph.clear();      // 清空段落内容
```

#### 范围删除
```cpp
Range range(&doc, start_para, end_para);
range.delete_content();
```

## 实现文件

### 新增文件

1. **include/cdocx_advanced.h** - 高级功能头文件
   - `Bookmark` 类
   - `BookmarkCollection` 类
   - `Range` 类
   - `DocumentBuilder` 类
   - `DocumentSearch` 类
   - `TableOperations` 类

2. **src/cdocx_advanced.cpp** - 高级功能实现
   - 所有 CRUD 操作的实现

### 修改文件

1. **include/cdocx.h** - 添加新方法和类
   - Run 的格式设置方法
   - Paragraph 的 CRUD 方法
   - DocumentInserter 类
   - Template 类的增强

2. **CMakeLists.txt** - 添加条件编译选项 `ENABLE_ADVANCED_FEATURES`

## 使用示例

完整的示例代码见 `examples/10_advanced_crud/main.cpp`。

### 基本用法

```cpp
#include <cdocx.h>
#include <cdocx_advanced.h>

// 创建文档
cdocx::Document doc("output.docx");
doc.create_empty();

// 使用 DocumentBuilder 创建内容
cdocx::DocumentBuilder builder(&doc);
builder.writeln("Title", cdocx::bold);
builder.writeln("Content here...");

// 保存
doc.save();
```

### 搜索和替换

```cpp
cdocx::Document doc("input.docx");
doc.open();

// 替换所有 "Company" 为 "ACME Corp"
cdocx::DocumentSearch::replace_all(doc, "Company", "ACME Corp");

doc.save("output.docx");
```

### 书签操作

```cpp
// 列出所有书签
cdocx::BookmarkCollection bookmarks(&doc);
for (const auto& bm : bookmarks) {
    std::cout << "Bookmark: " << bm.get_name() << std::endl;
    std::cout << "Text: " << bm.get_text() << std::endl;
}
```

## 与 Aspose.Words 的对比

| 功能 | Aspose.Words | CDocx (本实现) |
|------|-------------|----------------|
| 文档构建 | DocumentBuilder | DocumentBuilder |
| 书签操作 | BookmarkCollection | BookmarkCollection |
| 文本替换 | Range.Replace | DocumentSearch::replace |
| 段落格式 | ParagraphFormat | Paragraph::set_* 方法 |
| 表格操作 | Table, Row, Cell | TableOperations 类 |
| 图片插入 | DocumentBuilder.InsertImage | DocumentBuilder::insert_image |

## 注意事项

1. **独立性**：本实现完全独立于 `thirdparty/asposeWordsCpp` 和 `thirdparty/cs2cpp`，没有使用它们的任何代码或依赖。

2. **兼容性**：使用标准的 OpenXML 格式，与 Microsoft Word 兼容。

3. **性能**：实现考虑了内存效率，使用 pugixml 进行 XML 操作。

4. **扩展性**：架构允许轻松添加新的 CRUD 操作。

## 构建说明

```bash
mkdir build && cd build
cmake .. -DENABLE_ADVANCED_FEATURES=ON
cmake --build . --target cdocx
```

运行示例：
```bash
cmake --build . --target 10_advanced_crud
./examples/10_advanced_crud/10_advanced_crud.exe
```
