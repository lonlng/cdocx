//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/OdtSaveMeasureUnit.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specified units of measure to apply to measurable document content such as shape, widths and other during saving.
enum class ASPOSE_WORDS_SHARED_CLASS OdtSaveMeasureUnit
{
    /// Specifies that the document content is saved using centimeters.
    Centimeters = 0,
    /// Specifies that the document content is saved using inches.
    Inches = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::OdtSaveMeasureUnit>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::OdtSaveMeasureUnit, const char_t*>, 2>& values();
};
