//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Lists/ListTemplate.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class DocumentBase;

namespace Lists
{
class List;

}

class Style;

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
}

namespace Aspose {

namespace Words {

namespace Lists {

/// Stores and manages formatting of bulleted and numbered lists used in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-lists/">Working with Lists</a> documentation article.
/// 
/// A list in a %Microsoft Word document is a set of list formatting properties.
/// The formatting of the lists is stored in the <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see> collection separately
/// from the paragraphs of text.
/// 
/// You do not create objects of this class. There is always only one <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see>
/// object per document and it is accessible via the <see cref="Aspose::Words::DocumentBase::get_Lists">Lists</see> property.
/// 
/// To create a new list based on a predefined list template or based on a list style,
/// use the <see cref="Aspose::Words::Lists::ListCollection::Add(System::SharedPtr<Aspose::Words::Style>)">Add()</see> method.
/// 
/// To create a new list with formatting identical to an existing list,
/// use the <see cref="Aspose::Words::Lists::ListCollection::AddCopy(System::SharedPtr<Aspose::Words::Lists::List>)">AddCopy()</see> method.
/// 
/// To make a paragraph bulleted or numbered, you need to apply list formatting
/// to a paragraph by assigning a <see cref="Aspose::Words::Lists::List">List</see> object to the
/// <see cref="Aspose::Words::Lists::ListFormat::get_List">List</see> property of <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see>.
/// 
/// To remove list formatting from a paragraph, use the <see cref="Aspose::Words::Lists::ListFormat::RemoveNumbers">RemoveNumbers</see>
/// method.
/// 
/// If you know a bit about WordprocessingML, then you might know it defines separate concepts
/// for "list" and "list definition". This exactly corresponds to how list formatting is stored
/// in a %Microsoft Word document at the low level. List definition is like a "schema" and
/// list is like an instance of a list definition.
/// 
/// To simplify programming model, %Aspose.Words hides the distinction between list and list
/// definition in much the same way like %Microsoft Word hides this in its user interface.
/// This allows you to concentrate more on how you want your document to look like, rather than
/// building low-level objects to satisfy requirements of the %Microsoft Word file format.
/// 
/// It is not possible to delete lists once they are created in the current version of Aspose.Words.
/// This is similar to %Microsoft Word where user does not have explicit control over list definitions.
/// 
/// @sa Aspose::Words::Lists::List
/// @sa Aspose::Words::Lists::ListLevel
/// @sa Aspose::Words::Lists::ListFormat
class ASPOSE_WORDS_SHARED_CLASS ListCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Lists::List>>
{
    typedef ListCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Lists::List>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Lists::List>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the count of numbered and bulleted lists in the document.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();
    /// Gets the owner document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentBase> get_Document() const;

    /// Gets the enumerator object that will enumerate lists in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Lists::List>>> GetEnumerator() override;
    /// Creates a new list based on a predefined template and adds it to the collection of lists in the document.
    /// 
    /// %Aspose.Words list templates correspond to the 21 list templates available
    /// in the Bullets and Numbering dialog box in %Microsoft Word 2003.
    /// 
    /// All lists created using this method have 9 list levels.
    /// 
    /// @param listTemplate The template of the list.
    /// 
    /// @return The newly created list.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> Add(Aspose::Words::Lists::ListTemplate listTemplate);
    /// Creates a new single level list based on the predefined template and adds it to the list collection in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> AddSingleLevelList(Aspose::Words::Lists::ListTemplate listTemplate);
    /// Creates a new list that references a list style and adds it to the collection of lists in the document.
    /// 
    /// The newly created list references the list style. If you change the properties of the list
    /// style, it is reflected in the properties of the list. Vice versa, if you change the properties
    /// of the list, it is reflected in the properties of the list style.
    /// 
    /// @param listStyle The list style.
    /// 
    /// @return The newly created list.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> Add(const System::SharedPtr<Aspose::Words::Style>& listStyle);
    /// Creates a new list by copying the specified list and adding it to the collection of lists in the document.
    /// 
    /// The source list can be from any document. If the source list belongs to a different document,
    /// a copy of the list is created and added to the current document.
    /// 
    /// If the source list is a reference to or a definition of a list style,
    /// the newly created list is not related to the original list style.
    /// 
    /// @param srcList The source list to copy from.
    /// 
    /// @return The newly created list.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> AddCopy(const System::SharedPtr<Aspose::Words::Lists::List>& srcList);
    /// Gets a list by a list identifier.
    /// 
    /// You don't normally need to use this method. Most of the time you apply list formatting
    /// to paragraphs just by settings the <see cref="Aspose::Words::Lists::ListFormat::get_List">List</see> property
    /// of the <see cref="Aspose::Words::Lists::ListFormat">ListFormat</see> object.
    /// 
    /// @param listId The list identifier.
    /// 
    /// @return Returns the list object. Returns <c>%null</c> if a list with the specified identifier was not found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> GetListByListId(int32_t listId);

    /// Gets a list by index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::List> idx_get(int32_t index);

    ASPOSE_WORDS_SHARED_API iterator begin() noexcept;

    ASPOSE_WORDS_SHARED_API iterator end() noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator begin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator end() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cbegin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cend() const noexcept;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginConstIterator() const override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndConstIterator() const override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ListCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;

};

}
}
}
