//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisDisplayUnit.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Core/Dml/IDmlExtensionListSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IDmlChartTitleHolder.h>
#include <Aspose.Words.Cpp/Drawing/Charts/AxisBuiltInUnit.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Collections
{
template <typename> class StringToObjDictionary;
}
namespace Words
{

class DocumentBase;
namespace Drawing
{
namespace Charts
{

namespace Core
{
namespace ComplexTypes
{

enum class DmlChartStyleItem;
class DmlChartTx;
}

class DmlChartSpace;
class DmlChartTitle;
namespace SimpleTypes
{
enum class TitlePosition;
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

/// Provides access to the scaling options of the display units for the value axis.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS AxisDisplayUnit : public Aspose::Words::Drawing::Charts::Core::IDmlChartTitleHolder, public Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource
{
    typedef AxisDisplayUnit ThisType;
    typedef Aspose::Words::Drawing::Charts::Core::IDmlChartTitleHolder BaseType;
    typedef Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the scaling value of the display units as one of the predefined values.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::AxisBuiltInUnit get_Unit() const;
    /// Sets the scaling value of the display units as one of the predefined values.
    ASPOSE_WORDS_SHARED_API void set_Unit(Aspose::Words::Drawing::Charts::AxisBuiltInUnit value);
    /// Gets or sets a user-defined divisor to scale display units on the value axis.
    /// 
    /// The property is not supported by MS Office 2016 new charts. Default value is 1.
    /// 
    /// Setting this property sets the <see cref="Aspose::Words::Drawing::Charts::AxisDisplayUnit::get_Unit">Unit</see> property to
    /// <see cref="Aspose::Words::Drawing::Charts::AxisBuiltInUnit::Custom">Custom</see>.
    ASPOSE_WORDS_SHARED_API double get_CustomUnit() const;
    /// Setter for Aspose::Words::Drawing::Charts::AxisDisplayUnit::get_CustomUnit
    ASPOSE_WORDS_SHARED_API void set_CustomUnit(double value);
    /// Returns the document containing the parent chart.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentBase> get_Document();

    ASPOSE_WORDS_SHARED_API AxisDisplayUnit();

protected:

private:

    System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> get_Extensions() override;
    void set_Extensions(System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::DmlChartTitle> get_DCTitle() override;
    void set_DCTitle(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::DmlChartTitle> ) override;
    Aspose::Words::Drawing::Charts::Core::SimpleTypes::TitlePosition get_TitlePosition() override;
    bool get_TitleDeleted() override;
    void set_TitleDeleted(bool ) override;
    bool get_IsVisible() override;
    System::String get_DefaultTitleText() override;
    double get_DefaultFontSize() override;
    double get_DefaultDisplayedFontSize() override;
    Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartStyleItem get_StyleItem() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::DmlChartSpace> get_ChartSpace() override;

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<8,8,8,8>::type mField1;
    System::SharedPtr<System::Object> mField2;
    System::WeakPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> GenerateAutoTitle() override;
    int32_t GetRelativeFontSize(int32_t ) override;

};

}
}
}
}
