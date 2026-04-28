//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PageSet.h
#pragma once

#include <system/collections/ienumerable.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Saving
{

class PageRange;

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

namespace Saving {

/// Describes a random set of pages.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PageSet final : public System::Collections::Generic::IEnumerable<int32_t>
{
    typedef PageSet ThisType;
    typedef System::Collections::Generic::IEnumerable<int32_t> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a set with all the pages of the document in their original order.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PageSet> get_All();
    /// Gets a set with all the even pages of the document in their original order.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PageSet> get_Even();
    /// Gets a set with all the odd pages of the document in their original order.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PageSet> get_Odd();

    /// Creates an one-page set based on exact page index.
    /// 
    /// @param page Zero-based index of the page.
    ASPOSE_WORDS_SHARED_API PageSet(int32_t page);
    /// Creates a page set based on exact page indices.
    /// 
    /// @param pages Zero-based indices of pages.
    ASPOSE_WORDS_SHARED_API PageSet(const System::ArrayPtr<int32_t>& pages);
    /// Creates a page set based on ranges.
    /// 
    /// @param ranges Array of page ranges.
    ASPOSE_WORDS_SHARED_API PageSet(const System::ArrayPtr<System::SharedPtr<Aspose::Words::Saving::PageRange>>& ranges);

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<int32_t>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~PageSet();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
