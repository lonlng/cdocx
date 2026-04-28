//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontFallbackSettings.h
#pragma once

#include <system/object.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies font fallback mechanism settings.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FontFallbackSettings : public System::Object
{
    typedef FontFallbackSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Loads font fallback settings from XML file.
    /// 
    /// @param fileName Input file name.
    ASPOSE_WORDS_SHARED_API void Load(const System::String& fileName);
    /// Loads fallback settings from XML stream.
    /// 
    /// @param stream Input stream.
    ASPOSE_WORDS_SHARED_API void Load(const System::SharedPtr<System::IO::Stream>& stream);
    /// Loads predefined fallback settings which mimics the %Microsoft Word fallback and uses %Microsoft office fonts.
    ASPOSE_WORDS_SHARED_API void LoadMsOfficeFallbackSettings();
    /// Loads predefined fallback settings which uses Google Noto fonts.
    ASPOSE_WORDS_SHARED_API void LoadNotoFallbackSettings();
    /// Saves the current fallback settings to stream.
    /// 
    /// @param outputStream Output stream.
    ASPOSE_WORDS_SHARED_API void Save(const System::SharedPtr<System::IO::Stream>& outputStream);
    /// Saves the current fallback settings to file.
    /// 
    /// @param fileName Output file name.
    ASPOSE_WORDS_SHARED_API void Save(const System::String& fileName);
    /// Automatically builds the fallback settings by scanning available fonts.
    ASPOSE_WORDS_SHARED_API void BuildAutomatic();

    template <typename CharType, typename Traits>
    void Load(std::basic_istream<CharType, Traits>& stream)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        Load(streamWrapper);
    }

    template <typename CharType, typename Traits>
    void Save(std::basic_ostream<CharType, Traits>& outputStream)
    {
        auto outputStreamWrapper = System::IO::WrapSTDIOStream(outputStream);
        Save(outputStreamWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::WeakPtr<System::Object> mField2;

};

}
}
}
