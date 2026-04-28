//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/CommentCollection.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/NodeMatcher.h>
#include <Aspose.Words.Cpp/NodeCollection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Comment;
class DocumentBase;
class Node;
class NodeCollection;
}
}

namespace Aspose {

namespace Words {

/// Provides typed access to a collection of <see cref="Aspose::Words::Comment">Comment</see> nodes.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-comments/">Working with Comments</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS CommentCollection : public Aspose::Words::NodeCollection
{
    typedef CommentCollection ThisType;
    typedef Aspose::Words::NodeCollection BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Retrieves a <see cref="Aspose::Words::Comment">Comment</see> at the given index.
    /// 
    /// The index is zero-based.
    /// 
    /// Negative indexes are allowed and indicate access from the back of the collection.
    /// For example -1 means the last item, -2 means the second before last and so on.
    /// 
    /// If index is greater than or equal to the number of items in the list, this returns a null reference.
    /// 
    /// If index is negative and its absolute value is greater than the number of items in the list, this returns a null reference.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Comment> idx_get(int32_t index);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~CommentCollection();

};

}
}
