//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IHyphenationCallback.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// \interface IHyphenationCallback
/// Implemented by classes which can register hyphenation dictionaries.
class ASPOSE_WORDS_SHARED_CLASS IHyphenationCallback : public virtual System::Object
{
    typedef IHyphenationCallback ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Notifies application that hyphenation dictionary for the specified language wasn't found and may need to be registered.
    /// Implementation should find a dictionary and register it using <see cref="Aspose::Words::Hyphenation::RegisterDictionary(System::String, System::SharedPtr<System::IO::Stream>)">RegisterDictionary()</see> methods.
    /// If dictionary is unavailable for the specified language implementation can opt out of further calls for the same language
    /// using <see cref="Aspose::Words::Hyphenation::RegisterDictionary(System::String, System::String)">RegisterDictionary()</see> with <c>%null</c> value.
    /// 
    /// @param language A language name, e.g. "en-US". See .NET documentation for "culture name" and RFC 4646 for details.
    virtual void RequestDictionary(System::String language) = 0;

};

}
}
