//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/WebExtensionBindingCollection.h
#pragma once

#include <Aspose.Words.Cpp/WebExtensions/WebExtensionBinding.h>
#include <Aspose.Words.Cpp/WebExtensions/BaseWebExtensionCollection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Specifies a list of web extension bindings.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-office-add-ins/">Work with Office Add-ins</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS WebExtensionBindingCollection : public Aspose::Words::WebExtensions::BaseWebExtensionCollection<System::SharedPtr<Aspose::Words::WebExtensions::WebExtensionBinding>>
{
    typedef WebExtensionBindingCollection ThisType;
    typedef Aspose::Words::WebExtensions::BaseWebExtensionCollection<System::SharedPtr<Aspose::Words::WebExtensions::WebExtensionBinding>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    ASPOSE_WORDS_SHARED_API void SetTemplateWeakPtr(uint32_t argument) override;

protected:

    WebExtensionBindingCollection();

    virtual ASPOSE_WORDS_SHARED_API ~WebExtensionBindingCollection();

};

}
}
}
