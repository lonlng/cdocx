//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/CompositeNodeHelper.h
#pragma once

#include <Aspose.Words.Cpp/NodeChangingAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class Node;
class NodeChangingArgs;
}
}
namespace System
{
template <typename> class SmartPtr;
template <typename T0> using SharedPtr = System::SmartPtr<T0>;
}

namespace Aspose {

namespace Words {

/// \cond
class ASPOSE_WORDS_SHARED_CLASS CompositeNodeHelper
{
    typedef CompositeNodeHelper ThisType;

public:

    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeChangingArgs> DocumentBaseInternalEvent(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, const System::SharedPtr<Aspose::Words::Node>& newChild, const System::SharedPtr<Aspose::Words::Node>& oldParent, const System::SharedPtr<Aspose::Words::Node>& newParent, Aspose::Words::NodeChangingAction action);
    static ASPOSE_WORDS_SHARED_API void DocumentBaseBeforeEvent(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, const System::SharedPtr<Aspose::Words::NodeChangingArgs>& args);
    static ASPOSE_WORDS_SHARED_API void DocumentBaseAfterEvent(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, const System::SharedPtr<Aspose::Words::NodeChangingArgs>& args);
    static ASPOSE_WORDS_SHARED_API bool DocumentBaseIsTrackRevisionsEnabled(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);
    static ASPOSE_WORDS_SHARED_API void DocumentBaseCompareException(const System::SharedPtr<Aspose::Words::DocumentBase>& thisDoc, const System::SharedPtr<Aspose::Words::DocumentBase>& childDoc);

public:
    CompositeNodeHelper() = delete;
};/// \endcond

}
}
