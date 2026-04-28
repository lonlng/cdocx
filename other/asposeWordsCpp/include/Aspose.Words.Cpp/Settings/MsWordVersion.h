//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/MsWordVersion.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Allows Aspose.Wods to mimic MS Word version-specific application behavior.
enum class ASPOSE_WORDS_SHARED_CLASS MsWordVersion
{
    /// Optimize %Aspose.Words behavior to match MS Word 2000 version.
    Word2000 = 0,
    /// Optimize %Aspose.Words behavior to match MS Word 2002 version.
    Word2002 = 1,
    /// Optimize %Aspose.Words behavior to match MS Word 2003 version.
    Word2003 = 2,
    /// Optimize %Aspose.Words behavior to match MS Word 2007 version.
    Word2007 = 3,
    /// Optimize %Aspose.Words behavior to match MS Word 2010 version.
    Word2010 = 4,
    /// Optimize %Aspose.Words behavior to match MS Word 2013 version.
    Word2013 = 5,
    /// Optimize %Aspose.Words behavior to match MS Word 2016 version.
    Word2016 = 6,
    /// Optimize %Aspose.Words behavior to match MS Word 2019 version.
    Word2019 = 7
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::MsWordVersion>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::MsWordVersion, const char_t*>, 8>& values();
};
