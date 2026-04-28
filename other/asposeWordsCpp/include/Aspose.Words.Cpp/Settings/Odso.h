//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/Odso.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Settings/OdsoDataSourceType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Settings
{
class OdsoFieldMapDataCollection;
class OdsoRecipientDataCollection;
}
}
}

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies the Office Data Source Object (ODSO) settings for a mail merge data source.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// ODSO seems to be the "new" way the newer %Microsoft Word versions prefer to use when specifying certain
/// types of data sources for a mail merge document. ODSO probably first appeared in %Microsoft Word 2000.
/// 
/// The use of ODSO is poorly documented and the best way to learn how to use the properties of this object
/// is to create a document with a desired data source manually in %Microsoft Word and then open that document using
/// %Aspose.Words and examine the properties of the <see cref="Aspose::Words::Document::get_MailMergeSettings">MailMergeSettings</see> and
/// <see cref="Aspose::Words::Settings::MailMergeSettings::get_Odso">Odso</see> objects. This is a good approach to take if you want to learn how to
/// programmatically configure a data source, for example.
/// 
/// You do not normally need to create objects of this class directly because ODSO settings
/// are always available via the <see cref="Aspose::Words::Settings::MailMergeSettings::get_Odso">Odso</see> property.
/// 
/// @sa Aspose::Words::Settings::MailMergeSettings::get_Odso
class ASPOSE_WORDS_SHARED_CLASS Odso : public System::Object
{
    typedef Odso ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the character which shall be interpreted as the column delimiter used to separate columns within external data sources.
    /// The default value is 0 which means there is no column delimiter defined.
    /// 
    /// RK I have never seen this in use.
    ASPOSE_WORDS_SHARED_API char16_t get_ColumnDelimiter() const;
    /// Setter for Aspose::Words::Settings::Odso::get_ColumnDelimiter
    ASPOSE_WORDS_SHARED_API void set_ColumnDelimiter(char16_t value);
    /// Specifies that a hosting application shall treat the first row of data in the specified external data
    /// source as a header row containing the names of each column in the data source.
    /// The default value is <c>%false</c>.
    /// 
    /// RK I have never seen this in use.
    ASPOSE_WORDS_SHARED_API bool get_FirstRowContainsColumnNames() const;
    /// Setter for Aspose::Words::Settings::Odso::get_FirstRowContainsColumnNames
    ASPOSE_WORDS_SHARED_API void set_FirstRowContainsColumnNames(bool value);
    /// Specifies the location of the external data source to be connected to a document to perform the mail merge.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_DataSource() const;
    /// Specifies the location of the external data source to be connected to a document to perform the mail merge.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_DataSource(const System::String& value);
    /// Specifies the particular set of data that a source shall be connected to within an external data source.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_TableName() const;
    /// Specifies the particular set of data that a source shall be connected to within an external data source.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_TableName(const System::String& value);
    /// Specifies the type of the external data source to be connected to as part of the ODSO connection information for this mail merge.
    /// The default value is <see cref="Aspose::Words::Settings::OdsoDataSourceType::Default">Default</see>.
    /// 
    /// This setting is purely a suggestion of the data source type that is being used for this mail merge.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::OdsoDataSourceType get_DataSourceType() const;
    /// Setter for Aspose::Words::Settings::Odso::get_DataSourceType
    ASPOSE_WORDS_SHARED_API void set_DataSourceType(Aspose::Words::Settings::OdsoDataSourceType value);
    /// Specifies the Universal Data Link (UDL) connection string used to connect to an external data source.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_UdlConnectString() const;
    /// Specifies the Universal Data Link (UDL) connection string used to connect to an external data source.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_UdlConnectString(const System::String& value);
    /// Gets a collection of objects that specify how columns from the external data source
    /// are mapped to the predefined merge field names in the document.
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::OdsoFieldMapDataCollection> get_FieldMapDatas() const;
    /// Sets a collection of objects that specify how columns from the external data source
    /// are mapped to the predefined merge field names in the document.
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_FieldMapDatas(const System::SharedPtr<Aspose::Words::Settings::OdsoFieldMapDataCollection>& value);
    /// Gets a collection of objects that specify inclusion/exclusion of individual records in the mail merge.
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::OdsoRecipientDataCollection> get_RecipientDatas() const;
    /// Sets a collection of objects that specify inclusion/exclusion of individual records in the mail merge.
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_RecipientDatas(const System::SharedPtr<Aspose::Words::Settings::OdsoRecipientDataCollection>& value);

    /// Returns a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::Odso> Clone();

    ASPOSE_WORDS_SHARED_API Odso();

private:

    __TypeStub<2,2,2,2>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    System::String mField2;
    System::String mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::String mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;

};

}
}
}
