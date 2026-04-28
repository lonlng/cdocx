//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/ReplacerContext.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Replacing
{
class FindReplaceOptions;
}
}
}
namespace System
{
namespace Text
{
namespace RegularExpressions
{
class Regex;
}
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Find/replace operation context.
class ASPOSE_WORDS_SHARED_CLASS ReplacerContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef ReplacerContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Find/replace options.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& get_FindReplaceOptions() const;

    ASPOSE_WORDS_SHARED_API ReplacerContext();

    /// Sets pattern and replacement used by find/replace operation.
    ASPOSE_WORDS_SHARED_API void SetReplacement(const System::String& pattern, const System::String& replacement);
    /// Sets pattern and replacement used by find/replace operation.
    ASPOSE_WORDS_SHARED_API void SetReplacement(const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;

    System::SharedPtr<System::Object> mField2;

    System::String mField3;

    __TypeStub<4,4,4,4>::type mField4;

};

}
}
}
