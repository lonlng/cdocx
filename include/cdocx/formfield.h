/**
 * @file formfield.h
 * @brief Form field support for CDocx
 * @details Provides legacy form field functionality including text input,
 *          checkbox, and dropdown (combobox) fields.
 *
 * @since 0.7.0
 */

#pragma once

#include <cdocx/enums.h>
#include <cdocx/node.h>

#include <string>
#include <vector>

namespace cdocx {

// ============================================================================
// FormField - Legacy form field (text input, checkbox, dropdown)
// ============================================================================

class FormField : public Node {
  public:
    FormField();
    explicit FormField(Document* doc);
    FormField(Document* doc, FormFieldType type);

    std::string get_name() const { return name_; }
    void set_name(const std::string& name) { name_ = name; }

    FormFieldType get_form_field_type() const { return type_; }
    void set_form_field_type(FormFieldType type) { type_ = type; }

    std::string get_result() const { return result_; }
    void set_result(const std::string& result) { result_ = result; }

    bool get_enabled() const { return enabled_; }
    void set_enabled(bool enabled) { enabled_ = enabled; }

    bool get_calculate_on_exit() const { return calculate_on_exit_; }
    void set_calculate_on_exit(bool value) { calculate_on_exit_ = value; }

    std::string get_status_text() const { return status_text_; }
    void set_status_text(const std::string& text) { status_text_ = text; }

    std::string get_help_text() const { return help_text_; }
    void set_help_text(const std::string& text) { help_text_ = text; }

    std::string get_entry_macro() const { return entry_macro_; }
    void set_entry_macro(const std::string& macro) { entry_macro_ = macro; }

    std::string get_exit_macro() const { return exit_macro_; }
    void set_exit_macro(const std::string& macro) { exit_macro_ = macro; }

    // Text input specific
    TextFormFieldType get_text_input_type() const { return text_input_type_; }
    void set_text_input_type(TextFormFieldType type) { text_input_type_ = type; }

    std::string get_text_input_format() const { return text_input_format_; }
    void set_text_input_format(const std::string& format) { text_input_format_ = format; }

    std::string get_text_input_default() const { return text_input_default_; }
    void set_text_input_default(const std::string& value) { text_input_default_ = value; }

    int get_max_length() const { return max_length_; }
    void set_max_length(int length) { max_length_ = length; }

    // Check box specific
    bool get_checked() const { return checked_; }
    void set_checked(bool checked) { checked_ = checked; }

    bool get_default_value() const { return default_value_; }
    void set_default_value(bool value) { default_value_ = value; }

    bool get_is_check_box_exact_size() const { return is_exact_size_; }
    void set_is_check_box_exact_size(bool value) { is_exact_size_ = value; }

    double get_check_box_size() const { return check_box_size_; }
    void set_check_box_size(double size) { check_box_size_ = size; }

    // Combo box specific
    const std::vector<std::string>& get_drop_down_items() const { return drop_down_items_; }
    void set_drop_down_items(const std::vector<std::string>& items) { drop_down_items_ = items; }

    int get_drop_down_selected_index() const { return selected_index_; }
    void set_drop_down_selected_index(int index) { selected_index_ = index; }

    // Node overrides
    NodeType node_type() const override { return NodeType::FormField; }
    std::string get_text() const override { return result_; }
    void accept(DocumentVisitor* visitor) override;
    std::shared_ptr<Node> clone(bool deep) const override;

  private:
    FormFieldType type_ = FormFieldType::TextInput;
    std::string name_;
    std::string result_;
    bool enabled_ = true;
    bool calculate_on_exit_ = false;
    std::string status_text_;
    std::string help_text_;
    std::string entry_macro_;
    std::string exit_macro_;

    // Text input
    TextFormFieldType text_input_type_ = TextFormFieldType::Regular;
    std::string text_input_format_;
    std::string text_input_default_;
    int max_length_ = 0;

    // Check box
    bool checked_ = false;
    bool default_value_ = false;
    bool is_exact_size_ = false;
    double check_box_size_ = 0;

    // Drop down
    std::vector<std::string> drop_down_items_;
    int selected_index_ = 0;
};

}  // namespace cdocx
