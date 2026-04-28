//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontSettings.h
#pragma once

#include <system/enum_helpers.h>
#include <system/array.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Fonts
{

class FontFallbackSettings;

class FontSourceBase;
class FontSubstitutionSettings;
}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class ICollection;
template <typename> class IEnumerable;
}
}

namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies font settings for a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
/// 
/// %Aspose.Words uses font settings to resolve the fonts in the document. Fonts are resolved mostly when building document layout
/// or rendering to fixed page formats. But when loading some formats, %Aspose.Words also may require to resolve the fonts. For example, when
/// loading HTML documents %Aspose.Words may resolve the fonts to perform font fallback. So it is recommended that you set the font settings in
/// <see cref="Aspose::Words::Loading::LoadOptions">LoadOptions</see> when loading the document. Or at least before building the layout or rendering the document to the fixed-page format.
/// 
/// By default all documents uses single static font settings instance. It could be accessed by
/// <see cref="Aspose::Words::Fonts::FontSettings::get_DefaultInstance">DefaultInstance</see> property.
/// 
/// Changing font settings is safe at any time from any thread. But it is recommended that you do not change the font settings while
/// processing some documents which uses this settings. This can lead to the fact that the same font will be resolved differently
/// in different parts of the document.
class ASPOSE_WORDS_SHARED_CLASS FontSettings : public System::Object
{
    typedef FontSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Static default font settings.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontSettings> get_DefaultInstance();
    /// Settings related to font fallback mechanism.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontFallbackSettings> get_FallbackSettings() const;
    /// Settings related to font substitution mechanism.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontSubstitutionSettings> get_SubstitutionSettings() const;

    ASPOSE_WORDS_SHARED_API FontSettings();

    /// Sets the folder where %Aspose.Words looks for TrueType fonts when rendering documents or embedding fonts.
    /// This is a shortcut to <see cref="Aspose::Words::Fonts::FontSettings::SetFontsFolders(System::ArrayPtr<System::String>, bool)">SetFontsFolders()</see> for setting only one font directory.
    /// 
    /// @param fontFolder The folder that contains TrueType fonts.
    /// @param recursive True to scan the specified folders for fonts recursively.
    ASPOSE_WORDS_SHARED_API void SetFontsFolder(const System::String& fontFolder, bool recursive);
    /// Sets the folders where %Aspose.Words looks for TrueType fonts when rendering documents or embedding fonts.
    /// 
    /// By default, %Aspose.Words looks for fonts installed to the system.
    /// 
    /// Setting this property resets the cache of all previously loaded fonts.
    /// 
    /// @param fontsFolders An array of folders that contain TrueType fonts.
    /// @param recursive True to scan the specified folders for fonts recursively.
    ASPOSE_WORDS_SHARED_API void SetFontsFolders(const System::ArrayPtr<System::String>& fontsFolders, bool recursive);
    /// Sets the sources where %Aspose.Words looks for TrueType fonts when rendering documents or embedding fonts.
    /// 
    /// By default, %Aspose.Words looks for fonts installed to the system.
    /// 
    /// Setting this property resets the cache of all previously loaded fonts.
    /// 
    /// @param sources An array of sources that contain TrueType fonts.
    ASPOSE_WORDS_SHARED_API void SetFontsSources(const System::ArrayPtr<System::SharedPtr<Aspose::Words::Fonts::FontSourceBase>>& sources);
    /// Gets a copy of the array that contains the list of sources where %Aspose.Words looks for TrueType fonts.
    /// 
    /// The returned value is a copy of the data that %Aspose.Words uses. If you change the entries
    /// in the returned array, it will have no effect on document rendering. To specify new font sources
    /// use the <see cref="Aspose::Words::Fonts::FontSettings::SetFontsSources(System::ArrayPtr<System::SharedPtr<Aspose::Words::Fonts::FontSourceBase>>)">SetFontsSources()</see> method.
    /// 
    /// @return A copy of the current font sources.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<Aspose::Words::Fonts::FontSourceBase>> GetFontsSources();
    /// Resets the fonts sources to the system default.
    ASPOSE_WORDS_SHARED_API void ResetFontSources();
    /// Saves the font search cache to the stream.
    /// 
    /// @param outputStream Output stream.
    ASPOSE_WORDS_SHARED_API void SaveSearchCache(const System::SharedPtr<System::IO::Stream>& outputStream);
    /// Sets the sources where %Aspose.Words looks for TrueType fonts and additionally loads previously saved
    /// font search cache.
    /// 
    /// Loading previously saved font search cache will speed up the font cache initialization process. It is
    /// especially useful when access to font sources is complicated (e.g. when fonts are loaded via network).
    /// 
    /// When saving and loading font search cache, fonts in the provided sources are identified via cache key.
    /// For the fonts in the <see cref="Aspose::Words::Fonts::SystemFontSource">SystemFontSource</see> and <see cref="Aspose::Words::Fonts::FolderFontSource">FolderFontSource</see> cache key is the path
    /// to the font file. For <see cref="Aspose::Words::Fonts::MemoryFontSource">MemoryFontSource</see> and <see cref="Aspose::Words::Fonts::StreamFontSource">StreamFontSource</see> cache key is defined
    /// in the <see cref="Aspose::Words::Fonts::MemoryFontSource::get_CacheKey">CacheKey</see> and <see cref="Aspose::Words::Fonts::StreamFontSource::get_CacheKey">CacheKey</see> properties
    /// respectively. For the <see cref="Aspose::Words::Fonts::FileFontSource">FileFontSource</see> cache key is either <see cref="Aspose::Words::Fonts::FileFontSource::get_CacheKey">CacheKey</see>
    /// property or a file path if the <see cref="Aspose::Words::Fonts::FileFontSource::get_CacheKey">CacheKey</see> is <c>%null</c>.
    /// 
    /// It is highly recommended to provide the same font sources when loading cache as at the time the cache was saved.
    /// Any changes in the font sources (e.g. adding new fonts, moving font files or changing the cache key) may lead to the
    /// inaccurate font resolving by %Aspose.Words.
    /// 
    /// @param sources An array of sources that contain TrueType fonts.
    /// @param cacheInputStream Input stream with saved font search cache.
    ASPOSE_WORDS_SHARED_API void SetFontsSources(const System::ArrayPtr<System::SharedPtr<Aspose::Words::Fonts::FontSourceBase>>& sources, const System::SharedPtr<System::IO::Stream>& cacheInputStream);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FontSettings();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
