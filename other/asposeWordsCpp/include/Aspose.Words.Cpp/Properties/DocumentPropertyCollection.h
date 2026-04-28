//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Properties/DocumentPropertyCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Properties
{

class DocumentProperty;
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
}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Properties {

/// Base class for <see cref="Aspose::Words::Properties::BuiltInDocumentProperties">BuiltInDocumentProperties</see> and <see cref="Aspose::Words::Properties::CustomDocumentProperties">CustomDocumentProperties</see> collections.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-document-properties/">Work with Document Properties</a> documentation article.
/// 
/// The names of the properties are case-insensitive.
/// 
/// The properties in the collection are sorted alphabetically by name.
/// 
/// @sa Aspose::Words::Properties::BuiltInDocumentProperties
/// @sa Aspose::Words::Properties::CustomDocumentProperties
class ASPOSE_WORDS_SHARED_CLASS DocumentPropertyCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Properties::DocumentProperty>>
{
    typedef DocumentPropertyCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Properties::DocumentProperty>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets number of items in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns a <see cref="Aspose::Words::Properties::DocumentProperty">DocumentProperty</see> object by the name of the property.
    /// 
    /// Returns <c>%null</c> if a property with the specified name is not found.
    /// 
    /// @param name The case-insensitive name of the property to retrieve.
    virtual ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::DocumentProperty> idx_get(System::String name);
    /// Returns a <see cref="Aspose::Words::Properties::DocumentProperty">DocumentProperty</see> object by index.
    /// 
    /// @param index Zero-based index of the <see cref="Aspose::Words::Properties::DocumentProperty">DocumentProperty</see> to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Properties::DocumentProperty> idx_get(int32_t index);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Properties::DocumentProperty>>> GetEnumerator() override;
    /// Returns <c>%true</c> if a property with the specified name exists in the collection.
    /// 
    /// @param name The case-insensitive name of the property.
    /// 
    /// @return <c>%true</c> if the property exists in the collection; <c>%false</c> otherwise.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::String& name);
    /// Gets the index of a property by name.
    /// 
    /// @param name The case-insensitive name of the property.
    /// 
    /// @return The zero based index. Negative value if not found.
    ASPOSE_WORDS_SHARED_API int32_t IndexOf(const System::String& name);
    /// Removes a property with the specified name from the collection.
    /// 
    /// @param name The case-insensitive name of the property.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& name);
    /// Removes a property at the specified index.
    /// 
    /// @param index The zero based index.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all properties from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();

protected:

    DocumentPropertyCollection();

    virtual System::SharedPtr<Aspose::Words::Properties::DocumentPropertyCollection> Create() = 0;

    virtual ASPOSE_WORDS_SHARED_API ~DocumentPropertyCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
