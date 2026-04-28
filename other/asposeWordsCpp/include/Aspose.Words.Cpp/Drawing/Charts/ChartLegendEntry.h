//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartLegendEntry.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/Drawing/Core/Dml/IDmlExtensionListSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartItemTextProperties.h>
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
namespace Core
{
namespace Dml
{
class DmlExtension;
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

/// Represents a chart legend entry.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
/// 
/// A legend entry corresponds to a specific chart series or trendline.
/// 
/// The text of the entry is the name of the series or trendline. The text cannot be changed.
/// 
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::get_LegendEntry
class ASPOSE_WORDS_SHARED_CLASS ChartLegendEntry : public Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource, public Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties
{
    typedef ChartLegendEntry ThisType;
    typedef Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource BaseType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a value indicating whether this entry is hidden in the chart legend.
    /// The default value is <b>%false</b>.
    ASPOSE_WORDS_SHARED_API bool get_IsHidden() const;
    /// Sets a value indicating whether this entry is hidden in the chart legend.
    /// The default value is <b>%false</b>.
    ASPOSE_WORDS_SHARED_API void set_IsHidden(bool value);
    /// Provides access to the font formatting of this legend entry.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();

protected:

    ChartLegendEntry();

    virtual ASPOSE_WORDS_SHARED_API ~ChartLegendEntry();

private:

    System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> get_Extensions() override;
    void set_Extensions(System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> get_ItemTx() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_ItemTxPr() override;
    void set_ItemTxPr(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartSpPr> get_ItemSpPr() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_CollectionTxPr() override;

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;

    System::String GenerateItemText() override;
    System::SharedPtr<System::Object> FetchSpecialDefaultRunPropertyValue(int32_t ) override;
    System::SharedPtr<System::Object> GetRelativePropertyValue(int32_t , System::SharedPtr<System::Object> ) override;

};

}
}
}
}
