//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ImageData.h
#pragma once

#include <system/io/std_stream_wrappers.h>
#include <system/array.h>
#include <mutex>
#include <memory>
#include <iostream>
#include <cstdint>

#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/Drawing/ImageType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class BorderCollection;
enum class BorderType;

namespace Drawing
{

class ImageSize;

}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class SortedList;
}
}
namespace Drawing
{
class Color;
class Image;
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Defines an image for a shape.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-images/">Working with Images</a> documentation article.
/// 
/// Use the <see cref="Aspose::Words::Drawing::Shape::get_ImageData">ImageData</see> property to access and modify the image inside a shape.
/// You do not create instances of the <see cref="Aspose::Words::Drawing::ImageData">ImageData</see> class directly.
/// 
/// An image can be stored inside a shape, linked to external file or both (linked and stored in the document).
/// 
/// Regardless of whether the image is stored inside the shape or linked, you can always access the actual
/// image using the <see cref="Aspose::Words::Drawing::ImageData::ToByteArray">ToByteArray</see>, <see cref="Aspose::Words::Drawing::ImageData::ToStream">ToStream</see>, <see cref="Aspose::Words::Drawing::ImageData::ToImage">ToImage</see> or <see cref="Aspose::Words::Drawing::ImageData::Save(System::String)">Save()</see> methods.
/// If the image is stored inside the shape, you can also directly access it using the <see cref="Aspose::Words::Drawing::ImageData::get_ImageBytes">ImageBytes</see> property.
/// 
/// To store an image inside a shape use the <see cref="Aspose::Words::Drawing::ImageData::SetImage(System::String)">SetImage()</see> method. To link an image to a shape, set the <see cref="Aspose::Words::Drawing::ImageData::get_SourceFullName">SourceFullName</see> property.
class ASPOSE_WORDS_SHARED_CLASS ImageData : public Aspose::Words::IBorderAttrSource
{
    typedef ImageData ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the raw bytes of the image stored in the shape.
    /// 
    /// Setting the value to <c>%null</c> or an empty array will remove the image from the shape.
    /// 
    /// Returns <c>%null</c> if the image is not stored in the document (e.g the image is probably linked in this case).
    /// 
    /// @sa Aspose::Words::Drawing::ImageData::SetImage(System::String)
    /// @sa Aspose::Words::Drawing::ImageData::ToByteArray
    /// @sa Aspose::Words::Drawing::ImageData::ToImage
    /// @sa Aspose::Words::Drawing::ImageData::ToStream
    /// @sa Aspose::Words::Drawing::ImageData::Save(System::String)
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_ImageBytes();
    /// Setter for Aspose::Words::Drawing::ImageData::get_ImageBytes
    ASPOSE_WORDS_SHARED_API void set_ImageBytes(const System::ArrayPtr<uint8_t>& value);
    /// Returns <c>%true</c> if the shape has image bytes or links an image.
    ASPOSE_WORDS_SHARED_API bool get_HasImage();
    /// Gets the information about image size and resolution.
    /// 
    /// If the image is linked only and not stored in the document, returns zero size.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::ImageSize> get_ImageSize();
    /// Gets the type of the image.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ImageType get_ImageType();
    /// Returns <c>%true</c> if the image is linked to the shape (when <see cref="Aspose::Words::Drawing::ImageData::get_SourceFullName">SourceFullName</see> is specified).
    ASPOSE_WORDS_SHARED_API bool get_IsLink();
    /// Returns <c>%true</c> if the image is linked and not stored in the document.
    ASPOSE_WORDS_SHARED_API bool get_IsLinkOnly();
    /// Gets or sets the path and name of the source file for the linked image.
    /// 
    /// The default value is an empty string.
    /// 
    /// If <see cref="Aspose::Words::Drawing::ImageData::get_SourceFullName">SourceFullName</see> is not an empty string, the image is linked.
    ASPOSE_WORDS_SHARED_API System::String get_SourceFullName();
    /// Setter for Aspose::Words::Drawing::ImageData::get_SourceFullName
    ASPOSE_WORDS_SHARED_API void set_SourceFullName(const System::String& value);
    /// Defines the title of an image.
    /// 
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Title();
    /// Defines the title of an image.
    /// 
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_Title(const System::String& value);
    /// Defines the fraction of picture removal from the top side.
    /// 
    /// The amount of cropping can range from -1.0 to 1.0. The default value is 0. Note
    /// that a value of 1 will display no picture at all. Negative values will result in
    /// the picture being squeezed inward from the edge being cropped (the empty space
    /// between the picture and the cropped edge will be filled by the fill color of the
    /// shape). Positive values less than 1 will result in the remaining picture being
    /// stretched to fit the shape.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API double get_CropTop();
    /// Setter for Aspose::Words::Drawing::ImageData::get_CropTop
    ASPOSE_WORDS_SHARED_API void set_CropTop(double value);
    /// Defines the fraction of picture removal from the bottom side.
    /// 
    /// The amount of cropping can range from -1.0 to 1.0. The default value is 0. Note
    /// that a value of 1 will display no picture at all. Negative values will result in
    /// the picture being squeezed inward from the edge being cropped (the empty space
    /// between the picture and the cropped edge will be filled by the fill color of the
    /// shape). Positive values less than 1 will result in the remaining picture being
    /// stretched to fit the shape.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API double get_CropBottom();
    /// Setter for Aspose::Words::Drawing::ImageData::get_CropBottom
    ASPOSE_WORDS_SHARED_API void set_CropBottom(double value);
    /// Defines the fraction of picture removal from the left side.
    /// 
    /// The amount of cropping can range from -1.0 to 1.0. The default value is 0. Note
    /// that a value of 1 will display no picture at all. Negative values will result in
    /// the picture being squeezed inward from the edge being cropped (the empty space
    /// between the picture and the cropped edge will be filled by the fill color of the
    /// shape). Positive values less than 1 will result in the remaining picture being
    /// stretched to fit the shape.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API double get_CropLeft();
    /// Setter for Aspose::Words::Drawing::ImageData::get_CropLeft
    ASPOSE_WORDS_SHARED_API void set_CropLeft(double value);
    /// Defines the fraction of picture removal from the right side.
    /// 
    /// The amount of cropping can range from -1.0 to 1.0. The default value is 0. Note
    /// that a value of 1 will display no picture at all. Negative values will result in
    /// the picture being squeezed inward from the edge being cropped (the empty space
    /// between the picture and the cropped edge will be filled by the fill color of the
    /// shape). Positive values less than 1 will result in the remaining picture being
    /// stretched to fit the shape.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API double get_CropRight();
    /// Setter for Aspose::Words::Drawing::ImageData::get_CropRight
    ASPOSE_WORDS_SHARED_API void set_CropRight(double value);
    /// Gets the collection of borders of the image. Borders only have effect for inline images.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Defines the color value of the image that will be treated as transparent.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_ChromaKey();
    /// Defines the color value of the image that will be treated as transparent.
    /// 
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API void set_ChromaKey(System::Drawing::Color value);
    /// Gets or sets the brightness of the picture.
    /// The value for this property must be a number from 0.0 (dimmest) to 1.0 (brightest).
    /// 
    /// The default value is 0.5.
    ASPOSE_WORDS_SHARED_API double get_Brightness();
    /// Setter for Aspose::Words::Drawing::ImageData::get_Brightness
    ASPOSE_WORDS_SHARED_API void set_Brightness(double value);
    /// Gets or sets the contrast for the specified picture. The value
    /// for this property must be a number from 0.0 (the least contrast) to 1.0 (the greatest contrast).
    /// 
    /// The default value is 0.5.
    ASPOSE_WORDS_SHARED_API double get_Contrast();
    /// Setter for Aspose::Words::Drawing::ImageData::get_Contrast
    ASPOSE_WORDS_SHARED_API void set_Contrast(double value);
    /// Determines whether an image will be displayed in black and white.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_BiLevel();
    /// Determines whether an image will be displayed in black and white.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_BiLevel(bool value);
    /// Determines whether a picture will display in grayscale mode.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_GrayScale();
    /// Determines whether a picture will display in grayscale mode.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_GrayScale(bool value);

    /// Sets the image that the shape displays.
    /// 
    /// @param image The image object.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::Drawing::Image>& image);
    /// Sets the image that the shape displays.
    /// 
    /// @param stream The stream that contains the image.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& stream);
    /// Sets the image that the shape displays.
    /// 
    /// @param fileName The image file. Can be a file name or a URL.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::String& fileName);
    /// Gets the image stored in the shape as a <see cref="System::Drawing::Image">Image</see> object.
    /// 
    /// A new <see cref="System::Drawing::Image">Image</see> object is created every time this method is called.
    /// 
    /// It is the responsibility of the caller to dispose the image object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Drawing::Image> ToImage();
    /// Creates and returns a stream that contains the image bytes.
    /// 
    /// If the image bytes are stored in the shape, creates and returns a <see cref="System::IO::MemoryStream">MemoryStream</see> object.
    /// 
    /// If the image is linked and stored in a file, opens the file and returns a <see cref="System::IO::FileStream">FileStream</see> object.
    /// 
    /// If the image is linked and stored in an external URL, downloads the file and returns a <see cref="System::IO::MemoryStream">MemoryStream</see> object.
    /// 
    /// Is it the responsibility of the caller to dispose the stream object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> ToStream();
    /// Returns image bytes for any image regardless whether the image is stored or linked.
    /// 
    /// If the image is linked, downloads the image every time it is called.
    /// 
    /// @sa Aspose::Words::Drawing::ImageData::get_ImageBytes
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> ToByteArray();
    /// Saves the image into the specified stream.
    /// 
    /// Is it the responsibility of the caller to dispose the stream object.
    /// 
    /// @param stream The stream where to save the image to.
    ASPOSE_WORDS_SHARED_API void Save(const System::SharedPtr<System::IO::Stream>& stream);
    /// Saves the image into a file.
    /// 
    /// @param fileName The file name where to save the image.
    ASPOSE_WORDS_SHARED_API void Save(const System::String& fileName);
    /// Fits the image data to Shape frame so that the aspect ratio of the image data matches the aspect ratio of Shape frame.
    ASPOSE_WORDS_SHARED_API void FitImageToShape();

    template <typename CharType, typename Traits>
    void SetImage(std::basic_istream<CharType, Traits>& stream)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        SetImage(streamWrapper);
    }

    template <typename CharType, typename Traits>
    void Save(std::basic_ostream<CharType, Traits>& stream)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        Save(streamWrapper);
    }

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ImageData();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<System::Object> mField2;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;

};

}
}
}
