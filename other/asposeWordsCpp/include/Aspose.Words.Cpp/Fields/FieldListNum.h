//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldListNum.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{

enum class FieldSwitchType;
}
class Node;
class NodeRange;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the LISTNUM field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldListNum : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldListNum ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the abstract numbering definition used for the numbering.
    ASPOSE_WORDS_SHARED_API System::String get_ListName();
    /// Sets the name of the abstract numbering definition used for the numbering.
    ASPOSE_WORDS_SHARED_API void set_ListName(const System::String& value);
    /// Returns a value indicating whether the name of an abstract numbering definition
    /// is provided by the field's code.
    ASPOSE_WORDS_SHARED_API bool get_HasListName();
    /// Gets the level in the list, overriding the default behavior of the field.
    ASPOSE_WORDS_SHARED_API System::String get_ListLevel();
    /// Sets the level in the list, overriding the default behavior of the field.
    ASPOSE_WORDS_SHARED_API void set_ListLevel(const System::String& value);
    /// Gets the starting value for this field.
    ASPOSE_WORDS_SHARED_API System::String get_StartingNumber();
    /// Sets the starting value for this field.
    ASPOSE_WORDS_SHARED_API void set_StartingNumber(const System::String& value);

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Remove() override;

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldListNum();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
