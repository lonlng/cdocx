//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/SplitOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/LowCode/SplitCriteria.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace LowCode {

/// Specifies options how the document is split into parts.
class ASPOSE_WORDS_SHARED_CLASS SplitOptions : public System::Object
{
    typedef SplitOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the criteria for splitting the document into parts.
    ASPOSE_WORDS_SHARED_API Aspose::Words::LowCode::SplitCriteria get_SplitCriteria() const;
    /// Specifies the criteria for splitting the document into parts.
    ASPOSE_WORDS_SHARED_API void set_SplitCriteria(Aspose::Words::LowCode::SplitCriteria value);
    /// Specifies the paragraph style for splitting the document into parts when <see cref="Aspose::Words::LowCode::SplitCriteria::Style">Style</see> is used.
    ASPOSE_WORDS_SHARED_API System::String get_SplitStyle() const;
    /// Specifies the paragraph style for splitting the document into parts when <see cref="Aspose::Words::LowCode::SplitCriteria::Style">Style</see> is used.
    ASPOSE_WORDS_SHARED_API void set_SplitStyle(const System::String& value);

    ASPOSE_WORDS_SHARED_API SplitOptions();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;

};

}
}
}
