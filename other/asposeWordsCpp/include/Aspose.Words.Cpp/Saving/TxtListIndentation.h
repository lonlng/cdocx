//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/TxtListIndentation.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how list levels are indented when document is exporting to <see cref="Aspose::Words::SaveFormat::Text">Text</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS TxtListIndentation : public System::Object
{
    typedef TxtListIndentation ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets how many <see cref="Aspose::Words::Saving::TxtListIndentation::get_Character">Character</see> to use as indentation per one list level.
    /// The default value is 0, that means no indentation.
    ASPOSE_WORDS_SHARED_API int32_t get_Count() const;
    /// Sets how many <see cref="Aspose::Words::Saving::TxtListIndentation::get_Character">Character</see> to use as indentation per one list level.
    /// The default value is 0, that means no indentation.
    ASPOSE_WORDS_SHARED_API void set_Count(int32_t value);
    /// Gets which character to use for indenting list levels.
    /// The default value is '\\0', that means there is no indentation.
    ASPOSE_WORDS_SHARED_API char16_t get_Character() const;
    /// Sets which character to use for indenting list levels.
    /// The default value is '\\0', that means there is no indentation.
    ASPOSE_WORDS_SHARED_API void set_Character(char16_t value);

    ASPOSE_WORDS_SHARED_API TxtListIndentation();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<2,2,2,2>::type mField1;

};

}
}
}
