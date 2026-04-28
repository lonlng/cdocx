//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldIncludeText.h
#pragma once

#include <Aspose.Words.Cpp/Fields/IFieldIncludeTextCode.h>
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
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the INCLUDETEXT field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldIncludeText : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IFieldIncludeTextCode
{
    typedef FieldIncludeText ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IFieldIncludeTextCode BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the location of the document using an IRI.
    ASPOSE_WORDS_SHARED_API System::String get_SourceFullName() override;
    /// Sets the location of the document using an IRI.
    ASPOSE_WORDS_SHARED_API void set_SourceFullName(const System::String& value);
    /// Gets the name of the bookmark in the document to include.
    ASPOSE_WORDS_SHARED_API System::String get_BookmarkName() override;
    /// Sets the name of the bookmark in the document to include.
    ASPOSE_WORDS_SHARED_API void set_BookmarkName(const System::String& value);
    /// Gets whether to prevent fields in the included document from being updated.
    ASPOSE_WORDS_SHARED_API bool get_LockFields() override;
    /// Sets whether to prevent fields in the included document from being updated.
    ASPOSE_WORDS_SHARED_API void set_LockFields(bool value);
    /// Gets the name of the text converter for the format of the included file.
    ASPOSE_WORDS_SHARED_API System::String get_TextConverter() override;
    /// Sets the name of the text converter for the format of the included file.
    ASPOSE_WORDS_SHARED_API void set_TextConverter(const System::String& value);
    /// Gets the namespace mappings for XPath queries.
    ASPOSE_WORDS_SHARED_API System::String get_NamespaceMappings() override;
    /// Sets the namespace mappings for XPath queries.
    ASPOSE_WORDS_SHARED_API void set_NamespaceMappings(const System::String& value);
    /// Gets the location of XSL Transformation to format XML data.
    ASPOSE_WORDS_SHARED_API System::String get_XslTransformation() override;
    /// Sets the location of XSL Transformation to format XML data.
    ASPOSE_WORDS_SHARED_API void set_XslTransformation(const System::String& value);
    /// Gets XPath for the desired portion of the XML file.
    ASPOSE_WORDS_SHARED_API System::String get_XPath() override;
    /// Sets XPath for the desired portion of the XML file.
    ASPOSE_WORDS_SHARED_API void set_XPath(const System::String& value);
    /// Gets the encoding applied to the data within the referenced file.
    ASPOSE_WORDS_SHARED_API System::String get_Encoding();
    /// Sets the encoding applied to the data within the referenced file.
    ASPOSE_WORDS_SHARED_API void set_Encoding(const System::String& value);
    /// Gets the MIME type of the referenced file.
    ASPOSE_WORDS_SHARED_API System::String get_MimeType();
    /// Sets the MIME type of the referenced file.
    ASPOSE_WORDS_SHARED_API void set_MimeType(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldIncludeText();

private:

    int32_t get_SourceFullNameArgumentIndex() override;

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
