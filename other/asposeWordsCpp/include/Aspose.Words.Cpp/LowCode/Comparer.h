//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Comparer.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/LowCode/Processor.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Comparing
{
class CompareOptions;
}
namespace LowCode
{
class ComparerContext;
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
class DateTime;
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Provides methods intended to compare documents.
class ASPOSE_WORDS_SHARED_CLASS Comparer : public Aspose::Words::LowCode::Processor
{
    typedef Comparer ThisType;
    typedef Aspose::Words::LowCode::Processor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates new instance of the converter processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Comparer> Create();
    /// Creates new instance of the comparer processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Comparer> Create(const System::SharedPtr<Aspose::Words::LowCode::ComparerContext>& context);
    /// Compares two documents with additional options and saves the differences to the specified output file,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputFileName The output file name.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::String& v1, const System::String& v2, const System::String& outputFileName, const System::String& author, System::DateTime dateTime);
    /// Compares two documents with additional options and saves the differences to the specified output file,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputFileName The output file name.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::String& v1, const System::String& v2, const System::String& outputFileName, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);
    /// Compares two documents with additional options and saves the differences to the specified output file in the provided save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputFileName The output file name.
    /// @param saveFormat The output's save format.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::String& v1, const System::String& v2, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& author, System::DateTime dateTime);
    /// Compares two documents with additional options and saves the differences to the specified output file in the provided save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputFileName The output file name.
    /// @param saveFormat The output's save format.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::String& v1, const System::String& v2, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);
    /// Compares two documents with additional options and saves the differences to the specified output file in the provided save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputFileName The output file name.
    /// @param saveOptions The output's save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::String& v1, const System::String& v2, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& author, System::DateTime dateTime);
    /// Compares two documents with additional options and saves the differences to the specified output file in the provided save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputFileName The output file name.
    /// @param saveOptions The output's save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::String& v1, const System::String& v2, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);
    /// Compares two documents loaded from streams with additional options and saves the differences to the provided output stream in the specified save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputStream The output stream.
    /// @param saveFormat The output's save format.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::SharedPtr<System::IO::Stream>& v1, const System::SharedPtr<System::IO::Stream>& v2, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::String& author, System::DateTime dateTime);
    /// Compares two documents loaded from streams with additional options and saves the differences to the provided output stream in the specified save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputStream The output stream.
    /// @param saveFormat The output's save format.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::SharedPtr<System::IO::Stream>& v1, const System::SharedPtr<System::IO::Stream>& v2, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);
    /// Compares two documents loaded from streams with additional options and saves the differences to the provided output stream in the specified save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputStream The output stream.
    /// @param saveOptions The output's save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::SharedPtr<System::IO::Stream>& v1, const System::SharedPtr<System::IO::Stream>& v2, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& author, System::DateTime dateTime);
    /// Compares two documents loaded from streams with additional options and saves the differences to the provided output stream in the specified save format,
    /// producing changes as a number of edit and format revisions.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param outputStream The output stream.
    /// @param saveOptions The output's save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API void Compare(const System::SharedPtr<System::IO::Stream>& v1, const System::SharedPtr<System::IO::Stream>& v2, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);
    /// Compares two documents and saves the differences as images.
    /// Each item in the returned array represents a single page of the output rendered as an image.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param imageSaveOptions The output's image save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> CompareToImages(const System::String& v1, const System::String& v2, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& imageSaveOptions, const System::String& author, System::DateTime dateTime);
    /// Compares two documents and saves the differences as images.
    /// Each item in the returned array represents a single page of the output rendered as an image.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param imageSaveOptions The output's image save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> CompareToImages(const System::String& v1, const System::String& v2, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& imageSaveOptions, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);
    /// Compares two documents and saves the differences as images.
    /// Each item in the returned array represents a single page of the output rendered as an image.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param imageSaveOptions The output's image save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> CompareToImages(const System::SharedPtr<System::IO::Stream>& v1, const System::SharedPtr<System::IO::Stream>& v2, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& imageSaveOptions, const System::String& author, System::DateTime dateTime);
    /// Compares two documents and saves the differences as images.
    /// Each item in the returned array represents a single page of the output rendered as an image.
    /// 
    /// @param v1 The original document.
    /// @param v2 The modified document.
    /// @param imageSaveOptions The output's image save options.
    /// @param author Initials of the author to use for revisions.
    /// @param dateTime The date and time to use for revisions.
    /// @param compareOptions Document comparison options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> CompareToImages(const System::SharedPtr<System::IO::Stream>& v1, const System::SharedPtr<System::IO::Stream>& v2, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& imageSaveOptions, const System::String& author, System::DateTime dateTime, const System::SharedPtr<Aspose::Words::Comparing::CompareOptions>& compareOptions);

protected:

    ASPOSE_WORDS_SHARED_API void ExecuteCore() override;
    ASPOSE_WORDS_SHARED_API void CheckArgumentsSet() override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
