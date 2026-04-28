//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ImageSaveOptions.h
#pragma once

#include <system/shared_ptr.h>
#include <drawing/size.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Saving/TiffCompression.h>
#include <Aspose.Words.Cpp/Saving/ImagePixelFormat.h>
#include <Aspose.Words.Cpp/Saving/ImageColorMode.h>
#include <Aspose.Words.Cpp/Saving/ImageBinarizationMethod.h>
#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Saving
{
class GraphicsQualityOptions;
class MetafileRenderingOptions;
class MultiPageLayout;
class PageSet;
}

}
}
namespace System
{
namespace Drawing
{
class Color;

}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify additional options when rendering document pages or shapes to images.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ImageSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef ImageSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the rendered document pages or shapes will be saved if this save options object is used.
    /// Can be a raster
    /// <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see>, <see cref="Aspose::Words::SaveFormat::Png">Png</see>, <see cref="Aspose::Words::SaveFormat::Bmp">Bmp</see>,
    /// <see cref="Aspose::Words::SaveFormat::Jpeg">Jpeg</see> or vector <see cref="Aspose::Words::SaveFormat::Emf">Emf</see>, <see cref="Aspose::Words::SaveFormat::Eps">Eps</see>,
    /// <see cref="Aspose::Words::SaveFormat::WebP">WebP</see>, <see cref="Aspose::Words::SaveFormat::Svg">Svg</see>.
    /// 
    /// The number of other options depends on the selected format.
    /// 
    /// Also, it is possible to save to SVG both via <see cref="Aspose::Words::Saving::ImageSaveOptions">ImageSaveOptions</see> and via <see cref="Aspose::Words::Saving::SvgSaveOptions">SvgSaveOptions</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_SaveFormat
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Gets or sets the pages to render.
    /// Default is all the pages in the document.
    /// 
    /// This property has effect only when rendering document pages. This property is ignored when rendering shapes to images.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PageSet> get_PageSet();
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_PageSet
    ASPOSE_WORDS_SHARED_API void set_PageSet(const System::SharedPtr<Aspose::Words::Saving::PageSet>& value);
    /// Gets or sets the background (paper) color for the generated images.
    /// The default value is <see cref="System::Drawing::Color::get_White">White</see>.
    /// 
    /// When rendering pages of a document that specifies its own background color,
    /// then the document background color will override the color specified by this property.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_PaperColor();
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_PaperColor
    ASPOSE_WORDS_SHARED_API void set_PaperColor(System::Drawing::Color value);
    /// Gets or sets the pixel format for the generated images.
    /// 
    /// This property has effect only when saving to raster image formats.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::ImagePixelFormat::Format32BppArgb">Format32BppArgb</see>.
    /// 
    /// Pixel format of the output image may differ from the set value
    /// because of work of GDI+.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ImagePixelFormat get_PixelFormat() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_PixelFormat
    ASPOSE_WORDS_SHARED_API void set_PixelFormat(Aspose::Words::Saving::ImagePixelFormat value);
    /// Gets or sets the horizontal resolution for the generated images, in dots per inch.
    /// 
    /// This property has effect only when saving to raster image formats and affects the output size in pixels.
    /// 
    /// The default value is 96.
    ASPOSE_WORDS_SHARED_API float get_HorizontalResolution() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_HorizontalResolution
    ASPOSE_WORDS_SHARED_API void set_HorizontalResolution(float value);
    /// Gets or sets the vertical resolution for the generated images, in dots per inch.
    /// 
    /// This property has effect only when saving to raster image formats and affects the output size in pixels.
    /// 
    /// The default value is 96.
    ASPOSE_WORDS_SHARED_API float get_VerticalResolution() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_VerticalResolution
    ASPOSE_WORDS_SHARED_API void set_VerticalResolution(float value);
    /// Sets both horizontal and vertical resolution for the generated images, in dots per inch.
    /// 
    /// This property has effect only when saving to raster image formats.
    ASPOSE_WORDS_SHARED_API void set_Resolution(float value);
    /// Gets or sets the size of a generated image in pixels.
    /// 
    /// This property has effect only when saving to raster image formats.
    /// 
    /// The default value is (0 x 0), which means that the size of the generated image will be calculated
    /// according to the size of the image in points, the specified resolution and scale.
    ASPOSE_WORDS_SHARED_API System::Drawing::Size get_ImageSize() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_ImageSize
    ASPOSE_WORDS_SHARED_API void set_ImageSize(System::Drawing::Size value);
    /// Gets or sets a value determining the quality of the generated JPEG images.
    /// 
    /// Has effect only when saving to JPEG.
    /// 
    /// Use this property to get or set the quality of generated images when saving in JPEG format.
    /// The value may vary from 0 to 100 where 0 means worst quality but maximum compression and 100
    /// means best quality but minimum compression.
    /// 
    /// The default value is 95.
    ASPOSE_WORDS_SHARED_API int32_t get_JpegQuality();
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_JpegQuality
    ASPOSE_WORDS_SHARED_API void set_JpegQuality(int32_t value);
    /// Gets or sets the type of compression to apply when saving generated images to the TIFF format.
    /// 
    /// Has effect only when saving to TIFF.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::TiffCompression::Lzw">Lzw</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::TiffCompression get_TiffCompression() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_TiffCompression
    ASPOSE_WORDS_SHARED_API void set_TiffCompression(Aspose::Words::Saving::TiffCompression value);
    /// Gets or sets the color mode for the generated images.
    /// 
    /// This property has effect only when saving to raster image formats.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::ImageColorMode::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ImageColorMode get_ImageColorMode() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_ImageColorMode
    ASPOSE_WORDS_SHARED_API void set_ImageColorMode(Aspose::Words::Saving::ImageColorMode value);
    /// Gets or sets the layout used when rendering multiple pages into a single output.
    /// 
    /// Use one of the factory methods of <see cref="Aspose::Words::Saving::MultiPageLayout">MultiPageLayout</see> to configure this property.
    /// 
    /// For <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see> the default value is <see cref="Aspose::Words::Saving::MultiPageLayout::TiffFrames">TiffFrames</see>.
    /// For other formats the default value is <see cref="Aspose::Words::Saving::MultiPageLayout::SinglePage">SinglePage</see>.
    /// 
    /// This property has effect only when saving to the following formats:
    /// <see cref="Aspose::Words::SaveFormat::Jpeg">Jpeg</see>, <see cref="Aspose::Words::SaveFormat::Gif">Gif</see>, <see cref="Aspose::Words::SaveFormat::Png">Png</see>,
    /// <see cref="Aspose::Words::SaveFormat::Bmp">Bmp</see>, <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see>, <see cref="Aspose::Words::SaveFormat::WebP">WebP</see>
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MultiPageLayout> get_PageLayout() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_PageLayout
    ASPOSE_WORDS_SHARED_API void set_PageLayout(const System::SharedPtr<Aspose::Words::Saving::MultiPageLayout>& value);
    /// Gets or sets the brightness for the generated images.
    /// 
    /// This property has effect only when saving to raster image formats.
    /// 
    /// The default value is 0.5. The value must be in the range between 0 and 1.
    ASPOSE_WORDS_SHARED_API float get_ImageBrightness() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_ImageBrightness
    ASPOSE_WORDS_SHARED_API void set_ImageBrightness(float value);
    /// Gets or sets the contrast for the generated images.
    /// 
    /// This property has effect only when saving to raster image formats.
    /// 
    /// The default value is 0.5. The value must be in the range between 0 and 1.
    ASPOSE_WORDS_SHARED_API float get_ImageContrast() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_ImageContrast
    ASPOSE_WORDS_SHARED_API void set_ImageContrast(float value);
    /// Gets the zoom factor for the generated images.
    ASPOSE_WORDS_SHARED_API float get_Scale() const;
    /// Sets the zoom factor for the generated images.
    ASPOSE_WORDS_SHARED_API void set_Scale(float value);
    /// Allows to specify how metafiles are treated in the rendered output.
    /// 
    /// When <see cref="Aspose::Words::Saving::MetafileRenderingMode::Vector">Vector</see> is specified, %Aspose.Words renders
    /// metafile to vector graphics using its own metafile rendering engine first and then renders vector
    /// graphics to the image.
    /// 
    /// When <see cref="Aspose::Words::Saving::MetafileRenderingMode::Bitmap">Bitmap</see> is specified, %Aspose.Words renders
    /// metafile directly to the image using the GDI+ metafile rendering engine.
    /// 
    /// GDI+ metafile rendering engine works faster, supports almost all metafile features but on low
    /// resolutions may produce inconsistent result when compared to the rest of vector graphics (especially for text)
    /// on the page. %Aspose.Words metafile rendering engine will produce more consistent result even
    /// on low resolutions but works slower and may inaccurately render complex metafiles.
    /// 
    /// The default value for <see cref="Aspose::Words::Saving::MetafileRenderingMode">MetafileRenderingMode</see> is <see cref="Aspose::Words::Saving::MetafileRenderingMode::Bitmap">Bitmap</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MetafileRenderingOptions> get_MetafileRenderingOptions();
    /// Gets or sets method used while converting images to 1 bpp format
    /// when <see cref="Aspose::Words::Saving::ImageSaveOptions::get_SaveFormat">SaveFormat</see> is <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see> and
    /// <see cref="Aspose::Words::Saving::ImageSaveOptions::get_TiffCompression">TiffCompression</see> is equal to <see cref="Aspose::Words::Saving::TiffCompression::Ccitt3">Ccitt3</see> or <see cref="Aspose::Words::Saving::TiffCompression::Ccitt4">Ccitt4</see>.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::ImageBinarizationMethod::Threshold">Threshold</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ImageBinarizationMethod get_TiffBinarizationMethod() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_TiffBinarizationMethod
    ASPOSE_WORDS_SHARED_API void set_TiffBinarizationMethod(Aspose::Words::Saving::ImageBinarizationMethod value);
    /// Gets or sets the threshold that determines the value
    /// of the binarization error in the Floyd-Steinberg method.
    /// when <see cref="Aspose::Words::Saving::ImageBinarizationMethod">ImageBinarizationMethod</see> is <see cref="Aspose::Words::Saving::ImageBinarizationMethod::FloydSteinbergDithering">FloydSteinbergDithering</see>.
    /// 
    /// The default value is 128.
    ASPOSE_WORDS_SHARED_API uint8_t get_ThresholdForFloydSteinbergDithering() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_ThresholdForFloydSteinbergDithering
    ASPOSE_WORDS_SHARED_API void set_ThresholdForFloydSteinbergDithering(uint8_t value);
    /// Allows to specify rendering mode and quality for the <see cref="System::Drawing::Graphics">Graphics</see> object.
    /// 
    /// Use this property to override the Graphics settings provided by %Aspose.Words engine by default.
    /// 
    /// It will take effect only when a document is being saved to an image-like format.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::GraphicsQualityOptions> get_GraphicsQualityOptions() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_GraphicsQualityOptions
    ASPOSE_WORDS_SHARED_API void set_GraphicsQualityOptions(const System::SharedPtr<Aspose::Words::Saving::GraphicsQualityOptions>& value);
    /// Gets or sets a value determining whether to use GDI+ or %Aspose.Words metafile renderer when saving to EMF.
    /// 
    /// If set to <c>%true</c> GDI+ metafile renderer is used. I.e. content is written to GDI+ graphics
    /// object and saved to metafile.
    /// 
    /// If set to <c>%false</c> %Aspose.Words metafile renderer is used. I.e. content is written directly
    /// to the metafile format with %Aspose.Words.
    /// 
    /// Has effect only when saving to EMF.
    /// 
    /// GDI+ saving works only on .NET.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseGdiEmfRenderer() const;
    /// Setter for Aspose::Words::Saving::ImageSaveOptions::get_UseGdiEmfRenderer
    ASPOSE_WORDS_SHARED_API void set_UseGdiEmfRenderer(bool value);

    /// Initializes a new instance of this class that can be used to save rendered images in the
    /// <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see>, <see cref="Aspose::Words::SaveFormat::Png">Png</see>, <see cref="Aspose::Words::SaveFormat::Bmp">Bmp</see>,
    /// <see cref="Aspose::Words::SaveFormat::Jpeg">Jpeg</see>, <see cref="Aspose::Words::SaveFormat::Emf">Emf</see>, <see cref="Aspose::Words::SaveFormat::Eps">Eps</see>,
    /// <see cref="Aspose::Words::SaveFormat::WebP">WebP</see> or <see cref="Aspose::Words::SaveFormat::Svg">Svg</see> format.
    /// 
    /// @param saveFormat Can be
    ///     <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see>, <see cref="Aspose::Words::SaveFormat::Png">Png</see>, <see cref="Aspose::Words::SaveFormat::Bmp">Bmp</see>,
    ///     <see cref="Aspose::Words::SaveFormat::Jpeg">Jpeg</see>, <see cref="Aspose::Words::SaveFormat::Emf">Emf</see>, <see cref="Aspose::Words::SaveFormat::Eps">Eps</see><see cref="Aspose::Words::SaveFormat::WebP">WebP</see> or <see cref="Aspose::Words::SaveFormat::Svg">Svg</see> format.
    ASPOSE_WORDS_SHARED_API ImageSaveOptions(Aspose::Words::SaveFormat saveFormat);

    /// Creates a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions> Clone();

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsShapingSupported() override;

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    System::SharedPtr<System::Object> mField7;
    __TypeStub<4,4,4,4>::type mField8;
    __TypeStub<4,4,4,4>::type mField9;
    __TypeStub<4,4,4,4>::type mField10;
    System::Drawing::Size mField11;
    __TypeStub<4,4,4,4>::type mField12;
    __TypeStub<1,1,1,1>::type mField13;
    __TypeStub<4,4,4,4>::type mField14;
    __TypeStub<1,1,1,1>::type mField15;
    __TypeStub<1,1,1,1>::type mField16;
    System::SharedPtr<System::Object> mField17;

};

}
}
}
