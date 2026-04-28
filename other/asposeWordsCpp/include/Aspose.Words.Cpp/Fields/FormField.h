//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FormField.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/SpecialChar.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Fields/TextFormFieldType.h>
#include <Aspose.Words.Cpp/Fields/FieldType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class DocumentBase;

class DocumentVisitor;
namespace Fields
{
class DropDownItemCollection;

}
class Inline;
class INodeCloningListener;

class Node;

class RunPr;

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents a single form field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-form-fields/">Working with Form Fields</a> documentation article.
/// 
/// %Microsoft Word provides the following form fields: checkbox, text input and dropdown (combobox).
/// 
/// <see cref="Aspose::Words::Fields::FormField">FormField</see> is an inline-node and can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// <see cref="Aspose::Words::Fields::FormField">FormField</see> is represented in a document by a special character and
/// positioned as a character within a line of text.
/// 
/// A complete form field in a Word document is a complex structure represented by several
/// nodes: field start, field code such as FORMTEXT, form field data, field separator,
/// field result, field end and a bookmark. To programmatically create form fields in a Word document use
/// <see cref="Aspose::Words::DocumentBuilder::InsertCheckBox(System::String, bool, int32_t)">InsertCheckBox()</see>,
/// <see cref="Aspose::Words::DocumentBuilder::InsertTextInput(System::String, Aspose::Words::Fields::TextFormFieldType, System::String, System::String, int32_t)">InsertTextInput()</see> and
/// <see cref="Aspose::Words::DocumentBuilder::InsertComboBox(System::String, System::ArrayPtr<System::String>, int32_t)">InsertComboBox()</see> which
/// make sure all of the form field nodes are created in a correct order and in a suitable state.
class ASPOSE_WORDS_SHARED_CLASS FormField : public Aspose::Words::SpecialChar
{
    typedef FormField ThisType;
    typedef Aspose::Words::SpecialChar BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::SpecialChar::Clone;

public:

    /// Returns <see cref="Aspose::Words::NodeType::FormField">FormField</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets the form field name.
    ASPOSE_WORDS_SHARED_API System::String get_Name();
    /// Sets the form field name.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Returns the form field type.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldType get_Type();
    /// Gets or sets a string that represents the result of this form field.
    /// 
    /// For a text form field the result is the text that is in the field.
    /// 
    /// For a checkbox form field the result can be "1" or "0" to indicate checked or unchecked.
    /// 
    /// For a dropdown form field the result is the string selected in the dropdown.
    /// 
    /// Setting <see cref="Aspose::Words::Fields::FormField::get_Result">Result</see> for a text form field does not apply the text format
    /// specified in <see cref="Aspose::Words::Fields::FormField::get_TextInputFormat">TextInputFormat</see>. If you want to set a value and apply the
    /// format, use the <see cref="Aspose::Words::Fields::FormField::SetTextInputValue(System::SharedPtr<System::Object>)">SetTextInputValue()</see> method.
    /// 
    /// For a text form field the <see cref="Aspose::Words::Fields::FormField::get_TextInputDefault">TextInputDefault</see> value is applied
    /// if @a value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Result();
    /// Setter for Aspose::Words::Fields::FormField::get_Result
    ASPOSE_WORDS_SHARED_API void set_Result(const System::String& value);
    /// Returns or sets the text that's displayed in the status bar when a form field has the focus.
    /// 
    /// If the <see cref="Aspose::Words::Fields::FormField::get_OwnStatus">OwnStatus</see> property is set to <c>%true</c>, the <see cref="Aspose::Words::Fields::FormField::get_StatusText">StatusText</see> property specifies the status bar text.
    /// If the <see cref="Aspose::Words::Fields::FormField::get_OwnStatus">OwnStatus</see> property is set to <c>%false</c>, the <see cref="Aspose::Words::Fields::FormField::get_StatusText">StatusText</see> property specifies the name of an AutoText
    /// entry that contains status bar text for the form field.
    /// 
    /// %Microsoft Word allows strings with at most 138 characters.
    ASPOSE_WORDS_SHARED_API System::String get_StatusText();
    /// Setter for Aspose::Words::Fields::FormField::get_StatusText
    ASPOSE_WORDS_SHARED_API void set_StatusText(const System::String& value);
    /// Specifies the source of the text that's displayed in the status bar when a form field has the focus.
    /// 
    /// If <c>%true</c>, the text specified by the <see cref="Aspose::Words::Fields::FormField::get_StatusText">StatusText</see> property is displayed.
    /// If <c>%false</c>, the text of the AutoText entry specified by the <see cref="Aspose::Words::Fields::FormField::get_StatusText">StatusText</see> property is displayed.
    ASPOSE_WORDS_SHARED_API bool get_OwnStatus();
    /// Setter for Aspose::Words::Fields::FormField::get_OwnStatus
    ASPOSE_WORDS_SHARED_API void set_OwnStatus(bool value);
    /// Returns or sets the text that's displayed in a message box when the form field has the focus and the user presses F1.
    /// 
    /// If the <see cref="Aspose::Words::Fields::FormField::get_OwnHelp">OwnHelp</see> property is set to <c>%true</c>, <see cref="Aspose::Words::Fields::FormField::get_HelpText">HelpText</see> specifies the text string value.
    /// If <see cref="Aspose::Words::Fields::FormField::get_OwnHelp">OwnHelp</see> is set to <c>%false</c>, <see cref="Aspose::Words::Fields::FormField::get_HelpText">HelpText</see> specifies the name of an AutoText entry that contains help
    /// text for the form field.
    /// 
    /// %Microsoft Word allows strings with at most 255 characters.
    ASPOSE_WORDS_SHARED_API System::String get_HelpText();
    /// Setter for Aspose::Words::Fields::FormField::get_HelpText
    ASPOSE_WORDS_SHARED_API void set_HelpText(const System::String& value);
    /// Specifies the source of the text that's displayed in a message box when a form field has the focus and the user presses F1.
    /// 
    /// If <c>%true</c>, the text specified by the <see cref="Aspose::Words::Fields::FormField::get_HelpText">HelpText</see> property is displayed.
    /// If <c>%false</c>, the text in the AutoText entry specified by the <see cref="Aspose::Words::Fields::FormField::get_HelpText">HelpText</see> property is displayed.
    ASPOSE_WORDS_SHARED_API bool get_OwnHelp();
    /// Setter for Aspose::Words::Fields::FormField::get_OwnHelp
    ASPOSE_WORDS_SHARED_API void set_OwnHelp(bool value);
    /// True if references to the specified form field are automatically updated whenever the field is exited.
    /// 
    /// Setting <see cref="Aspose::Words::Fields::FormField::get_CalculateOnExit">CalculateOnExit</see> only affects the behavior of the form field when
    /// the document is opened in %Microsoft Word. %Aspose.Words never updates references
    /// to the form field.
    ASPOSE_WORDS_SHARED_API bool get_CalculateOnExit();
    /// Setter for Aspose::Words::Fields::FormField::get_CalculateOnExit
    ASPOSE_WORDS_SHARED_API void set_CalculateOnExit(bool value);
    /// Returns or sets an entry macro name for the form field.
    /// 
    /// The entry macro runs when the form field gets the focus in %Microsoft Word.
    /// 
    /// %Microsoft Word allows strings with at most 32 characters.
    ASPOSE_WORDS_SHARED_API System::String get_EntryMacro();
    /// Setter for Aspose::Words::Fields::FormField::get_EntryMacro
    ASPOSE_WORDS_SHARED_API void set_EntryMacro(const System::String& value);
    /// Returns or sets an exit macro name for the form field.
    /// 
    /// The exit macro runs when the form field loses the focus in %Microsoft Word.
    /// 
    /// %Microsoft Word allows strings with at most 32 characters.
    ASPOSE_WORDS_SHARED_API System::String get_ExitMacro();
    /// Setter for Aspose::Words::Fields::FormField::get_ExitMacro
    ASPOSE_WORDS_SHARED_API void set_ExitMacro(const System::String& value);
    /// True if a form field is enabled.
    /// 
    /// If a form field is enabled, its contents can be changed as the form is filled in.
    ASPOSE_WORDS_SHARED_API bool get_Enabled();
    /// True if a form field is enabled.
    /// 
    /// If a form field is enabled, its contents can be changed as the form is filled in.
    ASPOSE_WORDS_SHARED_API void set_Enabled(bool value);
    /// Returns or sets the text formatting for a text form field.
    /// 
    /// If the text form field contains regular text, then valid format strings are
    /// "", "UPPERCASE", "LOWERCASE", "FIRST CAPITAL" and "TITLE CASE". The strings
    /// are case-insensitive.
    /// 
    /// If the text form field contains a number or a date/time value, then valid
    /// format strings are number or date and time format strings.
    /// 
    /// %Microsoft Word allows strings with at most 64 characters.
    ASPOSE_WORDS_SHARED_API System::String get_TextInputFormat();
    /// Setter for Aspose::Words::Fields::FormField::get_TextInputFormat
    ASPOSE_WORDS_SHARED_API void set_TextInputFormat(const System::String& value);
    /// Gets the type of a text form field.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::TextFormFieldType get_TextInputType();
    /// Sets the type of a text form field.
    ASPOSE_WORDS_SHARED_API void set_TextInputType(Aspose::Words::Fields::TextFormFieldType value);
    /// Gets or sets the default string or a calculation expression of a text form field.
    /// 
    /// The meaning of this property depends on the value of the <see cref="Aspose::Words::Fields::FormField::get_TextInputType">TextInputType</see> property.
    /// 
    /// When <see cref="Aspose::Words::Fields::FormField::get_TextInputType">TextInputType</see> is <see cref="Aspose::Words::Fields::TextFormFieldType::Regular">Regular</see> or
    /// <see cref="Aspose::Words::Fields::TextFormFieldType::Number">Number</see>, this string specifies the default string for the text form field.
    /// This string is the content that %Microsoft Word will display in the document when the form field is empty.
    /// 
    /// When <see cref="Aspose::Words::Fields::FormField::get_TextInputType">TextInputType</see> is <see cref="Aspose::Words::Fields::TextFormFieldType::Calculated">Calculated</see>, then this string holds
    /// the expression to be calculated. The expression needs to be a formula valid according to %Microsoft Word formula field
    /// requirements. When you set a new expression using this property, %Aspose.Words calculates the formula result
    /// automatically and inserts it into the form field.
    /// 
    /// %Microsoft Word allows strings with at most 255 characters.
    ASPOSE_WORDS_SHARED_API System::String get_TextInputDefault();
    /// Setter for Aspose::Words::Fields::FormField::get_TextInputDefault
    ASPOSE_WORDS_SHARED_API void set_TextInputDefault(const System::String& value);
    /// Maximum length for the text field. Zero when the length is not limited.
    ASPOSE_WORDS_SHARED_API int32_t get_MaxLength();
    /// Maximum length for the text field. Zero when the length is not limited.
    ASPOSE_WORDS_SHARED_API void set_MaxLength(int32_t value);
    /// Provides access to the items of a dropdown form field.
    /// 
    /// %Microsoft Word allows maximum 25 items in a dropdown form field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::DropDownItemCollection> get_DropDownItems();
    /// Gets the index specifying the currently selected item in a dropdown form field.
    ASPOSE_WORDS_SHARED_API int32_t get_DropDownSelectedIndex();
    /// Sets the index specifying the currently selected item in a dropdown form field.
    ASPOSE_WORDS_SHARED_API void set_DropDownSelectedIndex(int32_t value);
    /// Gets or sets the checked status of the check box form field.
    /// Default value for this property is <c>%false</c>.
    /// 
    /// Applicable for a check box form field only.
    ASPOSE_WORDS_SHARED_API bool get_Checked();
    /// Setter for Aspose::Words::Fields::FormField::get_Checked
    ASPOSE_WORDS_SHARED_API void set_Checked(bool value);
    /// Gets or sets the default value of the check box form field.
    /// Default value for this property is <c>%false</c>.
    /// 
    /// Applicable for a check box form field only.
    ASPOSE_WORDS_SHARED_API bool get_Default();
    /// Setter for Aspose::Words::Fields::FormField::get_Default
    ASPOSE_WORDS_SHARED_API void set_Default(bool value);
    /// Gets or sets the boolean value that indicates whether the size of the textbox is automatic or specified explicitly.
    /// 
    /// Applicable for a check box form field only.
    /// 
    /// @sa Aspose::Words::Fields::FormField::get_CheckBoxSize
    ASPOSE_WORDS_SHARED_API bool get_IsCheckBoxExactSize();
    /// Setter for Aspose::Words::Fields::FormField::get_IsCheckBoxExactSize
    ASPOSE_WORDS_SHARED_API void set_IsCheckBoxExactSize(bool value);
    /// Gets or sets the size of the checkbox in points. Has effect only when <see cref="Aspose::Words::Fields::FormField::get_IsCheckBoxExactSize">IsCheckBoxExactSize</see> is <c>%true</c>.
    /// 
    /// Applicable for a check box form field only.
    /// 
    /// @sa Aspose::Words::Fields::FormField::get_IsCheckBoxExactSize
    ASPOSE_WORDS_SHARED_API double get_CheckBoxSize();
    /// Setter for Aspose::Words::Fields::FormField::get_CheckBoxSize
    ASPOSE_WORDS_SHARED_API void set_CheckBoxSize(double value);

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitFormField(System::SharedPtr<Aspose::Words::Fields::FormField>)">VisitFormField()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Removes the complete form field, not just the form field special character.
    ASPOSE_WORDS_SHARED_API void RemoveField();
    /// Applies the text format specified in <see cref="Aspose::Words::Fields::FormField::get_TextInputFormat">TextInputFormat</see> and stores the value in <see cref="Aspose::Words::Fields::FormField::get_Result">Result</see>.
    /// 
    /// @param newValue Can be a string, number or a <b>%DateTime</b> object.
    ASPOSE_WORDS_SHARED_API void SetTextInputValue(const System::SharedPtr<System::Object>& newValue);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~FormField();

private:

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<System::Object> mField1;

    void SetRunAttr(int32_t , System::SharedPtr<System::Object> ) override;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
