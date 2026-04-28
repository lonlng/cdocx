//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/BarcodeParameters.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Container class for barcode parameters to pass-through to BarcodeGenerator.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS BarcodeParameters : public System::Object
{
    typedef BarcodeParameters ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Bar code type.
    ASPOSE_WORDS_SHARED_API System::String get_BarcodeType() const;
    /// Bar code type.
    ASPOSE_WORDS_SHARED_API void set_BarcodeType(const System::String& value);
    /// Data to be encoded.
    ASPOSE_WORDS_SHARED_API System::String get_BarcodeValue() const;
    /// Data to be encoded.
    ASPOSE_WORDS_SHARED_API void set_BarcodeValue(const System::String& value);
    /// Bar code image height (in twips - 1/1440 inches)
    ASPOSE_WORDS_SHARED_API System::String get_SymbolHeight() const;
    /// Bar code image height (in twips - 1/1440 inches)
    ASPOSE_WORDS_SHARED_API void set_SymbolHeight(const System::String& value);
    /// Bar code foreground color (0x000000 - 0xFFFFFF)
    ASPOSE_WORDS_SHARED_API System::String get_ForegroundColor() const;
    /// Bar code foreground color (0x000000 - 0xFFFFFF)
    ASPOSE_WORDS_SHARED_API void set_ForegroundColor(const System::String& value);
    /// Bar code background color (0x000000 - 0xFFFFFF)
    ASPOSE_WORDS_SHARED_API System::String get_BackgroundColor() const;
    /// Bar code background color (0x000000 - 0xFFFFFF)
    ASPOSE_WORDS_SHARED_API void set_BackgroundColor(const System::String& value);
    /// Rotation of the barcode symbol. Valid values are [0, 3].
    ASPOSE_WORDS_SHARED_API System::String get_SymbolRotation() const;
    /// Rotation of the barcode symbol. Valid values are [0, 3].
    ASPOSE_WORDS_SHARED_API void set_SymbolRotation(const System::String& value);
    /// Scaling factor for the symbol. The value is in whole percentage points and the valid values are [10, 1000].
    ASPOSE_WORDS_SHARED_API System::String get_ScalingFactor() const;
    /// Scaling factor for the symbol. The value is in whole percentage points and the valid values are [10, 1000].
    ASPOSE_WORDS_SHARED_API void set_ScalingFactor(const System::String& value);
    /// Style of a Point of Sale barcode (barcode types UPCA|UPCE|EAN13|EAN8). The valid values (case insensitive) are [STD|SUP2|SUP5|CASE].
    ASPOSE_WORDS_SHARED_API System::String get_PosCodeStyle() const;
    /// Style of a Point of Sale barcode (barcode types UPCA|UPCE|EAN13|EAN8). The valid values (case insensitive) are [STD|SUP2|SUP5|CASE].
    ASPOSE_WORDS_SHARED_API void set_PosCodeStyle(const System::String& value);
    /// Style of a Case Code for barcode type ITF14. The valid values are [STD|EXT|ADD]
    ASPOSE_WORDS_SHARED_API System::String get_CaseCodeStyle() const;
    /// Style of a Case Code for barcode type ITF14. The valid values are [STD|EXT|ADD]
    ASPOSE_WORDS_SHARED_API void set_CaseCodeStyle(const System::String& value);
    /// Error correction level of QR Code. Valid values are [0, 3].
    ASPOSE_WORDS_SHARED_API System::String get_ErrorCorrectionLevel() const;
    /// Error correction level of QR Code. Valid values are [0, 3].
    ASPOSE_WORDS_SHARED_API void set_ErrorCorrectionLevel(const System::String& value);
    /// Whether to display barcode data (text) along with image.
    ASPOSE_WORDS_SHARED_API bool get_DisplayText() const;
    /// Whether to display barcode data (text) along with image.
    ASPOSE_WORDS_SHARED_API void set_DisplayText(bool value);
    /// Whether to add Start/Stop characters for barcode types NW7 and CODE39.
    ASPOSE_WORDS_SHARED_API bool get_AddStartStopChar() const;
    /// Whether to add Start/Stop characters for barcode types NW7 and CODE39.
    ASPOSE_WORDS_SHARED_API void set_AddStartStopChar(bool value);
    /// Whether to fix the check digit if it’s invalid.
    ASPOSE_WORDS_SHARED_API bool get_FixCheckDigit() const;
    /// Whether to fix the check digit if it’s invalid.
    ASPOSE_WORDS_SHARED_API void set_FixCheckDigit(bool value);
    /// Barcode postal address.
    ASPOSE_WORDS_SHARED_API System::String get_PostalAddress() const;
    /// Barcode postal address.
    ASPOSE_WORDS_SHARED_API void set_PostalAddress(const System::String& value);
    /// Whether <see cref="Aspose::Words::Fields::BarcodeParameters::get_PostalAddress">PostalAddress</see> is the name of a bookmark.
    ASPOSE_WORDS_SHARED_API bool get_IsBookmark() const;
    /// Whether <see cref="Aspose::Words::Fields::BarcodeParameters::get_PostalAddress">PostalAddress</see> is the name of a bookmark.
    ASPOSE_WORDS_SHARED_API void set_IsBookmark(bool value);
    /// Type of a Facing Identification Mark (FIM).
    ASPOSE_WORDS_SHARED_API System::String get_FacingIdentificationMark() const;
    /// Type of a Facing Identification Mark (FIM).
    ASPOSE_WORDS_SHARED_API void set_FacingIdentificationMark(const System::String& value);
    /// Whether <see cref="Aspose::Words::Fields::BarcodeParameters::get_PostalAddress">PostalAddress</see> is a U.S. postal address.
    ASPOSE_WORDS_SHARED_API bool get_IsUSPostalAddress() const;
    /// Whether <see cref="Aspose::Words::Fields::BarcodeParameters::get_PostalAddress">PostalAddress</see> is a U.S. postal address.
    ASPOSE_WORDS_SHARED_API void set_IsUSPostalAddress(bool value);

    ASPOSE_WORDS_SHARED_API BarcodeParameters();

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    System::String mField3;
    System::String mField4;
    System::String mField5;
    System::String mField6;
    System::String mField7;
    System::String mField8;
    System::String mField9;
    __TypeStub<1,1,1,1>::type mField10;
    __TypeStub<1,1,1,1>::type mField11;
    __TypeStub<1,1,1,1>::type mField12;
    System::String mField13;
    __TypeStub<1,1,1,1>::type mField14;
    System::String mField15;
    __TypeStub<1,1,1,1>::type mField16;

};

}
}
}
