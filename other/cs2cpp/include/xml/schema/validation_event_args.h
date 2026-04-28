/// @file xml/schema/validation_event_args.h

#pragma once

#include <xml/schema/xml_severity_type.h>
#include <xml/schema/xml_schema_exception.h>
#include <system/eventargs.h>


/// @cond
namespace System
{
class String;
namespace Xml
{
namespace Schema
{
class BaseProcessor;
class BaseValidator;
class SchemaInfo;
class XdrBuilder;
class XdrValidator;
class XmlSchema;
class XmlSchemaCollection;
class XmlSchemaSet;
class XmlSchemaValidator;
class XsdBuilder;
} // namespace Schema
class XmlValidatingReaderImpl;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Returns detailed information related to the ValidationEventHandler.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ValidationEventArgs : public EventArgs
{
    typedef ValidationEventArgs ThisType;
    typedef EventArgs BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<ValidationEventArgs>;

private:
    /// @cond
    friend class System::Xml::XmlValidatingReaderImpl;
    friend class BaseValidator;
    friend class BaseProcessor;
    friend class SchemaInfo;
    friend class XdrBuilder;
    friend class XdrValidator;
    friend class XmlSchema;
    friend class XmlSchemaCollection;
    friend class XmlSchemaSet;
    friend class XmlSchemaValidator;
    friend class XsdBuilder;
    /// @endcond

public:

    /// Returns the severity of the validation event.
    /// @returns An XmlSeverityType value representing the severity of the validation event.
    ASPOSECPP_SHARED_API XmlSeverityType get_Severity();
    /// Returns the XmlSchemaException associated with the validation event.
    /// @returns The XmlSchemaException associated with the validation event.
    ASPOSECPP_SHARED_API XmlSchemaException get_Exception();
    /// Returns the text description corresponding to the validation event.
    /// @returns The text description.
    ASPOSECPP_SHARED_API String get_Message();

protected:

    /// @cond
    ValidationEventArgs(XmlSchemaException ex);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(ValidationEventArgs, CODEPORTING_ARGS(XmlSchemaException ex));

    ValidationEventArgs(XmlSchemaException ex, XmlSeverityType severity);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(ValidationEventArgs, CODEPORTING_ARGS(XmlSchemaException ex, XmlSeverityType severity));

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
    const char* DBG_class_name() const override { return "ValidationEventArgs"; }
#endif
    /// @endcond

private:

    XmlSchemaException _ex;
    XmlSeverityType _severity;

};

} // namespace Schema
} // namespace Xml
} // namespace System


