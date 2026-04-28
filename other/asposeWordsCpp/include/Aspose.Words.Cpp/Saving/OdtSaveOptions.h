//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/OdtSaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/Saving/OdtSaveMeasureUnit.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Saving
{
class DigitalSignatureDetails;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> or
/// <see cref="Aspose::Words::SaveFormat::Ott">Ott</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
/// 
/// At the moment provides only the <see cref="Aspose::Words::Saving::OdtSaveOptions::get_SaveFormat">SaveFormat</see> property, but in the future will have
/// other options added, such as an encryption password or digital signature settings.
class ASPOSE_WORDS_SHARED_CLASS OdtSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef OdtSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can be <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> or <see cref="Aspose::Words::SaveFormat::Ott">Ott</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can be <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> or <see cref="Aspose::Words::SaveFormat::Ott">Ott</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Specifies whether export should correspond to ODT specification 1.1 strictly.
    /// OOo 3.0 displays files correctly when they contain elements and attributes of ODT 1.2.
    /// Use "false" for this purpose, or "true" for strict conformity of specification 1.1.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsStrictSchema11() const;
    /// Setter for Aspose::Words::Saving::OdtSaveOptions::get_IsStrictSchema11
    ASPOSE_WORDS_SHARED_API void set_IsStrictSchema11(bool value);
    /// Allows to specify units of measure to apply to document content.
    /// The default value is <see cref="Aspose::Words::Saving::OdtSaveMeasureUnit::Centimeters">Centimeters</see>
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::OdtSaveMeasureUnit get_MeasureUnit() const;
    /// Allows to specify units of measure to apply to document content.
    /// The default value is <see cref="Aspose::Words::Saving::OdtSaveMeasureUnit::Centimeters">Centimeters</see>
    ASPOSE_WORDS_SHARED_API void set_MeasureUnit(Aspose::Words::Saving::OdtSaveMeasureUnit value);
    /// Gets a password to encrypt document.
    /// 
    /// In order to save document without encryption this property should be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Password() const;
    /// Sets a password to encrypt document.
    /// 
    /// In order to save document without encryption this property should be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API void set_Password(const System::String& value);
    /// Gets <see cref="Aspose::Words::Saving::DigitalSignatureDetails">DigitalSignatureDetails</see> object used to sign a document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Saving::DigitalSignatureDetails>& get_DigitalSignatureDetails() const;
    /// Sets <see cref="Aspose::Words::Saving::DigitalSignatureDetails">DigitalSignatureDetails</see> object used to sign a document.
    ASPOSE_WORDS_SHARED_API void set_DigitalSignatureDetails(const System::SharedPtr<Aspose::Words::Saving::DigitalSignatureDetails>& value);

    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> format.
    ASPOSE_WORDS_SHARED_API OdtSaveOptions();
    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> format
    /// encrypted with a password.
    ASPOSE_WORDS_SHARED_API OdtSaveOptions(const System::String& password);
    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> or
    /// <see cref="Aspose::Words::SaveFormat::Ott">Ott</see> format.
    /// 
    /// @param saveFormat Can be <see cref="Aspose::Words::SaveFormat::Odt">Odt</see> or <see cref="Aspose::Words::SaveFormat::Ott">Ott</see>.
    ASPOSE_WORDS_SHARED_API OdtSaveOptions(Aspose::Words::SaveFormat saveFormat);

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    System::String mField4;

};

}
}
}
