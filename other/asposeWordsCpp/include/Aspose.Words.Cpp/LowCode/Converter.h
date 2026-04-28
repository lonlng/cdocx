//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Converter.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/LowCode/Processor.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
namespace Loading
{
class LoadOptions;
}
namespace LowCode
{
class ConverterContext;
}
namespace Saving
{
class ImageSaveOptions;
class SaveOptions;
}
}
}
namespace System
{
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Represents a group of methods intended to convert a variety of different types of documents using a single line of code.
/// 
/// The specified input and output files or streams, along with the desired save format,
/// are used to convert the given input document of the one format into the output document
/// of the other specified format.
/// 
/// The convert functionality supports over 35+ different file formats.
/// 
/// The <see cref="Aspose::Words::LowCode::Converter::ConvertToImages(System::String, Aspose::Words::SaveFormat)">ConvertToImages()</see> group of methods are designed to transform documents into images,
/// with each page being converted into a separate image file. These methods also convert PDF documents directly to fixed-page formats
/// without loading them into the document model, which enhances both performance and accuracy.
/// 
/// With <see cref="Aspose::Words::Saving::ImageSaveOptions::get_PageSet">PageSet</see>, you can specify a particular set of pages to convert into images.
class ASPOSE_WORDS_SHARED_CLASS Converter : public Aspose::Words::LowCode::Processor
{
    typedef Converter ThisType;
    typedef Aspose::Words::LowCode::Processor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates new instance of the converter processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Converter> Create();
    /// Creates new instance of the converter processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Converter> Create(const System::SharedPtr<Aspose::Words::LowCode::ConverterContext>& context);
    /// Converts the given input document into the output document using specified input output file names and its extensions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFile The input file name.
    /// @param outputFile The output file name.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::String& inputFile, const System::String& outputFile);
    /// Converts the given input document into the output document using specified input output file names and the final document format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFile The input file name.
    /// @param outputFile The output file name.
    /// @param saveFormat The save format.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::String& inputFile, const System::String& outputFile, Aspose::Words::SaveFormat saveFormat);
    /// Converts the given input document into the output document using specified input output file names and save options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFile The input file name.
    /// @param outputFile The output file name.
    /// @param saveOptions The save options.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::String& inputFile, const System::String& outputFile, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Converts the given input document into the output document using specified input output file names its load/save options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFile The input file name.
    /// @param loadOptions The input document load options.
    /// @param outputFile The output file name.
    /// @param saveOptions The save options.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::String& inputFile, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions, const System::String& outputFile, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Converts the given input document into a single output document using specified input and output streams.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat);
    /// Converts the given input document into a single output document using specified input and output streams.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input streams.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Converts the given input document into a single output document using specified input and output streams.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input streams.
    /// @param loadOptions The input document load options.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    static ASPOSE_WORDS_SHARED_API void Convert(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Converts the pages of the specified input file to image files.
    /// 
    /// @param inputFile The input file name.
    /// @param outputFile The output file name used to generate file name for page images using rule "outputFile_pageIndex.extension"
    static ASPOSE_WORDS_SHARED_API void ConvertToImages(const System::String& inputFile, const System::String& outputFile);
    /// Converts the pages of the specified input file to image files in the specified format.
    /// 
    /// @param inputFile The input file name.
    /// @param outputFile The output file name used to generate file name for page images using rule "outputFile_pageIndex.extension"
    /// @param saveFormat Save format. Only image save formats are allowed.
    static ASPOSE_WORDS_SHARED_API void ConvertToImages(const System::String& inputFile, const System::String& outputFile, Aspose::Words::SaveFormat saveFormat);
    /// Converts the pages of the specified input file to image files using the specified save options.
    /// 
    /// @param inputFile The input file name.
    /// @param outputFile The output file name used to generate file name for page images using rule "outputFile_pageIndex.extension"
    /// @param saveOptions Image save options.
    static ASPOSE_WORDS_SHARED_API void ConvertToImages(const System::String& inputFile, const System::String& outputFile, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions);
    /// Converts the pages of the specified input file to image files using the provided load and save options.
    /// 
    /// @param inputFile The input file name.
    /// @param loadOptions The input document load options.
    /// @param outputFile The output file name used to generate file name for page images using rule "outputFile_pageIndex.extension"
    /// @param saveOptions Image save options.
    static ASPOSE_WORDS_SHARED_API void ConvertToImages(const System::String& inputFile, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions, const System::String& outputFile, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions);
    /// Converts the pages of the specified input file to images in the specified format and returns an array of streams containing the images.
    /// 
    /// @param inputFile The input file name.
    /// @param saveFormat Save format. Only image save formats are allowed.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::String& inputFile, Aspose::Words::SaveFormat saveFormat);
    /// Converts the pages of the specified input file to images using the specified save options and returns an array of streams containing the images.
    /// 
    /// @param inputFile The input file name.
    /// @param saveOptions Image save options.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::String& inputFile, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions);
    /// Converts the pages of the specified input stream to images in the specified format and returns an array of streams containing the images.
    /// 
    /// @param inputStream The input stream.
    /// @param saveFormat Save format. Only image save formats are allowed.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::SharedPtr<System::IO::Stream>& inputStream, Aspose::Words::SaveFormat saveFormat);
    /// Converts the pages of the specified input stream to images using the specified save options and returns an array of streams containing the images.
    /// 
    /// @param inputStream The input stream.
    /// @param saveOptions Image save options.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions);
    /// Converts the pages of the specified input stream to images using the provided load and save options, and returns an array of streams containing the images.
    /// 
    /// @param inputStream The input stream.
    /// @param loadOptions The input document load options.
    /// @param saveOptions Image save options.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions);
    /// Converts the pages of the specified document to images in the specified format and returns an array of streams containing the images.
    /// 
    /// @param doc The input document.
    /// @param saveFormat Save format. Only image save formats are allowed.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::SharedPtr<Aspose::Words::Document>& doc, Aspose::Words::SaveFormat saveFormat);
    /// Converts the pages of the specified document to images using the specified save options and returns an array of streams containing the images.
    /// 
    /// @param doc The input document.
    /// @param saveOptions Image save options.
    /// 
    /// @return Returns array of image streams. The streams should be disposed by the end user.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(const System::SharedPtr<Aspose::Words::Document>& doc, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions);

protected:

    ASPOSE_WORDS_SHARED_API void ExecuteCore() override;

private:

};

}
}
}
