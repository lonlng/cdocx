//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Hyphenation.h
#pragma once

#include <system/string.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
class IHyphenationCallback;
class IWarningCallback;

}
}
namespace System
{
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

/// Provides methods for working with hyphenation dictionaries. These dictionaries prescribe where words of a specific language can be hyphenated.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-hyphenation/">Working with Hyphenation</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Hyphenation
{
    typedef Hyphenation ThisType;

public:

    /// Gets callback interface used to request dictionaries when page layout of the document is built.
    /// This allows delay loading of dictionaries which may be useful when processing documents in many languages.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::IHyphenationCallback> get_Callback();
    /// Sets callback interface used to request dictionaries when page layout of the document is built.
    /// This allows delay loading of dictionaries which may be useful when processing documents in many languages.
    static ASPOSE_WORDS_SHARED_API void set_Callback(const System::SharedPtr<Aspose::Words::IHyphenationCallback>& value);
    /// Called during a load hyphenation patterns, when an issue is detected that might result in formatting fidelity loss.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::IWarningCallback> get_WarningCallback();
    /// Called during a load hyphenation patterns, when an issue is detected that might result in formatting fidelity loss.
    static ASPOSE_WORDS_SHARED_API void set_WarningCallback(const System::SharedPtr<Aspose::Words::IWarningCallback>& value);

    /// Registers and loads a hyphenation dictionary for the specified language from a stream. Throws if dictionary cannot be read or has invalid format.
    /// 
    /// @param language A language name, e.g. "en-US". See .NET documentation for "culture name" and RFC 4646 for details.
    /// @param stream A stream for the dictionary file in OpenOffice format.
    static ASPOSE_WORDS_SHARED_API void RegisterDictionary(const System::String& language, const System::SharedPtr<System::IO::Stream>& stream);
    /// Registers and loads a hyphenation dictionary for the specified language from file. Throws if dictionary cannot be read or has invalid format.
    /// This method can also be used to register Null dictionary to prevent <see cref="Aspose::Words::Hyphenation::get_Callback">Callback</see> from being called repeatedly for the same language.
    /// 
    /// @param language A language name, e.g. "en-US". See .NET documentation for "culture name" and RFC 4646 for details.
    /// @param fileName A path to the dictionary file in Open Office format.
    ///     If this parameter is <c>%null</c> or empty string then registered is Null dictionary and callback is not called anymore for this language.
    ///     To enable callback again use <see cref="Aspose::Words::Hyphenation::UnregisterDictionary(System::String)">UnregisterDictionary()</see> method.
    static ASPOSE_WORDS_SHARED_API void RegisterDictionary(const System::String& language, const System::String& fileName);
    /// Unregisters a hyphenation dictionary for the specified language.
    /// This is different from registering Null dictionary. Unregistering a dictionary enables callback for the specified language.
    /// 
    /// @param language A language name, e.g. "en-US". See .NET documentation for "culture name" and RFC 4646 for details.
    ///     If <c>%null</c> or empty string then all dictionaries are unregistered.
    static ASPOSE_WORDS_SHARED_API void UnregisterDictionary(const System::String& language);
    /// Returns <c>%false</c> if for the specified language there is no dictionary registered or if registered is Null dictionary, <c>%true</c> otherwise.
    static ASPOSE_WORDS_SHARED_API bool IsDictionaryRegistered(const System::String& language);

    template <typename CharType, typename Traits>
    static void RegisterDictionary(System::String language, std::basic_istream<CharType, Traits>& stream)
    {
        auto streamWrapper = System::IO::WrapSTDIOStream(stream);
        RegisterDictionary(language, streamWrapper);
    }

protected:

private:

public:
    Hyphenation() = delete;
};

}
}
