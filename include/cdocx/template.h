/**
 * @file template.h
 * @brief Template-based placeholder replacement for DOCX documents
 * @details Provides the Template class for replacing placeholder strings
 *          in documents using customizable patterns (default: {{key}}).
 *          Supports both text and image placeholders with FSM-based
 *          processing for handling placeholders split across multiple runs.
 * 
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.2.0
 * 
 * @par 使用示例：
 * @code
 * #include <cdocx/template.h>
 * 
 * cdocx::Document doc("template.docx");
 * doc.open();
 * 
 * // 创建模板处理器
 * cdocx::Template tmpl(&doc);
 * 
 * // 设置文本占位符
 * tmpl.set("name", "John Doe");
 * tmpl.set("date", "2024-01-15");
 * tmpl.set("company", "Acme Inc.");
 * 
 * // 设置图片占位符
 * tmpl.set_image("logo", "path/to/logo.png");
 * 
 * // 执行替换
 * tmpl.replace_all();
 * 
 * // 保存结果
 * doc.save("output.docx");
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/base.h>
#include <map>
#include <string>
#include <vector>

namespace cdocx {

/**
 * @class Template
 * @brief Template engine for placeholder replacement in DOCX documents
 * @details The Template class provides a powerful mechanism for replacing
 *          placeholders in Word documents. It uses a Finite State Machine (FSM)
 *          to handle placeholders that may be split across multiple text runs.
 * 
 * @par 支持的占位符格式：
 * - 默认格式: {{key}}
 * - 自定义格式: 通过 set_pattern() 设置前缀和后缀
 * 
 * @par 处理流程：
 * 1. 设置占位符值 (set(), set_image())
 * 2. 执行替换 (replace_all())
 * 3. 保存文档
 * 
 * @par 注意事项：
 * - 占位符匹配是大小写敏感的
 * - 支持跨多个 runs 的占位符
 * - 图片占位符会替换为实际图片
 * 
 * @see Document, Document::paragraphs()
 * @since 0.1.0
 */
class Template {
private:
    Document* doc_;  ///< Target document pointer
    std::map<std::string, std::string> placeholders_;       ///< Text placeholders
    std::map<std::string, std::string> image_placeholders_; ///< Image placeholders
    std::string pattern_prefix_ = "{{";   ///< Placeholder start pattern
    std::string pattern_suffix_ = "}}";   ///< Placeholder end pattern

    /**
     * @struct PlaceholderContext
     * @brief Internal state for FSM-based placeholder processing
     * @details Maintains state while scanning for multi-run placeholders
     */
    struct PlaceholderContext {
        Run* first_run = nullptr;           ///< First run of current placeholder
        std::vector<Run*> runs_to_delete;   ///< Runs to clean up after replacement
        std::string collected_text;         ///< Accumulated text across runs
        size_t prefix_pos = 0;              ///< Position in prefix pattern
        
        /**
         * @brief Reset the context state
         */
        void clear() {
            first_run = nullptr;
            runs_to_delete.clear();
            collected_text.clear();
            prefix_pos = 0;
        }
    };

    /**
     * @brief Replace placeholders in a string
     * @param[in,out] text Text to process (modified in place)
     * @return true if any replacement was made
     */
    bool replace_in_string(std::string& text) const;

    /**
     * @brief Replace placeholders in all paragraphs
     */
    void replace_in_paragraphs();

    /**
     * @brief Replace placeholders in all tables
     */
    void replace_in_tables();

    /**
     * @brief Transition to collecting state in FSM
     * @param[in,out] ctx Placeholder context
     * @param[in,out] r Current run
     * @param[in] text Current text
     * @param[in] prefix_pos Position in prefix pattern
     */
    void transition_to_collecting_state(PlaceholderContext& ctx, Run& r, 
                                        const std::string& text, size_t prefix_pos);
    
    /**
     * @brief Try to replace a collected placeholder
     * @param[in] ctx Placeholder context
     * @param[in,out] p Current paragraph
     * @return true if replacement was successful
     */
    bool try_replace_placeholder(const PlaceholderContext& ctx, Paragraph& p);
    
    /**
     * @brief Delete runs collected during placeholder detection
     * @param[in] ctx Placeholder context
     * @param[in,out] p Current paragraph
     */
    void delete_collected_runs(const PlaceholderContext& ctx, Paragraph& p);
    
    /**
     * @brief Process a single paragraph for placeholders
     * @param[in,out] p Paragraph to process
     */
    void process_paragraph(Paragraph& p);
    
    /**
     * @brief Try to replace placeholder in a single run (const version)
     * @param[in,out] r The run to process
     * @return true if replacement was successful
     */
    bool try_replace_single_run(Run& r) const;

public:
    /**
     * @brief Construct template processor with default pattern
     * @param[in] document Target document (must remain valid during processing)
     */
    explicit Template(Document* document);

    /**
     * @brief Construct template processor with custom pattern
     * @param[in] document Target document
     * @param[in] prefix Placeholder start pattern (e.g., "<%")
     * @param[in] suffix Placeholder end pattern (e.g., "%>")
     */
    Template(Document* document, const std::string& prefix, const std::string& suffix);

    /**
     * @brief Set a text placeholder value
     * @param[in] key Placeholder key (without delimiters)
     * @param[in] value Replacement value
     * 
     * @par 示例：
     * @code
     * tmpl.set("name", "John Doe");
     * // Will replace {{name}} with "John Doe"
     * @endcode
     */
    void set(const std::string& key, const std::string& value);

    /**
     * @brief Set a text placeholder value (C-string version)
     * @param[in] key Placeholder key
     * @param[in] value Replacement value
     */
    void set(const std::string& key, const char* value);

    /**
     * @brief Set an image placeholder
     * @param[in] key Placeholder key
     * @param[in] image_path Path to the image file
     * 
     * @par 示例：
     * @code
     * tmpl.set_image("logo", "images/company_logo.png");
     * // Will replace {{logo}} with the image
     * @endcode
     */
    void set_image(const std::string& key, const std::string& image_path);

    /**
     * @brief Set custom placeholder pattern
     * @param[in] prefix Start pattern
     * @param[in] suffix End pattern
     * 
     * @par 示例：
     * @code
     * tmpl.set_pattern("<%", "%>");  // Will match <%key%>
     * tmpl.set_pattern("${", "}");   // Will match ${key}
     * @endcode
     */
    void set_pattern(const std::string& prefix, const std::string& suffix);

    /**
     * @brief Replace all placeholders in the document
     * @details Scans all paragraphs and tables, replacing placeholders
     *          with their corresponding values.
     * @pre Document must be open
     * @post All matching placeholders are replaced
     */
    void replace_all();

    /**
     * @brief Clear all placeholder values
     * @details Removes all set values but keeps the pattern configuration
     */
    void clear();

    /**
     * @brief Get the number of set placeholders
     * @return Total count of text and image placeholders
     */
    size_t size() const;
};

} // namespace cdocx
