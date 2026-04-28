/**
 * @file paragraph_builder.cpp
 * @brief ParagraphBuilder implementation
 * @since 0.8.0
 */

#include <cdocx/base.h>
#include <cdocx/paragraph.h>
#include <cdocx/paragraph_builder.h>

namespace cdocx {

ParagraphBuilder::ParagraphBuilder() : para_(std::make_shared<Paragraph>()) {
}

ParagraphBuilder::ParagraphBuilder(const std::string& text) : para_(std::make_shared<Paragraph>()) {
    para_->append_text(text);
}

ParagraphBuilder& ParagraphBuilder::add_run(const std::string& text) {
    auto run = std::make_shared<Run>();
    run->set_text(text);
    apply_current_formatting(*run);
    para_->append_child(run);
    return *this;
}

ParagraphBuilder& ParagraphBuilder::add_run(const std::string& text,
                                            bool bold,
                                            bool italic,
                                            int font_size) {
    auto run = std::make_shared<Run>();
    run->set_text(text);
    run->set_bold(bold);
    run->set_italic(italic);
    if (font_size > 0) {
        run->set_font_size(font_size);
    }
    para_->append_child(run);
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_bold(bool value) {
    bold_ = value;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_italic(bool value) {
    italic_ = value;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_underline(bool value) {
    underline_ = value;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_font_name(const std::string& name) {
    font_name_ = name;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_font_size(int size) {
    font_size_ = size;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_color(const std::string& color_hex) {
    color_ = color_hex;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::set_alignment(const std::string& alignment) {
    alignment_ = alignment;
    return *this;
}

ParagraphBuilder& ParagraphBuilder::clear_formatting() {
    bold_ = false;
    italic_ = false;
    underline_ = false;
    font_name_.clear();
    font_size_ = 0;
    color_.clear();
    return *this;
}

std::shared_ptr<Paragraph> ParagraphBuilder::build() {
    if (!alignment_.empty()) {
        para_->set_alignment(alignment_);
    }
    return para_;
}

void ParagraphBuilder::apply_current_formatting(Run& run) {
    run.set_bold(bold_);
    run.set_italic(italic_);
    if (underline_) {
        run.set_underline(UnderlineType::Single);
    }
    if (!font_name_.empty()) {
        run.set_font_name(font_name_);
    }
    if (font_size_ > 0) {
        run.set_font_size(font_size_);
    }
    if (!color_.empty()) {
        run.set_color(color_);
    }
}

}  // namespace cdocx
