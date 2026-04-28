//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Watermark.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/WatermarkType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class ImageWatermarkOptions;

class TextWatermarkOptions;
}
}
namespace System
{
namespace Drawing
{
class Image;

}
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

/// Represents class to work with document watermark.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-watermark/">Working with Watermark</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Watermark final : public System::Object
{
    typedef Watermark ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the watermark type.
    ASPOSE_WORDS_SHARED_API Aspose::Words::WatermarkType get_Type();

    /// Adds Text watermark into the document.
    /// 
    /// @param text Text that is displayed as a watermark.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when the text length is out of range or the text contains only whitespaces.
    /// @exception System::ArgumentNullException Throws when the text is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void SetText(const System::String& text);
    /// Adds Text watermark into the document.
    /// 
    /// @param text Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when the text length is out of range or the text contain only whitespaces.
    /// @exception System::ArgumentNullException Throws when the text is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void SetText(const System::String& text, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds Image watermark into the document.
    /// 
    /// @param image Image that is displayed as a watermark.
    /// 
    /// @exception System::ArgumentNullException Throws when the image is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::Drawing::Image>& image);
    /// Adds Image watermark into the document.
    /// 
    /// @param image Image that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    /// 
    /// @exception System::ArgumentNullException Throws when the image is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::Drawing::Image>& image, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds Image watermark into the document.
    /// 
    /// @param imagePath Path to the image file that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    /// 
    /// @exception System::ArgumentNullException Throws when the path is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::String& imagePath, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds Image watermark into the document.
    /// 
    /// @param imageStream The stream containing the image data that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    /// 
    /// @exception System::ArgumentNullException Throws when the path is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& imageStream, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Removes the watermark.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
