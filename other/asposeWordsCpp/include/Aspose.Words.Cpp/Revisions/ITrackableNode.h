//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Revisions/ITrackableNode.h
#pragma once

#include <Aspose.Words.Cpp/Revisions/IMoveTrackableNode.h>

namespace Aspose
{
namespace Words
{
namespace Revisions
{
class EditRevision;
}
}
}

namespace Aspose {

namespace Words {

namespace Revisions {

/// \cond
class ITrackableNode : public Aspose::Words::Revisions::IMoveTrackableNode
{
    typedef ITrackableNode ThisType;
    typedef Aspose::Words::Revisions::IMoveTrackableNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<Aspose::Words::Revisions::EditRevision> get_InsertRevision() = 0;
    virtual void set_InsertRevision(System::SharedPtr<Aspose::Words::Revisions::EditRevision> value) = 0;
    virtual System::SharedPtr<Aspose::Words::Revisions::EditRevision> get_DeleteRevision() = 0;
    virtual void set_DeleteRevision(System::SharedPtr<Aspose::Words::Revisions::EditRevision> value) = 0;

};/// \endcond

}
}
}
