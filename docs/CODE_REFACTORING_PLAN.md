# CDocx 代码重构计划

## 目标

1. 添加完整的 Doxygen 文档注释
2. 优化代码结构，提高可维护性
3. 统一命名规范和代码风格
4. 提高代码可读性和可扩展性

## 重构后的文件结构

```
include/
├── cdocx/                          # 公开 API 命名空间目录
│   ├── cdocx_fwd.h                 # 前向声明
│   ├── constants.h                 # 常量定义（带 Doxygen）
│   ├── iterator.h                  # 迭代器模板类
│   ├── base.h                      # Run, Paragraph, TableCell, TableRow, Table
│   ├── document.h                  # Document 类
│   ├── template.h                  # Template 类
│   ├── inserter.h                  # DocumentInserter 类
│   └── advanced.h                  # 高级功能（Bookmark, Range, DocumentBuilder）
├── cdocx.h                         # 主头文件（包含所有公开 API）
└── detail/                         # 内部实现（用户不应直接包含）
    └── impl.h                      # DocumentImpl, DocxTree, DocxTreeNode

src/
├── document.cpp                    # Document 实现
├── base_content.cpp                # Run, Paragraph, Table 实现
├── template.cpp                    # Template 实现
├── inserter.cpp                    # DocumentInserter 实现
├── advanced.cpp                    # 高级功能实现
├── impl.cpp                        # DocumentImpl 实现
├── tree.cpp                        # DocxTree 实现
└── utils.cpp                       # 工具函数实现
```

## Doxygen 注释规范

### 文件头注释
```cpp
/**
 * @file filename.h
 * @brief 简短描述
 * @details 详细描述
 * @author Author Name (@handle)
 * @copyright MIT License
 * @date 2024
 * @version 0.2.0
 */
```

### 类注释
```cpp
/**
 * @class ClassName
 * @brief 类的简短描述
 * @details 详细描述，包括使用示例
 * 
 * @par 示例：
 * @code
 * ClassName obj;
 * obj.method();
 * @endcode
 * 
 * @see RelatedClass, related_function()
 * 
 * @since 0.2.0
 */
```

### 函数/方法注释
```cpp
/**
 * @brief 简短描述
 * @details 详细描述
 * 
 * @param[in] param1 输入参数描述
 * @param[out] param2 输出参数描述
 * @param[in,out] param3 输入输出参数描述
 * 
 * @return 返回值描述
 * 
 * @retval true 成功时的返回值
 * @retval false 失败时的返回值
 * 
 * @throw std::runtime_error 抛出的异常描述
 * 
 * @pre 前置条件
 * @post 后置条件
 * 
 * @note 重要说明
 * @warning 警告信息
 * 
 * @par 线程安全：
 * 线程安全说明
 * 
 * @sa 相关函数
 * 
 * @since 0.1.0
 */
```

### 枚举注释
```cpp
/**
 * @enum EnumName
 * @brief 枚举描述
 */
enum class EnumName {
    Value1,  ///< 值1的描述
    Value2,  ///< 值2的描述
};
```

### 成员变量注释
```cpp
int member_var;  ///< 成员变量描述
```

## 命名规范

### 类名
- PascalCase: `Document`, `Paragraph`, `DocumentBuilder`

### 函数/方法名
- snake_case: `get_text()`, `set_bold()`, `insert_paragraph()`

### 成员变量
- 私有成员：尾部下划线 `impl_`, `current_node_`
- 保护成员：尾部下划线 `parent_`

### 常量
- 全大写+下划线：`MAX_IMAGE_SIZE`
- 枚举：保留原有风格或改为 `kCamelCase`

### 模板参数
- 单个大写字母：`T`, `P`, `C`
- 或者描述性名称：`InputIt`, `OutputIt`

## 代码组织原则

1. **单一职责原则**：每个类只负责一个功能领域
2. **依赖倒置**：高层模块不依赖低层模块，都依赖抽象
3. **接口隔离**：提供最小必要接口
4. **PIMPL 模式**：隐藏实现细节，保持 ABI 稳定

## 重构步骤

### Phase 1: 头文件重构
1. 创建新的文件结构
2. 添加完整的 Doxygen 注释
3. 优化类设计和接口

### Phase 2: 源文件重构
1. 添加实现注释
2. 优化代码结构
3. 添加错误处理和日志

### Phase 3: 文档生成
1. 创建 Doxygen 配置文件
2. 生成 API 文档
3. 验证文档完整性

### Phase 4: 测试验证
1. 验证构建成功
2. 运行单元测试
3. 检查向后兼容性
