//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeFinder.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/NodeEnumerator.h>

namespace Aspose
{

namespace Words
{

class Node;
class NodeRange;
enum class NodeType;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IList;
}
}
}

namespace Aspose {

namespace Words {

/// \cond
class NodeFinder : public Aspose::Words::NodeEnumerator
{
    typedef NodeFinder ThisType;
    typedef Aspose::Words::NodeEnumerator BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    static System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::Node>>> FindNodes(const System::SharedPtr<Aspose::Words::NodeRange>& range, const System::ArrayPtr<Aspose::Words::NodeType>& nodeTypes);
    System::SharedPtr<System::Collections::Generic::IList<System::SharedPtr<Aspose::Words::Node>>> Find();

protected:

    virtual bool OnNodeFinding();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};/// \endcond

}
}
