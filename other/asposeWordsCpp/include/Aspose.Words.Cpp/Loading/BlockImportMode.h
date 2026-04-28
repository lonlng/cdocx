//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/BlockImportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Specifies how properties of block-level elements are imported from HTML-based documents.
enum class ASPOSE_WORDS_SHARED_CLASS BlockImportMode
{
    /// Properties of parent blocks are merged and stored on child elements (i.e. paragraphs or tables).
    /// 
    /// Properties of parent blocks are merged as follows: margins are added together; borders of higher-level blocks
    /// are discarded and only the most inner-level borders are preserved. As a result, when this mode is specified,
    /// some formatting of blocks from the original document will be lost.
    /// 
    /// On the other hand, since all merged block-level properties are stored on document nodes, all formating
    /// in the resulting document will be available for modification.
    Merge = 0,
    /// Properties of parent blocks are imported to a special logical structure and are stored separately from
    /// document nodes.
    /// 
    /// Only margins and borders of 'body', 'div', and 'blockquote' HTML elements are imported. Properties of each HTML
    /// element are stored individually.
    /// 
    /// This mode allows to better preserve borders and margins seen in the HTML document and get better conversion
    /// results. The downside is that the resulting document gets harder to modify, since borders and margins stored
    /// in the logical structure are not available for editing.
    /// 
    /// This mode mimics MS Word's behavior regarding import of block properties.
    Preserve = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::BlockImportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::BlockImportMode, const char_t*>, 2>& values();
};
