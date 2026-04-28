//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IExpandableAttr.h
#pragma once

#include <Aspose.Words.Cpp/IComplexAttr.h>

namespace Aspose {

namespace Words {

/// \cond
class IExpandableAttr : public Aspose::Words::IComplexAttr
{
    typedef IExpandableAttr ThisType;
    typedef Aspose::Words::IComplexAttr BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::IExpandableAttr> Expand(System::SharedPtr<Aspose::Words::IExpandableAttr> parentAttr) = 0;
    virtual void Collapse(System::SharedPtr<Aspose::Words::IExpandableAttr> parentAttr) = 0;

};/// \endcond

}
}
