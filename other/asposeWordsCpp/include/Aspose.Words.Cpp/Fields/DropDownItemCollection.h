//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/DropDownItemCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/IComplexAttr.h>
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

namespace Fields {

/// A collection of strings that represent all the items in a drop-down form field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// @sa Aspose::Words::Fields::FormField
/// @sa Aspose::Words::Fields::FormField::get_DropDownItems
class ASPOSE_WORDS_SHARED_CLASS DropDownItemCollection : public System::Collections::Generic::IEnumerable<System::String>, public Aspose::Words::IComplexAttr
{
    typedef DropDownItemCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::String> BaseType;
    typedef Aspose::Words::IComplexAttr BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
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
    /// Adds a string to the end of the collection.
    /// 
    /// @param value The string to add to the end of the collection.
    /// 
    /// @return The zero-based index at which the new element is inserted.
    ASPOSE_WORDS_SHARED_API int32_t Add(const System::String& value);
    /// Determines whether the collection contains the specified value.
    /// 
    /// @param value Case-sensitive value to locate.
    /// 
    /// @return <c>%true</c> if the item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::String& value);
    /// Returns the zero-based index of the specified value in the collection.
    /// 
    /// @param value The case-sensitive value to locate.
    /// 
    /// @return The zero based index. Negative value if not found.
    ASPOSE_WORDS_SHARED_API int32_t IndexOf(const System::String& value);
    /// Inserts a string into the collection at the specified index.
    /// 
    /// @param index The zero-based index at which value is inserted.
    /// @param value The string to insert.
    ASPOSE_WORDS_SHARED_API void Insert(int32_t index, const System::String& value);
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

    DropDownItemCollection();

    virtual ASPOSE_WORDS_SHARED_API ~DropDownItemCollection();

private:

    bool get_IsInheritedComplexAttr() override;

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<Aspose::Words::IComplexAttr> DeepCloneComplexAttr() override;

protected:

};

}
}
}
