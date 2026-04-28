//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/SystemFontSource.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/Fonts/FontSourceType.h>
#include <Aspose.Words.Cpp/Fonts/FontSourceBase.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Fonts
{
class IFontData;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerable;
}
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Represents all TrueType fonts installed to the system.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SystemFontSource : public Aspose::Words::Fonts::FontSourceBase
{
    typedef SystemFontSource ThisType;
    typedef Aspose::Words::Fonts::FontSourceBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the type of the font source.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontSourceType get_Type() override;

    /// Ctor.
    ASPOSE_WORDS_SHARED_API SystemFontSource();
    /// Ctor.
    /// 
    /// @param priority Font source priority. See the <see cref="Aspose::Words::Fonts::FontSourceBase::get_Priority">Priority</see> property description for more information.
    ASPOSE_WORDS_SHARED_API SystemFontSource(int32_t priority);

    /// Returns system font folders or empty array if folders are not accessible.
    static ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> GetSystemFontFolders();

private:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Fonts::IFontData>>> GetFontDataInternal() override;

};

}
}
}
