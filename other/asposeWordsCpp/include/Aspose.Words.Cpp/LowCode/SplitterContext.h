//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/SplitterContext.h
#pragma once

#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace LowCode
{
class SplitOptions;

}
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Document splitter context.
class ASPOSE_WORDS_SHARED_CLASS SplitterContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef SplitterContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Document split options.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::LowCode::SplitOptions>& get_SplitOptions() const;

    ASPOSE_WORDS_SHARED_API SplitterContext();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
