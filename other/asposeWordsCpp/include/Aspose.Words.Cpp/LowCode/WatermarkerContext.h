//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/WatermarkerContext.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class ImageWatermarkOptions;

class TextWatermarkOptions;
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Document watermarker context.
class ASPOSE_WORDS_SHARED_CLASS WatermarkerContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef WatermarkerContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Image bytes to be used as a watermark.
    ASPOSE_WORDS_SHARED_API const System::ArrayPtr<uint8_t>& get_ImageWatermark() const;
    /// Image bytes to be used as a watermark.
    ASPOSE_WORDS_SHARED_API void set_ImageWatermark(const System::ArrayPtr<uint8_t>& value);
    /// Text to be used as a watermark.
    ASPOSE_WORDS_SHARED_API System::String get_TextWatermark() const;
    /// Text to be used as a watermark.
    ASPOSE_WORDS_SHARED_API void set_TextWatermark(const System::String& value);
    /// Options for the text watermark.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::ImageWatermarkOptions>& get_ImageWatermarkOptions() const;
    /// Options for the image watermark.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::TextWatermarkOptions>& get_TextWatermarkOptions() const;

    ASPOSE_WORDS_SHARED_API WatermarkerContext();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;

};

}
}
}
