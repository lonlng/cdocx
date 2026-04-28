//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/RevisionsView.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Allows to specify whether to work with the original or revised version of a document.
enum class ASPOSE_WORDS_SHARED_CLASS RevisionsView
{
    /// Specifies original version of a document.
    Original,
    /// Specifies revised version of a document.
    Final
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::RevisionsView>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::RevisionsView, const char_t*>, 2>& values();
};
