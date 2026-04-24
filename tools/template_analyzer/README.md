# Docx Template Analyzer

CDocx 模板分析器 —— 自动检测 Word 文档中的模板替换元素，并生成可直接使用的 C++17 头文件。

## 功能概述

该工具解析 `.docx` 文件（ZIP + Open XML），自动提取以下三类模板元素：

| 类型 | 说明 | 示例 |
|------|------|------|
| **Placeholder** | `{{key}}` 风格的文本占位符 | `{{company_name}}`、`{{date}}` |
| **Bookmark** | Word 书签 (`w:bookmarkStart`) | `AUTHOR`、`SIGNATURE` |
| **MERGEFIELD** | Word 邮件合并域 | `MERGEFIELD Name`、`MERGEFIELD Score` |

生成产物为一个 C++17 头文件，包含：
- 每个模板元素的 `inline constexpr const char*` 常量
- `names()` 函数：返回所有 key 的名称列表
- `fill()` 骨架函数：预写好的 `TemplateEngine` 赋值代码（注释状态）

## 环境要求

- **Python 3.7+**（纯标准库实现，无需第三方包）
- 跨平台：Windows / Linux / macOS 均可运行

## 快速开始

### 1. 基本用法

```bash
# 输出到 stdout
python tools/template_analyzer/analyze_template.py template.docx

# 输出到文件
python tools/template_analyzer/analyze_template.py template.docx -o template_keys.h
```

### 2. 完整示例

假设有一个 `report_template.docx`，内容如下：

```
公司名称: {{company}}
报告标题: {{title}}
日期: {{date}}

报告正文...

签字人: [BOOKMARK: SIGNER]
```

运行分析器：

```bash
python tools/template_analyzer/analyze_template.py report_template.docx -o report_keys.h
```

生成的 `report_keys.h`：

```cpp
#pragma once

#include <cdocx.h>
#include <map>
#include <string>

namespace TemplateKeys {

    // Placeholders ({{key}} style)
    inline constexpr const char* company = "company";
    inline constexpr const char* title   = "title";
    inline constexpr const char* date    = "date";

    // Bookmarks
    inline constexpr const char* signer = "SIGNER";

    // All key names
    inline std::vector<std::string> names() {
        return { company, title, date, signer };
    }

    // Skeleton fill function
    inline void fill(cdocx::TemplateEngine& engine,
                     const std::map<std::string, std::string>& data) {
        engine[cdocx::TemplateValue::text(company)] = data.at("company");
        engine[cdocx::TemplateValue::text(title)]   = data.at("title");
        engine[cdocx::TemplateValue::text(date)]    = data.at("date");
        engine[cdocx::TemplateValue::text(signer)]  = data.at("SIGNER");
    }

} // namespace TemplateKeys
```

### 3. 在 C++ 代码中使用

```cpp
#include "report_keys.h"
#include <cdocx.h>
#include <iostream>

int main() {
    cdocx::Document doc("report_template.docx");
    doc.open();

    cdocx::TemplateEngine engine(&doc);

    // 方式1: 直接赋值（推荐）
    engine[cdocx::TemplateValue::text(TemplateKeys::company)] = "Acme Inc.";
    engine[cdocx::TemplateValue::text(TemplateKeys::title)]   = "年度财报";
    engine[cdocx::TemplateValue::text(TemplateKeys::date)]    = "2026-04-24";
    engine[cdocx::TemplateValue::text(TemplateKeys::signer)]  = "张三";

    // 方式2: 使用生成的 fill() 函数
    // std::map<std::string, std::string> data = {
    //     {"company", "Acme Inc."},
    //     {"title",   "年度财报"},
    //     {"date",    "2026-04-24"},
    //     {"SIGNER",  "张三"}
    // };
    // TemplateKeys::fill(engine, data);

    // 方式3: 批量设置 + 格式
    engine[cdocx::TemplateValue::text(TemplateKeys::title)]
        = cdocx::TemplateValue::text("年度财报")
            .with_format(cdocx::TemplateFormat().bold().size(24));

    auto result = engine.apply();
    std::cout << "成功替换: " << result.success << " 处\n";

    doc.save("report_output.docx");
    return 0;
}
```

## 命令行参数

```
python analyze_template.py <docx文件> [选项]

位置参数:
  docx                  输入的 .docx 文件路径

可选参数:
  -o, --output OUTPUT   输出头文件路径（默认: '-' 表示 stdout）
  --guard GUARD         自定义 include guard 名称
                        （默认: 根据输出文件名自动生成）
```

### 示例

```bash
# 输出到 stdout
python analyze_template.py contract.docx

# 输出到指定文件
python analyze_template.py contract.docx -o include/contract_keys.h

# 自定义 include guard
python analyze_template.py contract.docx -o contract.h --guard CONTRACT_TEMPLATE_H
```

## 处理非 ASCII 字符

如果模板中包含中文、日文等非 ASCII 占位符（如 `{{公司名称}}`），工具会自动生成合法的 C++ 标识符：

| 原始占位符 | 生成的常量名 |
|-----------|------------|
| `{{公司名称}}` | `_____` |
| `{{标题}}`     | `__` |
| `{{日期}}`     | `___2`（自动去重）|

**编译注意事项**：生成的头文件为 **UTF-8 编码**。若使用 MSVC 编译且包含非 ASCII 字符串字面量，请添加 `/utf-8` 编译选项：

```bash
cl /std:c++17 /utf-8 /I include main.cpp
```

## 检测范围

工具会扫描 `.docx` 包内所有内容 XML 部件：

- `word/document.xml` — 文档正文
- `word/header*.xml` — 页眉
- `word/footer*.xml` — 页脚
- `word/endnotes.xml` — 尾注
- `word/footnotes.xml` — 脚注
- `word/comments.xml` — 批注

## 自动过滤

以下内部元素会被自动排除，不会出现在生成代码中：

- Word 自动生成的导航书签 `_GoBack`
- 重复出现的同名元素（按 `kind + name` 去重，保留首次出现）

## 与 TemplateEngine 配合

生成的代码基于 CDocx 的 `TemplateEngine` API，支持：

| 特性 | 说明 |
|------|------|
| 文本替换 | `engine["key"] = "value"` |
| 图片替换 | `engine["logo"] = TemplateValue::image("logo.png")` |
| 格式控制 | `.with_format(TemplateFormat().bold().size(24))` |
| 批量赋值 | `engine.set_batch(data_map)` |
| 作用域 | `.with_scope(TemplateScope::All)` 或 `First` |
| 目标类型 | 自动识别 Bookmark / Placeholder |

完整 `TemplateEngine` 用法请参考 `examples/21_template_engine/main.cpp` 和 `AGENTS.md`。

## 常见问题

**Q: 生成的 C++ 标识符可读性差（全是下划线）**
A: 占位符名称建议尽量使用 ASCII 字符（如 `{{company_name}}` 而非 `{{公司名称}}`），这样生成的常量名可读性最佳。非 ASCII 字符会被替换为下划线以确保标识符合法性。

**Q: 能否修改生成的常量命名风格？**
A: 目前常量名由占位符原文直接派生（去除 `{{}}` 后保留字母数字下划线）。如需自定义命名，可在生成后手动编辑头文件，或修改 `TemplateElement.cpp_name()` 方法的实现。

**Q: 占位符跨多个 `<w:r>` 怎么办？**
A: 工具在段落级别拼接所有文本后再提取占位符，因此即使 `{{` 和 `}}` 被 Word 拆分到不同的 Run 中，只要视觉上在同一段落内，工具仍能正确识别。
