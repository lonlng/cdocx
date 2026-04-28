//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/GoogleAiModel.h
#pragma once

#include <Aspose.Words.Cpp/AI/Language.h>
#include <Aspose.Words.Cpp/AI/AiModel.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Collections
{
class StringToStringDictionary;
}
namespace Words
{
namespace AI
{

class ChatMessage;
class CheckGrammarOptions;

enum class RequestMethod;
class SummarizeOptions;
}
class Document;

}
}
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

namespace AI {

/// Class representing Google AI Models (Gemini) integration within Aspose.Words.
class ASPOSE_WORDS_SHARED_CLASS GoogleAiModel : public Aspose::Words::AI::AiModel
{
    typedef GoogleAiModel ThisType;
    typedef Aspose::Words::AI::AiModel BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a URL of the model.
    /// The default value is "https://generativelanguage.googleapis.com/v1beta/models/".
    ASPOSE_WORDS_SHARED_API System::String get_Url() override;
    /// Sets a URL of the model.
    /// The default value is "https://generativelanguage.googleapis.com/v1beta/models/".
    ASPOSE_WORDS_SHARED_API void set_Url(System::String value) override;

    /// Initializes a new instance of <see cref="Aspose::Words::AI::GoogleAiModel">GoogleAiModel</see> class.
    /// 
    /// @param name The name of the model. For example, gemini-2.5-flash.
    ASPOSE_WORDS_SHARED_API GoogleAiModel(const System::String& name);
    /// Initializes a new instance of <see cref="Aspose::Words::AI::GoogleAiModel">GoogleAiModel</see> class.
    /// 
    /// @param name The name of the model. For example, gemini-2.5-flash.
    /// @param apiKey The API key to use the Gemini API.
    ///     Please refer to https://ai.google.dev/gemini-api/docs/api-key for details.
    ASPOSE_WORDS_SHARED_API GoogleAiModel(const System::String& name, const System::String& apiKey);

    /// Summarizes specified <see cref="Aspose::Words::Document">Document</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Summarize(System::SharedPtr<Aspose::Words::Document> doc, System::SharedPtr<Aspose::Words::AI::SummarizeOptions> options = nullptr) override;
    /// Summarizes specified <see cref="Aspose::Words::Document">Document</see> objects.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Summarize(System::ArrayPtr<System::SharedPtr<Aspose::Words::Document>> docs, System::SharedPtr<Aspose::Words::AI::SummarizeOptions> options = nullptr) override;
    /// Translates a specified document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Translate(System::SharedPtr<Aspose::Words::Document> doc, Aspose::Words::AI::Language language) override;

protected:

    ASPOSE_WORDS_SHARED_API System::String get_ChatEndpoint() override;
    ASPOSE_WORDS_SHARED_API System::String get_CountTokensEndpoint() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Collections::StringToStringDictionary> get_ChatHeaders() override;
    ASPOSE_WORDS_SHARED_API System::String get_Name() override;

    ASPOSE_WORDS_SHARED_API System::String CheckTextGrammar(System::String , System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions> ) override;
    ASPOSE_WORDS_SHARED_API System::String CreateRequestBody(System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Aspose::Words::AI::ChatMessage>>> , Aspose::Words::AI::RequestMethod ) override;
    ASPOSE_WORDS_SHARED_API System::String GetEndpointUrl(Aspose::Words::AI::RequestMethod ) override;

private:

    System::String mField0;

    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<System::Object> mField2;
    System::String mField3;

};

}
}
}
