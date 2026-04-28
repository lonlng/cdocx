//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/StructuredDocumentTagCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/NodeMatcher.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Markup
{
class IStructuredDocumentTag;
}
class Node;

}
}
namespace System
{

class String;
}

namespace Aspose {

namespace Words {

namespace Markup {

/// A collection of <see cref="Aspose::Words::Markup::IStructuredDocumentTag">IStructuredDocumentTag</see> instances that represent the structured document tags in the specified range.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS StructuredDocumentTagCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag>>
{
    typedef StructuredDocumentTagCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of structured document tags in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns the structured document tag by identifier.
    /// 
    /// Returns null if the structured document tag with the specified identifier cannot be found.
    /// 
    /// @param id The structured document tag identifier.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag> GetById(int32_t id);
    /// Returns the first structured document tag encountered in the collection with the specified title.
    /// 
    /// Returns null if the structured document tag with the specified title cannot be found.
    /// 
    /// @param title The title of structured document tag.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag> GetByTitle(const System::String& title);
    /// Returns the first structured document tag encountered in the collection with the specified tag.
    /// 
    /// Returns null if the structured document tag with the specified tag cannot be found.
    /// 
    /// @param tag The tag of the structured document tag.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag> GetByTag(const System::String& tag);
    /// Removes the structured document tag with the specified identifier.
    /// 
    /// @param id The structured document tag identifier.
    ASPOSE_WORDS_SHARED_API void Remove(int32_t id);
    /// Removes a structured document tag at the specified index.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);

    /// Returns the structured document tag at the specified index.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag> idx_get(int32_t index);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Markup::IStructuredDocumentTag>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~StructuredDocumentTagCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
