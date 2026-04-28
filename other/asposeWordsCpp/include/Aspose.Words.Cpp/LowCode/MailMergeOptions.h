//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/MailMergeOptions.h
#pragma once

#include <system/string.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/MailMerging/MailMergeCleanupOptions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace LowCode {

/// Represents options for the mail merge functionality.
class ASPOSE_WORDS_SHARED_CLASS MailMergeOptions : public System::Object
{
    typedef MailMergeOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a mail merge region start tag.
    ASPOSE_WORDS_SHARED_API System::String get_RegionStartTag() const;
    /// Sets a mail merge region start tag.
    ASPOSE_WORDS_SHARED_API void set_RegionStartTag(const System::String& value);
    /// Gets a mail merge region end tag.
    ASPOSE_WORDS_SHARED_API System::String get_RegionEndTag() const;
    /// Sets a mail merge region end tag.
    ASPOSE_WORDS_SHARED_API void set_RegionEndTag(const System::String& value);
    /// Gets a set of flags that specify what items should be removed during mail merge.
    ASPOSE_WORDS_SHARED_API Aspose::Words::MailMerging::MailMergeCleanupOptions get_CleanupOptions() const;
    /// Sets a set of flags that specify what items should be removed during mail merge.
    ASPOSE_WORDS_SHARED_API void set_CleanupOptions(Aspose::Words::MailMerging::MailMergeCleanupOptions value);
    /// Gets or sets a value indicating whether paragraphs with punctuation marks are considered as empty
    /// and should be removed if the <see cref="Aspose::Words::MailMerging::MailMergeCleanupOptions::RemoveEmptyParagraphs">RemoveEmptyParagraphs</see> option is specified.
    /// 
    /// The default value is <c>%true</c>.
    /// Here is the complete list of cleanable punctuation marks:
    /// 
    /// - !
    /// - ,
    /// - .
    /// - :
    /// - ;
    /// - ?
    /// - ¡
    /// - ¿
    ASPOSE_WORDS_SHARED_API bool get_CleanupParagraphsWithPunctuationMarks() const;
    /// Setter for Aspose::Words::LowCode::MailMergeOptions::get_CleanupParagraphsWithPunctuationMarks
    ASPOSE_WORDS_SHARED_API void set_CleanupParagraphsWithPunctuationMarks(bool value);
    /// When <c>%true</c>, specifies that in addition to MERGEFIELD fields, mail merge is performed into some other types of fields and
    /// also into "{{fieldName}}" tags.
    /// 
    /// Normally, mail merge is only performed into MERGEFIELD fields, but several customers had their reporting
    /// built using other fields and had many documents created this way. To simplify migration (and because this
    /// approach was independently used by several customers) the ability to mail merge into other fields was introduced.
    /// 
    /// When <see cref="Aspose::Words::LowCode::MailMergeOptions::get_UseNonMergeFields">UseNonMergeFields</see> is set to <c>%true</c>, %Aspose.Words will perform mail merge into the following fields:
    /// 
    /// MERGEFIELD FieldName
    /// 
    /// MACROBUTTON NOMACRO FieldName
    /// 
    /// IF 0 = 0 "{FieldName}" ""
    /// 
    /// Also, when <see cref="Aspose::Words::LowCode::MailMergeOptions::get_UseNonMergeFields">UseNonMergeFields</see> is set to <c>%true</c>, %Aspose.Words will perform mail merge into text tags
    /// "{{fieldName}}". These are not fields, but just text tags.
    ASPOSE_WORDS_SHARED_API bool get_UseNonMergeFields() const;
    /// Setter for Aspose::Words::LowCode::MailMergeOptions::get_UseNonMergeFields
    ASPOSE_WORDS_SHARED_API void set_UseNonMergeFields(bool value);
    /// Gets a value indicating whether the unused "mustache" tags should be preserved.
    /// 
    /// @sa Aspose::Words::LowCode::MailMergeOptions::get_UseNonMergeFields
    ASPOSE_WORDS_SHARED_API bool get_PreserveUnusedTags() const;
    /// Sets a value indicating whether the unused "mustache" tags should be preserved.
    /// 
    /// @sa Aspose::Words::LowCode::MailMergeOptions::get_UseNonMergeFields
    ASPOSE_WORDS_SHARED_API void set_PreserveUnusedTags(bool value);
    /// Gets a value indicating whether all of the document mail merge regions with the name of a data source
    /// should be merged while executing of a mail merge with regions against the data source or just the first one.
    ASPOSE_WORDS_SHARED_API bool get_MergeDuplicateRegions() const;
    /// Sets a value indicating whether all of the document mail merge regions with the name of a data source
    /// should be merged while executing of a mail merge with regions against the data source or just the first one.
    ASPOSE_WORDS_SHARED_API void set_MergeDuplicateRegions(bool value);
    /// Gets a value indicating whether fields in whole document are updated while executing of a mail merge with regions.
    ASPOSE_WORDS_SHARED_API bool get_MergeWholeDocument() const;
    /// Sets a value indicating whether fields in whole document are updated while executing of a mail merge with regions.
    ASPOSE_WORDS_SHARED_API void set_MergeWholeDocument(bool value);
    /// Gets a value indicating whether whole paragraph with <b>%TableStart</b> or <b>%TableEnd</b> field
    /// or particular range between <b>%TableStart</b> and <b>%TableEnd</b> fields should be included into mail merge region.
    ASPOSE_WORDS_SHARED_API bool get_UseWholeParagraphAsRegion() const;
    /// Sets a value indicating whether whole paragraph with <b>%TableStart</b> or <b>%TableEnd</b> field
    /// or particular range between <b>%TableStart</b> and <b>%TableEnd</b> fields should be included into mail merge region.
    ASPOSE_WORDS_SHARED_API void set_UseWholeParagraphAsRegion(bool value);
    /// Gets a value indicating whether lists are restarted at each section after executing of a mail merge.
    ASPOSE_WORDS_SHARED_API bool get_RestartListsAtEachSection() const;
    /// Sets a value indicating whether lists are restarted at each section after executing of a mail merge.
    ASPOSE_WORDS_SHARED_API void set_RestartListsAtEachSection(bool value);
    /// Gets a value indicating whether trailing and leading whitespaces are trimmed from mail merge values.
    ASPOSE_WORDS_SHARED_API bool get_TrimWhitespaces() const;
    /// Sets a value indicating whether trailing and leading whitespaces are trimmed from mail merge values.
    ASPOSE_WORDS_SHARED_API void set_TrimWhitespaces(bool value);
    /// Gets a value indicating whether merge fields and merge regions are merged regardless of the parent IF field's condition.
    ASPOSE_WORDS_SHARED_API bool get_UnconditionalMergeFieldsAndRegions() const;
    /// Sets a value indicating whether merge fields and merge regions are merged regardless of the parent IF field's condition.
    ASPOSE_WORDS_SHARED_API void set_UnconditionalMergeFieldsAndRegions(bool value);
    /// Gets a value indicating whether the section start of the first document section and its copies for subsequent data source rows
    /// are retained during mail merge or updated according to MS Word behaviour.
    ASPOSE_WORDS_SHARED_API bool get_RetainFirstSectionStart() const;
    /// Sets a value indicating whether the section start of the first document section and its copies for subsequent data source rows
    /// are retained during mail merge or updated according to MS Word behaviour.
    ASPOSE_WORDS_SHARED_API void set_RetainFirstSectionStart(bool value);

    ASPOSE_WORDS_SHARED_API MailMergeOptions();

protected:

private:

    System::String mField0;
    System::String mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    __TypeStub<1,1,1,1>::type mField9;
    __TypeStub<1,1,1,1>::type mField10;
    __TypeStub<1,1,1,1>::type mField11;
    __TypeStub<1,1,1,1>::type mField12;

};

}
}
}
