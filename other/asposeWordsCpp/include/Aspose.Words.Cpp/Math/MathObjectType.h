//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Math/MathObjectType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Math {

/// Specifies type of an Office Math object.
enum class ASPOSE_WORDS_SHARED_CLASS MathObjectType
{
    /// Instance of mathematical text.
    OMath,
    /// Math paragraph, or display math zone, that contains one or more <see cref="Aspose::Words::Math::MathObjectType::OMath">OMath</see> elements that are in display mode.
    OMathPara,
    /// Accent function, consisting of a base and a combining diacritical mark.
    Accent,
    /// Bar function, consisting of a base argument and an overbar or underbar.
    Bar,
    /// Border Box object, consisting of a border drawn around an instance of mathematical text (such as a formula or equation)
    BorderBox,
    /// Box object, which is used to group components of an equation or other instance of mathematical text.
    Box,
    /// Delimiter object, consisting of opening and closing delimiters (such as parentheses,
    /// braces, brackets, and vertical bars), and an element contained inside.
    Delimiter,
    /// Degree in the mathematical radical.
    Degree,
    /// Argument object. Encloses Office Math entities when they are used as arguments to other Office Math entities.
    Argument,
    /// Array object, consisting of one or more equations, expressions, or other mathematical text runs
    /// that can be vertically justified as a unit with respect to surrounding text on the line.
    Array,
    /// Fraction object, consisting of a numerator and denominator separated by a fraction bar.
    Fraction,
    /// Denominator of a fraction object.
    Denominator,
    /// Numerator of the Fraction object.
    Numerator,
    /// Function-Apply object, which consists of a function name and an argument element acted upon.
    Function,
    /// Name of the function. For example, function names are sin and cos.
    FunctionName,
    /// Group-Character object, consisting of a character drawn above or below text, often
    /// with the purpose of visually grouping items
    GroupCharacter,
    /// Lower limit of the <see cref="Aspose::Words::Math::MathObjectType::LowerLimit">LowerLimit</see> object and
    /// the upper limit of the <see cref="Aspose::Words::Math::MathObjectType::UpperLimit">UpperLimit</see> function.
    Limit,
    /// Lower-Limit object, consisting of text on the baseline and reduced-size text immediately below it.
    LowerLimit,
    /// Upper-Limit object, consisting of text on the baseline and reduced-size text immediately above it.
    UpperLimit,
    /// Matrix object, consisting of one or more elements laid out in one or more rows and one or more columns.
    Matrix,
    /// Single row of the matrix.
    MatrixRow,
    /// N-ary object, consisting of an n-ary object, a base (or operand), and optional upper and lower limits.
    NAry,
    /// Phantom object.
    Phantom,
    /// Radical object, consisting of a radical, a base element, and an optional degree .
    Radical,
    /// Subscript of the object that can have subscript part.
    SubscriptPart,
    /// Superscript of the superscript object.
    SuperscriptPart,
    /// Pre-Sub-Superscript object, which consists of a base element and a subscript and superscript placed to the left of the base.
    PreSubSuperscript,
    /// Subscript object, which consists of a base element and a reduced-size script placed below and to the right.
    Subscript,
    /// Sub-superscript object, which consists of a base element, a reduced-size script placed below and to the right, and a reduced-size script placed above and to the right.
    SubSuperscript,
    /// Superscript object, which consists of a base element and a reduced-size script placed above and to the right.
    Supercript
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Math::MathObjectType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Math::MathObjectType, const char_t*>, 30>& values();
};
