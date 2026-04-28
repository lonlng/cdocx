//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PageExtractOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Allows to specify options for document page extracting.
class ASPOSE_WORDS_SHARED_CLASS PageExtractOptions : public System::Object
{
    typedef PageExtractOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether the start page number in the resulting document shall be updated.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UpdatePageStartingNumber() const;
    /// Specifies whether the start page number in the resulting document shall be updated.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_UpdatePageStartingNumber(bool value);
    /// Specifies whether NUMPAGES fields in the resulting document will be replaced with their actual resulting values.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UnlinkPagesNumberFields() const;
    /// Specifies whether NUMPAGES fields in the resulting document will be replaced with their actual resulting values.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_UnlinkPagesNumberFields(bool value);

    ASPOSE_WORDS_SHARED_API PageExtractOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;

};

}
}
