//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MarkdownExportAsHtml.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify the elements to be exported to Markdown as raw HTML.
enum class ASPOSE_WORDS_SHARED_CLASS MarkdownExportAsHtml
{
    /// Export all elements using Markdown syntax without any raw HTML.
    None = 0x0000,
    /// Export tables as raw HTML.
    /// 
    /// When this option is enabled, every table will be exported as raw HTML.
    /// %Aspose.Words will try to preserve all formatting of the tables in this case.
    /// 
    /// If this flag is set, then related <see cref="Aspose::Words::Saving::MarkdownExportAsHtml::NonCompatibleTables">NonCompatibleTables</see> flag will be ignored.
    Tables = 0x0001,
    /// Export tables that cannot be correctly represented in pure Markdown as raw HTML.
    /// 
    /// When this option is enabled, %Aspose.Words will only export tables that have merged cells
    /// or nested tables as raw HTML. And all other tables will be exported in Markdown format.
    /// Also note, this option will not preserve all formatting of the table, but only preserves
    /// corresponding spans of the cells.
    /// 
    /// If related <see cref="Aspose::Words::Saving::MarkdownExportAsHtml::Tables">Tables</see> flag is set, then this flag will be ignored.
    NonCompatibleTables = 0x0002
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Saving::MarkdownExportAsHtml);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Saving);
template<>
struct EnumMetaInfo<Aspose::Words::Saving::MarkdownExportAsHtml>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::MarkdownExportAsHtml, const char_t*>, 3>& values();
};
