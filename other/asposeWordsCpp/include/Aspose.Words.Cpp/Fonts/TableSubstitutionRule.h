//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/TableSubstitutionRule.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/Fonts/FontSubstitutionRule.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Fonts
{
class ExternalFontCache;

namespace TrueType
{
class TTFont;
}
}
namespace Words
{
namespace Fonts
{
class FontInfo;

}
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
namespace Drawing
{
enum class FontStyle;
}
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Table font substitution rule.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS TableSubstitutionRule : public Aspose::Words::Fonts::FontSubstitutionRule
{
    typedef TableSubstitutionRule ThisType;
    typedef Aspose::Words::Fonts::FontSubstitutionRule BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Loads table substitution settings from XML file.
    /// 
    /// @param fileName Input file name.
    ASPOSE_WORDS_SHARED_API void Load(const System::String& fileName);
    /// Loads table substitution settings from XML stream.
    /// 
    /// @param stream Input stream.
    ASPOSE_WORDS_SHARED_API void Load(const System::SharedPtr<System::IO::Stream>& stream);
    /// Loads predefined table substitution settings for Windows platform.
    ASPOSE_WORDS_SHARED_API void LoadWindowsSettings();
    /// Loads predefined table substitution settings for Linux platform.
    ASPOSE_WORDS_SHARED_API void LoadLinuxSettings();
    /// Loads predefined table substitution settings for Android platform.
    ASPOSE_WORDS_SHARED_API void LoadAndroidSettings();
    /// Saves the current table substitution settings to file.
    /// 
    /// @param fileName Output file name.
    ASPOSE_WORDS_SHARED_API void Save(const System::String& fileName);
    /// Saves the current table substitution settings to stream.
    /// 
    /// @param outputStream Output stream.
    ASPOSE_WORDS_SHARED_API void Save(const System::SharedPtr<System::IO::Stream>& outputStream);
    /// Returns array containing substitute font names for the specified original font name.
    /// 
    /// @param originalFontName Original font name.
    /// 
    /// @return List of alternative font names.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerable<System::String>> GetSubstitutes(const System::String& originalFontName);
    /// Override substitute font names for given original font name.
    /// 
    /// @param originalFontName Original font name.
    /// @param substituteFontNames List of alternative font names.
    ASPOSE_WORDS_SHARED_API void SetSubstitutes(const System::String& originalFontName, const System::ArrayPtr<System::String>& substituteFontNames);
    /// Adds substitute font names for given original font name.
    /// 
    /// @param originalFontName Original font name.
    /// @param substituteFontNames List of alternative font names.
    ASPOSE_WORDS_SHARED_API void AddSubstitutes(const System::String& originalFontName, const System::ArrayPtr<System::String>& substituteFontNames);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Fonts::TrueType::TTFont> PerformSubstitutionCore(System::String , System::Drawing::FontStyle , System::SharedPtr<Aspose::Words::Fonts::FontInfo> , System::SharedPtr<Aspose::Fonts::ExternalFontCache> ) override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
