//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Rendering/PageInfo.h
#pragma once

#include <system/array.h>
#include <mutex>
#include <memory>
#include <drawing/size_f.h>
#include <cstdint>

#include <Aspose.Words.Cpp/PaperSize.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Drawing
{
class Size;
}
}

namespace Aspose {

namespace Words {

namespace Rendering {

/// Represents information about a particular document page.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/rendering/">Rendering</a> documentation article.
/// 
/// The page width and height returned by this object represent the "final" size of the page e.g. they are
/// already rotated to the correct orientation.
/// 
/// @sa Aspose::Words::Document::GetPageInfo(int32_t)
class ASPOSE_WORDS_SHARED_CLASS PageInfo : public System::Object
{
    typedef PageInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the paper size as enumeration.
    ASPOSE_WORDS_SHARED_API Aspose::Words::PaperSize get_PaperSize();
    /// Gets the width of the page in points.
    ASPOSE_WORDS_SHARED_API float get_WidthInPoints();
    /// Gets the height of the page in points.
    ASPOSE_WORDS_SHARED_API float get_HeightInPoints();
    /// Gets the page size in points.
    ASPOSE_WORDS_SHARED_API System::Drawing::SizeF get_SizeInPoints() const;
    /// Gets the paper tray (bin) for this page as specified in the document.
    /// The value is implementation (printer) specific.
    ASPOSE_WORDS_SHARED_API int32_t get_PaperTray() const;
    /// Returns <c>%true</c> if the page orientation specified in the document for this page is landscape.
    ASPOSE_WORDS_SHARED_API bool get_Landscape() const;
    /// Returns <c>%true</c> if the page contains colored content.
    ASPOSE_WORDS_SHARED_API bool get_Colored();

    /// Calculates the page size in pixels for a specified zoom factor and resolution.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param dpi The resolution (horizontal and vertical) to convert from points to pixels (dots per inch).
    /// 
    /// @return The size of the page in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Size GetSizeInPixels(float scale, float dpi);
    /// Calculates the page size in pixels for a specified zoom factor and resolution.
    /// 
    /// @param scale The zoom factor (1.0 is 100\%).
    /// @param horizontalDpi The horizontal resolution to convert from points to pixels (dots per inch).
    /// @param verticalDpi The vertical resolution to convert from points to pixels (dots per inch).
    /// 
    /// @return The size of the page in pixels.
    ASPOSE_WORDS_SHARED_API System::Drawing::Size GetSizeInPixels(float scale, float horizontalDpi, float verticalDpi);

protected:

private:

    System::Drawing::SizeF mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;

};

}
}
}
