#pragma once

#include <xml/xml_element.h>
#include <xml/xml_document.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/collections/ilist.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <security/cryptography/xml/key_info_clause.h>
#include <cstdint>

namespace System { namespace Security { namespace Cryptography { namespace Xml { class Signature; } } } }

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the KeyInfo element of an XML digital signature or an XML encryption.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS KeyInfo : public Collections::Generic::IEnumerable<SharedPtr<Xml::KeyInfoClause>>
{
    typedef KeyInfo ThisType;
    typedef IEnumerable<SharedPtr<Xml::KeyInfoClause>> BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class Signature;

public:

    ASPOSECPP_SHARED_API int32_t get_Count();

    ASPOSECPP_SHARED_API KeyInfo();

    ASPOSECPP_SHARED_API void AddClause(SharedPtr<KeyInfoClause> clause);
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<KeyInfoClause>>> GetEnumerator() override;

    /// @copydoc System::Collections::Generic::IEnumerable<SharedPtr<Xml::KeyInfoClause>>::virtualizeBeginIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<Xml::KeyInfoClause>>* virtualizeBeginIterator() override;
    /// @copydoc System::Collections::Generic::IEnumerable<SharedPtr<Xml::KeyInfoClause>>::virtualizeEndIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<Xml::KeyInfoClause>>* virtualizeEndIterator() override;
    /// @copydoc System::Collections::Generic::IEnumerable<SharedPtr<Xml::KeyInfoClause>>::virtualizeBeginConstIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<Xml::KeyInfoClause>>* virtualizeBeginConstIterator() const override;
    /// @copydoc System::Collections::Generic::IEnumerable<SharedPtr<Xml::KeyInfoClause>>::virtualizeEndConstIterator
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<Xml::KeyInfoClause>>* virtualizeEndConstIterator() const override;

protected:

    SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> xmlDocument);
    void LoadXml(SharedPtr<System::Xml::XmlElement> value);

    virtual ASPOSECPP_SHARED_API ~KeyInfo();

#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:

    String _id;
    SharedPtr<Collections::Generic::IList<SharedPtr<KeyInfoClause>>> _keyInfoClauses;

};

}}}} // System::Security::Cryptography::Xml
