//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/MergerContext.h
#pragma once

#include <Aspose.Words.Cpp/LowCode/MergeFormatMode.h>
#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace LowCode {

/// Document merger context.
class ASPOSE_WORDS_SHARED_CLASS MergerContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef MergerContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies how to merge formatting that clashes.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LowCode::MergeFormatMode get_MergeFormatMode() const;
    /// Specifies how to merge formatting that clashes.
    ASPOSE_WORDS_SHARED_API void set_MergeFormatMode(Aspose::Words::LowCode::MergeFormatMode value);

    ASPOSE_WORDS_SHARED_API MergerContext();

private:

    __TypeStub<4,4,4,4>::type mField0;

};

}
}
}
