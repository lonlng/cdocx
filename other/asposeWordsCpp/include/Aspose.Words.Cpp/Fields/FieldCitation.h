//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldCitation.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Fields
{
class FieldCitation;
enum class FieldSwitchType;
class FieldUpdateAction;
}
class Node;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class ICollection;
template <typename> class IEnumerable;
template <typename> class IList;
}
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the CITATION field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldCitation : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldCitation ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets a value that matches the <b>%Tag</b> element's value of the source to insert.
    ASPOSE_WORDS_SHARED_API System::String get_SourceTag();
    /// Sets a value that matches the <b>%Tag</b> element's value of the source to insert.
    ASPOSE_WORDS_SHARED_API void set_SourceTag(const System::String& value);
    /// Gets the language ID that is used in conjunction with the specified bibliographic style to format the citation
    /// in the document.
    ASPOSE_WORDS_SHARED_API System::String get_FormatLanguageId();
    /// Sets the language ID that is used in conjunction with the specified bibliographic style to format the citation
    /// in the document.
    ASPOSE_WORDS_SHARED_API void set_FormatLanguageId(const System::String& value);
    /// Gets a prefix that is prepended to the citation.
    ASPOSE_WORDS_SHARED_API System::String get_Prefix();
    /// Sets a prefix that is prepended to the citation.
    ASPOSE_WORDS_SHARED_API void set_Prefix(const System::String& value);
    /// Gets a suffix that is appended to the citation.
    ASPOSE_WORDS_SHARED_API System::String get_Suffix();
    /// Sets a suffix that is appended to the citation.
    ASPOSE_WORDS_SHARED_API void set_Suffix(const System::String& value);
    /// Gets whether the author information is suppressed from the citation.
    ASPOSE_WORDS_SHARED_API bool get_SuppressAuthor();
    /// Sets whether the author information is suppressed from the citation.
    ASPOSE_WORDS_SHARED_API void set_SuppressAuthor(bool value);
    /// Gets whether the title information is suppressed from the citation.
    ASPOSE_WORDS_SHARED_API bool get_SuppressTitle();
    /// Sets whether the title information is suppressed from the citation.
    ASPOSE_WORDS_SHARED_API void set_SuppressTitle(bool value);
    /// Gets whether the year information is suppressed from the citation.
    ASPOSE_WORDS_SHARED_API bool get_SuppressYear();
    /// Sets whether the year information is suppressed from the citation.
    ASPOSE_WORDS_SHARED_API void set_SuppressYear(bool value);
    /// Gets a page number associated with the citation.
    ASPOSE_WORDS_SHARED_API System::String get_PageNumber();
    /// Sets a page number associated with the citation.
    ASPOSE_WORDS_SHARED_API void set_PageNumber(const System::String& value);
    /// Gets a volume number associated with the citation.
    ASPOSE_WORDS_SHARED_API System::String get_VolumeNumber();
    /// Sets a volume number associated with the citation.
    ASPOSE_WORDS_SHARED_API void set_VolumeNumber(const System::String& value);
    /// Gets a value that matches the <b>%Tag</b> element's value of another source to be included in the citation.
    ASPOSE_WORDS_SHARED_API System::String get_AnotherSourceTag();
    /// Sets a value that matches the <b>%Tag</b> element's value of another source to be included in the citation.
    ASPOSE_WORDS_SHARED_API void set_AnotherSourceTag(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldCitation();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
