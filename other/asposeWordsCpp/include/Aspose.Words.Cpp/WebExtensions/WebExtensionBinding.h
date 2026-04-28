//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/WebExtensionBinding.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/WebExtensions/WebExtensionBindingType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Specifies a binding relationship between a web extension and the data in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-office-add-ins/">Work with Office Add-ins</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS WebExtensionBinding : public System::Object
{
    typedef WebExtensionBinding ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the binding identifier.
    ASPOSE_WORDS_SHARED_API System::String get_Id() const;
    /// Specifies the binding identifier.
    ASPOSE_WORDS_SHARED_API void set_Id(const System::String& value);
    /// Specifies the binding type.
    ASPOSE_WORDS_SHARED_API Aspose::Words::WebExtensions::WebExtensionBindingType get_BindingType() const;
    /// Specifies the binding type.
    ASPOSE_WORDS_SHARED_API void set_BindingType(Aspose::Words::WebExtensions::WebExtensionBindingType value);
    /// Specifies the binding key used to map the binding entry in this list with the bound data in the document.
    ASPOSE_WORDS_SHARED_API System::String get_AppRef() const;
    /// Specifies the binding key used to map the binding entry in this list with the bound data in the document.
    ASPOSE_WORDS_SHARED_API void set_AppRef(const System::String& value);

    /// Creates web extension binding with specified parameters.
    /// 
    /// @param id Binding identifier.
    /// @param bindingType Binding type.
    /// @param appRef Binding key used to map the binding entry in this list with the bound data in the document.
    ASPOSE_WORDS_SHARED_API WebExtensionBinding(const System::String& id, Aspose::Words::WebExtensions::WebExtensionBindingType bindingType, const System::String& appRef);

protected:

    WebExtensionBinding();

private:

    System::String mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::String mField2;

};

}
}
}
