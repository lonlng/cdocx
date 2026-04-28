//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListTemplate.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Lists {

/// Specifies one of the predefined list formats available in %Microsoft Word.
/// 
/// A list template value is used as a parameter into the
/// <see cref="Aspose::Words::Lists::ListCollection::Add(Aspose::Words::Lists::ListTemplate)">Add()</see> method.
/// 
/// %Aspose.Words list templates correspond to the 21 list templates available
/// in the Bullets and Numbering dialog box in %Microsoft Word 2003.
enum class ASPOSE_WORDS_SHARED_CLASS ListTemplate
{
    /// Default bulleted list with 9 levels. Bullet of the first level is a disc,
    /// bullet of the second level is a circle, bullet of the third level is a square.
    /// Then formatting repeats for the remaining levels.
    /// Each level is indented to the right by 0.25" relative to the previous level.
    /// Corresponds to the 1st bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletDefault,
    /// Same as <see cref="Aspose::Words::Lists::ListTemplate::BulletDefault">BulletDefault</see>.
    /// Corresponds to the 1st bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletDisk = static_cast<int32_t>(BulletDefault),
    /// The bullet of the first level is a circle. The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::BulletDefault">BulletDefault</see>.
    /// Corresponds to the 2nd bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletCircle,
    /// The bullet of the first level is a square. The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::BulletDefault">BulletDefault</see>.
    /// Corresponds to the 3rd bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletSquare,
    /// The bullet of the first level is a 4-diamond Wingding character. The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::BulletDefault">BulletDefault</see>.
    /// Corresponds to the 5th bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletDiamonds,
    /// The bullet of the first level is an arrow head Wingding character. The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::BulletDefault">BulletDefault</see>.
    /// Corresponds to the 6th bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletArrowHead,
    /// The bullet of the first level is a tick Wingding character. The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::BulletDefault">BulletDefault</see>.
    /// Corresponds to the 7th bulleted list template in the Bullets and Numbering dialog box in %Microsoft Word.
    BulletTick,
    /// Default numbered list with 9 levels. Arabic numbering (1., 2., 3., ...) for the first level,
    /// lowercase letter numbering (a., b., c., ...) for the second level,
    /// lowercase roman numbering (i., ii., iii., ...) for the third level.
    /// Then formatting repeats for the remaining levels.
    /// Each level is indented to the right by 0.25" relative to the previous level.
    /// Corresponds to the 1st numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberDefault,
    /// Same as <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 1st numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberArabicDot = static_cast<int32_t>(NumberDefault),
    /// The number of the first level is "1)". The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 2nd numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberArabicParenthesis,
    /// The number of the first level is "I.". The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 3rd numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberUppercaseRomanDot,
    /// The number of the first level is "A.". The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 4th numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberUppercaseLetterDot,
    /// The number of the first level is "a)". The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 5th numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberLowercaseLetterParenthesis,
    /// The number of the first level is "a.". The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 6th numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberLowercaseLetterDot,
    /// The number of the first level is "i.". The remaining levels are same as in <see cref="Aspose::Words::Lists::ListTemplate::NumberDefault">NumberDefault</see>.
    /// Corresponds to the 7th numbered list template in the Bullets and Numbering dialog box in %Microsoft Word.
    NumberLowercaseRomanDot,
    /// An outline list with levels numbered "1), a), i), (1), (a), (i), 1., a., i.".
    /// Corresponds to the 1st outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineNumbers,
    /// An outline list with levels are numbered "1., 1.1., 1.1.1, ...".
    /// Corresponds to the 2nd outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineLegal,
    /// An outline lists with various bullets for different levels.
    /// Corresponds to the 3rd outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineBullets,
    /// An outline list with levels linked to Heading styles.
    /// Corresponds to the 4th outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineHeadingsArticleSection,
    /// An outline list with levels linked to Heading styles.
    /// Corresponds to the 5th outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineHeadingsLegal,
    /// An outline list with levels linked to Heading styles.
    /// Corresponds to the 6th outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineHeadingsNumbers,
    /// An outline list with levels linked to Heading styles.
    /// Corresponds to the 7th outline list template in the Bullets and Numbering dialog box in %Microsoft Word.
    OutlineHeadingsChapter
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Lists::ListTemplate>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Lists::ListTemplate, const char_t*>, 22>& values();
};
