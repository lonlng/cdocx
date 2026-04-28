//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Rendering/NodeRendererBase.h
#pragma once

#include <system/object.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>
#include <drawing/rectangle_f.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Saving
{
class ImageSaveOptions;
class SvgSaveOptions;
}
}
}
namespace System
{
namespace Drawing
{
class Graphics;
class Rectangle;
class Size;
class SizeF;
}
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Rendering {

/// Base class for <see cref="Aspose::Words::Rendering::ShapeRenderer">ShapeRenderer</see> and <see cref="Aspose::Words::Rendering::OfficeMathRenderer">OfficeMathRenderer</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-shapes/">Working with Shapes</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS NodeRendererBase : public System::Object
{
    typedef NodeRendererBase ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the actual size of the shape in points.
    /// 
    /// This property returns the size of the actual (as rendered on the page) bounding box of the shape.
    /// The size takes into account shape rotation (if any).
    ASPOSE_WORDS_SHARED_API System::Drawing::SizeF get_SizeInPoints();
    /// Gets the actual bounds of the shape in points.
    /// 
    /// This property returns the actual (as rendered on the page) bounding box of the shape.
    /// The bounds takes into account shape rotation (if any).
    ASPOSE_WORDS_SHARED_API System::Drawing::RectangleF get_BoundsInPoints() const;
    /// Gets the opaque bounds of the shape in points.
    /// 
    /// This property returns the opaque (i.e. transparent parts of the shape are ignored) bounding box of the shape.
    /// The bounds takes the shape rotation into account.
    ASPOSE_WORDS_SHARED_API System::Drawing::RectangleF get_OpaqueBoundsInPoints();

    /// Calculates the size of the shape in pixels for a specified zoom factor and resolution.
    /// 
    /// This method converts <see cref="Aspose::Words::Rendering::NodeRendererBase::get_SizeInPoints">SizeInPoints</see> into size in pixels and it is useful
    /// when you want to create a bitmap for rendering the shape neatly onto the bitmap.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param dpi The resolution (horizontal and vertical) to convert from points to pixels (dots per inch).
    /// 
    /// @return The size of the shape in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Size GetSizeInPixels(float scale, float dpi);
    /// Calculates the size of the shape in pixels for a specified zoom factor and resolution.
    /// 
    /// This method converts <see cref="Aspose::Words::Rendering::NodeRendererBase::get_SizeInPoints">SizeInPoints</see> into size in pixels and it is useful
    /// when you want to create a bitmap for rendering the shape neatly onto the bitmap.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param horizontalDpi The horizontal resolution to convert from points to pixels (dots per inch).
    /// @param verticalDpi The vertical resolution to convert from points to pixels (dots per inch).
    /// 
    /// @return The size of the shape in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Size GetSizeInPixels(float scale, float horizontalDpi, float verticalDpi);
    /// Calculates the bounds of the shape in pixels for a specified zoom factor and resolution.
    /// 
    /// This method converts <see cref="Aspose::Words::Rendering::NodeRendererBase::get_BoundsInPoints">BoundsInPoints</see> into rectangle in pixels.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param dpi The resolution (horizontal and vertical) to convert from points to pixels (dots per inch).
    /// 
    /// @return The actual (as rendered on the page) bounding box of the shape in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Rectangle GetBoundsInPixels(float scale, float dpi);
    /// Calculates the bounds of the shape in pixels for a specified zoom factor and resolution.
    /// 
    /// This method converts <see cref="Aspose::Words::Rendering::NodeRendererBase::get_BoundsInPoints">BoundsInPoints</see> into rectangle in pixels.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param horizontalDpi The horizontal resolution to convert from points to pixels (dots per inch).
    /// @param verticalDpi The vertical resolution to convert from points to pixels (dots per inch).
    /// 
    /// @return The actual (as rendered on the page) bounding box of the shape in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Rectangle GetBoundsInPixels(float scale, float horizontalDpi, float verticalDpi);
    /// Calculates the opaque bounds of the shape in pixels for a specified zoom factor and resolution.
    /// 
    /// This method converts <see cref="Aspose::Words::Rendering::NodeRendererBase::get_OpaqueBoundsInPoints">OpaqueBoundsInPoints</see> into rectangle in pixels and it is useful
    /// when you want to create a bitmap for rendering the shape with only opaque part of the shape.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param dpi The resolution to convert from points to pixels (dots per inch).
    /// 
    /// @return The opaque rectangle of the shape in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Rectangle GetOpaqueBoundsInPixels(float scale, float dpi);
    /// Calculates the opaque bounds of the shape in pixels for a specified zoom factor and resolution.
    /// 
    /// This method converts <see cref="Aspose::Words::Rendering::NodeRendererBase::get_OpaqueBoundsInPoints">OpaqueBoundsInPoints</see> into rectangle in pixels and it is useful
    /// when you want to create a bitmap for rendering the shape with only opaque part of the shape.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param horizontalDpi The horizontal resolution to convert from points to pixels (dots per inch).
    /// @param verticalDpi The vertical resolution to convert from points to pixels (dots per inch).
    /// 
    /// @return The opaque rectangle of the shape in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Rectangle GetOpaqueBoundsInPixels(float scale, float horizontalDpi, float verticalDpi);
    /// Renders the shape into a <see cref="System::Drawing::Graphics">Graphics</see>
    /// object to a specified scale.
    /// 
    /// @param graphics The object where to render to.
    /// @param x The X coordinate (in world units) of the top left corner of the rendered shape.
    /// @param y The Y coordinate (in world units) of the top left corner of the rendered shape.
    /// @param scale The scale for rendering the shape (1.0 is 100\%).
    /// 
    /// @return The width and height (in world units) of the rendered shape.
    ASPOSE_WORDS_SHARED_API System::Drawing::SizeF RenderToScale(const System::SharedPtr<System::Drawing::Graphics>& graphics, float x, float y, float scale);
    /// Renders the shape into a <see cref="System::Drawing::Graphics">Graphics</see>
    /// object to a specified size.
    /// 
    /// @param graphics The object where to render to.
    /// @param x The X coordinate (in world units) of the top left corner of the rendered shape.
    /// @param y The Y coordinate (in world units) of the top left corner of the rendered shape.
    /// @param width The maximum width (in world units) that can be occupied by the rendered shape.
    /// @param height The maximum height (in world units) that can be occupied by the rendered shape.
    /// 
    /// @return The scale that was automatically calculated for the rendered shape to fit the specified size.
    ASPOSE_WORDS_SHARED_API float RenderToSize(const System::SharedPtr<System::Drawing::Graphics>& graphics, float x, float y, float width, float height);
    /// Renders the shape into an image and saves into a file.
    /// 
    /// @param fileName The name for the image file. If a file with the specified name already exists, the existing file is overwritten.
    /// @param saveOptions Specifies the options that control how the shape is rendered and saved. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void Save(const System::String& fileName, System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions> saveOptions);
    /// Renders the shape into an SVG image and saves into a file.
    /// 
    /// @param fileName The name for the image file. If a file with the specified name already exists, the existing file is overwritten.
    /// @param saveOptions Specifies the options that control how the shape is rendered and saved. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void Save(const System::String& fileName, System::SharedPtr<Aspose::Words::Saving::SvgSaveOptions> saveOptions);
    /// Renders the shape into an image and saves into a stream.
    /// 
    /// @param stream The stream where to save the image of the shape.
    /// @param saveOptions Specifies the options that control how the shape is rendered and saved. Can be <c>%null</c>.
    ///     If this is <c>%null</c>, the image will be saved in the PNG format.
    ASPOSE_WORDS_SHARED_API void Save(const System::SharedPtr<System::IO::Stream>& stream, System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions> saveOptions);
    /// Renders the shape into an SVG image and saves into a stream.
    /// 
    /// @param stream The stream where to save the SVG image of the shape.
    /// @param saveOptions Specifies the options that control how the shape is rendered and saved. Can be <c>%null</c>.
    ///     If this is <c>%null</c>, the image will be saved with the default options.
    ASPOSE_WORDS_SHARED_API void Save(const System::SharedPtr<System::IO::Stream>& stream, System::SharedPtr<Aspose::Words::Saving::SvgSaveOptions> saveOptions);

    ASPOSE_WORDS_SHARED_API NodeRendererBase();

    template <typename CharType, typename Traits>
    void Save(std::basic_ostream<CharType, Traits>& stream, System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions> saveOptions)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        Save(streamWrapper, saveOptions);
    }

    template <typename CharType, typename Traits>
    void Save(std::basic_ostream<CharType, Traits>& stream, System::SharedPtr<Aspose::Words::Saving::SvgSaveOptions> saveOptions)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        Save(streamWrapper, saveOptions);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::Drawing::RectangleF mField2;
    System::Drawing::RectangleF mField3;

};

}
}
}
