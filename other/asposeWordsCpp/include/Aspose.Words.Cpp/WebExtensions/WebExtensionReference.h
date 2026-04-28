//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/WebExtensionReference.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/WebExtensions/WebExtensionStoreType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Represents the reference to a web extension. The reference is used to identify the provider location and version of the
/// extension.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-office-add-ins/">Work with Office Add-ins</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS WebExtensionReference : public System::Object
{
    typedef WebExtensionReference ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Identifier associated with the web extension within a catalog provider.
    ASPOSE_WORDS_SHARED_API System::String get_Id() const;
    /// Identifier associated with the web extension within a catalog provider.
    ASPOSE_WORDS_SHARED_API void set_Id(const System::String& value);
    /// Specifies the version of the web extension.
    ASPOSE_WORDS_SHARED_API System::String get_Version() const;
    /// Specifies the version of the web extension.
    ASPOSE_WORDS_SHARED_API void set_Version(const System::String& value);
    /// Specifies the instance of the marketplace where the web extension is stored.
    ASPOSE_WORDS_SHARED_API System::String get_Store() const;
    /// Specifies the instance of the marketplace where the web extension is stored.
    ASPOSE_WORDS_SHARED_API void set_Store(const System::String& value);
    /// Specifies the type of marketplace.
    ASPOSE_WORDS_SHARED_API Aspose::Words::WebExtensions::WebExtensionStoreType get_StoreType() const;
    /// Specifies the type of marketplace.
    ASPOSE_WORDS_SHARED_API void set_StoreType(Aspose::Words::WebExtensions::WebExtensionStoreType value);

    ASPOSE_WORDS_SHARED_API WebExtensionReference();

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    __TypeStub<4,4,4,4>::type mField3;

};

}
}
}
