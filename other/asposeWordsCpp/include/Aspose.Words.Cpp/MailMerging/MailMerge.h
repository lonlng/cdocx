//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/MailMerge.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/MailMerging/MailMergeCleanupOptions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace MailMerging
{

class IFieldMergingCallback;

class IMailMergeCallback;
class IMailMergeDataSource;

class IMailMergeDataSourceRoot;

class MailMergeRegionInfo;
class MappedDataFieldCollection;

}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class IEnumerable;
template <typename> class IList;
}
}
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// Represents the mail merge functionality.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// For mail merge operation to work, the document should contain Word MERGEFIELD and
/// optionally NEXT fields. During mail merge operation, merge fields in the document are
/// replaced with values from your data source.
/// 
/// There are two distinct ways to use mail merge: with mail merge regions and without.
/// 
/// The simplest mail merge is without regions and it is very similar to how mail merge
/// works in Word. Use <c>%Execute</c> methods to merge information from some
/// data source such as <b>%DataTable</b>, <b>%DataSet</b>
/// or an array of objects into your document. The
/// <see cref="Aspose::Words::MailMerging::MailMerge">MailMerge</see> object processes all records of the data source and copies and appends
/// content of the whole document for each record.
/// 
/// Note that when <see cref="Aspose::Words::MailMerging::MailMerge">MailMerge</see> object encounters a NEXT field, it selects next record
/// in the data source and continues merging without copying any content.
/// 
/// Use <see cref="Aspose::Words::MailMerging::MailMerge::ExecuteWithRegions(System::SharedPtr<Aspose::Words::MailMerging::IMailMergeDataSource>)">ExecuteWithRegions()</see> and other overloads to merge information into a
/// document with mail merge regions defined. You can use
/// as data sources for this operation.
/// 
/// You need to use mail merge regions if you want to dynamically grow portions inside the
/// document. Without mail merge regions whole document will be repeated for every record of
/// the data source.
/// 
/// @sa Aspose::Words::Document
/// @sa Aspose::Words::Document::get_MailMerge
class ASPOSE_WORDS_SHARED_CLASS MailMerge : public System::Object
{
    typedef MailMerge ThisType;
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
    /// Setter for Aspose::Words::MailMerging::MailMerge::get_CleanupParagraphsWithPunctuationMarks
    ASPOSE_WORDS_SHARED_API void set_CleanupParagraphsWithPunctuationMarks(bool value);
    /// When <c>%true</c>, specifies that in addition to MERGEFIELD fields, mail merge is performed into some other types of fields and
    /// also into "{{fieldName}}" tags.
    /// 
    /// Normally, mail merge is only performed into MERGEFIELD fields, but several customers had their reporting
    /// built using other fields and had many documents created this way. To simplify migration (and because this
    /// approach was independently used by several customers) the ability to mail merge into other fields was introduced.
    /// 
    /// When <see cref="Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields">UseNonMergeFields</see> is set to <c>%true</c>, %Aspose.Words will perform mail merge into the following fields:
    /// 
    /// MERGEFIELD FieldName
    /// 
    /// MACROBUTTON NOMACRO FieldName
    /// 
    /// IF 0 = 0 "{FieldName}" ""
    /// 
    /// Also, when <see cref="Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields">UseNonMergeFields</see> is set to <c>%true</c>, %Aspose.Words will perform mail merge into text tags
    /// "{{fieldName}}". These are not fields, but just text tags.
    ASPOSE_WORDS_SHARED_API bool get_UseNonMergeFields() const;
    /// Setter for Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields
    ASPOSE_WORDS_SHARED_API void set_UseNonMergeFields(bool value);
    /// Gets a value indicating whether the unused "mustache" tags should be preserved.
    /// 
    /// @sa Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields
    ASPOSE_WORDS_SHARED_API bool get_PreserveUnusedTags() const;
    /// Sets a value indicating whether the unused "mustache" tags should be preserved.
    /// 
    /// @sa Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields
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
    /// Returns a collection that represents mapped data fields for the mail merge operation.
    /// 
    /// Mapped data fields allow to automatically map between names of fields in your data source
    /// and names of mail merge fields in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::MailMerging::MappedDataFieldCollection> get_MappedDataFields();
    /// Occurs during mail merge when a mail merge field is encountered in the document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::MailMerging::IFieldMergingCallback>& get_FieldMergingCallback() const;
    /// Occurs during mail merge when a mail merge field is encountered in the document.
    ASPOSE_WORDS_SHARED_API void set_FieldMergingCallback(const System::SharedPtr<Aspose::Words::MailMerging::IFieldMergingCallback>& value);
    /// Allows to handle particular events during mail merge.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::MailMerging::IMailMergeCallback>& get_MailMergeCallback() const;
    /// Allows to handle particular events during mail merge.
    ASPOSE_WORDS_SHARED_API void set_MailMergeCallback(const System::SharedPtr<Aspose::Words::MailMerging::IMailMergeCallback>& value);
    /// Gets a value indicating whether trailing and leading whitespaces are trimmed from mail merge values.
    ASPOSE_WORDS_SHARED_API bool get_TrimWhitespaces() const;
    /// Sets a value indicating whether trailing and leading whitespaces are trimmed from mail merge values.
    ASPOSE_WORDS_SHARED_API void set_TrimWhitespaces(bool value);
    /// Gets a value indicating whether merge fields and merge regions are merged regardless of the parent IF field's condition.
    ASPOSE_WORDS_SHARED_API bool get_UnconditionalMergeFieldsAndRegions() const;
    /// Sets a value indicating whether merge fields and merge regions are merged regardless of the parent IF field's condition.
    ASPOSE_WORDS_SHARED_API void set_UnconditionalMergeFieldsAndRegions(bool value);
    /// Gets a value indicating whether the <see cref="Aspose::Words::PageSetup::get_SectionStart">SectionStart</see> of the first document section and its copies for subsequent data source rows
    /// are retained during mail merge or updated according to MS Word behaviour.
    ASPOSE_WORDS_SHARED_API bool get_RetainFirstSectionStart() const;
    /// Sets a value indicating whether the <see cref="Aspose::Words::PageSetup::get_SectionStart">SectionStart</see> of the first document section and its copies for subsequent data source rows
    /// are retained during mail merge or updated according to MS Word behaviour.
    ASPOSE_WORDS_SHARED_API void set_RetainFirstSectionStart(bool value);

    /// Performs a mail merge from a custom data source.
    /// 
    /// Use this method to fill mail merge fields in the document with values from
    /// any data source such as a list or hashtable or objects. You need to write your
    /// own class that implements the <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see> interface.
    /// 
    /// You can use this method only when <see cref="Aspose::Words::Fields::FieldOptions::get_IsBidiTextSupportedOnUpdate">IsBidiTextSupportedOnUpdate</see> is <c>%false</c>,
    /// that is you do not need Right-To-Left language (such as Arabic or Hebrew) compatibility.
    /// 
    /// This method ignores the <see cref="Aspose::Words::MailMerging::MailMergeCleanupOptions::RemoveUnusedRegions">RemoveUnusedRegions</see> option.
    /// 
    /// @param dataSource An object that implements the custom mail merge data source interface.
    ASPOSE_WORDS_SHARED_API void Execute(const System::SharedPtr<Aspose::Words::MailMerging::IMailMergeDataSource>& dataSource);
    /// Performs a mail merge operation for a single record.
    /// 
    /// Use this method to fill mail merge fields in the document with values from
    /// an array of objects.
    /// 
    /// This method merges data for one record only. The array of field names
    /// and the array of values represent the data of a single record.
    /// 
    /// This method does not use mail merge regions.
    /// 
    /// This method ignores the <see cref="Aspose::Words::MailMerging::MailMergeCleanupOptions::RemoveUnusedRegions">RemoveUnusedRegions</see> option.
    /// 
    /// @param fieldNames Array of merge field names. Field names are not case sensitive.
    ///     If a field name that is not found in the document is encountered, it is ignored.
    /// @param values Array of values to be inserted into the merge fields.
    ///     Number of elements in this array must be the same as the number of elements in @a fieldNames.
    ASPOSE_WORDS_SHARED_API void Execute(const System::ArrayPtr<System::String>& fieldNames, const System::ArrayPtr<System::SharedPtr<System::Object>>& values);
    /// Performs a mail merge from a custom data source with mail merge regions.
    /// 
    /// Use this method to fill mail merge fields in the document with values from
    /// any custom data source such as an XML file or collections of business objects. You need to write your
    /// own class that implements the <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see> interface.
    /// 
    /// You can use this method only when <see cref="Aspose::Words::Fields::FieldOptions::get_IsBidiTextSupportedOnUpdate">IsBidiTextSupportedOnUpdate</see> is <c>%false</c>,
    /// that is you do not need Right-To-Left language (such as Arabic or Hebrew) compatibility.
    /// 
    /// @param dataSource An object that implements the custom mail merge data source interface.
    ASPOSE_WORDS_SHARED_API void ExecuteWithRegions(const System::SharedPtr<Aspose::Words::MailMerging::IMailMergeDataSource>& dataSource);
    /// Performs a mail merge from a custom data source with mail merge regions.
    /// 
    /// Use this method to fill mail merge fields in the document with values from
    /// any custom data source such as an XML file or collections of business objects. You need to write your own classes
    /// that implement the <see cref="Aspose::Words::MailMerging::IMailMergeDataSourceRoot">IMailMergeDataSourceRoot</see> and <see cref="Aspose::Words::MailMerging::IMailMergeDataSource">IMailMergeDataSource</see> interfaces.
    /// 
    /// You can use this method only when <see cref="Aspose::Words::Fields::FieldOptions::get_IsBidiTextSupportedOnUpdate">IsBidiTextSupportedOnUpdate</see> is <c>%false</c>,
    /// that is you do not need Right-To-Left language (such as Arabic or Hebrew) compatibility.
    /// 
    /// @param dataSourceRoot An object that implements the custom mail merge data source root interface.
    ASPOSE_WORDS_SHARED_API void ExecuteWithRegions(const System::SharedPtr<Aspose::Words::MailMerging::IMailMergeDataSourceRoot>& dataSourceRoot);
    /// Returns a collection of mail merge field names available in the document.
    /// 
    /// Returns full merge field names including optional prefix. Does not eliminate duplicate field names.
    /// 
    /// A new string array is created on every call.
    /// 
    /// Includes "mustache" field names if <see cref="Aspose::Words::MailMerging::MailMerge::get_UseNonMergeFields">UseNonMergeFields</see> is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> GetFieldNames();
    /// Returns a collection of mail merge field names available in the region.
    /// 
    /// Returns full merge field names including optional prefix. Does not eliminate duplicate field names.
    /// 
    /// If document contains multiple regions with the same name the very first region is processed.
    /// 
    /// A new string array is created on every call.
    /// 
    /// @param regionName Region name (case-insensitive).
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> GetFieldNamesForRegion(const System::String& regionName);
    /// Returns a collection of mail merge field names available in the region.
    /// 
    /// Returns full merge field names including optional prefix. Does not eliminate duplicate field names.
    /// 
    /// If document contains multiple regions with the same name the Nth region (zero-based) is processed.
    /// 
    /// A new string array is created on every call.
    /// 
    /// @param regionName Region name (case-insensitive).
    /// @param regionIndex Region index (zero-based).
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> GetFieldNamesForRegion(const System::String& regionName, int32_t regionIndex);
    /// Returns a collection of mail merge regions with the specified name.
    /// 
    /// @param regionName Region name (case-insensitive).
    /// 
    /// @return The list of regions.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::MailMerging::MailMergeRegionInfo>>> GetRegionsByName(const System::String& regionName);
    /// Returns a full hierarchy of regions (with fields) available in the document.
    /// 
    /// Hierarchy is returned in the form of the <see cref="Aspose::Words::MailMerging::MailMergeRegionInfo">MailMergeRegionInfo</see> class.
    /// 
    /// @return Regions' hierarchy.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::MailMerging::MailMergeRegionInfo> GetRegionsHierarchy();
    /// Removes mail merge related fields from the document.
    /// 
    /// This method removes MERGEFIELD and NEXT fields from the document.
    /// 
    /// This method could be useful if your mail merge operation does not always need
    /// to populate all fields in the document. Use this method to remove all remaining
    /// mail merge fields.
    ASPOSE_WORDS_SHARED_API void DeleteFields();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~MailMerge();

private:

    __TypeStub<1,1,1,1>::type mField0;

    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    __TypeStub<1,1,1,1>::type mField11;
    __TypeStub<1,1,1,1>::type mField12;
    __TypeStub<1,1,1,1>::type mField13;
    System::SharedPtr<System::Object> mField14;

    System::WeakPtr<System::Object> mField15;
    System::SharedPtr<System::Object> mField16;
    __TypeStub<1,1,1,1>::type mField17;
    System::SharedPtr<System::Object> mField18;
    System::SharedPtr<System::Object> mField19;
    System::SharedPtr<System::Object> mField20;
    System::SharedPtr<System::Object> mField21;
    System::String mField22;
    System::String mField23;

};

}
}
}
