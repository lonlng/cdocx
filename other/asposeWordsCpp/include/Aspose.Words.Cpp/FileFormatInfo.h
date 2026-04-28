//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/FileFormatInfo.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/LoadFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Text
{
class Encoding;
}
}

namespace Aspose {

namespace Words {

/// Contains data returned by <see cref="Aspose::Words::FileFormatUtil">FileFormatUtil</see> document format detection methods.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/detect-file-format-and-check-format-compatibility/">Detect File Format and Check Format Compatibility</a> documentation article.
/// 
/// You do not create instances of this class directly. Objects of this class are returned by
/// <see cref="Aspose::Words::FileFormatUtil::DetectFileFormat(System::SharedPtr<System::IO::Stream>)">DetectFileFormat()</see> methods.
class ASPOSE_WORDS_SHARED_CLASS FileFormatInfo : public System::Object
{
    typedef FileFormatInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the detected document format.
    /// 
    /// When an OOXML document is encrypted, it is not possible to ascertain whether it is
    /// an Excel, Word or PowerPoint document without decrypting it first so for an encrypted OOXML
    /// document this property will always return <see cref="Aspose::Words::LoadFormat::Docx">Docx</see>.
    /// 
    /// @sa Aspose::Words::FileFormatInfo::get_IsEncrypted
    ASPOSE_WORDS_SHARED_API Aspose::Words::LoadFormat get_LoadFormat() const;
    /// Returns <c>%true</c> if the document is encrypted and requires a password to open.
    /// 
    /// This property exists to help you sort documents that are encrypted from those that are not.
    /// If you attempt to load an encrypted document using %Aspose.Words without supplying a password an
    /// exception will be thrown. You can use this property to detect whether a document requires a password
    /// and take some action before loading a document, for example, prompt the user for a password.
    /// 
    /// @sa Aspose::Words::FileFormatInfo::get_LoadFormat
    ASPOSE_WORDS_SHARED_API bool get_IsEncrypted() const;
    /// Returns <c>%true</c> if this document contains a digital signature.
    /// This property merely informs that a digital signature is present on a document,
    /// but it does not  specify whether the signature is valid or not.
    /// 
    /// This property exists to help you sort documents that are digitally signed from those that are not.
    /// If you use %Aspose.Words to modify and save a document that is digitally signed, then the digital signature will
    /// be lost. This is by design because a digital signature exists to guard the authenticity of a document.
    /// Using this property you can detect digitally signed documents before processing them in the same way as normal
    /// documents and take some action to avoid losing the digital signature, for example notify the user.
    ASPOSE_WORDS_SHARED_API bool get_HasDigitalSignature() const;
    /// Returns <c>%true</c> if this document contains a VBA macros.
    ASPOSE_WORDS_SHARED_API bool get_HasMacros() const;
    /// Gets the detected encoding if applicable to the current document format.
    /// At the moment detects encoding only for HTML documents.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Text::Encoding> get_Encoding() const;

protected:

    __TypeStub<1,1,1,1>::type mField0;

    FileFormatInfo();

private:

    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    System::SharedPtr<System::Object> mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    System::SharedPtr<System::Object> mField8;
    __TypeStub<4,4,4,4>::type mField9;

};

}
}
