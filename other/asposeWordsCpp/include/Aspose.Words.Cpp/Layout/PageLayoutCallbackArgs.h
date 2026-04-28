//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/PageLayoutCallbackArgs.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Layout/PageLayoutEvent.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;

}
}

namespace Aspose {

namespace Words {

namespace Layout {

/// An argument passed into <see cref="Aspose::Words::Layout::IPageLayoutCallback::Notify(System::SharedPtr<Aspose::Words::Layout::PageLayoutCallbackArgs>)">Notify()</see>To learn more, visit the <a href="https://docs.aspose.com/words/net/converting-to-fixed-page-format/">Converting to Fixed-page Format</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PageLayoutCallbackArgs : public System::Object
{
    typedef PageLayoutCallbackArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets event.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::PageLayoutEvent get_Event() const;
    /// Gets document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Document>& get_Document() const;
    /// Gets 0-based index of the page in the document this event relates to.
    /// Returns negative value if there is no associated page, or if page was removed during reflow.
    ASPOSE_WORDS_SHARED_API int32_t get_PageIndex();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;

};

}
}
}
