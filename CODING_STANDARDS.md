# CDocx 编码规范总结

## 规范定义

本项目采用 **Google C++ Style Guide** 为基础，有以下自定义：

| 规范项 | 设置 |
|--------|------|
| **命名规范** | Google 风格 |
| **缩进** | 4 空格 (Google 是 2 空格) |
| **行宽** | 100 字符 (Google 是 80) |
| **头文件保护** | `#pragma once` (允许使用) |

## 快速参考

### 命名

```cpp
// 类型: CamelCase
class Document { };
enum class NumberStyle { };

// 函数/方法: CamelCase
void Open();
std::string GetText();
bool IsOpen() const;

// 变量: snake_case
std::string file_path;
int paragraph_count;

// 成员变量: snake_case_
class Document {
 private:
    std::unique_ptr<DocumentImpl> impl_;
    std::string filepath_;
};

// 常量: kCamelCase
constexpr int kMaxBufferSize = 1024;
const FormatFlag kBold = ...;

// 宏: UPPER_CASE
#define DISALLOW_COPY_AND_ASSIGN(TypeName) ...
```

### 格式化

```cpp
#pragma once  // 头文件保护

#include <string>   // C++ 标准库
#include <vector>   // (按组排序)

#include <pugixml.hpp>  // 第三方库

#include "cdocx/base.h"  // 项目头文件

namespace cdocx {

// 4 空格缩进，100 字符行宽，K&R 大括号
class Example {
 public:
    void DoSomething() {
        if (condition_) {
            Process();
        } else {
            HandleError();
        }
    }

 private:
    bool condition_;
};

}  // namespace cdocx
```

## 工具使用

```bash
# 格式化
cmake --build build --target format

# 格式检查
cmake --build build --target format-check

# 静态分析
cmake --build build --target tidy

# 自动修复
cmake --build build --target tidy-fix

# 一键检查全部
./scripts/code-quality.sh all
```

## 配置文件

- `.clang-format` - 格式化规则
- `.clang-tidy` - 静态分析规则
- `AI_PROMPT.txt` - AI 编码助手规范
