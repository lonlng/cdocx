//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/LayoutOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Layout/ContinuousSectionRestart.h>
#include <Aspose.Words.Cpp/Layout/CommentDisplayMode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Layout
{
class IPageLayoutCallback;

class RevisionOptions;
}
namespace Shaping
{
class ITextShaperFactory;
}
}
}

namespace Aspose {

namespace Words {

namespace Layout {

/// Holds the options that allow controlling the document layout process.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/converting-to-fixed-page-format/">Converting to Fixed-page Format</a> documentation article.
/// 
/// You do not create instances of this class directly. Use the <see cref="Aspose::Words::Document::get_LayoutOptions">LayoutOptions</see> property to access layout options for this document.
/// 
/// Note that after changing any of the options present in this class, <see cref="Aspose::Words::Document::UpdatePageLayout">UpdatePageLayout</see> method
/// should be called in order for the changed options to be applied to the layout.
class ASPOSE_WORDS_SHARED_CLASS LayoutOptions : public System::Object
{
    typedef LayoutOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets revision options.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Layout::RevisionOptions> get_RevisionOptions() const;
    /// Gets indication of whether hidden text in the document is rendered.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowHiddenText() const;
    /// Sets indication of whether hidden text in the document is rendered.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowHiddenText(bool value);
    /// Gets indication of whether paragraph marks are rendered.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowParagraphMarks() const;
    /// Sets indication of whether paragraph marks are rendered.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowParagraphMarks(bool value);
    /// Gets the way comments are rendered.
    /// Default value is <see cref="Aspose::Words::Layout::CommentDisplayMode::ShowInBalloons">ShowInBalloons</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::CommentDisplayMode get_CommentDisplayMode() const;
    /// Sets the way comments are rendered.
    /// Default value is <see cref="Aspose::Words::Layout::CommentDisplayMode::ShowInBalloons">ShowInBalloons</see>.
    ASPOSE_WORDS_SHARED_API void set_CommentDisplayMode(Aspose::Words::Layout::CommentDisplayMode value);
    /// Gets <see cref="Aspose::Words::Shaping::ITextShaperFactory">ITextShaperFactory</see> implementation used for Advanced Typography rendering features.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Shaping::ITextShaperFactory> get_TextShaperFactory() const;
    /// Sets <see cref="Aspose::Words::Shaping::ITextShaperFactory">ITextShaperFactory</see> implementation used for Advanced Typography rendering features.
    ASPOSE_WORDS_SHARED_API void set_TextShaperFactory(const System::SharedPtr<Aspose::Words::Shaping::ITextShaperFactory>& value);
    /// Gets <see cref="Aspose::Words::Layout::IPageLayoutCallback">IPageLayoutCallback</see> implementation used by page layout model.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Layout::IPageLayoutCallback> get_Callback() const;
    /// Sets <see cref="Aspose::Words::Layout::IPageLayoutCallback">IPageLayoutCallback</see> implementation used by page layout model.
    ASPOSE_WORDS_SHARED_API void set_Callback(const System::SharedPtr<Aspose::Words::Layout::IPageLayoutCallback>& value);
    /// Gets indication of whether the "Use printer metrics to lay out document" compatibility option is ignored.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnorePrinterMetrics() const;
    /// Sets indication of whether the "Use printer metrics to lay out document" compatibility option is ignored.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnorePrinterMetrics(bool value);
    /// Gets an indication of whether the original font metrics should be used after font substitution.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_KeepOriginalFontMetrics() const;
    /// Sets an indication of whether the original font metrics should be used after font substitution.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_KeepOriginalFontMetrics(bool value);
    /// Gets the mode of behavior for computing page numbers when a continuous section
    /// restarts the page numbering.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::ContinuousSectionRestart get_ContinuousSectionPageNumberingRestart() const;
    /// Sets the mode of behavior for computing page numbers when a continuous section
    /// restarts the page numbering.
    ASPOSE_WORDS_SHARED_API void set_ContinuousSectionPageNumberingRestart(Aspose::Words::Layout::ContinuousSectionRestart value);

    ASPOSE_WORDS_SHARED_API LayoutOptions();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    __TypeStub<1,1,1,1>::type mField9;

};

}
}
}
