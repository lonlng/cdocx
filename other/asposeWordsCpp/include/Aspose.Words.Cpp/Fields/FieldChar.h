//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldChar.h
#pragma once

#include <Aspose.Words.Cpp/SpecialChar.h>
#include <Aspose.Words.Cpp/Fields/FieldType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;

namespace Fields
{
class Field;

}

class RunPr;

}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Base class for nodes that represent field characters in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// A complete field in a %Microsoft Word document is a complex structure consisting of
/// a field start character, field code, field separator character, field result
/// and field end character. Some fields only have field start, field code and field end.
/// 
/// To easily insert a new field into a document, use the <see cref="Aspose::Words::DocumentBuilder::InsertField(System::String)">InsertField()</see>
/// method.
/// 
/// @sa Aspose::Words::Fields::FieldStart
/// @sa Aspose::Words::Fields::FieldSeparator
/// @sa Aspose::Words::Fields::FieldEnd
class ASPOSE_WORDS_SHARED_CLASS FieldChar : public Aspose::Words::SpecialChar
{
    typedef FieldChar ThisType;
    typedef Aspose::Words::SpecialChar BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the type of the field.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldType get_FieldType() const;
    /// Gets whether the parent field is locked (should not recalculate its result).
    ASPOSE_WORDS_SHARED_API bool get_IsLocked() const;
    /// Sets whether the parent field is locked (should not recalculate its result).
    ASPOSE_WORDS_SHARED_API void set_IsLocked(bool value);
    /// Gets whether the current result of the field is no longer correct (stale) due to other modifications
    /// made to the document.
    ASPOSE_WORDS_SHARED_API bool get_IsDirty() const;
    /// Sets whether the current result of the field is no longer correct (stale) due to other modifications
    /// made to the document.
    ASPOSE_WORDS_SHARED_API void set_IsDirty(bool value);

    /// Returns a field for the field char.
    /// 
    /// @return A field for the field char.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> GetField();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FieldChar();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;

};

}
}
}
