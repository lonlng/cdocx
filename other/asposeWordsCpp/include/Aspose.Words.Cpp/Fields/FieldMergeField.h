//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldMergeField.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/FieldType.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Bidi
{
class IBidiParagraphLevelOverride;
}
namespace Words
{
namespace Fields
{

class FieldEnd;

class FieldSeparator;
class FieldStart;
enum class FieldSwitchType;
class FieldUpdateAction;

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

namespace Fields {

/// Implements the MERGEFIELD field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldMergeField : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldMergeField ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

protected:

    /// MergeFieldType enumeration.
    enum class MergeFieldType
    {
        Common,
        Image,
        Barcode,
        RegionStart,
        RegionEnd
    };

public:

    /// Gets the %Microsoft Word field type.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldType get_Type() const override;
    /// Returns just the name of the data field. Any prefix is stripped to the prefix property.
    ASPOSE_WORDS_SHARED_API System::String get_FieldNameNoPrefix() const;
    /// Gets the name of a data field.
    ASPOSE_WORDS_SHARED_API System::String get_FieldName();
    /// Sets the name of a data field.
    ASPOSE_WORDS_SHARED_API void set_FieldName(const System::String& value);
    /// Gets the text to be inserted before the field if the field is not blank.
    ASPOSE_WORDS_SHARED_API System::String get_TextBefore();
    /// Sets the text to be inserted before the field if the field is not blank.
    ASPOSE_WORDS_SHARED_API void set_TextBefore(const System::String& value);
    /// Gets the text to be inserted after the field if the field is not blank.
    ASPOSE_WORDS_SHARED_API System::String get_TextAfter();
    /// Sets the text to be inserted after the field if the field is not blank.
    ASPOSE_WORDS_SHARED_API void set_TextAfter(const System::String& value);
    /// Gets whether this field is a mapped field.
    ASPOSE_WORDS_SHARED_API bool get_IsMapped();
    /// Sets whether this field is a mapped field.
    ASPOSE_WORDS_SHARED_API void set_IsMapped(bool value);
    /// Gets whether to enable character conversion for vertical formatting.
    ASPOSE_WORDS_SHARED_API bool get_IsVerticalFormatting();
    /// Sets whether to enable character conversion for vertical formatting.
    ASPOSE_WORDS_SHARED_API void set_IsVerticalFormatting(bool value);

protected:

    FieldMergeField();

    ASPOSE_WORDS_SHARED_API void Initialize(System::SharedPtr<Aspose::Words::Fields::FieldStart> , System::SharedPtr<Aspose::Words::Fields::FieldSeparator> , System::SharedPtr<Aspose::Words::Fields::FieldEnd> ) override;
    ASPOSE_WORDS_SHARED_API void ParseFieldCode() override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;
    ASPOSE_WORDS_SHARED_API void EndUpdate() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Bidi::IBidiParagraphLevelOverride> GetBidiParagraphLevelOverride() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldMergeField();

private:

    System::String mField0;

    System::String mField1;

    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

private:

};

}
}
}
