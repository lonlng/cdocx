/// @file xml/schema/xml_schema_object.h

#pragma once

#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class Compiler;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchema;
class XmlSchemaAnnotation;
class XmlSchemaComplexType;
class XmlSchemaObjectCollection;
class XmlSchemaSimpleType;
class XsdBuilder;
} // namespace Schema
namespace Serialization
{
class XmlSerializerNamespaces;
} // namespace Serialization
class XmlAttribute;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the root class for the Xml schema object model hierarchy and serves as a base class for classes such as the XmlSchema class.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaObject : public System::Object
{
    typedef XmlSchemaObject ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaObject>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchema;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaObjectCollection;
    friend class XmlSchemaSimpleType;
    friend class XsdBuilder;
    /// @endcond

public:

    /// Returns the line number in the file to which the @c schema element refers.
    /// @returns The line number.
    ASPOSECPP_SHARED_API int32_t get_LineNumber();
    /// Sets the line number in the file to which the @c schema element refers.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_LineNumber(int32_t value);
    /// Returns the line position in the file to which the @c schema element refers.
    /// @returns The line position.
    ASPOSECPP_SHARED_API int32_t get_LinePosition();
    /// Sets the line position in the file to which the @c schema element refers.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_LinePosition(int32_t value);
    /// Returns the source location for the file that loaded the schema.
    /// @returns The source location (URI) for the file.
    ASPOSECPP_SHARED_API String get_SourceUri();
    /// Sets the source location for the file that loaded the schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SourceUri(const String& value);
    /// Returns the parent of this XmlSchemaObject.
    /// @returns The parent XmlSchemaObject of this XmlSchemaObject.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> get_Parent();
    /// Sets the parent of this XmlSchemaObject.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Parent(const SharedPtr<XmlSchemaObject>& value);
    /// Returns the XmlSerializerNamespaces to use with this schema object.
    /// @returns The XmlSerializerNamespaces instance for the schema object.
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::Serialization::XmlSerializerNamespaces> get_Namespaces();
    /// Sets the XmlSerializerNamespaces to use with this schema object.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Namespaces(const SharedPtr<System::Xml::Serialization::XmlSerializerNamespaces>& value);

    /// Initializes a new instance of the XmlSchemaObject class.
    ASPOSECPP_SHARED_API XmlSchemaObject();

protected:

    /// @cond
    virtual ASPOSECPP_SHARED_API String get_IdAttribute();
    virtual ASPOSECPP_SHARED_API void set_IdAttribute(String value);
    virtual ASPOSECPP_SHARED_API String get_NameAttribute();
    virtual ASPOSECPP_SHARED_API void set_NameAttribute(String value);
    bool get_IsProcessing();
    void set_IsProcessing(bool value);

    virtual ASPOSECPP_SHARED_API void OnAdd(SharedPtr<XmlSchemaObjectCollection> container, SharedPtr<Object> item);
    virtual ASPOSECPP_SHARED_API void OnRemove(SharedPtr<XmlSchemaObjectCollection> container, SharedPtr<Object> item);
    virtual ASPOSECPP_SHARED_API void OnClear(SharedPtr<XmlSchemaObjectCollection> container);
    virtual ASPOSECPP_SHARED_API void SetUnhandledAttributes(ArrayPtr<SharedPtr<XmlAttribute>> moreAttributes);
    virtual ASPOSECPP_SHARED_API void AddAnnotation(SharedPtr<XmlSchemaAnnotation> annotation);
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone();

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
    const char* DBG_class_name() const override { return "XmlSchemaObject"; }
#endif
    /// @endcond

private:

    int32_t _lineNum;
    int32_t _linePos;
    String _sourceUri;
    SharedPtr<System::Xml::Serialization::XmlSerializerNamespaces> _namespaces;
    WeakPtr<XmlSchemaObject> _parent;
    bool _isProcessing;

    virtual ThisType* CppMemberwiseClone() const = 0;

};

} // namespace Schema
} // namespace Xml
} // namespace System


