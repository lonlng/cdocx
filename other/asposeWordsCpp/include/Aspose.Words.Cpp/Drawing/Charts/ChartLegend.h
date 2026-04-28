//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartLegend.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Core/Dml/IDmlExtensionListSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/LegendPosition.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartFormatSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Collections
{
template <typename> class StringToObjDictionary;
}
namespace Words
{

namespace Drawing
{
namespace Charts
{

class ChartFormat;

class ChartLegendEntryCollection;

enum class ChartShapeType;

}
namespace Core
{
namespace Dml
{
class DmlExtension;
namespace Fills
{
class DmlFill;
}
namespace Outlines
{
class DmlOutline;
}
namespace Themes
{
class IThemeProvider;
}
}
}
}
class Font;

}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents chart legend properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartLegend : public Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource, public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef ChartLegend ThisType;
    typedef Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource BaseType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns a collection of legend entries for all series and trendlines of the parent chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegendEntryCollection> get_LegendEntries() const;
    /// Specifies the position of the legend on a chart.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::LegendPosition get_Position();
    /// Specifies the position of the legend on a chart.
    ASPOSE_WORDS_SHARED_API void set_Position(Aspose::Words::Drawing::Charts::LegendPosition value);
    /// Provides access to the default font formatting of legend entries. To override the font formatting for
    /// a specific legend entry, use the<see cref="Aspose::Words::Drawing::Charts::ChartLegendEntry::get_Font">Font</see> property.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Provides access to fill and line formatting of the legend.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();
    /// Determines whether other chart elements shall be allowed to overlap legend.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Overlay() const;
    /// Determines whether other chart elements shall be allowed to overlap legend.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Overlay(bool value);

protected:

    ChartLegend();

    virtual ASPOSE_WORDS_SHARED_API ~ChartLegend();

private:

    System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> get_Extensions() override;
    void set_Extensions(System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> ) override;
    bool get_IsFillSupported() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_Fill() override;
    void set_Fill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> get_Outline() override;
    void set_Outline(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> ) override;
    Aspose::Words::Drawing::Charts::ChartShapeType get_ShapeType() override;
    void set_ShapeType(Aspose::Words::Drawing::Charts::ChartShapeType ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_ThemeProvider() override;
    bool get_IsFormatDefined() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<4,4,4,4>::type mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    System::SharedPtr<System::Object> mField11;

    void MaterializeSpPr() override;

};

}
}
}
}
