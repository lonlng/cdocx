//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/LoadOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Settings/MsWordVersion.h>
#include <Aspose.Words.Cpp/Loading/DocumentRecoveryMode.h>
#include <Aspose.Words.Cpp/LoadFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Fonts
{
class FontSettings;
}
class IWarningCallback;
namespace Licensing
{
void Venture(const System::SharedPtr<System::Object>&, bool, const uint8_t*, const size_t);

}
namespace Loading
{

class IDocumentLoadingCallback;
class IResourceLoadingCallback;
class LanguagePreferences;

}

}
}
namespace System
{
namespace Text
{
class Encoding;
}
}

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify additional options (such as password or base URI) when
/// loading a document into a <see cref="Aspose::Words::Document">Document</see> object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS LoadOptions : public System::Object
{
    typedef LoadOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format of the document to be loaded.
    /// Default is <see cref="Aspose::Words::LoadFormat::Auto">Auto</see>.
    /// 
    /// It is recommended that you specify the <see cref="Aspose::Words::LoadFormat::Auto">Auto</see> value and let %Aspose.Words detect
    /// the file format automatically. If you know the format of the document you are about to load, you can specify the format
    /// explicitly and this will slightly reduce the loading time by the overhead associated with auto detecting the format.
    /// If you specify an explicit load format and it will turn out to be wrong, the auto detection will be invoked and a second
    /// attempt to load the file will be made.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LoadFormat get_LoadFormat() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_LoadFormat
    ASPOSE_WORDS_SHARED_API void set_LoadFormat(Aspose::Words::LoadFormat value);
    /// Gets or sets the password for opening an encrypted document.
    /// Can be <c>%null</c> or empty string. Default is <c>%null</c>.
    /// 
    /// You need to know the password to open an encrypted document. If the document is not encrypted, set this to <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Password() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_Password
    ASPOSE_WORDS_SHARED_API void set_Password(const System::String& value);
    /// Gets or sets the string that will be used to resolve relative URIs found in the document into absolute URIs when required.
    /// Can be <c>%null</c> or empty string. Default is <c>%null</c>.
    /// 
    /// This property is used to resolve relative URIs into absolute in the following cases:
    /// 
    /// -# When loading an HTML document from a stream and the document contains images with
    ///    relative URIs and does not have a base URI specified in the BASE HTML element.
    /// -# When saving a document to PDF and other formats, to retrieve images linked using relative URIs
    ///    so the images can be saved into the output document.
    ASPOSE_WORDS_SHARED_API System::String get_BaseUri() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_BaseUri
    ASPOSE_WORDS_SHARED_API void set_BaseUri(const System::String& value);
    /// Gets or sets the encoding that will be used to load an HTML, TXT, or CHM document if the encoding is not specified
    /// inside the document.
    /// Can be <c>%null</c>. Default is <c>%null</c>.
    /// 
    /// This property is used only when loading HTML, TXT, or CHM documents.
    /// 
    /// If encoding is not specified inside the document and this property is <c>%null</c>, then the system will try to
    /// automatically detect the encoding.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Text::Encoding> get_Encoding() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_Encoding
    ASPOSE_WORDS_SHARED_API void set_Encoding(const System::SharedPtr<System::Text::Encoding>& value);
    /// Allows to control how external resources (images, style sheets) are loaded when a document is imported from HTML, MHTML.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::IResourceLoadingCallback> get_ResourceLoadingCallback() const;
    /// Allows to control how external resources (images, style sheets) are loaded when a document is imported from HTML, MHTML.
    ASPOSE_WORDS_SHARED_API void set_ResourceLoadingCallback(const System::SharedPtr<Aspose::Words::Loading::IResourceLoadingCallback>& value);
    /// Called during a load operation, when an issue is detected that might result in data or formatting fidelity loss.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::IWarningCallback> get_WarningCallback() const;
    /// Called during a load operation, when an issue is detected that might result in data or formatting fidelity loss.
    ASPOSE_WORDS_SHARED_API void set_WarningCallback(const System::SharedPtr<Aspose::Words::IWarningCallback>& value);
    /// Called during loading a document and accepts data about loading progress.
    /// 
    /// <see cref="Aspose::Words::LoadFormat::Docx">Docx</see>, <see cref="Aspose::Words::LoadFormat::FlatOpc">FlatOpc</see>, <see cref="Aspose::Words::LoadFormat::Docm">Docm</see>, <see cref="Aspose::Words::LoadFormat::Dotm">Dotm</see>, <see cref="Aspose::Words::LoadFormat::Dotx">Dotx</see>, <see cref="Aspose::Words::LoadFormat::Markdown">Markdown</see>, <see cref="Aspose::Words::LoadFormat::Rtf">Rtf</see>, <see cref="Aspose::Words::LoadFormat::WordML">WordML</see>, <see cref="Aspose::Words::LoadFormat::Doc">Doc</see>, <see cref="Aspose::Words::LoadFormat::Dot">Dot</see>, <see cref="Aspose::Words::LoadFormat::Odt">Odt</see>, <see cref="Aspose::Words::LoadFormat::Ott">Ott</see> formats supported.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::IDocumentLoadingCallback> get_ProgressCallback() const;
    /// Called during loading a document and accepts data about loading progress.
    /// 
    /// <see cref="Aspose::Words::LoadFormat::Docx">Docx</see>, <see cref="Aspose::Words::LoadFormat::FlatOpc">FlatOpc</see>, <see cref="Aspose::Words::LoadFormat::Docm">Docm</see>, <see cref="Aspose::Words::LoadFormat::Dotm">Dotm</see>, <see cref="Aspose::Words::LoadFormat::Dotx">Dotx</see>, <see cref="Aspose::Words::LoadFormat::Markdown">Markdown</see>, <see cref="Aspose::Words::LoadFormat::Rtf">Rtf</see>, <see cref="Aspose::Words::LoadFormat::WordML">WordML</see>, <see cref="Aspose::Words::LoadFormat::Doc">Doc</see>, <see cref="Aspose::Words::LoadFormat::Dot">Dot</see>, <see cref="Aspose::Words::LoadFormat::Odt">Odt</see>, <see cref="Aspose::Words::LoadFormat::Ott">Ott</see> formats supported.
    ASPOSE_WORDS_SHARED_API void set_ProgressCallback(const System::SharedPtr<Aspose::Words::Loading::IDocumentLoadingCallback>& value);
    /// Gets or sets whether to preserve the INCLUDEPICTURE field when reading %Microsoft Word formats.
    /// The default value is <c>%false</c>.
    /// 
    /// By default, the INCLUDEPICTURE field is converted into a shape object. You can override that if you need
    /// the field to be preserved, for example, if you wish to update it programmatically. Note however that this
    /// approach is not common for %Aspose.Words. Use it on your own risk.
    /// 
    /// One of the possible use cases may be using a MERGEFIELD as a child field to dynamically change the source path
    /// of the picture. In this case you need the INCLUDEPICTURE to be preserved in the model.
    ASPOSE_WORDS_SHARED_API bool get_PreserveIncludePictureField() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_PreserveIncludePictureField
    ASPOSE_WORDS_SHARED_API void set_PreserveIncludePictureField(bool value);
    /// Gets whether to convert shapes with EquationXML to Office Math objects.
    ASPOSE_WORDS_SHARED_API bool get_ConvertShapeToOfficeMath() const;
    /// Sets whether to convert shapes with EquationXML to Office Math objects.
    ASPOSE_WORDS_SHARED_API void set_ConvertShapeToOfficeMath(bool value);
    /// Allows to specify document font settings.
    /// 
    /// When loading some formats, %Aspose.Words may require to resolve the fonts. For example, when loading HTML documents Aspose.Words
    /// may resolve the fonts to perform font fallback.
    /// 
    /// If set to <c>%null</c>, default static font settings <see cref="Aspose::Words::Fonts::FontSettings::get_DefaultInstance">DefaultInstance</see> will be used.
    /// 
    /// The default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontSettings> get_FontSettings() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_FontSettings
    ASPOSE_WORDS_SHARED_API void set_FontSettings(const System::SharedPtr<Aspose::Words::Fonts::FontSettings>& value);
    /// Allows to use temporary files when reading document.
    /// By default this property is <c>%null</c> and no temporary files are used.
    /// 
    /// The folder must exist and be writable, otherwise an exception will be thrown.
    /// 
    /// %Aspose.Words automatically deletes all temporary files when reading is complete.
    ASPOSE_WORDS_SHARED_API System::String get_TempFolder() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_TempFolder
    ASPOSE_WORDS_SHARED_API void set_TempFolder(const System::String& value);
    /// Gets whether to convert metafile(<see cref="Aspose::FileFormat::Wmf">Wmf</see> or <see cref="Aspose::FileFormat::Emf">Emf</see>)
    /// images to <see cref="Aspose::FileFormat::Png">Png</see> image format.
    ASPOSE_WORDS_SHARED_API bool get_ConvertMetafilesToPng() const;
    /// Sets whether to convert metafile(<see cref="Aspose::FileFormat::Wmf">Wmf</see> or <see cref="Aspose::FileFormat::Emf">Emf</see>)
    /// images to <see cref="Aspose::FileFormat::Png">Png</see> image format.
    ASPOSE_WORDS_SHARED_API void set_ConvertMetafilesToPng(bool value);
    /// Allows to specify that the document loading process should match a specific MS Word version.
    /// Default value is <see cref="Aspose::Words::Settings::MsWordVersion::Word2019">Word2019</see>
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::MsWordVersion get_MswVersion() const;
    /// Allows to specify that the document loading process should match a specific MS Word version.
    /// Default value is <see cref="Aspose::Words::Settings::MsWordVersion::Word2019">Word2019</see>
    ASPOSE_WORDS_SHARED_API void set_MswVersion(Aspose::Words::Settings::MsWordVersion value);
    /// Specifies whether to update the fields with the <c>%dirty</c> attribute.
    ASPOSE_WORDS_SHARED_API bool get_UpdateDirtyFields() const;
    /// Specifies whether to update the fields with the <c>%dirty</c> attribute.
    ASPOSE_WORDS_SHARED_API void set_UpdateDirtyFields(bool value);
    /// Specifies whether to ignore the OLE data.
    /// 
    /// Ignoring OLE data may reduce memory consumption and increase performance without data lost in a case when destination format does not support OLE objects.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreOleData() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_IgnoreOleData
    ASPOSE_WORDS_SHARED_API void set_IgnoreOleData(bool value);
    /// Gets or sets whether to use LCID value obtained from Windows registry to determine page setup default margins.
    /// 
    /// If set to <c>%true</c>, then MS Word behavior is emulated which takes LCID value from Windows registry.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseSystemLcid() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_UseSystemLcid
    ASPOSE_WORDS_SHARED_API void set_UseSystemLcid(bool value);
    /// Gets language preferences that will be used when document is loading.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::LanguagePreferences> get_LanguagePreferences() const;
    /// Defines how the document should be handled if errors occur during loading.
    /// Use this property to specify whether the system should attempt to recover the document
    /// or follow another defined behavior.
    /// The default value is <see cref="Aspose::Words::Loading::DocumentRecoveryMode::TryRecover">TryRecover</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::DocumentRecoveryMode get_RecoveryMode() const;
    /// Setter for Aspose::Words::Loading::LoadOptions::get_RecoveryMode
    ASPOSE_WORDS_SHARED_API void set_RecoveryMode(Aspose::Words::Loading::DocumentRecoveryMode value);

    /// Initializes a new instance of this class with default values.
    ASPOSE_WORDS_SHARED_API LoadOptions();
    /// A shortcut to initialize a new instance of this class with the specified password to load an encrypted document.
    /// 
    /// @param password The password to open an encrypted document. Can be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API LoadOptions(const System::String& password);
    /// A shortcut to initialize a new instance of this class with properties set to the specified values.
    /// 
    /// @param loadFormat The format of the document to be loaded.
    /// @param password The password to open an encrypted document. Can be <c>%null</c> or empty string.
    /// @param baseUri The string that will be used to resolve relative URIs to absolute. Can be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API LoadOptions(Aspose::Words::LoadFormat loadFormat, const System::String& password, const System::String& baseUri);

    /// Determines whether the specified object is equal in value to the current object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::LoadOptions> Clone();

    virtual ASPOSE_WORDS_SHARED_API ~LoadOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    System::SharedPtr<System::Object> mField4;
    __TypeStub<4,4,4,4>::type mField5;
    System::String mField6;
    System::String mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    __TypeStub<1,1,1,1>::type mField11;
    __TypeStub<1,1,1,1>::type mField12;
    System::SharedPtr<System::Object> mField13;
    __TypeStub<4,4,4,4>::type mField14;
    System::SharedPtr<System::Object> mField15;
    __TypeStub<1,1,1,1>::type mField16;
    __TypeStub<1,1,1,1>::type mField17;
    System::String mField18;
    __TypeStub<1,1,1,1>::type mField19;
    __TypeStub<4,4,4,4>::type mField20;
    System::SharedPtr<System::Object> mField21;
    __TypeStub<4,4,4,4>::type mField22;
    __TypeStub<1,1,1,1>::type mField23;
    __TypeStub<1,1,1,1>::type mField24;

};

}
}
}
