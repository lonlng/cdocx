//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeEnumerator.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>

#include <Aspose.Words.Cpp/IDocumentPositionListener.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

enum class DocumentPositionMovement;

class Node;

class NodeRange;

}
}

namespace Aspose {

namespace Words {

/// \cond
class ASPOSE_WORDS_SHARED_CLASS NodeEnumerator : public System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>>, public Aspose::Words::IDocumentPositionListener
{
    typedef NodeEnumerator ThisType;
    typedef System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>> BaseType;
    typedef Aspose::Words::IDocumentPositionListener BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();
    CODEPORTING_ENUMERATOR_ITERATOR_METHODS_DECLARATION(CODEPORTING_ARGS(System::SharedPtr<Aspose::Words::Node>), ASPOSE_WORDS_SHARED_API);

public:

    ASPOSE_WORDS_SHARED_API void Dispose() override;
    ASPOSE_WORDS_SHARED_API void Reset() override;

protected:

    ASPOSE_WORDS_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(NodeEnumerator, CODEPORTING_ARGS(const System::SharedPtr<Aspose::Words::NodeRange>& range, bool stopAtInvalidRangeNodes));

    virtual ASPOSE_WORDS_SHARED_API bool NeedSkipRangeNodeExtract(System::SharedPtr<Aspose::Words::Node> );
    virtual ASPOSE_WORDS_SHARED_API void OnMoved(Aspose::Words::DocumentPositionMovement );

    virtual ASPOSE_WORDS_SHARED_API ~NodeEnumerator();

private:

    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Node>& get_Current() const override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;

    ASPOSE_WORDS_SHARED_API bool MoveNext() override;
    ASPOSE_WORDS_SHARED_API void NotifyMoved(Aspose::Words::DocumentPositionMovement ) override;

};/// \endcond

}
}
