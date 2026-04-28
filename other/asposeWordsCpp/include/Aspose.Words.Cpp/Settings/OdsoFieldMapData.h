//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/OdsoFieldMapData.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Settings/OdsoFieldMappingType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies how a column in the external data source shall be mapped to the predefined merge fields within the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// %Microsoft Word provides some predefined merge field names that it allows to insert into a document as MERGEFIELD or
/// use in the ADDRESSBLOCK or GREETINGLINE fields. The information specified in <see cref="Aspose::Words::Settings::OdsoFieldMapData">OdsoFieldMapData</see>
/// allows to map one column in the external data source to a single predefined merge field.
/// 
/// @sa Aspose::Words::Settings::OdsoFieldMapDataCollection
/// @sa Aspose::Words::Settings::Odso
class ASPOSE_WORDS_SHARED_CLASS OdsoFieldMapData : public System::Object
{
    typedef OdsoFieldMapData ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the zero-based index of the column within an external data source which shall be
    /// mapped to the local name of a specific MERGEFIELD field.
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_Column() const;
    /// Specifies the zero-based index of the column within an external data source which shall be
    /// mapped to the local name of a specific MERGEFIELD field.
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API void set_Column(int32_t value);
    /// Specifies the predefined merge field name which shall be mapped to the column number
    /// specified by the <see cref="Aspose::Words::Settings::OdsoFieldMapData::get_Column">Column</see> property within this field mapping.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_MappedName() const;
    /// Specifies the predefined merge field name which shall be mapped to the column number
    /// specified by the <see cref="Aspose::Words::Settings::OdsoFieldMapData::get_Column">Column</see> property within this field mapping.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_MappedName(const System::String& value);
    /// Specifies the column name within an external data source for the column whose
    /// index is specified by the <see cref="Aspose::Words::Settings::OdsoFieldMapData::get_Column">Column</see> property.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Specifies the column name within an external data source for the column whose
    /// index is specified by the <see cref="Aspose::Words::Settings::OdsoFieldMapData::get_Column">Column</see> property.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Specifies if a given mail merge field has been mapped to a column in the given external data source or not.
    /// The default value is <see cref="Aspose::Words::Settings::OdsoFieldMappingType::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::OdsoFieldMappingType get_Type() const;
    /// Specifies if a given mail merge field has been mapped to a column in the given external data source or not.
    /// The default value is <see cref="Aspose::Words::Settings::OdsoFieldMappingType::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API void set_Type(Aspose::Words::Settings::OdsoFieldMappingType value);

    /// Returns a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::OdsoFieldMapData> Clone();

    ASPOSE_WORDS_SHARED_API OdsoFieldMapData();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    System::String mField3;
    System::String mField4;
    __TypeStub<4,4,4,4>::type mField5;

};

}
}
}
