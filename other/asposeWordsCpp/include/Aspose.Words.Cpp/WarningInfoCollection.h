//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WarningInfoCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/IWarningCallback.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class WarningInfo;
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

/// Represents a typed collection of <see cref="Aspose::Words::WarningInfo">WarningInfo</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
/// 
/// You can use this collection object as the simplest form of <see cref="Aspose::Words::IWarningCallback">IWarningCallback</see> implementation to gather
/// all warnings that %Aspose.Words generates during a load or save operation. Create an instance of this class and assign it
/// to the <see cref="Aspose::Words::Loading::LoadOptions::get_WarningCallback">WarningCallback</see> or <see cref="Aspose::Words::DocumentBase::get_WarningCallback">WarningCallback</see> property.
/// 
/// @sa Aspose::Words::WarningInfo
/// @sa Aspose::Words::IWarningCallback
class ASPOSE_WORDS_SHARED_CLASS WarningInfoCollection : public Aspose::Words::IWarningCallback, public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::WarningInfo>>
{
    typedef WarningInfoCollection ThisType;
    typedef Aspose::Words::IWarningCallback BaseType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::WarningInfo>> BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::WarningInfo>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets an item at the specified index.
    /// 
    /// @param index Zero-based index of the item.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::WarningInfo> idx_get(int32_t index);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::WarningInfo>>> GetEnumerator() override;
    /// Removes all elements from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Implements the <see cref="Aspose::Words::IWarningCallback">IWarningCallback</see> interface. Adds a warning to this collection.
    ASPOSE_WORDS_SHARED_API void Warning(System::SharedPtr<Aspose::Words::WarningInfo> info) override;

    ASPOSE_WORDS_SHARED_API WarningInfoCollection();

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

    virtual ASPOSE_WORDS_SHARED_API ~WarningInfoCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
