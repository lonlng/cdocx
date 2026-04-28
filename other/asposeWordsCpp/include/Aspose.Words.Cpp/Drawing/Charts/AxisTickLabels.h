//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisTickLabels.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/ParagraphAlignment.h>
#include <Aspose.Words.Cpp/Drawing/ShapeTextOrientation.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartItemTextProperties.h>
#include <Aspose.Words.Cpp/Drawing/Charts/AxisTickLabelPosition.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
namespace Charts
{

namespace Core
{

namespace ComplexTypes
{
class DmlChartSpPr;
class DmlChartTx;
class DmlChartTxPr;
}

}
}

}
class Font;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents properties of axis tick mark labels.
class ASPOSE_WORDS_SHARED_CLASS AxisTickLabels : public Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties
{
    typedef AxisTickLabels ThisType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the position of the tick labels on the axis.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::AxisTickLabelPosition get_Position();
    /// Sets the position of the tick labels on the axis.
    ASPOSE_WORDS_SHARED_API void set_Position(Aspose::Words::Drawing::Charts::AxisTickLabelPosition value);
    /// Gets or sets the distance of the tick labels from the axis.
    /// 
    /// The property represents a percentage of the default label offset.
    /// 
    /// Valid range is from 0 to 1000 percent inclusive. The default value is 100\%.
    /// 
    /// The property has effect only for category axes. It is not supported by MS Office 2016 new charts.
    ASPOSE_WORDS_SHARED_API int32_t get_Offset();
    /// Setter for Aspose::Words::Drawing::Charts::AxisTickLabels::get_Offset
    ASPOSE_WORDS_SHARED_API void set_Offset(int32_t value);
    /// Gets or sets the interval at which the tick labels are drawn.
    /// 
    /// The property has effect for text category and series axes. It is not supported by MS Office 2016
    /// new charts. Valid range of a value is greater than or equal to 1.
    /// 
    /// Setting this property sets the <see cref="Aspose::Words::Drawing::Charts::AxisTickLabels::get_IsAutoSpacing">IsAutoSpacing</see> property to <c>%false</c>.
    ASPOSE_WORDS_SHARED_API int32_t get_Spacing();
    /// Setter for Aspose::Words::Drawing::Charts::AxisTickLabels::get_Spacing
    ASPOSE_WORDS_SHARED_API void set_Spacing(int32_t value);
    /// Gets or sets a flag indicating whether to use automatic interval for drawing the tick labels.
    /// 
    /// The default value is <c>%true</c>.
    /// 
    /// The property has effect for text category and series axes. It is not supported by MS Office 2016
    /// new charts.
    ASPOSE_WORDS_SHARED_API bool get_IsAutoSpacing();
    /// Setter for Aspose::Words::Drawing::Charts::AxisTickLabels::get_IsAutoSpacing
    ASPOSE_WORDS_SHARED_API void set_IsAutoSpacing(bool value);
    /// Gets or sets text alignment of the axis tick labels.
    /// 
    /// This property has effect only for multi-line labels.
    /// 
    /// The default value is <see cref="Aspose::Words::ParagraphAlignment::Center">Center</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::ParagraphAlignment get_Alignment();
    /// Setter for Aspose::Words::Drawing::Charts::AxisTickLabels::get_Alignment
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::ParagraphAlignment value);
    /// Gets or sets the orientation of the tick label text.
    /// 
    /// The default value is <see cref="Aspose::Words::Drawing::ShapeTextOrientation::Horizontal">Horizontal</see>.
    /// 
    /// Note that some <see cref="Aspose::Words::Drawing::ShapeTextOrientation">ShapeTextOrientation</see> values do not affect the orientation of tick label text
    /// in value axes.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ShapeTextOrientation get_Orientation();
    /// Setter for Aspose::Words::Drawing::Charts::AxisTickLabels::get_Orientation
    ASPOSE_WORDS_SHARED_API void set_Orientation(Aspose::Words::Drawing::ShapeTextOrientation value);
    /// Gets the rotation of the tick labels in degrees.
    ASPOSE_WORDS_SHARED_API int32_t get_Rotation();
    /// Sets the rotation of the tick labels in degrees.
    ASPOSE_WORDS_SHARED_API void set_Rotation(int32_t value);
    /// Provides access to font formatting of the tick labels.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~AxisTickLabels();

private:

    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> get_ItemTx() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_ItemTxPr() override;
    void set_ItemTxPr(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartSpPr> get_ItemSpPr() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_CollectionTxPr() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

    System::String GenerateItemText() override;
    System::SharedPtr<System::Object> FetchSpecialDefaultRunPropertyValue(int32_t ) override;
    System::SharedPtr<System::Object> GetRelativePropertyValue(int32_t , System::SharedPtr<System::Object> ) override;

};

}
}
}
}
