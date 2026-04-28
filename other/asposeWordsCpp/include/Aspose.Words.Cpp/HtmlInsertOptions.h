//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/HtmlInsertOptions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies options for the <see cref="Aspose::Words::DocumentBuilder::InsertHtml(System::String, Aspose::Words::HtmlInsertOptions)">InsertHtml()</see> method.
enum class ASPOSE_WORDS_SHARED_CLASS HtmlInsertOptions
{
    /// Use the default options when inserting HTML.
    None = 0,
    /// Use font and paragraph formatting specified in <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see> as base formatting for text
    /// inserted from HTML.
    /// 
    /// If this option is not specified, formatting of <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see> is ignored and text is inserted
    /// with default HTML formatting. As a result, the text looks as it is rendered in browsers.
    /// 
    /// If this option is specified, formatting of inserted text is based on formatting specified in
    /// <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>, and the text looks as if it were inserted using <see cref="Aspose::Words::DocumentBuilder::Write(System::String)">Write()</see>.
    UseBuilderFormatting = 1,
    /// Remove the empty paragraph that is normally inserted after HTML that ends with a block-level element.
    RemoveLastEmptyParagraph = 2,
    /// Preserve properties of block-level elements.
    /// 
    /// By default, properties of parent blocks are merged and stored on their child elements (i.e. paragraphs or tables).
    /// If this option is specified, properties of each block are stored separately in a special logical structure.
    /// As a result, this option allows to better preserve individual borders and margins seen in the HTML document
    /// and get better conversion results. The downside is that the resulting document gets harder to modify, since borders
    /// and margins stored in the logical structure are not available for editing.
    /// 
    /// Only margins and borders of 'body', 'div', and 'blockquote' HTML elements are preserved. Properties of each HTML
    /// element are stored separately.
    /// 
    /// If this option is specified, %Aspose.Words mimics MS Word's behavior regarding import of block properties.
    PreserveBlocks = 4
};

DECLARE_ENUM_OPERATORS(Aspose::Words::HtmlInsertOptions);
DECLARE_USING_GLOBAL_OPERATORS

}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words);
template<>
struct EnumMetaInfo<Aspose::Words::HtmlInsertOptions>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::HtmlInsertOptions, const char_t*>, 4>& values();
};
