//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Story.h
#pragma once

#include <Aspose.Words.Cpp/StoryType.h>
#include <Aspose.Words.Cpp/IStory.h>
#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class CompositeNode;

class DocumentBase;

class INodeCloningListener;

class Node;

class Paragraph;
class ParagraphCollection;

namespace Tables
{
class TableCollection;
}

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// Base class for elements that contain block-level nodes <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/logical-levels-of-nodes-in-a-document/">Logical Levels of Nodes in a Document</a> documentation article.
/// 
/// Text of a Word document is said to consist of several stories.
/// The main text is stored in the main text story represented by <see cref="Aspose::Words::Body">Body</see>,
/// each header and footer is stored in a separate story represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
class ASPOSE_WORDS_SHARED_CLASS Story : public Aspose::Words::CompositeNode, public Aspose::Words::IStory
{
    typedef Story ThisType;
    typedef Aspose::Words::CompositeNode BaseType;
    typedef Aspose::Words::IStory BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Gets the type of this story.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StoryType get_StoryType() override;
    /// Gets the first paragraph in the story.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Paragraph> get_FirstParagraph() override;
    /// Gets the last paragraph in the story.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Paragraph> get_LastParagraph() override;
    /// Gets a collection of paragraphs that are immediate children of the story.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ParagraphCollection> get_Paragraphs() override;
    /// Gets a collection of tables that are immediate children of the story.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::TableCollection> get_Tables() override;

    /// Deletes all shapes from the text of this story.
    ASPOSE_WORDS_SHARED_API void DeleteShapes();
    /// A shortcut method that creates a <see cref="Aspose::Words::Paragraph">Paragraph</see> object with optional text and appends it to the end of this object.
    /// 
    /// @param text The text for the paragraph. Can be <c>%null</c> or empty string.
    /// 
    /// @return The newly created and appended paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Paragraph> AppendParagraph(const System::String& text);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Story();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
