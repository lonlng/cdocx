/// @file system/codeporting_translator_cs2cpp_framework.h
/// Contains declaration of System::AsposeCppLibrary class.
#pragma once

#include "defines.h"

namespace System
{
    /// @cond
    /// Represents CodePorting.Translator Cs2Cpp Framework library and contains library initialization/uninitialization methods.
    /// This is a static type with no instance services.
    /// You should never create instances of it by any means.
    class Cs2CppFramework
    {
    public:
        /// Prepares the library for unload. Blocks until all worker threads exit.
        static ASPOSECPP_SHARED_API void PrepareForUnload();
    };
    /// @endcond
}
