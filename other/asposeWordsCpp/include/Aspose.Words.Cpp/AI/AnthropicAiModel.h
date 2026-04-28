//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/AnthropicAiModel.h
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

/// An abstract class representing the integration with Anthropic’s AI models within the Aspose.Words.
class ASPOSE_WORDS_SHARED_CLASS AnthropicAiModel : public Aspose::Words::AI::AiModel
{
    typedef AnthropicAiModel ThisType;
    typedef Aspose::Words::AI::AiModel BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a URL of the model.
    /// The default value is "https://api.anthropic.com/".
    ASPOSE_WORDS_SHARED_API System::String get_Url() override;
    /// Sets a URL of the model.
    /// The default value is "https://api.anthropic.com/".
    ASPOSE_WORDS_SHARED_API void set_Url(System::String value) override;

    /// Generates a summary of the specified document, with options to adjust the length of the summary.
    /// This operation leverages the connected AI model for content processing.
    /// 
    /// @param sourceDocument The document to be summarized.
    /// @param options Optional settings to control the summary length and other parameters.
    /// 
    /// @return A summarized version of the document's content.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Summarize(System::SharedPtr<Aspose::Words::Document> sourceDocument, System::SharedPtr<Aspose::Words::AI::SummarizeOptions> options = nullptr) override;
    /// Generates summaries for an array of documents, with options to control the summary length and other settings.
    /// This method utilizes the connected AI model for processing each document in the array.
    /// 
    /// @param sourceDocuments An array of documents to be summarized.
    /// @param options Optional settings to control the summary length and other parameters
    /// 
    /// @return A summarized version of the document's content.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Summarize(System::ArrayPtr<System::SharedPtr<Aspose::Words::Document>> sourceDocuments, System::SharedPtr<Aspose::Words::AI::SummarizeOptions> options = nullptr) override;
    /// Translates the provided document into the specified target language.
    /// This operation leverages the connected AI model for content translating.
    /// 
    /// @param sourceDocument The document to be translated.
    /// @param targetLanguage The language into which the document will be translated.
    /// 
    /// @return A new <see cref="Aspose::Words::Document">Document</see> object containing the translated document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Translate(System::SharedPtr<Aspose::Words::Document> sourceDocument, Aspose::Words::AI::Language targetLanguage) override;

    ASPOSE_WORDS_SHARED_API AnthropicAiModel();

protected:

    ASPOSE_WORDS_SHARED_API System::String get_ChatEndpoint() override;
    ASPOSE_WORDS_SHARED_API System::String get_CountTokensEndpoint() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Collections::StringToStringDictionary> get_ChatHeaders() override;

    virtual ASPOSE_WORDS_SHARED_API int32_t get_InputTokenLimit();
    virtual ASPOSE_WORDS_SHARED_API int32_t get_OutputTokenLimit();

    ASPOSE_WORDS_SHARED_API System::String CreateRequestBody(System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Aspose::Words::AI::ChatMessage>>> , Aspose::Words::AI::RequestMethod ) override;
    virtual ASPOSE_WORDS_SHARED_API System::String GetPromptsForCheckGrammar(System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions> );
    ASPOSE_WORDS_SHARED_API System::String CheckTextGrammar(System::String , System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions> ) override;

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;

    System::String mField2;

};

}
}
}
