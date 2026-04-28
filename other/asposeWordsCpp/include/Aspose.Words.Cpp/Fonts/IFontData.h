//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/IFontData.h
#pragma once

#include <system/array.h>
#include <cstdint>

namespace System
{
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Fonts {

/// \cond
class IFontData : public virtual System::Object
{
    typedef IFontData ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO(ThisType, ThisTypeBaseTypesInfo);

public:

    virtual bool get_IsEmbedded() = 0;

    virtual System::SharedPtr<System::IO::Stream> OpenStream() = 0;

    virtual int32_t GetSize() = 0;

    virtual System::String GetFilePath() = 0;

    virtual System::String GetCacheKeyInternal() = 0;

    virtual System::ArrayPtr<uint8_t> GetFontBytes() = 0;

};/// \endcond

}
}
