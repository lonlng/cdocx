//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/AiModel.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/AI/Language.h>
#include <Aspose.Words.Cpp/AI/AiModelType.h>
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

/// An abstract class representing the integration with various AI models within the Aspose.Words.
class ASPOSE_WORDS_SHARED_CLASS AiModel : public System::Object
{
    typedef AiModel ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using System::Object::ToString;

public:

    /// Gets a URL of the model.
    /// The default value is specific for the model.
    virtual ASPOSE_WORDS_SHARED_API System::String get_Url() = 0;
    /// Sets a URL of the model.
    /// The default value is specific for the model.
    virtual ASPOSE_WORDS_SHARED_API void set_Url(System::String value) = 0;
    /// Gets the number of milliseconds to wait before the request to AI model times out.
    /// The default value is 100,000 milliseconds (100 seconds).
    ASPOSE_WORDS_SHARED_API int32_t get_Timeout() const;
    /// Sets the number of milliseconds to wait before the request to AI model times out.
    /// The default value is 100,000 milliseconds (100 seconds).
    ASPOSE_WORDS_SHARED_API void set_Timeout(int32_t value);

    /// Generates a summary of the specified document, with options to adjust the length of the summary.
    /// This operation leverages the connected AI model for content processing.
    /// 
    /// @param sourceDocument The document to be summarized.
    /// @param options Optional settings to control the summary length and other parameters.
    /// 
    /// @return A summarized version of the document's content.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Summarize(System::SharedPtr<Aspose::Words::Document> sourceDocument, System::SharedPtr<Aspose::Words::AI::SummarizeOptions> options = nullptr) = 0;
    /// Generates summaries for an array of documents, with options to control the summary length and other settings.
    /// This method utilizes the connected AI model for processing each document in the array.
    /// 
    /// @param sourceDocuments An array of documents to be summarized.
    /// @param options Optional settings to control the summary length and other parameters
    /// 
    /// @return A summarized version of the document's content.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Summarize(System::ArrayPtr<System::SharedPtr<Aspose::Words::Document>> sourceDocuments, System::SharedPtr<Aspose::Words::AI::SummarizeOptions> options = nullptr) = 0;
    /// Checks grammar of the provided document.
    /// This operation leverages the connected AI model for checking grammar of document.
    /// 
    /// @param sourceDocument The document being checked for grammar.
    /// @param options Optional settings to control how grammar will be checked.
    /// 
    /// @return A new <see cref="Aspose::Words::Document">Document</see> with checked grammar.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> CheckGrammar(System::SharedPtr<Aspose::Words::Document> sourceDocument, System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions> options = nullptr);
    /// Translates the provided document into the specified target language.
    /// This operation leverages the connected AI model for content translating.
    /// 
    /// @param sourceDocument The document to be translated.
    /// @param targetLanguage The language into which the document will be translated.
    /// 
    /// @return A new <see cref="Aspose::Words::Document">Document</see> object containing the translated document.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Translate(System::SharedPtr<Aspose::Words::Document> sourceDocument, Aspose::Words::AI::Language targetLanguage) = 0;
    /// Sets a specified API key to the model.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::AI::AiModel> WithApiKey(const System::String& apiKey);
    /// Creates a new instance of <see cref="Aspose::Words::AI::AiModel">AiModel</see> class.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::AI::AiModel> Create(Aspose::Words::AI::AiModelType modelType);

protected:

    virtual ASPOSE_WORDS_SHARED_API System::String get_Name() = 0;

    virtual System::String get_ChatEndpoint() = 0;
    virtual System::String get_CountTokensEndpoint() = 0;
    virtual System::SharedPtr<Aspose::Collections::StringToStringDictionary> get_ChatHeaders() = 0;

    AiModel();

    virtual ASPOSE_WORDS_SHARED_API System::String GetEndpointUrl(Aspose::Words::AI::RequestMethod );

    virtual System::String CheckTextGrammar(System::String , System::SharedPtr<Aspose::Words::AI::CheckGrammarOptions> ) = 0;
    virtual System::String CreateRequestBody(System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<Aspose::Words::AI::ChatMessage>>> , Aspose::Words::AI::RequestMethod ) = 0;

    virtual ASPOSE_WORDS_SHARED_API ~AiModel();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;

};

}
}
}
