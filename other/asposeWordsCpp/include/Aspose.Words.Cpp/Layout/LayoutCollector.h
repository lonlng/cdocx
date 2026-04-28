//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/LayoutCollector.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
class Document;

class Node;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{

template <typename> class List;
}
}
}

namespace Aspose {

namespace Words {

namespace Layout {

/// This class allows to compute page numbers of document nodes.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/converting-to-fixed-page-format/">Converting to Fixed-page Format</a> documentation article.
/// 
/// When you create a <see cref="Aspose::Words::Layout::LayoutCollector">LayoutCollector</see> and specify a <see cref="Aspose::Words::Document">Document</see> document object to attach to,
/// the collector will record mapping of document nodes to layout objects when the document is formatted into pages.
/// 
/// You will be able to find out on which page a particular document node (e.g. run, paragraph or table cell) is located
/// by using the <see cref="Aspose::Words::Layout::LayoutCollector::GetStartPageIndex(System::SharedPtr<Aspose::Words::Node>)">GetStartPageIndex()</see>, <see cref="Aspose::Words::Layout::LayoutCollector::GetEndPageIndex(System::SharedPtr<Aspose::Words::Node>)">GetEndPageIndex()</see> and <see cref="Aspose::Words::Layout::LayoutCollector::GetNumPagesSpanned(System::SharedPtr<Aspose::Words::Node>)">GetNumPagesSpanned()</see> methods.
/// These methods automatically build page layout model of the document and update fields if required.
/// 
/// When you no longer need to collect layout information, it is best to set the <see cref="Aspose::Words::Layout::LayoutCollector::get_Document">Document</see> property to <c>%null</c>
/// to avoid unnecessary collection of more layout mappings.
class ASPOSE_WORDS_SHARED_CLASS LayoutCollector : public System::Object
{
    typedef LayoutCollector ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the document this collector instance is attached to.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document() const;
    /// Sets the document this collector instance is attached to.
    ASPOSE_WORDS_SHARED_API void set_Document(const System::SharedPtr<Aspose::Words::Document>& value);

    /// Initializes an instance of this class.
    /// 
    /// @param doc The document to which this collector instance will be attached to.
    ASPOSE_WORDS_SHARED_API LayoutCollector(const System::SharedPtr<Aspose::Words::Document>& doc);

    /// Gets 1-based index of the page where node begins. Returns 0 if node cannot be mapped to a page.
    ASPOSE_WORDS_SHARED_API int32_t GetStartPageIndex(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Gets 1-based index of the page where node ends. Returns 0 if node cannot be mapped to a page.
    ASPOSE_WORDS_SHARED_API int32_t GetEndPageIndex(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Gets number of pages the specified node spans. 0 if node is within a single page.
    /// This is the same as <see cref="Aspose::Words::Layout::LayoutCollector::GetEndPageIndex(System::SharedPtr<Aspose::Words::Node>)">GetEndPageIndex()</see> - <see cref="Aspose::Words::Layout::LayoutCollector::GetStartPageIndex(System::SharedPtr<Aspose::Words::Node>)">GetStartPageIndex()</see>.
    ASPOSE_WORDS_SHARED_API int32_t GetNumPagesSpanned(const System::SharedPtr<Aspose::Words::Node>& node);
    /// Clears all collected layout data. Call this method after document was manually updated, or layout was rebuilt.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Returns an opaque position of the <see cref="Aspose::Words::Layout::LayoutEnumerator">LayoutEnumerator</see> which corresponds to the specified node.
    /// You can use returned value as an argument to <see cref="Aspose::Words::Layout::LayoutEnumerator::get_Current">Current</see> given the document being
    /// enumerated and the document of the node are the same.
    /// 
    /// This method works for only <see cref="Aspose::Words::Paragraph">Paragraph</see> nodes, as well as indivisible inline nodes,
    /// e.g. <see cref="Aspose::Words::BookmarkStart">BookmarkStart</see> or <see cref="Aspose::Words::Drawing::Shape">Shape</see>. It doesn't work for <see cref="Aspose::Words::Run">Run</see>, <see cref="Aspose::Words::Tables::Cell">Cell</see><see cref="Aspose::Words::Tables::Row">Row</see> or <see cref="Aspose::Words::Tables::Table">Table</see> nodes, and nodes within header/footer.
    /// 
    /// Note that the entity returned for a <see cref="Aspose::Words::Paragraph">Paragraph</see> node is a paragraph break span. Use the appropriate method to ascend to the parent line
    /// 
    /// If you need to navigate to a <see cref="Aspose::Words::Run">Run</see> of text then you can insert bookmark right before it
    /// and then navigate to the bookmark instead.
    /// 
    /// If you need to navigate to a <see cref="Aspose::Words::Tables::Cell">Cell</see> node then you can move to a <see cref="Aspose::Words::Paragraph">Paragraph</see>
    /// node in this cell and then ascend to a parent entity. The same approach can be used for <see cref="Aspose::Words::Tables::Row">Row</see>
    /// and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Object> GetEntity(const System::SharedPtr<Aspose::Words::Node>& node);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~LayoutCollector();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
