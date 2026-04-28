//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DocumentPositionMovement.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// DocumentPositionMovement enumeration.
enum class ASPOSE_WORDS_SHARED_CLASS DocumentPositionMovement
{
    None,
    Inside,
    StartEnd,
    Sibling,
    Above,
    Below
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::DocumentPositionMovement>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::DocumentPositionMovement, const char_t*>, 6>& values();
};
