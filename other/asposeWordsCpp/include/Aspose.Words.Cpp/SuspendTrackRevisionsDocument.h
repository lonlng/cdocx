//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SuspendTrackRevisionsDocument.h
#pragma once

#include <system/shared_ptr.h>
#include <system/idisposable.h>

#include <Aspose.Words.Cpp/SuspendedRevisionTypes.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
}
}

namespace Aspose {

namespace Words {

/// \cond
class ASPOSE_WORDS_SHARED_CLASS SuspendTrackRevisionsDocument final : public System::IDisposable
{
    typedef SuspendTrackRevisionsDocument ThisType;
    typedef System::IDisposable BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    ASPOSE_WORDS_SHARED_API SuspendTrackRevisionsDocument(const System::SharedPtr<Aspose::Words::DocumentBase>& document);
    ASPOSE_WORDS_SHARED_API SuspendTrackRevisionsDocument(const System::SharedPtr<Aspose::Words::DocumentBase>& document, Aspose::Words::SuspendedRevisionTypes revisionTypes);

    ASPOSE_WORDS_SHARED_API void Close();
    ASPOSE_WORDS_SHARED_API void Dispose() override;

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;

};/// \endcond

}
}
