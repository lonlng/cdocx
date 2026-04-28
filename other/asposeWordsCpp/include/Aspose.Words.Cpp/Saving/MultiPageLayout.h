//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MultiPageLayout.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Drawing
{
class Color;
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Defines a layout for rendering multiple pages into a single output.
class ASPOSE_WORDS_SHARED_CLASS MultiPageLayout final : public System::Object
{
    typedef MultiPageLayout ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the background color of the output.
    /// The default is <see cref="System::Drawing::Color::Empty">Empty</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BackColor();
    /// Sets the background color of the output.
    /// The default is <see cref="System::Drawing::Color::Empty">Empty</see>.
    ASPOSE_WORDS_SHARED_API void set_BackColor(System::Drawing::Color value);
    /// Gets the color of the pages border.
    /// The default is <see cref="System::Drawing::Color::Empty">Empty</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_BorderColor();
    /// Sets the color of the pages border.
    /// The default is <see cref="System::Drawing::Color::Empty">Empty</see>.
    ASPOSE_WORDS_SHARED_API void set_BorderColor(System::Drawing::Color value);
    /// Gets the width of the pages border.
    /// The default is 0.
    ASPOSE_WORDS_SHARED_API float get_BorderWidth() const;
    /// Sets the width of the pages border.
    /// The default is 0.
    ASPOSE_WORDS_SHARED_API void set_BorderWidth(float value);

    /// Creates a layout where all specified pages are rendered vertically one below the other in a single output.
    /// 
    /// @param verticalGap The vertical gap between pages in points.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MultiPageLayout> Vertical(float verticalGap);
    /// Creates a layout in which all specified pages are rendered horizontally side by side,
    /// left to right, in a single output.
    /// 
    /// @param horizontalGap The horizontal gap between pages in points.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MultiPageLayout> Horizontal(float horizontalGap);
    /// Creates a layout in which pages are rendered left-to-right, top-to-bottom, in a grid with the
    /// specified number of columns.
    /// 
    /// @param columns The number of columns in the layout. Must be greater than zero.
    /// @param horizontalGap The horizontal gap between columns in points.
    /// @param verticalGap The vertical gap between rows in points.
    /// 
    /// @exception System::ArgumentOutOfRangeException Thrown if @a columns is less than or equal to zero.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MultiPageLayout> Grid(int32_t columns, float horizontalGap, float verticalGap);
    /// Creates a layout where each page is rendered as a separate frame in a multi-frame TIFF image.
    /// Applicable only to TIFF image formats.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MultiPageLayout> TiffFrames();
    /// Creates a layout that renders only the first of specified pages.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::MultiPageLayout> SinglePage();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;

};

}
}
}
