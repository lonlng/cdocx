//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MetafileRenderingOptions.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Saving/MetafileRenderingMode.h>
#include <Aspose.Words.Cpp/Saving/EmfPlusDualRenderingMode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify additional metafile rendering options.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/handling-windows-metafiles/">Handling Windows Metafiles</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS MetafileRenderingOptions : public System::Object
{
    typedef MetafileRenderingOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets a value determining how metafile images should be rendered.
    /// 
    /// The default value depends on the save format. For images it is <see cref="Aspose::Words::Saving::MetafileRenderingMode::Bitmap">Bitmap</see>.
    /// For other formats it is <see cref="Aspose::Words::Saving::MetafileRenderingMode::VectorWithFallback">VectorWithFallback</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::MetafileRenderingMode get_RenderingMode() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_RenderingMode
    ASPOSE_WORDS_SHARED_API void set_RenderingMode(Aspose::Words::Saving::MetafileRenderingMode value);
    /// Gets or sets a value determining how EMF+ Dual metafiles should be rendered.
    /// 
    /// EMF+ Dual metafiles contains both EMF+ and EMF parts. MS Word and GDI+ always renders EMF+ part.
    /// %Aspose.Words currently doesn't fully supports all EMF+ records and in some cases rendering result of
    /// EMF part looks better then rendering result of EMF+ part.
    /// 
    /// This option is used only when metafile is rendered as vector graphics. When metafile is rendered
    /// to bitmap, EMF+ part is always used.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::EmfPlusDualRenderingMode::EmfPlusWithFallback">EmfPlusWithFallback</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::EmfPlusDualRenderingMode get_EmfPlusDualRenderingMode() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_EmfPlusDualRenderingMode
    ASPOSE_WORDS_SHARED_API void set_EmfPlusDualRenderingMode(Aspose::Words::Saving::EmfPlusDualRenderingMode value);
    /// Gets or sets a value determining how WMF metafiles with embedded EMF metafiles should be rendered.
    /// 
    /// WMF metafiles could contain embedded EMF data. MS Word in most cases uses embedded EMF data.
    /// GDI+ always uses WMF data.
    /// 
    /// When this value is set to <c>%true</c>, %Aspose.Words uses embedded EMF data when rendering.
    /// 
    /// When this value is set to <c>%false</c>, %Aspose.Words uses WMF data when rendering.
    /// 
    /// This option is used only when metafile is rendered as vector graphics. When metafile is rendered
    /// to bitmap, WMF data is always used.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseEmfEmbeddedToWmf() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_UseEmfEmbeddedToWmf
    ASPOSE_WORDS_SHARED_API void set_UseEmfEmbeddedToWmf(bool value);
    /// Gets or sets a value determining whether or not the raster operations should be emulated.
    /// 
    /// Specific raster operations could be used in metafiles. They can not be rendered directly to vector graphics.
    /// Emulating raster operations requires partial rasterization of the resulting vector graphics which may affect the
    /// metafile rendering performance.
    /// 
    /// When this value is set to <c>%true</c>, %Aspose.Words emulates the raster operations. The resulting output maybe
    /// partially rasterized and performance might be slower.
    /// 
    /// When this value is set to <c>%false</c>, %Aspose.Words does not emulate the raster operations. When Aspose.Words
    /// encounters a raster operation in a metafile it fallbacks to rendering the metafile into a bitmap by using the
    /// operating system.
    /// 
    /// This option is used only when metafile is rendered as vector graphics.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_EmulateRasterOperations() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_EmulateRasterOperations
    ASPOSE_WORDS_SHARED_API void set_EmulateRasterOperations(bool value);
    /// Gets or sets a value determining whether or not to use the GDI+ for raster operations emulation.
    /// 
    /// Windows GDI+ library could be used to emulate raster operations. It provides support for all raster operation
    /// comparing to %Aspose.Words own emulation but performance may be slower in some cases.
    /// 
    /// When this value is set to <c>%true</c>, %Aspose.Words uses GDI+ for raster operations emulation.
    /// 
    /// When this value is set to <c>%false</c>, %Aspose.Words uses its own implementation of raster operations emulation.
    /// 
    /// This option is used only when metafile is rendered as vector graphics.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseGdiRasterOperationsEmulation() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_UseGdiRasterOperationsEmulation
    ASPOSE_WORDS_SHARED_API void set_UseGdiRasterOperationsEmulation(bool value);
    /// Gets or sets a value determining whether metafile rendering emulates the display of the metafile according to the size on page
    /// or the display of the metafile in its default size.
    /// 
    /// When metafiles are displayed in MS Word, some graphics may be scaled according to the actual metafile size in pixels.
    /// I.e. even zooming may affect the metafile display.
    /// 
    /// When this value is set to <c>%true</c>, %Aspose.Words emulates rendering according to the metafile size on page.
    /// The size in pixels is calculated from the metafile size on the page and the specified <see cref="Aspose::Words::Saving::MetafileRenderingOptions::get_EmulateRenderingToSizeOnPageResolution">EmulateRenderingToSizeOnPageResolution</see>.
    /// 
    /// When this value is set to <c>%false</c>, %Aspose.Words emulates metafile rendering to its default size in pixels.
    /// 
    /// This option is used only when metafile is rendered as vector graphics.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_EmulateRenderingToSizeOnPage() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_EmulateRenderingToSizeOnPage
    ASPOSE_WORDS_SHARED_API void set_EmulateRenderingToSizeOnPage(bool value);
    /// Gets or sets the resolution in pixels per inch for the emulation of metafile rendering to the size on page.
    /// 
    /// This option is used only when <see cref="Aspose::Words::Saving::MetafileRenderingOptions::get_EmulateRenderingToSizeOnPage">EmulateRenderingToSizeOnPage</see> is set to <c>%true</c>.
    /// 
    /// The default value is 96. This is a default display resolution. I.e. metafile rendering will emulate the display of
    /// the metafile in MS Word with a 100\% zoom factor.
    ASPOSE_WORDS_SHARED_API int32_t get_EmulateRenderingToSizeOnPageResolution() const;
    /// Setter for Aspose::Words::Saving::MetafileRenderingOptions::get_EmulateRenderingToSizeOnPageResolution
    ASPOSE_WORDS_SHARED_API void set_EmulateRenderingToSizeOnPageResolution(int32_t value);

    ASPOSE_WORDS_SHARED_API MetafileRenderingOptions();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;

};

}
}
}
