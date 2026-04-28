//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlVersion.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Indicates the version of HTML is used when saving the document to <see cref="Aspose::Words::SaveFormat::Html">Html</see> and
/// <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see> formats.
enum class ASPOSE_WORDS_SHARED_CLASS HtmlVersion
{
    /// Saves the document in compliance with the XHTML 1.0 Transitional standard.
    /// 
    /// %Aspose.Words aims to output XHTML according to the XHTML 1.0 Transitional standard,
    /// but the output will not always validate against the DTD. Some structures inside a %Microsoft Word
    /// document are hard or impossible to map to a document that will validate against the XHTML schema.
    /// For example, XHTML does not allow nested lists (UL cannot be nested inside another UL element),
    /// but in %Microsoft Word document multilevel lists occur quite often.
    Xhtml = 0,
    /// Saves the document in compliance with the HTML 5 standard.
    Html5 = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::HtmlVersion>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::HtmlVersion, const char_t*>, 2>& values();
};
