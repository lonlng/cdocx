//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/OdsoRecipientData.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Represents information about a single record within an external data source that is to be excluded from the mail merge.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// If a record shall be merged into a merged document, then no information is needed about that record.
/// However, if a given record shall not be merged into a merged document, then the value of the unique key
/// for that record shall be stored in the <see cref="Aspose::Words::Settings::OdsoRecipientData::get_UniqueTag">UniqueTag</see> property of this object to indicate this exclusion.
class ASPOSE_WORDS_SHARED_CLASS OdsoRecipientData : public System::Object
{
    typedef OdsoRecipientData ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether the record from the data source shall be imported into a document when the mail merge is performed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_Active() const;
    /// Specifies whether the record from the data source shall be imported into a document when the mail merge is performed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_Active(bool value);
    /// Specifies the column within the data source that contains unique data for the current record.
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_Column() const;
    /// Specifies the column within the data source that contains unique data for the current record.
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API void set_Column(int32_t value);
    /// Specifies the contents of a given record in the column containing unique data.
    /// The default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_UniqueTag() const;
    /// Specifies the contents of a given record in the column containing unique data.
    /// The default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_UniqueTag(const System::ArrayPtr<uint8_t>& value);
    /// Represents the hash code for this record.
    /// Sometimes %Microsoft Word uses <see cref="Aspose::Words::Settings::OdsoRecipientData::get_Hash">Hash</see> of a whole record instead of a <see cref="Aspose::Words::Settings::OdsoRecipientData::get_UniqueTag">UniqueTag</see> value.
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_Hash() const;
    /// Represents the hash code for this record.
    /// Sometimes %Microsoft Word uses <see cref="Aspose::Words::Settings::OdsoRecipientData::get_Hash">Hash</see> of a whole record instead of a <see cref="Aspose::Words::Settings::OdsoRecipientData::get_UniqueTag">UniqueTag</see> value.
    /// The default value is 0.
    ASPOSE_WORDS_SHARED_API void set_Hash(int32_t value);

    /// Returns a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Settings::OdsoRecipientData> Clone();

    ASPOSE_WORDS_SHARED_API OdsoRecipientData();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::SharedPtr<System::Object> mField2;
    __TypeStub<4,4,4,4>::type mField3;

};

}
}
}
