//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DocumentBuilderOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Allows to specify additional options for the document building process.
class ASPOSE_WORDS_SHARED_CLASS DocumentBuilderOptions : public System::Object
{
    typedef DocumentBuilderOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// True if the formatting applied to table content does not affect the formatting of the content that follows it.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ContextTableFormatting() const;
    /// True if the formatting applied to table content does not affect the formatting of the content that follows it.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ContextTableFormatting(bool value);
    /// Corresponds to Design Mode in %Microsoft Word.
    ASPOSE_WORDS_SHARED_API bool get_DesignMode() const;
    /// Corresponds to Design Mode in %Microsoft Word.
    ASPOSE_WORDS_SHARED_API void set_DesignMode(bool value);

    ASPOSE_WORDS_SHARED_API DocumentBuilderOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;

};

}
}
