//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ImageSize.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Contains information about image size and resolution.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-images/">Working with Images</a> documentation article.
/// 
/// @sa Aspose::Words::Drawing::ImageData::get_ImageSize
class ASPOSE_WORDS_SHARED_CLASS ImageSize : public System::Object
{
    typedef ImageSize ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the width of the image in pixels.
    ASPOSE_WORDS_SHARED_API int32_t get_WidthPixels() const;
    /// Gets the height of the image in pixels.
    ASPOSE_WORDS_SHARED_API int32_t get_HeightPixels() const;
    /// Gets the horizontal resolution in DPI.
    ASPOSE_WORDS_SHARED_API double get_HorizontalResolution() const;
    /// Gets the vertical resolution in DPI.
    ASPOSE_WORDS_SHARED_API double get_VerticalResolution() const;
    /// Gets the width of the image in points. 1 point is 1/72 inch.
    ASPOSE_WORDS_SHARED_API double get_WidthPoints();
    /// Gets the height of the image in points. 1 point is 1/72 inch.
    ASPOSE_WORDS_SHARED_API double get_HeightPoints();

    /// Initializes width and height to the given values in pixels. Initializes resolution to 96 dpi.
    /// 
    /// @param widthPixels Width in pixels.
    /// @param heightPixels Height in pixels.
    ASPOSE_WORDS_SHARED_API ImageSize(int32_t widthPixels, int32_t heightPixels);
    /// Initializes width, height and resolution to the given values.
    /// 
    /// @param widthPixels Width in pixels.
    /// @param heightPixels Height in pixels.
    /// @param horizontalResolution Horizontal resolution in DPI.
    /// @param verticalResolution Vertical resolution in DPI.
    ASPOSE_WORDS_SHARED_API ImageSize(int32_t widthPixels, int32_t heightPixels, double horizontalResolution, double verticalResolution);

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<8,8,8,8>::type mField2;
    __TypeStub<8,8,8,8>::type mField3;

};

}
}
}
