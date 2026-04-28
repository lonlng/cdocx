//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/FileFormatUtil.h
#pragma once

#include <system/io/std_stream_wrappers.h>
#include <system/exceptions.h>
#include <mutex>
#include <memory>
#include <iostream>

#include <Aspose.Words.Cpp/Drawing/ImageType.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/LoadFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class FileFormatInfo;

}
}
namespace System
{

namespace IO
{
class Stream;
}
template <typename> class SmartPtr;
template <typename T0> using SharedPtr = System::SmartPtr<T0>;
class String;
}

namespace Aspose {

namespace Words {

/// Provides utility methods for working with file formats, such as detecting file format
/// or converting file extensions to/from file format enums.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/detect-file-format-and-check-format-compatibility/">Detect File Format and Check Format Compatibility</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FileFormatUtil
{
    typedef FileFormatUtil ThisType;

public:

    /// Detects and returns the information about a format of a document stored in a disk file.
    /// 
    /// Even if this method detects the document format, it does not guarantee
    /// that the specified document is valid. This method only detects the document format by
    /// reading data that is sufficient for detection. To fully verify that a document is valid
    /// you need to load the document into a <see cref="Aspose::Words::Document">Document</see> object.
    /// 
    /// This method throws <see cref="Aspose::Words::FileCorruptedException">FileCorruptedException</see> when the format is
    /// recognized, but the detection cannot complete because of corruption.
    /// 
    /// @param fileName The file name.
    /// 
    /// @return A <see cref="Aspose::Words::FileFormatInfo">FileFormatInfo</see> object that contains the detected information.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::FileFormatInfo> DetectFileFormat(const System::String& fileName);
    /// Detects and returns the information about a format of a document stored in a stream.
    /// 
    /// The stream must be positioned at the beginning of the document.
    /// 
    /// When this method returns, the position in the stream is restored to the original position.
    /// 
    /// Even if this method detects the document format, it does not guarantee
    /// that the specified document is valid. This method only detects the document format by
    /// reading data that is sufficient for detection. To fully verify that a document is valid
    /// you need to load the document into a <see cref="Aspose::Words::Document">Document</see> object.
    /// 
    /// This method throws <see cref="Aspose::Words::FileCorruptedException">FileCorruptedException</see> when the format is
    /// recognized, but the detection cannot complete because of corruption.
    /// 
    /// @param stream The stream.
    /// 
    /// @return A <see cref="Aspose::Words::FileFormatInfo">FileFormatInfo</see> object that contains the detected information.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::FileFormatInfo> DetectFileFormat(const System::SharedPtr<System::IO::Stream>& stream);
    /// Converts IANA content type into a load format enumerated value.
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API Aspose::Words::LoadFormat ContentTypeToLoadFormat(const System::String& contentType);
    /// Converts IANA content type into a save format enumerated value.
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat ContentTypeToSaveFormat(const System::String& contentType);
    /// Converts a load format enumerated value into a file extension. The returned extension is a lower-case string with a leading dot.
    /// 
    /// The <see cref="Aspose::Words::SaveFormat::WordML">WordML</see> value is converted to ".wml".
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API System::String LoadFormatToExtension(Aspose::Words::LoadFormat loadFormat);
    /// Converts a <see cref="Aspose::Words::SaveFormat">SaveFormat</see> value to a <see cref="Aspose::Words::LoadFormat">LoadFormat</see> value if possible.
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API Aspose::Words::LoadFormat SaveFormatToLoadFormat(Aspose::Words::SaveFormat saveFormat);
    /// Converts a <see cref="Aspose::Words::LoadFormat">LoadFormat</see> value to a <see cref="Aspose::Words::SaveFormat">SaveFormat</see> value if possible.
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat LoadFormatToSaveFormat(Aspose::Words::LoadFormat loadFormat);
    /// Converts a save format enumerated value into a file extension. The returned extension is a lower-case string with a leading dot.
    /// 
    /// The <see cref="Aspose::Words::SaveFormat::WordML">WordML</see> value is converted to ".wml".
    /// 
    /// The <see cref="Aspose::Words::SaveFormat::FlatOpc">FlatOpc</see> value is converted to ".fopc".
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API System::String SaveFormatToExtension(Aspose::Words::SaveFormat saveFormat);
    /// Converts a file name extension into a <see cref="Aspose::Words::SaveFormat">SaveFormat</see> value.
    /// 
    /// If the extension cannot be recognized, returns <see cref="Aspose::Words::SaveFormat::Unknown">Unknown</see>.
    /// 
    /// @param extension The file extension. Can be with or without a leading dot. Case-insensitive.
    /// 
    /// @exception System::ArgumentNullException Throws if the parameter is <c>%null</c>.
    static ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat ExtensionToSaveFormat(const System::String& extension);
    /// Converts an %Aspose.Words image type enumerated value into a file extension. The returned extension is a lower-case string with a leading dot.
    /// 
    /// @exception System::ArgumentException Throws when cannot convert.
    static ASPOSE_WORDS_SHARED_API System::String ImageTypeToExtension(Aspose::Words::Drawing::ImageType imageType);

    ASPOSE_WORDS_SHARED_API FileFormatUtil();

    template <typename CharType, typename Traits>
    static System::SharedPtr<Aspose::Words::FileFormatInfo> DetectFileFormat(std::basic_istream<CharType, Traits>& stream)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        return DetectFileFormat(streamWrapper);
    }

protected:

private:

};

}
}
