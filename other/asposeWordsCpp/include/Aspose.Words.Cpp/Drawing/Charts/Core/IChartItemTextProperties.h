//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/Core/IChartItemTextProperties.h
#pragma once

#include <system/object.h>
#include <cstdint>

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
class IChartItemTextProperties : public virtual System::Object
{
    typedef IChartItemTextProperties ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> get_ItemTx() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_ItemTxPr() = 0;
    virtual void set_ItemTxPr(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> value) = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartSpPr> get_ItemSpPr() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_CollectionTxPr() = 0;

    virtual System::String GenerateItemText() = 0;
    virtual System::SharedPtr<System::Object> FetchSpecialDefaultRunPropertyValue(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> GetRelativePropertyValue(int32_t key, System::SharedPtr<System::Object> value) = 0;

};/// \endcond

}
}
}
}
}
