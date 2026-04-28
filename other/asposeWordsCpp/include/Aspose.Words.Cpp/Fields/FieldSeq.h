//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldSeq.h
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

/// Implements the SEQ field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldSeq : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldSeq ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name assigned to the series of items that are to be numbered.
    ASPOSE_WORDS_SHARED_API System::String get_SequenceIdentifier();
    /// Sets the name assigned to the series of items that are to be numbered.
    ASPOSE_WORDS_SHARED_API void set_SequenceIdentifier(const System::String& value);
    /// Gets a bookmark name that refers to an item elsewhere in the document rather than in the current location.
    ASPOSE_WORDS_SHARED_API System::String get_BookmarkName();
    /// Sets a bookmark name that refers to an item elsewhere in the document rather than in the current location.
    ASPOSE_WORDS_SHARED_API void set_BookmarkName(const System::String& value);
    /// Gets whether to insert the next sequence number for the specified item.
    ASPOSE_WORDS_SHARED_API bool get_InsertNextNumber();
    /// Sets whether to insert the next sequence number for the specified item.
    ASPOSE_WORDS_SHARED_API void set_InsertNextNumber(bool value);
    /// Gets an integer number to reset the sequence number to. Returns -1 if the number is absent.
    ASPOSE_WORDS_SHARED_API System::String get_ResetNumber();
    /// Sets an integer number to reset the sequence number to. Returns -1 if the number is absent.
    ASPOSE_WORDS_SHARED_API void set_ResetNumber(const System::String& value);
    /// Gets an integer number representing a heading level to reset the sequence number to.
    /// Returns -1 if the number is absent.
    ASPOSE_WORDS_SHARED_API System::String get_ResetHeadingLevel();
    /// Sets an integer number representing a heading level to reset the sequence number to.
    /// Returns -1 if the number is absent.
    ASPOSE_WORDS_SHARED_API void set_ResetHeadingLevel(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldSeq();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
