//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/MustacheTag.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class Run;
}
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// Represents "mustache" tag.
class ASPOSE_WORDS_SHARED_CLASS MustacheTag : public System::Object
{
    typedef MustacheTag ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the run that contains the beginning of the tag.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Run>& get_ReferenceRun() const;
    /// Gets the zero-based starting position of the tag from the start of the <see cref="Aspose::Words::MailMerging::MustacheTag::get_ReferenceRun">ReferenceRun</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_ReferenceOffset() const;
    /// Gets the text of the tag.
    ASPOSE_WORDS_SHARED_API System::String get_Text() const;

protected:

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;

};

}
}
}
