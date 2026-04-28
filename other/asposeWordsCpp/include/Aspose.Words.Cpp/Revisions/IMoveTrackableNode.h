//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Revisions/IMoveTrackableNode.h
#pragma once

#include <system/object.h>

namespace Aspose
{
namespace Words
{
namespace Revisions
{
class MoveRevision;
}
}
}

namespace Aspose {

namespace Words {

namespace Revisions {

/// \cond
class IMoveTrackableNode : public virtual System::Object
{
    typedef IMoveTrackableNode ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveFromRevision() = 0;
    virtual void set_MoveFromRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> value) = 0;
    virtual System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveToRevision() = 0;
    virtual void set_MoveToRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> value) = 0;

    virtual void RemoveMoveRevisions() = 0;

};/// \endcond

}
}
}
