//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/PdfLoadOptions.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Loading/LoadOptions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify additional options when loading Pdf document into a <see cref="Aspose::Words::Document">Document</see> object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PdfLoadOptions : public Aspose::Words::Loading::LoadOptions
{
    typedef PdfLoadOptions ThisType;
    typedef Aspose::Words::Loading::LoadOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the 0-based index of the first page to read. Default is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_PageIndex() const;
    /// Sets the 0-based index of the first page to read. Default is 0.
    ASPOSE_WORDS_SHARED_API void set_PageIndex(int32_t value);
    /// Gets the number of pages to read. Default is MaxValue which means all pages of the document will be read.
    ASPOSE_WORDS_SHARED_API int32_t get_PageCount() const;
    /// Sets the number of pages to read. Default is MaxValue which means all pages of the document will be read.
    ASPOSE_WORDS_SHARED_API void set_PageCount(int32_t value);
    /// Gets the flag indicating whether images must be skipped while loading PDF document. Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_SkipPdfImages() const;
    /// Sets the flag indicating whether images must be skipped while loading PDF document. Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_SkipPdfImages(bool value);

    ASPOSE_WORDS_SHARED_API PdfLoadOptions();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;

};

}
}
}
