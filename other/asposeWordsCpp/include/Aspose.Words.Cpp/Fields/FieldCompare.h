//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldCompare.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
class FieldUpdateAction;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the COMPARE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldCompare : public Aspose::Words::Fields::Field
{
    typedef FieldCompare ThisType;
    typedef Aspose::Words::Fields::Field BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

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

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldCompare();

private:

};

}
}
}
