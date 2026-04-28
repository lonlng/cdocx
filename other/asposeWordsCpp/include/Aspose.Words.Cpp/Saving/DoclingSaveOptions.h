//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DoclingSaveOptions.h
#pragma once

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Docling">Docling</see>
/// format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify
/// Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS DoclingSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef DoclingSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Docling">Docling</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Docling">Docling</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Gets a value indicating whether non-image shapes should be rendered and written to the output
    /// Docling JSON document.
    ASPOSE_WORDS_SHARED_API bool get_RenderNonImageShapes() const;
    /// Sets a value indicating whether non-image shapes should be rendered and written to the output
    /// Docling JSON document.
    ASPOSE_WORDS_SHARED_API void set_RenderNonImageShapes(bool value);

    ASPOSE_WORDS_SHARED_API DoclingSaveOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;

};

}
}
}
