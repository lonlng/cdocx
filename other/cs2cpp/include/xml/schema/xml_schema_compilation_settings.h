/// @file xml/schema/xml_schema_compilation_settings.h

#pragma once

#include <system/object.h>


namespace System {

namespace Xml {

namespace Schema {

/// Provides schema compilation options for the XmlSchemaSet class This class cannot be inherited.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaCompilationSettings final : public System::Object
{
    typedef XmlSchemaCompilationSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaCompilationSettings>;

public:

    /// Returns a value indicating whether the XmlSchemaSet should check for Unique Particle Attribution (UPA) violations.
    /// @returns @c true if the XmlSchemaSet should check for Unique Particle Attribution (UPA) violations;
    /// otherwise, @c false.
    /// The default is @c true.
    ASPOSECPP_SHARED_API bool get_EnableUpaCheck();
    /// Sets a value indicating whether the XmlSchemaSet should check for Unique Particle Attribution (UPA) violations.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_EnableUpaCheck(bool value);

    /// Initializes a new instance of the XmlSchemaCompilationSettings class.
    ASPOSECPP_SHARED_API XmlSchemaCompilationSettings();

private:

    bool _enableUpaCheck;

};

} // namespace Schema
} // namespace Xml
} // namespace System


