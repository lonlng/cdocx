//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MailMergeSettings.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Settings/MailMergeMainDocumentType.h>
#include <Aspose.Words.Cpp/Settings/MailMergeDestination.h>
#include <Aspose.Words.Cpp/Settings/MailMergeDataType.h>
#include <Aspose.Words.Cpp/Settings/MailMergeCheckErrors.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Settings
{

class Odso;
}

}
}

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies all of the mail merge information for a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// You can use this object to specify a mail merge data source for a document and this information
/// (along with the available data fields) will appear in %Microsoft Word when the user opens this document.
/// Or you can use this object to query mail merge settings that the user has specified in %Microsoft Word
/// for this document.
/// 
/// You do not normally need to create objects of this class directly because Mail merge settings
/// of a document are always available via the <see cref="Aspose::Words::Document::get_MailMergeSettings">MailMergeSettings</see> property.
/// 
/// To detect whether this document is a mail merge main document, check the value of the
/// <see cref="Aspose::Words::Settings::MailMergeSettings::get_MainDocumentType">MainDocumentType</see> property.
/// 
/// To remove mail merge settings and data source information from a document you can use the
/// <see cref="Aspose::Words::Settings::MailMergeSettings::Clear">Clear</see> method. %Aspose.Words will not write mail merge settings to a document if
/// the <see cref="Aspose::Words::Settings::MailMergeSettings::get_MainDocumentType">MainDocumentType</see> property is set to <see cref="Aspose::Words::Settings::MailMergeMainDocumentType::NotAMergeDocument">NotAMergeDocument</see>
/// or the <see cref="Aspose::Words::Settings::MailMergeSettings::get_DataType">DataType</see> property is set to <see cref="Aspose::Words::Settings::MailMergeDataType::None">None</see>.
/// 
/// The best way to learn how to use the properties of this object is to create a document with a desired
/// data source manually in %Microsoft Word and then open that document using %Aspose.Words and examine the properties
/// of the <see cref="Aspose::Words::Document::get_MailMergeSettings">MailMergeSettings</see> and <see cref="Aspose::Words::Settings::MailMergeSettings::get_Odso">Odso</see> objects. This is
/// a good approach to take if you want to learn how to programmatically configure a data source, for example.
/// 
/// %Aspose.Words preserves mail merge information when loading, saving and converting documents
/// between different formats, but does not use this information when performing its own mail merge
/// using the <see cref="Aspose::Words::MailMerging::MailMerge">MailMerge</see> object.
/// 
/// @sa Aspose::Words::Document::get_MailMergeSettings
class ASPOSE_WORDS_SHARED_CLASS MailMergeSettings : public System::Object
{
    typedef MailMergeSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the one-based index of the record from the data source which shall be displayed in %Microsoft Word. The default value is 1.
    ASPOSE_WORDS_SHARED_API int32_t get_ActiveRecord() const;
    /// Specifies the one-based index of the record from the data source which shall be displayed in %Microsoft Word. The default value is 1.
    ASPOSE_WORDS_SHARED_API void set_ActiveRecord(int32_t value);
    /// Specifies the column within the data source that contains e-mail addresses. The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_AddressFieldName() const;
    /// Specifies the column within the data source that contains e-mail addresses. The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_AddressFieldName(const System::String& value);
    /// Specifies the type of error reporting which shall be conducted by %Microsoft Word when performing a mail merge.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeCheckErrors::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::MailMergeCheckErrors get_CheckErrors() const;
    /// Specifies the type of error reporting which shall be conducted by %Microsoft Word when performing a mail merge.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeCheckErrors::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API void set_CheckErrors(Aspose::Words::Settings::MailMergeCheckErrors value);
    /// Specifies the connection string used to connect to an external data source. The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_ConnectString() const;
    /// Specifies the connection string used to connect to an external data source. The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_ConnectString(const System::String& value);
    /// Specifies the path to the mail-merge data source. The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_DataSource() const;
    /// Specifies the path to the mail-merge data source. The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_DataSource(const System::String& value);
    /// Specifies the type of the mail-merge data source and the method of data access.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeDataType::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::MailMergeDataType get_DataType() const;
    /// Specifies the type of the mail-merge data source and the method of data access.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeDataType::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API void set_DataType(Aspose::Words::Settings::MailMergeDataType value);
    /// Specifies how %Microsoft Word will output the results of a mail merge.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeDestination::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::MailMergeDestination get_Destination() const;
    /// Specifies how %Microsoft Word will output the results of a mail merge.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeDestination::Default">Default</see>.
    ASPOSE_WORDS_SHARED_API void set_Destination(Aspose::Words::Settings::MailMergeDestination value);
    /// Specifies how an application performing the mail merge shall handle blank lines in the merged documents resulting from the mail merge.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_DoNotSupressBlankLines() const;
    /// Specifies how an application performing the mail merge shall handle blank lines in the merged documents resulting from the mail merge.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_DoNotSupressBlankLines(bool value);
    /// Specifies the path to the mail-merge header source.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_HeaderSource() const;
    /// Specifies the path to the mail-merge header source.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_HeaderSource(const System::String& value);
    /// Not sure about this one.
    /// The %Microsoft Word Automation Reference suggests that this specifies that the query is executed every time the document
    /// is opened in %Microsoft Word. But the OOXML specification suggests that this specifies that the query contains a reference
    /// to an external query file which contains the actual query.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_LinkToQuery() const;
    /// Setter for Aspose::Words::Settings::MailMergeSettings::get_LinkToQuery
    ASPOSE_WORDS_SHARED_API void set_LinkToQuery(bool value);
    /// Specifies that the documents produced during a mail merge operation should be emailed as an attachment rather
    /// than the body of the actual e-mail. The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_MailAsAttachment() const;
    /// Specifies that the documents produced during a mail merge operation should be emailed as an attachment rather
    /// than the body of the actual e-mail. The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_MailAsAttachment(bool value);
    /// Specifies the text which shall appear in the subject line of the e-mails or faxes produced during mail merge.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_MailSubject() const;
    /// Specifies the text which shall appear in the subject line of the e-mails or faxes produced during mail merge.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_MailSubject(const System::String& value);
    /// Specifies the mail-merge main document type.
    /// The default value is <see cref="Aspose::Words::Settings::MailMergeMainDocumentType::Default">Default</see>.
    /// 
    /// The main document is the document that contains information that is the same for each version of the merged document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Settings::MailMergeMainDocumentType get_MainDocumentType() const;
    /// Setter for Aspose::Words::Settings::MailMergeSettings::get_MainDocumentType
    ASPOSE_WORDS_SHARED_API void set_MainDocumentType(Aspose::Words::Settings::MailMergeMainDocumentType value);
    /// Gets the object that specifies the Office Data Source Object (ODSO) settings.
    /// 
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::Odso> get_Odso() const;
    /// Sets the object that specifies the Office Data Source Object (ODSO) settings.
    /// 
    /// This object is never <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Odso(const System::SharedPtr<Aspose::Words::Settings::Odso>& value);
    /// Contains the Structured Query Language string that shall be run against the specified external data source to
    /// return the set of records which shall be imported into the document when the mail merge operation is performed.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Query() const;
    /// Contains the Structured Query Language string that shall be run against the specified external data source to
    /// return the set of records which shall be imported into the document when the mail merge operation is performed.
    /// The default value is an empty string.
    ASPOSE_WORDS_SHARED_API void set_Query(const System::String& value);
    /// Specifies that %Microsoft Word shall display the data from the specified external data source where merge fields
    /// have been inserted (e.g. preview merged data). The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ViewMergedData() const;
    /// Specifies that %Microsoft Word shall display the data from the specified external data source where merge fields
    /// have been inserted (e.g. preview merged data). The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ViewMergedData(bool value);

    /// Clears the mail merge settings in such a way that when the document is saved,
    /// no mail merge settings will be saved and it will become a normal document.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Returns a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::MailMergeSettings> Clone();

    ASPOSE_WORDS_SHARED_API MailMergeSettings();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;
    __TypeStub<4,4,4,4>::type mField2;
    System::String mField3;
    System::String mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    System::String mField8;
    __TypeStub<1,1,1,1>::type mField9;
    __TypeStub<1,1,1,1>::type mField10;
    System::String mField11;
    __TypeStub<4,4,4,4>::type mField12;
    System::SharedPtr<System::Object> mField13;
    System::String mField14;
    __TypeStub<1,1,1,1>::type mField15;
    __TypeStub<4,4,4,4>::type mField16;
    __TypeStub<4,4,4,4>::type mField17;
    __TypeStub<4,4,4,4>::type mField18;
    __TypeStub<4,4,4,4>::type mField19;

};

}
}
}
