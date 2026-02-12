# CDocx 代码质量规范指南

本文档介绍 CDocx 项目的代码质量工具配置和使用方法。

## 规范说明

本项目采用 **Google C++ Style Guide** 的变体：

| 规范项 | Google 标准 | 本项目设置 |
|--------|-------------|-----------|
| 命名规范 | Google 风格 | ✅ **完全遵循** |
| 函数名 | `CamelCase()` | ✅ `CamelCase()` |
| 常量 | `kCamelCase` | ✅ `kCamelCase` |
| 成员变量 | `snake_case_` | ✅ `snake_case_` |
| 缩进 | 2 空格 | 🔧 **4 空格** |
| 行宽 | 80 字符 | 🔧 **100 字符** |
| 头文件保护 | `#ifndef` | 🔧 **`#pragma once`** |

## 工具概览

| 工具 | 配置文件 | 用途 |
|------|----------|------|
| **clang-format** | `.clang-format` | 自动化代码格式化 |
| **clang-tidy** | `.clang-tidy` | 静态代码分析和建议 |

## 快速开始

### 1. 安装工具

```bash
# Ubuntu/Debian
sudo apt-get install clang-format clang-tidy

# macOS
brew install llvm

# Windows (via LLVM installer)
# Download from: https://releases.llvm.org/download.html
```

### 2. 验证版本

```bash
clang-format --version  # 建议 14.0+
clang-tidy --version    # 建议 14.0+
```

### 3. 构建项目

```bash
mkdir build && cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd ..
```

### 4. 运行代码检查

```bash
# Linux/macOS
./scripts/code-quality.sh all

# Windows
scripts\code-quality.bat all
```

## 命名规范详解

### 类型名

```cpp
// CamelCase
class Document { };
struct SectionProperties { };
enum class NumberStyle { Decimal, Bullet };
template<typename T>
class Iterator { };
using StringVector = std::vector<std::string>;
```

### 函数和方法

```cpp
// CamelCase
class Document {
 public:
    void Open();
    bool IsOpen() const;
    std::string GetFilepath() const;
    void SetText(const std::string& text);
    Paragraph& GetParagraphs();
};
```

### 变量

```cpp
// snake_case
std::string file_path;
int paragraph_count;

// Class members: trailing underscore
class Document {
 private:
    std::unique_ptr<DocumentImpl> impl_;
    std::string filepath_;
    bool is_open_;
};
```

### 常量

```cpp
// kCamelCase
constexpr int kMaxBufferSize = 1024;
const char kDefaultExtension[] = ".docx";

// Enums
enum class FormatFlag {
    kNone = 0,
    kBold = 1 << 0,
    kItalic = 1 << 1,
};
```

### 宏

```cpp
// UPPER_CASE
#define CDOCX_API __declspec(dllexport)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;      \
    void operator=(const TypeName&) = delete
```

## 头文件规范

### 头文件保护

本项目使用 `#pragma once`：

```cpp
#pragma once

// 内容
```

### Include 顺序

```cpp
// 1. Related header (for .cpp files)
#include "cdocx/document.h"

// 2. C system headers
#include <sys/types.h>
#include <unistd.h>

// 3. C++ standard library headers
#include <string>
#include <vector>

// 4. Third-party headers
#include <pugixml.hpp>

// 5. Project headers
#include "cdocx/base.h"
#include "cdocx/iterator.h"
```

每组之间用空行分隔。

## 格式化规范

### 缩进和行宽

```cpp
// 4 空格缩进，100 字符行宽
void MyFunction() {
    if (condition) {
        DoSomething();
    } else {
        DoOtherThing();
    }
}
```

### 大括号

使用 K&R 风格（Attach）：

```cpp
// ✅ 正确
if (condition) {
    DoSomething();
}

for (int i = 0; i < count; ++i) {
    Process(i);
}

// ❌ 错误
if (condition)
{
    DoSomething();
}
```

### 函数调用

```cpp
// 短函数
DoSomething();

// 长参数列表
ReturnType result = SomeFunction(
    very_long_argument1, very_long_argument2,
    very_long_argument3);

// Lambda
auto lambda = [](int x) {
    return x * 2;
};
```

## 代码质量命令

### 格式化

```bash
# 格式化所有代码
cmake --build build --target format

# 或直接使用
clang-format -i src/*.cpp include/*.h include/**/*.h
```

### 格式检查（CI）

```bash
cmake --build build --target format-check
```

### 静态分析

```bash
# 分析代码
cmake --build build --target tidy

# 自动修复问题
cmake --build build --target tidy-fix
```

⚠️ **警告**：`tidy-fix` 会自动修改代码，使用前请提交 git！

### 运行所有检查

```bash
# Linux/macOS
./scripts/code-quality.sh all

# Windows
scripts\code-quality.bat all
```

## Clang-Tidy 检查类别

### 启用的主要检查

| 类别 | 说明 |
|------|------|
| `google-*` | **Google 风格专用检查**（除 header-guard 外） |
| `modernize-*` | 现代 C++ 建议 |
| `cppcoreguidelines-*` | C++ 核心准则 |
| `performance-*` | 性能优化建议 |
| `readability-*` | 可读性改进 |
| `bugprone-*` | Bug 预防 |
| `cert-*` | 安全编码 (CERT) |

### 豁免的检查

| 检查 | 原因 |
|------|------|
| `llvm-header-guard` | 我们使用 `#pragma once` |
| `google-build-namespaces` | 允许 using 指令在 cc 文件中 |
| `readability-identifier-length` | 短变量名在局部作用域可接受 |

## CI/CD 集成

### GitHub Actions

```yaml
name: Code Quality

on: [push, pull_request]

jobs:
  code-quality:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Install tools
        run: sudo apt-get install -y clang-format clang-tidy
      
      - name: Configure CMake
        run: |
          mkdir build
          cd build
          cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
      
      - name: Check formatting
        run: cmake --build build --target format-check
      
      - name: Static analysis
        run: cmake --build build --target tidy
```

### 预提交钩子

```bash
#!/bin/bash
# .git/hooks/pre-commit

# 检查格式
if ! cmake --build build --target format-check 2>/dev/null; then
    echo "Code formatting check failed."
    echo "Run: cmake --build build --target format"
    exit 1
fi
```

## 编辑器集成

### VS Code

安装 **C/C++** 扩展（Microsoft）并配置：

```json
// settings.json
{
    "C_Cpp.formatting": "clangFormat",
    "C_Cpp.clang_format_style": "file",
    "C_Cpp.clang_format_fallbackStyle": "none",
    "C_Cpp.codeAnalysis.clangTidy.enabled": true,
    "editor.formatOnSave": true,
    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "editor.rulers": [100]
}
```

### CLion

1. **Settings → Editor → Code Style → C/C++**
   - 选择 "Project" 使用 .clang-format

2. **Settings → Editor → Inspections → C/C++**
   - 启用 "Clang-Tidy"

### Vim/Neovim

使用 ALE 插件：

```vim
" .vimrc
let g:ale_c_clangformat_executable = 'clang-format'
let g:ale_c_clangtidy_executable = 'clang-tidy'
let g:ale_fixers = {'cpp': ['clang-format']}
let g:ale_linters = {'cpp': ['clang-tidy']}
let g:ale_cpp_clangformat_options = '-style=file'

" 设置缩进
set tabstop=4
set shiftwidth=4
set expandtab
```

## 故障排除

### "函数名应为 CamelCase"

```cpp
// ❌ 错误
void open_file();
void get_text();

// ✅ 正确
void OpenFile();
void GetText();
```

### "常量应为 kCamelCase"

```cpp
// ❌ 错误
const int MAX_SIZE = 100;
const char* default_name = "doc";

// ✅ 正确
constexpr int kMaxSize = 100;
const char kDefaultName[] = "doc";
```

### "成员变量应有下划线后缀"

```cpp
// ❌ 错误
class MyClass {
 private:
    int private_member;
};

// ✅ 正确
class MyClass {
 private:
    int private_member_;
};
```

## 参考文档

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Clang-Format Style Options](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [Clang-Tidy Checks](https://clang.llvm.org/extra/clang-tidy/checks/list.html)
