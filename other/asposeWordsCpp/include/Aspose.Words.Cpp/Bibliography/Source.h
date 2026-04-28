//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/Source.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Bibliography/SourceType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Bibliography
{

class ContributorCollection;

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

namespace Bibliography {

/// Represents an individual source, such as a book, journal article, or interview.
class ASPOSE_WORDS_SHARED_CLASS Source final : public System::Object
{
    typedef Source ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the locale ID of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Lcid() const;
    /// Sets the locale ID of a source.
    ASPOSE_WORDS_SHARED_API void set_Lcid(const System::String& value);
    /// Gets contributors list (author, editor, writer etc) of a source.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Bibliography::ContributorCollection>& get_Contributors() const;
    /// Gets the source type of a source.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Bibliography::SourceType get_SourceType() const;
    /// Sets the source type of a source.
    ASPOSE_WORDS_SHARED_API void set_SourceType(Aspose::Words::Bibliography::SourceType value);
    /// Gets the abbreviated case number of a source.
    ASPOSE_WORDS_SHARED_API System::String get_AbbreviatedCaseNumber() const;
    /// Sets the abbreviated case number of a source.
    ASPOSE_WORDS_SHARED_API void set_AbbreviatedCaseNumber(const System::String& value);
    /// Gets the album title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_AlbumTitle() const;
    /// Sets the album title of a source.
    ASPOSE_WORDS_SHARED_API void set_AlbumTitle(const System::String& value);
    /// Gets the book title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_BookTitle() const;
    /// Sets the book title of a source.
    ASPOSE_WORDS_SHARED_API void set_BookTitle(const System::String& value);
    /// Gets the broadcaster of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Broadcaster() const;
    /// Sets the broadcaster of a source.
    ASPOSE_WORDS_SHARED_API void set_Broadcaster(const System::String& value);
    /// Gets the broadcast title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_BroadcastTitle() const;
    /// Sets the broadcast title of a source.
    ASPOSE_WORDS_SHARED_API void set_BroadcastTitle(const System::String& value);
    /// Gets the case number of a source.
    ASPOSE_WORDS_SHARED_API System::String get_CaseNumber() const;
    /// Sets the case number of a source.
    ASPOSE_WORDS_SHARED_API void set_CaseNumber(const System::String& value);
    /// Gets the chapter number of a source.
    ASPOSE_WORDS_SHARED_API System::String get_ChapterNumber() const;
    /// Sets the chapter number of a source.
    ASPOSE_WORDS_SHARED_API void set_ChapterNumber(const System::String& value);
    /// Gets the city of a source.
    ASPOSE_WORDS_SHARED_API System::String get_City() const;
    /// Sets the city of a source.
    ASPOSE_WORDS_SHARED_API void set_City(const System::String& value);
    /// Gets the comments of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Comments() const;
    /// Sets the comments of a source.
    ASPOSE_WORDS_SHARED_API void set_Comments(const System::String& value);
    /// Gets the conference or proceedings name of a source.
    ASPOSE_WORDS_SHARED_API System::String get_ConferenceName() const;
    /// Sets the conference or proceedings name of a source.
    ASPOSE_WORDS_SHARED_API void set_ConferenceName(const System::String& value);
    /// Gets the country or region of a source.
    ASPOSE_WORDS_SHARED_API System::String get_CountryOrRegion() const;
    /// Sets the country or region of a source.
    ASPOSE_WORDS_SHARED_API void set_CountryOrRegion(const System::String& value);
    /// Gets the court of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Court() const;
    /// Sets the court of a source.
    ASPOSE_WORDS_SHARED_API void set_Court(const System::String& value);
    /// Gets the day of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Day() const;
    /// Sets the day of a source.
    ASPOSE_WORDS_SHARED_API void set_Day(const System::String& value);
    /// Gets the day accessed of a source.
    ASPOSE_WORDS_SHARED_API System::String get_DayAccessed() const;
    /// Sets the day accessed of a source.
    ASPOSE_WORDS_SHARED_API void set_DayAccessed(const System::String& value);
    /// Gets the department of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Department() const;
    /// Sets the department of a source.
    ASPOSE_WORDS_SHARED_API void set_Department(const System::String& value);
    /// Gets the distributor of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Distributor() const;
    /// Sets the distributor of a source.
    ASPOSE_WORDS_SHARED_API void set_Distributor(const System::String& value);
    /// Gets the editor of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Edition() const;
    /// Sets the editor of a source.
    ASPOSE_WORDS_SHARED_API void set_Edition(const System::String& value);
    /// Gets the guid of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Guid() const;
    /// Sets the guid of a source.
    ASPOSE_WORDS_SHARED_API void set_Guid(const System::String& value);
    /// Gets the institution of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Institution() const;
    /// Sets the institution of a source.
    ASPOSE_WORDS_SHARED_API void set_Institution(const System::String& value);
    /// Gets the internet site title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_InternetSiteTitle() const;
    /// Sets the internet site title of a source.
    ASPOSE_WORDS_SHARED_API void set_InternetSiteTitle(const System::String& value);
    /// Gets the issue of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Issue() const;
    /// Sets the issue of a source.
    ASPOSE_WORDS_SHARED_API void set_Issue(const System::String& value);
    /// Gets the journal name of a source.
    ASPOSE_WORDS_SHARED_API System::String get_JournalName() const;
    /// Sets the journal name of a source.
    ASPOSE_WORDS_SHARED_API void set_JournalName(const System::String& value);
    /// Gets the medium of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Medium() const;
    /// Sets the medium of a source.
    ASPOSE_WORDS_SHARED_API void set_Medium(const System::String& value);
    /// Gets the month of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Month() const;
    /// Sets the month of a source.
    ASPOSE_WORDS_SHARED_API void set_Month(const System::String& value);
    /// Gets the month accessed of a source.
    ASPOSE_WORDS_SHARED_API System::String get_MonthAccessed() const;
    /// Sets the month accessed of a source.
    ASPOSE_WORDS_SHARED_API void set_MonthAccessed(const System::String& value);
    /// Gets the number of volumes of a source.
    ASPOSE_WORDS_SHARED_API System::String get_NumberVolumes() const;
    /// Sets the number of volumes of a source.
    ASPOSE_WORDS_SHARED_API void set_NumberVolumes(const System::String& value);
    /// Gets the pages of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Pages() const;
    /// Sets the pages of a source.
    ASPOSE_WORDS_SHARED_API void set_Pages(const System::String& value);
    /// Gets the patent number of a source.
    ASPOSE_WORDS_SHARED_API System::String get_PatentNumber() const;
    /// Sets the patent number of a source.
    ASPOSE_WORDS_SHARED_API void set_PatentNumber(const System::String& value);
    /// Gets the periodical title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_PeriodicalTitle() const;
    /// Sets the periodical title of a source.
    ASPOSE_WORDS_SHARED_API void set_PeriodicalTitle(const System::String& value);
    /// Gets the production company of a source.
    ASPOSE_WORDS_SHARED_API System::String get_ProductionCompany() const;
    /// Sets the production company of a source.
    ASPOSE_WORDS_SHARED_API void set_ProductionCompany(const System::String& value);
    /// Gets the publication title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_PublicationTitle() const;
    /// Sets the publication title of a source.
    ASPOSE_WORDS_SHARED_API void set_PublicationTitle(const System::String& value);
    /// Gets the publisher of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Publisher() const;
    /// Sets the publisher of a source.
    ASPOSE_WORDS_SHARED_API void set_Publisher(const System::String& value);
    /// Gets the recording number of a source.
    ASPOSE_WORDS_SHARED_API System::String get_RecordingNumber() const;
    /// Sets the recording number of a source.
    ASPOSE_WORDS_SHARED_API void set_RecordingNumber(const System::String& value);
    /// Gets the reference order of a source.
    ASPOSE_WORDS_SHARED_API System::String get_RefOrder() const;
    /// Sets the reference order of a source.
    ASPOSE_WORDS_SHARED_API void set_RefOrder(const System::String& value);
    /// Gets the reporter of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Reporter() const;
    /// Sets the reporter of a source.
    ASPOSE_WORDS_SHARED_API void set_Reporter(const System::String& value);
    /// Gets the short title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_ShortTitle() const;
    /// Sets the short title of a source.
    ASPOSE_WORDS_SHARED_API void set_ShortTitle(const System::String& value);
    /// Gets the standard number of a source.
    ASPOSE_WORDS_SHARED_API System::String get_StandardNumber() const;
    /// Sets the standard number of a source.
    ASPOSE_WORDS_SHARED_API void set_StandardNumber(const System::String& value);
    /// Gets the state or province of a source.
    ASPOSE_WORDS_SHARED_API System::String get_StateOrProvince() const;
    /// Sets the state or province of a source.
    ASPOSE_WORDS_SHARED_API void set_StateOrProvince(const System::String& value);
    /// Gets the station of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Station() const;
    /// Sets the station of a source.
    ASPOSE_WORDS_SHARED_API void set_Station(const System::String& value);
    /// Gets the identifying tag name of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Tag() const;
    /// Sets the identifying tag name of a source.
    ASPOSE_WORDS_SHARED_API void set_Tag(const System::String& value);
    /// Gets the theater of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Theater() const;
    /// Sets the theater of a source.
    ASPOSE_WORDS_SHARED_API void set_Theater(const System::String& value);
    /// Gets the thesis type of a source.
    ASPOSE_WORDS_SHARED_API System::String get_ThesisType() const;
    /// Sets the thesis type of a source.
    ASPOSE_WORDS_SHARED_API void set_ThesisType(const System::String& value);
    /// Gets the title of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Title() const;
    /// Sets the title of a source.
    ASPOSE_WORDS_SHARED_API void set_Title(const System::String& value);
    /// Gets the type of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Type() const;
    /// Sets the type of a source.
    ASPOSE_WORDS_SHARED_API void set_Type(const System::String& value);
    /// Gets the url of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Url() const;
    /// Sets the url of a source.
    ASPOSE_WORDS_SHARED_API void set_Url(const System::String& value);
    /// Gets the version of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Version() const;
    /// Sets the version of a source.
    ASPOSE_WORDS_SHARED_API void set_Version(const System::String& value);
    /// Gets the volume of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Volume() const;
    /// Sets the volume of a source.
    ASPOSE_WORDS_SHARED_API void set_Volume(const System::String& value);
    /// Gets the year of a source.
    ASPOSE_WORDS_SHARED_API System::String get_Year() const;
    /// Sets the year of a source.
    ASPOSE_WORDS_SHARED_API void set_Year(const System::String& value);
    /// Gets the year accessed of a source.
    ASPOSE_WORDS_SHARED_API System::String get_YearAccessed() const;
    /// Sets the year accessed of a source.
    ASPOSE_WORDS_SHARED_API void set_YearAccessed(const System::String& value);
    /// Gets the digital object identifier.
    ASPOSE_WORDS_SHARED_API System::String get_Doi() const;
    /// Sets the digital object identifier.
    ASPOSE_WORDS_SHARED_API void set_Doi(const System::String& value);

    /// Initialize a new instance of the <see cref="Aspose::Words::Bibliography::Source">Source</see> class.
    /// 
    /// @param tag The identifying tag name.
    /// @param sourceType The source type.
    ASPOSE_WORDS_SHARED_API Source(const System::String& tag, Aspose::Words::Bibliography::SourceType sourceType);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Source();

private:

    __TypeStub<4,4,4,4>::type mField0;

    __TypeStub<1,1,1,1>::type mField1;

    System::SharedPtr<System::Object> mField2;

    __TypeStub<4,4,4,4>::type mField3;
    System::String mField4;
    System::String mField5;
    System::String mField6;
    System::String mField7;
    System::String mField8;
    System::String mField9;
    System::String mField10;
    System::String mField11;
    System::String mField12;
    System::String mField13;
    System::String mField14;
    System::String mField15;
    System::String mField16;
    System::String mField17;
    System::String mField18;
    System::String mField19;
    System::String mField20;
    System::String mField21;
    System::String mField22;
    System::String mField23;
    System::String mField24;
    System::String mField25;
    System::String mField26;
    System::String mField27;
    System::String mField28;
    System::String mField29;
    System::String mField30;
    System::String mField31;
    System::String mField32;
    System::String mField33;
    System::String mField34;
    System::String mField35;
    System::String mField36;
    System::String mField37;
    System::String mField38;
    System::String mField39;
    System::String mField40;
    System::String mField41;
    System::String mField42;
    System::String mField43;
    System::String mField44;
    System::String mField45;
    System::String mField46;
    System::String mField47;
    System::String mField48;
    System::String mField49;
    System::String mField50;
    System::String mField51;
    System::String mField52;
    System::String mField53;
    System::String mField54;
    System::String mField55;
    __TypeStub<4,4,4,4>::type mField56;

};

}
}
}
