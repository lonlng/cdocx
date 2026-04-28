//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/MarkdownLoadOptions.h
#pragma once

#include <Aspose.Words.Cpp/Loading/LoadOptions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify additional options when loading <see cref="Aspose::Words::LoadFormat::Markdown">Markdown</see> document into a <see cref="Aspose::Words::Document">Document</see> object.
class ASPOSE_WORDS_SHARED_CLASS MarkdownLoadOptions : public Aspose::Words::Loading::LoadOptions
{
    typedef MarkdownLoadOptions ThisType;
    typedef Aspose::Words::Loading::LoadOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets a boolean value indicating whether to preserve empty lines while load a <see cref="Aspose::Words::LoadFormat::Markdown">Markdown</see> document.
    /// The default value is <c>%false</c>.
    /// Normally, empty lines between block-level elements in Markdown are ignored. Empty lines at the beginning and
    /// end of the document are also ignored. This option allows to import such empty lines.
    ASPOSE_WORDS_SHARED_API bool get_PreserveEmptyLines() const;
    /// Setter for Aspose::Words::Loading::MarkdownLoadOptions::get_PreserveEmptyLines
    ASPOSE_WORDS_SHARED_API void set_PreserveEmptyLines(bool value);
    /// Gets a boolean value indicating either to recognize a sequence
    /// of two plus characters "++" as underline text formatting.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ImportUnderlineFormatting() const;
    /// Sets a boolean value indicating either to recognize a sequence
    /// of two plus characters "++" as underline text formatting.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ImportUnderlineFormatting(bool value);
    /// Gets a character value representing `soft line break`.
    /// The default value is <c>%SPACE (U+0020)</c>.
    ASPOSE_WORDS_SHARED_API char16_t get_SoftLineBreakCharacter() const;
    /// Sets a character value representing `soft line break`.
    /// The default value is <c>%SPACE (U+0020)</c>.
    ASPOSE_WORDS_SHARED_API void set_SoftLineBreakCharacter(char16_t value);

    /// Initializes a new instance of <see cref="Aspose::Words::Loading::MarkdownLoadOptions">MarkdownLoadOptions</see> class.
    ASPOSE_WORDS_SHARED_API MarkdownLoadOptions();

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<2,2,2,2>::type mField2;

};

}
}
}
