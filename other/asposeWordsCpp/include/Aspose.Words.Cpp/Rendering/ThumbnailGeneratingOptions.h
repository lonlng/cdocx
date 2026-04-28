//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Rendering/ThumbnailGeneratingOptions.h
#pragma once

#include <system/object.h>
#include <drawing/size.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Rendering {

/// Can be used to specify additional options when generating thumbnail for a document.
class ASPOSE_WORDS_SHARED_CLASS ThumbnailGeneratingOptions : public System::Object
{
    typedef ThumbnailGeneratingOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether to generate thumbnail from first page of the document or first image.
    ASPOSE_WORDS_SHARED_API bool get_GenerateFromFirstPage() const;
    /// Specifies whether to generate thumbnail from first page of the document or first image.
    ASPOSE_WORDS_SHARED_API void set_GenerateFromFirstPage(bool value);
    /// Size of generated thumbnail in pixels.
    /// Default is 600x900.
    ASPOSE_WORDS_SHARED_API System::Drawing::Size get_ThumbnailSize() const;
    /// Size of generated thumbnail in pixels.
    /// Default is 600x900.
    ASPOSE_WORDS_SHARED_API void set_ThumbnailSize(System::Drawing::Size value);

    ASPOSE_WORDS_SHARED_API ThumbnailGeneratingOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::Drawing::Size mField1;

};

}
}
}
