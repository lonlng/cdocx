/**
 * @file inserter.h
 * @brief Document insertion functionality for merging DOCX files
 * @details Provides the DocumentInserter class for inserting content from
 *          one document into another. Supports inserting entire documents,
 *          paragraphs only, or tables only, at various positions.
 * 
 * @author Amir Mohamadi (@amiremohamadi)
 * @copyright MIT License
 * @date 2024
 * @version 0.2.0
 * 
 * @par 使用示例：
 * @code
 * #include <cdocx/inserter.h>
 * 
 * // 打开目标文档
 * cdocx::Document target("main.docx");
 * target.open();
 * 
 * // 打开源文档
 * cdocx::Document source("content.docx");
 * source.open();
 * 
 * // 创建插入器
 * cdocx::DocumentInserter inserter(&target);
 * 
 * // 在末尾插入整个文档
 * inserter.insert_document(&source);
 * 
 * // 在特定位置插入（0 = 开头, -1 = 末尾）
 * inserter.insert_document_at(&source, 2);
 * 
 * // 只插入段落
 * inserter.insert_paragraphs(&source);
 * 
 * // 保存结果
 * target.save("combined.docx");
 * @endcode
 */

#pragma once

#include <cdocx/fwd.h>
#include <cdocx/base.h>
#include <pugixml.hpp>

namespace cdocx {

/**
 * @class DocumentInserter
 * @brief Inserts content from one document into another
 * @details The DocumentInserter class provides flexible content insertion
 *          capabilities. It can insert:
 *          - Complete documents (paragraphs and tables)
 *          - Paragraphs only
 *          - Tables only
 * 
 * @par 插入位置：
 * - 默认：文档末尾
 * - 指定索引：0 = 文档开头，1 = 第一个元素后，-1 = 文档末尾
 * - 指定段落：在特定段落后插入
 * 
 * @par 注意事项：
 * - 源文档的内容会被克隆，源文档不会被修改
 * - 样式可能需要手动同步
 * - 图片等媒体文件需要单独处理
 * 
 * @see Document
 * @since 0.1.0
 */
class DocumentInserter {
private:
    Document* target_doc_;  ///< Target document for insertion

    /**
     * @brief Clone a paragraph from source to target
     * @param[in] source_para Source paragraph node
     * @param[in] target_parent Target parent node (body or cell)
     * @return The cloned paragraph node
     */
    pugi::xml_node clone_paragraph(const pugi::xml_node& source_para, 
                                    pugi::xml_node target_parent);

    /**
     * @brief Clone a table from source to target
     * @param[in] source_table Source table node
     * @param[in] target_parent Target parent node
     * @return The cloned table node
     */
    pugi::xml_node clone_table(const pugi::xml_node& source_table,
                               pugi::xml_node target_parent);

public:
    /**
     * @brief Construct inserter for target document
     * @param[in] target Target document (must remain valid during operations)
     */
    explicit DocumentInserter(Document* target);

    /**
     * @brief Insert entire document at the end
     * @param[in] source Source document to insert
     * @details Inserts all paragraphs and tables from source at the end
     *          of the target document.
     * @pre Both documents must be open
     */
    void insert_document(Document* source);

    /**
     * @brief Insert document after a specific paragraph
     * @param[in] source Source document to insert
     * @param[in] after_para Paragraph after which to insert
     * @pre Both documents must be open
     */
    void insert_document_after(Document* source, Paragraph& after_para);

    /**
     * @brief Insert document at specific position
     * @param[in] source Source document to insert
     * @param[in] position Insert position:
     *                     - 0 = beginning of document
     *                     - N = after Nth block element
     *                     - -1 = end of document (default)
     * @pre Both documents must be open
     */
    void insert_document_at(Document* source, int position);

    /**
     * @brief Insert only paragraphs from source document
     * @param[in] source Source document
     * @param[in] position Insert position (default: -1 = end)
     * @pre Both documents must be open
     */
    void insert_paragraphs(Document* source, int position = -1);

    /**
     * @brief Insert only tables from source document
     * @param[in] source Source document
     * @param[in] position Insert position (default: -1 = end)
     * @pre Both documents must be open
     */
    void insert_tables(Document* source, int position = -1);
};

} // namespace cdocx
