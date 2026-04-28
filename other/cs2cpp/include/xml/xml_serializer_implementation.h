/// @file xml/xml_serializer_implementation.h
#pragma once

#include <xml/xml_serializer.h>
#include <xml/xml_serialization_writer.h>
#include <xml/xml_serialization_reader.h>
#include <system/type_info.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/collections/dictionary.h>

namespace System {

namespace Xml {

namespace Serialization {

/// Internal class to use with XmlSerializer.
class ASPOSECPP_SHARED_CLASS  XmlSerializerImplementation : public System::Object
{
public:

    ASPOSECPP_SHARED_API virtual System::SharedPtr<XmlSerializationReader> get_Reader()
    {
        throw NotSupportedException();
    }

    ASPOSECPP_SHARED_API virtual System::SharedPtr<XmlSerializationWriter> get_Writer()
    {
        throw NotSupportedException();
    }

    ASPOSECPP_SHARED_API virtual System::SharedPtr<Collections::Generic::Dictionary<String, String>> get_ReadMethods()
    {
        throw NotSupportedException();
    }

    ASPOSECPP_SHARED_API virtual System::SharedPtr<Collections::Generic::Dictionary<String, String>> get_WriteMethods()
    {
        throw NotSupportedException();
    }

    ASPOSECPP_SHARED_API virtual System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<XmlSerializer>>> get_TypedSerializers()
    {
        throw NotSupportedException();
    }

    ASPOSECPP_SHARED_API virtual bool CanSerialize(const TypeInfo& type)
    {
        ASPOSE_UNUSED(type);
        throw NotSupportedException();
    }

    ASPOSECPP_SHARED_API virtual System::SharedPtr<XmlSerializer> GetSerializer(const TypeInfo& type)
    {
        ASPOSE_UNUSED(type);
        throw NotSupportedException();
    }
};

} // namespace Serialization
} // namespace Xml
} // namespace System


