//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/Core/IDmlChartTitleHolder.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Charts/Core/SimpleTypes/TitlePosition.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/ComplexTypes/DmlChartStyleItem.h>

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
class DmlChartTx;
}
class DmlChartSpace;
class DmlChartTitle;
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

namespace Core {

/// \cond
class IDmlChartTitleHolder : public virtual System::Object
{
    typedef IDmlChartTitleHolder ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::DmlChartTitle> get_DCTitle() = 0;
    virtual void set_DCTitle(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::DmlChartTitle> value) = 0;
    virtual Aspose::Words::Drawing::Charts::Core::SimpleTypes::TitlePosition get_TitlePosition() = 0;
    virtual bool get_IsVisible() = 0;
    virtual bool get_TitleDeleted() = 0;
    virtual void set_TitleDeleted(bool value) = 0;
    virtual System::String get_DefaultTitleText() = 0;
    virtual double get_DefaultDisplayedFontSize() = 0;
    virtual double get_DefaultFontSize() = 0;
    virtual Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartStyleItem get_StyleItem() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::DmlChartSpace> get_ChartSpace() = 0;

    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> GenerateAutoTitle() = 0;
    virtual int32_t GetRelativeFontSize(int32_t chartFontSize) = 0;

};/// \endcond

}
}
}
}
}
