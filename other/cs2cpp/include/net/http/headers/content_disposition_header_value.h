/// @file net/http/headers/content_disposition_header_value.h
#pragma once

#include "system/date_time_offset.h"
#include <cstdint>
#include <system/collections/icollection.h>
#include <system/date_time_offset.h>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/http/headers/name_value_header_value.h>
#include <net/http/headers/object_collection.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Content-Disposition' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ContentDispositionHeaderValue : public System::ICloneable
{
    /// This type.
    typedef ContentDispositionHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a disposition type.
    /// @returns A disposition type.
    ASPOSECPP_SHARED_API String get_DispositionType();
    /// Sets a disposition type.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_DispositionType(String value);
    /// Returns a parameters collection of the 'Content-Disposition' header.
    /// @returns A parameters collection of the 'Content-Disposition' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<NameValueHeaderValue>>> get_Parameters();
    /// Gets a name for a part of the content body.
    /// @returns A name for a part of the content body.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets a name for a part of the content body.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Name(String value);
    /// Gets a value that determines how to construct a filename for storing the message payload. It is used when the
    /// entity is detached and stored in a separate file.
    /// @returns A value that determines how to construct a filename for storing the message payload.
    ASPOSECPP_SHARED_API String get_FileName();
    /// Sets a value that determines how to construct a filename for storing the message payload. It is used when the
    /// entity is detached and stored in a separate file.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_FileName(String value);
    /// Gets a value that determines how to construct filenames for storing the message payload. It is used when the
    /// entities are detached and stored in separate files.
    /// @returns A value determines how to construct filenames for storing the message payload.
    ASPOSECPP_SHARED_API String get_FileNameStar();
    /// Sets a value that determines how to construct filenames for storing the message payload. It is used when the
    /// entities are detached and stored in separate files.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_FileNameStar(String value);
    /// Gets the file creation date.
    /// @returns The file creation date.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_CreationDate();
    /// Sets the file creation date.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_CreationDate(Nullable<DateTimeOffset> value);
    /// Gets the file modification date.
    /// @returns The file modification date.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_ModificationDate();
    /// Sets the file modification date.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ModificationDate(Nullable<DateTimeOffset> value);
    /// Gets the date when the file was read the last time.
    /// @returns The date when the file was read the last time.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_ReadDate();
    /// Sets the date when the file read the last time.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ReadDate(Nullable<DateTimeOffset> value);
    /// Gets an approximate file size.
    /// @returns An approximate file size.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_Size();
    /// Sets an approximate file size.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Size(Nullable<int64_t> value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API ContentDispositionHeaderValue();
    /// Constructs a new instance.
    /// @param dispositionType A disposition type.
    ASPOSECPP_SHARED_API ContentDispositionHeaderValue(String dispositionType);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the ContentDispositionHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the ContentDispositionHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<ContentDispositionHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the ContentDispositionHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<ContentDispositionHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the ContentDispositionHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetDispositionTypeLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

protected:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ASPOSECPP_SHARED_API ContentDispositionHeaderValue(System::SharedPtr<ContentDispositionHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(ContentDispositionHeaderValue, CODEPORTING_ARGS(System::SharedPtr<ContentDispositionHeaderValue> source), CODEPORTING_ARGS(source));

private:
    /// Determines how to construct a filename for storing the message payload. It is used when the entity is detached
    /// and stored in a separate file.
    static const String fileName;
    /// A name for a part of the content body.
    static const String name;
    /// determines how to construct filenames for storing the message payload. It is used when the entities are detached
    /// and stored in separate files.
    static const String fileNameStar;
    /// The file creation date.
    static const String creationDate;
    /// The file modification date.
    static const String modificationDate;
    /// The date when the file was read the last time.
    static const String readDate;
    /// An approximate file size.
    static const String size;
    /// A parameters collection of the 'Content-Disposition' header.
    System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> _parameters;
    /// A disposition type.
    String _dispositionType;

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
    /// Parses the specified string representation of a disposition type.
    /// @param input The string representation of a disposition type.
    /// @param startIndex A start position for parsing.
    /// @param dispositionType The output parameter where a parsed value will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    static int32_t GetDispositionTypeExpressionLength(String input, int32_t startIndex, String& dispositionType);
    /// Checks the specified string representation of a disposition type.
    /// @param dispositionType The string representation of a disposition type.
    /// @param parameterName Not used.
    /// @throws System::ArgumentException The exception is thrown when the specified string is empty.
    /// @throws System::FormatException The exception is thrown when the specified string contains not only a token.
    static void CheckDispositionTypeFormat(String dispositionType, String parameterName);
    /// Gets a value by the specified name from the collection.
    /// @param parameter The name to look for.
    /// @returns A corresponding value to the specified name when a collection element is found, otherwise false.
    Nullable<DateTimeOffset> GetDate(String parameter);
    /// Looks for a name-value pair by the specified name in the collection and sets the specified value.
    /// @param parameter The name to look for.
    /// @param date The value that must be set.
    void SetDate(String parameter, Nullable<DateTimeOffset> date);
    /// Gets a value by the specified name from the collection.
    /// @param parameter The name to look for.
    /// @returns A corresponding value to the specified name when a collection element is found, otherwise false.
    String GetName(String parameter);
    /// Looks for an element by the specified name in the collection and sets the specified value.
    /// @param parameter The name to look for.
    /// @param value The value that must be set.
    void SetName(String parameter, String value);
    /// Encodes the specified MIME type to the Base64 string representation and wraps it in the quotes.
    /// @param input The MIME type.
    /// @returns The Base64 string representation that is wrapped in the quotes.
    /// @throws System::ArgumentException The exception is thrown when the specified string has an incorrect format.
    String EncodeAndQuoteMime(String input);
    /// Checks that the specified string is wrapped in the quotes.
    /// @param value The value that must be checked.
    /// @returns True when the specified string is wrapped in the quotes, otherwise false.
    bool IsQuoted(String value);
    /// Checks if the specified string is not encoded in Base64.
    /// @param input The value that must be checked.
    /// @returns False when the specified string is encoded in Base64, otherwise true.
    bool RequiresEncoding(String input);
    /// Encodes the specified MIME type to Base64.
    /// @param input The MIME type.
    /// @returns The Base64 string representation.
    String EncodeMime(String input);
    /// Tries to decode a MIME type from the specified Base64 string representation.
    /// @param input The Base64 string representation.
    /// @param output The output parameter where the decoded MIME type will be assigned.
    /// @returns True when decoding is successfully done, otherwise false.
    bool TryDecodeMime(String input, String& output);
    /// Decodes a string from the specified RFC 5987 string representation.
    /// @param input The RFC 5987 string representation.
    /// @returns The decoding result.
    String Encode5987(String input);
    /// Tries to decode a string from the specified RFC 5987 string representation.
    /// @param input The RFC 5987 string representation.
    /// @param output The output parameter where the decoded string will be assigned.
    /// @returns True when decoding is successfully done, otherwise false.
    bool TryDecode5987(String input, String& output);
};

}}}} // namespace System::Net::Http::Headers
