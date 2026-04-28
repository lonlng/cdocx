//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DigitalSignatures/CertificateHolder.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Security
{
namespace Cryptography
{
namespace X509Certificates
{
class X509Certificate2;
}
}
class SecureString;
}
}

namespace Aspose {

namespace Words {

namespace DigitalSignatures {

/// Represents a holder of <b>%X509Certificate2</b> instance.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-digital-signatures/">Work with Digital Signatures</a> documentation article.
/// 
/// <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see> can be created by static factory methods only.
/// It contains an instance of <b>%X509Certificate2</b> which is used to introduce private, public keys and certificate chains into the system.
/// This class is applied in <see cref="Aspose::Words::DigitalSignatures::DigitalSignatureUtil">DigitalSignatureUtil</see> and <see cref="Aspose::Words::Saving::PdfDigitalSignatureDetails">PdfDigitalSignatureDetails</see> instead of obsolete methods with
/// <see cref="System::Security::Cryptography::X509Certificates::X509Certificate2">X509Certificate2</see> as parameters.
class ASPOSE_WORDS_SHARED_CLASS CertificateHolder : public System::Object
{
    typedef CertificateHolder ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the instance of <b>%X509Certificate2</b> which holds private, public keys and certificate chain.
    /// 
    /// @return <see cref="System::Security::Cryptography::X509Certificates::X509Certificate2">X509Certificate2</see>
    ///     <see cref="System::Security::Cryptography::X509Certificates::X509Certificate2">X509Certificate2</see>
    ///     instance
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate2> get_Certificate();

    /// Creates <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see> object using byte array of PKCS12 store and its password.
    /// 
    /// @param certBytes A byte array that contains data from an X.509 certificate.
    /// @param password The password required to access the X.509 certificate data.
    /// 
    /// @return An instance of <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see>
    /// 
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a certBytes is <c>%null</c>
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a password is <c>%null</c>
    /// @exception System::Security::SecurityException Thrown if PKCS12 store contains no aliases
    /// @exception System::IO::IOException Thrown if there is wrong password or corrupted file.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder> Create(const System::ArrayPtr<uint8_t>& certBytes, const System::SharedPtr<System::Security::SecureString>& password);
    /// Creates <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see> object using byte array of PKCS12 store and its password.
    /// 
    /// @param certBytes A byte array that contains data from an X.509 certificate.
    /// @param password The password required to access the X.509 certificate data.
    /// 
    /// @return An instance of <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see>
    /// 
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a certBytes is <c>%null</c>
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a password is <c>%null</c>
    /// @exception System::Security::SecurityException Thrown if PKCS12 store contains no aliases
    /// @exception System::IO::IOException Thrown if there is wrong password or corrupted file.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder> Create(const System::ArrayPtr<uint8_t>& certBytes, const System::String& password);
    /// Creates <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see> object using path to PKCS12 store and its password.
    /// 
    /// @param fileName The name of a certificate file.
    /// @param password The password required to access the X.509 certificate data.
    /// 
    /// @return An instance of <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see>
    /// 
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a fileName is <c>%null</c>
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a password is <c>%null</c>
    /// @exception System::Security::SecurityException Thrown if PKCS12 store contains no aliases
    /// @exception System::IO::IOException Thrown if there is wrong password or corrupted file.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder> Create(const System::String& fileName, const System::String& password);
    /// Creates <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see> object using path to PKCS12 store, its password and the alias by using which private key and certificate will be found.
    /// 
    /// @param fileName The name of a certificate file.
    /// @param password The password required to access the X.509 certificate data.
    /// @param alias The associated alias for a certificate and its private key
    /// 
    /// @return An instance of <see cref="Aspose::Words::DigitalSignatures::CertificateHolder">CertificateHolder</see>
    /// 
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a fileName is <c>%null</c>
    /// @exception Org::BouncyCastle::Security::InvalidParameterException Thrown if @a password is <c>%null</c>
    /// @exception System::Security::SecurityException Thrown if PKCS12 store contains no aliases
    /// @exception System::IO::IOException Thrown if there is wrong password or corrupted file.
    /// @exception System::Security::SecurityException Thrown if there is no private key with the given alias
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder> Create(const System::String& fileName, const System::String& password, const System::String& alias);

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
