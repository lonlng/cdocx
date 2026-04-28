//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldFormat.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/NumberStyle.h>
#include <Aspose.Words.Cpp/Lists/ListLabelUtil.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Fields
{

class GeneralFormatCollection;

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

/// Provides typed access to field's numeric, date and time, and general formatting.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldFormat : public System::Object
{
    typedef FieldFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets a formatting that is applied to a numeric field result. Corresponds to the \\\# switch.
    ASPOSE_WORDS_SHARED_API System::String get_NumericFormat();
    /// Sets a formatting that is applied to a numeric field result. Corresponds to the \\\# switch.
    ASPOSE_WORDS_SHARED_API void set_NumericFormat(const System::String& value);
    /// Gets a formatting that is applied to a date and time field result. Corresponds to the \\\@ switch.
    ASPOSE_WORDS_SHARED_API System::String get_DateTimeFormat();
    /// Sets a formatting that is applied to a date and time field result. Corresponds to the \\\@ switch.
    ASPOSE_WORDS_SHARED_API void set_DateTimeFormat(const System::String& value);
    /// Gets a collection of general formats that are applied to a numeric, text or any field result.
    /// Corresponds to the \\* switches.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::GeneralFormatCollection> get_GeneralFormats();

protected:

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
