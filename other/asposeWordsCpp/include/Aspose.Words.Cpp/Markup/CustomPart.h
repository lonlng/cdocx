//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/CustomPart.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Represents a custom (arbitrary content) part, that is not defined by the ISO/IEC 29500 standard.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// This class represents an OOXML part that is a target of an "unknown relationship".
/// All relationships not defined within ISO/IEC 29500 are considered "unknown relationships".
/// Unknown relationships are permitted within an Office Open XML document provided that they
/// conform to relationship markup guidelines.
/// 
/// %Microsoft Word preserves custom parts during open/save cycles. Some additional info can be found
/// here http://blogs.msdn.com/dmahugh/archive/2006/11/25/arbitrary-content-in-an-opc-package.aspx
/// 
/// %Aspose.Words also roundtrips custom parts and in addition, allows to programmatically access
/// such parts via the <see cref="Aspose::Words::Markup::CustomPart">CustomPart</see> and <see cref="Aspose::Words::Markup::CustomPartCollection">CustomPartCollection</see> objects.
/// 
/// Do not confuse custom parts with Custom XML Data. Use <see cref="Aspose::Words::Markup::CustomXmlPart">CustomXmlPart</see> if you need
/// to access Custom XML Data.
/// 
/// @sa Aspose::Words::Markup::CustomPartCollection
/// @sa Aspose::Words::Document::get_PackageCustomParts
class ASPOSE_WORDS_SHARED_CLASS CustomPart : public System::Object
{
    typedef CustomPart ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets this part's absolute name within the OOXML package or the target URL.
    /// 
    /// If the relationship target is internal, then this property is the absolute part name within the package.
    /// If the relationship target is external, then this property is the target URL.
    /// 
    /// The default value is an empty string. A valid value must be a non-empty string.
    /// 
    /// @sa Aspose::Words::Markup::CustomPart::get_IsExternal
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Setter for Aspose::Words::Markup::CustomPart::get_Name
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Gets or sets the relationship type from the parent part to this custom part.
    /// 
    /// The relationship type for a custom part must be "unknown" e.g. a custom relationship type,
    /// not one of the relationship types defined within ISO/IEC 29500.
    /// 
    /// The default value is an empty string. A valid value must be a non-empty string.
    ASPOSE_WORDS_SHARED_API System::String get_RelationshipType() const;
    /// Setter for Aspose::Words::Markup::CustomPart::get_RelationshipType
    ASPOSE_WORDS_SHARED_API void set_RelationshipType(const System::String& value);
    /// False if this custom part is stored inside the OOXML package. True if this custom part is an external target.
    /// 
    /// The default value is <c>%false</c>.
    /// 
    /// @sa Aspose::Words::Markup::CustomPart::get_Name
    ASPOSE_WORDS_SHARED_API bool get_IsExternal() const;
    /// Setter for Aspose::Words::Markup::CustomPart::get_IsExternal
    ASPOSE_WORDS_SHARED_API void set_IsExternal(bool value);
    /// Specifies the content type of this custom part.
    /// 
    /// This property is applicable only when <see cref="Aspose::Words::Markup::CustomPart::get_IsExternal">IsExternal</see> is <c>%false</c>.
    /// 
    /// The default value is an empty string. A valid value must be a non-empty string.
    ASPOSE_WORDS_SHARED_API System::String get_ContentType() const;
    /// Setter for Aspose::Words::Markup::CustomPart::get_ContentType
    ASPOSE_WORDS_SHARED_API void set_ContentType(const System::String& value);
    /// Contains the data of this custom part.
    /// 
    /// This property is applicable only when <see cref="Aspose::Words::Markup::CustomPart::get_IsExternal">IsExternal</see> is <c>%false</c>.
    /// 
    /// The default value is an empty byte array. The value cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_Data() const;
    /// Setter for Aspose::Words::Markup::CustomPart::get_Data
    ASPOSE_WORDS_SHARED_API void set_Data(const System::ArrayPtr<uint8_t>& value);

    /// Makes a "deep enough" copy of the object.
    /// Does not duplicate the bytes of the <see cref="Aspose::Words::Markup::CustomPart::get_Data">Data</see> value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomPart> Clone();

    ASPOSE_WORDS_SHARED_API CustomPart();

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    __TypeStub<1,1,1,1>::type mField3;
    System::String mField4;
    System::SharedPtr<System::Object> mField5;
    System::String mField6;

};

}
}
}
