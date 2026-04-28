//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/MailMergeRegionInfo.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class Field;
class FieldMergeField;
}
namespace MailMerging
{

class MustacheTag;
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

namespace MailMerging {

/// Contains information about a mail merge region.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS MailMergeRegionInfo : public System::Object
{
    typedef MailMergeRegionInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns parent region info (null for top-level region).
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::MailMerging::MailMergeRegionInfo>& get_ParentRegion() const;
    /// Returns a list of child regions.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::MailMerging::MailMergeRegionInfo>>>& get_Regions() const;
    /// Returns a list of child fields.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::Fields::Field>>>& get_Fields() const;
    /// Returns a list of child "mustache" tags.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::MailMerging::MustacheTag>>>& get_MustacheTags() const;
    /// Returns the name of region.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Returns a start field for the region.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::FieldMergeField>& get_StartField() const;
    /// Returns a start "mustache" tag for the region.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::MailMerging::MustacheTag>& get_StartMustacheTag() const;
    /// Returns an end field for the region.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fields::FieldMergeField>& get_EndField() const;
    /// Returns an end "mustache" tag for the region.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::MailMerging::MustacheTag>& get_EndMustacheTag() const;
    /// Returns the nesting level for the region.
    ASPOSE_WORDS_SHARED_API int32_t get_Level() const;

protected:

    MailMergeRegionInfo();

    virtual ASPOSE_WORDS_SHARED_API ~MailMergeRegionInfo();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::String mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;

    System::SharedPtr<System::Object> mField7;

    System::SharedPtr<System::Object> mField8;

    __TypeStub<4,4,4,4>::type mField9;

};

}
}
}
