//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/PhysicalFontInfo.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Fonts
{

class FontEmbeddingLicensingRights;

}
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies information about physical font available to %Aspose.Words font engine.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PhysicalFontInfo : public System::Object
{
    typedef PhysicalFontInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Family name of the font.
    ASPOSE_WORDS_SHARED_API System::String get_FontFamilyName() const;
    /// Full name of the font.
    ASPOSE_WORDS_SHARED_API System::String get_FullFontName() const;
    /// Version string of the font.
    ASPOSE_WORDS_SHARED_API System::String get_Version() const;
    /// Path to the font file if any.
    ASPOSE_WORDS_SHARED_API System::String get_FilePath() const;
    /// Embedding licensing rights for the font.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::FontEmbeddingLicensingRights>& get_EmbeddingLicensingRights() const;

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    System::String mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
