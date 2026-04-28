//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Framesets/FramesetCollection.h
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
namespace Framesets
{
class Frameset;
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

namespace Framesets {

/// Represents a collection of instances of the <see cref="Aspose::Words::Framesets::Frameset">Frameset</see> class.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FramesetCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Framesets::Frameset>>
{
    typedef FramesetCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Framesets::Frameset>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Framesets::Frameset>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of frames or frames pages contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets a frame or frames page at the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Framesets::Frameset> idx_get(int32_t index);

    /// Returns an enumerator that iterates through the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Framesets::Frameset>>> GetEnumerator() override;

    ASPOSE_WORDS_SHARED_API FramesetCollection();

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

    virtual ASPOSE_WORDS_SHARED_API ~FramesetCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
