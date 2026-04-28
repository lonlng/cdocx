//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/OdsoRecipientDataCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Settings
{
class OdsoRecipientData;
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

namespace Settings {

/// A typed collection of <see cref="Aspose::Words::Settings::OdsoRecipientData">OdsoRecipientData</see>To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// @sa Aspose::Words::Settings::OdsoRecipientData
/// @sa Aspose::Words::Settings::Odso::get_RecipientDatas
class ASPOSE_WORDS_SHARED_CLASS OdsoRecipientDataCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData>>
{
    typedef OdsoRecipientDataCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or sets an item in this collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData> idx_get(int32_t index);
    /// Gets or sets an item in this collection.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, const System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData>& value);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData>>> GetEnumerator() override;
    /// Adds an object to the end of this collection.
    /// 
    /// @param value The object to add. Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API int32_t Add(const System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData>& value);
    /// Removes all elements from this collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Removes the element at the specified index.
    /// 
    /// @param index The zero-based index of the element.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);

    ASPOSE_WORDS_SHARED_API OdsoRecipientDataCollection();

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

    virtual ASPOSE_WORDS_SHARED_API ~OdsoRecipientDataCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
