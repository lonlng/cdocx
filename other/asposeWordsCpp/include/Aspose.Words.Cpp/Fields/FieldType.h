//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies %Microsoft Word field types.
enum class ASPOSE_WORDS_SHARED_CLASS FieldType
{
    /// Field type is not specified or unknown.
    FieldNone = 0,
    /// Specifies that the field was unable to be parsed.
    FieldCannotParse = 1,
    /// Specifies the ADDIN field.
    FieldAddin = 81,
    /// Specifies the ADDRESSBLOCK field.
    FieldAddressBlock = 93,
    /// Specifies the ADVANCE field.
    FieldAdvance = 84,
    /// Specifies the ASK field.
    FieldAsk = 38,
    /// Specifies the AUTHOR field.
    FieldAuthor = 17,
    /// Specifies the AUTONUM field.
    FieldAutoNum = 54,
    /// Specifies the AUTONUMLGL field.
    FieldAutoNumLegal = 53,
    /// Specifies the AUTONUMOUT field.
    FieldAutoNumOutline = 52,
    /// Specifies the AUTOTEXT field.
    FieldAutoText = 79,
    /// Specifies the AUTOTEXTLIST field.
    FieldAutoTextList = 89,
    /// Specifies the BARCODE field.
    FieldBarcode = 63,
    /// Specifies the BIBLIOGRAPHY field.
    FieldBibliography = 100500,
    /// Specifies the BIDIOUTLINE field.
    FieldBidiOutline = 92,
    /// Specifies the CITATION field.
    FieldCitation = 1980,
    /// Specifies the COMMENTS field.
    FieldComments = 19,
    /// Specifies the COMPARE field.
    FieldCompare = 80,
    /// Specifies the CREATEDATE field.
    FieldCreateDate = 21,
    /// Specifies the DATA field.
    FieldData = 40,
    /// Specifies the DATABASE field.
    FieldDatabase = 78,
    /// Specifies the DATE field.
    FieldDate = 31,
    /// Specifies the DDE field.
    FieldDDE = 45,
    /// Specifies the DISPLAYBARCODE field.
    FieldDisplayBarcode = 6301,
    /// Specifies the MERGEBARCODE field.
    FieldMergeBarcode = 6302,
    /// Specifies the DDEAUTO field.
    FieldDDEAuto = 46,
    /// Specifies the DOCPROPERTY field.
    FieldDocProperty = 85,
    /// Specifies the DOCVARIABLE field.
    FieldDocVariable = 64,
    /// Specifies the EDITTIME field.
    FieldEditTime = 25,
    /// Specifies the EMBED field.
    FieldEmbed = 58,
    /// Specifies the EQ field.
    FieldEquation = 49,
    /// Specifies the FILENAME field.
    FieldFileName = 29,
    /// Specifies the FILESIZE field.
    FieldFileSize = 69,
    /// Specifies the FILLIN field.
    FieldFillIn = 39,
    /// Specifies the FOOTNOTEREF field.
    FieldFootnoteRef = 5,
    /// Specifies the FORMCHECKBOX field.
    FieldFormCheckBox = 71,
    /// Specifies the FORMDROPDOWN field.
    FieldFormDropDown = 83,
    /// Specifies the FORMTEXT field.
    FieldFormTextInput = 70,
    /// Specifies the = (formula) field.
    FieldFormula = 34,
    /// Specifies the GREETINGLINE field.
    FieldGreetingLine = 94,
    /// Specifies the GLOSSARY field.
    FieldGlossary = 47,
    /// Specifies the GOTOBUTTON field.
    FieldGoToButton = 50,
    /// Specifies the field that represents an HTML control.
    FieldHtmlActiveX = 91,
    /// Specifies the HYPERLINK field.
    FieldHyperlink = 88,
    /// Specifies the IF field.
    FieldIf = 7,
    /// Specifies the INCLUDE field.
    FieldInclude = 36,
    /// Specifies the INCLUDEPICTURE field.
    FieldIncludePicture = 67,
    /// Specifies the INCLUDETEXT field.
    FieldIncludeText = 68,
    /// Specifies the INDEX field.
    FieldIndex = 8,
    /// Specifies the XE field.
    FieldIndexEntry = 4,
    /// Specifies the INFO field.
    FieldInfo = 14,
    /// Specifies the IMPORT field.
    FieldImport = 55,
    /// Specifies the KEYWORDS field.
    FieldKeyword = 18,
    /// Specifies the LASTSAVEDBY field.
    FieldLastSavedBy = 20,
    /// Specifies the LINK field.
    FieldLink = 56,
    /// Specifies the LISTNUM field.
    FieldListNum = 90,
    /// Specifies the MACROBUTTON field.
    FieldMacroButton = 51,
    /// Specifies the MERGEFIELD field.
    FieldMergeField = 59,
    /// Specifies the MERGEREC field.
    FieldMergeRec = 44,
    /// Specifies the MERGESEQ field.
    FieldMergeSeq = 75,
    /// Specifies the NEXT field.
    FieldNext = 41,
    /// Specifies the NEXTIF field.
    FieldNextIf = 42,
    /// Specifies the NOTEREF field.
    FieldNoteRef = 72,
    /// Specifies the NUMCHARS field.
    FieldNumChars = 28,
    /// Specifies the NUMPAGES field.
    FieldNumPages = 26,
    /// Specifies the NUMWORDS field.
    FieldNumWords = 27,
    /// Specifies the OCX field.
    /// Normally, %Aspose.Words will represent an ActiveX control as a
    /// <see cref="Aspose::Words::Drawing::Shape">Shape</see> object, but for some documents, where a control does
    /// not have data and/or seems to be invalid, it will be represented as a field.
    FieldOcx = 87,
    /// Specifies the PAGE field.
    FieldPage = 33,
    /// Specifies the PAGEREF field.
    FieldPageRef = 37,
    /// Specifies the PRINT field.
    FieldPrint = 48,
    /// Specifies the PRINTDATE field.
    FieldPrintDate = 23,
    /// Specifies the PRIVATE field.
    FieldPrivate = 77,
    /// Specifies the QUOTE field.
    FieldQuote = 35,
    /// Specifies the REF field.
    FieldRef = 3,
    /// Specifies that the field represents a REF field where the keyword has been omitted.
    FieldRefNoKeyword = 2,
    /// Specifies the RD field.
    FieldRefDoc = 11,
    /// Specifies the REVNUM field.
    FieldRevisionNum = 24,
    /// Specifies the SAVEDATE field.
    FieldSaveDate = 22,
    /// Specifies the SECTION field.
    FieldSection = 65,
    /// Specifies the SECTIONPAGES field.
    FieldSectionPages = 66,
    /// Specifies the SEQ field.
    FieldSequence = 12,
    /// Specifies the SET field.
    FieldSet = 6,
    /// Specifies the SHAPE field.
    FieldShape = 95,
    /// Specifies the SKIPIF field.
    FieldSkipIf = 43,
    /// Specifies the STYLEREF field.
    FieldStyleRef = 10,
    /// Specifies the SUBJECT field.
    FieldSubject = 16,
    /// Specifies the SYMBOL field.
    FieldSymbol = 57,
    /// Specifies the TEMPLATE field.
    FieldTemplate = 30,
    /// Specifies the TIME field.
    FieldTime = 32,
    /// Specifies the TITLE field.
    FieldTitle = 15,
    /// Specifies the TOA field.
    FieldTOA = 73,
    /// Specifies the TA field.
    FieldTOAEntry = 74,
    /// Specifies the TOC field.
    FieldTOC = 13,
    /// Specifies the TC field.
    FieldTOCEntry = 9,
    /// Specifies the USERADDRESS field.
    FieldUserAddress = 62,
    /// Specifies the USERINITIALS field.
    FieldUserInitials = 61,
    /// Specifies the USERNAME field.
    FieldUserName = 60
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::FieldType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::FieldType, const char_t*>, 97>& values();
};
