//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/OoxmlCompliance.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify which OOXML specification will be used when saving in the DOCX format.
enum class ASPOSE_WORDS_SHARED_CLASS OoxmlCompliance
{
    /// ECMA-376 1st Edition, 2006.
    Ecma376_2006 = 0,
    /// ISO/IEC 29500:2008 Transitional compliance level.
    Iso29500_2008_Transitional = 1,
    /// ISO/IEC 29500:2008 Strict compliance level.
    Iso29500_2008_Strict = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::OoxmlCompliance>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::OoxmlCompliance, const char_t*>, 3>& values();
};
