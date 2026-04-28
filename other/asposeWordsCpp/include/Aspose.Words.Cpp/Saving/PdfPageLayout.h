//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfPageLayout.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the page layout to be used when the document is opened in a PDF reader.
enum class ASPOSE_WORDS_SHARED_CLASS PdfPageLayout
{
    /// Display one page at a time.
    SinglePage = 0,
    /// Display the pages in one column.
    OneColumn = 1,
    /// Display the pages in two columns, with odd-numbered pages on the left.
    TwoColumnLeft = 2,
    /// Display the pages in two columns, with odd-numbered pages on the right.
    TwoColumnRight = 3,
    /// Display the pages two at a time, with odd-numbered pages on the left.
    TwoPageLeft = 4,
    /// Display the pages two at a time, with odd-numbered pages on the right.
    TwoPageRight = 5
};

/// \cond
class PdfPageLayoutUtil : public System::Object
{
    typedef PdfPageLayoutUtil ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    static System::String ToString(Aspose::Words::Saving::PdfPageLayout enumValue);

};/// \endcond

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfPageLayout>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfPageLayout, const char_t*>, 6>& values();
};
