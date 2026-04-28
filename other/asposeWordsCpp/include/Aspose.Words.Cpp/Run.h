//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Run.h
#pragma once

#include <Aspose.Words.Cpp/Inline.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class DocumentBase;

class DocumentVisitor;

class PhoneticGuide;

class RunPr;

}
}

namespace Aspose {

namespace Words {

/// Represents a run of characters with the same font formatting.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
/// 
/// All text of the document is stored in runs of text.
/// 
/// <see cref="Aspose::Words::Run">Run</see> can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see> or inline <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see>.
class ASPOSE_WORDS_SHARED_CLASS Run : public Aspose::Words::Inline
{
    typedef Run ThisType;
    typedef Aspose::Words::Inline BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::Run">Run</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets the text of the run.
    ASPOSE_WORDS_SHARED_API System::String get_Text() const;
    /// Sets the text of the run.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);
    /// Gets a boolean value indicating either the run is a phonetic guide.
    ASPOSE_WORDS_SHARED_API bool get_IsPhoneticGuide();
    /// Gets a <see cref="Aspose::Words::Run::get_PhoneticGuide">PhoneticGuide</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::PhoneticGuide> get_PhoneticGuide();

    /// Initializes a new instance of the <see cref="Aspose::Words::Run">Run</see> class.
    /// 
    /// When <see cref="Aspose::Words::Run">Run</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Run">Run</see> to the document use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the paragraph where you want the run inserted.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API Run(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);
    /// Initializes a new instance of the <b>%Run</b> class.
    /// 
    /// When <see cref="Aspose::Words::Run">Run</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Run">Run</see> to the document use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the paragraph where you want the run inserted.
    /// 
    /// @param doc The owner document.
    /// @param text The text of the run.
    ASPOSE_WORDS_SHARED_API Run(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, const System::String& text);

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitRun(System::SharedPtr<Aspose::Words::Run>)">VisitRun()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Gets the text of the run.
    /// 
    /// @return The text of the run.
    ASPOSE_WORDS_SHARED_API System::String GetText() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Run();

private:

    System::String mField0;
    System::SharedPtr<System::Object> mField1;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
