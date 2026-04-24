# Docx Template Analyzer

CDocx 模板分析器 —— 自动检测 Word 文档中的模板替换元素，并生成**可直接编译运行的 C++17 程序**。

## 功能概述

该工具解析 `.docx` 文件（ZIP + Open XML），自动提取以下三类模板元素：

| 类型 | 说明 | 示例 |
|------|------|------|
| **Placeholder** | `{{key}}` 风格的文本占位符 | `{{company_name}}`、`{{date}}` |
| **Bookmark** | Word 书签 (`w:bookmarkStart`) | `AUTHOR`、`SIGNATURE` |
| **MERGEFIELD** | Word 邮件合并域 | `MERGEFIELD Name`、`MERGEFIELD Score` |

**默认生成产物**：一个完整的 `.cpp` 源文件，包含 `main()` 函数，直接编译运行即可完成模板填充。

**可选生成产物**：`.h` 头文件（仅含常量和骨架函数）。

## 环境要求

- **Python 3.7+**（纯标准库实现，无需第三方包）
- 跨平台：Windows / Linux / macOS 均可运行

## 快速开始

### 1. 生成可编译的 C++ 程序（默认）

```bash
python tools/template_analyzer/analyze_template.py template.docx -o fill_template.cpp
```

生成的 `fill_template.cpp` 是一个完整的程序：

```cpp
#include <cdocx.h>
#include <iostream>

namespace TemplateKeys {
    inline constexpr const char* company_name = "company_name";
    inline constexpr const char* date = "date";
    // ... 其他常量
}

int main() {
    cdocx::Document doc("template.docx");
    doc.open();

    cdocx::TemplateEngine engine(&doc);

    // ===== 直接在这里修改数据 =====
    engine[cdocx::TemplateValue::text(TemplateKeys::company_name)] = "Acme Inc.";
    engine[cdocx::TemplateValue::text(TemplateKeys::date)]        = "2026-04-24";
    // =============================

    engine.apply();
    doc.save("output.docx");
    return 0;
}
```

**使用步骤**：
1. 修改 `.cpp` 中赋值语句的字符串值
2. 编译：`g++ -std=c++17 fill_template.cpp -lcdocx -o fill_template`
3. 运行：`./fill_template`
4. 得到 `output.docx`

### 2. 生成头文件模式

```bash
python tools/template_analyzer/analyze_template.py template.docx -o template_keys.h --mode header
```

生成只含常量和注释骨架的头文件，适合集成到现有项目中。

### 3. 完整示例

假设 `report_template.docx` 内容如下：

```
公司名称: {{company}}
报告标题: {{title}}
日期: {{date}}

签字人: [BOOKMARK: SIGNER]
```

运行分析器：

```bash
python tools/template_analyzer/analyze_template.py report_template.docx -o fill_report.cpp --out-docx report_filled.docx
```

生成 `fill_report.cpp`，其中 `main()` 内已写好：

```cpp
    // --- Placeholders ({{key}} style) ---
    engine[cdocx::TemplateValue::text(TemplateKeys::company)] = "company";  // TODO: replace value
    engine[cdocx::TemplateValue::text(TemplateKeys::title)]   = "title";    // TODO: replace value
    engine[cdocx::TemplateValue::text(TemplateKeys::date)]    = "date";     // TODO: replace value

    // --- Bookmarks ---
    engine[cdocx::TemplateValue::text(TemplateKeys::signer)]  = "SIGNER";   // TODO: replace value
```

直接修改右侧字符串值，编译运行即可得到填充后的 `report_filled.docx`。

## 命令行参数

```
python analyze_template.py <docx文件> [选项]

位置参数:
  docx                  输入的 .docx 文件路径

可选参数:
  -o, --output OUTPUT   输出文件路径（默认: '-' 表示 stdout）
                        扩展名决定模式: .h -> 头文件, 其他 -> 完整程序
  --mode {program,header,auto}
                        输出模式:
                          program = 完整可编译 .cpp（默认）
                          header  = .h 头文件（仅常量）
                          auto    = 根据扩展名自动决定
  --out-docx OUT_DOCX   生成程序中使用的输出 .docx 路径
                        （默认: output.docx，仅 program 模式有效）
  --guard GUARD         头文件模式的 include guard 名称
```

### 示例

```bash
# 生成完整程序（默认）
python analyze_template.py contract.docx -o fill_contract.cpp

# 生成完整程序并指定输出 docx 路径
python analyze_template.py contract.docx -o fill_contract.cpp --out-docx filled/contract_2026.docx

# 生成头文件
python analyze_template.py contract.docx -o include/contract_keys.h --mode header

# 自定义 include guard
python analyze_template.py contract.docx -o contract.h --mode header --guard CONTRACT_TEMPLATE_H
```

## 处理非 ASCII 字符

如果模板中包含中文、日文等非 ASCII 占位符（如 `{{公司名称}}`），工具会自动生成合法的 C++ 标识符：

| 原始占位符 | 生成的常量名 |
|-----------|------------|
| `{{公司名称}}` | `_____` |
| `{{标题}}`     | `__` |
| `{{日期}}`     | `___2`（自动去重）|

**编译注意事项**：生成的文件为 **UTF-8 编码**。若使用 MSVC 编译且包含非 ASCII 字符串字面量，请添加 `/utf-8` 编译选项：

```bash
cl /std:c++17 /utf-8 fill_template.cpp
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

## 生成代码结构说明

### Program 模式（`.cpp`）

生成的 `.cpp` 文件包含：

1. **头文件引用**：`cdocx.h`、`iostream`、`map`、`string`
2. **常量命名空间**：`TemplateKeys::{key}` 对应每个模板元素
3. **`main()` 函数**：
   - 打开模板文档（含错误检查）
   - 创建 `TemplateEngine`
   - 按类别分组列出所有替换项（`// TODO: replace value`）
   - 提供 `set_batch` 批量赋值注释示例
   - 调用 `engine.apply()` 并打印结果统计
   - 保存输出文档（含错误检查）

### Header 模式（`.h`）

生成的 `.h` 文件包含：

1. **`inline constexpr const char*`** 常量
2. **`names()`**：返回所有 key 的 `vector<string>`
3. **注释掉的 `fill()` 骨架函数**：供手动解注释使用

## 常见问题

**Q: 生成的 C++ 标识符可读性差（全是下划线）**
A: 占位符名称建议尽量使用 ASCII 字符（如 `{{company_name}}` 而非 `{{公司名称}}`），这样生成的常量名可读性最佳。非 ASCII 字符会被替换为下划线以确保标识符合法性。

**Q: 能否修改生成的常量命名风格？**
A: 目前常量名由占位符原文直接派生（去除 `{{}}` 后保留字母数字下划线）。如需自定义命名，可在生成后手动编辑文件，或修改 `TemplateElement.cpp_name()` 方法的实现。

**Q: 占位符跨多个 `<w:r>` 怎么办？**
A: 工具在段落级别拼接所有文本后再提取占位符，因此即使 `{{` 和 `}}` 被 Word 拆分到不同的 Run 中，只要视觉上在同一段落内，工具仍能正确识别。

**Q: 编译时找不到 `cdocx.h`？**
A: 确保编译命令中包含 `-I` 指向 cdocx 的 `include` 目录。例如：

```bash
g++ -std=c++17 -I /path/to/cdocx/include fill_template.cpp -lcdocx -o fill_template
```

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
