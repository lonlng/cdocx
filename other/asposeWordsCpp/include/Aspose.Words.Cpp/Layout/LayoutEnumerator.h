//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/LayoutEnumerator.h
#pragma once

#include <system/object.h>
#include <system/enum_helpers.h>
#include <system/collections/virtualized_iterator.h>
#include <system/collections/ienumerator.h>

#include <Aspose.Words.Cpp/Layout/LayoutEntityType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
template <typename> class List;
}
}
namespace Drawing
{
class RectangleF;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Layout {

/// Enumerates page layout entities of a document.
/// You can use this class to walk over the page layout model. Available properties are type, geometry, text and page index where entity is rendered,
/// as well as overall structure and relationships.
/// Use combination of <see cref="Aspose::Words::Layout::LayoutCollector::GetEntity(System::SharedPtr<Aspose::Words::Node>)">GetEntity()</see> and <see cref="Aspose::Words::Layout::LayoutEnumerator::get_Current">Current</see> move to the entity which corresponds to a document node.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/converting-to-fixed-page-format/">Converting to Fixed-page Format</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS LayoutEnumerator : public System::Object, public ::System::Details::EnumeratorBasedIterator<System::SharedPtr<System::Object>>, protected ::System::Details::IteratorPointerUpdater<System::SharedPtr<System::Object>, false>
{
    typedef LayoutEnumerator ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();
    CODEPORTING_ENUMERATOR_ITERATOR_METHODS_DECLARATION(CODEPORTING_ARGS(System::SharedPtr<System::Object>), ASPOSE_WORDS_SHARED_API);

public:

    /// Gets the type of the current entity.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::LayoutEntityType get_Type();
    /// Returns the bounding rectangle of the current entity relative to the page top left corner (in points).
    ASPOSE_WORDS_SHARED_API System::Drawing::RectangleF get_Rectangle();
    /// Gets the kind of the current entity. This can be an empty string but never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Kind();
    /// Gets text of the current span entity. Throws for other entity types.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Gets the 1-based index of a page which contains the current entity.
    ASPOSE_WORDS_SHARED_API int32_t get_PageIndex();
    /// Gets current position in the page layout model.
    /// This property returns an opaque object which corresponds to the current layout entity.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Object>& get_Current() const;
    /// Sets current position in the page layout model.
    /// This property returns an opaque object which corresponds to the current layout entity.
    ASPOSE_WORDS_SHARED_API void set_Current(const System::SharedPtr<System::Object>& value);
    /// Gets document this instance enumerates.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document() const;

    /// Initializes new instance of this class.
    /// 
    /// If page layout model of the document hasn't been built the enumerator calls <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see> to build it.
    /// 
    /// Whenever document is updated and new page layout model is created, a new enumerator must be used to access it.
    /// 
    /// @param document A document whose page layout model to enumerate.
    ASPOSE_WORDS_SHARED_API LayoutEnumerator(const System::SharedPtr<Aspose::Words::Document>& document);

    /// Moves the enumerator to the first page of the document.
    ASPOSE_WORDS_SHARED_API void Reset();
    /// Moves to the next sibling entity in visual order.
    /// When iterating lines of a paragraph broken across pages this method
    /// will not move to the next page but rather move to the next entity on the same page.
    ASPOSE_WORDS_SHARED_API bool MoveNext();
    /// Moves to the next sibling entity in a logical order.
    /// When iterating lines of a paragraph broken across pages this method
    /// will move to the next line even if it resides on another page.
    ASPOSE_WORDS_SHARED_API bool MoveNextLogical();
    /// Moves to the previous sibling entity.
    ASPOSE_WORDS_SHARED_API bool MovePrevious();
    /// Moves to the previous sibling entity in a logical order.
    /// When iterating lines of a paragraph broken across pages this method
    /// will move to the previous line even if it resides on another page.
    ASPOSE_WORDS_SHARED_API bool MovePreviousLogical();
    /// Moves to the first child entity.
    ASPOSE_WORDS_SHARED_API bool MoveFirstChild();
    /// Moves to the last child entity.
    ASPOSE_WORDS_SHARED_API bool MoveLastChild();
    /// Moves to the parent entity.
    ASPOSE_WORDS_SHARED_API bool MoveParent();
    /// Moves to the parent entity of the specified type.
    /// 
    /// @param types The parent entity type to move to. Use bitwise-OR to specify multiple parent types.
    ASPOSE_WORDS_SHARED_API bool MoveParent(Aspose::Words::Layout::LayoutEntityType types);

    /// Gets a named property of the entity.
    /// 
    /// @param key A name of the property (case-sensitive).
    /// 
    /// @return Null if property is not available, otherwise value of the property.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Object> idx_get(const System::String& key);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
