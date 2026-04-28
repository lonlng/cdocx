//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/EndnoteOptions.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/NumberStyle.h>
#include <Aspose.Words.Cpp/Notes/IFootnoteOptions.h>
#include <Aspose.Words.Cpp/Notes/FootnoteNumberingRule.h>
#include <Aspose.Words.Cpp/Notes/EndnotePosition.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Notes
{
enum class FootnoteLocation;
}

}
}

namespace Aspose {

namespace Words {

namespace Notes {

/// Represents the endnote numbering options for a document or section.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-footnote-and-endnote/">Working with Footnote and Endnote</a> documentation article.
/// 
/// @sa Aspose::Words::Document::get_EndnoteOptions
/// @sa Aspose::Words::PageSetup::get_EndnoteOptions
class ASPOSE_WORDS_SHARED_CLASS EndnoteOptions final : public Aspose::Words::Notes::IFootnoteOptions
{
    typedef EndnoteOptions ThisType;
    typedef Aspose::Words::Notes::IFootnoteOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the endnotes position.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Notes::EndnotePosition get_Position();
    /// Specifies the endnotes position.
    ASPOSE_WORDS_SHARED_API void set_Position(Aspose::Words::Notes::EndnotePosition value);
    /// Specifies the number format for automatically numbered endnotes.
    /// 
    /// Not all number styles are applicable for this property. For the list of applicable
    /// number styles see the Insert Footnote or Endnote dialog box in %Microsoft Word. If you select
    /// a number style that is not applicable, %Microsoft Word will revert to a default value.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NumberStyle get_NumberStyle() override;
    /// Setter for Aspose::Words::Notes::EndnoteOptions::get_NumberStyle
    ASPOSE_WORDS_SHARED_API void set_NumberStyle(Aspose::Words::NumberStyle value) override;
    /// Specifies the starting number or character for the first automatically numbered endnotes.
    /// 
    /// This property has effect only when <see cref="Aspose::Words::Notes::EndnoteOptions::get_RestartRule">RestartRule</see> is set to
    /// <see cref="Aspose::Words::Notes::FootnoteNumberingRule::Continuous">Continuous</see>.
    ASPOSE_WORDS_SHARED_API int32_t get_StartNumber() override;
    /// Setter for Aspose::Words::Notes::EndnoteOptions::get_StartNumber
    ASPOSE_WORDS_SHARED_API void set_StartNumber(int32_t value) override;
    /// Determines when automatic numbering restarts.
    /// 
    /// Not all values are applicable to endnotes.
    /// To ascertain which values are applicable see <see cref="Aspose::Words::Notes::FootnoteNumberingRule">FootnoteNumberingRule</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Notes::FootnoteNumberingRule get_RestartRule() override;
    /// Setter for Aspose::Words::Notes::EndnoteOptions::get_RestartRule
    ASPOSE_WORDS_SHARED_API void set_RestartRule(Aspose::Words::Notes::FootnoteNumberingRule value) override;

protected:

private:

    Aspose::Words::Notes::FootnoteLocation get_Location() override;
    void set_Location(Aspose::Words::Notes::FootnoteLocation ) override;

    System::WeakPtr<System::Object> mField0;

};

}
}
}
