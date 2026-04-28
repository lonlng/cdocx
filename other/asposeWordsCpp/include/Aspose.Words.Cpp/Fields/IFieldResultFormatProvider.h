//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldResultFormatProvider.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class IFieldResultFormatApplier;
}
class Inline;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldResultFormatProvider : public virtual System::Object
{
    typedef IFieldResultFormatProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Inline> GetSourceNode() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::IFieldResultFormatApplier> GetFormatApplier() = 0;

};/// \endcond

}
}
}
