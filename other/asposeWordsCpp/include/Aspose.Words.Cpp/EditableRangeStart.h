//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/EditableRangeStart.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Model/Text/INodeWithCommentId.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/IDisplaceableByCustomXml.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;

class DocumentVisitor;
class EditableRange;

class Node;
namespace Revisions
{
enum class DisplacedByType;
}

}
}

namespace Aspose {

namespace Words {

/// Represents a start of an editable range in a Word document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// A complete editable range in a Word document consists of a <see cref="Aspose::Words::EditableRangeStart">EditableRangeStart</see>
/// and a matching <see cref="Aspose::Words::EditableRangeEnd">EditableRangeEnd</see> with the same Id.
/// 
/// <see cref="Aspose::Words::EditableRangeStart">EditableRangeStart</see> and <see cref="Aspose::Words::EditableRangeEnd">EditableRangeEnd</see> are just markers inside a document
/// that specify where the editable range starts and ends.
/// 
/// Use the <see cref="Aspose::Words::EditableRangeStart::get_EditableRange">EditableRange</see> class as a "facade" to work with an editable range
/// as a single object.
/// 
/// @note Currently editable ranges are supported only at the inline-level, that is inside <see cref="Aspose::Words::Paragraph">Paragraph</see>,
/// but editable range start and editable range end can be in different paragraphs.
class ASPOSE_WORDS_SHARED_CLASS EditableRangeStart final : public Aspose::Words::Node, public Aspose::Words::IDisplaceableByCustomXml, public Aspose::Words::INodeWithAnnotationId
{
    typedef EditableRangeStart ThisType;
    typedef Aspose::Words::Node BaseType;
    typedef Aspose::Words::IDisplaceableByCustomXml BaseType1;
    typedef Aspose::Words::INodeWithAnnotationId BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the identifier of the editable range.
    ASPOSE_WORDS_SHARED_API int32_t get_Id() const;
    /// Specifies the identifier of the editable range.
    ASPOSE_WORDS_SHARED_API void set_Id(int32_t value);
    /// Gets the facade object that encapsulates this editable range start and end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::EditableRange> get_EditableRange();
    /// Returns <see cref="Aspose::Words::NodeType::EditableRangeStart">EditableRangeStart</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitEditableRangeStart(System::SharedPtr<Aspose::Words::EditableRangeStart>)">VisitEditableRangeStart()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~EditableRangeStart();

private:

    Aspose::Words::Revisions::DisplacedByType get_DisplacedByCustomXml() override;
    void set_DisplacedByCustomXml(Aspose::Words::Revisions::DisplacedByType ) override;
    int32_t get_IdInternal() override;
    void set_IdInternal(int32_t ) override;
    int32_t get_ParentIdInternal() override;
    void set_ParentIdInternal(int32_t ) override;

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::String mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
