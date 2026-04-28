//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/RevisionGroup.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/RevisionType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
}

namespace Aspose {

namespace Words {

/// Represents a group of sequential <see cref="Aspose::Words::Revision">Revision</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/track-changes-in-a-document/">Track Changes in a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS RevisionGroup : public System::Object
{
    typedef RevisionGroup ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns inserted/deleted/moved text or description of format change.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Gets the author of this revision group.
    ASPOSE_WORDS_SHARED_API System::String get_Author();
    /// Gets the type of revisions included in this group.
    ASPOSE_WORDS_SHARED_API Aspose::Words::RevisionType get_RevisionType();

protected:

private:

    System::String mField0;

    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
