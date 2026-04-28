//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/XlsxSaveOptions.h
#pragma once

#include <Aspose.Words.Cpp/Saving/XlsxSectionMode.h>
#include <Aspose.Words.Cpp/Saving/XlsxDateTimeParsingMode.h>
#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/Saving/CompressionLevel.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Xlsx">Xlsx</see>
/// format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify
/// Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS XlsxSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef XlsxSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Xlsx">Xlsx</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Xlsx">Xlsx</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Specifies the compression level used to save document.
    /// The default value is <see cref="Aspose::Words::Saving::CompressionLevel::Normal">Normal</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::CompressionLevel get_CompressionLevel() const;
    /// Specifies the compression level used to save document.
    /// The default value is <see cref="Aspose::Words::Saving::CompressionLevel::Normal">Normal</see>.
    ASPOSE_WORDS_SHARED_API void set_CompressionLevel(Aspose::Words::Saving::CompressionLevel value);
    /// Gets the way how sections are handled when saving to the output XLSX document.
    /// The default value is <see cref="Aspose::Words::Saving::XlsxSectionMode::MultipleWorksheets">MultipleWorksheets</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::XlsxSectionMode get_SectionMode() const;
    /// Sets the way how sections are handled when saving to the output XLSX document.
    /// The default value is <see cref="Aspose::Words::Saving::XlsxSectionMode::MultipleWorksheets">MultipleWorksheets</see>.
    ASPOSE_WORDS_SHARED_API void set_SectionMode(Aspose::Words::Saving::XlsxSectionMode value);
    /// Gets the mode that specifies how document text is parsed to identify date and time values.
    /// The default value is <see cref="Aspose::Words::Saving::XlsxDateTimeParsingMode::UseCurrentLocale">UseCurrentLocale</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::XlsxDateTimeParsingMode get_DateTimeParsingMode() const;
    /// Sets the mode that specifies how document text is parsed to identify date and time values.
    /// The default value is <see cref="Aspose::Words::Saving::XlsxDateTimeParsingMode::UseCurrentLocale">UseCurrentLocale</see>.
    ASPOSE_WORDS_SHARED_API void set_DateTimeParsingMode(Aspose::Words::Saving::XlsxDateTimeParsingMode value);

    ASPOSE_WORDS_SHARED_API XlsxSaveOptions();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;

};

}
}
}
