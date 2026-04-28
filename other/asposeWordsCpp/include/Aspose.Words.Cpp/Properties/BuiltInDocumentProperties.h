//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Properties/BuiltInDocumentProperties.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>
#include <mutex>
#include <memory>
#include <cstdint>

#include <Aspose.Words.Cpp/Properties/DocumentSecurity.h>
#include <Aspose.Words.Cpp/Properties/DocumentPropertyCollection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Properties
{
class DocumentProperty;
}

}
}
namespace System
{
class DateTime;
}

namespace Aspose {

namespace Words {

namespace Properties {

/// A collection of built-in document properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-document-properties/">Work with Document Properties</a> documentation article.
/// 
/// Provides access to <see cref="Aspose::Words::Properties::DocumentProperty">DocumentProperty</see> objects by their names (using an indexer) and
/// via a set of typed properties that return values of appropriate types.
/// 
/// The names of the properties are case-insensitive.
/// 
/// The properties in the collection are sorted alphabetically by name.
/// 
/// @sa Aspose::Words::Document
/// @sa Aspose::Words::Document::get_BuiltInDocumentProperties
/// @sa Aspose::Words::Document::get_CustomDocumentProperties
class ASPOSE_WORDS_SHARED_CLASS BuiltInDocumentProperties : public Aspose::Words::Properties::DocumentPropertyCollection
{
    typedef BuiltInDocumentProperties ThisType;
    typedef Aspose::Words::Properties::DocumentPropertyCollection BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::Properties::DocumentPropertyCollection::idx_get;

public:

    /// Gets the name of the document's author.
    ASPOSE_WORDS_SHARED_API System::String get_Author();
    /// Sets the name of the document's author.
    ASPOSE_WORDS_SHARED_API void set_Author(const System::String& value);
    /// Represents an estimate of the number of bytes in the document.
    /// 
    /// %Microsoft Word does not always set this property.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API int32_t get_Bytes();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_Bytes
    ASPOSE_WORDS_SHARED_API void set_Bytes(int32_t value);
    /// Represents an estimate of the number of characters in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_Characters();
    /// Represents an estimate of the number of characters in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API void set_Characters(int32_t value);
    /// Represents an estimate of the number of characters (including spaces) in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_CharactersWithSpaces();
    /// Represents an estimate of the number of characters (including spaces) in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API void set_CharactersWithSpaces(int32_t value);
    /// Gets the document comments.
    ASPOSE_WORDS_SHARED_API System::String get_Comments();
    /// Sets the document comments.
    ASPOSE_WORDS_SHARED_API void set_Comments(const System::String& value);
    /// Gets the category of the document.
    ASPOSE_WORDS_SHARED_API System::String get_Category();
    /// Sets the category of the document.
    ASPOSE_WORDS_SHARED_API void set_Category(const System::String& value);
    /// Gets the company property.
    ASPOSE_WORDS_SHARED_API System::String get_Company();
    /// Sets the company property.
    ASPOSE_WORDS_SHARED_API void set_Company(const System::String& value);
    /// Gets or sets date of the document creation in UTC.
    /// 
    /// For documents originated from RTF format this property returns local time of the author's machine at the moment of document creation.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API System::DateTime get_CreatedTime();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_CreatedTime
    ASPOSE_WORDS_SHARED_API void set_CreatedTime(System::DateTime value);
    /// Specifies the base string used for evaluating relative hyperlinks in this document.
    /// 
    /// %Aspose.Words does not use this property.
    ASPOSE_WORDS_SHARED_API System::String get_HyperlinkBase();
    /// Specifies the base string used for evaluating relative hyperlinks in this document.
    /// 
    /// %Aspose.Words does not use this property.
    ASPOSE_WORDS_SHARED_API void set_HyperlinkBase(const System::String& value);
    /// Gets the document keywords.
    ASPOSE_WORDS_SHARED_API System::String get_Keywords();
    /// Sets the document keywords.
    ASPOSE_WORDS_SHARED_API void set_Keywords(const System::String& value);
    /// Gets or sets the date when the document was last printed in UTC.
    /// 
    /// For documents originated from RTF format this property returns the local time of last print operation.
    /// 
    /// If the document was never printed, this property will return DateTime.MinValue.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API System::DateTime get_LastPrinted();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_LastPrinted
    ASPOSE_WORDS_SHARED_API void set_LastPrinted(System::DateTime value);
    /// Gets the name of the last author.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API System::String get_LastSavedBy();
    /// Sets the name of the last author.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API void set_LastSavedBy(const System::String& value);
    /// Gets or sets the time of the last save in UTC.
    /// 
    /// For documents originated from RTF format this property returns the local time of last save operation.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API System::DateTime get_LastSavedTime();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_LastSavedTime
    ASPOSE_WORDS_SHARED_API void set_LastSavedTime(System::DateTime value);
    /// Represents an estimate of the number of lines in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount(bool)">UpdateWordCount()</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_Lines();
    /// Represents an estimate of the number of lines in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount(bool)">UpdateWordCount()</see>.
    ASPOSE_WORDS_SHARED_API void set_Lines(int32_t value);
    /// Indicates whether hyperlinks in a document are up-to-date.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API bool get_LinksUpToDate();
    /// Indicates whether hyperlinks in a document are up-to-date.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API void set_LinksUpToDate(bool value);
    /// Indicates whether document thumbnail is cropped or scaled to fit the display.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API bool get_ScaleCrop();
    /// Indicates whether the document is a shared document.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API bool get_SharedDocument();
    /// Indicates whether hyperlinks in a document were changed.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API bool get_HyperlinksChanged();
    /// Gets the manager property.
    ASPOSE_WORDS_SHARED_API System::String get_Manager();
    /// Sets the manager property.
    ASPOSE_WORDS_SHARED_API void set_Manager(const System::String& value);
    /// Gets the name of the application.
    ASPOSE_WORDS_SHARED_API System::String get_NameOfApplication();
    /// Sets the name of the application.
    ASPOSE_WORDS_SHARED_API void set_NameOfApplication(const System::String& value);
    /// Represents an estimate of the number of pages in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_Pages();
    /// Represents an estimate of the number of pages in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see>.
    ASPOSE_WORDS_SHARED_API void set_Pages(int32_t value);
    /// Represents an estimate of the number of paragraphs in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_Paragraphs();
    /// Represents an estimate of the number of paragraphs in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API void set_Paragraphs(int32_t value);
    /// Gets the document revision number.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API int32_t get_RevisionNumber();
    /// Sets the document revision number.
    /// 
    /// %Aspose.Words does not update this property.
    ASPOSE_WORDS_SHARED_API void set_RevisionNumber(int32_t value);
    /// Specifies the security level of a document as a numeric value.
    /// 
    /// Use this property for informational purposes only because %Microsoft Word does not always
    /// set this property. This property is available in DOC and OOXML documents only.
    /// 
    /// To protect or unprotect a document use the
    /// <see cref="Aspose::Words::Document::Protect(Aspose::Words::ProtectionType, System::String)">Protect()</see> and <see cref="Aspose::Words::Document::Unprotect">Unprotect</see> methods.
    /// 
    /// %Aspose.Words updates this property to a correct value before saving a document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Properties::DocumentSecurity get_Security();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_Security
    ASPOSE_WORDS_SHARED_API void set_Security(Aspose::Words::Properties::DocumentSecurity value);
    /// Gets the subject of the document.
    ASPOSE_WORDS_SHARED_API System::String get_Subject();
    /// Sets the subject of the document.
    ASPOSE_WORDS_SHARED_API void set_Subject(const System::String& value);
    /// Gets or sets the informational name of the document template.
    /// 
    /// In %Microsoft Word, this property is for informational purposes only and
    /// usually contains only the file name of the template without the path.
    /// 
    /// Empty string means the document is attached to the Normal template.
    /// 
    /// To get or set the actual name of the attached template, use the
    /// <see cref="Aspose::Words::Document::get_AttachedTemplate">AttachedTemplate</see> property.
    /// 
    /// @sa Aspose::Words::Document::get_AttachedTemplate
    ASPOSE_WORDS_SHARED_API System::String get_Template();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_Template
    ASPOSE_WORDS_SHARED_API void set_Template(const System::String& value);
    /// Gets or sets the thumbnail of the document.
    /// 
    /// For now this property is used only when a document is being exported to ePub,
    /// it's not read from and written to other document formats.
    /// 
    /// Image of arbitrary format can be set to this property, but the format is checked during export.
    /// 
    /// Only gif, jpeg and png images can be used for ePub publication.
    /// 
    /// @exception System::InvalidOperationException Thrown if the image is invalid or its format is unsupported for specific format of document.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_Thumbnail();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_Thumbnail
    ASPOSE_WORDS_SHARED_API void set_Thumbnail(const System::ArrayPtr<uint8_t>& value);
    /// Gets the title of the document.
    ASPOSE_WORDS_SHARED_API System::String get_Title();
    /// Sets the title of the document.
    ASPOSE_WORDS_SHARED_API void set_Title(const System::String& value);
    /// Gets the total editing time in minutes.
    ASPOSE_WORDS_SHARED_API int32_t get_TotalEditingTime();
    /// Sets the total editing time in minutes.
    ASPOSE_WORDS_SHARED_API void set_TotalEditingTime(int32_t value);
    /// Gets the content type of the document.
    ASPOSE_WORDS_SHARED_API System::String get_ContentType();
    /// Sets the content type of the document.
    ASPOSE_WORDS_SHARED_API void set_ContentType(const System::String& value);
    /// Gets the content status of the document.
    ASPOSE_WORDS_SHARED_API System::String get_ContentStatus();
    /// Sets the content status of the document.
    ASPOSE_WORDS_SHARED_API void set_ContentStatus(const System::String& value);
    /// Represents the version number of the application that created the document.
    /// 
    /// When a document was created by %Microsoft Word, then high 16 bit represent
    /// the major version and low 16 bit represent the build number.
    ASPOSE_WORDS_SHARED_API int32_t get_Version();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_Version
    ASPOSE_WORDS_SHARED_API void set_Version(int32_t value);
    /// Represents an estimate of the number of words in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_Words();
    /// Represents an estimate of the number of words in the document.
    /// 
    /// %Aspose.Words updates this property when you call <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see>.
    ASPOSE_WORDS_SHARED_API void set_Words(int32_t value);
    /// Specifies document headings and their names.
    /// 
    /// Every heading pair occupies two elements in this array.
    /// 
    /// The first element of the pair is a <see cref="System::String">String</see> and specifies the heading name.
    /// The second element of the pair is an <see cref="System::Int32">Int32</see> and specifies the count of document
    /// parts for this heading in the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_TitlesOfParts">TitlesOfParts</see> property.
    /// 
    /// The total sum of counts for all heading pairs in this property must be equal to the
    /// number of elements in the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_TitlesOfParts">TitlesOfParts</see> property.
    /// 
    /// %Aspose.Words does not update this property.
    /// 
    /// @sa Aspose::Words::Properties::BuiltInDocumentProperties::get_TitlesOfParts
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::Object>> get_HeadingPairs();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_HeadingPairs
    ASPOSE_WORDS_SHARED_API void set_HeadingPairs(const System::ArrayPtr<System::SharedPtr<System::Object>>& value);
    /// Each string in the array specifies the name of a part in the document.
    /// 
    /// %Aspose.Words does not update this property.
    /// 
    /// @sa Aspose::Words::Properties::BuiltInDocumentProperties::get_HeadingPairs
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> get_TitlesOfParts();
    /// Setter for Aspose::Words::Properties::BuiltInDocumentProperties::get_TitlesOfParts
    ASPOSE_WORDS_SHARED_API void set_TitlesOfParts(const System::ArrayPtr<System::String>& value);

    /// Returns a <see cref="Aspose::Words::Properties::DocumentProperty">DocumentProperty</see> object by the name of the property.
    /// 
    /// The string names of the properties correspond to the names of the typed
    /// properties available from <see cref="Aspose::Words::Properties::BuiltInDocumentProperties">BuiltInDocumentProperties</see>.
    /// 
    /// If you request a property that is not present in the document, but the name
    /// of the property is recognized as a valid built-in name, a new <see cref="Aspose::Words::Properties::DocumentProperty">DocumentProperty</see>
    /// is created, added to the collection and returned. The newly created property is assigned
    /// a default value (empty string, zero, <c>%false</c> or DateTime.MinValue depending on the type
    /// of the built-in property).
    /// 
    /// If you request a property that is not present in the document and the name
    /// is not recognized as a built-in name, a <c>%null</c> is returned.
    /// 
    /// @param name The case-insensitive name of the property to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::DocumentProperty> idx_get(System::String name) override;

protected:

    System::SharedPtr<System::Object> mField0;

    BuiltInDocumentProperties();

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::DocumentPropertyCollection> Create() override;

    virtual ASPOSE_WORDS_SHARED_API ~BuiltInDocumentProperties();

private:

};

}
}
}
