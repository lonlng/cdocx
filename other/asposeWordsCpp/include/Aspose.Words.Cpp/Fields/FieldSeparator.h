//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldSeparator.h
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

/// Represents a Word field separator that separates the field code from the field result.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see> is an inline-level node and represented
/// by the <see cref="Aspose::Words::ControlChar::FieldSeparatorChar">FieldSeparatorChar</see> control character in the document.
/// 
/// <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see> can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// A complete field in a %Microsoft Word document is a complex structure consisting of
/// a field start character, field code, field separator character, field result
/// and field end character. Some fields only have field start, field code and field end.
/// 
/// To easily insert a new field into a document, use the <see cref="Aspose::Words::DocumentBuilder::InsertField(System::String)">InsertField()</see>
/// method.
class ASPOSE_WORDS_SHARED_CLASS FieldSeparator : public Aspose::Words::Fields::FieldChar
{
    typedef FieldSeparator ThisType;
    typedef Aspose::Words::Fields::FieldChar BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::FieldSeparator">FieldSeparator</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitFieldSeparator(System::SharedPtr<Aspose::Words::Fields::FieldSeparator>)">VisitFieldSeparator()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <b>%False</b> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FieldSeparator();

private:

    System::SharedPtr<System::Object> mField0;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
