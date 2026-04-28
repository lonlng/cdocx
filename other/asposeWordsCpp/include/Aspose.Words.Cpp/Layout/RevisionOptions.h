//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/RevisionOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/MeasurementUnits.h>
#include <Aspose.Words.Cpp/Drawing/HorizontalAlignment.h>
#include <Aspose.Words.Cpp/Layout/ShowInBalloons.h>
#include <Aspose.Words.Cpp/Layout/RevisionTextEffect.h>
#include <Aspose.Words.Cpp/Layout/RevisionColor.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Allows to control how document revisions are handled during layout process.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/converting-to-fixed-page-format/">Converting to Fixed-page Format</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS RevisionOptions : public System::Object
{
    typedef RevisionOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Allow to specify whether revision text should be marked with special formatting markup.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowRevisionMarks() const;
    /// Allow to specify whether revision text should be marked with special formatting markup.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowRevisionMarks(bool value);
    /// Allows to specify whether revision bars should be rendered near lines containing revised content.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowRevisionBars() const;
    /// Allows to specify whether revision bars should be rendered near lines containing revised content.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowRevisionBars(bool value);
    /// Allows to specify whether the original text should be shown instead of revised one.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowOriginalRevision() const;
    /// Allows to specify whether the original text should be shown instead of revised one.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowOriginalRevision(bool value);
    /// Allows to specify the color to be used for inserted cells <see cref="Aspose::Words::RevisionType::Insertion">Insertion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Blue">Blue</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_InsertCellColor();
    /// Allows to specify the color to be used for inserted cells <see cref="Aspose::Words::RevisionType::Insertion">Insertion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Blue">Blue</see>.
    ASPOSE_WORDS_SHARED_API void set_InsertCellColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the color to be used for deleted cells <see cref="Aspose::Words::RevisionType::Deletion">Deletion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Pink">Pink</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_DeleteCellColor();
    /// Allows to specify the color to be used for deleted cells <see cref="Aspose::Words::RevisionType::Deletion">Deletion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Pink">Pink</see>.
    ASPOSE_WORDS_SHARED_API void set_DeleteCellColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the color to be used for inserted content <see cref="Aspose::Words::RevisionType::Insertion">Insertion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_InsertedTextColor();
    /// Allows to specify the color to be used for inserted content <see cref="Aspose::Words::RevisionType::Insertion">Insertion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API void set_InsertedTextColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the effect to be applied to the inserted content <see cref="Aspose::Words::RevisionType::Insertion">Insertion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::Underline">Underline</see>.
    /// 
    /// @exception System::ArgumentOutOfRangeException Value of <see cref="Aspose::Words::Layout::RevisionTextEffect::Hidden">Hidden</see>
    ///     is not allowed.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionTextEffect get_InsertedTextEffect();
    /// Setter for Aspose::Words::Layout::RevisionOptions::get_InsertedTextEffect
    ASPOSE_WORDS_SHARED_API void set_InsertedTextEffect(Aspose::Words::Layout::RevisionTextEffect value);
    /// Allows to specify the color to be used for deleted content <see cref="Aspose::Words::RevisionType::Deletion">Deletion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_DeletedTextColor();
    /// Allows to specify the color to be used for deleted content <see cref="Aspose::Words::RevisionType::Deletion">Deletion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API void set_DeletedTextColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the effect to be applied to the deleted content <see cref="Aspose::Words::RevisionType::Deletion">Deletion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::StrikeThrough">StrikeThrough</see>
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionTextEffect get_DeletedTextEffect();
    /// Allows to specify the effect to be applied to the deleted content <see cref="Aspose::Words::RevisionType::Deletion">Deletion</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::StrikeThrough">StrikeThrough</see>
    ASPOSE_WORDS_SHARED_API void set_DeletedTextEffect(Aspose::Words::Layout::RevisionTextEffect value);
    /// Allows to specify the color to be used for areas where content was moved from <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_MovedFromTextColor();
    /// Allows to specify the color to be used for areas where content was moved from <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API void set_MovedFromTextColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the effect to be applied to the areas where content was moved from <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::DoubleStrikeThrough">DoubleStrikeThrough</see>
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionTextEffect get_MovedFromTextEffect();
    /// Allows to specify the effect to be applied to the areas where content was moved from <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::DoubleStrikeThrough">DoubleStrikeThrough</see>
    ASPOSE_WORDS_SHARED_API void set_MovedFromTextEffect(Aspose::Words::Layout::RevisionTextEffect value);
    /// Allows to specify the color to be used for areas where content was moved to <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_MovedToTextColor();
    /// Allows to specify the color to be used for areas where content was moved to <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::ByAuthor">ByAuthor</see>.
    ASPOSE_WORDS_SHARED_API void set_MovedToTextColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the effect to be applied to the areas where content was moved to <see cref="Aspose::Words::RevisionType::Moving">Moving</see>.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::DoubleUnderline">DoubleUnderline</see>
    /// 
    /// @exception System::ArgumentOutOfRangeException Value of <see cref="Aspose::Words::Layout::RevisionTextEffect::Hidden">Hidden</see>
    ///     is not allowed.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionTextEffect get_MovedToTextEffect();
    /// Setter for Aspose::Words::Layout::RevisionOptions::get_MovedToTextEffect
    ASPOSE_WORDS_SHARED_API void set_MovedToTextEffect(Aspose::Words::Layout::RevisionTextEffect value);
    /// Allows to specify the color to be used for content with changes of formatting properties <see cref="Aspose::Words::RevisionType::FormatChange">FormatChange</see>
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::NoHighlight">NoHighlight</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_RevisedPropertiesColor();
    /// Allows to specify the color to be used for content with changes of formatting properties <see cref="Aspose::Words::RevisionType::FormatChange">FormatChange</see>
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::NoHighlight">NoHighlight</see>.
    ASPOSE_WORDS_SHARED_API void set_RevisedPropertiesColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify the effect for content areas with changes of formatting properties <see cref="Aspose::Words::RevisionType::FormatChange">FormatChange</see>
    /// Default value is <see cref="Aspose::Words::Layout::RevisionTextEffect::None">None</see>
    /// 
    /// @exception System::ArgumentOutOfRangeException <see cref="Aspose::Words::Layout::RevisionTextEffect::Hidden">Hidden</see> is not allowed.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionTextEffect get_RevisedPropertiesEffect();
    /// Setter for Aspose::Words::Layout::RevisionOptions::get_RevisedPropertiesEffect
    ASPOSE_WORDS_SHARED_API void set_RevisedPropertiesEffect(Aspose::Words::Layout::RevisionTextEffect value);
    /// Allows to specify the color to be used for side bars that identify document lines containing revised information.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Red">Red</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_RevisionBarsColor() const;
    /// Allows to specify the color to be used for side bars that identify document lines containing revised information.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Red">Red</see>.
    ASPOSE_WORDS_SHARED_API void set_RevisionBarsColor(Aspose::Words::Layout::RevisionColor value);
    /// Gets width of revision bars, points.
    ASPOSE_WORDS_SHARED_API float get_RevisionBarsWidth() const;
    /// Sets width of revision bars, points.
    ASPOSE_WORDS_SHARED_API void set_RevisionBarsWidth(float value);
    /// Gets or sets rendering position of revision bars.
    /// Default value is <see cref="Aspose::Words::Drawing::HorizontalAlignment::Outside">Outside</see>.
    /// 
    /// @exception System::ArgumentOutOfRangeException Values of <see cref="Aspose::Words::Drawing::HorizontalAlignment::Center">Center</see> and <see cref="Aspose::Words::Drawing::HorizontalAlignment::Inside">Inside</see>
    ///     are not allowed.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::HorizontalAlignment get_RevisionBarsPosition() const;
    /// Setter for Aspose::Words::Layout::RevisionOptions::get_RevisionBarsPosition
    ASPOSE_WORDS_SHARED_API void set_RevisionBarsPosition(Aspose::Words::Drawing::HorizontalAlignment value);
    /// Allows to specify the color to be used for comments.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Red">Red</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::RevisionColor get_CommentColor() const;
    /// Allows to specify the color to be used for comments.
    /// Default value is <see cref="Aspose::Words::Layout::RevisionColor::Red">Red</see>.
    ASPOSE_WORDS_SHARED_API void set_CommentColor(Aspose::Words::Layout::RevisionColor value);
    /// Allows to specify whether the revisions are rendered in the balloons.
    /// Default value is <see cref="Aspose::Words::Layout::ShowInBalloons::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Layout::ShowInBalloons get_ShowInBalloons() const;
    /// Allows to specify whether the revisions are rendered in the balloons.
    /// Default value is <see cref="Aspose::Words::Layout::ShowInBalloons::None">None</see>.
    ASPOSE_WORDS_SHARED_API void set_ShowInBalloons(Aspose::Words::Layout::ShowInBalloons value);
    /// Allows to specify the measurement units for revision comments.
    /// Default value is <see cref="Aspose::Words::MeasurementUnits::Centimeters">Centimeters</see>
    ASPOSE_WORDS_SHARED_API Aspose::Words::MeasurementUnits get_MeasurementUnit() const;
    /// Allows to specify the measurement units for revision comments.
    /// Default value is <see cref="Aspose::Words::MeasurementUnits::Centimeters">Centimeters</see>
    ASPOSE_WORDS_SHARED_API void set_MeasurementUnit(Aspose::Words::MeasurementUnits value);

protected:

    RevisionOptions();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<4,4,4,4>::type mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    System::SharedPtr<System::Object> mField11;
    System::SharedPtr<System::Object> mField12;
    System::SharedPtr<System::Object> mField13;
    System::SharedPtr<System::Object> mField14;
    System::SharedPtr<System::Object> mField15;
    __TypeStub<1,1,1,1>::type mField16;

};

}
}
}
