//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Replacing/FindReplaceOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Replacing/ReplacementFormat.h>
#include <Aspose.Words.Cpp/Replacing/FindReplaceDirection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Font;
class ParagraphFormat;

namespace Replacing
{

class IReplacingCallback;
}

}
}

namespace Aspose {

namespace Words {

namespace Replacing {

/// Specifies options for find/replace operations.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/find-and-replace/">Find and Replace</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FindReplaceOptions : public System::Object
{
    typedef FindReplaceOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Text formatting applied to new content.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_ApplyFont() const;
    /// Paragraph formatting applied to new content.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ParagraphFormat> get_ApplyParagraphFormat() const;
    /// Selects direction for replace. Default value is <see cref="Aspose::Words::Replacing::FindReplaceDirection::Forward">Forward</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Replacing::FindReplaceDirection get_Direction() const;
    /// Selects direction for replace. Default value is <see cref="Aspose::Words::Replacing::FindReplaceDirection::Forward">Forward</see>.
    ASPOSE_WORDS_SHARED_API void set_Direction(Aspose::Words::Replacing::FindReplaceDirection value);
    /// True indicates case-sensitive comparison, false indicates case-insensitive comparison.
    ASPOSE_WORDS_SHARED_API bool get_MatchCase() const;
    /// True indicates case-sensitive comparison, false indicates case-insensitive comparison.
    ASPOSE_WORDS_SHARED_API void set_MatchCase(bool value);
    /// True indicates the oldValue must be a standalone word.
    ASPOSE_WORDS_SHARED_API bool get_FindWholeWordsOnly() const;
    /// True indicates the oldValue must be a standalone word.
    ASPOSE_WORDS_SHARED_API void set_FindWholeWordsOnly(bool value);
    /// The user-defined method which is called before every replace occurrence.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Replacing::IReplacingCallback> get_ReplacingCallback() const;
    /// The user-defined method which is called before every replace occurrence.
    ASPOSE_WORDS_SHARED_API void set_ReplacingCallback(const System::SharedPtr<Aspose::Words::Replacing::IReplacingCallback>& value);
    /// True indicates that a text search is performed sequentially from top to bottom considering the text boxes.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseLegacyOrder() const;
    /// True indicates that a text search is performed sequentially from top to bottom considering the text boxes.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_UseLegacyOrder(bool value);
    /// Gets a boolean value indicating either to ignore text inside delete revisions.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreDeleted() const;
    /// Sets a boolean value indicating either to ignore text inside delete revisions.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnoreDeleted(bool value);
    /// Gets a boolean value indicating either to ignore text inside insert revisions.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreInserted() const;
    /// Sets a boolean value indicating either to ignore text inside insert revisions.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnoreInserted(bool value);
    /// Gets or sets a boolean value indicating either to ignore text inside fields.
    /// The default value is <c>%false</c>.
    /// 
    /// This option affects whole field (all nodes between
    /// <see cref="Aspose::Words::NodeType::FieldStart">FieldStart</see> and <see cref="Aspose::Words::NodeType::FieldEnd">FieldEnd</see>).
    /// 
    /// To ignore only field codes, please use corresponding option <see cref="Aspose::Words::Replacing::FindReplaceOptions::get_IgnoreFieldCodes">IgnoreFieldCodes</see>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreFields() const;
    /// Setter for Aspose::Words::Replacing::FindReplaceOptions::get_IgnoreFields
    ASPOSE_WORDS_SHARED_API void set_IgnoreFields(bool value);
    /// Gets or sets a boolean value indicating either to ignore text inside field codes.
    /// The default value is <c>%false</c>.
    /// 
    /// This option affects only field codes (it does not ignore nodes between
    /// <see cref="Aspose::Words::NodeType::FieldSeparator">FieldSeparator</see> and <see cref="Aspose::Words::NodeType::FieldEnd">FieldEnd</see>).
    /// 
    /// To ignore whole field, please use corresponding option <see cref="Aspose::Words::Replacing::FindReplaceOptions::get_IgnoreFields">IgnoreFields</see>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreFieldCodes() const;
    /// Setter for Aspose::Words::Replacing::FindReplaceOptions::get_IgnoreFieldCodes
    ASPOSE_WORDS_SHARED_API void set_IgnoreFieldCodes(bool value);
    /// Gets a boolean value indicating either to ignore footnotes.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreFootnotes() const;
    /// Sets a boolean value indicating either to ignore footnotes.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnoreFootnotes(bool value);
    /// Gets a boolean value indicating whether to recognize and use substitutions within replacement patterns.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseSubstitutions() const;
    /// Sets a boolean value indicating whether to recognize and use substitutions within replacement patterns.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_UseSubstitutions(bool value);
    /// Gets a boolean value indicating that old find/replace algorithm is used.
    ASPOSE_WORDS_SHARED_API bool get_LegacyMode() const;
    /// Sets a boolean value indicating that old find/replace algorithm is used.
    ASPOSE_WORDS_SHARED_API void set_LegacyMode(bool value);
    /// Gets or sets a boolean value indicating either to ignore content of <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see>.
    /// The default value is <c>%false</c>.
    /// 
    /// When this option is set to <c>%true</c>, the content of <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see>
    /// will be treated as a simple text.
    /// 
    /// Otherwise, <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see> will be processed as standalone Story
    /// and replacing pattern will be searched separately for each <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see>,
    /// so that if pattern crosses a <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see>, then replacement will not
    /// be performed for such pattern.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreStructuredDocumentTags() const;
    /// Setter for Aspose::Words::Replacing::FindReplaceOptions::get_IgnoreStructuredDocumentTags
    ASPOSE_WORDS_SHARED_API void set_IgnoreStructuredDocumentTags(bool value);
    /// Gets a boolean value indicating either it is allowed to replace paragraph break
    /// when there is no next sibling paragraph.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_SmartParagraphBreakReplacement() const;
    /// Sets a boolean value indicating either it is allowed to replace paragraph break
    /// when there is no next sibling paragraph.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_SmartParagraphBreakReplacement(bool value);
    /// Gets a boolean value indicating either to ignore shapes within a text.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreShapes() const;
    /// Sets a boolean value indicating either to ignore shapes within a text.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnoreShapes(bool value);
    /// Specifies format of the replacement. Default is <see cref="Aspose::Words::Replacing::ReplacementFormat::Text">Text</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Replacing::ReplacementFormat get_ReplacementFormat() const;
    /// Specifies format of the replacement. Default is <see cref="Aspose::Words::Replacing::ReplacementFormat::Text">Text</see>.
    ASPOSE_WORDS_SHARED_API void set_ReplacementFormat(Aspose::Words::Replacing::ReplacementFormat value);
    /// Gets a boolean value indicating either to ignore text inside OfficeMath/\>.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreOfficeMath() const;
    /// Sets a boolean value indicating either to ignore text inside OfficeMath/\>.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnoreOfficeMath(bool value);

    /// Initializes a new instance of the FindReplaceOptions class with default settings.
    ASPOSE_WORDS_SHARED_API FindReplaceOptions();
    /// Initializes a new instance of the FindReplaceOptions class with the specified direction.
    /// 
    /// @param direction The direction of the find and replace operation.
    ASPOSE_WORDS_SHARED_API FindReplaceOptions(Aspose::Words::Replacing::FindReplaceDirection direction);
    /// Initializes a new instance of the FindReplaceOptions class with the specified replacing callback.
    /// 
    /// @param replacingCallback The callback to use for replacing found text.
    ASPOSE_WORDS_SHARED_API FindReplaceOptions(const System::SharedPtr<Aspose::Words::Replacing::IReplacingCallback>& replacingCallback);
    /// Initializes a new instance of the FindReplaceOptions class with the specified direction and replacing callback.
    /// 
    /// @param direction The direction of the find and replace operation.
    /// @param replacingCallback The callback to use for replacing found text.
    ASPOSE_WORDS_SHARED_API FindReplaceOptions(Aspose::Words::Replacing::FindReplaceDirection direction, const System::SharedPtr<Aspose::Words::Replacing::IReplacingCallback>& replacingCallback);

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;
    __TypeStub<1,1,1,1>::type mField10;
    __TypeStub<1,1,1,1>::type mField11;
    System::SharedPtr<System::Object> mField12;
    __TypeStub<1,1,1,1>::type mField13;
    __TypeStub<1,1,1,1>::type mField14;
    __TypeStub<1,1,1,1>::type mField15;
    __TypeStub<1,1,1,1>::type mField16;
    __TypeStub<1,1,1,1>::type mField17;
    __TypeStub<1,1,1,1>::type mField18;
    __TypeStub<1,1,1,1>::type mField19;
    __TypeStub<1,1,1,1>::type mField20;

};

}
}
}
