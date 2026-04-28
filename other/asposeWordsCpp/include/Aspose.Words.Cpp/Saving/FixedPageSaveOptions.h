//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/Saving/NumeralFormat.h>
#include <Aspose.Words.Cpp/Saving/ColorMode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Saving
{
class IPageSavingCallback;
class MetafileRenderingOptions;

class PageSet;
}
}
}
namespace System
{
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Contains common options that can be specified when saving a document into fixed page formats (PDF, XPS,
/// images etc).
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FixedPageSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef FixedPageSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the pages to render.
    /// Default is all the pages in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PageSet> get_PageSet() const;
    /// Sets the pages to render.
    /// Default is all the pages in the document.
    ASPOSE_WORDS_SHARED_API void set_PageSet(const System::SharedPtr<Aspose::Words::Saving::PageSet>& value);
    /// Allows to control how separate pages are saved when a document is exported to fixed page format.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IPageSavingCallback> get_PageSavingCallback() const;
    /// Allows to control how separate pages are saved when a document is exported to fixed page format.
    ASPOSE_WORDS_SHARED_API void set_PageSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IPageSavingCallback>& value);
    /// Gets <see cref="Aspose::Words::Saving::NumeralFormat">NumeralFormat</see> used for rendering of numerals.
    /// European numerals are used by default.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::NumeralFormat get_NumeralFormat() const;
    /// Sets <see cref="Aspose::Words::Saving::NumeralFormat">NumeralFormat</see> used for rendering of numerals.
    /// European numerals are used by default.
    ASPOSE_WORDS_SHARED_API void set_NumeralFormat(Aspose::Words::Saving::NumeralFormat value);
    /// Allows to specify metafile rendering options.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MetafileRenderingOptions> get_MetafileRenderingOptions() const;
    /// Allows to specify metafile rendering options.
    ASPOSE_WORDS_SHARED_API void set_MetafileRenderingOptions(const System::SharedPtr<Aspose::Words::Saving::MetafileRenderingOptions>& value);
    /// Gets or sets a value determining the quality of the JPEG images inside Html document.
    /// 
    /// Has effect only when a document contains JPEG images.
    /// 
    /// Use this property to get or set the quality of the images inside a document when saving in fixed page format.
    /// The value may vary from 0 to 100 where 0 means worst quality but maximum compression and 100
    /// means best quality but minimum compression.
    /// 
    /// The default value is 95.
    ASPOSE_WORDS_SHARED_API int32_t get_JpegQuality() const;
    /// Setter for Aspose::Words::Saving::FixedPageSaveOptions::get_JpegQuality
    ASPOSE_WORDS_SHARED_API void set_JpegQuality(int32_t value);
    /// Gets a value determining how colors are rendered.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ColorMode get_ColorMode() const;
    /// Sets a value determining how colors are rendered.
    ASPOSE_WORDS_SHARED_API void set_ColorMode(Aspose::Words::Saving::ColorMode value);
    /// Flag indicates whether it is required to optimize output.
    /// If this flag is set redundant nested canvases and empty canvases are removed,
    /// also neighbor glyphs with the same formatting are concatenated.
    /// Note: The accuracy of the content display may be affected if this property is set to <c>%true</c>.
    /// Default is <c>%false</c>.
    virtual ASPOSE_WORDS_SHARED_API bool get_OptimizeOutput();
    /// Setter for Aspose::Words::Saving::FixedPageSaveOptions::get_OptimizeOutput
    virtual ASPOSE_WORDS_SHARED_API void set_OptimizeOutput(bool value);

    /// Determines whether the specified object is equal in value to the current object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsFlowFormat() override;

    virtual ASPOSE_WORDS_SHARED_API bool get_CreateOutlinesForHeadingsInTables();
    virtual ASPOSE_WORDS_SHARED_API bool get_IsShapingSupported();

    ASPOSE_WORDS_SHARED_API FixedPageSaveOptions();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<4,4,4,4>::type mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    System::SharedPtr<System::Object> mField7;

};

}
}
}
