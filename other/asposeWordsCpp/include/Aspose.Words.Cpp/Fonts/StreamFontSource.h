//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/StreamFontSource.h
#pragma once

#include <system/array.h>
#include <Aspose.Words.Cpp/Fonts/IFontData.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fonts/FontSourceType.h>
#include <Aspose.Words.Cpp/Fonts/FontSourceBase.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Collections
{
namespace Generic
{
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

/// Base class for user-defined stream font source.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
/// 
/// In order to use the stream font source you should create a derived class from the <see cref="Aspose::Words::Fonts::StreamFontSource">StreamFontSource</see>
/// and provide implementation of the <see cref="Aspose::Words::Fonts::StreamFontSource::OpenFontDataStream">OpenFontDataStream</see> method.
/// 
/// <see cref="Aspose::Words::Fonts::StreamFontSource::OpenFontDataStream">OpenFontDataStream</see> method could be called several times. For the first time it will be called
/// when %Aspose.Words scans the provided font sources to get the list of available fonts. Later it may be called if the
/// font is used in the document to parse the font data and to embed the font data to some output formats.
/// 
/// <see cref="Aspose::Words::Fonts::StreamFontSource">StreamFontSource</see> may be useful because it allows to load the font data only when it is required
/// and not to store it in the memory for the <see cref="Aspose::Words::Fonts::FontSettings">FontSettings</see> lifetime.
class ASPOSE_WORDS_SHARED_CLASS StreamFontSource : public Aspose::Words::Fonts::FontSourceBase, public Aspose::Fonts::IFontData
{
    typedef StreamFontSource ThisType;
    typedef Aspose::Words::Fonts::FontSourceBase BaseType;
    typedef Aspose::Fonts::IFontData BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The key of this source in the cache.
    ASPOSE_WORDS_SHARED_API System::String get_CacheKey() const;
    /// Returns the type of the font source.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fonts::FontSourceType get_Type() override;
    ASPOSE_WORDS_SHARED_API bool get_IsEmbedded() override;

    /// This method should open the stream with font data on demand.
    /// 
    /// @return Font data stream.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> OpenFontDataStream() = 0;

protected:

    ASPOSE_WORDS_SHARED_API StreamFontSource();

    virtual ASPOSE_WORDS_SHARED_API ~StreamFontSource();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> OpenStream() override;
    ASPOSE_WORDS_SHARED_API int32_t GetSize() override;
    ASPOSE_WORDS_SHARED_API System::String GetFilePath() override;
    ASPOSE_WORDS_SHARED_API System::String GetCacheKeyInternal() override;
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> GetFontBytes() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Fonts::IFontData>>> GetFontDataInternal() override;

};

}
}
}
