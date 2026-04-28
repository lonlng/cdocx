//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/ComparisonEvaluationResult.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// The comparison evaluation result.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ComparisonEvaluationResult final : public System::Object
{
    typedef ComparisonEvaluationResult ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the comparison evaluation result.
    ASPOSE_WORDS_SHARED_API bool get_Result() const;
    /// Gets the failed comparison evaluation result's error message.
    ASPOSE_WORDS_SHARED_API System::String get_ErrorMessage() const;

    /// Creates a comparison evaluation result.
    ASPOSE_WORDS_SHARED_API ComparisonEvaluationResult(bool result);
    /// Creates a failed comparison evaluation result with the corresponding error message.
    ASPOSE_WORDS_SHARED_API ComparisonEvaluationResult(const System::String& errorMessage);

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::String mField1;

};

}
}
}
