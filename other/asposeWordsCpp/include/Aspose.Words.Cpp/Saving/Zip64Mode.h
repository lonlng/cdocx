//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/Zip64Mode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies when to use ZIP64 format extensions for OOXML files.
/// 
/// @sa Aspose::Words::Saving::OoxmlSaveOptions::get_Zip64Mode
enum class ASPOSE_WORDS_SHARED_CLASS Zip64Mode
{
    /// Do not use ZIP64 format extensions.
    Never = 0,
    /// If necessary use ZIP64 format extensions.
    IfNecessary = 1,
    /// Always use ZIP64 format extensions.
    Always = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::Zip64Mode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::Zip64Mode, const char_t*>, 3>& values();
};
