//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/CleanupOptions.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Allows to specify options for document cleaning.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/clean-up-a-document/">Clean Up a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS CleanupOptions : public System::Object
{
    typedef CleanupOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether unused styles should be removed from document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UnusedStyles() const;
    /// Specifies whether unused styles should be removed from document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_UnusedStyles(bool value);
    /// Specifies whether unused list and list definitions should be removed from document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UnusedLists() const;
    /// Specifies whether unused list and list definitions should be removed from document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_UnusedLists(bool value);
    /// Gets/sets a flag indicating whether duplicate styles should be removed from document.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_DuplicateStyle() const;
    /// Gets/sets a flag indicating whether duplicate styles should be removed from document.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_DuplicateStyle(bool value);
    /// Specifies that unused <see cref="Aspose::Words::Style::get_BuiltIn">BuiltIn</see> styles should be removed from document.
    ASPOSE_WORDS_SHARED_API bool get_UnusedBuiltinStyles() const;
    /// Specifies that unused <see cref="Aspose::Words::Style::get_BuiltIn">BuiltIn</see> styles should be removed from document.
    ASPOSE_WORDS_SHARED_API void set_UnusedBuiltinStyles(bool value);

    ASPOSE_WORDS_SHARED_API CleanupOptions();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;

};

}
}
