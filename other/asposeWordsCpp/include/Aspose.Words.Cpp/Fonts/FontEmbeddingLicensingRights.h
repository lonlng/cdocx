//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontEmbeddingLicensingRights.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Fonts/FontEmbeddingUsagePermissions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Represents embedding licensing rights for the font.
class ASPOSE_WORDS_SHARED_CLASS FontEmbeddingLicensingRights : public System::Object
{
    typedef FontEmbeddingLicensingRights ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Usage permissions.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontEmbeddingUsagePermissions get_EmbeddingUsagePermissions() const;
    /// Indicates the "No subsetting" restriction.
    ASPOSE_WORDS_SHARED_API bool get_NoSubsetting() const;
    /// Indicates the "Bitmap embedding only" restriction.
    ASPOSE_WORDS_SHARED_API bool get_BitmapEmbeddingOnly() const;

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;

};

}
}
}
