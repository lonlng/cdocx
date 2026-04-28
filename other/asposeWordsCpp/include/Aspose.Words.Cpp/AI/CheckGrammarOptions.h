//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/CheckGrammarOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace AI {

/// Allows to specify various options while checking grammar of a document using AI.
class ASPOSE_WORDS_SHARED_CLASS CheckGrammarOptions : public System::Object
{
    typedef CheckGrammarOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Allows to specify either final or revised document to be returned with proofed text.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_MakeRevisions() const;
    /// Allows to specify either final or revised document to be returned with proofed text.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_MakeRevisions(bool value);
    /// Allows to specify either AI will try to improve stylistics of the text being proofed.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ImproveStylistics() const;
    /// Allows to specify either AI will try to improve stylistics of the text being proofed.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ImproveStylistics(bool value);
    /// Allows to specify either <see cref="Aspose::Words::AI::AiModel::CheckGrammar(System::SharedPtr<Aspose::Words::Document>, System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions>)">CheckGrammar()</see> will try to preserve
    /// layout and formatting of the original document, or not.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_PreserveFormatting() const;
    /// Allows to specify either <see cref="Aspose::Words::AI::AiModel::CheckGrammar(System::SharedPtr<Aspose::Words::Document>, System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions>)">CheckGrammar()</see> will try to preserve
    /// layout and formatting of the original document, or not.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_PreserveFormatting(bool value);

    ASPOSE_WORDS_SHARED_API CheckGrammarOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;

};

}
}
}
