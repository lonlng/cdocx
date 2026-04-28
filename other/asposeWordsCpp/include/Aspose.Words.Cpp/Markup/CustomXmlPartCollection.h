//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/CustomXmlPartCollection.h
#pragma once

#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Markup
{
class CustomXmlPart;
}

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
}

namespace Aspose {

namespace Words {

namespace Markup {

/// Represents a collection of Custom XML Parts. The items are <see cref="Aspose::Words::Markup::CustomXmlPart">CustomXmlPart</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// You do not normally need to create instances of this class. You can access custom XML data
/// stored in a document via the <see cref="Aspose::Words::Document::get_CustomXmlParts">CustomXmlParts</see> property.
/// 
/// @sa Aspose::Words::Markup::CustomXmlPart
/// @sa Aspose::Words::Document::get_CustomXmlParts
class ASPOSE_WORDS_SHARED_CLASS CustomXmlPartCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>>
{
    typedef CustomXmlPartCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or sets an item at the specified index.
    /// 
    /// @param index Zero-based index of the item.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPart> idx_get(int32_t index);
    /// Gets or sets an item at the specified index.
    /// 
    /// @param index Zero-based index of the item.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, const System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>& value);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>>> GetEnumerator() override;
    /// Adds an item to the collection.
    /// 
    /// @param part The custom XML part to add.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Markup::CustomXmlPart>& part);
    /// Creates a new XML part with the specified XML and adds it to the collection.
    /// 
    /// @param id Identifier of a new custom XML part.
    /// @param xml XML data of the part.
    /// 
    /// @return Created custom XML part.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPart> Add(const System::String& id, const System::String& xml);
    /// Removes an item at the specified index.
    /// 
    /// @param index The zero based index.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all elements from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Finds and returns a custom XML part by its identifier.
    /// 
    /// @param id Case-sensitive string that identifies the custom XML part.
    /// 
    /// @return Returns <c>%null</c> if a custom XML part with the specified identifier is not found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPart> GetById(const System::String& id);
    /// Makes a deep copy of this collection and its items.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPartCollection> Clone();

    ASPOSE_WORDS_SHARED_API CustomXmlPartCollection();

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

    virtual ASPOSE_WORDS_SHARED_API ~CustomXmlPartCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
