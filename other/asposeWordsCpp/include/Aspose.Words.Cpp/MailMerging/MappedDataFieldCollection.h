//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/MailMerging/MappedDataFieldCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/keyvalue_pair.h>
#include <system/collections/ienumerable.h>
#include <system/collections/dictionary.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
}
}
}

namespace Aspose {

namespace Words {

namespace MailMerging {

/// Allows to automatically map between names of fields in your data source
/// and names of mail merge fields in the document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/mail-merge-and-reporting/">Mail Merge and Reporting</a> documentation article.
/// 
/// This is implemented as a collection of string keys into string values.
/// The keys are the names of mail merge fields in the document and the values
/// are the names of fields in your data source.
/// 
/// @sa Aspose::Words::MailMerging::MailMerge
/// @sa Aspose::Words::MailMerging::MailMerge::get_MappedDataFields
class ASPOSE_WORDS_SHARED_CLASS MappedDataFieldCollection : public System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<System::String, System::String>>
{
    typedef MappedDataFieldCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<System::String, System::String>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::Dictionary<System::String, System::String>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or sets the name of the field in the data source associated with the specified mail merge field.
    ASPOSE_WORDS_SHARED_API System::String idx_get(const System::String& documentFieldName);
    /// Gets or sets the name of the field in the data source associated with the specified mail merge field.
    ASPOSE_WORDS_SHARED_API void idx_set(const System::String& documentFieldName, const System::String& value);

    /// Returns a dictionary enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::Collections::Generic::KeyValuePair<System::String, System::String>>> GetEnumerator() override;
    /// Adds a new field mapping.
    /// 
    /// @param documentFieldName Case-sensitive name of the mail merge field in the document.
    /// @param dataSourceFieldName Case-sensitive name of the field in the data source.
    ASPOSE_WORDS_SHARED_API void Add(const System::String& documentFieldName, const System::String& dataSourceFieldName);
    /// Determines whether a mapping from the specified field in the document exists in the collection.
    /// 
    /// @param documentFieldName Case-sensitive name of the mail merge field in the document.
    /// 
    /// @return <c>%true</c> if item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool ContainsKey(const System::String& documentFieldName);
    /// Determines whether a mapping from the specified field in the data source exists in the collection.
    /// 
    /// @param dataSourceFieldName Case-sensitive name of the field in the data source.
    /// 
    /// @return <c>%true</c> if item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool ContainsValue(const System::String& dataSourceFieldName);
    /// Removes a field mapping.
    /// 
    /// @param documentFieldName Case-sensitive name of the mail merge field in the document.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& documentFieldName);
    /// Removes all elements from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();

    ASPOSE_WORDS_SHARED_API iterator begin() noexcept;

    ASPOSE_WORDS_SHARED_API iterator end() noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator begin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator end() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cbegin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cend() const noexcept;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginConstIterator() const override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndConstIterator() const override;

protected:

    MappedDataFieldCollection();

    virtual ASPOSE_WORDS_SHARED_API ~MappedDataFieldCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
