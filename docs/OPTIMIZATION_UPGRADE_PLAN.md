# CDocx 优化升级方案

## 文档信息
- **版本**: 1.0
- **日期**: 2026-02-10
- **状态**: 计划中

---

## 1. 优化目标

### 1.1 总体目标
将 CDocx 从 v0.2.0 升级到 v0.5.0，实现从基础 DOCX 操作库到功能完善的文档处理库的跨越。

### 1.2 具体目标
| 目标类别 | 当前状态 | 目标状态 | 衡量标准 |
|---------|---------|---------|---------|
| 功能完整度 | 30% | 70% | 与 Aspose.Words 功能对比 |
| 格式支持 | DOCX | DOCX/PDF/HTML/图片 | 多格式导出 |
| API 稳定性 | Beta | Stable | 单元测试覆盖率 >80% |
| 性能 | 基础 | 优化 | 大文件 (>100MB) 流畅处理 |
| 文档质量 | 良好 | 优秀 | 完整 API 文档 + 示例 |

---

## 2. 核心优化方案

### 2.1 架构优化

#### 2.1.1 分层架构设计
```
┌─────────────────────────────────────────┐
│              Public API Layer           │
│  (Document, Paragraph, Table, etc.)    │
├─────────────────────────────────────────┤
│           Service Layer                 │
│  (ExportService, LayoutService, etc.)  │
├─────────────────────────────────────────┤
│         Document Model Layer            │
│  (DOM: Nodes, Elements, Attributes)    │
├─────────────────────────────────────────┤
│         I/O & Format Layer              │
│  (DOCX, PDF, HTML, Image Writers)      │
├─────────────────────────────────────────┤
│         Infrastructure Layer            │
│  (XML, ZIP, Memory, Utils)             │
└─────────────────────────────────────────┘
```

#### 2.1.2 模块化设计
```cpp
// 新模块结构
namespace cdocx {
    // Core - 核心文档操作
    namespace core {
        class Document;
        class Paragraph;
        class Run;
        class Table;
    }
    
    // Page - 页面设置
    namespace page {
        class PageSetup;
        class HeaderFooter;
        class PageNumber;
    }
    
    // Lists - 列表
    namespace lists {
        class List;
        class ListLevel;
        class ListCollection;
    }
    
    // Export - 导出
    namespace export_ {
        class PdfExporter;
        class HtmlExporter;
        class ImageExporter;
    }
    
    // Fields - 域
    namespace fields {
        class Field;
        class PageField;
        class HyperlinkField;
        class TocField;
    }
    
    // Annotations - 批注
    namespace annotations {
        class Comment;
        class Footnote;
    }
    
    // Styles - 样式
    namespace styles {
        class Style;
        class ParagraphStyle;
        class CharacterStyle;
    }
}
```

### 2.2 性能优化

#### 2.2.1 内存优化

**当前问题**:
- 所有文档内容常驻内存
- 大文件加载慢
- 内存占用高

**优化方案**:

1. **分页加载机制** (Partial Loading)
```cpp
class Document {
public:
    // 按需加载指定页面
    void load_page_range(int start_page, int end_page);
    
    // 卸载不活跃页面
    void unload_page(int page_number);
    
private:
    // 内存中的页面缓存
    LRUCache<int, Page> page_cache_;
    
    // 原始文档句柄
    std::unique_ptr<DocumentSource> source_;
};
```

2. **流式处理** (Streaming)
```cpp
class StreamingDocument {
public:
    // 逐块读取大文档
    void open_streaming(const std::string& path);
    
    // 获取下一个段落
    bool next_paragraph(Paragraph& para);
    
    // 获取下一个表格
    bool next_table(Table& table);
};
```

3. **内存池** (Memory Pool)
```cpp
class NodeMemoryPool {
public:
    // 预分配内存块
    void preallocate(size_t node_count);
    
    // 快速分配
    template<typename T, typename... Args>
    T* allocate(Args&&... args);
    
    // 批量释放
    void reset();
};
```

#### 2.2.2 并行处理

1. **并行加载**
```cpp
class ParallelLoader {
public:
    void load_document_async(const std::string& path,
                            std::function<void(Document&)> callback);
    
    void set_thread_count(int count);
};
```

2. **并行导出**
```cpp
class ParallelPdfExporter {
public:
    // 多线程 PDF 渲染
    void export_parallel(const Document& doc, 
                        const std::string& output_path,
                        int thread_count = 4);
};
```

#### 2.2.3 缓存策略

```cpp
class DocumentCache {
public:
    // 缓存策略配置
    struct CacheConfig {
        size_t max_memory_mb = 100;
        size_t max_nodes = 10000;
        bool compress_inactive = true;
    };
    
    void set_config(const CacheConfig& config);
    
    // 智能缓存
    void cache_node(NodePtr node);
    NodePtr get_node(const std::string& id);
    
    // 内存压力时自动释放
    void handle_memory_pressure();
};
```

### 2.3 导出功能实现

#### 2.3.1 PDF 导出方案

**技术选型**: libharu + 自定义布局引擎

**实现架构**:
```cpp
class PdfExporter {
public:
    bool export(const Document& doc, const std::string& path);
    
private:
    // 1. 文档解析
    void parse_document(const Document& doc);
    
    // 2. 布局计算
    void calculate_layout(LayoutContext& ctx);
    
    // 3. 分页
    void paginate(PaginationContext& ctx);
    
    // 4. 渲染
    void render_to_pdf(RenderContext& ctx);
    
    // 字体管理
    FontManager font_manager_;
    
    // 图片处理
    ImageProcessor image_processor_;
};
```

**关键算法**:
1. **文本分行**: Knuth-Plass 算法优化
2. **分页**: 避免孤行寡行
3. **字体嵌入**: 子集化减少体积

#### 2.3.2 HTML 导出方案

**技术选型**: 原生实现 + CSS 生成

**实现要点**:
```cpp
class HtmlExporter {
public:
    struct HtmlOptions {
        bool inline_css = false;
        bool embed_images = true;
        bool preserve_page_layout = false;
        std::string css_class_prefix = "cdocx-";
    };
    
    std::string export_to_string(const Document& doc, 
                                  const HtmlOptions& options);
    
private:
    // DOM 构建
    void build_dom(const Document& doc, HtmlDom& dom);
    
    // CSS 生成
    void generate_css(const Document& doc, CssStylesheet& css);
    
    // 内联样式映射
    std::map<formatting_flag, std::string> style_map_;
};
```

#### 2.3.3 图片渲染方案

**技术选型**: Skia / Cairo

```cpp
class ImageRenderer {
public:
    enum Format { PNG, JPEG, BMP, TIFF };
    
    void render_page(const Document& doc, 
                    int page_number,
                    Image& output,
                    int dpi = 96);
    
    void render_document(const Document& doc,
                        const std::string& output_dir,
                        Format format = PNG);
};
```

### 2.4 核心功能增强

#### 2.4.1 样式系统重构

**当前问题**: 无样式系统，只有直接格式

**新设计**:
```cpp
// 样式定义
class Style {
public:
    enum Type { Paragraph, Character, Table, List };
    
    std::string get_name() const;
    Type get_type() const;
    
    // 继承
    void set_base_style(StylePtr base);
    StylePtr get_base_style() const;
    
    // 格式
    ParagraphFormat& get_paragraph_format();
    CharacterFormat& get_character_format();
};

// 样式集合
class StyleCollection {
public:
    Style& add(const std::string& name, Style::Type type);
    Style& get_default(Style::Type type);
    
    // 内置样式
    void add_builtin_styles();
};

// 应用样式
class Paragraph {
public:
    void apply_style(Style& style);
    void clear_direct_formatting();  // 保留样式格式
};
```

#### 2.4.2 域系统实现

**架构设计**:
```cpp
// 域基类
class Field {
public:
    enum Type { Page, NumPages, Date, Hyperlink, TOC, MergeField /* ... */ };
    
    virtual Type get_type() const = 0;
    virtual void update() = 0;
    virtual std::string get_result() const = 0;
    
    // 域代码
    std::string get_field_code() const;
    void set_field_code(const std::string& code);
};

// 具体域实现
class PageNumberField : public Field {
public:
    void set_format(PageNumberFormat format);
    void set_start_number(int start);
};

class HyperlinkField : public Field {
public:
    void set_url(const std::string& url);
    void set_bookmark(const std::string& bookmark);
    void set_tooltip(const std::string& tooltip);
};

class TocField : public Field {
public:
    void set_heading_levels(int min, int max);
    void update();  // 重新生成目录
};

// 域管理
class FieldManager {
public:
    void update_all_fields();
    void update_fields_by_type(Field::Type type);
    
    // 邮件合并
    void execute_mail_merge(const DataSource& data);
};
```

#### 2.4.3 列表系统

**设计要点**:
```cpp
class List {
public:
    // 列表类型
    enum Type { Bullet, Number, Roman, Letter };
    
    // 9 级支持
    static constexpr int MAX_LEVELS = 9;
    
    // 级别配置
    ListLevel& get_level(int level);
    void set_level_format(int level, const ListLevelFormat& format);
};

class ListLevelFormat {
public:
    void set_number_format(const std::string& format);  // "%1." "(%1)"
    void set_number_style(NumberStyle style);
    void set_alignment(Alignment align);
    void set_indent(double indent);
    void set_tab_position(double position);
};

// 段落关联
class Paragraph {
public:
    void set_list(List& list, int level = 0);
    void remove_from_list();
    bool is_in_list() const;
    int get_list_level() const;
    
    // 列表级别调整
    void promote();  // 提升级别
    void demote();   // 降低级别
};
```

---

## 3. 实施计划

### 3.1 阶段划分

#### 阶段 1: 基础架构 (4 周)
| 周次 | 任务 | 负责人 | 产出 |
|-----|------|-------|------|
| W1 | 架构设计文档 | Architect | 架构设计文档 |
| W1-W2 | 模块接口定义 | Core Team | 头文件框架 |
| W2-W3 | 基础设施搭建 | Dev Team | 构建系统更新 |
| W3-W4 | 单元测试框架 | QA | 测试框架 + 示例测试 |

#### 阶段 2: 核心功能 (8 周)
| 周次 | 任务 | 依赖 | 产出 |
|-----|------|------|------|
| W5-W6 | 页面设置模块 | 阶段 1 | PageSetup API |
| W6-W8 | 页眉页脚 | 页面设置 | HeaderFooter API |
| W8-W10 | 列表系统 | - | Lists API |
| W10-W12 | 表格增强 | - | Enhanced Table API |

#### 阶段 3: 导出功能 (8 周)
| 周次 | 任务 | 依赖 | 产出 |
|-----|------|------|------|
| W13-W15 | PDF 导出框架 | 阶段 2 | PDF 基础导出 |
| W15-W17 | PDF 完善 | PDF 框架 | 完整 PDF 支持 |
| W17-W19 | HTML 导出 | 阶段 2 | HTML 导出 |
| W19-W20 | 图片渲染 | HTML | 图片导出 |

#### 阶段 4: 高级功能 (8 周)
| 周次 | 任务 | 依赖 | 产出 |
|-----|------|------|------|
| W21-W23 | 域系统 | 阶段 2 | Fields API |
| W23-W25 | 注释系统 | - | Comments API |
| W25-W27 | 样式系统 | 阶段 2 | Styles API |
| W27-W28 | 集成测试 | 全部 | 测试报告 |

### 3.2 里程碑

```
M1 (4周):  架构完成，开发环境就绪
M2 (12周): 核心功能完成，可处理基本文档
M3 (20周): 导出功能完成，支持 PDF/HTML
M4 (28周): v0.5.0 发布，功能完善
```

### 3.3 资源需求

| 资源类型 | 需求 | 说明 |
|---------|------|------|
| 开发人员 | 3-4人 | 核心开发 |
| 测试人员 | 1-2人 | QA 和测试 |
| 技术负责人 | 1人 | 架构和代码审查 |
| 构建服务器 | 1台 | CI/CD |
| 测试设备 | Windows/Linux/Mac | 兼容性测试 |

---

## 4. 技术细节

### 4.1 关键算法

#### 4.1.1 文本布局算法
```cpp
// Knuth-Plass 换行算法
class TextLayoutEngine {
public:
    struct BreakPoint {
        int position;
        double demerits;  // 不完美度
        int line_number;
    };
    
    // 计算最优换行点
    std::vector<BreakPoint> compute_breakpoints(
        const std::vector<TextBox>& boxes,
        double line_width);
    
private:
    // 动态规划表
    std::vector<double> demerits_table_;
};
```

#### 4.1.2 分页算法
```cpp
class PaginationEngine {
public:
    struct PageBreak {
        NodePtr node;
        bool avoid_widow;   // 避免寡行
        bool avoid_orphan;  // 避免孤行
    };
    
    // 计算分页点
    std::vector<PageBreak> paginate(
        const Document& doc,
        const PageSetup& setup);
    
private:
    //  widow/orphan 控制
    bool is_widow(NodePtr para);
    bool is_orphan(NodePtr para);
};
```

### 4.2 依赖库

| 功能 | 库 | 版本 | 许可证 |
|------|----|----|----|
| PDF 生成 | libharu | 2.4.x | Zlib |
| 图像处理 | stb_image | 最新 | Public Domain |
| 字体渲染 | FreeType | 2.13.x | FTL |
| 几何计算 | CGAL (可选) | 5.6.x | GPL/LGPL |
| 压缩 | zlib | 1.3.x | Zlib |
| 正则 | RE2 | 最新 | BSD |

### 4.3 兼容性

#### 向后兼容
- 保持现有 API 不变
- 新功能通过扩展类提供
- 废弃 API 标记为 `[[deprecated]]`

#### 平台支持
| 平台 | 最低版本 | 支持等级 |
|-----|---------|---------|
| Windows | Windows 10 | 一级支持 |
| Linux | Ubuntu 20.04 | 一级支持 |
| macOS | 11.0 | 一级支持 |
| iOS | 14.0 | 二级支持 |
| Android | API 24 | 二级支持 |

---

## 5. 质量保证

### 5.1 测试策略

#### 测试金字塔
```
       /\
      /  \     E2E 测试 (10%)
     /----\
    /      \   集成测试 (30%)
   /--------\
  /          \ 单元测试 (60%)
 /------------\
```

#### 关键测试场景
1. **功能测试**: 每个 API 的功能验证
2. **兼容性测试**: 不同 Word 版本的文档
3. **性能测试**: 大文件处理 (>100MB, >1000页)
4. **压力测试**: 并发操作
5. **内存测试**: 内存泄漏检测

### 5.2 性能基准

| 场景 | 当前 | 目标 | 测试方法 |
|-----|-----|-----|---------|
| 100页文档加载 | 5s | <2s | 时间测量 |
| 1000页文档加载 | 60s | <15s | 时间测量 |
| PDF 导出 (100页) | N/A | <10s | 时间测量 |
| 内存占用 (100MB docx) | 500MB | <300MB | 内存分析 |

### 5.3 代码质量

- **静态分析**: Clang-Tidy, PVS-Studio
- **代码覆盖率**: >80% 行覆盖率
- **文档覆盖率**: 100% 公共 API
- **审查**: 所有代码必须经过审查

---

## 6. 风险评估

| 风险 | 可能性 | 影响 | 缓解措施 |
|-----|-------|-----|---------|
| PDF 渲染复杂度高 | 高 | 高 | 分阶段实现，先用 libharu |
| 性能优化不及预期 | 中 | 高 | 早期性能测试，及时调整方案 |
| 第三方库兼容问题 | 中 | 中 | 多版本测试，准备替代方案 |
| 开发进度延迟 | 中 | 中 | 敏捷开发，定期回顾 |

---

## 7. 附录

### 7.1 参考文档
- [ASPOSE_COMPARISON_AND_ROADMAP.md](ASPOSE_COMPARISON_AND_ROADMAP.md)
- [IMPLEMENTATION_PLAN.md](IMPLEMENTATION_PLAN.md)
- Microsoft Office Open XML 规范
- PDF 1.7 规范

### 7.2 相关项目
- Aspose.Words for C++
- LibreOffice Writer
- docx4j
- python-docx

### 7.3 修订历史
| 版本 | 日期 | 作者 | 变更说明 |
|-----|-----|-----|---------|
| 1.0 | 2026-02-10 | CDocx Team | 初始版本 |
