/**
 * @file template_engine.cpp
 * @brief TemplateEngine implementation
 * @author lonlng
 * @copyright MIT License
 * @date 2026
 * @version 0.8.0
 */

#include <cdocx/bookmark_replacer.h>
#include <cdocx/document.h>
#include <cdocx/template.h>
#include <cdocx/template_engine.h>

#include "sync_common.h"

#include <filesystem>
#include <memory>
#include <unordered_set>

namespace {

// Helper: append a child node with a single attribute/value pair.
pugi::xml_node append_attr_node(pugi::xml_node parent,
                                const char* name,
                                const char* attr,
                                const char* value) {
    pugi::xml_node n = parent.append_child(name);
    n.append_attribute(attr).set_value(value);
    return n;
}

pugi::xml_node append_attr_node(pugi::xml_node parent,
                                const char* name,
                                const char* attr,
                                int value) {
    pugi::xml_node n = parent.append_child(name);
    n.append_attribute(attr).set_value(value);
    return n;
}

}  // namespace

namespace cdocx {

// ============================================================================
// TemplateFormat
// ============================================================================

TemplateFormat& TemplateFormat::bold(bool value) {
    bold_ = value;
    return *this;
}

TemplateFormat& TemplateFormat::italic(bool value) {
    italic_ = value;
    return *this;
}

TemplateFormat& TemplateFormat::underline(bool value) {
    underline_ = value;
    return *this;
}

TemplateFormat& TemplateFormat::strikethrough(bool value) {
    strikethrough_ = value;
    return *this;
}

TemplateFormat& TemplateFormat::size(int half_points) {
    size_ = half_points;
    return *this;
}

TemplateFormat& TemplateFormat::font(const std::string& name) {
    font_ = name;
    font_ascii_ = name;
    font_far_east_ = name;
    return *this;
}

TemplateFormat& TemplateFormat::font_ascii(const std::string& name) {
    font_ascii_ = name;
    return *this;
}

TemplateFormat& TemplateFormat::font_far_east(const std::string& name) {
    font_far_east_ = name;
    return *this;
}

TemplateFormat& TemplateFormat::color(const std::string& hex) {
    color_ = hex;
    return *this;
}

TemplateFormat& TemplateFormat::alignment(const std::string& align) {
    alignment_ = align;
    return *this;
}

TemplateFormat& TemplateFormat::line_spacing(int twips) {
    line_spacing_ = twips;
    return *this;
}

TemplateFormat& TemplateFormat::space_before(int twips) {
    space_before_ = twips;
    return *this;
}

TemplateFormat& TemplateFormat::space_after(int twips) {
    space_after_ = twips;
    return *this;
}

BookmarkFormat TemplateFormat::to_bookmark_format() const {
    BookmarkFormat fmt;
    if (font_ascii_) fmt.font_ascii = *font_ascii_;
    if (font_far_east_) fmt.font_far_east = *font_far_east_;
    if (size_) fmt.font_size = *size_;
    if (color_) fmt.color = *color_;
    if (bold_) fmt.bold = *bold_;
    if (italic_) fmt.italic = *italic_;
    if (underline_) fmt.underline = *underline_;
    if (strikethrough_) fmt.strikethrough = *strikethrough_;
    if (alignment_) fmt.alignment = *alignment_;
    if (line_spacing_) fmt.line_spacing = *line_spacing_;
    if (space_before_) fmt.space_before = *space_before_;
    if (space_after_) fmt.space_after = *space_after_;
    return fmt;
}

bool TemplateFormat::is_empty() const {
    const auto has = [](const auto&... opts) { return (!opts.has_value() && ...); };
    return has(bold_, italic_, underline_, strikethrough_, size_, font_, font_ascii_,
               font_far_east_, color_, alignment_, line_spacing_, space_before_, space_after_);
}

// ============================================================================
// TemplateValue
// ============================================================================

TemplateValue::TemplateValue(TextData data)
    : type_(TemplateValueType::Text), data_(std::move(data)) {}

TemplateValue::TemplateValue(ImageData data)
    : type_(TemplateValueType::Image), data_(std::move(data)) {}

TemplateValue TemplateValue::text(const std::string& content) {
    return TemplateValue(TextData{content, TemplateFormat()});
}

TemplateValue TemplateValue::text(const std::string& content, const TemplateFormat& format) {
    return TemplateValue(TextData{content, format});
}

TemplateValue TemplateValue::image(const std::string& path) {
    return TemplateValue(ImageData{path, ImageSize(), "", ImageAlignment::Center});
}

TemplateValue TemplateValue::image(const std::string& path, double width, double height) {
    return TemplateValue(ImageData{path, ImageSize(width, height), "", ImageAlignment::Center});
}

TemplateValue& TemplateValue::with_format(const TemplateFormat& format) {
    if (std::holds_alternative<TextData>(data_)) {
        std::get<TextData>(data_).format = format;
    }
    return *this;
}

TemplateValue& TemplateValue::sized(double width_pt, double height_pt) {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).size = ImageSize(width_pt, height_pt);
    }
    return *this;
}

TemplateValue& TemplateValue::sized(const ImageSize& size) {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).size = size;
    }
    return *this;
}

TemplateValue& TemplateValue::centered() {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).align = ImageAlignment::Center;
    }
    return *this;
}

TemplateValue& TemplateValue::left_aligned() {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).align = ImageAlignment::Left;
    }
    return *this;
}

TemplateValue& TemplateValue::right_aligned() {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).align = ImageAlignment::Right;
    }
    return *this;
}

TemplateValue& TemplateValue::with_caption(const std::string& caption) {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).caption = caption;
    }
    return *this;
}

TemplateValue& TemplateValue::with_alignment(ImageAlignment align) {
    if (std::holds_alternative<ImageData>(data_)) {
        std::get<ImageData>(data_).align = align;
    }
    return *this;
}

const std::string& TemplateValue::text_content() const {
    return std::get<TextData>(data_).content;
}

const TemplateFormat& TemplateValue::text_format() const {
    return std::get<TextData>(data_).format;
}

const std::string& TemplateValue::image_path() const {
    return std::get<ImageData>(data_).path;
}

const ImageSize& TemplateValue::image_size() const {
    return std::get<ImageData>(data_).size;
}

const std::string& TemplateValue::image_caption() const {
    return std::get<ImageData>(data_).caption;
}

ImageAlignment TemplateValue::image_alignment() const {
    return std::get<ImageData>(data_).align;
}

// ============================================================================
// TemplateEngine::Setter
// ============================================================================

TemplateEngine::Setter::Setter(TemplateEngine* engine, std::string key)
    : engine_(engine), key_(std::move(key)) {}

TemplateEngine::Setter& TemplateEngine::Setter::operator=(const TemplateValue& value) {
    engine_->set(key_, value);
    return *this;
}

TemplateEngine::Setter& TemplateEngine::Setter::operator=(TemplateValue&& value) {
    engine_->set(key_, std::move(value));
    return *this;
}

TemplateEngine::Setter& TemplateEngine::Setter::operator=(const std::string& text) {
    engine_->set(key_, text);
    return *this;
}

TemplateEngine::Setter& TemplateEngine::Setter::operator=(const char* text) {
    engine_->set(key_, text);
    return *this;
}

// ============================================================================
// TemplateEngine
// ============================================================================

TemplateEngine::TemplateEngine(Document* doc) : doc_(doc) {}

TemplateEngine::Setter TemplateEngine::operator[](const std::string& key) {
    return {this, key};
}

TemplateEngine& TemplateEngine::set(const std::string& key, const TemplateValue& value) {
    queue_[key] = value;
    return *this;
}

TemplateEngine& TemplateEngine::set(const std::string& key, TemplateValue&& value) {
    queue_[key] = std::move(value);
    return *this;
}

TemplateEngine& TemplateEngine::set(const std::string& key, const std::string& text) {
    queue_[key] = TemplateValue::text(text);
    return *this;
}

TemplateEngine& TemplateEngine::set(const std::string& key, const char* text) {
    queue_[key] = TemplateValue::text(text ? std::string(text) : std::string());
    return *this;
}

TemplateEngine& TemplateEngine::set_batch(const std::map<std::string, TemplateValue>& data) {
    for (const auto& [key, value] : data) {
        queue_[key] = value;
    }
    return *this;
}

TemplateEngine& TemplateEngine::set_batch(const std::map<std::string, std::string>& data) {
    for (const auto& [key, text] : data) {
        queue_[key] = TemplateValue::text(text);
    }
    return *this;
}

TemplateEngine& TemplateEngine::with_action(TemplateAction action) {
    default_action_ = action;
    return *this;
}

TemplateEngine& TemplateEngine::with_scope(TemplateScope scope) {
    default_scope_ = scope;
    return *this;
}

TemplateEngine& TemplateEngine::with_target(TemplateTarget target) {
    default_target_ = target;
    return *this;
}

TemplateEngine& TemplateEngine::with_format_policy(FormatPolicy policy) {
    default_format_policy_ = policy;
    return *this;
}

TemplateEngine& TemplateEngine::with_default_format(const TemplateFormat& format) {
    default_format_ = format;
    return *this;
}

TemplateEngine& TemplateEngine::with_delimiters(const std::string& prefix,
                                               const std::string& suffix) {
    delimiter_prefix_ = prefix;
    delimiter_suffix_ = suffix;
    return *this;
}

bool TemplateEngine::has(const std::string& key) const {
    return queue_.find(key) != queue_.end();
}

TemplateEngine& TemplateEngine::remove(const std::string& key) {
    queue_.erase(key);
    return *this;
}

TemplateEngine& TemplateEngine::clear() {
    queue_.clear();
    return *this;
}

size_t TemplateEngine::size() const {
    return queue_.size();
}

// ============================================================================
// Execution
// ============================================================================

// ============================================================================
// Target Resolution
// ============================================================================

/** @brief Cached bookmark name lookup for batch template operations. */
class BookmarkNameCache {
  public:
    explicit BookmarkNameCache(Document* doc) {
        if (doc) {
            const BookmarkReplacer replacer(doc);
            for (const auto& bm : doc->get_bookmarks()) {
                names_.insert(bm.get_name());
            }
        }
    }

    bool contains(const std::string& name) const {
        return names_.find(name) != names_.end();
    }

  private:
    std::unordered_set<std::string> names_;
};

static TemplateTarget resolve_target(const BookmarkNameCache* cache,
                                    const std::string& key,
                                    TemplateTarget preferred) {
    if (preferred == TemplateTarget::Auto) {
        return (cache && cache->contains(key)) ? TemplateTarget::BookmarkTarget
                                               : TemplateTarget::Placeholder;
    }
    return preferred;
}

static TemplateTarget resolve_target(Document* doc,
                                    const std::string& key,
                                    TemplateTarget preferred,
                                    const std::string& /*prefix*/,
                                    const std::string& /*suffix*/) {
    if (preferred == TemplateTarget::Auto) {
        const BookmarkReplacer replacer(doc);
        return replacer.has_bookmark(key) ? TemplateTarget::BookmarkTarget
                                          : TemplateTarget::Placeholder;
    }
    return preferred;
}

// ============================================================================
// Insert Mode Helpers (Physical XML)
// ============================================================================

static pugi::xml_node find_bookmark_start(pugi::xml_node para) {
    for (pugi::xml_node child = para.first_child(); child; child = child.next_sibling()) {
        if (is_bookmark_start_node(child.name())) {
            return child;
        }
    }
    return pugi::xml_node{};
}

static bool insert_formatted_run_after(pugi::xml_node para,
                                        pugi::xml_node after_node,
                                        const std::string& text,
                                        const BookmarkFormat& format) {
    pugi::xml_node run = para.insert_child_after("w:r", after_node);
    if (!run) {
        return false;
    }

    const bool has_run_props = format.is_valid() || format.bold || format.italic ||
                               format.underline || format.strikethrough ||
                               !format.color.empty();
    if (has_run_props) {
        pugi::xml_node run_props = run.append_child("w:rPr");

        if (!format.font_ascii.empty() || !format.font_far_east.empty()) {
            pugi::xml_node run_fonts = run_props.append_child("w:rFonts");
            if (!format.font_ascii.empty()) {
                run_fonts.append_attribute("w:ascii").set_value(format.font_ascii.c_str());
            }
            if (!format.font_far_east.empty()) {
                run_fonts.append_attribute("w:eastAsia").set_value(format.font_far_east.c_str());
            }
        }

        if (format.font_size > 0) {
            append_attr_node(run_props, "w:sz", "w:val", format.font_size);
            append_attr_node(run_props, "w:szCs", "w:val", format.font_size);
        }

        if (!format.color.empty()) {
            append_attr_node(run_props, "w:color", "w:val", format.color.c_str());
        }

        if (format.bold) {
            run_props.append_child("w:b");
        }
        if (format.italic) {
            run_props.append_child("w:i");
        }
        if (format.underline) {
            append_attr_node(run_props, "w:u", "w:val", "single");
        }
        if (format.strikethrough) {
            run_props.append_child("w:strike");
        }
    }

    run.append_child("w:t").text().set(text.c_str());
    return true;
}

static bool insert_image_run_after(pugi::xml_node para,
                                    pugi::xml_node after_node,
                                    const ImageSize& size,
                                    ImageAlignment align,
                                    const std::string& rel_id,
                                    int image_id) {
    pugi::xml_node run = para.insert_child_after("w:r", after_node);
    if (!run) {
        return false;
    }

    append_image_drawing(run, rel_id, size, align, image_id, "image");
    return true;
}

// ============================================================================
// Execution
// ============================================================================

TemplateEngine::Result TemplateEngine::apply() {
    return apply_if([](const std::string&) { return true; });
}

TemplateEngine::Result TemplateEngine::apply(const std::string& key) {
    last_result_ = Result();
    if (!doc_ || !doc_->is_open()) {
        return last_result_;
    }

    auto it = queue_.find(key);
    if (it == queue_.end()) {
        return last_result_;
    }

    const auto& value = it->second;
    if (value.is_empty()) {
        last_result_.skipped++;
        return last_result_;
    }

    auto actual = resolve_target(doc_, key, default_target_,
                                 delimiter_prefix_, delimiter_suffix_);
    if (actual == TemplateTarget::Placeholder) {
        last_result_ = apply_placeholder(key, value);
    } else {
        last_result_ = apply_bookmark(key, value);
        doc_->sync_from_physical_tree();
    }
    return last_result_;
}

TemplateEngine::Result TemplateEngine::apply_if(
    const std::function<bool(const std::string&)>& predicate) {
    last_result_ = Result();
    if (!doc_ || !doc_->is_open() || queue_.empty()) {
        return last_result_;
    }

    // Cache bookmark names once for Auto target resolution (avoids O(n*m) DOM sync)
    std::unique_ptr<BookmarkNameCache> bm_cache;
    if (default_target_ == TemplateTarget::Auto) {
        bm_cache = std::make_unique<BookmarkNameCache>(doc_);
    }

    std::vector<std::pair<std::string, TemplateValue>> placeholders;
    std::vector<std::pair<std::string, TemplateValue>> bookmarks;

    for (const auto& [key, value] : queue_) {
        if (!predicate(key)) {
            last_result_.skipped++;
            continue;
        }
        if (value.is_empty()) {
            last_result_.skipped++;
            continue;
        }
        auto actual = resolve_target(bm_cache.get(), key, default_target_);
        if (actual == TemplateTarget::Placeholder) {
            placeholders.emplace_back(key, value);
        } else {
            bookmarks.emplace_back(key, value);
        }
    }

    if (!placeholders.empty()) {
        for (const auto& [key, value] : placeholders) {
            auto r = apply_placeholder(key, value);
            last_result_.success += r.success;
            last_result_.failed += r.failed;
        }
        doc_->sync_to_physical_tree();
    }

    if (!bookmarks.empty()) {
        if (placeholders.empty()) {
            doc_->sync_to_physical_tree();
        }
        auto collection = doc_->get_bookmarks();

        for (const auto& [key, value] : bookmarks) {
            auto bm_opt = collection.get(key);
            if (!bm_opt) {
                last_result_.failed++;
                continue;
            }
            if (value.is_text()) {
                const bool ok = apply_text_to_bookmark(
                    *bm_opt, value.text_content(), value.text_format(), default_format_policy_);
                if (ok) {
                    last_result_.success++;
                } else {
                    last_result_.failed++;
                }
            } else if (value.is_image()) {
                const bool ok = apply_image_to_bookmark(*bm_opt, value);
                if (ok) {
                    last_result_.success++;
                } else {
                    last_result_.failed++;
                }
            }
        }
        doc_->sync_from_physical_tree();
    }

    return last_result_;
}

// ============================================================================
// Internal Execution
// ============================================================================

TemplateEngine::Result TemplateEngine::apply_bookmark(const std::string& key,
                                                     const TemplateValue& value) {
    Result r;
    const BookmarkReplacer replacer(doc_);

    if (!replacer.has_bookmark(key)) {
        return r;  // Not found - return empty result for fallback
    }

    if (value.is_text()) {
        const bool ok = apply_text_to_bookmark(
            key, value.text_content(), value.text_format(), default_format_policy_);
        if (ok) {
            r.success++;
        } else {
            r.failed++;
        }
    } else if (value.is_image()) {
        const bool ok = apply_image_to_bookmark(key, value);
        if (ok) {
            r.success++;
        } else {
            r.failed++;
        }
    }

    return r;
}

TemplateEngine::Result TemplateEngine::apply_bookmark(Bookmark& bookmark,
                                                     const TemplateValue& value) {
    Result r;

    if (value.is_text()) {
        const bool ok = apply_text_to_bookmark(
            bookmark, value.text_content(), value.text_format(), default_format_policy_);
        if (ok) {
            r.success++;
        } else {
            r.failed++;
        }
    } else if (value.is_image()) {
        const bool ok = apply_image_to_bookmark(bookmark, value);
        if (ok) {
            r.success++;
        } else {
            r.failed++;
        }
    }

    return r;
}

TemplateEngine::Result TemplateEngine::apply_placeholder(const std::string& key,
                                                        const TemplateValue& value) {
    Result r;
    const Template tmpl(doc_, delimiter_prefix_, delimiter_suffix_);

    if (value.is_text()) {
        const bool ok = apply_text_to_placeholder(key, value.text_content());
        if (ok) {
            r.success++;
        } else {
            r.failed++;
        }
    } else if (value.is_image()) {
        const bool ok = apply_image_to_placeholder(key, value);
        if (ok) {
            r.success++;
        } else {
            r.failed++;
        }
    }

    return r;
}

bool TemplateEngine::apply_text_to_bookmark(const std::string& name,
                                           const std::string& text,
                                           const TemplateFormat& format,
                                           FormatPolicy policy) {
    auto collection = doc_->get_bookmarks();
    auto bm_opt = collection.get(name);
    if (!bm_opt) {
        return false;
    }
    return apply_text_to_bookmark(*bm_opt, text, format, policy);
}

bool TemplateEngine::apply_text_to_bookmark(Bookmark& bookmark,
                                           const std::string& text,
                                           const TemplateFormat& format,
                                           FormatPolicy policy) {
    if (default_action_ == TemplateAction::Insert) {
        if (!bookmark.is_valid()) {
            return false;
        }

        auto paras = bookmark.get_covered_paragraphs();
        if (paras.empty()) {
            return false;
        }

        const pugi::xml_node bookmark_start = find_bookmark_start(paras[0]);
        if (!bookmark_start) {
            return false;
        }

        BookmarkFormat bmf;
        if (policy == FormatPolicy::Preserve) {
            bmf = bookmark.get_format();
        } else {
            TemplateFormat effective = format;
            if (effective.is_empty() && !default_format_.is_empty()) {
                effective = default_format_;
            }
            if (!effective.is_empty()) {
                bmf = effective.to_bookmark_format();
            } else if (policy == FormatPolicy::Custom) {
                bmf = bookmark.get_format();
            }
        }

        return insert_formatted_run_after(paras[0], bookmark_start, text, bmf);
    }

    // Replace mode
    BookmarkReplacer replacer(doc_);

    switch (policy) {
        case FormatPolicy::Preserve:
            return replacer.replace_text(bookmark, text);

        case FormatPolicy::Override:
        case FormatPolicy::Custom: {
            if (format.is_empty() && policy == FormatPolicy::Custom) {
                return replacer.replace_text(bookmark, text);
            }
            TemplateFormat effective = format;
            if (effective.is_empty() && !default_format_.is_empty()) {
                effective = default_format_;
            }
            if (effective.is_empty()) {
                return replacer.replace_text(bookmark, text);
            }
            return replacer.replace_text_with_format(bookmark, text,
                                                     effective.to_bookmark_format());
        }
    }
    return false;
}

bool TemplateEngine::apply_image_to_bookmark(const std::string& name,
                                            const TemplateValue& value) {
    auto collection = doc_->get_bookmarks();
    auto bm_opt = collection.get(name);
    if (!bm_opt) {
        return false;
    }
    return apply_image_to_bookmark(*bm_opt, value);
}

bool TemplateEngine::apply_image_to_bookmark(Bookmark& bookmark,
                                            const TemplateValue& value) {
    if (default_action_ == TemplateAction::Insert) {
        if (!bookmark.is_valid()) {
            return false;
        }

        auto paras = bookmark.get_covered_paragraphs();
        if (paras.empty()) {
            return false;
        }

        const pugi::xml_node bookmark_start = find_bookmark_start(paras[0]);
        if (!bookmark_start) {
            return false;
        }

        const auto& path = value.image_path();
        const auto& size = value.image_size();
        auto align = value.image_alignment();

        if (!std::filesystem::exists(path)) {
            return false;
        }

        ImageSize actual_size = size;
        if (!actual_size.is_valid()) {
            if (!detect_image_size(path, actual_size)) {
                actual_size = ImageSize(400, 300);
            }
        }

        const std::string rel_id = doc_->add_media_with_rel(path, nullptr);
        if (rel_id.empty()) {
            return false;
        }

        return insert_image_run_after(paras[0], bookmark_start, actual_size, align, rel_id,
                                      image_counter_++);
    }

    // Replace mode
    BookmarkReplacer replacer(doc_);
    const auto& path = value.image_path();
    const auto& size = value.image_size();
    const auto& caption = value.image_caption();
    auto align = value.image_alignment();

    if (!std::filesystem::exists(path)) {
        return false;
    }

    if (size.is_valid()) {
        return replacer.replace_with_image_advanced(bookmark, path, size, caption, align);
    } else {
        return replacer.replace_with_image(bookmark, path, caption);
    }
}

bool TemplateEngine::apply_text_to_placeholder(const std::string& key,
                                              const std::string& text) {
    Template tmpl(doc_, delimiter_prefix_, delimiter_suffix_);
    if (default_action_ == TemplateAction::Insert) {
        const std::string pattern = delimiter_prefix_ + key + delimiter_suffix_;
        // Prevent unintended cascading replacements if the replacement text
        // itself contains the placeholder pattern.
        if (text.find(pattern) != std::string::npos || text.empty()) {
            return false;
        }
        tmpl.set(key, text + pattern);
    } else {
        tmpl.set(key, text);
    }
    if (default_scope_ == TemplateScope::First) {
        return tmpl.replace_first();
    }
    tmpl.replace_all();
    return true;
}

bool TemplateEngine::apply_image_to_placeholder(const std::string& key,
                                               const TemplateValue& value) {
    if (default_action_ == TemplateAction::Insert) {
        return false;
    }
    Template tmpl(doc_, delimiter_prefix_, delimiter_suffix_);
    tmpl.set_image(key, value.image_path());
    if (default_scope_ == TemplateScope::First) {
        return tmpl.replace_first();
    }
    tmpl.replace_all();
    return true;
}

}  // namespace cdocx
