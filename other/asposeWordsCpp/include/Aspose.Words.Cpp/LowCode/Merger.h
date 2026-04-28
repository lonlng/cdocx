//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Merger.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/LowCode/Processor.h>
#include <Aspose.Words.Cpp/LowCode/MergeFormatMode.h>
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

class MergerContext;
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
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Represents a group of methods intended to merge a variety of different types of documents into a single output document.
/// 
/// The specified input and output files or streams, along with the desired merge and save options,
/// are used to merge the given input documents into a single output document.
/// 
/// The merging functionality supports over 35 different file formats.
class ASPOSE_WORDS_SHARED_CLASS Merger : public Aspose::Words::LowCode::Processor
{
    typedef Merger ThisType;
    typedef Aspose::Words::LowCode::Processor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates new instance of the mail merger processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Merger> Create();
    /// Creates new instance of the mail merger processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Merger> Create(const System::SharedPtr<Aspose::Words::LowCode::MergerContext>& context);
    /// Merges the given input documents into a single output document using specified input
    /// and output file names using <see cref="Aspose::Words::LowCode::MergeFormatMode::KeepSourceFormatting">KeepSourceFormatting</see>.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param outputFile The output file name.
    /// @param inputFiles The input file names.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::String& outputFile, const System::ArrayPtr<System::String>& inputFiles);
    /// Merges the given input documents into a single output document using specified input output file names and the final document format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param outputFile The output file name.
    /// @param inputFiles The input file names.
    /// @param saveFormat The save format.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::String& outputFile, const System::ArrayPtr<System::String>& inputFiles, Aspose::Words::SaveFormat saveFormat, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single output document using specified input output file names and save options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param outputFile The output file name.
    /// @param inputFiles The input file names.
    /// @param saveOptions The save options.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::String& outputFile, const System::ArrayPtr<System::String>& inputFiles, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single output document using specified input output file names and save options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param outputFile The output file name.
    /// @param inputFiles The input file names.
    /// @param loadOptions Load options for the input files.
    /// @param saveOptions The save options.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::String& outputFile, const System::ArrayPtr<System::String>& inputFiles, const System::ArrayPtr<System::SharedPtr<Aspose::Words::Loading::LoadOptions>>& loadOptions, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single document and returns <see cref="Aspose::Words::Document">Document</see> instance of the final document.
    /// 
    /// @param inputFiles The input file names.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Merge(const System::ArrayPtr<System::String>& inputFiles, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single document and returns <see cref="Aspose::Words::Document">Document</see> instance of the final document.
    /// 
    /// @param inputFiles The input file names.
    /// @param loadOptions Load options for the input files.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Merge(const System::ArrayPtr<System::String>& inputFiles, const System::ArrayPtr<System::SharedPtr<Aspose::Words::Loading::LoadOptions>>& loadOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single document and returns <see cref="Aspose::Words::Document">Document</see> instance of the final document.
    /// 
    /// @param inputDocuments The input documents.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Merge(const System::ArrayPtr<System::SharedPtr<Aspose::Words::Document>>& inputDocuments, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single output document using specified input output streams and the final document format.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param outputStream The output stream.
    /// @param inputStreams The input streams.
    /// @param saveFormat The save format.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::SharedPtr<System::IO::Stream>& outputStream, const System::ArrayPtr<System::SharedPtr<System::IO::Stream>>& inputStreams, Aspose::Words::SaveFormat saveFormat);
    /// Merges the given input documents into a single output document using specified input output streams and save options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param outputStream The output stream.
    /// @param inputStreams The input streams.
    /// @param saveOptions The save options.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::SharedPtr<System::IO::Stream>& outputStream, const System::ArrayPtr<System::SharedPtr<System::IO::Stream>>& inputStreams, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single output document using specified input output streams and save options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param outputStream The output stream.
    /// @param inputStreams The input streams.
    /// @param loadOptions Load options for the input files.
    /// @param saveOptions The save options.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API void Merge(const System::SharedPtr<System::IO::Stream>& outputStream, const System::ArrayPtr<System::SharedPtr<System::IO::Stream>>& inputStreams, const System::ArrayPtr<System::SharedPtr<Aspose::Words::Loading::LoadOptions>>& loadOptions, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single document and returns <see cref="Aspose::Words::Document">Document</see> instance of the final document.
    /// 
    /// @param inputStreams The input streams.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Merge(const System::ArrayPtr<System::SharedPtr<System::IO::Stream>>& inputStreams, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single document and returns <see cref="Aspose::Words::Document">Document</see> instance of the final document.
    /// 
    /// @param inputStreams The input streams.
    /// @param loadOptions Load options for the input files.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> Merge(const System::ArrayPtr<System::SharedPtr<System::IO::Stream>>& inputStreams, const System::ArrayPtr<System::SharedPtr<Aspose::Words::Loading::LoadOptions>>& loadOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input documents into a single output document using specified input output file names and save options.
    /// Renders the output to images.
    /// 
    /// @param inputFiles The input file names.
    /// @param saveOptions The save options.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> MergeToImages(const System::ArrayPtr<System::String>& inputFiles, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);
    /// Merges the given input document streams into a single output document using specified image save options.
    /// Renders the output to images.
    /// 
    /// @param inputStreams The input file streams.
    /// @param saveOptions The save options.
    /// @param mergeFormatMode Specifies how to merge formatting that clashes.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> MergeToImages(const System::ArrayPtr<System::SharedPtr<System::IO::Stream>>& inputStreams, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, Aspose::Words::LowCode::MergeFormatMode mergeFormatMode);

protected:

    ASPOSE_WORDS_SHARED_API void ExecuteCore() override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
