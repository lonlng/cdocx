/// @file net/http/headers/entity_tag_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Entity-Tag' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS EntityTagHeaderValue : public System::ICloneable
{
    /// This type.
    typedef EntityTagHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a string representation of an EntityTagHeaderValue-class instance.
    /// @returns A string representation of an EntityTagHeaderValue-class instance.
    ASPOSECPP_SHARED_API String get_Tag();
    /// Gets a value that indicates if the current instance is a weak validator.
    /// @returns A value that indicates if the current instance is a weak validator.
    ASPOSECPP_SHARED_API bool get_IsWeak();
    /// Gets a value of the 'ETag' header.
    /// @returns A value of the 'ETag' header.
    ASPOSECPP_SHARED_API static System::SharedPtr<EntityTagHeaderValue> get_Any();

    /// Constructs a new instance.
    /// @param tag A string representation of an EntityTagHeaderValue-class instance.
    ASPOSECPP_SHARED_API EntityTagHeaderValue(String tag);
    /// Constructs a new instance.
    /// @param tag A string representation of an EntityTagHeaderValue-class instance.
    /// @param isWeak A value that indicates if the current instance is a weak validator.
    ASPOSECPP_SHARED_API EntityTagHeaderValue(String tag, bool isWeak);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the EntityTagHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the EntityTagHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<EntityTagHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the EntityTagHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<EntityTagHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the EntityTagHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetEntityTagLength(String input, int32_t startIndex,
                                      System::SharedPtr<EntityTagHeaderValue>& parsedValue);

private:
    /// A value of the 'ETag' header.
    static System::SharedPtr<EntityTagHeaderValue> s_any;
    /// A string representation of an EntityTagHeaderValue-class instance.
    String _tag;
    /// Indicates if the current instance is a weak validator.
    bool _isWeak;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    EntityTagHeaderValue(System::SharedPtr<EntityTagHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(EntityTagHeaderValue, CODEPORTING_ARGS(System::SharedPtr<EntityTagHeaderValue> source), CODEPORTING_ARGS(source));

    /// Constructs a new instance.
    EntityTagHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(EntityTagHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
