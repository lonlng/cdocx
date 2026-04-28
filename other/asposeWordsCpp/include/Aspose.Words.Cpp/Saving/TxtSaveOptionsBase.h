//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/TxtSaveOptionsBase.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/TxtExportHeadersFootersMode.h>
#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Text
{
class Encoding;
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// The base class for specifying additional options when saving a document into a text based formats.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS TxtSaveOptionsBase : public Aspose::Words::Saving::SaveOptions
{
    typedef TxtSaveOptionsBase ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the encoding to use when exporting in text formats.
    /// Default value is <b>%Encoding.UTF8</b>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Text::Encoding> get_Encoding() const;
    /// Specifies the encoding to use when exporting in text formats.
    /// Default value is <b>%Encoding.UTF8</b>.
    ASPOSE_WORDS_SHARED_API void set_Encoding(const System::SharedPtr<System::Text::Encoding>& value);
    /// Specifies the string to use as a paragraph break when exporting in text formats.
    /// 
    /// The default value is <see cref="Aspose::Words::ControlChar::CrLf">CrLf</see>.
    ASPOSE_WORDS_SHARED_API System::String get_ParagraphBreak() const;
    /// Specifies the string to use as a paragraph break when exporting in text formats.
    /// 
    /// The default value is <see cref="Aspose::Words::ControlChar::CrLf">CrLf</see>.
    ASPOSE_WORDS_SHARED_API void set_ParagraphBreak(const System::String& value);
    /// Allows to specify whether the page breaks should be preserved during export.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ForcePageBreaks() const;
    /// Allows to specify whether the page breaks should be preserved during export.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ForcePageBreaks(bool value);
    /// Specifies the way headers and footers are exported to the text formats.
    /// Default value is <see cref="Aspose::Words::Saving::TxtExportHeadersFootersMode::PrimaryOnly">PrimaryOnly</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::TxtExportHeadersFootersMode get_ExportHeadersFootersMode() const;
    /// Specifies the way headers and footers are exported to the text formats.
    /// Default value is <see cref="Aspose::Words::Saving::TxtExportHeadersFootersMode::PrimaryOnly">PrimaryOnly</see>.
    ASPOSE_WORDS_SHARED_API void set_ExportHeadersFootersMode(Aspose::Words::Saving::TxtExportHeadersFootersMode value);

    ASPOSE_WORDS_SHARED_API TxtSaveOptionsBase();

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;

};

}
}
}
