//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldInfo.h
#pragma once

#include <system/shared_ptr.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/IFieldCode.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{

enum class FieldSwitchType;
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

/// Implements the INFO field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldInfo : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldInfo ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the type of the document property to insert.
    ASPOSE_WORDS_SHARED_API System::String get_InfoType();
    /// Sets the type of the document property to insert.
    ASPOSE_WORDS_SHARED_API void set_InfoType(const System::String& value);
    /// Gets an optional value that updates the property.
    ASPOSE_WORDS_SHARED_API System::String get_NewValue();
    /// Sets an optional value that updates the property.
    ASPOSE_WORDS_SHARED_API void set_NewValue(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldInfo();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
