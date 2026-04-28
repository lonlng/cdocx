//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Replacer.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/LowCode/Processor.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace LowCode
{
class ReplacerContext;
}
namespace Replacing
{
class FindReplaceOptions;

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
namespace Text
{
namespace RegularExpressions
{
class Regex;
}
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Provides methods intended to find and replace text in the document.
class ASPOSE_WORDS_SHARED_CLASS Replacer : public Aspose::Words::LowCode::Processor
{
    typedef Replacer ThisType;
    typedef Aspose::Words::LowCode::Processor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates new instance of the replacer processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Replacer> Create(const System::SharedPtr<Aspose::Words::LowCode::ReplacerContext>& context);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file using a regular expression.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), each page of the output will be saved as a separate file. The specified output file name will be used to generate file names for each part following the rule: outputFile_partIndex.extension.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF file.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input stream using a regular expression, with the specified save format and additional options.
    /// 
    /// If the output format is an image (BMP, EMF, EPS, GIF, JPEG, PNG, or WebP), only the first page of the output will be saved to the specified stream.
    /// 
    /// If the output format is TIFF, the output will be saved as a single multi-frame TIFF to the specified stream.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// 
    /// @return The number of replacements made.
    static ASPOSE_WORDS_SHARED_API int32_t Replace(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputStream The input file stream.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified character string pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputStream The input file stream.
    /// @param saveOptions The save options.
    /// @param pattern A string to be replaced.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::String& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified regular expression pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified regular expression pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputFileName The input file name.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::String& inputFileName, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);
    /// Replaces all occurrences of a specified regular expression pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputStream The input file stream.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    /// @param options <see cref="Aspose::Words::Replacing::FindReplaceOptions">FindReplaceOptions</see> object to specify additional options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement, const System::SharedPtr<Aspose::Words::Replacing::FindReplaceOptions>& options);
    /// Replaces all occurrences of a specified regular expression pattern with a replacement string in the input file.
    /// Renders output to images.
    /// 
    /// @param inputStream The input file stream.
    /// @param saveOptions The save options.
    /// @param pattern A regular expression pattern used to find matches.
    /// @param replacement A string to replace all occurrences of pattern.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ReplaceToImages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::ImageSaveOptions>& saveOptions, const System::SharedPtr<System::Text::RegularExpressions::Regex>& pattern, const System::String& replacement);

protected:

    ASPOSE_WORDS_SHARED_API void ExecuteCore() override;
    ASPOSE_WORDS_SHARED_API void CheckArgumentsSet() override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
