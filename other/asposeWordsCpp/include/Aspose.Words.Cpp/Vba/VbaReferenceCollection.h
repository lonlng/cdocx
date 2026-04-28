//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Vba/VbaReferenceCollection.h
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
namespace Vba
{

class VbaReference;
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

namespace Vba {

/// Represents a collection of <see cref="Aspose::Words::Vba::VbaReference">VbaReference</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-vba-macros/">Working with VBA Macros</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS VbaReferenceCollection final : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Vba::VbaReference>>
{
    typedef VbaReferenceCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Vba::VbaReference>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Vba::VbaReference>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Returns the number of VBA references in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Removes the first occurrence of a specified <see cref="Aspose::Words::Vba::VbaReference">VbaReference</see> item from the collection.
    ASPOSE_WORDS_SHARED_API void Remove(const System::SharedPtr<Aspose::Words::Vba::VbaReference>& item);
    /// Removes the <see cref="Aspose::Words::Vba::VbaReference">VbaReference</see> element at the specified index of the collection.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);

    /// Gets <see cref="Aspose::Words::Vba::VbaReference">VbaReference</see> object at the specified index.
    /// 
    /// @param index The zero-based index of the reference to get.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Vba::VbaReference> idx_get(int32_t index);

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

    virtual ASPOSE_WORDS_SHARED_API ~VbaReferenceCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;

    System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Vba::VbaReference>>> GetEnumerator() override;

};

}
}
}
