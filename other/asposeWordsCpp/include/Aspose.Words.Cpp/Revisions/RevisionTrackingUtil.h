//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Revisions/RevisionTrackingUtil.h
#pragma once

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

class CompositeNode;

class Node;

}
}
namespace System
{

template <typename> class SmartPtr;
template <typename T0> using SharedPtr = System::SmartPtr<T0>;

}

namespace Aspose {

namespace Words {

namespace Revisions {

/// \cond
class ASPOSE_WORDS_SHARED_CLASS RevisionTrackingUtil
{
    typedef RevisionTrackingUtil ThisType;

public:

    static ASPOSE_WORDS_SHARED_API bool TrackDeletion(const System::SharedPtr<Aspose::Words::Node>& node);
    static ASPOSE_WORDS_SHARED_API void TrackInsertion(const System::SharedPtr<Aspose::Words::Node>& node, const System::SharedPtr<Aspose::Words::CompositeNode>& oldParent, const System::SharedPtr<Aspose::Words::Node>& oldNextSibling);

protected:

private:

public:
    RevisionTrackingUtil() = delete;
};/// \endcond

}
}
}
