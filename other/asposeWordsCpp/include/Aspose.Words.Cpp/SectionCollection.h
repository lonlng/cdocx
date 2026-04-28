//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SectionCollection.h
#pragma once

#include <Aspose.Words.Cpp/NodeCollection.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class CompositeNode;

class Section;
}
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::Section">Section</see> objects in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-sections/">Working with Sections</a> documentation article.
/// 
/// A %Microsoft Word document can contain multiple sections. To create a section in a %Microsoft Word,
/// select the Insert/Break command and select a break type. The break specifies whether section starts
/// on a new page or on the same page.
/// 
/// Programmatically inserting and removing sections can be used to customize documents produced
/// during mail merge. If a document needs to have different content or parts of the
/// content depending on some criteria, then you can create a "master" document that contains
/// multiple sections and delete some of the sections before or after mail merge.
class ASPOSE_WORDS_SHARED_CLASS SectionCollection : public Aspose::Words::NodeCollection
{
    typedef SectionCollection ThisType;
    typedef Aspose::Words::NodeCollection BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Retrieves a section at the given index.
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
    /// @param index An index into the list of sections.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> idx_get(int32_t index);

    /// Copies all sections from the collection to a new array of sections.
    /// 
    /// @return An array of sections.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<Aspose::Words::Section>> ToArray();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~SectionCollection();

};

}
}
