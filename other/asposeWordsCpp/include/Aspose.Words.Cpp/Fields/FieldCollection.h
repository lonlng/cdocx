//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldCollection.h
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

namespace Fields
{
class Field;

}
class Node;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// A collection of <see cref="Aspose::Words::Fields::Field">Field</see> objects that represents the fields in the specified range.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// An instance of this collection iterates fields which start fall within the specified range.
/// 
/// The <see cref="Aspose::Words::Fields::FieldCollection">FieldCollection</see> collection does not own the fields it contains, rather, is just a selection of fields.
/// 
/// The <see cref="Aspose::Words::Fields::FieldCollection">FieldCollection</see> collection is "live", i.e. changes to the children of the node object
/// that it was created from are immediately reflected in the fields returned by the <see cref="Aspose::Words::Fields::FieldCollection">FieldCollection</see>
/// properties and methods.
class ASPOSE_WORDS_SHARED_CLASS FieldCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Fields::Field>>
{
    typedef FieldCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Fields::Field>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of the fields in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns a field at the specified index.
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
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> idx_get(int32_t index);

    /// Removes the specified field from this collection and from the document.
    /// 
    /// @param field A field to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::SharedPtr<Aspose::Words::Fields::Field>& field);
    /// Removes a field at the specified index from this collection and from the document.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all fields of this collection from the document and from this collection itself.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Fields::Field>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FieldCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
