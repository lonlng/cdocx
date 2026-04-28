//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/ControlChar.h
#pragma once

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// Control characters often encountered in documents.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-control-characters/">Working With Control Characters</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ControlChar
{
    typedef ControlChar ThisType;

public:

    /// End of a table cell or end of a table row character: "\x0007" or "\a".
    static ASPOSE_WORDS_SHARED_API System::String& Cell();
    /// Tab character: "\x0009" or "\t".
    static ASPOSE_WORDS_SHARED_API System::String& Tab();
    /// Line feed character: "\x000a" or "\n". Same as <see cref="Aspose::Words::ControlChar::LineFeed">LineFeed</see>.
    static ASPOSE_WORDS_SHARED_API System::String& Lf();
    /// Line feed character: "\x000a" or "\n". Same as <see cref="Aspose::Words::ControlChar::Lf">Lf</see>.
    static ASPOSE_WORDS_SHARED_API System::String& LineFeed();
    /// Line break character: "\x000b" or "\v".
    static ASPOSE_WORDS_SHARED_API System::String& LineBreak();
    /// Page break character: "\x000c" or "\f". Note it has the same value as <see cref="Aspose::Words::ControlChar::SectionBreak">SectionBreak</see>.
    static ASPOSE_WORDS_SHARED_API System::String& PageBreak();
    /// End of section character: "\x000c" or "\f". Note it has the same value as <see cref="Aspose::Words::ControlChar::PageBreak">PageBreak</see>.
    static ASPOSE_WORDS_SHARED_API System::String& SectionBreak();
    /// Carriage return character: "\x000d" or "\r". Same as <see cref="Aspose::Words::ControlChar::ParagraphBreak">ParagraphBreak</see>.
    static ASPOSE_WORDS_SHARED_API System::String& Cr();
    /// End of paragraph character: "\x000d" or "\r". Same as <see cref="Aspose::Words::ControlChar::Cr">Cr</see>
    static ASPOSE_WORDS_SHARED_API System::String& ParagraphBreak();
    /// End of column character: "\x000e".
    static ASPOSE_WORDS_SHARED_API System::String& ColumnBreak();
    /// Carriage return followed by line feed character: "\x000d\x000a" or "\r\n".
    /// Not used as such in %Microsoft Word documents, but commonly used in text files for paragraph breaks.
    static ASPOSE_WORDS_SHARED_API System::String& CrLf();
    /// Non-breaking space character: "\x00a0".
    static ASPOSE_WORDS_SHARED_API System::String& NonBreakingSpace();

protected:

public:

    /// End of a table cell or end of a table row character: (char)7 or "\a".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t CellChar = (char16_t)7;
    /// Tab character: (char)9 or "\t".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t TabChar = (char16_t)9;
    /// Line feed character: (char)10 or "\n".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t LineFeedChar = (char16_t)10;
    /// Line break character: (char)11 or "\v".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t LineBreakChar = (char16_t)11;
    /// Page break character: (char)12 or "\f".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t PageBreakChar = (char16_t)12;
    /// End of section character: (char)12 or "\f".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t SectionBreakChar = (char16_t)12;
    /// End of paragraph character: (char)13 or "\r".
    static constexpr ASPOSE_WORDS_SHARED_API char16_t ParagraphBreakChar = (char16_t)13;
    /// End of column character: (char)14.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t ColumnBreakChar = (char16_t)14;
    /// Start of MS Word field character: (char)19.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t FieldStartChar = (char16_t)19;
    /// Field separator character separates field code from field value. Optional in some fields. Value: (char)20.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t FieldSeparatorChar = (char16_t)20;
    /// End of MS Word field character: (char)21.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t FieldEndChar = (char16_t)21;
    /// Non-breaking Hyphen in %Microsoft Word is (char)30.
    /// 
    /// Non-breaking Hyphen in %Microsoft Word does not correspond to the
    /// Unicode character U+2011 non-breaking hyphen but instead represents
    /// internal information that tells %Microsoft Word to display a hyphen and not to break a line.
    /// 
    /// Useful info: http://www.cs.tut.fi/~jkorpela/dashes.html#linebreaks.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t NonBreakingHyphenChar = (char16_t)30;
    /// Optional Hyphen in %Microsoft Word is (char)31.
    /// 
    /// Optional Hyphen in %Microsoft Word does not correspond to the Unicode character U+00AD soft hyphen.
    /// Instead, it inserts internal information that tells Word about a possible hyphenation point.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t OptionalHyphenChar = (char16_t)31;
    /// Space character: (char)32.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t SpaceChar = (char16_t)32;
    /// Non-breaking space character: (char)160.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t NonBreakingSpaceChar = u'\x00a0';
    /// This is the "o" character used as a default value in text input form fields.
    static constexpr ASPOSE_WORDS_SHARED_API char16_t DefaultTextInputChar = u'\x2002';

protected:

     static constexpr char16_t BackslashChar = u'\\';
     static constexpr char16_t YenChar = u'\x00a5';
     static constexpr char16_t UnicodeOptionalHyphenChar = u'\x00ad';
     static constexpr char16_t EnSpaceChar = u'\x2002';
     static constexpr char16_t EmSpaceChar = u'\x2003';
     static constexpr char16_t FourPerEmSpaceChar = u'\x2005';
     static constexpr char16_t IdeographicSpaceChar = u'\x3000';
     static constexpr char16_t LeftToRightMarkChar = u'\x200e';
     static constexpr char16_t RightToLeftMarkChar = u'\x200f';
     static constexpr char16_t LeftToRightEmbedding = u'\x202A';
     static constexpr char16_t RightToLeftEmbedding = u'\x202B';
     static constexpr char16_t LeftToRightOverride = u'\x202D';
     static constexpr char16_t RightToLeftOverride = u'\x202E';
     static constexpr char16_t PopDirectionalFormatting = u'\x202C';
     static constexpr char16_t LeftToRightIsolate = u'\x2066';
     static constexpr char16_t RightToLeftIsolate = u'\x2067';
     static constexpr char16_t FirstStrongIsolate = u'\x2068';
     static constexpr char16_t PopDirectionalIsolate = u'\x2069';
     static constexpr char16_t ArabicLetterMark = u'\x061C';
     static constexpr char16_t UnicodeNonBreakingHyphenChar = u'\x2011';
     static constexpr char16_t EnDashChar = u'\x2013';
     static constexpr char16_t EmDashChar = u'\x2014';
     static constexpr char16_t ZeroWidthNonJoinerChar = u'\x200c';
     static constexpr char16_t ZeroWidthJoinerChar = u'\x200d';
     static constexpr char16_t ZeroWidthSpaceChar = u'\x200b';
     static constexpr char16_t ZeroWithNoBreakSpace = u'\xfeff';
     static constexpr char16_t UnicodeLineSeparator = u'\x2028';

public:
    ControlChar() = delete;
};

}
}
