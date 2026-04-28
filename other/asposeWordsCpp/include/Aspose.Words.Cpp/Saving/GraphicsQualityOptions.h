//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/GraphicsQualityOptions.h
#pragma once

#include <system/object.h>
#include <system/nullable.h>
#include <drawing/text/text_rendering_hint.h>
#include <drawing/drawing2d/smoothing_mode.h>
#include <drawing/drawing2d/interpolation_mode.h>
#include <drawing/drawing2d/compositing_quality.h>
#include <drawing/drawing2d/compositing_mode.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Drawing
{
class StringFormat;
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify additional <see cref="System::Drawing::Graphics">Graphics</see> quality options.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS GraphicsQualityOptions : public System::Object
{
    typedef GraphicsQualityOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets text layout information (such as alignment, orientation and tab stops) display manipulations
    /// (such as ellipsis insertion and national digit substitution) and OpenType features.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Drawing::StringFormat>& get_StringFormat() const;
    /// Sets text layout information (such as alignment, orientation and tab stops) display manipulations
    /// (such as ellipsis insertion and national digit substitution) and OpenType features.
    ASPOSE_WORDS_SHARED_API void set_StringFormat(const System::SharedPtr<System::Drawing::StringFormat>& value);
    /// Gets a value that specifies how composited images are drawn to this Graphics.
    ASPOSE_WORDS_SHARED_API System::Nullable<System::Drawing::Drawing2D::CompositingMode> get_CompositingMode() const;
    /// Sets a value that specifies how composited images are drawn to this Graphics.
    ASPOSE_WORDS_SHARED_API void set_CompositingMode(System::Nullable<System::Drawing::Drawing2D::CompositingMode> value);
    /// Gets the rendering quality of composited images drawn to this Graphics.
    ASPOSE_WORDS_SHARED_API System::Nullable<System::Drawing::Drawing2D::CompositingQuality> get_CompositingQuality() const;
    /// Sets the rendering quality of composited images drawn to this Graphics.
    ASPOSE_WORDS_SHARED_API void set_CompositingQuality(System::Nullable<System::Drawing::Drawing2D::CompositingQuality> value);
    /// Gets the interpolation mode associated with this Graphics.
    ASPOSE_WORDS_SHARED_API System::Nullable<System::Drawing::Drawing2D::InterpolationMode> get_InterpolationMode() const;
    /// Sets the interpolation mode associated with this Graphics.
    ASPOSE_WORDS_SHARED_API void set_InterpolationMode(System::Nullable<System::Drawing::Drawing2D::InterpolationMode> value);
    /// Gets the rendering quality for this Graphics.
    ASPOSE_WORDS_SHARED_API System::Nullable<System::Drawing::Drawing2D::SmoothingMode> get_SmoothingMode() const;
    /// Sets the rendering quality for this Graphics.
    ASPOSE_WORDS_SHARED_API void set_SmoothingMode(System::Nullable<System::Drawing::Drawing2D::SmoothingMode> value);
    /// Gets the rendering mode for text associated with this Graphics.
    ASPOSE_WORDS_SHARED_API System::Nullable<System::Drawing::Text::TextRenderingHint> get_TextRenderingHint() const;
    /// Sets the rendering mode for text associated with this Graphics.
    ASPOSE_WORDS_SHARED_API void set_TextRenderingHint(System::Nullable<System::Drawing::Text::TextRenderingHint> value);
    /// Gets or sets a flag indicating whether WrapMode is TileFlipXY.
    /// 
    /// The <see cref="System::Drawing::Drawing2D::WrapMode">WrapMode</see> specifies how a texture or gradient is tiled when it is smaller
    /// than the area being filled.
    /// 
    /// By default uses <see cref="System::Drawing::Drawing2D::WrapMode::Tile">Tile</see> (specifies tiling without flipping).
    /// This causes inaccurate rendering of the scaled image(with high resolution).
    /// 
    /// This property allows to switch WrapMode to <see cref="System::Drawing::Drawing2D::WrapMode::TileFlipXY">TileFlipXY</see> (specifies that tiles are
    /// flipped horizontally as you move along a row and flipped vertically as you move along a column).
    ASPOSE_WORDS_SHARED_API bool get_UseTileFlipMode() const;
    /// Setter for Aspose::Words::Saving::GraphicsQualityOptions::get_UseTileFlipMode
    ASPOSE_WORDS_SHARED_API void set_UseTileFlipMode(bool value);

    ASPOSE_WORDS_SHARED_API GraphicsQualityOptions();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::Nullable<System::Drawing::Drawing2D::CompositingMode> mField1;
    System::Nullable<System::Drawing::Drawing2D::CompositingQuality> mField2;
    System::Nullable<System::Drawing::Drawing2D::InterpolationMode> mField3;
    System::Nullable<System::Drawing::Drawing2D::SmoothingMode> mField4;
    System::Nullable<System::Drawing::Text::TextRenderingHint> mField5;
    __TypeStub<1,1,1,1>::type mField6;

};

}
}
}
