//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IBorderAttrSource.h
#pragma once

#include <system/object.h>
#include <cstdint>

namespace Aspose
{
namespace Words
{
enum class BorderType;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class SortedList;
}
}
}

namespace Aspose {

namespace Words {

/// \cond
class IBorderAttrSource : public virtual System::Object
{
    typedef IBorderAttrSource ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() = 0;

    virtual System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t key) = 0;
    virtual System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t key) = 0;
    virtual void SetBorderAttr(int32_t key, System::SharedPtr<System::Object> value) = 0;

};/// \endcond

}
}
