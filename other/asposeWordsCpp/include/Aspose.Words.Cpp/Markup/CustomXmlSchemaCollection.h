//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/CustomXmlSchemaCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

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

/// A collection of strings that represent XML schemas that are associated with a custom XML part.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// You do not create instances of this class. You access the collection of XML schemas of a custom XML part
/// via the <see cref="Aspose::Words::Markup::CustomXmlPart::get_Schemas">Schemas</see> property.
/// 
/// @sa Aspose::Words::Markup::CustomXmlPart
/// @sa Aspose::Words::Markup::CustomXmlPart::get_Schemas
class ASPOSE_WORDS_SHARED_CLASS CustomXmlSchemaCollection : public System::Collections::Generic::IEnumerable<System::String>
{
    typedef CustomXmlSchemaCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::String> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::String>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or sets the element at the specified index.
    ASPOSE_WORDS_SHARED_API System::String idx_get(int32_t index);
    /// Gets or sets the element at the specified index.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, const System::String& value);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::String>> GetEnumerator() override;
    /// Adds an item to the collection.
    /// 
    /// @param value The item to add.
    ASPOSE_WORDS_SHARED_API void Add(const System::String& value);
    /// Returns the zero-based index of the specified value in the collection.
    /// 
    /// @param value The case-sensitive value to locate.
    /// 
    /// @return The zero based index. Negative value if not found.
    ASPOSE_WORDS_SHARED_API int32_t IndexOf(const System::String& value);
    /// Removes the specified value from the collection.
    /// 
    /// @param name The case-sensitive value to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& name);
    /// Removes a value at the specified index.
    /// 
    /// @param index The zero based index.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all elements from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Makes a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlSchemaCollection> Clone();

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

    CustomXmlSchemaCollection();

    virtual ASPOSE_WORDS_SHARED_API ~CustomXmlSchemaCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
