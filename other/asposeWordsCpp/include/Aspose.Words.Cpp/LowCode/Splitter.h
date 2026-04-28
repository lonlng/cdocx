//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/Splitter.h
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
class SplitOptions;
class SplitterContext;
}
namespace Saving
{

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

/// Provides methods intended to split the documents into parts using different criteria.
class ASPOSE_WORDS_SHARED_CLASS Splitter : public Aspose::Words::LowCode::Processor
{
    typedef Splitter ThisType;
    typedef Aspose::Words::LowCode::Processor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Creates new instance of the splitter processor.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::LowCode::Splitter> Create(const System::SharedPtr<Aspose::Words::LowCode::SplitterContext>& context);
    /// Removes empty pages from the document and saves the output. Returns a list of page numbers that were removed.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// 
    /// @return List of page numbers has been considered as blank and removed.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::List<int32_t>> RemoveBlankPages(const System::String& inputFileName, const System::String& outputFileName);
    /// Removes empty pages from the document and saves the output in the specified format. Returns a list of page numbers that were removed.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// 
    /// @return List of page numbers has been considered as blank and removed.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::List<int32_t>> RemoveBlankPages(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat);
    /// Removes empty pages from the document and saves the output in the specified format. Returns a list of page numbers that were removed.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// 
    /// @return List of page numbers has been considered as blank and removed.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::List<int32_t>> RemoveBlankPages(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Removes blank pages from a document provided in an input stream and saves the updated document
    /// to an output stream in the specified save format. Returns a list of page numbers that were removed.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// 
    /// @return List of page numbers has been considered as blank and removed.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::List<int32_t>> RemoveBlankPages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat);
    /// Removes blank pages from a document provided in an input stream and saves the updated document
    /// to an output stream in the specified save format. Returns a list of page numbers that were removed.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// 
    /// @return List of page numbers has been considered as blank and removed.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::List<int32_t>> RemoveBlankPages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions);
    /// Extracts a specified range of pages from a document file and saves the extracted pages
    /// to a new file. The output file format is determined by the extension of the output file name.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param startPageIndex The zero-based index of the first page to extract.
    /// @param pageCount Number of pages to be extracted.
    static ASPOSE_WORDS_SHARED_API void ExtractPages(const System::String& inputFileName, const System::String& outputFileName, int32_t startPageIndex, int32_t pageCount);
    /// Extracts a specified range of pages from a document file and saves the extracted pages
    /// to a new file using the specified save format.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveFormat The save format.
    /// @param startPageIndex The zero-based index of the first page to extract.
    /// @param pageCount Number of pages to be extracted.
    static ASPOSE_WORDS_SHARED_API void ExtractPages(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, int32_t startPageIndex, int32_t pageCount);
    /// Extracts a specified range of pages from a document file and saves the extracted pages
    /// to a new file using the specified save format.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name.
    /// @param saveOptions The save options.
    /// @param startPageIndex The zero-based index of the first page to extract.
    /// @param pageCount Number of pages to be extracted.
    static ASPOSE_WORDS_SHARED_API void ExtractPages(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, int32_t startPageIndex, int32_t pageCount);
    /// Extracts a specified range of pages from a document stream and saves the extracted pages
    /// to an output stream using the specified save format.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveFormat The save format.
    /// @param startPageIndex The zero-based index of the first page to extract.
    /// @param pageCount Number of pages to be extracted.
    static ASPOSE_WORDS_SHARED_API void ExtractPages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, Aspose::Words::SaveFormat saveFormat, int32_t startPageIndex, int32_t pageCount);
    /// Extracts a specified range of pages from a document stream and saves the extracted pages
    /// to an output stream using the specified save format.
    /// 
    /// @param inputStream The input stream.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    /// @param startPageIndex The zero-based index of the first page to extract.
    /// @param pageCount Number of pages to be extracted.
    static ASPOSE_WORDS_SHARED_API void ExtractPages(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<System::IO::Stream>& outputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, int32_t startPageIndex, int32_t pageCount);
    /// Splits a document into multiple parts based on the specified split options and saves
    /// the resulting parts to files. The output file format is determined by the extension of the output file name.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name used to generate file name for document parts using rule "outputFile_partIndex.extension"
    /// @param options Document split options.
    static ASPOSE_WORDS_SHARED_API void Split(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::LowCode::SplitOptions>& options);
    /// Splits a document into multiple parts based on the specified split options and saves
    /// the resulting parts to files in the specified save format.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name used to generate file name for document parts using rule "outputFile_partIndex.extension"
    /// @param saveFormat The save format.
    /// @param options Document split options.
    static ASPOSE_WORDS_SHARED_API void Split(const System::String& inputFileName, const System::String& outputFileName, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<Aspose::Words::LowCode::SplitOptions>& options);
    /// Splits a document into multiple parts based on the specified split options and saves
    /// the resulting parts to files in the specified save format.
    /// 
    /// @param inputFileName The input file name.
    /// @param outputFileName The output file name used to generate file name for document parts using rule "outputFile_partIndex.extension"
    /// @param saveOptions The save options.
    /// @param options Document split options.
    static ASPOSE_WORDS_SHARED_API void Split(const System::String& inputFileName, const System::String& outputFileName, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<Aspose::Words::LowCode::SplitOptions>& options);
    /// Splits a document from an input stream into multiple parts based on the specified split options and
    /// returns the resulting parts as an array of streams in the specified save format.
    /// 
    /// @param inputStream The input stream.
    /// @param saveFormat The save format.
    /// @param options Document split options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> Split(const System::SharedPtr<System::IO::Stream>& inputStream, Aspose::Words::SaveFormat saveFormat, const System::SharedPtr<Aspose::Words::LowCode::SplitOptions>& options);
    /// Splits a document from an input stream into multiple parts based on the specified split options and
    /// returns the resulting parts as an array of streams in the specified save format.
    /// 
    /// @param inputStream The input stream.
    /// @param saveOptions The save options.
    /// @param options Document split options.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<System::IO::Stream>> Split(const System::SharedPtr<System::IO::Stream>& inputStream, const System::SharedPtr<Aspose::Words::Saving::SaveOptions>& saveOptions, const System::SharedPtr<Aspose::Words::LowCode::SplitOptions>& options);

protected:

    ASPOSE_WORDS_SHARED_API void ExecuteCore() override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
