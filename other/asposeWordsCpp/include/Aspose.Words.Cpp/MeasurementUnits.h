//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MeasurementUnits.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the unit of measurement.
enum class ASPOSE_WORDS_SHARED_CLASS MeasurementUnits
{
    /// Inches.
    Inches = 0,
    /// Centimeters.
    Centimeters = 1,
    /// Millimeters.
    Millimeters = 2,
    /// Points.
    Points = 3,
    /// Picas (commonly used in traditional typewriter font spacing).
    Picas = 4
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::MeasurementUnits>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::MeasurementUnits, const char_t*>, 5>& values();
};
