/// @file xml/schema/xml_schema_external.h

#pragma once

#include <xml/schema/xml_schema_object.h>
#include <system/array.h>


/// @cond
namespace System
{
class Uri;
namespace Xml
{
namespace Schema
{
enum class Compositor;
class Preprocessor;
class SchemaCollectionPreprocessor;
class XmlSchema;
} // namespace Schema
class XmlAttribute;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Provides information about the included schema.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaExternal : public XmlSchemaObject
{
    typedef XmlSchemaExternal ThisType;
    typedef XmlSchemaObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaExternal>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionPreprocessor;
    /// @endcond

public:

    /// Returns the Uniform Resource Identifier (URI) location for the schema,
    /// which tells the schema processor where the schema physically resides.
    /// @returns The URI location for the schema. Optional for imported schemas.
    ASPOSECPP_SHARED_API String get_SchemaLocation();
    /// Sets the Uniform Resource Identifier (URI) location for the schema,
    /// which tells the schema processor where the schema physically resides.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaLocation(const String& value);
    /// Returns the XmlSchema for the referenced schema.
    /// @returns The XmlSchema for the referenced schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> get_Schema();
    /// Sets the XmlSchema for the referenced schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Schema(const SharedPtr<XmlSchema>& value);
    /// Returns the string id.
    /// @returns The string id. The default is String::Empty. Optional.
    ASPOSECPP_SHARED_API String get_Id();
    /// Sets the string id.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Id(const String& value);
    /// Returns the qualified attributes, which do not belong to the schema target namespace.
    /// @returns Qualified attributes that belong to another target namespace.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlAttribute>> get_UnhandledAttributes();
    /// Sets the qualified attributes, which do not belong to the schema target namespace.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_UnhandledAttributes(const ArrayPtr<SharedPtr<XmlAttribute>>& value);

    /// Initializes a new instance of the XmlSchemaExternal class.
    ASPOSECPP_SHARED_API XmlSchemaExternal();

protected:

    /// @cond
    SharedPtr<Uri> get_BaseUri();
    void set_BaseUri(const SharedPtr<Uri>& value);
    ASPOSECPP_SHARED_API String get_IdAttribute() override;
    ASPOSECPP_SHARED_API void set_IdAttribute(String value) override;
    System::Xml::Schema::Compositor get_Compositor();
    void set_Compositor(System::Xml::Schema::Compositor value);

    ASPOSECPP_SHARED_API void SetUnhandledAttributes(ArrayPtr<SharedPtr<XmlAttribute>> moreAttributes) override;

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
    const char* DBG_class_name() const override { return "XmlSchemaExternal"; }
#endif
    /// @endcond

private:

    String _location;
    SharedPtr<Uri> _baseUri;
    WeakPtr<XmlSchema> _schema;
    String _id;
    ArrayPtr<SharedPtr<XmlAttribute>> _moreAttributes;
    System::Xml::Schema::Compositor _compositor;

};

} // namespace Schema
} // namespace Xml
} // namespace System


