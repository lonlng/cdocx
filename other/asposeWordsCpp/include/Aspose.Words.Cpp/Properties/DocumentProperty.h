//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Properties/DocumentProperty.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Properties/PropertyType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class DateTime;
}

namespace Aspose {

namespace Words {

namespace Properties {

/// Represents a custom or built-in document property.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-document-properties/">Work with Document Properties</a> documentation article.
/// 
/// @sa Aspose::Words::Properties::DocumentPropertyCollection
class ASPOSE_WORDS_SHARED_CLASS DocumentProperty : public System::Object
{
    typedef DocumentProperty ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the name of the property.
    /// 
    /// Cannot be <c>%null</c> and cannot be an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Gets the value of the property.
    /// 
    /// Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Object> get_Value();
    /// Sets the value of the property.
    /// 
    /// Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Value(const System::SharedPtr<System::Object>& value);
    /// Gets the data type of the property.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Properties::PropertyType get_Type() const;
    /// Gets the source of a linked custom document property.
    ASPOSE_WORDS_SHARED_API System::String get_LinkSource() const;
    /// Shows whether this property is linked to content or not.
    ASPOSE_WORDS_SHARED_API bool get_IsLinkToContent();

    /// Returns the property value as a string formatted according to the current locale.
    /// 
    /// Converts a boolean property into "Y" or "N".
    /// Converts a date property into a short date string.
    /// For all other types converts a property using Object.ToString().
    ASPOSE_WORDS_SHARED_API System::String ToString() const override;
    /// Returns the property value as integer.
    ASPOSE_WORDS_SHARED_API int32_t ToInt();
    /// Returns the property value as double.
    ASPOSE_WORDS_SHARED_API double ToDouble();
    /// Returns the property value as <b>%DateTime</b> in UTC.
    /// 
    /// Throws an exception if the property type is not <see cref="Aspose::Words::Properties::PropertyType::DateTime">DateTime</see>.
    /// 
    /// %Microsoft Word stores only the date part (no time) for custom date properties.
    ASPOSE_WORDS_SHARED_API System::DateTime ToDateTime();
    /// Returns the property value as bool.
    /// 
    /// Throws an exception if the property type is not <see cref="Aspose::Words::Properties::PropertyType::Boolean">Boolean</see>.
    ASPOSE_WORDS_SHARED_API bool ToBool();
    /// Returns the property value as byte array.
    /// 
    /// Throws an exception if the property type is not <see cref="Aspose::Words::Properties::PropertyType::ByteArray">ByteArray</see>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> ToByteArray();

protected:

private:

    System::String mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;

protected:

};

}
}
}
