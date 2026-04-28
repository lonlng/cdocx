//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfPageMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how the PDF document should be displayed when opened in the PDF reader.
enum class ASPOSE_WORDS_SHARED_CLASS PdfPageMode
{
    /// Neither document outline nor thumbnail images are visible.
    UseNone = 0,
    /// Document outline is visible.
    /// Note that if there're no outlines in the PDF document then outline navigation pane will not be visible anyway.
    UseOutlines = 1,
    /// Thumbnail images are visible.
    UseThumbs = 2,
    /// Full-screen mode, with no menu bar, window controls, or any other window visible.
    FullScreen = 3,
    /// Optional content group panel is visible.
    UseOC = 4,
    /// Attachments panel is visible.
    UseAttachments = 5
};

/// \cond
class PdfPageModeUtil : public System::Object
{
    typedef PdfPageModeUtil ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    static System::String ToString(Aspose::Words::Saving::PdfPageMode enumValue);

};/// \endcond

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfPageMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfPageMode, const char_t*>, 6>& values();
};
