//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Range.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class BookmarkCollection;
class Document;
namespace Fields
{
class FieldCollection;
class FormFieldCollection;
}
namespace Markup
{
class StructuredDocumentTagCollection;
}
class Node;

namespace Replacing
{
class FindReplaceOptions;
}
class RevisionCollection;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
}
}
class String;
namespace Text
{
namespace RegularExpressions
{
class Regex;
}
}
}

namespace Aspose {

namespace Words {

/// Represents a contiguous area in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-ranges/">Working with Ranges</a> documentation article.
/// 
/// The document is represented by a tree of nodes and the nodes provide operations
/// to work with the tree, but some operations are easier to perform if the document
/// is treated as a contiguous sequence of text.
/// 
/// <see cref="Aspose::Words::Range">Range</see> is a "facade" interface that provide methods that treat the document
/// or portions of the document as "flat" text regardless of the fact that the document
/// nodes are stored in a tree-like object model.
/// 
/// <see cref="Aspose::Words::Range">Range</see> does not contain any text or nodes, it is merely a view or "window"
/// over a fragment of a document.
class ASPOSE_WORDS_SHARED_CLASS Range : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>>
{
    typedef Range ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the text of the range.
    /// 
    /// The returned string includes all control and special characters as described in <see cref="Aspose::Words::ControlChar">ControlChar</see>.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Returns a <see cref="Aspose::Words::Range::get_FormFields">FormFields</see> collection that represents all form fields in the range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FormFieldCollection> get_FormFields();
    /// Returns a <see cref="Aspose::Words::Range::get_Bookmarks">Bookmarks</see> collection that represents all bookmarks in the range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BookmarkCollection> get_Bookmarks();
    /// Returns a <see cref="Aspose::Words::Range::get_Fields">Fields</see> collection that represents all fields in the range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldCollection> get_Fields();
    /// Returns a <see cref="Aspose::Words::Range::get_StructuredDocumentTags">StructuredDocumentTags</see> collection that represents all structured document tags in the range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::StructuredDocumentTagCollection> get_StructuredDocumentTags();
    /// Gets a collection of revisions (tracked changes) that exist in this range.
    /// 
    /// The returned collection is a "live" collection, which means if you remove parts of a document that contain
    /// revisions, the deleted revisions will automatically disappear from this collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RevisionCollection> get_Revisions();

    /// Deletes all characters of the range.
    ASPOSE_WORDS_SHARED_API void Delete();
    /// Replaces all occurrences of a specified character string pattern with a replacement string.
    /// 
    /// The pattern will not be used as regular expression.
    /// Please use <see cref="Aspose::Words::Range::Replace(System::SharedPtr<System::Text::RegularExpressions::Regex>, System::String)">Replace()</see> if you need regular expressions.
    /// 
    /// Used case-insensitive comparison.
    /// 
    /// Method is able to process breaks in both pattern and replacement strings.
    /// 
    /// You should use special meta-characters if you need to work with breaks:
    /// 
    /// - <b>%\&p</b> - paragraph break
    /// - <b>%\&b</b> - section break
    /// - <b>%\&m</b> - page break
    /// - <b>%\&l</b> - manual line break
    /// 
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a character pattern specified by a regular expression with another string.
    /// 
    /// Replaces the whole match captured by the regular expression.
    /// 
    /// Method is able to process breaks in both pattern and replacement strings.
    /// 
    /// You should use special meta-characters if you need to work with breaks:
    /// 
    /// - <b>%\&p</b> - paragraph break
    /// - <b>%\&b</b> - section break
    /// - <b>%\&m</b> - page break
    /// - <b>%\&l</b> - manual line break
    /// 
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string.
    /// 
    /// The pattern will not be used as regular expression.
    /// Please use <see cref="Aspose::Words::Range::Replace(System::SharedPtr<System::Text::RegularExpressions::Regex>, System::String, System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>)">Replace()</see> if you need regular expressions.
    /// 
    /// Method is able to process breaks in both pattern and replacement strings.
    /// 
    /// You should use special meta-characters if you need to work with breaks:
    /// 
    /// - <b>%\&p</b> - paragraph break
    /// - <b>%\&b</b> - section break
    /// - <b>%\&m</b> - page break
    /// - <b>%\&l</b> - manual line break
    /// - <b>%\&\&</b> - \& character
    /// 
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a character pattern specified by a regular expression with another string.
    /// 
    /// Replaces the whole match captured by the regular expression.
    /// 
    /// Method is able to process breaks in both pattern and replacement strings.
    /// 
    /// You should use special meta-characters if you need to work with breaks:
    /// 
    /// - <b>%\&p</b> - paragraph break
    /// - <b>%\&b</b> - section break
    /// - <b>%\&m</b> - page break
    /// - <b>%\&l</b> - manual line break
    /// - <b>%\&\&</b> - \& character
    /// 
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Updates the values of document fields in this range.
    /// 
    /// When you open, modify and then save a document, %Aspose.Words does not update fields automatically, it keeps them intact.
    /// Therefore, you would usually want to call this method before saving if you have modified the document
    /// programmatically and want to make sure the proper (calculated) field values appear in the saved document.
    /// 
    /// There is no need to update fields after executing a mail merge because mail merge is a kind of field update
    /// and automatically updates all fields in the document.
    /// 
    /// This method does not update all field types. For the detailed list of supported field types, see the Programmers Guide.
    /// 
    /// This method does not update fields that are related to the page layout algorithms (e.g. PAGE, PAGES, PAGEREF).
    /// The page layout-related fields are updated when you render a document or call <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see>.
    /// 
    /// To update fields in the whole document use <see cref="Aspose::Words::Document::UpdateFields">UpdateFields</see>.
    ASPOSE_WORDS_SHARED_API void UpdateFields();
    /// Unlinks fields in this range.
    /// 
    /// Replaces all the fields in this range with their most recent results.
    /// 
    /// To unlink fields in the whole document use <see cref="Aspose::Words::Range::UnlinkFields">UnlinkFields</see>.
    ASPOSE_WORDS_SHARED_API void UnlinkFields();
    /// Changes field type values <see cref="Aspose::Words::Fields::FieldChar::get_FieldType">FieldType</see> of <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see>, <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see>, <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see>
    /// in this range so that they correspond to the field types contained in the field codes.
    /// 
    /// Use this method after document changes that affect field types.
    /// 
    /// To change field type values in the whole document use <see cref="Aspose::Words::Document::NormalizeFieldTypes">NormalizeFieldTypes</see>.
    ASPOSE_WORDS_SHARED_API void NormalizeFieldTypes();
    /// Constructs a new fully formed document that contains the range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> ToDocument();
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Range();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;

};

}
}
