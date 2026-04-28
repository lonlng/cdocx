//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/Core/IEmbeddedObject.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
namespace Core
{
class OleObject;
}
}
class IShapeAttrSource;
}
}
namespace System
{
namespace IO
{
class Stream;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Ole {

namespace Core {

/// \cond
class IEmbeddedObject : public System::Object
{
    typedef IEmbeddedObject ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::String get_ClsidInternal() = 0;
    virtual bool get_IsForms2OleControlInternal() = 0;
    virtual int32_t get_Id() = 0;
    virtual void set_Id(int32_t value) = 0;
    virtual bool get_IsEmpty() = 0;

    virtual System::String GetName() = 0;
    virtual System::SharedPtr<Aspose::Words::Drawing::Core::OleObject> GetOleObject() = 0;
    virtual System::String GetExtensionForUser(System::String progId) = 0;
    virtual System::String GetFileNameForUser() = 0;
    virtual void SaveForUser(System::SharedPtr<System::IO::Stream> stream, System::SharedPtr<Aspose::Words::IShapeAttrSource> attrSource) = 0;

};/// \endcond

}
}
}
}
}
