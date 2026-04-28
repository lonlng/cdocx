//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldAutoNumLgl.h
#pragma once

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

/// Implements the AUTONUMLGL field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldAutoNumLgl : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldAutoNumLgl ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets whether to display the number without a trailing period.
    ASPOSE_WORDS_SHARED_API bool get_RemoveTrailingPeriod();
    /// Sets whether to display the number without a trailing period.
    ASPOSE_WORDS_SHARED_API void set_RemoveTrailingPeriod(bool value);
    /// Gets the separator character to be used.
    ASPOSE_WORDS_SHARED_API System::String get_SeparatorCharacter();
    /// Sets the separator character to be used.
    ASPOSE_WORDS_SHARED_API void set_SeparatorCharacter(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldAutoNumLgl();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
