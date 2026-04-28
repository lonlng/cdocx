//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldIf.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IMergeFieldSurrogate.h>
#include <Aspose.Words.Cpp/Fields/FieldIfComparisonResult.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/Fields/Expressions/IComparisonExpression.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{

class FieldArgument;

class FieldEnd;

class FieldSeparator;
class FieldStart;
class FieldUpdateAction;
enum class FieldUpdateStrategy;
class IFieldArgument;
}
class INodeModifier;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the IF field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// Compares the values designated by the expressions <see cref="Aspose::Words::Fields::FieldIf::get_LeftExpression">LeftExpression</see> and <see cref="Aspose::Words::Fields::FieldIf::get_RightExpression">RightExpression</see>
/// in comparison using the operator designated by <see cref="Aspose::Words::Fields::FieldIf::get_ComparisonOperator">ComparisonOperator</see>.
/// 
/// A field in the following format will be used as a mail merge source: { IF 0 = 0 "{PatientsNameFML}" "" \\* MERGEFORMAT }
class ASPOSE_WORDS_SHARED_CLASS FieldIf : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IMergeFieldSurrogate
{
    typedef FieldIf ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IMergeFieldSurrogate BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the node that represents the start of the field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() override;
    /// Gets the node that represents the field separator. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldSeparator> get_Separator() override;
    /// Gets the node that represents the field end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() override;
    /// Gets the left part of the comparison expression.
    ASPOSE_WORDS_SHARED_API System::String get_LeftExpression();
    /// Sets the left part of the comparison expression.
    ASPOSE_WORDS_SHARED_API void set_LeftExpression(const System::String& value);
    /// Gets the comparison operator.
    ASPOSE_WORDS_SHARED_API System::String get_ComparisonOperator();
    /// Sets the comparison operator.
    ASPOSE_WORDS_SHARED_API void set_ComparisonOperator(const System::String& value);
    /// Gets the right part of the comparison expression.
    ASPOSE_WORDS_SHARED_API System::String get_RightExpression();
    /// Sets the right part of the comparison expression.
    ASPOSE_WORDS_SHARED_API void set_RightExpression(const System::String& value);
    /// Gets the text displayed if the comparison expression is true.
    ASPOSE_WORDS_SHARED_API System::String get_TrueText();
    /// Sets the text displayed if the comparison expression is true.
    ASPOSE_WORDS_SHARED_API void set_TrueText(const System::String& value);
    /// Gets the text displayed if the comparison expression is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API System::String get_FalseText();
    /// Sets the text displayed if the comparison expression is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_FalseText(const System::String& value);

    /// Evaluates the condition.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::FieldIfComparisonResult">FieldIfComparisonResult</see> value that represents the result of the condition evaluation.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldIfComparisonResult EvaluateCondition();

protected:

    ASPOSE_WORDS_SHARED_API bool get_SupportsConditionalUpdate() override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldUpdateStrategy GetChildFieldsUpdateStrategyInArgument(System::SharedPtr<Aspose::Words::Fields::IFieldArgument> ) override;
    ASPOSE_WORDS_SHARED_API void NotifyChildFieldUpdated(System::SharedPtr<Aspose::Words::Fields::IFieldArgument> ) override;
    ASPOSE_WORDS_SHARED_API void ParseFieldCode() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::INodeModifier> GetResultModifier() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldIf();

private:

    System::SharedPtr<System::Object> mField0;

    System::String GetMergeFieldName() override;
    bool CanWorkAsMergeField() override;
    bool IsMergeValueRequired() override;

private:

};

}
}
}
