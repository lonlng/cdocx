//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataLabelLocationMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies how the values ​​that specify the location of a data label - the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Left">Left</see> and
/// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Top">Top</see> properties - are interpreted.
enum class ASPOSE_WORDS_SHARED_CLASS ChartDataLabelLocationMode
{
    /// The location of a data label is specified by an offset from the position defined by its
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see> property.
    Offset,
    /// The location of a data label is specified using absolute coordinates, staring from the upper left corner
    /// of a chart.
    Absolute
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::ChartDataLabelLocationMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::ChartDataLabelLocationMode, const char_t*>, 2>& values();
};
