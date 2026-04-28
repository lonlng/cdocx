//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldStart.h
#pragma once

#include <system/array.h>
#include <cstdint>

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

enum class FieldType;

}
class RunPr;

}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents a start of a Word field in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see> is an inline-level node and represented by the
/// <see cref="Aspose::Words::ControlChar::FieldStartChar">FieldStartChar</see> control character in the document.
/// 
/// <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see> can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// A complete field in a %Microsoft Word document is a complex structure consisting of
/// a field start character, field code, field separator character, field result
/// and field end character. Some fields only have field start, field code and field end.
/// 
/// To easily insert a new field into a document, use the <see cref="Aspose::Words::DocumentBuilder::InsertField(System::String)">InsertField()</see>
/// method.
class ASPOSE_WORDS_SHARED_CLASS FieldStart : public Aspose::Words::Fields::FieldChar
{
    typedef FieldStart ThisType;
    typedef Aspose::Words::Fields::FieldChar BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::FieldStart">FieldStart</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets custom field data which is associated with the field.
    ASPOSE_WORDS_SHARED_API const System::ArrayPtr<uint8_t>& get_FieldData() const;

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitFieldStart(System::SharedPtr<Aspose::Words::Fields::FieldStart>)">VisitFieldStart()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <b>%False</b> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FieldStart();

private:

    System::SharedPtr<System::Object> mField0;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
