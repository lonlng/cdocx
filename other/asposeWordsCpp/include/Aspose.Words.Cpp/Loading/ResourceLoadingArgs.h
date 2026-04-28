//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/ResourceLoadingArgs.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Loading/ResourceType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Provides data for the <see cref="Aspose::Words::Loading::IResourceLoadingCallback::ResourceLoading(System::SharedPtr<Aspose::Words::Loading::ResourceLoadingArgs>)">ResourceLoading()</see> method.
class ASPOSE_WORDS_SHARED_CLASS ResourceLoadingArgs : public System::Object
{
    typedef ResourceLoadingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Type of resource.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::ResourceType get_ResourceType() const;
    /// URI of the resource which is used for downloading
    /// if <see cref="Aspose::Words::Loading::IResourceLoadingCallback::ResourceLoading(System::SharedPtr<Aspose::Words::Loading::ResourceLoadingArgs>)">ResourceLoading()</see>
    /// returns <see cref="Aspose::Words::Loading::ResourceLoadingAction::Default">Default</see>.
    /// Initially it's set to absolute URI of the resource,
    /// but user can redefine it to any value.
    ASPOSE_WORDS_SHARED_API System::String get_Uri() const;
    /// Setter for Aspose::Words::Loading::ResourceLoadingArgs::get_Uri
    ASPOSE_WORDS_SHARED_API void set_Uri(const System::String& value);
    /// Original URI of the resource as specified in imported document.
    ASPOSE_WORDS_SHARED_API System::String get_OriginalUri() const;

    /// Sets user provided data of the resource which is used
    /// if <see cref="Aspose::Words::Loading::IResourceLoadingCallback::ResourceLoading(System::SharedPtr<Aspose::Words::Loading::ResourceLoadingArgs>)">ResourceLoading()</see>
    /// returns <see cref="Aspose::Words::Loading::ResourceLoadingAction::UserProvided">UserProvided</see>.
    ASPOSE_WORDS_SHARED_API void SetData(const System::ArrayPtr<uint8_t>& data);

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;

};

}
}
}
