//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ConvertUtil.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Provides helper functions to convert between various measurement units.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/convert-between-measurement-units/">Convert Between Measurement Units</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ConvertUtil
{
    typedef ConvertUtil ThisType;

public:

    /// Converts points to pixels at 96 dpi.
    /// 
    /// @param points The value to convert.
    static ASPOSE_WORDS_SHARED_API double PointToPixel(double points);
    /// Converts points to pixels at the specified pixel resolution.
    /// 
    /// @param points The value to convert.
    /// @param resolution The dpi (dots per inch) resolution.
    static ASPOSE_WORDS_SHARED_API double PointToPixel(double points, double resolution);
    /// Converts pixels to points at 96 dpi.
    /// 
    /// @param pixels The value to convert.
    static ASPOSE_WORDS_SHARED_API double PixelToPoint(double pixels);
    /// Converts pixels to points at the specified pixel resolution.
    /// 
    /// @param pixels The value to convert.
    /// @param resolution The dpi (dots per inch) resolution.
    static ASPOSE_WORDS_SHARED_API double PixelToPoint(double pixels, double resolution);
    /// Converts pixels from one resolution to another.
    /// 
    /// @param pixels The value to convert.
    /// @param oldDpi The current dpi (dots per inch) resolution.
    /// @param newDpi The new dpi (dots per inch) resolution.
    static ASPOSE_WORDS_SHARED_API int32_t PixelToNewDpi(double pixels, double oldDpi, double newDpi);
    /// Converts inches to points.
    /// 
    /// @param inches The value to convert.
    static ASPOSE_WORDS_SHARED_API double InchToPoint(double inches);
    /// Converts points to inches.
    /// 
    /// @param points The value to convert.
    static ASPOSE_WORDS_SHARED_API double PointToInch(double points);
    /// Converts millimeters to points.
    /// 
    /// @param millimeters The value to convert.
    static ASPOSE_WORDS_SHARED_API double MillimeterToPoint(double millimeters);

public:
    ConvertUtil() = delete;
};

}
}
