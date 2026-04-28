//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontInfo.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fonts/FontPitch.h>
#include <Aspose.Words.Cpp/Fonts/FontFamily.h>
#include <Aspose.Words.Cpp/Fonts/EmbeddedFontStyle.h>
#include <Aspose.Words.Cpp/Fonts/EmbeddedFontFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Fonts
{

class FontEmbeddingLicensingRights;

}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IList;
}
}

}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies information about a font used in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
/// 
/// You do not create instances of this class directly.
/// Use the <see cref="Aspose::Words::DocumentBase::get_FontInfos">FontInfos</see> property to access the collection of fonts
/// defined in a document.
/// 
/// @sa Aspose::Words::Fonts::FontInfoCollection
/// @sa Aspose::Words::DocumentBase::get_FontInfos
class ASPOSE_WORDS_SHARED_CLASS FontInfo : public System::Object
{
    typedef FontInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The pitch indicates if the font is fixed pitch, proportionally spaced, or relies on a default setting.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontPitch get_Pitch() const;
    /// The pitch indicates if the font is fixed pitch, proportionally spaced, or relies on a default setting.
    ASPOSE_WORDS_SHARED_API void set_Pitch(Aspose::Words::Fonts::FontPitch value);
    /// Indicates that this font is a TrueType or OpenType font as opposed to a raster or vector font.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsTrueType() const;
    /// Indicates that this font is a TrueType or OpenType font as opposed to a raster or vector font.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_IsTrueType(bool value);
    /// Gets the font family this font belongs to.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontFamily get_Family() const;
    /// Sets the font family this font belongs to.
    ASPOSE_WORDS_SHARED_API void set_Family(Aspose::Words::Fonts::FontFamily value);
    /// Gets the character set for the font.
    ASPOSE_WORDS_SHARED_API int32_t get_Charset();
    /// Sets the character set for the font.
    ASPOSE_WORDS_SHARED_API void set_Charset(int32_t value);
    /// Gets or sets the PANOSE typeface classification number.
    /// 
    /// PANOSE is a compact 10-byte description of a fonts critical visual characteristics,
    /// such as contrast, weight, and serif style. The digits represent Family Kind, Serif Style,
    /// Weight, Proportion, Contrast, Stroke Variation, Arm Style, Letterform, Midline, and X-Height.
    /// 
    /// Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_Panose() const;
    /// Setter for Aspose::Words::Fonts::FontInfo::get_Panose
    ASPOSE_WORDS_SHARED_API void set_Panose(const System::ArrayPtr<uint8_t>& value);
    /// Gets the name of the font.
    /// 
    /// Cannot be <c>%null</c>. Can be an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Gets the alternate name for the font.
    /// 
    /// Cannot be <c>%null</c>. Can be an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_AltName() const;
    /// Sets the alternate name for the font.
    /// 
    /// Cannot be <c>%null</c>. Can be an empty string.
    ASPOSE_WORDS_SHARED_API void set_AltName(const System::String& value);
    /// Gets the embedded font licensing rights.
    /// 
    /// The value may be null if font is not embedded.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontEmbeddingLicensingRights> get_EmbeddingLicensingRights();

    /// Gets a specific embedded font file.
    /// 
    /// @param format Specifies the font format to retrieve.
    /// @param style Specifies the font style to retrieve.
    /// 
    /// @return Returns <c>%null</c> if the specified font is not embedded.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> GetEmbeddedFont(Aspose::Words::Fonts::EmbeddedFontFormat format, Aspose::Words::Fonts::EmbeddedFontStyle style);
    /// Gets an embedded font file in OpenType format. Fonts in Embedded OpenType format are converted to OpenType.
    /// 
    /// @param style Specifies the font style to retrieve.
    /// 
    /// @return Returns <c>%null</c> if the specified font is not embedded.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> GetEmbeddedFontAsOpenType(Aspose::Words::Fonts::EmbeddedFontStyle style);

protected:

    FontInfo();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::String mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::String mField8;
    System::String mField9;
    System::SharedPtr<System::Object> mField10;

protected:

};

}
}
}
