//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/FrameFormat.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/HeightRule.h>
#include <Aspose.Words.Cpp/Drawing/VerticalAlignment.h>
#include <Aspose.Words.Cpp/Drawing/RelativeVerticalPosition.h>
#include <Aspose.Words.Cpp/Drawing/RelativeHorizontalPosition.h>
#include <Aspose.Words.Cpp/Drawing/HorizontalAlignment.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Represents frame related formatting for a paragraph.
/// 
/// This object is always created. If a paragraph is a frame, then all properties will contain respective values, otherwise
/// all properties are set to their defaults.
/// 
/// Use <see cref="Aspose::Words::FrameFormat::get_IsFrame">IsFrame</see> to check whether paragraph is a frame.
class ASPOSE_WORDS_SHARED_CLASS FrameFormat : public System::Object
{
    typedef FrameFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the rule for determining the height of the specified frame.
    ASPOSE_WORDS_SHARED_API Aspose::Words::HeightRule get_HeightRule();
    /// Gets the height of the specified frame.
    ASPOSE_WORDS_SHARED_API double get_Height();
    /// Gets horizontal distance between a frame and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API double get_HorizontalDistanceFromText();
    /// Gets horizontal distance between the edge of the frame and the item specified by the <see cref="Aspose::Words::FrameFormat::get_RelativeHorizontalPosition">RelativeHorizontalPosition</see> property.
    ASPOSE_WORDS_SHARED_API double get_HorizontalPosition();
    /// Gets the relative horizontal position of a frame.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::RelativeHorizontalPosition get_RelativeHorizontalPosition();
    /// Gets the relative vertical position of a frame.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::RelativeVerticalPosition get_RelativeVerticalPosition();
    /// Specifies vertical distance (in points) between a frame and the surrounding text.
    ASPOSE_WORDS_SHARED_API double get_VerticalDistanceFromText();
    /// Gets vertical distance between the edge of the frame and the item specified by the <see cref="Aspose::Words::FrameFormat::get_RelativeVerticalPosition">RelativeVerticalPosition</see> property.
    ASPOSE_WORDS_SHARED_API double get_VerticalPosition();
    /// Gets the width of the specified frame, in points.
    ASPOSE_WORDS_SHARED_API double get_Width();
    /// Gets vertical alignment of the specified frame.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::VerticalAlignment get_VerticalAlignment();
    /// Gets horizontal alignment of the specified frame.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::HorizontalAlignment get_HorizontalAlignment();
    /// Returns <c>%true</c> if the paragraph is a frame.
    ASPOSE_WORDS_SHARED_API bool get_IsFrame();

protected:

private:

    System::WeakPtr<System::Object> mField0;

};

}
}
