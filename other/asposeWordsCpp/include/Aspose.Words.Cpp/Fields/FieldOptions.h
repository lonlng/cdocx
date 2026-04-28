//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldOptions.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>

#include <Aspose.Words.Cpp/Fields/FieldUpdateCultureSource.h>
#include <Aspose.Words.Cpp/Fields/FieldIndexFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Fields
{

class IBarcodeGenerator;
class IBibliographyStylesProvider;
class IComparisonExpressionEvaluator;
class IFieldDatabaseProvider;
class IFieldResultFormatter;
class IFieldUpdateCultureProvider;
class IFieldUpdatingCallback;
class IFieldUpdatingProgressCallback;
class IFieldUserPromptRespondent;
class ToaCategories;
class UserInformation;
}
}
}
namespace System
{
namespace Globalization
{
class CultureInfo;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents options to control field handling in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldOptions final : public System::Object
{
    typedef FieldOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies what culture to use to format the field result.
    /// 
    /// By default, the culture of the current thread is used.
    /// 
    /// The setting affects only date/time fields with \\\\\@ format switch.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldUpdateCultureSource get_FieldUpdateCultureSource() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_FieldUpdateCultureSource
    ASPOSE_WORDS_SHARED_API void set_FieldUpdateCultureSource(Aspose::Words::Fields::FieldUpdateCultureSource value);
    /// Gets or sets a provider that returns a culture object specific for each particular field.
    /// 
    /// The provider is requested when the value of <see cref="Aspose::Words::Fields::FieldOptions::get_FieldUpdateCultureSource">FieldUpdateCultureSource</see> is <see cref="Aspose::Words::Fields::FieldUpdateCultureSource::FieldCode">FieldCode</see>.
    /// 
    /// If the provider is present, then the culture object it returns is used for the field update. Otherwise, a system culture is used.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IFieldUpdateCultureProvider>& get_FieldUpdateCultureProvider() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_FieldUpdateCultureProvider
    ASPOSE_WORDS_SHARED_API void set_FieldUpdateCultureProvider(const System::SharedPtr<Aspose::Words::Fields::IFieldUpdateCultureProvider>& value);
    /// Gets or sets the value indicating whether bidirectional text is fully supported during field update or not.
    /// 
    /// When this property is set to <c>%true</c>, additional steps are performed to produce Right-To-Left language
    /// (i.e. Arabic or Hebrew) compatible field result during its update.
    /// 
    /// When this property is set to <c>%false</c> and Right-To-Left language is used, correctness of field result
    /// after its update is not guaranteed.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsBidiTextSupportedOnUpdate() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_IsBidiTextSupportedOnUpdate
    ASPOSE_WORDS_SHARED_API void set_IsBidiTextSupportedOnUpdate(bool value);
    /// Gets or sets the respondent to user prompts during field update.
    /// 
    /// If the value of this property is set to <c>%null</c>, the fields that require user response on prompting
    /// (such as <see cref="Aspose::Words::Fields::FieldAsk">FieldAsk</see> or <see cref="Aspose::Words::Fields::FieldFillIn">FieldFillIn</see>) are not updated.
    /// 
    /// The default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IFieldUserPromptRespondent>& get_UserPromptRespondent() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_UserPromptRespondent
    ASPOSE_WORDS_SHARED_API void set_UserPromptRespondent(const System::SharedPtr<Aspose::Words::Fields::IFieldUserPromptRespondent>& value);
    /// Gets the field comparison expressions evaluator.
    /// 
    /// @sa Aspose::Words::Fields::IComparisonExpressionEvaluator
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IComparisonExpressionEvaluator>& get_ComparisonExpressionEvaluator() const;
    /// Sets the field comparison expressions evaluator.
    /// 
    /// @sa Aspose::Words::Fields::IComparisonExpressionEvaluator
    ASPOSE_WORDS_SHARED_API void set_ComparisonExpressionEvaluator(const System::SharedPtr<Aspose::Words::Fields::IComparisonExpressionEvaluator>& value);
    /// Gets default document author's name. If author's name is already specified in built-in document properties,
    /// this option is not considered.
    ASPOSE_WORDS_SHARED_API System::String get_DefaultDocumentAuthor() const;
    /// Sets default document author's name. If author's name is already specified in built-in document properties,
    /// this option is not considered.
    ASPOSE_WORDS_SHARED_API void set_DefaultDocumentAuthor(const System::String& value);
    /// Gets custom style separator for the \\t switch in <see cref="Aspose::Words::Fields::FieldToc">FieldToc</see> field.
    ASPOSE_WORDS_SHARED_API System::String get_CustomTocStyleSeparator() const;
    /// Sets custom style separator for the \\t switch in <see cref="Aspose::Words::Fields::FieldToc">FieldToc</see> field.
    ASPOSE_WORDS_SHARED_API void set_CustomTocStyleSeparator(const System::String& value);
    /// Gets or sets the value indicating whether legacy (early than AW 13.10) number format for fields is enabled or not.
    /// 
    /// When this property is set to <c>%true</c>, template symbol "#" worked as in .net:
    /// Replaces the pound sign with the corresponding digit if one is present; otherwise, no symbols appears in the result string.
    /// 
    /// When this property is set to <c>%false</c>, template symbol "#" works as MS Word:
    /// This format item specifies the requisite numeric places to display in the result.
    /// If the result does not include a digit in that place, MS Word displays a space. For example, { = 9 + 6 \\\# \$\#\#\# } displays \$ 15.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_LegacyNumberFormat() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_LegacyNumberFormat
    ASPOSE_WORDS_SHARED_API void set_LegacyNumberFormat(bool value);
    /// Gets or sets the value indicating that number format is parsed using invariant culture or not
    /// 
    /// When this property is set to <c>%true</c>, number format is taken from an invariant culture.
    /// 
    /// When this property is set to <c>%false</c>, number format is taken from the current thread's culture.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseInvariantCultureNumberFormat() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_UseInvariantCultureNumberFormat
    ASPOSE_WORDS_SHARED_API void set_UseInvariantCultureNumberFormat(bool value);
    /// Gets or set custom barcode generator.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IBarcodeGenerator>& get_BarcodeGenerator() const;
    /// Gets or set custom barcode generator.
    ASPOSE_WORDS_SHARED_API void set_BarcodeGenerator(const System::SharedPtr<Aspose::Words::Fields::IBarcodeGenerator>& value);
    /// Gets a provider that returns a query result for the <see cref="Aspose::Words::Fields::FieldDatabase">FieldDatabase</see> field.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IFieldDatabaseProvider>& get_FieldDatabaseProvider() const;
    /// Sets a provider that returns a query result for the <see cref="Aspose::Words::Fields::FieldDatabase">FieldDatabase</see> field.
    ASPOSE_WORDS_SHARED_API void set_FieldDatabaseProvider(const System::SharedPtr<Aspose::Words::Fields::IFieldDatabaseProvider>& value);
    /// Gets a provider that returns a bibliography style for
    /// the <see cref="Aspose::Words::Fields::FieldBibliography">FieldBibliography</see> and <see cref="Aspose::Words::Fields::FieldCitation">FieldCitation</see> fields.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IBibliographyStylesProvider>& get_BibliographyStylesProvider() const;
    /// Sets a provider that returns a bibliography style for
    /// the <see cref="Aspose::Words::Fields::FieldBibliography">FieldBibliography</see> and <see cref="Aspose::Words::Fields::FieldCitation">FieldCitation</see> fields.
    ASPOSE_WORDS_SHARED_API void set_BibliographyStylesProvider(const System::SharedPtr<Aspose::Words::Fields::IBibliographyStylesProvider>& value);
    /// Gets or sets the culture to preprocess field values.
    /// 
    /// Currently this property only affects value of the <see cref="Aspose::Words::Fields::FieldDocProperty">FieldDocProperty</see> field.
    /// 
    /// The default value is <c>%null</c>. When this property is set to <c>%null</c>, the <see cref="Aspose::Words::Fields::FieldDocProperty">FieldDocProperty</see> field's value is preprocessed
    /// with the culture controlled by the <see cref="Aspose::Words::Fields::FieldOptions::get_FieldUpdateCultureSource">FieldUpdateCultureSource</see> property.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Globalization::CultureInfo>& get_PreProcessCulture() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_PreProcessCulture
    ASPOSE_WORDS_SHARED_API void set_PreProcessCulture(const System::SharedPtr<System::Globalization::CultureInfo>& value);
    /// Gets the current user information.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::UserInformation>& get_CurrentUser() const;
    /// Sets the current user information.
    ASPOSE_WORDS_SHARED_API void set_CurrentUser(const System::SharedPtr<Aspose::Words::Fields::UserInformation>& value);
    /// Gets the table of authorities categories.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::ToaCategories>& get_ToaCategories() const;
    /// Sets the table of authorities categories.
    ASPOSE_WORDS_SHARED_API void set_ToaCategories(const System::SharedPtr<Aspose::Words::Fields::ToaCategories>& value);
    /// Gets a <see cref="Aspose::Words::Fields::FieldOptions::get_FieldIndexFormat">FieldIndexFormat</see> that represents
    /// the formatting for the <see cref="Aspose::Words::Fields::FieldIndex">FieldIndex</see> fields in the document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldIndexFormat get_FieldIndexFormat();
    /// Sets a <see cref="Aspose::Words::Fields::FieldOptions::get_FieldIndexFormat">FieldIndexFormat</see> that represents
    /// the formatting for the <see cref="Aspose::Words::Fields::FieldIndex">FieldIndex</see> fields in the document.
    ASPOSE_WORDS_SHARED_API void set_FieldIndexFormat(Aspose::Words::Fields::FieldIndexFormat value);
    /// Gets the file name of the document.
    /// 
    /// This property is used by the <see cref="Aspose::Words::Fields::FieldFileName">FieldFileName</see> field with higher priority than the <see cref="Aspose::Words::Document::get_OriginalFileName">OriginalFileName</see> property.
    ASPOSE_WORDS_SHARED_API System::String get_FileName() const;
    /// Sets the file name of the document.
    /// 
    /// This property is used by the <see cref="Aspose::Words::Fields::FieldFileName">FieldFileName</see> field with higher priority than the <see cref="Aspose::Words::Document::get_OriginalFileName">OriginalFileName</see> property.
    ASPOSE_WORDS_SHARED_API void set_FileName(const System::String& value);
    /// Gets or sets the file name of the template used by the document.
    /// 
    /// This property is used by the <see cref="Aspose::Words::Fields::FieldTemplate">FieldTemplate</see> field if the <see cref="Aspose::Words::Document::get_AttachedTemplate">AttachedTemplate</see> property is empty.
    /// 
    /// If this property is empty, the default template file name <c>%Normal.dotm</c> is used.
    ASPOSE_WORDS_SHARED_API System::String get_TemplateName() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_TemplateName
    ASPOSE_WORDS_SHARED_API void set_TemplateName(const System::String& value);
    /// Allows to control how the field result is formatted.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IFieldResultFormatter>& get_ResultFormatter() const;
    /// Allows to control how the field result is formatted.
    ASPOSE_WORDS_SHARED_API void set_ResultFormatter(const System::SharedPtr<Aspose::Words::Fields::IFieldResultFormatter>& value);
    /// Gets or sets paths of MS Word built-in templates.
    /// 
    /// This property is used by the <see cref="Aspose::Words::Fields::FieldAutoText">FieldAutoText</see> and <see cref="Aspose::Words::Fields::FieldGlossary">FieldGlossary</see> fields, if referenced auto text entry is not found in the <see cref="Aspose::Words::Document::get_AttachedTemplate">AttachedTemplate</see> template.
    /// 
    /// By default MS Word stores built-in templates in c:\\Users\\\<username\>\\AppData\\Roaming\\Microsoft\\Document Building Blocks\\1033\\16\\Built-In Building Blocks.dotx and
    /// C:\\Users\\\<username\>\\AppData\\Roaming\\Microsoft\\Templates\\Normal.dotm files.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> get_BuiltInTemplatesPaths() const;
    /// Setter for Aspose::Words::Fields::FieldOptions::get_BuiltInTemplatesPaths
    ASPOSE_WORDS_SHARED_API void set_BuiltInTemplatesPaths(const System::ArrayPtr<System::String>& value);
    /// Gets <see cref="Aspose::Words::Fields::IFieldUpdatingCallback">IFieldUpdatingCallback</see> implementation
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IFieldUpdatingCallback>& get_FieldUpdatingCallback() const;
    /// Sets <see cref="Aspose::Words::Fields::IFieldUpdatingCallback">IFieldUpdatingCallback</see> implementation
    ASPOSE_WORDS_SHARED_API void set_FieldUpdatingCallback(const System::SharedPtr<Aspose::Words::Fields::IFieldUpdatingCallback>& value);
    /// Gets <see cref="Aspose::Words::Fields::IFieldUpdatingProgressCallback">IFieldUpdatingProgressCallback</see> implementation.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::IFieldUpdatingProgressCallback>& get_FieldUpdatingProgressCallback() const;
    /// Sets <see cref="Aspose::Words::Fields::IFieldUpdatingProgressCallback">IFieldUpdatingProgressCallback</see> implementation.
    ASPOSE_WORDS_SHARED_API void set_FieldUpdatingProgressCallback(const System::SharedPtr<Aspose::Words::Fields::IFieldUpdatingProgressCallback>& value);

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::String mField5;
    System::String mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    System::SharedPtr<System::Object> mField11;
    System::SharedPtr<System::Object> mField12;
    System::SharedPtr<System::Object> mField13;
    System::SharedPtr<System::Object> mField14;
    System::String mField15;
    System::String mField16;
    System::SharedPtr<System::Object> mField17;
    System::SharedPtr<System::Object> mField18;
    System::SharedPtr<System::Object> mField19;
    System::SharedPtr<System::Object> mField20;
    System::WeakPtr<System::Object> mField21;

};

}
}
}
