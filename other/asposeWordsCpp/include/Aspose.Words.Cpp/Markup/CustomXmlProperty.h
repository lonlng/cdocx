//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/CustomXmlProperty.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Represents a single custom XML attribute or a smart tag property.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// Used as an item of a <see cref="Aspose::Words::Markup::CustomXmlPropertyCollection">CustomXmlPropertyCollection</see> collection.
class ASPOSE_WORDS_SHARED_CLASS CustomXmlProperty : public System::Object
{
    typedef CustomXmlProperty ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the name of the custom XML attribute or smart tag property.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Gets or sets the namespace URI of the custom XML attribute or smart tag property.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Uri() const;
    /// Setter for Aspose::Words::Markup::CustomXmlProperty::get_Uri
    ASPOSE_WORDS_SHARED_API void set_Uri(const System::String& value);
    /// Gets or sets the value of the custom XML attribute or smart tag property.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Value() const;
    /// Setter for Aspose::Words::Markup::CustomXmlProperty::get_Value
    ASPOSE_WORDS_SHARED_API void set_Value(const System::String& value);

    /// Initializes a new instance of this class.
    /// 
    /// @param name The name of the property. Cannot be <c>%null</c>.
    /// @param uri The namespace URI of the property. Cannot be <c>%null</c>.
    /// @param value The value of the property. Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API CustomXmlProperty(const System::String& name, const System::String& uri, const System::String& value);

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;

};

}
}
}
