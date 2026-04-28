//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/PersonCollection.h
#pragma once

#include <system/details/pointer_collection_helpers.h>
#include <system/collections/ienumerable.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Bibliography/Contributor.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Bibliography
{
class Person;
}
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
template <typename> class IList;
}
}
}

namespace Aspose {

namespace Words {

namespace Bibliography {

/// Represents a list of persons who are bibliography source contributors.
class ASPOSE_WORDS_SHARED_CLASS PersonCollection final : public Aspose::Words::Bibliography::Contributor, public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bibliography::Person>>
{
    typedef PersonCollection ThisType;
    typedef Aspose::Words::Bibliography::Contributor BaseType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bibliography::Person>> BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of persons contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Initialize a new instance of the <see cref="Aspose::Words::Bibliography::PersonCollection">PersonCollection</see> class.
    ASPOSE_WORDS_SHARED_API PersonCollection();
    ASPOSE_WORDS_SHARED_API PersonCollection(const System::SharedPtr<System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bibliography::Person>>>& persons);
    /// Initialize a new instance of the <see cref="Aspose::Words::Bibliography::PersonCollection">PersonCollection</see> class.
    ASPOSE_WORDS_SHARED_API PersonCollection(const System::ArrayPtr<System::SharedPtr<Aspose::Words::Bibliography::Person>>& persons);

    /// Adds a <see cref="Aspose::Words::Bibliography::Person">Person</see> to the collection.
    /// 
    /// @param person The person to add to the collection.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Bibliography::Person>& person);
    /// Removes the person from the collection.
    /// 
    /// @param person The person to remove from the collection.
    ASPOSE_WORDS_SHARED_API bool Remove(const System::SharedPtr<Aspose::Words::Bibliography::Person>& person);
    /// Removes the person at the specified index.
    /// 
    /// @param index The zero-based index of the person to remove.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all items from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Determines whether the collection contains a specific person.
    /// 
    /// @param person The person to locate in the collection.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::SharedPtr<Aspose::Words::Bibliography::Person>& person);

    /// Gets or sets a person at the specified index.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Person> idx_get(int32_t index);
    /// Gets or sets a person at the specified index.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, const System::SharedPtr<Aspose::Words::Bibliography::Person>& value);

    ASPOSE_WORDS_SHARED_API void SetTemplateWeakPtr(uint32_t argument) override;

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bibliography::Contributor> Clone() override;

    virtual ASPOSE_WORDS_SHARED_API ~PersonCollection();

private:

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Bibliography::Person>>> GetEnumerator() override;

};

}
}
}
