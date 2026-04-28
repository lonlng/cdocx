//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/SvgSaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/SvgTextOutputMode.h>
#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Saving
{
class IResourceSavingCallback;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Svg">Svg</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SvgSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef SvgSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Svg">Svg</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Svg">Svg</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Controls whether a border is added to the outline of the page.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowPageBorder() const;
    /// Controls whether a border is added to the outline of the page.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowPageBorder(bool value);
    /// Gets or sets a value determining how text should be rendered in SVG.
    /// 
    /// Use this property to get or set the mode of how text inside a document should be rendered
    /// when saving in SVG format.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::SvgTextOutputMode::UseTargetMachineFonts">UseTargetMachineFonts</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::SvgTextOutputMode get_TextOutputMode() const;
    /// Setter for Aspose::Words::Saving::SvgSaveOptions::get_TextOutputMode
    ASPOSE_WORDS_SHARED_API void set_TextOutputMode(Aspose::Words::Saving::SvgTextOutputMode value);
    /// Specifies the physical folder where resources (images) are saved when exporting a document to Svg format.
    /// Default is <c>%null</c>.
    /// 
    /// Has effect only if <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ExportEmbeddedImages">ExportEmbeddedImages</see> property is <c>%false</c>.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in SVG format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the
    /// images in the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder where to save the images,
    /// but still needs to save the images somewhere. In this case, you need to specify an accessible folder
    /// in the <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder">ResourcesFolder</see> property
    /// 
    /// @sa Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolderAlias
    ASPOSE_WORDS_SHARED_API System::String get_ResourcesFolder() const;
    /// Setter for Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder
    ASPOSE_WORDS_SHARED_API void set_ResourcesFolder(const System::String& value);
    /// Specifies the name of the folder used to construct image URIs written into an SVG document.
    /// Default is <c>%null</c>.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in SVG format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// @sa Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder
    ASPOSE_WORDS_SHARED_API System::String get_ResourcesFolderAlias() const;
    /// Setter for Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ResourcesFolderAlias(const System::String& value);
    /// Specifies whether images should be embedded into the SVG document as base64.
    /// Be aware that activating this option can lead to a significant increase in the size of the output SVG file.
    ASPOSE_WORDS_SHARED_API bool get_ExportEmbeddedImages() const;
    /// Specifies whether images should be embedded into the SVG document as base64.
    /// Be aware that activating this option can lead to a significant increase in the size of the output SVG file.
    ASPOSE_WORDS_SHARED_API void set_ExportEmbeddedImages(bool value);
    /// Gets or sets a value in pixels per inch that limits resolution of exported raster images. Default value is zero.
    /// 
    /// If the value of this property is non-zero, it limits resolution of exported raster images.
    /// That is, higher-resolution images are resampled down to the limit and lower-resolution images are exported as is.
    /// 
    /// If the value of this property is zero, all raster images are exported without resampling.
    ASPOSE_WORDS_SHARED_API int32_t get_MaxImageResolution() const;
    /// Setter for Aspose::Words::Saving::SvgSaveOptions::get_MaxImageResolution
    ASPOSE_WORDS_SHARED_API void set_MaxImageResolution(int32_t value);
    /// Specifies if the output SVG should fill the available viewport area (browser window or container).
    /// When set to <c>%true</c> width and height of output SVG are set to 100\%.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_FitToViewPort() const;
    /// Specifies if the output SVG should fill the available viewport area (browser window or container).
    /// When set to <c>%true</c> width and height of output SVG are set to 100\%.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_FitToViewPort(bool value);
    /// Specifies a prefix that is prepended to all generated element IDs in the output document.
    /// Default value is null and no prefix is prepended.
    /// 
    /// @exception System::ArgumentException The value does not meet the requirements specified above.
    ASPOSE_WORDS_SHARED_API System::String get_IdPrefix() const;
    /// Setter for Aspose::Words::Saving::SvgSaveOptions::get_IdPrefix
    ASPOSE_WORDS_SHARED_API void set_IdPrefix(const System::String& value);
    /// Allows to control how resources (images) are saved when a document is exported to SVG format.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback> get_ResourceSavingCallback() const;
    /// Allows to control how resources (images) are saved when a document is exported to SVG format.
    ASPOSE_WORDS_SHARED_API void set_ResourceSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback>& value);
    /// Specifies whether JavaScript will be removed from links.
    /// Default is <c>%false</c>.
    /// If this option is enabled, all links containing JavaScript will be replaced with "javascript:void(0)".
    ASPOSE_WORDS_SHARED_API bool get_RemoveJavaScriptFromLinks() const;
    /// Specifies whether JavaScript will be removed from links.
    /// Default is <c>%false</c>.
    /// If this option is enabled, all links containing JavaScript will be replaced with "javascript:void(0)".
    ASPOSE_WORDS_SHARED_API void set_RemoveJavaScriptFromLinks(bool value);

    ASPOSE_WORDS_SHARED_API SvgSaveOptions();

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsShapingSupported() override;

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    System::String mField4;
    System::String mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<4,4,4,4>::type mField8;
    System::String mField9;

};

}
}
}
