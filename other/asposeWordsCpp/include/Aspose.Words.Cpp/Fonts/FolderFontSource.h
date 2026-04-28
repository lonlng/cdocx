//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FolderFontSource.h
#pragma once

#include <system/string.h>
#include <cstdint>

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

/// Represents the folder that contains TrueType font files.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FolderFontSource : public Aspose::Words::Fonts::FontSourceBase
{
    typedef FolderFontSource ThisType;
    typedef Aspose::Words::Fonts::FontSourceBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Path to the folder.
    ASPOSE_WORDS_SHARED_API System::String get_FolderPath() const;
    /// Determines whether or not to scan the subfolders.
    ASPOSE_WORDS_SHARED_API bool get_ScanSubfolders() const;
    /// Returns the type of the font source.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontSourceType get_Type() override;

    /// Ctor.
    /// 
    /// @param folderPath Path to folder.
    /// @param scanSubfolders Determines whether or not to scan subfolders.
    ASPOSE_WORDS_SHARED_API FolderFontSource(const System::String& folderPath, bool scanSubfolders);
    /// Ctor.
    /// 
    /// @param folderPath Path to folder.
    /// @param scanSubfolders Determines whether or not to scan subfolders.
    /// @param priority Font source priority. See the <see cref="Aspose::Words::Fonts::FontSourceBase::get_Priority">Priority</see> property description for more information.
    ASPOSE_WORDS_SHARED_API FolderFontSource(const System::String& folderPath, bool scanSubfolders, int32_t priority);

private:

    System::String mField0;
    __TypeStub<1,1,1,1>::type mField1;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Fonts::IFontData>>> GetFontDataInternal() override;

};

}
}
}
