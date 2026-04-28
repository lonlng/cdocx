//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/ToaCategories.h
#pragma once

#include <system/string.h>
#include <mutex>
#include <memory>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents a table of authorities categories.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ToaCategories : public System::Object
{
    typedef ToaCategories ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the default table of authorities categories.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::ToaCategories> get_DefaultCategories();

    ASPOSE_WORDS_SHARED_API ToaCategories();

    /// Gets or sets the category heading by category number.
    ASPOSE_WORDS_SHARED_API System::String idx_get(int32_t number);
    /// Gets or sets the category heading by category number.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t number, const System::String& value);

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
