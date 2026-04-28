//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/CellCollection.h
#pragma once

#include <Aspose.Words.Cpp/NodeCollection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class CompositeNode;

namespace Tables
{
class Cell;

}
}
}

namespace Aspose {

namespace Words {

namespace Tables {

/// Provides typed access to a collection of <see cref="Aspose::Words::Tables::Cell">Cell</see> nodes.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS CellCollection : public Aspose::Words::NodeCollection
{
    typedef CellCollection ThisType;
    typedef Aspose::Words::NodeCollection BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Retrieves a <see cref="Aspose::Words::Tables::Cell">Cell</see> at the given index.
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
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Cell> idx_get(int32_t index);

    /// Copies all cells from the collection to a new array of cells.
    /// 
    /// @return An array of cells.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<Aspose::Words::Tables::Cell>> ToArray();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~CellCollection();

};

}
}
}
