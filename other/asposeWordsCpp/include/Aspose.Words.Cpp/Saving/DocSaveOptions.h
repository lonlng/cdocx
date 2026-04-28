//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DocSaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
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

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Doc">Doc</see> or
/// <see cref="Aspose::Words::SaveFormat::Dot">Dot</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
/// 
/// At the moment provides only the <see cref="Aspose::Words::Saving::DocSaveOptions::get_SaveFormat">SaveFormat</see> property, but in the future will have
/// other options added, such as an encryption password or digital signature settings.
class ASPOSE_WORDS_SHARED_CLASS DocSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef DocSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can be <see cref="Aspose::Words::SaveFormat::Doc">Doc</see> or <see cref="Aspose::Words::SaveFormat::Dot">Dot</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can be <see cref="Aspose::Words::SaveFormat::Doc">Doc</see> or <see cref="Aspose::Words::SaveFormat::Dot">Dot</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Gets/sets a password to encrypt document using RC4 encryption method.
    /// 
    /// In order to save document without encryption this property should be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Password() const;
    /// Gets/sets a password to encrypt document using RC4 encryption method.
    /// 
    /// In order to save document without encryption this property should be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API void set_Password(const System::String& value);
    /// When <c>%false</c>, RoutingSlip data is not saved to output document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_SaveRoutingSlip() const;
    /// When <c>%false</c>, RoutingSlip data is not saved to output document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_SaveRoutingSlip(bool value);
    /// When <c>%false</c>, small metafiles are not compressed for performance reason.
    /// Default value is <c>%true</c>, all metafiles are compressed regardless of its size.
    ASPOSE_WORDS_SHARED_API bool get_AlwaysCompressMetafiles() const;
    /// When <c>%false</c>, small metafiles are not compressed for performance reason.
    /// Default value is <c>%true</c>, all metafiles are compressed regardless of its size.
    ASPOSE_WORDS_SHARED_API void set_AlwaysCompressMetafiles(bool value);
    /// When <c>%false</c>, PictureBullet data is not saved to output document.
    /// Default value is <c>%true</c>.
    /// 
    /// This option is provided for Word 97, which cannot work correctly with PictureBullet data.
    /// To remove PictureBullet data, set the option to "false".
    ASPOSE_WORDS_SHARED_API bool get_SavePictureBullet() const;
    /// Setter for Aspose::Words::Saving::DocSaveOptions::get_SavePictureBullet
    ASPOSE_WORDS_SHARED_API void set_SavePictureBullet(bool value);
    /// Gets <see cref="Aspose::Words::Saving::DigitalSignatureDetails">DigitalSignatureDetails</see> object used to sign a document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Saving::DigitalSignatureDetails>& get_DigitalSignatureDetails() const;
    /// Sets <see cref="Aspose::Words::Saving::DigitalSignatureDetails">DigitalSignatureDetails</see> object used to sign a document.
    ASPOSE_WORDS_SHARED_API void set_DigitalSignatureDetails(const System::SharedPtr<Aspose::Words::Saving::DigitalSignatureDetails>& value);

    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::Doc">Doc</see> format.
    ASPOSE_WORDS_SHARED_API DocSaveOptions();
    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::Doc">Doc</see> or
    /// <see cref="Aspose::Words::SaveFormat::Dot">Dot</see> format.
    /// 
    /// @param saveFormat Can be <see cref="Aspose::Words::SaveFormat::Doc">Doc</see> or <see cref="Aspose::Words::SaveFormat::Dot">Dot</see>.
    ASPOSE_WORDS_SHARED_API DocSaveOptions(Aspose::Words::SaveFormat saveFormat);

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;

};

}
}
}
