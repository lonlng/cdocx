//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/PageLayoutEvent.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// A code of event raised during page layout model build and rendering.
/// Page layout model is built in two steps.
/// First, "conversion step", this is when page layout pulls document content and creates object graph.
/// Second, "reflow step", this is when structures are split, merged and arranged into pages.
/// Depending of the operation which triggered build, page layout model may or may not be further rendered into fixed page format.
/// For example, computing number of pages in the document or updating fields does not require rendering, whereas export to Pdf does.
enum class ASPOSE_WORDS_SHARED_CLASS PageLayoutEvent
{
    /// Default value
    None,
    /// Corresponds to a checkpoint in code which is often visited and which is suitable to abort process.
    /// While inside <see cref="Aspose::Words::Layout::IPageLayoutCallback::Notify(System::SharedPtr<Aspose::Words::Layout::PageLayoutCallbackArgs>)">Notify()</see> throw custom exception to abort process.
    /// You can throw when handling any callback event to abort process.
    /// Note that if process is aborted the page layout model remains in undefined state. If process is aborted upon reflow of a complete page,
    /// however, it should be possible to use layout model up to the end of that page.
    WatchDog,
    /// Build of the page layout has started. Fired once.
    /// This is the first event which occurs when <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see> is called.
    BuildStarted,
    /// Build of the page layout has finished. Fired once.
    /// This is the last event which occurs when <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see> is called.
    BuildFinished,
    /// Conversion of document model to page layout has started. Fired once.
    /// This occurs when layout model starts pulling document content.
    ConversionStarted,
    /// Conversion of document model to page layout has finished. Fired once.
    /// This occurs when layout model stops pulling document content.
    ConversionFinished,
    /// Reflow of the page layout has started. Fired once.
    /// This occurs when layout model starts reflowing document content.
    ReflowStarted,
    /// Reflow of the page layout has finished. Fired once.
    /// This occurs when layout model stops reflowing document content.
    ReflowFinished,
    /// Reflow of the page has started.
    /// Note that page may reflow multiple times and that reflow may restart before it is finished.
    /// 
    /// @sa Aspose::Words::Layout::PageLayoutCallbackArgs::get_PageIndex
    PartReflowStarted,
    /// Reflow of the page has finished.
    /// Note that page may reflow multiple times and that reflow may restart before it is finished.
    /// 
    /// @sa Aspose::Words::Layout::PageLayoutCallbackArgs::get_PageIndex
    PartReflowFinished,
    /// Rendering of page has started. This is fired once per page.
    PartRenderingStarted,
    /// Rendering of page has finished. This is fired once per page.
    PartRenderingFinished
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Layout::PageLayoutEvent>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::PageLayoutEvent, const char_t*>, 12>& values();
};
