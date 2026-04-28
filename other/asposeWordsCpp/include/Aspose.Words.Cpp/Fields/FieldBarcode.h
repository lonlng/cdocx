//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldBarcode.h
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
}
class NodeRange;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the BARCODE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldBarcode : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldBarcode ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the postal address used for generating a barcode or the name of the bookmark that refers to it.
    ASPOSE_WORDS_SHARED_API System::String get_PostalAddress();
    /// Sets the postal address used for generating a barcode or the name of the bookmark that refers to it.
    ASPOSE_WORDS_SHARED_API void set_PostalAddress(const System::String& value);
    /// Gets whether <see cref="Aspose::Words::Fields::FieldBarcode::get_PostalAddress">PostalAddress</see> is the name of a bookmark.
    ASPOSE_WORDS_SHARED_API bool get_IsBookmark();
    /// Sets whether <see cref="Aspose::Words::Fields::FieldBarcode::get_PostalAddress">PostalAddress</see> is the name of a bookmark.
    ASPOSE_WORDS_SHARED_API void set_IsBookmark(bool value);
    /// Gets the type of a Facing Identification Mark (FIM) to insert.
    ASPOSE_WORDS_SHARED_API System::String get_FacingIdentificationMark();
    /// Sets the type of a Facing Identification Mark (FIM) to insert.
    ASPOSE_WORDS_SHARED_API void set_FacingIdentificationMark(const System::String& value);
    /// Gets whether <see cref="Aspose::Words::Fields::FieldBarcode::get_PostalAddress">PostalAddress</see> is a U.S. postal address.
    ASPOSE_WORDS_SHARED_API bool get_IsUSPostalAddress();
    /// Sets whether <see cref="Aspose::Words::Fields::FieldBarcode::get_PostalAddress">PostalAddress</see> is a U.S. postal address.
    ASPOSE_WORDS_SHARED_API void set_IsUSPostalAddress(bool value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
