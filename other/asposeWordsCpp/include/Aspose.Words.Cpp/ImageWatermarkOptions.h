//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ImageWatermarkOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Contains options that can be specified when adding a watermark with image.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-watermark/">Working with Watermark</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ImageWatermarkOptions : public System::Object
{
    typedef ImageWatermarkOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the scale factor expressed as a fraction of the image. The default value is 0 - auto.
    /// 
    /// Valid values range from 0 to 65.5 inclusive.
    /// 
    /// Auto scale means that the watermark will be scaled to its max width and max height relative to
    /// the page margins.
    /// 
    /// @exception System::ArgumentOutOfRangeException Throws when argument was out of the range of valid values.
    ASPOSE_WORDS_SHARED_API double get_Scale() const;
    /// Setter for Aspose::Words::ImageWatermarkOptions::get_Scale
    ASPOSE_WORDS_SHARED_API void set_Scale(double value);
    /// Gets a boolean value which is responsible for washout effect of the watermark.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsWashout() const;
    /// Sets a boolean value which is responsible for washout effect of the watermark.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_IsWashout(bool value);

    ASPOSE_WORDS_SHARED_API ImageWatermarkOptions();

protected:

private:

    __TypeStub<8,8,8,8>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;

};

}
}
