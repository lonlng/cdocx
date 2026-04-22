/**
 * @file bookmark_replacer.cpp
 * @brief BookmarkReplacer implementation
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.3.0
 */

#include <cdocx/advanced.h>
#include <cdocx/bookmark_replacer.h>
#include <cdocx/caption_generator.h>
#include <cdocx/document.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <sstream>

namespace cdocx {

// ============================================================================
// Constructor
// ============================================================================

BookmarkReplacer::BookmarkReplacer(Document* doc) : doc_(doc), next_image_id_(1) {
}

// ============================================================================
// Text Replacement
// ============================================================================

bool BookmarkReplacer::replace_text(const std::string& bookmark_name, const std::string& new_text) {
    auto bm = get_bookmark(bookmark_name);
    if (!bm) {
        stats_.fail_count++;
        return false;
    }
    return replace_text(*bm, new_text);
}

bool BookmarkReplacer::replace_text(Bookmark& bookmark, const std::string& new_text) {
    bool result = bookmark.set_text_keep_format(new_text);
    if (result) {
        stats_.success_count++;
    } else {
        stats_.fail_count++;
    }
    return result;
}

int BookmarkReplacer::replace_text_batch(const std::map<std::string, std::string>& replacements) {
    int success_count = 0;

    for (const auto& pair : replacements) {
        if (replace_text(pair.first, pair.second)) {
            success_count++;
        }
    }

    return success_count;
}

bool BookmarkReplacer::replace_text_with_format(const std::string& bookmark_name,
                                                const std::string& new_text,
                                                const BookmarkFormat& format) {
    auto bm = get_bookmark(bookmark_name);
    if (!bm) {
        stats_.fail_count++;
        return false;
    }
    return replace_text_with_format(*bm, new_text, format);
}

bool BookmarkReplacer::replace_text_with_format(Bookmark& bookmark,
                                                const std::string& new_text,
                                                const BookmarkFormat& format) {
    bool result = bookmark.set_text_formatted(new_text, format);
    if (result) {
        stats_.success_count++;
    } else {
        stats_.fail_count++;
    }
    return result;
}

// ============================================================================
// Image Replacement
// ============================================================================

bool BookmarkReplacer::replace_with_image(const std::string& bookmark_name,
                                          const std::string& image_path,
                                          const std::string& caption) {
    auto bm = get_bookmark(bookmark_name);
    if (!bm) {
        return false;
    }
    return replace_with_image(*bm, image_path, caption);
}

bool BookmarkReplacer::replace_with_image(Bookmark& bookmark,
                                          const std::string& image_path,
                                          const std::string& caption) {
    ImageSize size;
    if (!detect_image_size(image_path, size)) {
        size = ImageSize(400, 300);
    }
    return replace_with_image_advanced(bookmark, image_path, size, caption, ImageAlignment::Center);
}

bool BookmarkReplacer::replace_with_image_advanced(const std::string& bookmark_name,
                                                   const std::string& image_path,
                                                   const ImageSize& size,
                                                   const std::string& caption,
                                                   ImageAlignment align) {
    auto bm = get_bookmark(bookmark_name);
    if (!bm) {
        stats_.fail_count++;
        return false;
    }
    return replace_with_image_advanced(*bm, image_path, size, caption, align);
}

bool BookmarkReplacer::replace_with_image_advanced(Bookmark& bookmark,
                                                   const std::string& image_path,
                                                   const ImageSize& size,
                                                   const std::string& caption,
                                                   ImageAlignment align) {
    // Validate image file exists
    std::ifstream file(image_path, std::ios::binary);
    if (!file) {
        stats_.fail_count++;
        return false;
    }
    file.close();

    // Get file extension and determine content type
    std::string ext = get_file_extension(image_path);
    std::string content_type = get_content_type(ext);
    if (content_type.empty()) {
        stats_.fail_count++;
        return false;
    }

    // Generate unique image name
    std::string image_name = "image_" + std::to_string(generate_image_id()) + "." + ext;

    // Add media file to document with relationship
    std::string rel_id = doc_->add_media_with_rel(image_path, &image_name);
    if (rel_id.empty()) {
        stats_.fail_count++;
        return false;
    }

    // Clear bookmark content
    if (!clear_bookmark_content(bookmark)) {
        stats_.fail_count++;
        return false;
    }

    // Insert image at bookmark location
    if (!insert_image_at_bookmark(bookmark, image_path, size, align, rel_id)) {
        stats_.fail_count++;
        return false;
    }

    // Add caption if provided
    if (!caption.empty()) {
        int figure_number = CaptionGenerator::get_next_figure_number(doc_);
        pugi::xml_node bookmark_para = bookmark.get_covered_paragraphs().empty()
                                           ? pugi::xml_node()
                                           : bookmark.get_covered_paragraphs()[0];
        if (bookmark_para) {
            CaptionGenerator::insert_figure_caption(doc_, bookmark_para, caption, figure_number);
        }
    }

    stats_.success_count++;
    return true;
}

bool BookmarkReplacer::replace_with_image_from_memory(const std::string& bookmark_name,
                                                      const std::vector<uint8_t>& image_data,
                                                      const std::string& image_name,
                                                      const ImageSize& size,
                                                      const std::string& caption,
                                                      ImageAlignment align) {
    auto bm = get_bookmark(bookmark_name);
    if (!bm) {
        stats_.fail_count++;
        return false;
    }
    return replace_with_image_from_memory(*bm, image_data, image_name, size, caption, align);
}

bool BookmarkReplacer::replace_with_image_from_memory(Bookmark& bookmark,
                                                      const std::vector<uint8_t>& image_data,
                                                      const std::string& image_name,
                                                      const ImageSize& size,
                                                      const std::string& caption,
                                                      ImageAlignment align) {
    // Get content type from extension
    std::string ext = get_file_extension(image_name);
    std::string content_type = get_content_type(ext);
    if (content_type.empty()) {
        content_type = "image/png";  // Default
    }

    // Add media from memory and create relationship
    std::string rel_id = doc_->add_media_from_memory_with_rel(image_name, image_data, content_type);
    if (rel_id.empty()) {
        stats_.fail_count++;
        return false;
    }

    // Clear bookmark content
    if (!clear_bookmark_content(bookmark)) {
        stats_.fail_count++;
        return false;
    }

    // Insert image at bookmark location using the relationship ID
    if (!insert_image_at_bookmark(bookmark, image_name, size, align, rel_id)) {
        stats_.fail_count++;
        return false;
    }

    // Add caption if provided
    if (!caption.empty()) {
        int figure_number = CaptionGenerator::get_next_figure_number(doc_);
        pugi::xml_node bookmark_para = bookmark.get_covered_paragraphs().empty()
                                           ? pugi::xml_node()
                                           : bookmark.get_covered_paragraphs()[0];
        if (bookmark_para) {
            CaptionGenerator::insert_figure_caption(doc_, bookmark_para, caption, figure_number);
        }
    }

    stats_.success_count++;
    return true;
}

// ============================================================================
// Advanced Features
// ============================================================================

bool BookmarkReplacer::replace_if(const std::string& bookmark_name,
                                  const ReplaceCallback& callback) {
    auto bm = get_bookmark(bookmark_name);
    if (!bm) {
        stats_.fail_count++;
        return false;
    }

    std::string old_text = bm->get_text();
    std::string new_text;

    if (!callback(bookmark_name, old_text, new_text)) {
        stats_.skip_count++;
        return false;
    }

    return replace_text(bookmark_name, new_text);
}

bool BookmarkReplacer::replace_and_remove(const std::string& bookmark_name,
                                          const std::string& new_text) {
    bool result = replace_text(bookmark_name, new_text);
    if (result) {
        auto bm = get_bookmark(bookmark_name);
        if (bm) {
            bm->remove();
        }
    }
    return result;
}

bool BookmarkReplacer::replace_with_image_and_remove(const std::string& bookmark_name,
                                                     const std::string& image_path,
                                                     const std::string& caption) {
    bool result = replace_with_image(bookmark_name, image_path, caption);
    if (result) {
        auto bm = get_bookmark(bookmark_name);
        if (bm) {
            bm->remove();
        }
    }
    return result;
}

// ============================================================================
// Query Methods
// ============================================================================

bool BookmarkReplacer::has_bookmark(const std::string& bookmark_name) const {
    return get_bookmark(bookmark_name).has_value();
}

std::vector<std::string> BookmarkReplacer::list_bookmarks() const {
    if (!doc_) {
        return {};
    }

    auto bookmarks = doc_->get_bookmarks();
    return bookmarks.get_names();
}

std::string BookmarkReplacer::get_bookmark_text(const std::string& bookmark_name) const {
    auto bm = get_bookmark(bookmark_name);
    if (bm) {
        return bm->get_text();
    }
    return "";
}

// ============================================================================
// Private Helpers
// ============================================================================

std::optional<Bookmark> BookmarkReplacer::get_bookmark(const std::string& name) const {
    if (!doc_) {
        return std::nullopt;
    }

    auto bookmarks = doc_->get_bookmarks();
    return bookmarks.get(name);
}

bool BookmarkReplacer::clear_bookmark_content(Bookmark& bookmark) {
    if (!bookmark.is_valid()) {
        return false;
    }

    // Get covered paragraphs
    auto paras = bookmark.get_covered_paragraphs();
    if (paras.empty()) {
        return false;
    }

    // Get bookmark start and end nodes
    pugi::xml_node start_para = paras[0];
    pugi::xml_node end_para = paras.back();

    // Find bookmark start and end markers
    pugi::xml_node bookmark_start, bookmark_end;
    std::string bookmark_id;

    for (pugi::xml_node child = start_para.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "w:bookmarkStart") {
            bookmark_start = child;
            bookmark_id = child.attribute("w:id").value();
            break;
        }
    }

    for (pugi::xml_node child = end_para.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "w:bookmarkEnd") {
            if (std::string(child.attribute("w:id").value()) == bookmark_id) {
                bookmark_end = child;
                break;
            }
        }
    }

    if (!bookmark_start || !bookmark_end) {
        // Fallback to simple text clearing
        return bookmark.set_text("");
    }

    // Single paragraph case: remove all content between bookmarkStart and bookmarkEnd
    if (start_para == end_para) {
        pugi::xml_node current = bookmark_start.next_sibling();
        while (current && current != bookmark_end) {
            pugi::xml_node next = current.next_sibling();
            // Remove all node types: w:r (runs), w:drawing (images), w:tbl (tables), etc.
            start_para.remove_child(current);
            current = next;
        }
    } else {
        // Cross-paragraph case
        // 1. Clear content from start paragraph (after bookmarkStart)
        pugi::xml_node current = bookmark_start.next_sibling();
        while (current) {
            pugi::xml_node next = current.next_sibling();
            start_para.remove_child(current);
            current = next;
        }

        // 2. Remove intermediate paragraphs entirely
        pugi::xml_node current_para = start_para.next_sibling("w:p");
        while (current_para && current_para != end_para) {
            pugi::xml_node next_para = current_para.next_sibling("w:p");
            start_para.parent().remove_child(current_para);
            current_para = next_para;
        }

        // 3. Clear content from end paragraph (before bookmarkEnd)
        if (end_para != start_para) {
            std::vector<pugi::xml_node> to_remove;
            for (pugi::xml_node child = end_para.first_child(); child && child != bookmark_end;
                 child = child.next_sibling()) {
                to_remove.push_back(child);
            }
            for (auto& node : to_remove) {
                end_para.remove_child(node);
            }
        }
    }

    return true;
}

bool BookmarkReplacer::insert_image_at_bookmark(Bookmark& bookmark,
                                                const std::string& image_path,
                                                const ImageSize& size,
                                                ImageAlignment align,
                                                const std::string& rel_id) {
    if (!bookmark.is_valid()) {
        return false;
    }

    // Get the paragraph containing the bookmark
    auto paras = bookmark.get_covered_paragraphs();
    if (paras.empty()) {
        return false;
    }

    pugi::xml_node para = paras[0];

    // Find bookmarkEnd node
    pugi::xml_node bookmark_end;
    for (pugi::xml_node child = para.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "w:bookmarkEnd") {
            bookmark_end = child;
            break;
        }
    }

    if (!bookmark_end) {
        // Append to end of paragraph
        bookmark_end = para.append_child("w:bookmarkEnd");
    }

    // Create run with drawing
    pugi::xml_node run = para.insert_child_before("w:r", bookmark_end);

    // Add drawing element
    pugi::xml_node drawing = run.append_child("w:drawing");

    // Create inline or anchor based on alignment
    if (align == ImageAlignment::Center) {
        // Use inline for center alignment
        pugi::xml_node inline_node = drawing.append_child("wp:inline");
        inline_node.append_attribute("distT").set_value(0);
        inline_node.append_attribute("distB").set_value(0);
        inline_node.append_attribute("distL").set_value(0);
        inline_node.append_attribute("distR").set_value(0);

        // Extent
        pugi::xml_node extent = inline_node.append_child("wp:extent");
        extent.append_attribute("cx").set_value(size.width_emu());
        extent.append_attribute("cy").set_value(size.height_emu());

        // Doc properties
        pugi::xml_node docPr = inline_node.append_child("wp:docPr");
        docPr.append_attribute("id").set_value(generate_image_id());
        docPr.append_attribute("name").set_value("Picture");

        // Add graphic data
        pugi::xml_node graphic = inline_node.append_child("a:graphic");
        graphic.append_attribute("xmlns:a").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/main");

        pugi::xml_node graphic_data = graphic.append_child("a:graphicData");
        graphic_data.append_attribute("uri").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node pic = graphic_data.append_child("pic:pic");
        pic.append_attribute("xmlns:pic")
            .set_value("http://schemas.openxmlformats.org/drawingml/2006/picture");

        // Non-visual picture properties
        pugi::xml_node nvPicPr = pic.append_child("pic:nvPicPr");
        pugi::xml_node cnvPr = nvPicPr.append_child("pic:cNvPr");
        cnvPr.append_attribute("id").set_value(0);
        cnvPr.append_attribute("name").set_value(image_path.c_str());
        nvPicPr.append_child("pic:cNvPicPr");

        // Blip fill
        pugi::xml_node blipFill = pic.append_child("pic:blipFill");
        pugi::xml_node blip = blipFill.append_child("a:blip");
        blip.append_attribute("r:embed").set_value(rel_id.c_str());
        pugi::xml_node stretch = blipFill.append_child("a:stretch");
        stretch.append_child("a:fillRect");

        // Shape properties
        pugi::xml_node spPr = pic.append_child("pic:spPr");
        pugi::xml_node xfrm = spPr.append_child("a:xfrm");
        pugi::xml_node ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx").set_value(size.width_emu());
        ext.append_attribute("cy").set_value(size.height_emu());
        pugi::xml_node prstGeom = spPr.append_child("a:prstGeom");
        prstGeom.append_attribute("prst").set_value("rect");
        prstGeom.append_child("a:avLst");

    } else {
        // Use anchor for left/right alignment
        pugi::xml_node anchor = drawing.append_child("wp:anchor");
        anchor.append_attribute("simplePos").set_value(0);
        anchor.append_attribute("relativeHeight").set_value(251658240);
        anchor.append_attribute("behindDoc").set_value(0);
        anchor.append_attribute("locked").set_value(0);
        anchor.append_attribute("layoutInCell").set_value(1);
        anchor.append_attribute("allowOverlap").set_value(1);

        // Simple position
        pugi::xml_node simplePos = anchor.append_child("wp:simplePos");
        simplePos.append_attribute("x").set_value(0);
        simplePos.append_attribute("y").set_value(0);

        // Horizontal position
        pugi::xml_node positionH = anchor.append_child("wp:positionH");
        positionH.append_attribute("relativeFrom").set_value("column");
        pugi::xml_node align_node = positionH.append_child("wp:align");
        align_node.text().set(align == ImageAlignment::Left ? "left" : "right");

        // Vertical position
        pugi::xml_node positionV = anchor.append_child("wp:positionV");
        positionV.append_attribute("relativeFrom").set_value("paragraph");
        pugi::xml_node posV_align = positionV.append_child("wp:align");
        posV_align.text().set("top");

        // Extent
        pugi::xml_node extent = anchor.append_child("wp:extent");
        extent.append_attribute("cx").set_value(size.width_emu());
        extent.append_attribute("cy").set_value(size.height_emu());

        // Doc properties
        pugi::xml_node docPr = anchor.append_child("wp:docPr");
        docPr.append_attribute("id").set_value(generate_image_id());
        docPr.append_attribute("name").set_value("Picture");

        // Graphic data (same as inline)
        pugi::xml_node graphic = anchor.append_child("a:graphic");
        graphic.append_attribute("xmlns:a").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/main");

        pugi::xml_node graphic_data = graphic.append_child("a:graphicData");
        graphic_data.append_attribute("uri").set_value(
            "http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node pic = graphic_data.append_child("pic:pic");
        pic.append_attribute("xmlns:pic")
            .set_value("http://schemas.openxmlformats.org/drawingml/2006/picture");

        pugi::xml_node nvPicPr = pic.append_child("pic:nvPicPr");
        pugi::xml_node cnvPr = nvPicPr.append_child("pic:cNvPr");
        cnvPr.append_attribute("id").set_value(0);
        cnvPr.append_attribute("name").set_value(image_path.c_str());
        nvPicPr.append_child("pic:cNvPicPr");

        pugi::xml_node blipFill = pic.append_child("pic:blipFill");
        pugi::xml_node blip = blipFill.append_child("a:blip");
        blip.append_attribute("r:embed").set_value(rel_id.c_str());
        pugi::xml_node stretch = blipFill.append_child("a:stretch");
        stretch.append_child("a:fillRect");

        pugi::xml_node spPr = pic.append_child("pic:spPr");
        pugi::xml_node xfrm = spPr.append_child("a:xfrm");
        pugi::xml_node ext = xfrm.append_child("a:ext");
        ext.append_attribute("cx").set_value(size.width_emu());
        ext.append_attribute("cy").set_value(size.height_emu());
        pugi::xml_node prstGeom = spPr.append_child("a:prstGeom");
        prstGeom.append_attribute("prst").set_value("rect");
        prstGeom.append_child("a:avLst");
    }

    return true;
}

std::string BookmarkReplacer::get_file_extension(const std::string& path) const {
    size_t dot_pos = path.rfind('.');
    if (dot_pos == std::string::npos) {
        return "";
    }

    std::string ext = path.substr(dot_pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext;
}

std::string BookmarkReplacer::get_content_type(const std::string& ext) const {
    if (ext == "png")
        return "image/png";
    if (ext == "jpg" || ext == "jpeg")
        return "image/jpeg";
    if (ext == "gif")
        return "image/gif";
    if (ext == "bmp")
        return "image/bmp";
    if (ext == "tiff" || ext == "tif")
        return "image/tiff";
    if (ext == "wmf")
        return "image/x-wmf";
    if (ext == "emf")
        return "image/x-emf";
    return "";
}

// ============================================================================
// Batch Transaction Support (P3 Enhancement)
// ============================================================================

std::vector<std::tuple<std::string, bool, std::string>> BookmarkReplacer::preview_replacements(
    const std::map<std::string, std::string>& replacements) const {
    std::vector<std::tuple<std::string, bool, std::string>> results;

    for (const auto& pair : replacements) {
        const std::string& bookmark_name = pair.first;

        if (!doc_) {
            results.emplace_back(bookmark_name, false, "Document not available");
            continue;
        }

        auto bm = get_bookmark(bookmark_name);
        if (bm) {
            results.emplace_back(bookmark_name, true, "");
        } else {
            results.emplace_back(bookmark_name, false, "Bookmark not found");
        }
    }

    return results;
}

bool BookmarkReplacer::BatchResult::did_succeed(const std::string& bookmark_name) const {
    for (const auto& failure : failures) {
        if (failure.first == bookmark_name) {
            return false;
        }
    }
    // If not in failures and we have some successes, assume it succeeded
    return true;
}

std::string BookmarkReplacer::BatchResult::get_error(const std::string& bookmark_name) const {
    for (const auto& failure : failures) {
        if (failure.first == bookmark_name) {
            return failure.second;
        }
    }
    return "";
}

BookmarkReplacer::BatchResult BookmarkReplacer::replace_text_batch_transaction(
    const std::map<std::string, std::string>& replacements, bool strict) {
    BatchResult result;

    if (!doc_ || replacements.empty()) {
        result.all_succeeded = false;
        return result;
    }

    // Step 1: Preview - validate all bookmarks exist
    auto preview = preview_replacements(replacements);
    bool all_exist = true;
    for (const auto& item : preview) {
        const std::string& name = std::get<0>(item);
        bool exists = std::get<1>(item);
        const std::string& error = std::get<2>(item);

        if (!exists) {
            all_exist = false;
            result.failures.emplace_back(name, error);
            result.fail_count++;
        }
    }

    if (!all_exist) {
        result.all_succeeded = false;
        if (strict) {
            // In strict mode, abort if any bookmark doesn't exist
            return result;
        }
        // In non-strict mode, continue with existing bookmarks only
    }

    // Step 2: Create backup by saving to memory (if document is saved to disk)
    // Note: Full backup/restore would require deep copy of XML documents
    // For now, we track what was modified for potential rollback
    std::vector<std::string> successfully_replaced;

    // Step 3: Perform replacements
    for (const auto& pair : replacements) {
        const std::string& bookmark_name = pair.first;
        const std::string& new_text = pair.second;

        // Skip if bookmark doesn't exist (already counted in preview)
        if (!has_bookmark(bookmark_name)) {
            continue;
        }

        // Attempt replacement
        if (replace_text(bookmark_name, new_text)) {
            result.success_count++;
            successfully_replaced.push_back(bookmark_name);
        } else {
            result.fail_count++;
            result.failures.emplace_back(bookmark_name, "Replacement failed");

            if (strict) {
                // Rollback: restore original text for already replaced bookmarks
                // Note: This is a simplified rollback - full implementation would
                // require storing original text before replacement
                result.all_succeeded = false;
                // In a full implementation, we would restore original texts here
                return result;
            }
        }
    }

    result.all_succeeded = (result.fail_count == 0);
    return result;
}

}  // namespace cdocx
