//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/ComparisonExpression.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// The comparison expression.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ComparisonExpression final : public System::Object
{
    typedef ComparisonExpression ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the left expression.
    ASPOSE_WORDS_SHARED_API System::String get_LeftExpression() const;
    /// Gets the comparison operator.
    ASPOSE_WORDS_SHARED_API System::String get_ComparisonOperator() const;
    /// Gets the right expression.
    ASPOSE_WORDS_SHARED_API System::String get_RightExpression() const;

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;

};

}
}
}
