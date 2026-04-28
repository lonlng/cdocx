//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PlainTextDocument.h
#pragma once

#include <system/string.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Loading
{
class LoadOptions;
}
namespace Properties
{
class BuiltInDocumentProperties;
class CustomDocumentProperties;
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

/// Allows to extract plain-text representation of the document's content.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-text-document/">Working with Text Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PlainTextDocument : public System::Object
{
    typedef PlainTextDocument ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets textual content of the document concatenated as a string.
    ASPOSE_WORDS_SHARED_API System::String get_Text() const;
    /// Gets <see cref="Aspose::Words::PlainTextDocument::get_BuiltInDocumentProperties">BuiltInDocumentProperties</see> of the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::BuiltInDocumentProperties> get_BuiltInDocumentProperties() const;
    /// Gets <see cref="Aspose::Words::PlainTextDocument::get_CustomDocumentProperties">CustomDocumentProperties</see> of the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::CustomDocumentProperties> get_CustomDocumentProperties() const;

    /// Creates a plain text document from a file. Automatically detects the file format.
    /// 
    /// @param fileName Name of the file to extract the text from.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentException The name of the file cannot be null or empty string.
    ASPOSE_WORDS_SHARED_API PlainTextDocument(const System::String& fileName);
    /// Creates a plain text document from a file. Allows to specify additional options such as an encryption password.
    /// 
    /// @param fileName Name of the file to extract the text from.
    /// @param loadOptions Additional options to use when loading a document. Can be <c>%null</c>.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentException The name of the file cannot be null or empty string.
    ASPOSE_WORDS_SHARED_API PlainTextDocument(const System::String& fileName, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);
    /// Creates a plain text document from a stream. Automatically detects the file format.
    /// 
    /// The document must be stored at the beginning of the stream. The stream must support random positioning.
    /// 
    /// @param stream The stream where to extract the text from.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentNullException The stream cannot be null.
    /// @exception System::NotSupportedException The stream does not support reading or seeking.
    /// @exception System::ObjectDisposedException The stream is a disposed object.
    ASPOSE_WORDS_SHARED_API PlainTextDocument(const System::SharedPtr<System::IO::Stream>& stream);
    /// Creates a plain text document from a stream. Allows to specify additional options such as an encryption password.
    /// 
    /// The document must be stored at the beginning of the stream. The stream must support random positioning.
    /// 
    /// @param stream The stream where to extract the text from.
    /// @param loadOptions Additional options to use when loading a document. Can be <c>%null</c>.
    /// 
    /// @exception Aspose::Words::UnsupportedFileFormatException The document format is not recognized or not supported.
    /// @exception Aspose::Words::FileCorruptedException The document appears to be corrupted and cannot be loaded.
    /// @exception System::Exception There is a problem with the document and it should be reported to %Aspose.Words developers.
    /// @exception System::IO::IOException There is an input/output exception.
    /// @exception Aspose::Words::IncorrectPasswordException The document is encrypted and requires a password to open, but you supplied an incorrect password.
    /// @exception System::ArgumentNullException The stream cannot be null.
    /// @exception System::NotSupportedException The stream does not support reading or seeking.
    /// @exception System::ObjectDisposedException The stream is a disposed object.
    ASPOSE_WORDS_SHARED_API PlainTextDocument(const System::SharedPtr<System::IO::Stream>& stream, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);
    ASPOSE_WORDS_SHARED_API PlainTextDocument(std::istream& stream);
    ASPOSE_WORDS_SHARED_API PlainTextDocument(std::istream& stream, const System::SharedPtr<Aspose::Words::Loading::LoadOptions>& loadOptions);

private:

    System::String mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
