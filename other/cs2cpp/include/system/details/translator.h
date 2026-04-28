/// @file system/details/Translator.h
#pragma once

#include <defines.h>


namespace CodePorting { namespace Translator { namespace Cs2Cpp {

/// API to get information from translator.
class Translator
{
public:
    /// Checks whether code is translated or running in C#.
    /// @return Always returns true.
    static bool get_IsTranslated()
    {
        return true;
    }

    /// Platform family.
    enum class Platform
    {
        /// Untranslated code.
        DotNet,
        /// Translated code, built for Windows.
        Windows,
        /// Translated code, built for Linux.
        Linux,
        /// Translated code, built for MacOS.
        MacOS,
        /// Translated code, built for WebAssembly.
        WebAssembly
    };

    /// The platform current code is being built for or is being executed at.
    static constexpr Platform CurrentPlatform =
#if defined(CODEPORTING_WINDOWS)
        Platform::Windows;
#elif defined(CODEPORTING_LINUX)
        Platform::Linux;
#elif defined(CODEPORTING_MACOS)
        Platform::MacOS;
#elif defined(CODEPORTING_WEBASSEMBLY)
        Platform::WebAssembly;
#else
#error "Unknown platform"
#endif

    /// Build configuration.
    enum class Configuration
    {
        /// Debug configuration.
        Debug,
        /// Release configuration.
        Release,
        /// No information is present.
        Unknown
    };

    /// Configuration current code is built for. In C++, will be a constexpr static field.
    static constexpr Configuration CurrentConfiguration =
#if defined(_DEBUG) || defined(DEBUG)
        Configuration::Debug;
#else
        Configuration::Release;
#endif
};

} } } // namespace CodePorting::Translator::Cs2Cpp

