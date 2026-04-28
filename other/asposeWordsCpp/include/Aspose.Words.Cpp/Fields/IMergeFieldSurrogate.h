//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IMergeFieldSurrogate.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class FieldEnd;
class FieldSeparator;
class FieldStart;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IMergeFieldSurrogate : public virtual System::Object
{
    typedef IMergeFieldSurrogate ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::FieldSeparator> get_Separator() = 0;
    virtual System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() = 0;

    virtual bool IsMergeValueRequired() = 0;
    virtual System::String GetMergeFieldName() = 0;
    virtual bool CanWorkAsMergeField() = 0;

};/// \endcond

}
}
}
