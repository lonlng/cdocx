//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/FootnoteSeparator.h
#pragma once

#include <system/object_ext.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Story.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Notes/FootnoteSeparatorType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;

class DocumentVisitor;

class Node;

}
}

namespace Aspose {

namespace Words {

namespace Notes {

/// Represents a container for the footnote/endnote separator and continuation content of a document.
/// 
/// <see cref="Aspose::Words::Notes::FootnoteSeparator">FootnoteSeparator</see> can contain <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> child nodes.
/// 
/// There can only be one <see cref="Aspose::Words::Notes::FootnoteSeparator">FootnoteSeparator</see> of each <see cref="Aspose::Words::Notes::FootnoteSeparatorType">FootnoteSeparatorType</see> in a document.
class ASPOSE_WORDS_SHARED_CLASS FootnoteSeparator : public Aspose::Words::Story
{
    typedef FootnoteSeparator ThisType;
    typedef Aspose::Words::Story BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::Story::Equals;

public:

    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    ASPOSE_WORDS_SHARED_API Aspose::Words::Notes::FootnoteSeparatorType get_SeparatorType() const;

    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~FootnoteSeparator();

private:

    __TypeStub<4,4,4,4>::type mField0;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
