//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/Contributor.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Bibliography {

/// Represents a bibliography source contributor. Can be either an corporate (an organization) or a list of persons.
class ASPOSE_WORDS_SHARED_CLASS Contributor : public virtual System::Object
{
    typedef Contributor ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

protected:

    Contributor();

    virtual System::SharedPtr<Aspose::Words::Bibliography::Contributor> Clone() = 0;

};

}
}
}
