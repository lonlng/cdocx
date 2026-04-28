//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BookmarkEnd.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/IDisplaceableByCustomXml.h>
#include <Aspose.Words.Cpp/IBookmarkNode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class DocumentBase;
class DocumentVisitor;
class Node;

namespace Revisions
{
enum class DisplacedByType;
}

}
}

namespace Aspose {

namespace Words {

/// Represents an end of a bookmark in a Word document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-bookmarks/">Working with Bookmarks</a> documentation article.
/// 
/// A complete bookmark in a Word document consists of a <see cref="Aspose::Words::BookmarkStart">BookmarkStart</see>
/// and a matching <see cref="Aspose::Words::BookmarkEnd">BookmarkEnd</see> with the same bookmark name.
/// 
/// <see cref="Aspose::Words::BookmarkStart">BookmarkStart</see> and <see cref="Aspose::Words::BookmarkEnd">BookmarkEnd</see> are just markers inside a document
/// that specify where the bookmark starts and ends.
/// 
/// Use the <see cref="Aspose::Words::Bookmark">Bookmark</see> class as a "facade" to work with a bookmark
/// as a single object.
class ASPOSE_WORDS_SHARED_CLASS BookmarkEnd : public Aspose::Words::Node, public Aspose::Words::IBookmarkNode, public Aspose::Words::IDisplaceableByCustomXml
{
    typedef BookmarkEnd ThisType;
    typedef Aspose::Words::Node BaseType;
    typedef Aspose::Words::IBookmarkNode BaseType1;
    typedef Aspose::Words::IDisplaceableByCustomXml BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::BookmarkEnd">BookmarkEnd</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets the bookmark name.
    /// 
    /// Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Name() override;
    /// Sets the bookmark name.
    /// 
    /// Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Name(System::String value) override;

    /// Initializes a new instance of the <see cref="Aspose::Words::BookmarkEnd">BookmarkEnd</see> class.
    /// 
    /// @param doc The owner document.
    /// @param name The name of the bookmark. Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API BookmarkEnd(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, const System::String& name);

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitBookmarkEnd(System::SharedPtr<Aspose::Words::BookmarkEnd>)">VisitBookmarkEnd()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~BookmarkEnd();

private:

    Aspose::Words::Revisions::DisplacedByType get_DisplacedByCustomXml() override;
    void set_DisplacedByCustomXml(Aspose::Words::Revisions::DisplacedByType ) override;

    System::String mField0;
    __TypeStub<4,4,4,4>::type mField1;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
