# CDocx 代码重构说明

## 概述

本文档说明 CDocx 项目的代码结构和设计决策。

## 文件组织结构

### 头文件 (include/)

```
include/
├── cdocx.h                    # 主头文件，包含所有模块
├── cdocx/                     # 子模块头文件目录
│   ├── fwd.h                  # 前向声明
│   ├── constants.h            # 常量定义
│   ├── iterator.h             # 迭代器模板
│   ├── base.h                 # Run, Paragraph, Table 基础类
│   ├── document.h             # Document 类
│   ├── template.h             # Template 类
│   ├── inserter.h             # DocumentInserter 类
│   └── advanced.h             # 高级功能 (Bookmark, Range, DocumentBuilder)
└── detail/
    └── impl.h                 # 内部实现 (PIMPL)
```

### 源文件 (src/)

```
src/
├── base_content.cpp           # Run, Paragraph, Table 实现
├── document.cpp               # Document 类实现
├── template.cpp               # Template 类实现
├── inserter.cpp               # DocumentInserter 实现
├── tree.cpp                   # DocxTree 实现
├── impl.cpp                   # DocumentImpl 实现
└── advanced.cpp               # 高级功能实现
```

## Doxygen 注释规范

### 文件头注释

```cpp
/**
 * @file filename.h
 * @brief 简短描述
 * @details 详细描述
 * @author Author Name
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 */
```

### 类注释

```cpp
/**
 * @class ClassName
 * @brief 类的简短描述
 * @details 详细描述和使用示例
 * 
 * @par 使用示例：
 * @code
 * ClassName obj;
 * obj.method();
 * @endcode
 * 
 * @see RelatedClass
 * @since 0.2.0
 */
```

### 函数注释

```cpp
/**
 * @brief 简短描述
 * @details 详细描述
 * @param[in] param1 输入参数描述
 * @param[out] param2 输出参数描述
 * @return 返回值描述
 * @retval true 成功返回值
 * @retval false 失败返回值
 * @note 重要说明
 * @warning 警告信息
 * @sa 相关函数
 * @since 0.2.0
 */
```

## 设计原则

### 1. 模块化设计

- **fwd.h**: 所有公共类的前向声明，减少编译依赖
- **constants.h**: 格式标志常量，使用 `constexpr`
- **iterator.h**: 模板迭代器类，支持 C++11 范围循环
- **base.h**: 基础内容类 (Run, Paragraph, TableCell, TableRow, Table)
- **document.h**: 主 Document 类，清晰的 API 接口
- **template.h**: 模板替换功能
- **inserter.h**: 文档插入/合并功能
- **advanced.h**: 高级功能（书签、范围、DocumentBuilder、搜索替换）

### 2. 完善的文档注释

每个文件、类、方法都添加了完整的 Doxygen 注释：
- 功能描述
- 使用示例
- 参数说明
- 返回值说明
- 异常说明
- 版本信息

### 3. 命名规范

- **类名**: PascalCase (`Document`, `Paragraph`)
- **方法名**: snake_case (`get_text()`, `set_bold()`)
- **成员变量**: 尾部下划线 (`parent_`, `current_`)
- **常量**: `constexpr` 或 kCamelCase
- **命名空间**: 小写 (`cdocx`)

### 4. 内部实现优化

- **PIMPL 模式**: 隐藏实现细节，保持 ABI 稳定
- **树形结构**: 清晰的文档包组织结构
- **缓存机制**: 快速访问常用 XML 部件
- **状态跟踪**: 修改标记优化保存性能

## 构建系统

### CMake 选项

```cmake
option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_EXAMPLES "Build example programs" ON)
option(BUILD_TESTING "Build tests" ON)
option(BUILD_DOCS "Build documentation with Doxygen" OFF)
```

### 生成文档

```bash
# 使用 Doxygen
doxygen Doxyfile

# 或在 CMake 构建中
cmake .. -DBUILD_DOCS=ON
cmake --build . --target docs
```

文档将生成在 `docs/doxygen/html/` 目录。

## 使用示例

### 包含头文件

```cpp
// 包含所有功能
#include <cdocx.h>

// 或只包含特定模块
#include <cdocx/document.h>
#include <cdocx/base.h>
```

### 基础用法

```cpp
#include <cdocx.h>
#include <iostream>

int main() {
    // 创建文档
    cdocx::Document doc("output.docx");
    doc.create_empty();
    
    // 添加格式化文本
    auto para = doc.paragraphs();
    para.add_run("Hello, ", cdocx::bold);
    para.add_run("World!", cdocx::italic | cdocx::underline);
    
    // 保存
    doc.save();
    
    return 0;
}
```

### 使用 DocumentBuilder

```cpp
#include <cdocx/advanced.h>

cdocx::DocumentBuilder builder(&doc);
builder.set_font_size(24);
builder.set_bold(true);
builder.writeln("Chapter 1");
builder.clear_formatting();

// 创建表格
builder.start_table();
builder.insert_row();
builder.insert_cell();
builder.write("Cell 1");
builder.insert_cell();
builder.write("Cell 2");
builder.end_row();
builder.end_table();
```

## 代码质量

### 文档覆盖率

- 文件头: 100%
- 类定义: 100%
- 公共方法: 100%

### 代码组织

- 单一职责原则: 每个类只负责一个功能领域
- 依赖倒置: 高层模块不依赖低层细节
- 接口隔离: 提供最小必要接口
- 开闭原则: 对扩展开放，对修改关闭

## 贡献指南

添加新代码时请遵循以下规范：

1. 添加完整的 Doxygen 注释
2. 遵循命名规范
3. 保持模块化设计
4. 更新相关文档
5. 添加必要的测试

## 参考链接

- [Doxygen 文档](http://www.doxygen.nl/)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
