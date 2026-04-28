//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/MailMergeCleanupOptions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace MailMerging {

/// Specifies options that determine what items are removed during mail merge.
enum class ASPOSE_WORDS_SHARED_CLASS MailMergeCleanupOptions
{
    /// Specifies a default value.
    None = 0x00,
    /// Specifies whether paragraphs that contained mail merge fields with no data should be removed from the document.
    /// When this option is set, paragraphs which contain region start and end merge fields which are otherwise empty
    /// are also removed.
    RemoveEmptyParagraphs = 0x01,
    /// Specifies whether unused mail merge regions should be removed from the document.
    RemoveUnusedRegions = 0x02,
    /// Specifies whether unused merge fields should be removed from the document.
    RemoveUnusedFields = 0x04,
    /// Specifies whether fields that contain merge fields (for example, IFs) should be removed from the document
    /// if the nested merge fields are removed.
    RemoveContainingFields = 0x08,
    /// Specifies whether static fields should be removed from the document. Static fields are fields, which
    /// results remain the same upon any document change. Fields, which do not store their results in a document
    /// and are calculated on the fly (like <see cref="Aspose::Words::Fields::FieldType::FieldListNum">FieldListNum</see>,
    /// <see cref="Aspose::Words::Fields::FieldType::FieldSymbol">FieldSymbol</see>, etc.) are not considered to be static.
    /// 
    /// Here is the full list of field types, which are not considered to be static:
    /// 
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldAdvance">FieldAdvance</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldAutoNum">FieldAutoNum</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldAutoNumLegal">FieldAutoNumLegal</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldAutoNumOutline">FieldAutoNumOutline</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldBarcode">FieldBarcode</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldBidiOutline">FieldBidiOutline</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldDate">FieldDate</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldDisplayBarcode">FieldDisplayBarcode</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldMergeBarcode">FieldMergeBarcode</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldFormCheckBox">FieldFormCheckBox</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldFormDropDown">FieldFormDropDown</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldFormula">FieldFormula</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldGoToButton">FieldGoToButton</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldHyperlink">FieldHyperlink</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldIncludeText">FieldIncludeText</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldIndexEntry">FieldIndexEntry</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldLink">FieldLink</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldListNum">FieldListNum</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldMacroButton">FieldMacroButton</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldNoteRef">FieldNoteRef</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldNumPages">FieldNumPages</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldPage">FieldPage</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldPageRef">FieldPageRef</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldPrint">FieldPrint</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldPrintDate">FieldPrintDate</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldPrivate">FieldPrivate</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldRefDoc">FieldRefDoc</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldSection">FieldSection</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldSectionPages">FieldSectionPages</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldSymbol">FieldSymbol</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldTime">FieldTime</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldTOAEntry">FieldTOAEntry</see>
    /// - <see cref="Aspose::Words::Fields::FieldType::FieldTOCEntry">FieldTOCEntry</see>
    RemoveStaticFields = 0x10,
    /// Specifies whether empty rows that contain mail merge regions should be removed from the document.
    RemoveEmptyTableRows = 0x20,
    /// Specifies whether to remove from the document tables that contain mail merge regions that were removed using
    /// either the <see cref="Aspose::Words::MailMerging::MailMergeCleanupOptions::RemoveUnusedRegions">RemoveUnusedRegions</see> or the <see cref="Aspose::Words::MailMerging::MailMergeCleanupOptions::RemoveEmptyTableRows">RemoveEmptyTableRows</see> option.
    RemoveEmptyTables = 0x40
};

DECLARE_ENUM_OPERATORS(Aspose::Words::MailMerging::MailMergeCleanupOptions);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::MailMerging);
template<>
struct EnumMetaInfo<Aspose::Words::MailMerging::MailMergeCleanupOptions>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::MailMerging::MailMergeCleanupOptions, const char_t*>, 8>& values();
};
