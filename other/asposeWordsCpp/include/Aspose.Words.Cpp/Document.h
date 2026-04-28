//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Document.h
#pragma once

#include <system/io/std_stream_wrappers.h>
#include <system/date_time.h>
#include <system/array.h>
#include <mutex>
#include <memory>
#include <iostream>

#include <Aspose.Words.Cpp/Settings/JustificationMode.h>
#include <Aspose.Words.Cpp/Saving/OoxmlCompliance.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/ImportFormatMode.h>
#include <Aspose.Words.Cpp/ISectionAttrSource.h>
#include <Aspose.Words.Cpp/IWatermarkProvider.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/RevisionsView.h>
#include <Aspose.Words.Cpp/ProtectionType.h>
#include <Aspose.Words.Cpp/LoadFormat.h>
#include <Aspose.Words.Cpp/DocumentBase.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Bibliography
{
class Bibliography;
}
namespace BuildingBlocks
{
class GlossaryDocument;
}
class CleanupOptions;
namespace Comparing
{

class CompareOptions;

}
namespace DigitalSignatures
{
class DigitalSignatureCollection;

}
class DocumentBase;

class DocumentRenderingContext;
class DocumentVisitor;
namespace Drawing
{

class Shape;
class ShapeBase;
}
namespace Fields
{

class FieldOptions;

}

namespace Fonts
{
class DocumentFontProvider;

class FontSettings;
}

namespace Framesets
{
class Frameset;
}
class ImportFormatOptions;

class INodeCloningListener;

namespace Layout
{

class LayoutOptions;

}
namespace Licensing
{
void Venture(const System::SharedPtr<System::Object>&, bool, const uint8_t*, const size_t);

}
namespace Loading
{
class IResourceLoadingCallback;
class LoadOptions;
}

namespace MailMerging
{
class MailMerge;

}

namespace Markup
{
class CustomPartCollection;
class CustomXmlPartCollection;

}

class Node;

namespace Notes
{
class EndnoteOptions;
class FootnoteOptions;
}

class PageExtractOptions;

namespace Properties
{
class BuiltInDocumentProperties;
class CustomDocumentProperties;
}

namespace Rendering
{

class PageInfo;
class ThumbnailGeneratingOptions;
}

class RevisionCollection;
namespace Revisions
{

class RevisionTrackingUtil;
}

namespace Saving
{

class SaveOptions;
class SaveOutputParameters;

}
class Section;
class SectionCollection;
namespace Settings
{
class CompatibilityOptions;

class HyphenationOptions;
class MailMergeSettings;
class ViewOptions;
class WriteProtection;
}
class StyleCollection;
enum class SuspendedRevisionTypes;

namespace Themes
{
class Theme;

}

class VariableCollection;
namespace Vba
{
class VbaProject;
}

class Watermark;
namespace WebExtensions
{
class TaskPaneCollection;
}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class IList;
template <typename> class List;
}
}
namespace Drawing
{
class Graphics;
class SizeF;
}
namespace IO
{
class MemoryStream;
class Stream;
}
namespace Web
{
class HttpResponse;
}
}

namespace Aspose {

namespace Words {

/// Represents a Word document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-document/">Working with Document</a> documentation article.
/// 
/// The <see cref="Aspose::Words::Document">Document</see> is a central object in the %Aspose.Words library.
/// 
/// To load an existing document in any of the <see cref="Aspose::Words::LoadFormat">LoadFormat</see> formats, pass a file name
/// or a stream into one of the <see cref="Aspose::Words::Document">Document</see> constructors. To create a blank document, call the
/// constructor without parameters.
/// 
/// Use one of the Save method overloads to save the document in any of the
/// <see cref="Aspose::Words::SaveFormat">SaveFormat</see> formats.
/// 
/// To draw document pages directly onto a <b>%Graphics</b> object use
/// <see cref="Aspose::Words::Document::RenderToScale(int32_t, System::SharedPtr<System::Drawing::Graphics>, float, float, float)">RenderToScale()</see> or <see cref="Aspose::Words::Document::RenderToSize(int32_t, System::SharedPtr<System::Drawing::Graphics>, float, float, float, float)">RenderToSize()</see> method.
/// 
/// To print the document, use one of the <see cref="Aspose::Words::Document::Print(System::String)">Print()</see> methods.
/// 
/// <see cref="Aspose::Words::Document::get_MailMerge">MailMerge</see> is the Aspose.Words's reporting engine that allows to populate
/// reports designed in %Microsoft Word with data from various data sources quickly and easily.
/// The data can be from a  or an array of values.
/// <b>%MailMerge</b> will go through the records found in the data source and insert them into
/// mail merge fields in the document growing it as necessary.
/// 
/// <see cref="Aspose::Words::Document">Document</see> stores document-wide information such as <see cref="Aspose::Words::DocumentBase::get_Styles">Styles</see>,
/// <see cref="Aspose::Words::Document::get_BuiltInDocumentProperties">BuiltInDocumentProperties</see>, <see cref="Aspose::Words::Document::get_CustomDocumentProperties">CustomDocumentProperties</see>, lists and macros.
/// Most of these objects are accessible via the corresponding properties of the <see cref="Aspose::Words::Document">Document</see>.
/// 
/// The <see cref="Aspose::Words::Document">Document</see> is a root node of a tree that contains all other nodes of the document.
/// The tree is a Composite design pattern and in many ways similar to XmlDocument.
/// The content of the document can be manipulated freely programmatically:
/// 
/// - The nodes of the document can be accessed via typed collections, for example <see cref="Aspose::Words::Document::get_Sections">Sections</see>,
///   <see cref="Aspose::Words::ParagraphCollection">ParagraphCollection</see> etc.
/// - The nodes of the document can be selected by their node type using
///   <see cref="Aspose::Words::CompositeNode::GetChildNodes(Aspose::Words::NodeType, bool)">GetChildNodes()</see>
///   or using an XPath query with <see cref="Aspose::Words::CompositeNode::SelectNodes(System::String)">SelectNodes()</see> or <see cref="Aspose::Words::CompositeNode::SelectSingleNode(System::String)">SelectSingleNode()</see>.
/// - Content nodes can be added or removed from anywhere in the document using
///   <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>, <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see>,
///   <see cref="Aspose::Words::CompositeNode::RemoveChild``1(System::SharedPtr<``0>)">RemoveChild``1()</see> and other
///   methods provided by the base class <see cref="Aspose::Words::CompositeNode">CompositeNode</see>.
/// - The formatting attributes of each node can be changed via the properties of that node.
/// 
/// Consider using <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see> that simplifies the task of programmatically creating
/// or populating the document tree.
/// 
/// The <see cref="Aspose::Words::Document">Document</see> can contain only <see cref="Aspose::Words::Section">Section</see> objects.
/// 
/// In %Microsoft Word, a valid document needs to have at least one section.
class ASPOSE_WORDS_SHARED_CLASS Document : public Aspose::Words::DocumentBase, public Aspose::Words::ISectionAttrSource, public Aspose::Words::IWatermarkProvider
{
    typedef Document ThisType;
    typedef Aspose::Words::DocumentBase BaseType;
    typedef Aspose::Words::ISectionAttrSource BaseType1;
    typedef Aspose::Words::IWatermarkProvider BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::DocumentBase::Clone;

public:

    /// Gets or sets the full path of the template attached to the document.
    /// 
    /// Empty string means the document is attached to the Normal template.
    /// 
    /// @exception System::ArgumentNullException Throws if you attempt to set to a <c>%null</c> value.
    /// 
    /// @sa Aspose::Words::Properties::BuiltInDocumentProperties::get_Template
    ASPOSE_WORDS_SHARED_API System::String get_AttachedTemplate();
    /// Setter for Aspose::Words::Document::get_AttachedTemplate
    ASPOSE_WORDS_SHARED_API void set_AttachedTemplate(const System::String& value);
    /// Gets a flag indicating whether the styles in the document are updated to match the styles in the
    /// attached template each time the document is opened in MS Word.
    ASPOSE_WORDS_SHARED_API bool get_AutomaticallyUpdateStyles();
    /// Sets a flag indicating whether the styles in the document are updated to match the styles in the
    /// attached template each time the document is opened in MS Word.
    ASPOSE_WORDS_SHARED_API void set_AutomaticallyUpdateStyles(bool value);
    /// Specifies whether to turn on the gray shading on form fields.
    ASPOSE_WORDS_SHARED_API bool get_ShadeFormData();
    /// Specifies whether to turn on the gray shading on form fields.
    ASPOSE_WORDS_SHARED_API void set_ShadeFormData(bool value);
    /// True if changes are tracked when this document is edited in %Microsoft Word.
    /// 
    /// Setting this option only instructs %Microsoft Word whether the track changes
    /// is turned on or off. This property has no effect on changes to the document that you make
    /// programmatically via %Aspose.Words.
    /// 
    /// If you want to automatically track changes as they are made programmatically by Aspose.Words
    /// to this document use the <see cref="Aspose::Words::Document::StartTrackRevisions(System::String, System::DateTime)">StartTrackRevisions()</see> method.
    ASPOSE_WORDS_SHARED_API bool get_TrackRevisions();
    /// Setter for Aspose::Words::Document::get_TrackRevisions
    ASPOSE_WORDS_SHARED_API void set_TrackRevisions(bool value);
    /// Specifies whether to display grammar errors in this document.
    ASPOSE_WORDS_SHARED_API bool get_ShowGrammaticalErrors();
    /// Specifies whether to display grammar errors in this document.
    ASPOSE_WORDS_SHARED_API void set_ShowGrammaticalErrors(bool value);
    /// Specifies whether to display spelling errors in this document.
    ASPOSE_WORDS_SHARED_API bool get_ShowSpellingErrors();
    /// Specifies whether to display spelling errors in this document.
    ASPOSE_WORDS_SHARED_API void set_ShowSpellingErrors(bool value);
    /// Returns <c>%true</c> if the document has been checked for spelling.
    ASPOSE_WORDS_SHARED_API bool get_SpellingChecked();
    /// Returns <c>%true</c> if the document has been checked for spelling.
    ASPOSE_WORDS_SHARED_API void set_SpellingChecked(bool value);
    /// Returns <c>%true</c> if the document has been checked for grammar.
    ASPOSE_WORDS_SHARED_API bool get_GrammarChecked();
    /// Returns <c>%true</c> if the document has been checked for grammar.
    ASPOSE_WORDS_SHARED_API void set_GrammarChecked(bool value);
    /// Specifies whether kerning applies to both Latin text and punctuation.
    ASPOSE_WORDS_SHARED_API bool get_PunctuationKerning();
    /// Specifies whether kerning applies to both Latin text and punctuation.
    ASPOSE_WORDS_SHARED_API void set_PunctuationKerning(bool value);
    /// Returns <see cref="Aspose::Words::NodeType::Document">Document</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns a collection that represents all the built-in document properties of the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::BuiltInDocumentProperties> get_BuiltInDocumentProperties() const;
    /// Returns a collection that represents a list of task pane add-ins.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::WebExtensions::TaskPaneCollection> get_WebExtensionTaskPanes() const;
    /// Returns a collection that represents all the custom document properties of the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::CustomDocumentProperties> get_CustomDocumentProperties();
    /// Returns a <see cref="Aspose::Words::MailMerging::MailMerge">MailMerge</see> object that represents the mail merge functionality for the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::MailMerging::MailMerge> get_MailMerge();
    /// Gets the currently active document protection type.
    /// 
    /// This property allows to retrieve the currently set document protection type.
    /// To change the document protection type use the <see cref="Aspose::Words::Document::Protect(Aspose::Words::ProtectionType, System::String)">Protect()</see>
    /// and <see cref="Aspose::Words::Document::Unprotect">Unprotect</see> methods.
    /// 
    /// When a document is protected, the user can make only limited changes,
    /// such as adding annotations, making revisions, or completing a form.
    /// 
    /// Note that document protection is different from write protection.
    /// Write protection is specified using the <see cref="Aspose::Words::Document::get_WriteProtection">WriteProtection</see>
    /// 
    /// @sa Aspose::Words::Document::Protect(Aspose::Words::ProtectionType, System::String)
    /// @sa Aspose::Words::Document::Unprotect
    /// @sa Aspose::Words::Document::get_WriteProtection
    ASPOSE_WORDS_SHARED_API Aspose::Words::ProtectionType get_ProtectionType();
    /// Returns a collection that represents all sections in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::SectionCollection> get_Sections();
    /// Gets the first section in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_FirstSection();
    /// Gets the last section in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_LastSection();
    /// Provides options to control how the document is displayed in %Microsoft Word.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::ViewOptions> get_ViewOptions();
    /// Provides access to the document write protection options.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::WriteProtection> get_WriteProtection();
    /// Provides access to document compatibility options (that is, the user preferences entered on the <b>%Compatibility</b>
    /// tab of the <b>%Options</b> dialog in Word).
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::CompatibilityOptions> get_CompatibilityOptions();
    /// Gets or sets the object that contains all of the mail merge information for a document.
    /// 
    /// You can use this object to specify a mail merge data source for a document and this information
    /// (along with the available data fields) will appear in %Microsoft Word when the user opens this document.
    /// Or you can use this object to query mail merge settings that the user has specified in %Microsoft Word
    /// for this document.
    /// 
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::MailMergeSettings> get_MailMergeSettings();
    /// Setter for Aspose::Words::Document::get_MailMergeSettings
    ASPOSE_WORDS_SHARED_API void set_MailMergeSettings(const System::SharedPtr<Aspose::Words::Settings::MailMergeSettings>& value);
    /// Provides access to document hyphenation options.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::HyphenationOptions> get_HyphenationOptions();
    /// Returns <c>%true</c> if the document has any tracked changes.
    ASPOSE_WORDS_SHARED_API bool get_HasRevisions();
    /// Returns <c>%true</c> if the document has a VBA project (macros).
    /// 
    /// @sa Aspose::Words::Document::RemoveMacros
    ASPOSE_WORDS_SHARED_API bool get_HasMacros();
    /// Provides access to the document watermark.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Watermark> get_Watermark();
    /// Gets the number of document versions that was stored in the DOC document.
    /// 
    /// Versions in %Microsoft Word are accessed via the File/Versions menu. %Microsoft Word supports
    /// versions only for DOC files.
    /// 
    /// This property allows to detect if there were document versions stored in this document
    /// before it was opened in %Aspose.Words. %Aspose.Words provides no other support for document versions.
    /// If you save this document using %Aspose.Words, the document will be saved without versions.
    ASPOSE_WORDS_SHARED_API int32_t get_VersionsCount();
    /// Gets or sets the interval (in points) between the default tab stops.
    /// 
    /// @sa Aspose::Words::TabStopCollection
    /// @sa Aspose::Words::TabStop
    ASPOSE_WORDS_SHARED_API double get_DefaultTabStop();
    /// Setter for Aspose::Words::Document::get_DefaultTabStop
    ASPOSE_WORDS_SHARED_API void set_DefaultTabStop(double value);
    /// Gets the <see cref="Aspose::Words::Document::get_Theme">Theme</see> object for this document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Themes::Theme> get_Theme();
    /// Gets or sets the collection of Custom XML Data Storage Parts.
    /// 
    /// %Aspose.Words loads and saves Custom XML Parts into OOXML and DOC documents only.
    /// 
    /// This property cannot be <c>%null</c>.
    /// 
    /// @sa Aspose::Words::Markup::CustomXmlPart
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPartCollection> get_CustomXmlParts() const;
    /// Setter for Aspose::Words::Document::get_CustomXmlParts
    ASPOSE_WORDS_SHARED_API void set_CustomXmlParts(const System::SharedPtr<Aspose::Words::Markup::CustomXmlPartCollection>& value);
    /// Gets or sets the collection of custom parts (arbitrary content) that are linked to the OOXML package using "unknown relationships".
    /// 
    /// Do not confuse these custom parts with Custom XML Data. If you need to access Custom XML parts,
    /// use the <see cref="Aspose::Words::Document::get_CustomXmlParts">CustomXmlParts</see> property.
    /// 
    /// This collection contains OOXML parts whose parent is the OOXML package and they targets are of an "unknown relationship".
    /// For more information see <see cref="Aspose::Words::Markup::CustomPart">CustomPart</see>.
    /// 
    /// %Aspose.Words loads and saves custom parts into OOXML documents only.
    /// 
    /// This property cannot be <c>%null</c>.
    /// 
    /// @sa Aspose::Words::Markup::CustomPart
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomPartCollection> get_PackageCustomParts() const;
    /// Setter for Aspose::Words::Document::get_PackageCustomParts
    ASPOSE_WORDS_SHARED_API void set_PackageCustomParts(const System::SharedPtr<Aspose::Words::Markup::CustomPartCollection>& value);
    /// Returns the collection of variables added to a document or template.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::VariableCollection> get_Variables();
    /// Gets or sets the glossary document within this document or template. A glossary document is a storage
    /// for AutoText, AutoCorrect and Building Block entries defined in a document.
    /// 
    /// This property returns <c>%null</c> if the document does not have a glossary document.
    /// 
    /// You can add a glossary document to a document by creating a
    /// <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see> object and assigning to this property.
    /// 
    /// @sa Aspose::Words::BuildingBlocks::GlossaryDocument
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument> get_GlossaryDocument() const;
    /// Setter for Aspose::Words::Document::get_GlossaryDocument
    ASPOSE_WORDS_SHARED_API void set_GlossaryDocument(const System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument>& value);
    /// Gets the original file name of the document.
    /// 
    /// Returns <c>%null</c> if the document was loaded from a stream or created blank.
    ASPOSE_WORDS_SHARED_API System::String get_OriginalFileName() const;
    /// Gets the format of the original document that was loaded into this object.
    /// 
    /// If you created a new blank document, returns the <see cref="Aspose::Words::LoadFormat::Doc">Doc</see> value.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LoadFormat get_OriginalLoadFormat() const;
    /// Gets the OOXML compliance version determined from the loaded document content.
    /// Makes sense only for OOXML documents.
    /// 
    /// If you created a new blank document or load non OOXML document
    /// returns the <see cref="Aspose::Words::Saving::OoxmlCompliance::Ecma376_2006">Ecma376_2006</see> value.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::OoxmlCompliance get_Compliance();
    /// Gets the collection of digital signatures for this document and their validation results.
    /// 
    /// This collection contains digital signatures that were loaded from the original document.
    /// These digital signatures will not be saved when you save this <see cref="Aspose::Words::Document">Document</see> object
    /// into a file or stream because saving or converting will produce a document that is different from the
    /// original and the original digital signatures will no longer be valid.
    /// 
    /// This collection is never <c>%null</c>. If the document is not signed, it will contain zero elements.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::DigitalSignatureCollection> get_DigitalSignatures() const;
    /// Gets or sets document font settings.
    /// 
    /// This property allows to specify font settings per document. If set to <c>%null</c>, default static font settings
    /// <see cref="Aspose::Words::Fonts::FontSettings::get_DefaultInstance">DefaultInstance</see> will be used.
    /// 
    /// The default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontSettings> get_FontSettings() const;
    /// Setter for Aspose::Words::Document::get_FontSettings
    ASPOSE_WORDS_SHARED_API void set_FontSettings(const System::SharedPtr<Aspose::Words::Fonts::FontSettings>& value);
    /// Gets the <see cref="Aspose::Words::Document::get_Bibliography">Bibliography</see> object that represents the list of sources available in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Bibliography> get_Bibliography();
    /// Returns a <see cref="Aspose::Words::Document::get_Frameset">Frameset</see> instance if this document represents a frames page.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Framesets::Frameset> get_Frameset() const;
    /// Specifies whether to include textboxes, footnotes and endnotes in word count statistics.
    ASPOSE_WORDS_SHARED_API bool get_IncludeTextboxesFootnotesEndnotesInStat();
    /// Specifies whether to include textboxes, footnotes and endnotes in word count statistics.
    ASPOSE_WORDS_SHARED_API void set_IncludeTextboxesFootnotesEndnotesInStat(bool value);
    /// Gets the number of pages in the document as calculated by the most recent page layout operation.
    /// 
    /// @sa Aspose::Words::Document::UpdatePageLayout
    ASPOSE_WORDS_SHARED_API int32_t get_PageCount();
    /// Gets a collection of revisions (tracked changes) that exist in this document.
    /// 
    /// The returned collection is a "live" collection, which means if you remove parts of a document that contain
    /// revisions, the deleted revisions will automatically disappear from this collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RevisionCollection> get_Revisions();
    /// Gets a <see cref="Aspose::Words::Layout::LayoutOptions">LayoutOptions</see> object that represents options to control the layout process of this document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Layout::LayoutOptions> get_LayoutOptions() const;
    /// Gets a value indicating whether to work with the original or revised version of a document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::RevisionsView get_RevisionsView() const;
    /// Sets a value indicating whether to work with the original or revised version of a document.
    ASPOSE_WORDS_SHARED_API void set_RevisionsView(Aspose::Words::RevisionsView value);
    /// Gets the character spacing adjustment of a document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::JustificationMode get_JustificationMode();
    /// Sets the character spacing adjustment of a document.
    ASPOSE_WORDS_SHARED_API void set_JustificationMode(Aspose::Words::Settings::JustificationMode value);
    /// Provides options that control numbering and positioning of footnotes in this document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Notes::FootnoteOptions> get_FootnoteOptions();
    /// Provides options that control numbering and positioning of endnotes in this document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Notes::EndnoteOptions> get_EndnoteOptions();
    /// Gets a <see cref="Aspose::Words::Fields::FieldOptions">FieldOptions</see> object that represents options to control field handling in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldOptions> get_FieldOptions();
    /// Gets a flag indicating that %Microsoft Word will remove all user information from comments, revisions and
    /// document properties upon saving the document.
    ASPOSE_WORDS_SHARED_API bool get_RemovePersonalInformation();
    /// Sets a flag indicating that %Microsoft Word will remove all user information from comments, revisions and
    /// document properties upon saving the document.
    ASPOSE_WORDS_SHARED_API void set_RemovePersonalInformation(bool value);
    /// Gets a <see cref="Aspose::Words::Document::get_VbaProject">VbaProject</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Vba::VbaProject> get_VbaProject() const;
    /// Sets a <see cref="Aspose::Words::Document::get_VbaProject">VbaProject</see>.
    ASPOSE_WORDS_SHARED_API void set_VbaProject(const System::SharedPtr<Aspose::Words::Vba::VbaProject>& value);

    /// Creates a blank Word document.
    /// 
    /// A blank document is retrieved from resources, and by default, the resulting document looks more like created by <see cref="Aspose::Words::Settings::MsWordVersion::Word2007">Word2007</see>.
    /// This blank document contains a default fonts table, minimal default styles, and latent styles.
    /// 
    /// <see cref="Aspose::Words::Settings::CompatibilityOptions::OptimizeFor(Aspose::Words::Settings::MsWordVersion)">OptimizeFor()</see> method can be used to optimize the document contents as well as default %Aspose.Words behavior to a particular version of MS Word.
    /// 
    /// The document paper size is Letter by default. If you want to change page setup, use
    /// <see cref="Aspose::Words::Section::get_PageSetup">PageSetup</see>.
    /// 
    /// After creation, you can use <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see> to add document content easily.
    ASPOSE_WORDS_SHARED_API Document();
    /// Opens an existing document from a file. Automatically detects the file format.
    /// 
    /// @param fileName File name of the document to open.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentException The name of the file cannot be null or empty string.
    ASPOSE_WORDS_SHARED_API Document(const System::String& fileName);
    /// Opens an existing document from a file. Allows to specify additional options such as an encryption password.
    /// 
    /// @param fileName File name of the document to open.
    /// @param loadOptions Additional options to use when loading a document. Can be <c>%null</c>.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentException The name of the file cannot be null or empty string.
    ASPOSE_WORDS_SHARED_API Document(const System::String& fileName, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);
    /// Opens an existing document from a stream. Automatically detects the file format.
    /// 
    /// The document must be stored at the beginning of the stream. The stream must support random positioning.
    /// 
    /// @param stream Stream where to load the document from.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentNullException The stream cannot be null.
    /// @exception System::NotSupportedException The stream does not support reading or seeking.
    /// @exception System::ObjectDisposedException The stream is a disposed object.
    ASPOSE_WORDS_SHARED_API Document(const System::SharedPtr<System::IO::Stream>& stream);
    /// Opens an existing document from a stream. Allows to specify additional options such as an encryption password.
    /// 
    /// The document must be stored at the beginning of the stream. The stream must support random positioning.
    /// 
    /// @param stream The stream where to load the document from.
    /// @param loadOptions Additional options to use when loading a document. Can be <c>%null</c>.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentNullException The stream cannot be null.
    /// @exception System::NotSupportedException The stream does not support reading or seeking.
    /// @exception System::ObjectDisposedException The stream is a disposed object.
    ASPOSE_WORDS_SHARED_API Document(const System::SharedPtr<System::IO::Stream>& stream, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);

    /// Performs a deep copy of the <see cref="Aspose::Words::Document">Document</see>.
    /// 
    /// @return The cloned document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Clone();
    /// Accepts a visitor.
    /// 
    /// Enumerates over this node and all of its children. Each node calls a corresponding method on <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the nodes.
    /// 
    /// @return True if all nodes were visited; false if <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> stopped the operation before visiting all nodes.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the start of the document.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the document.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Appends the specified document to the end of this document.
    /// 
    /// @param srcDoc The document to append.
    /// @param importFormatMode Specifies how to merge style formatting that clashes.
    ASPOSE_WORDS_SHARED_API void AppendDocument(const System::SharedPtr<Aspose::Words::Document>& srcDoc, Aspose::Words::ImportFormatMode importFormatMode);
    /// Appends the specified document to the end of this document.
    /// 
    /// @param srcDoc The document to append.
    /// @param importFormatMode Specifies how to merge style formatting that clashes.
    /// @param importFormatOptions Allows to specify options that affect formatting of a result document.
    ASPOSE_WORDS_SHARED_API void AppendDocument(const System::SharedPtr<Aspose::Words::Document>& srcDoc, Aspose::Words::ImportFormatMode importFormatMode, const System::SharedPtr<Aspose::Words::ImportFormatOptions>& importFormatOptions);
    /// Saves the document to a file. Automatically determines the save format from the extension.
    /// 
    /// @param fileName The name for the document. If a document with the
    ///     specified file name already exists, the existing document is overwritten.
    /// 
    /// @return Additional information that you can optionally use.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(const System::String& fileName);
    /// Saves the document to a file in the specified format.
    /// 
    /// @param fileName The name for the document. If a document with the
    ///     specified file name already exists, the existing document is overwritten.
    /// @param saveFormat The format in which to save the document.
    /// 
    /// @return Additional information that you can optionally use.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(const System::String& fileName, Aspose::Words::SaveFormat saveFormat);
    /// Saves the document to a file using the specified save options.
    /// 
    /// @param fileName The name for the document. If a document with the
    ///     specified file name already exists, the existing document is overwritten.
    /// @param saveOptions Specifies the options that control how the document is saved. Can be <c>%null</c>.
    /// 
    /// @return Additional information that you can optionally use.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(const System::String& fileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Saves the document to a stream using the specified format.
    /// 
    /// @param stream Stream where to save the document.
    /// @param saveFormat The format in which to save the document.
    /// 
    /// @return Additional information that you can optionally use.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(const System::SharedPtr<System::IO::Stream>& stream, Aspose::Words::SaveFormat saveFormat);
    /// Saves the document to a stream using the specified save options.
    /// 
    /// @param stream Stream where to save the document.
    /// @param saveOptions Specifies the options that control how the document is saved. Can be <c>%null</c>.
    ///     If this is <c>%null</c>, the document will be saved in the binary DOC format.
    /// 
    /// @return Additional information that you can optionally use.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(const System::SharedPtr<System::IO::Stream>& stream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// If the document contains no sections, creates one section with one paragraph.
    ASPOSE_WORDS_SHARED_API void EnsureMinimum();
    /// Accepts all tracked changes in the document.
    ASPOSE_WORDS_SHARED_API void AcceptAllRevisions();
    /// Protects the document from changes without changing the existing password or assigns a random password.
    /// 
    /// When a document is protected, the user can make only limited changes,
    /// such as adding annotations, making revisions, or completing a form.
    /// 
    /// When you protect a document, and the document already has a protection password,
    /// the existing protection password is not changed.
    /// 
    /// When you protect a document, and the document does not have a protection password,
    /// this method assigns a random password that makes it impossible to unprotect the document
    /// in %Microsoft Word, but you still can unprotect the document in %Aspose.Words as it does not
    /// require a password when unprotecting.
    /// 
    /// @param type Specifies the protection type for the document.
    ASPOSE_WORDS_SHARED_API void Protect(Aspose::Words::ProtectionType type);
    /// Protects the document from changes and optionally sets a protection password.
    /// 
    /// When a document is protected, the user can make only limited changes,
    /// such as adding annotations, making revisions, or completing a form.
    /// 
    /// Note that document protection is different from write protection.
    /// Write protection is specified using the <see cref="Aspose::Words::Document::get_WriteProtection">WriteProtection</see>.
    /// 
    /// @param type Specifies the protection type for the document.
    /// @param password The password to protect the document with.
    ///     Specify <c>%null</c> or empty string if you want to protect the document without a password.
    ASPOSE_WORDS_SHARED_API void Protect(Aspose::Words::ProtectionType type, const System::String& password);
    /// Removes protection from the document regardless of the password.
    /// 
    /// This method unprotects the document even if it has a protection password.
    /// 
    /// Note that document protection is different from write protection.
    /// Write protection is specified using the <see cref="Aspose::Words::Document::get_WriteProtection">WriteProtection</see>.
    ASPOSE_WORDS_SHARED_API void Unprotect();
    /// Removes protection from the document if a correct password is specified.
    /// 
    /// This method unprotects the document only if a correct password is specified.
    /// 
    /// Note that document protection is different from write protection.
    /// Write protection is specified using the <see cref="Aspose::Words::Document::get_WriteProtection">WriteProtection</see>.
    /// 
    /// @param password The password to unprotect the document with.
    /// 
    /// @return <c>%true</c> if a correct password was specified and the document was unprotected.
    ASPOSE_WORDS_SHARED_API bool Unprotect(const System::String& password);
    /// Updates word count properties of the document.
    /// 
    /// <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see> recalculates and updates Characters, Words and Paragraphs
    /// properties in the <see cref="Aspose::Words::Document::get_BuiltInDocumentProperties">BuiltInDocumentProperties</see> collection of the <see cref="Aspose::Words::Document">Document</see>.
    /// 
    /// Note that <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see> does not update number of lines and pages properties.
    /// Use the <see cref="Aspose::Words::Document::UpdateWordCount">UpdateWordCount</see> overload and pass <c>%true</c> value as a parameter to do that.
    /// 
    /// When you use an evaluation version, the evaluation watermark will also be included
    /// in the word count.
    ASPOSE_WORDS_SHARED_API void UpdateWordCount();
    /// Updates word count properties of the document, optionally updates <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_Lines">Lines</see> property.
    /// 
    /// @param updateLinesCount <c>%true</c> if number of lines in the document shall be calculated.
    ASPOSE_WORDS_SHARED_API void UpdateWordCount(bool updateLinesCount);
    /// Implements an earlier approach to table column widths re-calculation that has known issues.
    [[deprecated("Obsolete, column widths are re-calculated automatically before saving.")]]
    ASPOSE_WORDS_SHARED_API void UpdateTableLayout();
    /// Updates list labels for all list items in the document.
    /// 
    /// This method updates list label properties such as <see cref="Aspose::Words::Lists::ListLabel::get_LabelValue">LabelValue</see> and
    /// <see cref="Aspose::Words::Lists::ListLabel::get_LabelString">LabelString</see> for each <see cref="Aspose::Words::Paragraph::get_ListLabel">ListLabel</see> object in the document.
    /// 
    /// Also, this method is sometimes implicitly called when updating fields in the document. This is required
    /// because some fields that may reference list numbers (such as TOC or REF) need them be up-to-date.
    ASPOSE_WORDS_SHARED_API void UpdateListLabels();
    /// Updates the <see cref="Aspose::Words::Notes::Footnote::get_ActualReferenceMark">ActualReferenceMark</see> property of all footnotes and endnotes in the document.
    ASPOSE_WORDS_SHARED_API void UpdateActualReferenceMarks();
    /// Removes all macros (the VBA project) as well as toolbars and command customizations from the document.
    /// 
    /// By removing all macros from a document you can ensure the document contains no macro viruses.
    ASPOSE_WORDS_SHARED_API void RemoveMacros();
    /// Updates the values of fields in the whole document.
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
    /// Use the <see cref="Aspose::Words::Document::NormalizeFieldTypes">NormalizeFieldTypes</see> method before fields updating if there were document changes that affected field types.
    /// 
    /// To update fields in a specific part of the document use <see cref="Aspose::Words::Range::UpdateFields">UpdateFields</see>.
    ASPOSE_WORDS_SHARED_API void UpdateFields();
    /// Unlinks fields in the whole document.
    /// 
    /// Replaces all the fields in the whole document with their most recent results.
    /// 
    /// To unlink fields in a specific part of the document use <see cref="Aspose::Words::Range::UnlinkFields">UnlinkFields</see>.
    ASPOSE_WORDS_SHARED_API void UnlinkFields();
    /// Changes field type values <see cref="Aspose::Words::Fields::FieldChar::get_FieldType">FieldType</see> of <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see>, <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see>, <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see>
    /// in the whole document so that they correspond to the field types contained in the field codes.
    /// 
    /// Use this method after document changes that affect field types.
    /// 
    /// To change field type values in a specific part of the document use <see cref="Aspose::Words::Range::NormalizeFieldTypes">NormalizeFieldTypes</see>.
    ASPOSE_WORDS_SHARED_API void NormalizeFieldTypes();
    /// Joins runs with same formatting in all paragraphs of the document.
    /// 
    /// This is an optimization method. Some documents contain adjacent runs with same formatting.
    /// Usually this occurs if a document was intensively edited manually.
    /// You can reduce the document size and speed up further processing by joining these runs.
    /// 
    /// The operation checks every <see cref="Aspose::Words::Paragraph">Paragraph</see> node in the document for adjacent <see cref="Aspose::Words::Run">Run</see>
    /// nodes having identical properties. It ignores unique identifiers used to track editing sessions of run
    /// creation and modification. First run in every joining sequence accumulates all text. Remaining
    /// runs are deleted from the document.
    /// 
    /// @return Number of joins performed. When <b>%N</b> adjacent runs are being joined they count as <b>%N - 1</b> joins.
    ASPOSE_WORDS_SHARED_API int32_t JoinRunsWithSameFormatting();
    /// Converts formatting specified in table styles into direct formatting on tables in the document.
    /// 
    /// This method exists because this version of %Aspose.Words provides only limited support for
    /// table styles (see below). This method might be useful when you load a DOCX or WordprocessingML
    /// document that contains tables formatted with table styles and you need to query formatting of
    /// tables, cells, paragraphs or text.
    /// 
    /// This version of %Aspose.Words provides limited support for table styles as follows:
    /// 
    /// - Table styles defined in DOCX or WordprocessingML documents are preserved as table styles
    ///   when saving the document as DOCX or WordprocessingML.
    /// - Table styles defined in DOCX or WordprocessingML documents are automatically converted
    ///   to direct formatting on tables when saving the document into any other format,
    ///   rendering or printing.
    /// - Table styles defined in DOC documents are preserved as table styles when
    ///   saving the document as DOC only.
    ASPOSE_WORDS_SHARED_API void ExpandTableStylesToDirectFormatting();
    /// Cleans unused styles and lists from the document.
    ASPOSE_WORDS_SHARED_API void Cleanup();
    /// Cleans unused styles and lists from the document depending on given <see cref="Aspose::Words::CleanupOptions">CleanupOptions</see>.
    ASPOSE_WORDS_SHARED_API void Cleanup(const System::SharedPtr<Aspose::Words::CleanupOptions>& options);
    /// Removes external XML schema references from this document.
    ASPOSE_WORDS_SHARED_API void RemoveExternalSchemaReferences();
    /// Starts automatically marking all further changes you make to the document programmatically as revision changes.
    /// 
    /// If you call this method and then make some changes to the document programmatically,
    /// save the document and later open the document in MS Word you will see these changes as revisions.
    /// 
    /// Currently %Aspose.Words supports tracking of node insertions and deletions only. Formatting changes are not
    /// recorded as revisions.
    /// 
    /// Automatic tracking of changes is supported both when modifying this document through node manipulations
    /// as well as when using <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>
    /// 
    /// This method does not change the <see cref="Aspose::Words::Document::get_TrackRevisions">TrackRevisions</see> option and does not use its value
    /// for the purposes of revision tracking.
    /// 
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// 
    /// @sa Aspose::Words::Document::StopTrackRevisions
    ASPOSE_WORDS_SHARED_API void StartTrackRevisions(const System::String& author, System::DateTime dateTime);
    /// Starts automatically marking all further changes you make to the document programmatically as revision changes.
    /// 
    /// If you call this method and then make some changes to the document programmatically,
    /// save the document and later open the document in MS Word you will see these changes as revisions.
    /// 
    /// Currently %Aspose.Words supports tracking of node insertions and deletions only. Formatting changes are not
    /// recorded as revisions.
    /// 
    /// Automatic tracking of changes is supported both when modifying this document through node manipulations
    /// as well as when using <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>
    /// 
    /// This method does not change the <see cref="Aspose::Words::Document::get_TrackRevisions">TrackRevisions</see> option and does not use its value
    /// for the purposes of revision tracking.
    /// 
    /// @param author Initials of the author to use for revisions.
    /// 
    /// @sa Aspose::Words::Document::StopTrackRevisions
    ASPOSE_WORDS_SHARED_API void StartTrackRevisions(const System::String& author);
    /// Stops automatic marking of document changes as revisions.
    /// 
    /// @sa Aspose::Words::Document::StartTrackRevisions(System::String, System::DateTime)
    ASPOSE_WORDS_SHARED_API void StopTrackRevisions();
    /// Compares this document with another document producing changes as number of edit and format revisions <see cref="Aspose::Words::Revision">Revision</see>.
    /// 
    /// @note Documents must not have revisions before comparison.
    /// 
    /// @param document Document to compare.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    ASPOSE_WORDS_SHARED_API void Compare(const System::SharedPtr<Aspose::Words::Document>& document, const System::String& author, System::DateTime dateTime);
    /// Compares this document with another document producing changes as a number of edit and format revisions <see cref="Aspose::Words::Revision">Revision</see>.
    /// Allows to specify comparison options using <see cref="Aspose::Words::Comparing::CompareOptions">CompareOptions</see>.
    ASPOSE_WORDS_SHARED_API void Compare(const System::SharedPtr<Aspose::Words::Document>& document, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& options);
    /// Copies styles from the specified template to a document.
    ASPOSE_WORDS_SHARED_API void CopyStylesFromTemplate(const System::String& template_);
    /// Copies styles from the specified template to a document.
    ASPOSE_WORDS_SHARED_API void CopyStylesFromTemplate(const System::SharedPtr<Aspose::Words::Document>& template_);
    /// Rebuilds the page layout of the document.
    /// 
    /// This method formats a document into pages and updates the page number related fields in the document such
    /// as PAGE, PAGES, PAGEREF and REF. The up-to-date page layout information is required for a correct rendering of the document
    /// to fixed-page formats.
    /// 
    /// This method is automatically invoked when you first convert a document to PDF, XPS, image or print it.
    /// However, if you modify the document after rendering and then attempt to render it again - %Aspose.Words will not
    /// update the page layout automatically. In this case you should call <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see> before
    /// rendering again.
    ASPOSE_WORDS_SHARED_API void UpdatePageLayout();
    /// Renders a document page into a <see cref="System::Drawing::Graphics">Graphics</see> object to a specified scale.
    /// 
    /// @param pageIndex The 0-based page index.
    /// @param graphics The object where to render to.
    /// @param x The X coordinate (in world units) of the top left corner of the rendered page.
    /// @param y The Y coordinate (in world units) of the top left corner of the rendered page.
    /// @param scale The scale for rendering the page (1.0 is 100\%).
    /// 
    /// @return The width and height (in world units) of the rendered page.
    ASPOSE_WORDS_SHARED_API System::Drawing::SizeF RenderToScale(int32_t pageIndex, const System::SharedPtr<System::Drawing::Graphics>& graphics, float x, float y, float scale);
    /// Renders a document page into a <see cref="System::Drawing::Graphics">Graphics</see> object to a specified size.
    /// 
    /// @param pageIndex The 0-based page index.
    /// @param graphics The object where to render to.
    /// @param x The X coordinate (in world units) of the top left corner of the rendered page.
    /// @param y The Y coordinate (in world units) of the top left corner of the rendered page.
    /// @param width The maximum width (in world units) that can be occupied by the rendered page.
    /// @param height The maximum height (in world units) that can be occupied by the rendered page.
    /// 
    /// @return The scale that was automatically calculated for the rendered page to fit the specified size.
    ASPOSE_WORDS_SHARED_API float RenderToSize(int32_t pageIndex, const System::SharedPtr<System::Drawing::Graphics>& graphics, float x, float y, float width, float height);
    /// Gets the page size, orientation and other information about a page that might be useful for printing or rendering.
    /// 
    /// @param pageIndex The 0-based page index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Rendering::PageInfo> GetPageInfo(int32_t pageIndex);
    /// Updates <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_Thumbnail">Thumbnail</see> of the document according to the specified options.
    /// 
    /// @param options The generating options to use.
    ASPOSE_WORDS_SHARED_API void UpdateThumbnail(const System::SharedPtr<Aspose::Words::Rendering::ThumbnailGeneratingOptions>& options);
    /// Updates <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_Thumbnail">Thumbnail</see> of the document using default options.
    ASPOSE_WORDS_SHARED_API void UpdateThumbnail();
    /// Returns the <see cref="Aspose::Words::Document">Document</see> object representing the specified range of pages and the given page extract options.
    /// 
    /// @param index The zero-based index of the first page to extract.
    /// @param count Number of pages to be extracted.
    /// @param options Provides options for managing the page extracting process.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> ExtractPages(int32_t index, int32_t count, const System::SharedPtr<Aspose::Words::PageExtractOptions>& options);
    /// Returns the <see cref="Aspose::Words::Document">Document</see> object representing specified range of pages.
    /// 
    /// @param index The zero-based index of the first page to extract.
    /// @param count Number of pages to be extracted.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> ExtractPages(int32_t index, int32_t count);
    /// Removes blank pages from the document.
    /// 
    /// @return List of page numbers has been considered as blank and removed.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::List<int32_t>> RemoveBlankPages();

    ASPOSE_WORDS_SHARED_API Document(std::istream& stream);
    ASPOSE_WORDS_SHARED_API Document(std::istream& stream, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);

    template <typename CharType, typename Traits>
    System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(std::basic_ostream<CharType, Traits>& stream, Aspose::Words::SaveFormat saveFormat)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        return Save(streamWrapper, saveFormat);
    }

    template <typename CharType, typename Traits>
    System::SharedPtr<Aspose::Words::Saving::SaveOutputParameters> Save(std::basic_ostream<CharType, Traits>& stream, System::SharedPtr<Aspose::Words::Saving::SaveOptions> saveOptions)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        return Save(streamWrapper, saveOptions);
    }

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::DocumentFontProvider> get_FontProvider() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentRenderingContext> get_RenderingContext() override;

    ASPOSE_WORDS_SHARED_API bool get_IsTrackRevisionsEnabled() override;
    ASPOSE_WORDS_SHARED_API bool get_IsMoveRevisionsTracked() override;

    __TypeStub<8,8,8,8>::type mField0;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Themes::Theme> GetThemeInternal() override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    virtual ASPOSE_WORDS_SHARED_API void WriteDocToHttResponse(System::SharedPtr<System::Web::HttpResponse> , System::ArrayPtr<uint8_t> , int32_t , System::String , System::String );

    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    ASPOSE_WORDS_SHARED_API void SuspendTrackRevisions(Aspose::Words::SuspendedRevisionTypes ) override;
    ASPOSE_WORDS_SHARED_API void ResumeTrackRevisions(Aspose::Words::SuspendedRevisionTypes ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Document();

private:

    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    System::SharedPtr<System::Object> mField11;
    System::SharedPtr<System::Object> mField12;
    System::SharedPtr<System::Object> mField13;
    System::SharedPtr<System::Object> mField14;
    System::SharedPtr<System::Object> mField15;
    System::SharedPtr<System::Object> mField16;
    __TypeStub<4,4,4,4>::type mField17;
    System::SharedPtr<System::Object> mField18;
    System::String mField19;
    System::String mField20;
    __TypeStub<4,4,4,4>::type mField21;
    System::String mField22;
    System::SharedPtr<System::Object> mField23;
    System::SharedPtr<System::Object> mField24;
    System::SharedPtr<System::Object> mField25;
    System::SharedPtr<System::Object> mField26;
    System::SharedPtr<System::Object> mField27;
    System::SharedPtr<System::Object> mField28;
    System::SharedPtr<System::Object> mField29;
    System::SharedPtr<System::Object> mField30;
    System::SharedPtr<System::Object> mField31;
    System::SharedPtr<System::Object> mField32;
    System::SharedPtr<System::Object> mField33;
    System::SharedPtr<System::Object> mField34;
    __TypeStub<4,4,4,4>::type mField35;
    System::SharedPtr<System::Object> mField36;
    System::SharedPtr<System::Object> mField37;
    __TypeStub<1,1,1,1>::type mField38;
    __TypeStub<4,4,4,4>::type mField39;
    __TypeStub<4,4,4,4>::type mField40;
    System::SharedPtr<System::Object> mField41;
    System::DateTime mField42;
    System::SharedPtr<System::Object> mField43;
    System::SharedPtr<System::Object> mField44;
    __TypeStub<4,4,4,4>::type mField45;
    System::SharedPtr<System::Object> mField46;
    System::SharedPtr<System::Object> mField47;
    System::SharedPtr<System::Object> mField48;
    System::SharedPtr<System::Object> mField49;
    System::SharedPtr<System::Object> mField50;
    System::SharedPtr<System::Object> mField51;

    void Add(System::SharedPtr<Aspose::Words::Drawing::Shape> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Shape> Get() override;
    void Remove() override;

    System::SharedPtr<System::Object> GetDirectSectionAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectSectionAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedSectionAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchSectionAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchSectionAttr(int32_t , Aspose::Words::RevisionsView ) override;
    void SetSectionAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void SetSectionAttr(int32_t , System::SharedPtr<System::Object> , Aspose::Words::RevisionsView ) override;
    void ClearSectionAttrs() override;
    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

protected:

};

}
}
