/// @file xml/schema/xml_schema_object_table.h

#pragma once

#include <xml/xml_qualified_name.h>
#include <xml/schema/xml_schema_object.h>
#include <system/shared_ptr.h>
#include <system/collections/keyvalue_pair.h>
#include <system/collections/ienumerable.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
template <typename> class ICollection;
template <typename> class IEnumerator;
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace Xml
{
namespace Schema
{
class BaseProcessor;
class Compiler;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchema;
class XmlSchemaAttributeGroup;
class XmlSchemaComplexType;
class XmlSchemaObjectEntry;
class XmlSchemaRedefine;
class XmlSchemaSet;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Provides the collections for contained elements in the XmlSchema class (for example, Attributes, AttributeGroups, Elements, and so on).
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaObjectTable : public Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<SharedPtr<System::Xml::XmlQualifiedName>, SharedPtr<System::Xml::Schema::XmlSchemaObject>>>
{
    typedef XmlSchemaObjectTable ThisType;
    typedef Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<SharedPtr<System::Xml::XmlQualifiedName>, SharedPtr<System::Xml::Schema::XmlSchemaObject>>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaObjectTable>;

private:
    /// @cond
    friend class BaseProcessor;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchema;
    friend class XmlSchemaAttributeGroup;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaRedefine;
    friend class XmlSchemaSet;
    /// @endcond

public:

    /// Returns the number of items contained in the XmlSchemaObjectTable.
    /// @returns The number of items contained in the XmlSchemaObjectTable.
    ASPOSECPP_SHARED_API int32_t get_Count();
    /// Returns a collection of all the named elements in the XmlSchemaObjectTable.
    /// @returns A collection of all the named elements in the XmlSchemaObjectTable.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::ICollection<SharedPtr<XmlQualifiedName>>> get_Names();
    /// Returns a collection of all the values for all the elements in the XmlSchemaObjectTable.
    /// @returns A collection of all the values for all the elements in the XmlSchemaObjectTable.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::ICollection<SharedPtr<XmlSchemaObject>>> get_Values();

    /// Determines if the qualified name specified exists in the collection.
    /// @param name The XmlQualifiedName.
    /// @returns @c true if the qualified name specified exists in the collection; otherwise, @c false.
    ASPOSECPP_SHARED_API bool Contains(const SharedPtr<XmlQualifiedName>& name);

    /// Returns the element in the XmlSchemaObjectTable specified by qualified name.
    /// @param name The XmlQualifiedName of the element to return.
    /// @returns The XmlSchemaObject of the element in the XmlSchemaObjectTable specified by qualified name.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> idx_get(const SharedPtr<XmlQualifiedName>& name);

    /// Returns an enumerator that can iterate through the XmlSchemaObjectTable.
    /// @returns An Collections::IDictionaryEnumerator that can iterate through XmlSchemaObjectTable.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<Collections::Generic::KeyValuePair<SharedPtr<XmlQualifiedName>, SharedPtr<XmlSchemaObject>>>> GetEnumerator() override;

protected:

    /// @cond
    XmlSchemaObjectTable();
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlSchemaObjectTable, CODEPORTING_ARGS());

    void Add(const SharedPtr<XmlQualifiedName>& name, const SharedPtr<XmlSchemaObject>& value);
    void Insert(const SharedPtr<XmlQualifiedName>& name, const SharedPtr<XmlSchemaObject>& value);
    void Replace(const SharedPtr<XmlQualifiedName>& name, const SharedPtr<XmlSchemaObject>& value);
    void Clear();
    void Remove(const SharedPtr<XmlQualifiedName>& name);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaObjectTable();

    /// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlSchemaObjectTable"; }
#endif
    /// @endcond

private:

    SharedPtr<Collections::Generic::Dictionary<SharedPtr<XmlQualifiedName>, SharedPtr<XmlSchemaObject>>> _table;
    SharedPtr<Collections::Generic::List<XmlSchemaObjectEntry>> _entries;

    int32_t FindIndexByValue(const SharedPtr<XmlSchemaObject>& xso);

};

} // namespace Schema
} // namespace Xml
} // namespace System


