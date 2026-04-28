//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/WebExtensionProperty.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Specifies a web extension custom property.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-office-add-ins/">Work with Office Add-ins</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS WebExtensionProperty : public System::Object
{
    typedef WebExtensionProperty ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies a custom property name
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Specifies a custom property name
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Specifies a custom property value.
    ASPOSE_WORDS_SHARED_API System::String get_Value() const;
    /// Specifies a custom property value.
    ASPOSE_WORDS_SHARED_API void set_Value(const System::String& value);

    /// Creates web extension custom property with specified name and value.
    /// 
    /// @param name Property name.
    /// @param value Property value.
    ASPOSE_WORDS_SHARED_API WebExtensionProperty(const System::String& name, const System::String& value);

protected:

    WebExtensionProperty();

private:

    System::String mField0;
    System::String mField1;

};

}
}
}
