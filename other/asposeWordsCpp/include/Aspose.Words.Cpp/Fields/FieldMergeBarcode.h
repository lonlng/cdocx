//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldMergeBarcode.h
#pragma once

#include <Aspose.Words.Cpp/Fields/IMergeFieldSurrogate.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class FieldEnd;
class FieldSeparator;
class FieldStart;
enum class FieldSwitchType;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the MERGEBARCODE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldMergeBarcode : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IMergeFieldSurrogate
{
    typedef FieldMergeBarcode ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IMergeFieldSurrogate BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the node that represents the start of the field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() override;
    /// Gets the node that represents the field separator. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldSeparator> get_Separator() override;
    /// Gets the node that represents the field end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() override;
    /// Gets the barcode value.
    ASPOSE_WORDS_SHARED_API System::String get_BarcodeValue();
    /// Sets the barcode value.
    ASPOSE_WORDS_SHARED_API void set_BarcodeValue(const System::String& value);
    /// Gets the barcode type (QR, etc.)
    ASPOSE_WORDS_SHARED_API System::String get_BarcodeType();
    /// Sets the barcode type (QR, etc.)
    ASPOSE_WORDS_SHARED_API void set_BarcodeType(const System::String& value);
    /// Gets the height of the symbol. The units are in TWIPS (1/1440 inch).
    ASPOSE_WORDS_SHARED_API System::String get_SymbolHeight();
    /// Sets the height of the symbol. The units are in TWIPS (1/1440 inch).
    ASPOSE_WORDS_SHARED_API void set_SymbolHeight(const System::String& value);
    /// Gets the rotation of the barcode symbol. Valid values are [0, 3]
    ASPOSE_WORDS_SHARED_API System::String get_SymbolRotation();
    /// Sets the rotation of the barcode symbol. Valid values are [0, 3]
    ASPOSE_WORDS_SHARED_API void set_SymbolRotation(const System::String& value);
    /// Gets a scaling factor for the symbol. The value is in whole percentage points and the valid values are [10, 1000]
    ASPOSE_WORDS_SHARED_API System::String get_ScalingFactor();
    /// Sets a scaling factor for the symbol. The value is in whole percentage points and the valid values are [10, 1000]
    ASPOSE_WORDS_SHARED_API void set_ScalingFactor(const System::String& value);
    /// Gets the foreground color of the barcode symbol. Valid values are in the range [0, 0xFFFFFF]
    ASPOSE_WORDS_SHARED_API System::String get_ForegroundColor();
    /// Sets the foreground color of the barcode symbol. Valid values are in the range [0, 0xFFFFFF]
    ASPOSE_WORDS_SHARED_API void set_ForegroundColor(const System::String& value);
    /// Gets the background color of the barcode symbol. Valid values are in the range [0, 0xFFFFFF]
    ASPOSE_WORDS_SHARED_API System::String get_BackgroundColor();
    /// Sets the background color of the barcode symbol. Valid values are in the range [0, 0xFFFFFF]
    ASPOSE_WORDS_SHARED_API void set_BackgroundColor(const System::String& value);
    /// Gets the style of a Point of Sale barcode (barcode types UPCA|UPCE|EAN13|EAN8). The valid values (case insensitive) are [STD|SUP2|SUP5|CASE].
    ASPOSE_WORDS_SHARED_API System::String get_PosCodeStyle();
    /// Sets the style of a Point of Sale barcode (barcode types UPCA|UPCE|EAN13|EAN8). The valid values (case insensitive) are [STD|SUP2|SUP5|CASE].
    ASPOSE_WORDS_SHARED_API void set_PosCodeStyle(const System::String& value);
    /// Gets the style of a Case Code for barcode type ITF14. The valid values are [STD|EXT|ADD]
    ASPOSE_WORDS_SHARED_API System::String get_CaseCodeStyle();
    /// Sets the style of a Case Code for barcode type ITF14. The valid values are [STD|EXT|ADD]
    ASPOSE_WORDS_SHARED_API void set_CaseCodeStyle(const System::String& value);
    /// Gets an error correction level of QR Code. Valid values are [0, 3].
    ASPOSE_WORDS_SHARED_API System::String get_ErrorCorrectionLevel();
    /// Sets an error correction level of QR Code. Valid values are [0, 3].
    ASPOSE_WORDS_SHARED_API void set_ErrorCorrectionLevel(const System::String& value);
    /// Gets whether to display barcode data (text) along with image.
    ASPOSE_WORDS_SHARED_API bool get_DisplayText();
    /// Sets whether to display barcode data (text) along with image.
    ASPOSE_WORDS_SHARED_API void set_DisplayText(bool value);
    /// Gets whether to add Start/Stop characters for barcode types NW7 and CODE39.
    ASPOSE_WORDS_SHARED_API bool get_AddStartStopChar();
    /// Sets whether to add Start/Stop characters for barcode types NW7 and CODE39.
    ASPOSE_WORDS_SHARED_API void set_AddStartStopChar(bool value);
    /// Gets whether to fix the check digit if it’s invalid.
    ASPOSE_WORDS_SHARED_API bool get_FixCheckDigit();
    /// Sets whether to fix the check digit if it’s invalid.
    ASPOSE_WORDS_SHARED_API void set_FixCheckDigit(bool value);

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;
    System::String GetMergeFieldName() override;
    bool CanWorkAsMergeField() override;
    bool IsMergeValueRequired() override;

};

}
}
}
