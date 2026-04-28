//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldUpdatingProgressArgs.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Provides data for the field updating progress event.
class ASPOSE_WORDS_SHARED_CLASS FieldUpdatingProgressArgs final : public System::Object
{
    typedef FieldUpdatingProgressArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the total fields count to be updated.
    ASPOSE_WORDS_SHARED_API int32_t get_TotalFieldsCount() const;
    /// Gets the number of updated fields.
    ASPOSE_WORDS_SHARED_API int32_t get_UpdatedFieldsCount() const;
    /// Gets a value indicating whether field updating is completed.
    ASPOSE_WORDS_SHARED_API bool get_UpdateCompleted() const;

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;

};

}
}
}
