//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldInfoResultProvider.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
class Document;
namespace Fields
{
namespace Expressions
{
class Constant;
}
class IFieldCode;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldInfoResultProvider : public System::Object
{
    typedef IFieldInfoResultProvider ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Fields::Expressions::Constant> GetResult(System::SharedPtr<Aspose::Words::Document> document, System::SharedPtr<Aspose::Words::Fields::IFieldCode> fieldCode) = 0;

};/// \endcond

}
}
}
