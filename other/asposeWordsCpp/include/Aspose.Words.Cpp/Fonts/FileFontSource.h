//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FileFontSource.h
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

/// Represents the single TrueType font file stored in the file system.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FileFontSource : public Aspose::Words::Fonts::FontSourceBase
{
    typedef FileFontSource ThisType;
    typedef Aspose::Words::Fonts::FontSourceBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Path to the font file.
    ASPOSE_WORDS_SHARED_API System::String get_FilePath() const;
    /// The key of this source in the cache.
    /// 
    /// This key is used to identify cache item when saving/loading font search cache with
    /// <see cref="Aspose::Words::Fonts::FontSettings::SaveSearchCache(System::SharedPtr<System::IO::Stream>)">SaveSearchCache()</see> and
    /// <see cref="Aspose::Words::Fonts::FontSettings::SetFontsSources(System::ArrayPtr<System::SharedPtr<Aspose::Words::Fonts::FontSourceBase>>, System::SharedPtr<System::IO::Stream>)">SetFontsSources()</see> methods.
    /// 
    /// If key is not specified then <see cref="Aspose::Words::Fonts::FileFontSource::get_FilePath">FilePath</see> will be used as a key instead.
    ASPOSE_WORDS_SHARED_API System::String get_CacheKey() const;
    /// Returns the type of the font source.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontSourceType get_Type() override;

    /// Ctor.
    /// 
    /// @param filePath Path to font file.
    ASPOSE_WORDS_SHARED_API FileFontSource(const System::String& filePath);
    /// Ctor.
    /// 
    /// @param filePath Path to font file.
    /// @param priority Font source priority. See the <see cref="Aspose::Words::Fonts::FontSourceBase::get_Priority">Priority</see> property description for more information.
    ASPOSE_WORDS_SHARED_API FileFontSource(const System::String& filePath, int32_t priority);
    /// Ctor.
    /// 
    /// @param filePath Path to font file.
    /// @param priority Font source priority. See the <see cref="Aspose::Words::Fonts::FontSourceBase::get_Priority">Priority</see> property description for more information.
    /// @param cacheKey The key of this source in the cache. See <see cref="Aspose::Words::Fonts::FileFontSource::get_CacheKey">CacheKey</see> property description for more information.
    ASPOSE_WORDS_SHARED_API FileFontSource(const System::String& filePath, int32_t priority, const System::String& cacheKey);

private:

    System::String mField0;
    System::String mField1;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Fonts::IFontData>>> GetFontDataInternal() override;

};

}
}
}
