//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/TxtLoadOptions.h
#pragma once

#include <drawing/color.h>

#include <Aspose.Words.Cpp/Loading/TxtTrailingSpacesOptions.h>
#include <Aspose.Words.Cpp/Loading/TxtLeadingSpacesOptions.h>
#include <Aspose.Words.Cpp/Loading/LoadOptions.h>
#include <Aspose.Words.Cpp/Loading/DocumentDirection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify additional options when loading <see cref="Aspose::Words::LoadFormat::Text">Text</see> document into a <see cref="Aspose::Words::Document">Document</see> object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS TxtLoadOptions : public Aspose::Words::Loading::LoadOptions
{
    typedef TxtLoadOptions ThisType;
    typedef Aspose::Words::Loading::LoadOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a boolean value indicating either automatic numbering detection
    /// will be performed while loading a document.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_AutoNumberingDetection() const;
    /// Sets a boolean value indicating either automatic numbering detection
    /// will be performed while loading a document.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_AutoNumberingDetection(bool value);
    /// Allows to specify how numbered list items are recognized when document is imported from plain text format.
    /// The default value is <c>%true</c>.
    /// 
    /// If this option is set to <c>%false</c>, lists recognition algorithm detects list paragraphs, when list numbers ends with
    /// either dot, right bracket or bullet symbols (such as "•", "*", "-" or "o").
    /// 
    /// If this option is set to <c>%true</c>, whitespaces are also used as list number delimiters:
    /// list recognition algorithm for Arabic style numbering (1., 1.1.2.) uses both whitespaces and dot (".") symbols.
    ASPOSE_WORDS_SHARED_API bool get_DetectNumberingWithWhitespaces() const;
    /// Setter for Aspose::Words::Loading::TxtLoadOptions::get_DetectNumberingWithWhitespaces
    ASPOSE_WORDS_SHARED_API void set_DetectNumberingWithWhitespaces(bool value);
    /// Gets preferred option of a trailing space handling.
    /// Default value is <see cref="Aspose::Words::Loading::TxtTrailingSpacesOptions::Trim">Trim</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::TxtTrailingSpacesOptions get_TrailingSpacesOptions() const;
    /// Sets preferred option of a trailing space handling.
    /// Default value is <see cref="Aspose::Words::Loading::TxtTrailingSpacesOptions::Trim">Trim</see>.
    ASPOSE_WORDS_SHARED_API void set_TrailingSpacesOptions(Aspose::Words::Loading::TxtTrailingSpacesOptions value);
    /// Gets preferred option of a leading space handling.
    /// Default value is <see cref="Aspose::Words::Loading::TxtLeadingSpacesOptions::ConvertToIndent">ConvertToIndent</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::TxtLeadingSpacesOptions get_LeadingSpacesOptions() const;
    /// Sets preferred option of a leading space handling.
    /// Default value is <see cref="Aspose::Words::Loading::TxtLeadingSpacesOptions::ConvertToIndent">ConvertToIndent</see>.
    ASPOSE_WORDS_SHARED_API void set_LeadingSpacesOptions(Aspose::Words::Loading::TxtLeadingSpacesOptions value);
    /// Gets a document direction.
    /// The default value is <see cref="Aspose::Words::Loading::DocumentDirection::LeftToRight">LeftToRight</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::DocumentDirection get_DocumentDirection() const;
    /// Sets a document direction.
    /// The default value is <see cref="Aspose::Words::Loading::DocumentDirection::LeftToRight">LeftToRight</see>.
    ASPOSE_WORDS_SHARED_API void set_DocumentDirection(Aspose::Words::Loading::DocumentDirection value);
    /// Specifies either to detect hyperlinks in text.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_DetectHyperlinks() const;
    /// Specifies either to detect hyperlinks in text.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_DetectHyperlinks(bool value);

    /// Initializes a new instance of this class with default values.
    ASPOSE_WORDS_SHARED_API TxtLoadOptions();

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    System::Drawing::Color mField6;
    __TypeStub<4,4,4,4>::type mField7;

};

}
}
}
