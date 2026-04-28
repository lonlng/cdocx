//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Comparing/AdvancedCompareOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Comparing {

/// Allows to set advanced compare options.
class ASPOSE_WORDS_SHARED_CLASS AdvancedCompareOptions : public System::Object
{
    typedef AdvancedCompareOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether to ignore difference in DrawingML unique Id.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreDmlUniqueId() const;
    /// Specifies whether to ignore difference in DrawingML unique Id.
    ASPOSE_WORDS_SHARED_API void set_IgnoreDmlUniqueId(bool value);
    /// Specifies whether to ignore difference in StructuredDocumentTag store item Id.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreStoreItemId() const;
    /// Specifies whether to ignore difference in StructuredDocumentTag store item Id.
    ASPOSE_WORDS_SHARED_API void set_IgnoreStoreItemId(bool value);

    ASPOSE_WORDS_SHARED_API AdvancedCompareOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;

};

}
}
}
