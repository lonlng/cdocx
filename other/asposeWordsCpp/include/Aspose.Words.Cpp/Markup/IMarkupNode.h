//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/IMarkupNode.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Markup/MarkupLevel.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// \cond
class IMarkupNode : public virtual System::Object
{
    typedef IMarkupNode ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::Markup::MarkupLevel get_Level_IMarkupNode() = 0;

};/// \endcond

}
}
}
