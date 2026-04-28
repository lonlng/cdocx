//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/Corporate.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Bibliography/Contributor.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Bibliography {

/// Represents a corporate (an organization) bibliography source contributor.
class ASPOSE_WORDS_SHARED_CLASS Corporate final : public Aspose::Words::Bibliography::Contributor
{
    typedef Corporate ThisType;
    typedef Aspose::Words::Bibliography::Contributor BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of an organization.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Sets the name of an organization.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);

    /// Initialize a new instance of the <see cref="Aspose::Words::Bibliography::Corporate">Corporate</see> class.
    /// 
    /// @param name The name of an organization.
    ASPOSE_WORDS_SHARED_API Corporate(const System::String& name);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> Clone() override;

private:

    System::String mField0;

};

}
}
}
