//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IIndexFilter.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// \interface IIndexFilter
/// Defines a filter for skipping items based on their indices.
class ASPOSE_WORDS_SHARED_CLASS IIndexFilter : public virtual System::Object
{
    typedef IIndexFilter ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Determines whether the item with the specified index should be skipped.
    /// 
    /// @param index The index of the item.
    /// 
    /// @return <c>%true</c> if the item should be skipped; otherwise, <c>%false</c>.
    virtual bool ShouldSkipIndex(int32_t index) = 0;

};

}
}
