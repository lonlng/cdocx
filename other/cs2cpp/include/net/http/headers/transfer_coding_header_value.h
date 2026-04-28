/// @file net/http/headers/transfer_coding_header_value.h
#pragma once

#include <system/collections/icollection.h>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/http/headers/name_value_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Accept-Encoding' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS TransferCodingHeaderValue : public virtual System::ICloneable
{
    /// This type.
    typedef TransferCodingHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a value.
    /// @returns The value.
    ASPOSECPP_SHARED_API String get_Value();
    /// Returns the parameters.
    /// @returns The parameters.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<NameValueHeaderValue>>>
        get_Parameters();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API TransferCodingHeaderValue();
    /// Constructs a new instance.
    /// @param value The value.
    ASPOSECPP_SHARED_API TransferCodingHeaderValue(String value);

    /// Converts a passed string to an instance of the TransferCodingHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the TransferCodingHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<TransferCodingHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the TransferCodingHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<TransferCodingHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the TransferCodingHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @param transferCodingCreator The delegate that is used to create instances of the TransferCodingHeaderValue
    /// class.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t
        GetTransferCodingLength(String input, int32_t startIndex,
                                const HeaderFunc<System::SharedPtr<TransferCodingHeaderValue>>& transferCodingCreator,
                                System::SharedPtr<TransferCodingHeaderValue>& parsedValue);
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;

protected:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ASPOSECPP_SHARED_API TransferCodingHeaderValue(System::SharedPtr<TransferCodingHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(TransferCodingHeaderValue, CODEPORTING_ARGS(System::SharedPtr<TransferCodingHeaderValue> source), CODEPORTING_ARGS(source));

private:
    /// The collection of the header parameters.
    System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> _parameters;
    /// The value.
    String _value;

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
