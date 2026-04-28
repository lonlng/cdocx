//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Watermarker.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/LowCode/Processor.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class ImageWatermarkOptions;
namespace LowCode
{
class WatermarkerContext;
}
namespace Saving
{
class ImageSaveOptions;
class SaveOptions;
}
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
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Provides methods intended to insert watermarks into the documents.
class ASPOSE_WORDS_SHARED_CLASS Watermarker : public Aspose::Words::LowCode::Processor
{
    typedef Watermarker ThisType;
    typedef Aspose::Words::LowCode::Processor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates new instance of the watermarker processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Watermarker> Create(const System::SharedPtr<Aspose::Words::LowCode::WatermarkerContext>& context);
    /// Adds a text watermark into the document.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::String& inputFileName, const System::String& outputFileName, const System::String& watermarkText);
    /// Adds a text watermark into the document with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::String& inputFileName, const System::String& outputFileName, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds a text watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& watermarkText);
    /// Adds a text watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds a text watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& watermarkText);
    /// Adds a text watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds a text watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::String& watermarkText);
    /// Adds a text watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds a text watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& watermarkText);
    /// Adds a text watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API void SetText(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds an image watermark into the document.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param watermarkImageFileName Image that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::String& inputFileName, const System::String& outputFileName, const System::String& watermarkImageFileName);
    /// Adds an image watermark into the document with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param watermarkImageFileName Image that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::String& inputFileName, const System::String& outputFileName, const System::String& watermarkImageFileName, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param watermarkImageFileName Image that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& watermarkImageFileName);
    /// Adds an image watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param watermarkImageFileName Image that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& watermarkImageFileName, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param watermarkImageFileName Image that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& watermarkImageFileName);
    /// Adds an image watermark into the document with options and specified save format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param watermarkImageFileName Image that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& watermarkImageFileName, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param watermarkImage Image that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::Drawing::Image>& watermarkImage);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param watermarkImage Image that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::Drawing::Image>& watermarkImage, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param watermarkImage Image that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::Drawing::Image>& watermarkImage);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param watermarkImage Image that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::Drawing::Image>& watermarkImage, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param watermarkImageStream Image stream that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::IO::Stream>& watermarkImageStream);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param watermarkImageStream Image stream that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::IO::Stream>& watermarkImageStream, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param watermarkImageStream Image stream that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::IO::Stream>& watermarkImageStream);
    /// Adds an image watermark into the document from streams with options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param watermarkImageStream Image stream that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API void SetImage(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::IO::Stream>& watermarkImageStream, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds a text watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& watermarkText);
    /// Adds a text watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds a text watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputStream The input file stream.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& watermarkText);
    /// Adds a text watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputStream The input file stream.
    /// @param saveOptions The save options.
    /// @param watermarkText Text that is displayed as a watermark.
    /// @param options Defines additional options for the text watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& watermarkText, const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& options);
    /// Adds an image watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param watermarkImageBytes Image bytes that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::ArrayPtr<uint8_t>& watermarkImageBytes);
    /// Adds an image watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param watermarkImageBytes Image bytes that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::ArrayPtr<uint8_t>& watermarkImageBytes, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);
    /// Adds an image watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputStream The input stream.
    /// @param saveOptions The save options.
    /// @param watermarkImageStream Image stream that is displayed as a watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::SharedPtr<System::IO::Stream>& watermarkImageStream);
    /// Adds an image watermark into the document with options. Renders the output to images.
    /// 
    /// @param inputStream The input stream.
    /// @param saveOptions The save options.
    /// @param watermarkImageStream Image stream that is displayed as a watermark.
    /// @param options Defines additional options for the image watermark.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> SetWatermarkToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::SharedPtr<System::IO::Stream>& watermarkImageStream, const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& options);

protected:

    ASPOSE_WORDS_SHARED_API void ExecuteCore() override;
    ASPOSE_WORDS_SHARED_API void CheckArgumentsSet() override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
