//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldEnd.h
#pragma once

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Fields/FieldChar.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class DocumentVisitor;
namespace Fields
{
class Field;

enum class FieldType;
}

class RunPr;

}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents an end of a Word field in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see> is an inline-level node and represented
/// by the <see cref="Aspose::Words::ControlChar::FieldEndChar">FieldEndChar</see> control character in the document.
/// 
/// <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see> can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// A complete field in a %Microsoft Word document is a complex structure consisting of
/// a field start character, field code, field separator character, field result
/// and field end character. Some fields only have field start, field code and field end.
/// 
/// To easily insert a new field into a document, use the <see cref="Aspose::Words::DocumentBuilder::InsertField(System::String)">InsertField()</see>
/// method.
class ASPOSE_WORDS_SHARED_CLASS FieldEnd : public Aspose::Words::Fields::FieldChar
{
    typedef FieldEnd ThisType;
    typedef Aspose::Words::Fields::FieldChar BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::FieldEnd">FieldEnd</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns <c>%true</c> if this field has a separator.
    ASPOSE_WORDS_SHARED_API bool get_HasSeparator() const;

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitFieldEnd(System::SharedPtr<Aspose::Words::Fields::FieldEnd>)">VisitFieldEnd()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <b>%False</b> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FieldEnd();

private:

    __TypeStub<1,1,1,1>::type mField0;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
