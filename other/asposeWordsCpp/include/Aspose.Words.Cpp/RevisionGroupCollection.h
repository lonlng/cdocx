//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/RevisionGroupCollection.h
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

class RevisionGroup;

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

/// A collection of <see cref="Aspose::Words::RevisionGroup">RevisionGroup</see> objects that represent revision groups in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/track-changes-in-a-document/">Track Changes in a Document</a> documentation article.
/// 
/// You do not create instances of this class directly. Use the <see cref="Aspose::Words::RevisionCollection::get_Groups">Groups</see>
/// property to get revision groups present in a document.
class ASPOSE_WORDS_SHARED_CLASS RevisionGroupCollection final : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::RevisionGroup>>
{
    typedef RevisionGroupCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::RevisionGroup>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::RevisionGroup>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Returns the number of revision groups in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::RevisionGroup>>> GetEnumerator() override;

    /// Returns a revision group at the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RevisionGroup> idx_get(int32_t index);

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

    virtual ASPOSE_WORDS_SHARED_API ~RevisionGroupCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
