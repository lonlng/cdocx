/**
 * @file formfield.cpp
 * @brief Form field implementation
 * @since 0.7.0
 */

#include <cdocx/formfield.h>

namespace cdocx {

FormField::FormField() = default;

FormField::FormField(Document* doc) {
    set_document(doc);
}

FormField::FormField(Document* doc, FormFieldType type) : type_(type) {
    set_document(doc);
}

void FormField::accept(DocumentVisitor* visitor) {
    if (!visitor) {
        return;
    }
    visitor->visit_form_field(*this);
}

std::shared_ptr<Node> FormField::clone(bool /*deep*/) const {
    auto cloned = std::make_shared<FormField>(get_document(), type_);
    cloned->name_ = name_;
    cloned->result_ = result_;
    cloned->enabled_ = enabled_;
    cloned->calculate_on_exit_ = calculate_on_exit_;
    cloned->status_text_ = status_text_;
    cloned->help_text_ = help_text_;
    cloned->entry_macro_ = entry_macro_;
    cloned->exit_macro_ = exit_macro_;
    cloned->text_input_type_ = text_input_type_;
    cloned->text_input_format_ = text_input_format_;
    cloned->text_input_default_ = text_input_default_;
    cloned->max_length_ = max_length_;
    cloned->checked_ = checked_;
    cloned->default_value_ = default_value_;
    cloned->is_exact_size_ = is_exact_size_;
    cloned->check_box_size_ = check_box_size_;
    cloned->drop_down_items_ = drop_down_items_;
    cloned->selected_index_ = selected_index_;
    return cloned;
}

}  // namespace cdocx
