/// @file security/cryptography/x509_certificates/x509_extension_collection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/list.h>
#include <system/collections/base_enumerator.h>
#include <system/collections/ienumerable.h>
#include <system/collections/icollection.h>

#include <security/cryptography/x509_certificates/x509_extension.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Collection of extension objects.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509ExtensionCollection final
    : public System::Collections::Generic::List<SharedPtr<X509Extension> >
{
    /// This type.
    typedef X509ExtensionCollection ThisType;
    /// Parent type.
    typedef System::Collections::Generic::List<SharedPtr<X509Extension> > BaseType;
    /// RTTI data.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    using BaseType::idx_get;

    /// Constructs empty collection.
    X509ExtensionCollection() = default;

    /// Accessor. Not implemented.
    /// @param key Key to get extension at. 
    /// @return Extension at specified key.
    ASPOSECPP_SHARED_API SharedPtr<X509Extension> idx_get(const String& key) const;

protected:
    ASPOSECPP_SHARED_API ~X509ExtensionCollection() override;
};

/// Enumerator to iterate through extension collection.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509ExtensionEnumerator final
    : public System::Collections::Generic::SimpleEnumerator<X509ExtensionCollection::vector_t>
{
public:
    /// Creates enumerator.
    /// @param collection Collection to iterate through.
    X509ExtensionEnumerator(const SharedPtr<X509ExtensionCollection>& collection)
        : SimpleEnumerator<X509ExtensionCollection::vector_t>(collection, collection->data())
    {}

    /// This type.
    typedef X509ExtensionEnumerator ThisType;
    /// Parent type.
    typedef System::Collections::Generic::IEnumerator<SharedPtr<X509Extension> > BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();
};

/// Pointer to collection of X509 extensions.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
class ASPOSECPP_SHARED_CLASS X509ExtensionCollectionPtr : public SharedPtr<X509ExtensionCollection>
{
public:
    /// Null pointer constructor.
    X509ExtensionCollectionPtr() = default;
    /// Constructor.
    /// @param obj Certificate collection to point to.
    X509ExtensionCollectionPtr(const SharedPtr<X509ExtensionCollection>& obj)
        : SharedPtr<X509ExtensionCollection>(obj)
    { }

    /// Accessor.
    /// @param idx Index of certificate to get.
    /// @return Certificate at specified position.
    SharedPtr<X509Extension>& operator[] (int32_t idx) const
    {
        return (*(this->GetPointer()))[idx];
    }

    bool IsNull() const
    {
        return this->GetPointer() == nullptr;
    }
};

}}}} // namespace System::Security::Cryptography::X509Certificates
