//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/CustomXmlPropertyCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Markup
{
class CustomXmlProperty;

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

namespace Markup {

/// Represents a collection of custom XML attributes or smart tag properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// Items are <see cref="Aspose::Words::Markup::CustomXmlProperty">CustomXmlProperty</see> objects.
class ASPOSE_WORDS_SHARED_CLASS CustomXmlPropertyCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::CustomXmlProperty>>
{
    typedef CustomXmlPropertyCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::CustomXmlProperty>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets a property with the specified name.
    /// 
    /// @param name Case-sensitive name of the property to locate.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlProperty> idx_get(const System::String& name);
    /// Gets a property at the specified index.
    /// 
    /// @param index Zero-based index of the property.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlProperty> idx_get(int32_t index);

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Markup::CustomXmlProperty>>> GetEnumerator() override;
    /// Adds a property to the collection.
    /// 
    /// @param property The property to add.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Markup::CustomXmlProperty>& property);
    /// Determines whether the collection contains a property with the given name.
    /// 
    /// @param name Case-sensitive name of the property to locate.
    /// 
    /// @return <c>%true</c> if the item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::String& name);
    /// Returns the zero-based index of the specified property in the collection.
    /// 
    /// @param name The case-sensitive name of the property.
    /// 
    /// @return The zero based index. Negative value if not found.
    ASPOSE_WORDS_SHARED_API int32_t IndexOfKey(const System::String& name);
    /// Removes a property with the specified name from the collection.
    /// 
    /// @param name The case-sensitive name of the property.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& name);
    /// Removes a property at the specified index.
    /// 
    /// @param index The zero based index.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all elements from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();

protected:

    CustomXmlPropertyCollection();

    virtual ASPOSE_WORDS_SHARED_API ~CustomXmlPropertyCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
