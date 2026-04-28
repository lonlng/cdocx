//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DownsampleOptions.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify downsample options.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS DownsampleOptions : public System::Object
{
    typedef DownsampleOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether images should be downsampled.
    ASPOSE_WORDS_SHARED_API bool get_DownsampleImages() const;
    /// Specifies whether images should be downsampled.
    ASPOSE_WORDS_SHARED_API void set_DownsampleImages(bool value);
    /// Specifies the resolution in pixels per inch which the images should be downsampled to.
    ASPOSE_WORDS_SHARED_API int32_t get_Resolution() const;
    /// Specifies the resolution in pixels per inch which the images should be downsampled to.
    ASPOSE_WORDS_SHARED_API void set_Resolution(int32_t value);
    /// Specifies the threshold resolution in pixels per inch.
    /// If resolution of an image in the document is less than threshold value,
    /// the downsampling algorithm will not be applied.
    /// A value of 0 means the threshold check is not used and all images that can be reduced in size are downsampled.
    ASPOSE_WORDS_SHARED_API int32_t get_ResolutionThreshold() const;
    /// Setter for Aspose::Words::Saving::DownsampleOptions::get_ResolutionThreshold
    ASPOSE_WORDS_SHARED_API void set_ResolutionThreshold(int32_t value);

    ASPOSE_WORDS_SHARED_API DownsampleOptions();

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;

};

}
}
}
