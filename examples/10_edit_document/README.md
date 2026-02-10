# 示例 10: 编辑 Word 文档（保留图片）

这个示例展示了如何使用 CDocx 库打开包含图片的 Word 文档，编辑文本内容，然后保存修改，同时**保持文档中的图片不变**。

## 功能特点

- ✅ 打开包含图片的 DOCX 文件
- ✅ 删除包含特定关键词的段落
- ✅ 查找并替换文本
- ✅ 应用文本格式（粗体、斜体等）
- ✅ 添加新的格式化段落
- ✅ **图片和其他媒体文件保持不变**
- ✅ 保存为新文件

## 文件结构

```
10_edit_document/
├── main.cpp              # 示例源代码
├── CMakeLists.txt        # 构建配置
├── data/
│   └── 10_example.docx   # 示例输入文档（包含图片）
└── README.md            # 本说明文件
```

## 使用方法

### 基本使用

```bash
# 使用默认文件 (data/10_example.docx -> data/10_example_edited.docx)
./10_edit_document

# 指定输入和输出文件
./10_edit_document input.docx output.docx
```

### 编辑操作说明

程序执行以下编辑操作：

1. **删除文本**: 删除所有包含 "TestBlue" 的段落
2. **替换文本**: 将 "TestRed" 替换为 "TestRed (MODIFIED)"
3. **格式化文本**: 将包含 "TestGreen" 的文本设为粗体
4. **添加段落**: 在文档末尾添加三个格式化段落（粗体、斜体、下划线）

## 示例输出

```
╔════════════════════════════════════════════════════════════╗
║     CDocx Document Editor Example (with Images)            ║
╚════════════════════════════════════════════════════════════╝

[OPEN] Opening document: data/10_example.docx
       Document opened successfully!

========== Document Statistics ==========
  Paragraphs: 25
  Runs: 45
  Total characters: 1250
==========================================

========== Media Files ==========
  - image1.png
  - image2.jpg
==================================

========== Original Content ==========
[0] 标题1
[1] 标题2
[2] TestRed
[3] TestBlue
...
========================================

[DELETE] Looking for paragraphs containing: "TestBlue"
  Found: "TestBlue"
  Deleted 1 paragraph(s)

[REPLACE] "TestRed" -> "TestRed (MODIFIED)"
  Replaced in: "TestRed"
  Total replacements: 1

[FORMAT] Applying formatting to text containing: "TestGreen"
  Applied BOLD to: "TestGreen"
  Formatted 1 run(s)

[ADD] Adding formatted paragraphs...
  Added bold paragraph
  Added italic paragraph
  Added underlined paragraph

[SAVE] Saving to: data/10_example_edited.docx
       Document saved successfully!

╔════════════════════════════════════════════════════════════╗
║                     SUMMARY                                ║
╠════════════════════════════════════════════════════════════╣
║  Input file:  data/10_example.docx
║  Output file: data/10_example_edited.docx
║  Paragraphs deleted: 1
║  Text replacements:  1
║  Images preserved:   Yes (unchanged)
╚════════════════════════════════════════════════════════════╝
```

## 核心代码说明

### 1. 打开文档

```cpp
Document doc("data/10_example.docx");
doc.open();

if (!doc.is_open()) {
    std::cerr << "Failed to open document" << std::endl;
    return 1;
}
```

### 2. 删除包含特定文本的段落

```cpp
for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
    std::string para_text = para.get_text();
    
    // 如果段落包含关键词，清空该段落
    if (contains_ignore_case(para_text, "TestBlue")) {
        for (auto run = para.runs(); run.has_next(); run.next()) {
            run.set_text("");  // 清空文本
        }
    }
}
```

### 3. 查找并替换文本

```cpp
for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
    for (auto run = para.runs(); run.has_next(); run.next()) {
        std::string text = run.get_text();
        
        // 查找并替换
        size_t pos = text.find("TestRed");
        if (pos != std::string::npos) {
            text.replace(pos, strlen("TestRed"), "TestRed (MODIFIED)");
            run.set_text(text);
        }
    }
}
```

### 4. 应用文本格式

```cpp
for (auto para = doc.paragraphs(); para.has_next(); para.next()) {
    for (auto run = para.runs(); run.has_next(); run.next()) {
        std::string text = run.get_text();
        
        if (contains_ignore_case(text, "TestGreen")) {
            run.set_bold(true);  // 设为粗体
        }
    }
}
```

### 5. 添加新段落

```cpp
// 找到最后一个段落
Paragraph* last_para = nullptr;
for (auto& para : doc.paragraphs()) {
    last_para = &para;
}

// 在最后添加新段落
if (last_para) {
    last_para->insert_paragraph_after("New text", bold | italic);
}
```

### 6. 保存文档（图片自动保留）

```cpp
doc.save("data/10_example_edited.docx");
```

**注意**: 当调用 `save()` 时，CDocx 会自动保存所有修改，包括原始文档中的所有图片和媒体文件。无需额外操作来保留图片。

## 查看文档中的媒体文件

```cpp
std::vector<std::string> media = doc.list_media();
for (const auto& file : media) {
    std::cout << "Media: " << file << std::endl;
}
```

## 注意事项

1. **图片保留**: CDocx 在保存时会自动保留所有原始图片和媒体文件
2. **修改标记**: 文本编辑会自动标记 document.xml 为已修改
3. **空段落**: 删除文本是将 run 的文本设为空字符串，而不是删除整个段落
4. **格式继承**: 新添加的段落会应用指定的格式，不会继承前一段落的格式

## 进阶用法

### 导出图片

```cpp
doc.export_media("image1.png", "output_image.png");
```

### 替换图片（保持图片不变，但替换内容）

```cpp
doc.replace_media("image1.png", "new_image.png");
```

### 使用 XML API 进行高级编辑

```cpp
pugi::xml_document* doc_xml = doc.get_document_xml();
pugi::xml_node body = doc_xml->child("w:document").child("w:body");

// 直接操作 XML
doc.mark_modified("word/document.xml");
```

## 构建和运行

```bash
# 构建
cd build
cmake --build . --target 10_edit_document

# 运行
./examples/10_edit_document/10_edit_document
```

## 依赖

- CDocx 库
- 示例文档 `data/10_example.docx`（包含图片）
