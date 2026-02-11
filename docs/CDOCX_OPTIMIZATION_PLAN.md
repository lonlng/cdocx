# cdocx 书签替换功能优化技术方案

## 文档信息

| 项目 | 内容 |
|------|------|
| 版本 | v1.0 |
| 日期 | 2026-02-11 |
| 目标 | 实现纯 cdocx 书签替换，摆脱 Aspose.Words 依赖 |

---

## 目录

1. [现状分析](#一现状分析)
2. [优化目标](#二优化目标)
3. [功能实现方案](#三功能实现方案)
4. [API 设计](#四api-设计)
5. [实施路线图](#五实施路线图)
6. [风险与应对](#六风险与应对)

---

## 一、现状分析

### 1.1 当前架构

```
┌─────────────────────────────────────────────────────────────┐
│                    当前实现方式                              │
├─────────────────────────────────────────────────────────────┤
│  Aspose.Words               cdocx                           │
│  ┌─────────────┐           ┌─────────────┐                  │
│  │ 书签替换     │           │ 水印去除     │                  │
│  │ 图片插入     │           │ XML操作      │                  │
│  │ 格式保留     │           │ 文档合并     │                  │
│  └─────────────┘           └─────────────┘                  │
└─────────────────────────────────────────────────────────────┘
```

### 1.2 cdocx 能力矩阵

| 功能模块 | 当前状态 | 完成度 | 问题描述 |
|----------|----------|--------|----------|
| **Bookmark 基础操作** | ✅ 完整 | 100% | 支持跨段落书签 |
| **Bookmark 格式提取** | ✅ 完整 | 100% | `BookmarkFormat` 结构体实现 |
| **图片插入** | ✅ 完整 | 100% | `BookmarkReplacer::replace_with_image` 实现 |
| **图片对齐** | ✅ 完整 | 100% | 支持 Left/Center/Right 三种对齐 |
| **图标题生成** | ✅ 完整 | 100% | `CaptionGenerator` 类实现 |
| **字体格式控制** | ✅ 完整 | 100% | 支持 FarEast/Ascii 区分 |
| **水印去除** | ✅ 完整 | 90% | 已实现 |
| **XML 底层操作** | ✅ 完整 | 95% | pugixml 支持良好 |

**更新时间**: 2026-02-11 | **版本**: v0.3.0

### 1.3 关键代码缺口（已修复）

#### 缺口 1：图片插入 ✅ 已修复
```cpp
// src/bookmark_replacer.cpp - BookmarkReplacer::replace_with_image()
bool BookmarkReplacer::replace_with_image(const std::string& bookmark_name,
                                           const std::string& image_path,
                                           const std::string& caption);
// 支持 PNG/JPG/GIF/BMP/TIFF/WMF/EMF 格式
// 自动处理关系文件和媒体管理
```

#### 缺口 2：书签文本替换 ✅ 已修复
```cpp
// src/advanced.cpp - Bookmark 类增强方法
BookmarkFormat Bookmark::get_format() const;           // 提取原格式
bool Bookmark::set_text_keep_format(const std::string& text);  // 保留格式替换
bool Bookmark::set_text_formatted(const std::string& text, 
                                   const BookmarkFormat& format);
```

#### 缺口 3：跨段落书签 ✅ 已修复
```cpp
// src/advanced.cpp - Bookmark 类新增方法
bool Bookmark::is_cross_paragraph() const;                    // 检测跨段落
std::vector<pugi::xml_node> get_covered_paragraphs() const;   // 获取覆盖段落
bool Bookmark::set_text_cross_paragraph(const std::string& text);
```

---

## 二、优化目标

### 2.1 总体目标

实现 **纯 cdocx** 书签替换功能，达到与当前 Aspose.Words 实现等价的能力。

### 2.2 具体目标

| 优先级 | 目标 | 验收标准 |
|--------|------|----------|
| P0 | 图片插入功能 | 支持 PNG/JPG，可设置尺寸，正确生成 rels |
| P0 | 书签文本替换（保格式） | 替换后字体、字号、颜色与原书签一致 |
| P1 | 图片对齐控制 | 支持 Left/Center/Right 三种对齐 |
| P1 | 图标题自动生成 | 格式："图 X [描述]"，中文编号 |
| P2 | 跨段落书签 | 支持书签跨越多个段落 |
| P2 | 中西文字体区分 | 支持 FontNameFarEast/FontNameAscii |

### 2.3 目标架构

```
┌─────────────────────────────────────────────────────────────┐
│                    目标架构（纯 cdocx）                       │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────────────────────────────┐    │
│  │              BookmarkReplacer 类                    │    │
│  │  ┌──────────────┐  ┌──────────────┐                │    │
│  │  │ 文本替换      │  │ 图片替换      │                │    │
│  │  │ - 保留格式    │  │ - 对齐控制    │                │    │
│  │  │ - 跨段落      │  │ - 标题生成    │                │    │
│  │  └──────────────┘  └──────────────┘                │    │
│  └─────────────────────────────────────────────────────┘    │
│                         ↓                                   │
│  ┌─────────────────────────────────────────────────────┐    │
│  │              DocumentBuilder 增强                   │    │
│  │  - insert_image() [完善]                            │    │
│  │  - insert_image_with_caption() [新增]               │    │
│  │  - set_font_far_east() [新增]                       │    │
│  └─────────────────────────────────────────────────────┘    │
│                         ↓                                   │
│  ┌─────────────────────────────────────────────────────┐    │
│  │              Bookmark 增强                          │    │
│  │  - get_format() [新增]                              │    │
│  │  - set_text_formatted() [新增]                      │    │
│  │  - is_cross_paragraph() [新增]                      │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

---

## 三、功能实现方案

### 3.1 图片插入功能（P0）

#### 3.1.1 技术难点

1. **OpenXML 图片结构复杂**：
   ```xml
   <w:drawing>
     <wp:inline distT="0" distB="0" distL="0" distR="0">
       <wp:extent cx="5486400" cy="4114800"/>  <!-- EMU 单位 -->
       <wp:docPr id="1" name="Picture 1"/>
       <a:graphicData uri="http://...">
         <pic:pic>
           <pic:blipFill>
             <a:blip r:embed="rId4"/>  <!-- 关系 ID -->
           </pic:blipFill>
         </pic:pic>
       </a:graphicData>
     </wp:inline>
   </w:drawing>
   ```

2. **关系管理**：需要在 `[Content_Types].xml` 和 `word/_rels/document.xml.rels` 中添加条目

3. **媒体文件**：需要复制图片到 `word/media/` 目录

#### 3.1.2 实现方案

```cpp
// 新增文件：include/cdocx/image.h
#pragma once

#include <cdocx/fwd.h>
#include <string>

namespace cdocx {

// 图片对齐方式
enum class ImageAlignment {
    Left,
    Center,
    Right
};

// 图片尺寸
struct ImageSize {
    double width_pt;   // 磅
    double height_pt;  // 磅
    
    // EMU 单位转换 (1 磅 = 12700 EMU)
    int64_t width_emu() const { return static_cast<int64_t>(width_pt * 12700); }
    int64_t height_emu() const { return static_cast<int64_t>(height_pt * 12700); }
};

// 图片插入器
class ImageInserter {
public:
    // 插入图片到指定段落
    static bool insert(
        Document* doc,
        pugi::xml_node paragraph,
        const std::string& image_path,
        const ImageSize& size,
        ImageAlignment align = ImageAlignment::Center
    );
    
    // 生成唯一的关系 ID
    static std::string generate_rel_id(Document* doc);
    
    // 添加媒体文件到文档
    static std::string add_media_file(Document* doc, 
                                       const std::string& image_path);
    
    // 更新 [Content_Types].xml
    static bool update_content_types(Document* doc, 
                                      const std::string& content_type);
    
    // 更新关系文件
    static bool add_relationship(Document* doc,
                                  const std::string& rel_id,
                                  const std::string& target,
                                  const std::string& type);
};

} // namespace cdocx
```

#### 3.1.3 核心算法

```cpp
// src/image.cpp 核心实现逻辑

bool ImageInserter::insert(Document* doc, pugi::xml_node paragraph,
                           const std::string& image_path,
                           const ImageSize& size,
                           ImageAlignment align) {
    // Step 1: 复制图片到 word/media/
    std::string media_name = add_media_file(doc, image_path);
    
    // Step 2: 生成关系 ID
    std::string rel_id = generate_rel_id(doc);
    
    // Step 3: 更新 document.xml.rels
    add_relationship(doc, rel_id, "media/" + media_name,
                     "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image");
    
    // Step 4: 更新 [Content_Types].xml
    update_content_types(doc, get_content_type(image_path));
    
    // Step 5: 创建 w:drawing 元素
    pugi::xml_node run = paragraph.append_child("w:r");
    pugi::xml_node drawing = run.append_child("w:drawing");
    
    // 根据对齐方式选择 inline 或 anchor
    if (align == ImageAlignment::Center) {
        create_inline_drawing(drawing, rel_id, size);
    } else {
        create_anchor_drawing(drawing, rel_id, size, align);
    }
    
    return true;
}
```

### 3.2 书签格式提取（P0）

#### 3.2.1 问题分析

当前 `set_text()` 直接删除所有 `w:r` 节点，导致格式丢失。需要：
1. 先提取第一个 `w:r` 的格式属性
2. 创建新文本时复用这些属性

#### 3.2.2 实现方案

```cpp
// 新增结构体：include/cdocx/advanced.h

struct BookmarkFormat {
    std::string font_ascii;      // 西文字体
    std::string font_far_east;   // 中文字体
    std::string font_hint;       // 字体提示
    int font_size = 0;           // 字号（半磅）
    std::string color;           // 颜色（RGB）
    bool bold = false;
    bool italic = false;
    bool underline = false;
    std::string align;           // 对齐方式
    
    // 检查是否有效
    bool is_valid() const { return font_size > 0; }
};

// Bookmark 类新增方法
class Bookmark {
public:
    // ... 现有方法 ...
    
    // 提取书签范围内的格式信息
    BookmarkFormat get_format() const;
    
    // 设置带格式的文本
    bool set_text_formatted(const std::string& text, 
                            const BookmarkFormat& format);
    
    // 设置纯文本（保留原格式）
    bool set_text_keep_format(const std::string& text);
};
```

#### 3.2.3 格式提取算法

```cpp
BookmarkFormat Bookmark::get_format() const {
    BookmarkFormat fmt;
    
    // 从 start_node_ 的父节点（段落）中找第一个 w:r
    pugi::xml_node para = start_node_.parent();
    pugi::xml_node run = para.child("w:r");
    
    if (!run) return fmt;
    
    // 提取 w:rPr (run properties)
    pugi::xml_node rPr = run.child("w:rPr");
    if (!rPr) return fmt;
    
    // 字体
    pugi::xml_node rFonts = rPr.child("w:rFonts");
    if (rFonts) {
        fmt.font_ascii = rFonts.attribute("w:ascii").value();
        fmt.font_far_east = rFonts.attribute("w:farEast").value();
        fmt.font_hint = rFonts.attribute("w:hint").value();
    }
    
    // 字号
    pugi::xml_node sz = rPr.child("w:sz");
    if (sz) {
        fmt.font_size = sz.attribute("w:val").as_int();
    }
    
    // 颜色
    pugi::xml_node color = rPr.child("w:color");
    if (color) {
        fmt.color = color.attribute("w:val").value();
    }
    
    // 粗体
    pugi::xml_node b = rPr.child("w:b");
    fmt.bold = b != nullptr;
    
    // 斜体
    pugi::xml_node i = rPr.child("w:i");
    fmt.italic = i != nullptr;
    
    // 下划线
    pugi::xml_node u = rPr.child("w:u");
    fmt.underline = u != nullptr;
    
    return fmt;
}
```

#### 3.2.4 格式应用算法

```cpp
bool Bookmark::set_text_keep_format(const std::string& text) {
    // 1. 提取原格式
    BookmarkFormat fmt = get_format();
    
    // 2. 清除原有内容
    pugi::xml_node para = start_node_.parent();
    pugi::xml_node run = para.child("w:r");
    while (run) {
        pugi::xml_node next = run.next_sibling("w:r");
        // 保留 bookmarkStart/End 标记
        if (run != start_node_ && run != end_node_) {
            para.remove_child(run);
        }
        run = next;
    }
    
    // 3. 创建新 run（在 bookmarkEnd 之前）
    pugi::xml_node new_run = para.insert_child_before("w:r", end_node_);
    
    // 4. 应用格式
    if (fmt.is_valid()) {
        pugi::xml_node rPr = new_run.append_child("w:rPr");
        
        // 字体
        if (!fmt.font_ascii.empty() || !fmt.font_far_east.empty()) {
            pugi::xml_node rFonts = rPr.append_child("w:rFonts");
            if (!fmt.font_ascii.empty())
                rFonts.append_attribute("w:ascii").set_value(fmt.font_ascii.c_str());
            if (!fmt.font_far_east.empty())
                rFonts.append_attribute("w:farEast").set_value(fmt.font_far_east.c_str());
            if (!fmt.font_hint.empty())
                rFonts.append_attribute("w:hint").set_value(fmt.font_hint.c_str());
        }
        
        // 字号
        if (fmt.font_size > 0) {
            pugi::xml_node sz = rPr.append_child("w:sz");
            sz.append_attribute("w:val").set_value(fmt.font_size);
        }
        
        // 颜色
        if (!fmt.color.empty()) {
            pugi::xml_node color = rPr.append_child("w:color");
            color.append_attribute("w:val").set_value(fmt.color.c_str());
        }
        
        // 粗体
        if (fmt.bold) {
            rPr.append_child("w:b");
        }
        
        // 斜体
        if (fmt.italic) {
            rPr.append_child("w:i");
        }
        
        // 下划线
        if (fmt.underline) {
            pugi::xml_node u = rPr.append_child("w:u");
            u.append_attribute("w:val").set_value("single");
        }
    }
    
    // 5. 添加文本
    pugi::xml_node t = new_run.append_child("w:t");
    t.text().set(text.c_str());
    
    return true;
}
```

### 3.3 图片对齐控制（P1）

#### 3.3.1 OpenXML 对齐方式

```xml
<!-- Center 对齐（inline） -->
<wp:inline>
  <wp:extent cx="..." cy="..."/>
</wp:inline>

<!-- Left/Right 对齐（anchor） -->
<wp:anchor simplePos="0" relativeHeight="...">
  <wp:simplePos x="0" y="0"/>
  <wp:positionH relativeFrom="column">
    <wp:align>left</wp:align>  <!-- 或 right -->
  </wp:positionH>
  <wp:extent cx="..." cy="..."/>
</wp:anchor>
```

#### 3.3.2 实现方案

```cpp
void create_inline_drawing(pugi::xml_node& drawing, 
                           const std::string& rel_id,
                           const ImageSize& size) {
    pugi::xml_node inline_node = drawing.append_child("wp:inline");
    inline_node.append_attribute("distT").set_value(0);
    inline_node.append_attribute("distB").set_value(0);
    inline_node.append_attribute("distL").set_value(0);
    inline_node.append_attribute("distR").set_value(0);
    
    // extent
    pugi::xml_node extent = inline_node.append_child("wp:extent");
    extent.append_attribute("cx").set_value(size.width_emu());
    extent.append_attribute("cy").set_value(size.height_emu());
    
    // docPr
    pugi::xml_node docPr = inline_node.append_child("wp:docPr");
    docPr.append_attribute("id").set_value(1);
    docPr.append_attribute("name").set_value("Picture");
    
    // graphicData
    add_graphic_data(inline_node, rel_id);
}

void create_anchor_drawing(pugi::xml_node& drawing,
                           const std::string& rel_id,
                           const ImageSize& size,
                           ImageAlignment align) {
    pugi::xml_node anchor = drawing.append_child("wp:anchor");
    anchor.append_attribute("simplePos").set_value(0);
    anchor.append_attribute("relativeHeight").set_value(251658240);
    anchor.append_attribute("behindDoc").set_value(0);
    anchor.append_attribute("locked").set_value(0);
    anchor.append_attribute("layoutInCell").set_value(1);
    anchor.append_attribute("allowOverlap").set_value(1);
    
    // simplePos
    pugi::xml_node simplePos = anchor.append_child("wp:simplePos");
    simplePos.append_attribute("x").set_value(0);
    simplePos.append_attribute("y").set_value(0);
    
    // positionH
    pugi::xml_node positionH = anchor.append_child("wp:positionH");
    positionH.append_attribute("relativeFrom").set_value("column");
    pugi::xml_node align_node = positionH.append_child("wp:align");
    align_node.text().set(align == ImageAlignment::Left ? "left" : "right");
    
    // positionV
    pugi::xml_node positionV = anchor.append_child("wp:positionV");
    positionV.append_attribute("relativeFrom").set_value("paragraph");
    pugi::xml_node posV_align = positionV.append_child("wp:align");
    posV_align.text().set("top");
    
    // extent
    pugi::xml_node extent = anchor.append_child("wp:extent");
    extent.append_attribute("cx").set_value(size.width_emu());
    extent.append_attribute("cy").set_value(size.height_emu());
    
    // docPr
    pugi::xml_node docPr = anchor.append_child("wp:docPr");
    docPr.append_attribute("id").set_value(1);
    docPr.append_attribute("name").set_value("Picture");
    
    // graphicData
    add_graphic_data(anchor, rel_id);
}
```

### 3.4 图标题自动生成（P1）

#### 3.4.1 需求分析

- 格式：`图 X [描述]`（中文编号）
- 字体：中文宋体，英文 Times New Roman
- 字号：10.5pt（五号）
- 对齐：居中

#### 3.4.2 实现方案

```cpp
// 新增类：CaptionGenerator
class CaptionGenerator {
public:
    // 生成图标题
    static pugi::xml_node insert_figure_caption(Document* doc,
                                                  pugi::xml_node after_para,
                                                  const std::string& description,
                                                  int figure_number);
    
    // 统计文档中已有图片数量
    static int count_existing_figures(Document* doc);
    
private:
    // 创建标题段落
    static pugi::xml_node create_caption_paragraph(Document* doc,
                                                    const std::string& full_text);
    
    // 生成编号文本（中文）
    static std::string generate_number_text(int number);
};
```

#### 3.4.3 标题生成算法

```cpp
int CaptionGenerator::count_existing_figures(Document* doc) {
    int count = 0;
    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) return 0;
    
    // 遍历所有段落，查找包含"图"的标题
    for (pugi::xml_node para = doc_xml->child("w:document")
                                     .child("w:body")
                                     .child("w:p");
         para; para = para.next_sibling("w:p")) {
        
        std::string text;
        for (pugi::xml_node run = para.child("w:r"); run; run = run.next_sibling("w:r")) {
            pugi::xml_node t = run.child("w:t");
            if (t) text += t.text().get();
        }
        
        // 匹配 "图 X" 或 "图X" 格式
        if (text.find(u8"图 ") == 0 || 
            (text.find(u8"图") == 0 && text.length() > 1 && isdigit(text[3]))) {
            count++;
        }
    }
    
    return count;
}

pugi::xml_node CaptionGenerator::insert_figure_caption(Document* doc,
                                                        pugi::xml_node after_para,
                                                        const std::string& description,
                                                        int figure_number) {
    pugi::xml_document* doc_xml = doc->get_document_xml();
    if (!doc_xml) return pugi::xml_node();
    
    pugi::xml_node body = doc_xml->child("w:document").child("w:body");
    
    // 创建新段落
    pugi::xml_node caption_para = body.insert_child_after("w:p", after_para);
    
    // 段落属性：居中对齐
    pugi::xml_node pPr = caption_para.append_child("w:pPr");
    pugi::xml_node jc = pPr.append_child("w:jc");
    jc.append_attribute("w:val").set_value("center");
    
    // 生成完整文本
    std::string caption_text = u8"图 " + std::to_string(figure_number) + " " + description;
    
    // 创建 run
    pugi::xml_node run = caption_para.append_child("w:r");
    
    // 格式属性
    pugi::xml_node rPr = run.append_child("w:rPr");
    
    // 字体设置（中西文区分）
    pugi::xml_node rFonts = rPr.append_child("w:rFonts");
    rFonts.append_attribute("w:ascii").set_value("Times New Roman");
    rFonts.append_attribute("w:eastAsia").set_value("SimSun");
    rFonts.append_attribute("w:hAnsi").set_value("Times New Roman");
    
    // 字号 10.5pt = 21 半磅
    pugi::xml_node sz = rPr.append_child("w:sz");
    sz.append_attribute("w:val").set_value(21);
    pugi::xml_node szCs = rPr.append_child("w:szCs");
    szCs.append_attribute("w:val").set_value(21);
    
    // 文本
    pugi::xml_node t = run.append_child("w:t");
    t.text().set(caption_text.c_str());
    
    return caption_para;
}
```

### 3.5 跨段落书签（P2）

#### 3.5.1 问题描述

当前实现假设书签起止在同一段落：
```xml
<w:p>
  <w:bookmarkStart w:id="0" w:name="bookmark1"/>
  <w:r><w:t>文本内容</w:t></w:r>
  <w:bookmarkEnd w:id="0"/>
</w:p>
```

实际可能是：
```xml
<w:p>
  <w:bookmarkStart w:id="0" w:name="bookmark1"/>
  <w:r><w:t>开始文本</w:t></w:r>
</w:p>
<w:p>
  <w:r><w:t>中间段落</w:t></w:r>
</w:p>
<w:p>
  <w:r><w:t>结束文本</w:t></w:r>
  <w:bookmarkEnd w:id="0"/>
</w:p>
```

#### 3.5.2 实现方案

```cpp
class Bookmark {
public:
    // ...
    
    // 检查是否跨段落
    bool is_cross_paragraph() const;
    
    // 获取书签范围内的所有段落
    std::vector<pugi::xml_node> get_covered_paragraphs() const;
    
    // 跨段落设置文本（删除中间段落，合并到第一段）
    bool set_text_cross_paragraph(const std::string& text);
};
```

#### 3.5.3 跨段落处理算法

```cpp
std::vector<pugi::xml_node> Bookmark::get_covered_paragraphs() const {
    std::vector<pugi::xml_node> paragraphs;
    
    pugi::xml_node start_para = start_node_.parent();
    pugi::xml_node end_para = end_node_.parent();
    
    // 同一段落
    if (start_para == end_para) {
        paragraphs.push_back(start_para);
        return paragraphs;
    }
    
    // 跨段落：收集所有段落
    paragraphs.push_back(start_para);
    
    pugi::xml_node current = start_para.next_sibling("w:p");
    while (current && current != end_para) {
        paragraphs.push_back(current);
        current = current.next_sibling("w:p");
    }
    
    if (end_para) {
        paragraphs.push_back(end_para);
    }
    
    return paragraphs;
}

bool Bookmark::set_text_cross_paragraph(const std::string& text) {
    auto paragraphs = get_covered_paragraphs();
    if (paragraphs.empty()) return false;
    
    // 只有一段，使用普通方法
    if (paragraphs.size() == 1) {
        return set_text_keep_format(text);
    }
    
    // 多段处理：
    // 1. 提取第一段格式
    BookmarkFormat fmt;
    pugi::xml_node first_run = paragraphs[0].child("w:r");
    if (first_run) {
        // 提取格式...
    }
    
    // 2. 删除中间段落（保留第一段和最后一段）
    for (size_t i = 1; i < paragraphs.size() - 1; ++i) {
        paragraphs[i].parent().remove_child(paragraphs[i]);
    }
    
    // 3. 移动 bookmarkEnd 到第一段
    pugi::xml_node last_para = paragraphs.back();
    pugi::xml_node end_node_in_last = last_para.find_child_by_attribute(
        "w:bookmarkEnd", "w:id", start_node_.attribute("w:id").value());
    
    if (end_node_in_last) {
        // 移动到最后一段之前
        paragraphs[0].insert_move_before(end_node_in_last, paragraphs[0].last_child());
    }
    
    // 4. 删除最后一段的其余内容
    if (paragraphs.size() > 1) {
        last_para.parent().remove_child(last_para);
    }
    
    // 5. 在第一段插入新文本
    return set_text_keep_format(text);
}
```

---

## 四、API 设计（已完全实现）

### 4.1 高层 API（BookmarkReplacer 类）

**实现状态**: ✅ 已完成 | **文件**: `include/cdocx/bookmark_replacer.h`, `src/bookmark_replacer.cpp`

```cpp
// include/cdocx/bookmark_replacer.h
#pragma once

#include <cdocx/document.h>
#include <cdocx/advanced.h>
#include <functional>
#include <map>

namespace cdocx {

// 替换回调函数类型
using ReplaceCallback = std::function<bool(const std::string& bookmark_name,
                                            const std::string& old_text,
                                            std::string& new_text)>;

class BookmarkReplacer {
public:
    // 构造函数
    explicit BookmarkReplacer(Document* doc);
    
    // ==================== 文本替换 ====================
    
    // 简单文本替换（保留原格式）
    bool replace_text(const std::string& bookmark_name,
                      const std::string& new_text);
    
    // 批量文本替换
    bool replace_text_batch(const std::map<std::string, std::string>& replacements);
    
    // 带格式控制的文本替换
    bool replace_text_with_format(const std::string& bookmark_name,
                                   const std::string& new_text,
                                   const BookmarkFormat& format);
    
    // ==================== 图片替换 ====================
    
    // 简单图片替换（默认居中，带标题）
    bool replace_with_image(const std::string& bookmark_name,
                            const std::string& image_path,
                            const std::string& caption = "");
    
    // 完整图片替换（支持对齐）
    bool replace_with_image_advanced(const std::string& bookmark_name,
                                      const std::string& image_path,
                                      const ImageSize& size,
                                      const std::string& caption = "",
                                      ImageAlignment align = ImageAlignment::Center);
    
    // ==================== 高级功能 ====================
    
    // 使用回调进行条件替换
    bool replace_if(const std::string& bookmark_name, ReplaceCallback callback);
    
    // 替换并删除书签
    bool replace_and_remove(const std::string& bookmark_name,
                            const std::string& new_text);
    
    // 检查书签是否存在
    bool has_bookmark(const std::string& bookmark_name) const;
    
    // 获取所有书签名称
    std::vector<std::string> list_bookmarks() const;
    
    // ==================== 统计信息 ====================
    
    // 获取替换统计
    struct Stats {
        int success_count = 0;
        int fail_count = 0;
        int skip_count = 0;
    };
    Stats get_stats() const { return stats_; }
    void reset_stats() { stats_ = Stats(); }

private:
    Document* doc_;
    Stats stats_;
    
    // 获取书签
    std::optional<Bookmark> get_bookmark(const std::string& name);
    
    // 清除书签内容
    bool clear_bookmark_content(Bookmark& bookmark);
};

} // namespace cdocx
```

### 4.2 使用示例

```cpp
// example: 纯 cdocx 书签替换
#include <cdocx.h>
#include <cdocx/bookmark_replacer.h>
#include <iostream>

int main() {
    // 打开文档
    cdocx::Document doc("template.docx");
    doc.open();
    
    if (!doc.is_open()) {
        std::cerr << "Failed to open document!" << std::endl;
        return 1;
    }
    
    // 创建替换器
    cdocx::BookmarkReplacer replacer(&doc);
    
    // 1. 文本替换（保留原格式）
    replacer.replace_text("REPORT_NO_NAME", 
                          "BGP-2024-BJ-001 Beijing Geological Survey Report");
    replacer.replace_text("FORCASTING_DATE", "2024-06-15");
    
    // 2. 批量替换
    std::map<std::string, std::string> text_bookmarks = {
        {"FORCASTING_COMPANY", "Beijing Geological Research Institute"},
        {"FORCASTING_METHOD", "GPR + TEM Integrated Detection"},
        {"FACE_STATION", "K0+250"},
    };
    replacer.replace_text_batch(text_bookmarks);
    
    // 3. 图片替换（带标题，居中）
    replacer.replace_with_image("GPR_RESULT_IMG", 
                                "images/gpr_result.png",
                                "GPR Detection Result");
    
    // 4. 图片替换（指定大小和对齐）
    cdocx::ImageSize size{400, 300};  // 400x300 磅
    replacer.replace_with_image_advanced("FORCASTING_COMPANY_LOGO",
                                          "images/logo.png",
                                          size,
                                          "",  // 无标题
                                          cdocx::ImageAlignment::Left);
    
    // 5. 检查替换统计
    auto stats = replacer.get_stats();
    std::cout << "Replacement Summary:\n"
              << "  Success: " << stats.success_count << "\n"
              << "  Failed: " << stats.fail_count << "\n"
              << "  Skipped: " << stats.skip_count << std::endl;
    
    // 保存文档
    doc.save("output.docx");
    std::cout << "Document saved to: output.docx" << std::endl;
    
    return 0;
}
```

---

## 五、实施路线图

### 5.1 阶段划分（✅ 已完成）

```
┌─────────────────────────────────────────────────────────────────────┐
│                          实施路线图                                  │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  Phase 1: 基础功能 ✅ COMPLETED                                     │
│  ├─ 图片插入核心实现                                               │
│  │   ├─ 媒体文件管理（add_media_with_rel）                        │
│  │   ├─ OpenXML drawing 结构生成                                  │
│  │   └─ 关系文件更新逻辑                                           │
│  │                                                                │
│  └─ 书签格式保留 ✅                                                │
│      ├─ BookmarkFormat 结构定义                                    │
│      ├─ get_format() / set_text_keep_format() 实现                │
│      └─ 单元测试与调试                                             │
│                                                                     │
│  Phase 2: 增强功能 ✅ COMPLETED                                     │
│  ├─ 图片对齐与标题                                                │
│  │   ├─ ImageAlignment 枚举与 anchor 实现                         │
│  │   ├─ CaptionGenerator 标题生成器                               │
│  │   └─ DocumentBuilder::insert_image_with_caption()              │
│  │                                                                │
│  └─ 跨段落书签 ✅                                                  │
│      ├─ is_cross_paragraph() / get_covered_paragraphs()           │
│      └─ set_text_cross_paragraph() 实现                           │
│                                                                     │
│  Phase 3: 高层 API ✅ COMPLETED                                     │
│  ├─ BookmarkReplacer 类设计                                        │
│  ├─ replace_text() / replace_with_image() 实现                    │
│  └─ 批量替换与统计功能                                             │
│                                                                     │
│  Phase 4: 测试与文档 ✅ COMPLETED                                   │
│  ├─ 功能测试：各种书签类型                                        │
│  ├─ 示例代码与使用文档                                             │
│  └─ 使用文档更新                                                   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘

完成日期：2026-02-11 | 实际耗时：1 天
```

### 5.2 文件变更清单（已完成）

#### 新增文件 ✅

| 文件路径 | 说明 | 实际行数 |
|----------|------|----------|
| `include/cdocx/bookmark_replacer.h` | 高层替换 API | ~300 行 |
| `include/cdocx/caption_generator.h` | 标题生成器 | ~200 行 |
| `src/bookmark_replacer.cpp` | 替换器实现 | ~500 行 |
| `src/caption_generator.cpp` | 标题生成实现 | ~270 行 |
| `examples/bookmark_replacement_example.cpp` | 使用示例 | ~200 行 |
| `test/test_bookmark_replacement.cpp` | 单元测试 | ~100 行 |

#### 修改文件 ✅

| 文件路径 | 修改内容 | 变更行数 |
|----------|----------|----------|
| `include/cdocx/advanced.h` | 添加 BookmarkFormat、ImageSize、ImageAlignment、Bookmark 新方法 | ~150 行 |
| `src/advanced.cpp` | 实现格式提取/应用、跨段落书签处理 | ~400 行 |
| `include/cdocx.h` | 包含新头文件，更新版本号 | ~5 行 |
| `CMakeLists.txt` | 更新版本号到 0.3.0 | ~1 行 |

**总新增代码**: ~1500+ 行 | **实现时间**: 2026-02-11

### 5.3 测试计划

```cpp
// test/bookmark_replacement_test.cpp

TEST_CASE("Bookmark text replacement keeps format") {
    // 创建测试文档
    cdocx::Document doc;
    doc.create_empty();
    
    // 创建带格式的书签
    cdocx::DocumentBuilder builder(&doc);
    builder.set_font_name("SimSun");
    builder.set_font_size(14);
    builder.set_bold(true);
    builder.start_bookmark("test_bm");
    builder.write("Original");
    builder.end_bookmark("test_bm");
    
    doc.save("test_format.docx");
    
    // 替换文本
    cdocx::BookmarkReplacer replacer(&doc);
    replacer.replace_text("test_bm", "Replaced");
    
    // 验证格式保留
    auto bm = doc.get_bookmarks().get("test_bm");
    auto fmt = bm->get_format();
    
    REQUIRE(fmt.font_far_east == "SimSun");
    REQUIRE(fmt.font_size == 28);  // 14pt = 28 半磅
    REQUIRE(fmt.bold == true);
}

TEST_CASE("Image insertion with caption") {
    cdocx::Document doc("template.docx");
    doc.open();
    
    cdocx::BookmarkReplacer replacer(&doc);
    bool result = replacer.replace_with_image("IMG_BOOKMARK",
                                              "test.png",
                                              "Test Image");
    
    REQUIRE(result == true);
    
    // 验证图片存在
    auto media = doc.list_media();
    REQUIRE(media.size() > 0);
    
    // 验证标题生成
    // ... 检查段落文本
}

TEST_CASE("Cross-paragraph bookmark replacement") {
    // 测试跨段落书签
    // ...
}
```

---

## 六、风险与应对

### 6.1 技术风险

| 风险 | 概率 | 影响 | 应对措施 |
|------|------|------|----------|
| **OpenXML 兼容性** | 中 | 高 | 使用标准 OOXML 格式，测试多种 Word 版本 |
| **图片格式支持** | 低 | 中 | 优先支持 PNG/JPG，其他格式转码 |
| **大文档性能** | 中 | 中 | 延迟加载、增量更新 |
| **中文编码问题** | 中 | 高 | 使用 UTF-8，测试中文文件名和内容 |

### 6.2 项目风险

| 风险 | 概率 | 影响 | 应对措施 |
|------|------|------|----------|
| **进度延期** | 中 | 高 | 分阶段交付，先做 P0 功能 |
| **与现有代码冲突** | 低 | 中 | 保持向后兼容，新增 API 不修改旧接口 |
| **测试覆盖不足** | 中 | 高 | 建立自动化测试，多种模板测试 |

### 6.3 回滚方案

若实施过程中遇到不可解决的问题：

1. **短期回滚**：保留 Aspose.Words 用于图片插入，cdocx 仅用于文本
2. **中期方案**：使用混合架构（Aspose 生成，cdocx 后处理）
3. **长期方案**：考虑其他开源方案（如 LibreOffice SDK）

---

## 附录

### A. 参考资料

1. [OOXML 标准文档](https://www.ecma-international.org/publications/standards/Ecma-376.htm)
2. [pugixml 文档](https://pugixml.org/docs/manual.html)
3. [WordprocessingML 结构参考](https://docs.microsoft.com/en-us/office/open-xml/word-processing)

### B. 术语表

| 术语 | 说明 |
|------|------|
| EMU | English Metric Unit，英制公制单位（1 磅 = 12700 EMU）|
| Run (w:r) | Word 中的文本运行，包含格式和文本 |
| Drawing (w:drawing) | Word 中的图片/图形元素 |
| Relationship (rels) | OOXML 中文件间的关系定义 |

### C. 代码仓库结构建议

```
cdocx/
├── include/cdocx/
│   ├── cdocx.h              # 主头文件
│   ├── document.h           # 文档类
│   ├── advanced.h           # 高级功能（Bookmark、Builder）
│   ├── image.h              # 【新增】图片插入
│   ├── bookmark_replacer.h  # 【新增】书签替换器
│   └── caption_generator.h  # 【新增】标题生成
├── src/
│   ├── document.cpp
│   ├── advanced.cpp
│   ├── image.cpp            # 【新增】
│   ├── bookmark_replacer.cpp # 【新增】
│   └── caption_generator.cpp # 【新增】
└── test/
    └── bookmark_replacement_test.cpp  # 【新增】
```

---

**文档结束**

*本方案由技术团队制定，实施前请进行技术评审。*
