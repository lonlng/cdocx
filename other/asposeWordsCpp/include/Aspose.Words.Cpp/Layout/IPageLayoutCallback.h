//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/IPageLayoutCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Layout
{
class PageLayoutCallbackArgs;
}
}
}

namespace Aspose {

namespace Words {

namespace Layout {

/// \interface IPageLayoutCallback
/// Implement this interface if you want to have your own custom method called during build and rendering of page layout model.
/// 
/// The primary use for this interface is to allow application code to abort build process.
/// 
/// It is possible to build page layout model for only a few pages at start of the document then abort process and render only what has been built already.
/// 
/// Note, however, that rendering results may not match what would be rendered for each page if process would have finished.
/// 
/// This technique may not work for every document or may fail completely.
/// 
/// @sa Aspose::Words::Layout::LayoutOptions::get_Callback
class ASPOSE_WORDS_SHARED_CLASS IPageLayoutCallback : public virtual System::Object
{
    typedef IPageLayoutCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// This is called to notify of layout build and rendering progress.
    /// 
    /// Exception when thrown by implementation aborts layout build process.
    /// 
    /// @param args An argument of the event.
    virtual void Notify(System::SharedPtr<Aspose::Words::Layout::PageLayoutCallbackArgs> args) = 0;

};

}
}
}
