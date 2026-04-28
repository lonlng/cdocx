//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FormFieldCollection.h
#pragma once

#include <system/shared_ptr.h>
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
class FormField;
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
template <typename> class IEnumerator;

}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// A collection of <see cref="Aspose::Words::Fields::FormField">FormField</see> objects that represent all the form fields in a range.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-form-fields/">Working with Form Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FormFieldCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Fields::FormField>>
{
    typedef FormFieldCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Fields::FormField>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of form fields in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns a form field at the specified index.
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
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FormField> idx_get(int32_t index);
    /// Returns a form field by bookmark name.
    /// 
    /// @param bookmarkName Case-insensitive bookmark name.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FormField> idx_get(const System::String& bookmarkName);

    /// Removes a form field with the specified name.
    /// 
    /// @param formField The case-insensitive name of the form field to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& formField);
    /// Removes a form field at the specified index.
    /// 
    /// @param index The zero-based index of the form field to remove.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all form fields from this collection and from the document.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Fields::FormField>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~FormFieldCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
