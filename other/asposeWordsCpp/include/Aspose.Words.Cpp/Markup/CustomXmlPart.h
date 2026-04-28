//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/CustomXmlPart.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Markup
{
class CustomXmlSchemaCollection;
}

}
}

namespace Aspose {

namespace Words {

namespace Markup {

/// Represents a Custom XML Data Storage Part (custom XML data within a package).
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// A DOCX or DOC document can contain one or more Custom XML Data Storage parts. %Aspose.Words preserves and
/// allows to create and extract Custom XML Data via the <see cref="Aspose::Words::Document::get_CustomXmlParts">CustomXmlParts</see> collection.
/// 
/// @sa Aspose::Words::Document::get_CustomXmlParts
/// @sa Aspose::Words::Markup::CustomXmlPartCollection
class ASPOSE_WORDS_SHARED_CLASS CustomXmlPart : public System::Object
{
    typedef CustomXmlPart ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the string that identifies this custom XML part within an OOXML document.
    /// 
    /// ISO/IEC 29500 specifies that this value is a GUID, but old versions of %Microsoft Word allowed any
    /// string here. %Aspose.Words does the same for ECMA-376 format. But note, that %Microsoft Word Online fails
    /// to open a document created with a non-GUID value. So, a GUID is preferred value for this property.
    /// 
    /// A valid value must be an identifier that is unique among all custom XML data parts in this document.
    /// 
    /// The default value is an empty string. The value cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Id() const;
    /// Setter for Aspose::Words::Markup::CustomXmlPart::get_Id
    ASPOSE_WORDS_SHARED_API void set_Id(const System::String& value);
    /// Specifies the set of XML schemas that are associated with this custom XML part.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlSchemaCollection> get_Schemas() const;
    /// Gets the XML content of this Custom XML Data Storage Part.
    /// 
    /// The default value is an empty byte array. The value cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_Data() const;
    /// Sets the XML content of this Custom XML Data Storage Part.
    /// 
    /// The default value is an empty byte array. The value cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Data(const System::ArrayPtr<uint8_t>& value);
    /// Specifies a cyclic redundancy check (CRC) checksum of the <see cref="Aspose::Words::Markup::CustomXmlPart::get_Data">Data</see> content.
    ASPOSE_WORDS_SHARED_API int64_t get_DataChecksum();

    /// Makes a "deep enough" copy of the object.
    /// Does not duplicate the bytes of the <see cref="Aspose::Words::Markup::CustomXmlPart::get_Data">Data</see> value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPart> Clone();

    ASPOSE_WORDS_SHARED_API CustomXmlPart();

protected:

private:

    System::String mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
}
