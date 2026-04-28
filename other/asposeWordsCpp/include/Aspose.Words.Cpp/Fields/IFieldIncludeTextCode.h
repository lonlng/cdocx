//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldIncludeTextCode.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \cond
class IFieldIncludeTextCode : public virtual System::Object
{
    typedef IFieldIncludeTextCode ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::String get_SourceFullName() = 0;
    virtual System::String get_BookmarkName() = 0;
    virtual bool get_LockFields() = 0;
    virtual System::String get_NamespaceMappings() = 0;
    virtual System::String get_XPath() = 0;
    virtual System::String get_XslTransformation() = 0;
    virtual System::String get_TextConverter() = 0;
    virtual int32_t get_SourceFullNameArgumentIndex() = 0;

};/// \endcond

}
}
}
