//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Vba/VbaModuleCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Vba
{
class VbaModule;

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

namespace Vba {

/// Represents a collection of <see cref="Aspose::Words::Vba::VbaModule">VbaModule</see> objects.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-vba-macros/">Working with VBA Macros</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS VbaModuleCollection final : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Vba::VbaModule>>
{
    typedef VbaModuleCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Vba::VbaModule>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Vba::VbaModule>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Returns the number of VBA modules in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Adds a module to the collection.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Vba::VbaModule>& vbaModule);

    /// Retrieves a <see cref="Aspose::Words::Vba::VbaModule">VbaModule</see> object by index.
    /// 
    /// @param index Zero-based index of the module to retrieve.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Vba::VbaModule> idx_get(int32_t index);
    /// Retrieves a <see cref="Aspose::Words::Vba::VbaModule">VbaModule</see> object by name, or Null if not found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Vba::VbaModule> idx_get(const System::String& name);

    /// Removes the specified module from the collection.
    /// 
    /// @param module_ The module to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::SharedPtr<Aspose::Words::Vba::VbaModule>& module_);

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

    virtual ASPOSE_WORDS_SHARED_API ~VbaModuleCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::WeakPtr<System::Object> mField2;

    System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Vba::VbaModule>>> GetEnumerator() override;

};

}
}
}
