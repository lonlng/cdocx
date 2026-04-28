//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/SummarizeOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/AI/SummaryLength.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace AI {

/// Allows to specify various options for summarizing document content.
class ASPOSE_WORDS_SHARED_CLASS SummarizeOptions : public System::Object
{
    typedef SummarizeOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Allows to specify summary length.
    /// Default value is <see cref="Aspose::Words::AI::SummaryLength::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::AI::SummaryLength get_SummaryLength() const;
    /// Allows to specify summary length.
    /// Default value is <see cref="Aspose::Words::AI::SummaryLength::Medium">Medium</see>.
    ASPOSE_WORDS_SHARED_API void set_SummaryLength(Aspose::Words::AI::SummaryLength value);

    /// Initializes a new instances of <see cref="Aspose::Words::AI::SummarizeOptions">SummarizeOptions</see> class.
    ASPOSE_WORDS_SHARED_API SummarizeOptions();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;

};

}
}
}
