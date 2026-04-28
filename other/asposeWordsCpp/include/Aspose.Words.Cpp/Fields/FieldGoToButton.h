//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldGoToButton.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
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

/// Implements the GOTOBUTTON field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldGoToButton : public Aspose::Words::Fields::Field
{
    typedef FieldGoToButton ThisType;
    typedef Aspose::Words::Fields::Field BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of a bookmark, a page number, or some other item to jump to.
    ASPOSE_WORDS_SHARED_API System::String get_Location();
    /// Sets the name of a bookmark, a page number, or some other item to jump to.
    ASPOSE_WORDS_SHARED_API void set_Location(const System::String& value);
    /// Gets the text of the "button" that appears in the document, such that it can be selected to activate the jump.
    ASPOSE_WORDS_SHARED_API System::String get_DisplayText();
    /// Sets the text of the "button" that appears in the document, such that it can be selected to activate the jump.
    ASPOSE_WORDS_SHARED_API void set_DisplayText(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

private:

};

}
}
}
