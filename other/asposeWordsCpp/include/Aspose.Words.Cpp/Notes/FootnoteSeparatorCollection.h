//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/FootnoteSeparatorCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Notes
{
class FootnoteSeparator;
enum class FootnoteSeparatorType;
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

namespace Notes {

/// Provides typed access to <see cref="Aspose::Words::Notes::FootnoteSeparator">FootnoteSeparator</see> nodes of a document.
class ASPOSE_WORDS_SHARED_CLASS FootnoteSeparatorCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Notes::FootnoteSeparator>>
{
    typedef FootnoteSeparatorCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Notes::FootnoteSeparator>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Retrieves a <see cref="Aspose::Words::Notes::FootnoteSeparator">FootnoteSeparator</see> of the specified type.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Notes::FootnoteSeparator> idx_get(Aspose::Words::Notes::FootnoteSeparatorType separatorType);

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Notes::FootnoteSeparator>>> GetEnumerator() override;

    ASPOSE_WORDS_SHARED_API FootnoteSeparatorCollection();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FootnoteSeparatorCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
