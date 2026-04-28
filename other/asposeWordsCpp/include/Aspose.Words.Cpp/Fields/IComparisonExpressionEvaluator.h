//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IComparisonExpressionEvaluator.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class ComparisonEvaluationResult;
class ComparisonExpression;
class Field;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IComparisonExpressionEvaluator
/// When implemented, allows to override default comparison expressions evaluation for the <see cref="Aspose::Words::Fields::FieldIf">FieldIf</see> and <see cref="Aspose::Words::Fields::FieldCompare">FieldCompare</see> fields.
/// 
/// @sa Aspose::Words::Fields::FieldOptions::get_ComparisonExpressionEvaluator
class ASPOSE_WORDS_SHARED_CLASS IComparisonExpressionEvaluator : public virtual System::Object
{
    typedef IComparisonExpressionEvaluator ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Evaluates comparison expression.
    virtual System::SharedPtr<Aspose::Words::Fields::ComparisonEvaluationResult> Evaluate(System::SharedPtr<Aspose::Words::Fields::Field> field, System::SharedPtr<Aspose::Words::Fields::ComparisonExpression> expression) = 0;

};

}
}
}
