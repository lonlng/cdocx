//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldBibliography.h
#pragma once

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
enum class FieldSwitchType;
class FieldUpdateAction;
}
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
}
}
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the BIBLIOGRAPHY field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldBibliography : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldBibliography ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the language ID that is used to format the bibliographic sources in the document.
    ASPOSE_WORDS_SHARED_API System::String get_FormatLanguageId();
    /// Sets the language ID that is used to format the bibliographic sources in the document.
    ASPOSE_WORDS_SHARED_API void set_FormatLanguageId(const System::String& value);
    /// Gets the language ID that is used to filter the bibliographic data to only the sources in the document that
    /// use that language.
    ASPOSE_WORDS_SHARED_API System::String get_FilterLanguageId();
    /// Sets the language ID that is used to filter the bibliographic data to only the sources in the document that
    /// use that language.
    ASPOSE_WORDS_SHARED_API void set_FilterLanguageId(const System::String& value);
    /// Gets a value so that only the sources with matching Tag element value are displayed in the bibliography.
    ASPOSE_WORDS_SHARED_API System::String get_SourceTag();
    /// Sets a value so that only the sources with matching Tag element value are displayed in the bibliography.
    ASPOSE_WORDS_SHARED_API void set_SourceTag(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldBibliography();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
