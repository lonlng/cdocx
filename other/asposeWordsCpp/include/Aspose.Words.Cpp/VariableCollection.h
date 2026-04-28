//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/VariableCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/sorted_list.h>
#include <system/collections/keyvalue_pair.h>
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

/// A collection of document variables.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-document-properties/">Work with Document Properties</a> documentation article.
/// 
/// Variable names and values are strings.
/// 
/// Variable names are case-insensitive.
class ASPOSE_WORDS_SHARED_CLASS VariableCollection : public System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<System::String, System::String>>
{
    typedef VariableCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<System::String, System::String>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::SortedList<System::String, System::String>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or a sets a document variable by the case-insensitive name.
    /// <c>%null</c> values are not allowed as a right hand side of the assignment and will be replaced by empty string.
    ASPOSE_WORDS_SHARED_API System::String idx_get(const System::String& name);
    /// Gets or a sets a document variable by the case-insensitive name.
    /// <c>%null</c> values are not allowed as a right hand side of the assignment and will be replaced by empty string.
    ASPOSE_WORDS_SHARED_API void idx_set(const System::String& name, const System::String& value);
    /// Gets or sets a document variable at the specified index.
    /// <c>%null</c> values are not allowed as a right hand side of the assignment and will be replaced by empty string.
    /// 
    /// @param index Zero-based index of the document variable.
    ASPOSE_WORDS_SHARED_API System::String idx_get(int32_t index);
    /// Gets or sets a document variable at the specified index.
    /// <c>%null</c> values are not allowed as a right hand side of the assignment and will be replaced by empty string.
    /// 
    /// @param index Zero-based index of the document variable.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, const System::String& value);

    /// Returns an enumerator object that can be used to iterate over all variable in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::Collections::Generic::KeyValuePair<System::String, System::String>>> GetEnumerator() override;
    /// Adds a document variable to the collection.
    /// 
    /// @param name The case-insensitive name of the variable to add.
    /// @param value The value of the variable. The value cannot be <c>%null</c>, if value is null empty string will be used instead.
    ASPOSE_WORDS_SHARED_API void Add(const System::String& name, const System::String& value);
    /// Determines whether the collection contains a document variable with the given name.
    /// 
    /// @param name Case-insensitive name of the document variable to locate.
    /// 
    /// @return <c>%true</c> if item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::String& name);
    /// Returns the zero-based index of the specified document variable in the collection.
    /// 
    /// @param name The case-insensitive name of the variable.
    /// 
    /// @return The zero based index. Negative value if not found.
    ASPOSE_WORDS_SHARED_API int32_t IndexOfKey(const System::String& name);
    /// Removes a document variable with the specified name from the collection.
    /// 
    /// @param name The case-insensitive name of the variable.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& name);
    /// Removes a document variable at the specified index.
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

    VariableCollection();

    virtual ASPOSE_WORDS_SHARED_API ~VariableCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
