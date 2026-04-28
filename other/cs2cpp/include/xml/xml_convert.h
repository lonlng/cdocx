/// @file xml/xml_convert.h

#pragma once

#include <xml/xml_date_time_serialization_mode.h>
#include <xml/xml_char_type.h>
#include <system/object_ext.h>
#include <system/exceptions.h>
#include <system/enum_helpers.h>
#include <system/enum.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
class Details_ArgumentException; using ArgumentException = System::ExceptionWrapper<Details_ArgumentException>;
class DateTime;
class DateTimeOffset;
class Decimal;
class Guid;
namespace Internal
{
namespace Xml
{
namespace XPath
{
class IDQuery;
class NumberFunctions;
class NumericExpr;
class StringFunctions;
class XPathComparerHelper;
class XPathScanner;
} // namespace XPath
} // namespace Xml
} // namespace Internal
enum class StringSplitOptions;
namespace Text
{
namespace RegularExpressions
{
class Regex;
} // namespace RegularExpressions
} // namespace Text
class TimeSpan;
class Uri;
namespace Xml
{
class CharEntityEncoderFallbackBuffer;
class DocumentSchemaValidator;
class DocumentXmlWriter;
class DtdParser;
namespace Schema
{
class Datatype_anyURI;
class Datatype_boolean;
class Datatype_byte;
class Datatype_char;
class Datatype_decimal;
class Datatype_double;
class Datatype_duration;
class Datatype_fixed;
class Datatype_float;
class Datatype_hexBinary;
class Datatype_int;
class Datatype_integer;
class Datatype_List;
class Datatype_long;
class Datatype_short;
class Datatype_unsignedByte;
class Datatype_unsignedInt;
class Datatype_unsignedLong;
class Datatype_unsignedShort;
class Datatype_uuid;
class NamespaceList;
class Preprocessor;
class SchemaCollectionPreprocessor;
class StringFacetsChecker;
class XmlBaseConverter;
class XmlListConverter;
class XmlMiscConverter;
class XmlNumeric10Converter;
class XmlSchemaParticle;
class XmlSchemaValidator;
class XmlUntypedConverter;
class XmlUntypedStringConverter;
class XsdBuilder;
} // namespace Schema
class XmlCharCheckingReader;
class XmlCharCheckingWriter;
class XmlEncodedRawTextWriter;
class XmlNode;
class XmlQualifiedName;
class XmlReader;
class XmlSqlBinaryReader;
class XmlTextEncoder;
class XmlTextReaderImpl;
class XmlTextWriter;
class XmlUtf8RawTextWriter;
class XmlWellFormedWriter;
class XmlWriter;
namespace XPath
{
class XPathNavigator;
class XPathNavigatorReader;
} // namespace XPath
class XsdValidatingReader;
namespace Xsl
{
namespace XsltOld
{
class Compiler;
class ContainerAction;
class CopyOfAction;
class NumberAction;
class Processor;
class TemplateAction;
class UseAttributeSetsAction;
class XsltCompileContext;
class XsltOutput;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

enum class ExceptionType
{
    ArgumentException,
    XmlException
};

/// Encodes and decodes XML names, and provides methods for converting between runtime types and XML Schema definition language (XSD) types.
/// When converting data types, the values returned are locale-independent.
class ASPOSECPP_SHARED_CLASS XmlConvert : public System::Object
{
    typedef XmlConvert ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlConvert>;

private:
    /// @cond
    friend class XmlSqlBinaryReader;
    friend class XmlReader;
    friend class CharEntityEncoderFallbackBuffer;
    friend class XmlEncodedRawTextWriter;
    friend class XmlUtf8RawTextWriter;
    friend class XmlWriter;
    friend class XmlCharCheckingReader;
    friend class XmlCharCheckingWriter;
    friend class XmlReader;
    friend class XmlTextEncoder;
    friend class XmlTextReaderImpl;
    friend class XmlTextWriter;
    friend class XmlWellFormedWriter;
    friend class XmlWellFormedWriter;
    friend class XsdValidatingReader;
    friend class DocumentSchemaValidator;
    friend class DocumentXmlWriter;
    friend class XmlNode;
    friend class Schema::Datatype_List;
    friend class Schema::Datatype_boolean;
    friend class Schema::Datatype_float;
    friend class Schema::Datatype_double;
    friend class Schema::Datatype_decimal;
    friend class Schema::Datatype_duration;
    friend class Schema::Datatype_hexBinary;
    friend class Schema::Datatype_anyURI;
    friend class Schema::Datatype_integer;
    friend class Schema::Datatype_long;
    friend class Schema::Datatype_int;
    friend class Schema::Datatype_short;
    friend class Schema::Datatype_byte;
    friend class Schema::Datatype_unsignedLong;
    friend class Schema::Datatype_unsignedInt;
    friend class Schema::Datatype_unsignedShort;
    friend class Schema::Datatype_unsignedByte;
    friend class Schema::Datatype_char;
    friend class Schema::Datatype_fixed;
    friend class Schema::Datatype_uuid;
    friend class DtdParser;
    friend class Schema::XmlSchemaParticle;
    friend class Schema::StringFacetsChecker;
    friend class Schema::NamespaceList;
    friend class Schema::Preprocessor;
    friend class Schema::SchemaCollectionPreprocessor;
    friend class Schema::XmlSchemaValidator;
    friend class Schema::XmlUntypedStringConverter;
    friend class Schema::XmlBaseConverter;
    friend class Schema::XmlNumeric10Converter;
    friend class Schema::XmlMiscConverter;
    friend class Schema::XmlUntypedConverter;
    friend class Schema::XmlListConverter;
    friend class Schema::XsdBuilder;
    friend class XmlQualifiedName;
    friend class Internal::Xml::XPath::XPathComparerHelper;
    friend class Internal::Xml::XPath::IDQuery;
    friend class Internal::Xml::XPath::NumberFunctions;
    friend class Internal::Xml::XPath::NumericExpr;
    friend class Internal::Xml::XPath::StringFunctions;
    friend class Internal::Xml::XPath::XPathScanner;
    friend class XPath::XPathNavigator;
    friend class XPath::XPathNavigatorReader;
    friend class Xsl::XsltOld::ContainerAction;
    friend class Xsl::XsltOld::Compiler;
    friend class Xsl::XsltOld::CopyOfAction;
    friend class Xsl::XsltOld::TemplateAction;
    friend class Xsl::XsltOld::UseAttributeSetsAction;
    friend class Xsl::XsltOld::NumberAction;
    friend class Xsl::XsltOld::Processor;
    friend class Xsl::XsltOld::XsltCompileContext;
    friend class Xsl::XsltOld::XsltCompileContext;
    friend class Xsl::XsltOld::XsltOutput;
    /// @endcond

public:

    /// Converts the name to a valid XML name.
    /// @param name A name to be translated.
    /// @returns The name with any invalid characters replaced by an escape string.
    static ASPOSECPP_SHARED_API String EncodeName(const String& name);
    /// Verifies the name is valid according to the XML specification.
    /// @param name The name to be encoded.
    /// @returns The encoded name.
    static ASPOSECPP_SHARED_API String EncodeNmToken(const String& name);
    /// Converts the name to a valid XML local name.
    /// @param name The name to be encoded.
    /// @returns The encoded name.
    static ASPOSECPP_SHARED_API String EncodeLocalName(const String& name);
    /// Decodes a name. This method does the reverse of the XmlConvert::EncodeName(String) and XmlConvert::EncodeLocalName(String) methods.
    /// @param name The name to be transformed.
    /// @returns The decoded name.
    static ASPOSECPP_SHARED_API String DecodeName(const String& name);
    /// Verifies that the name is a valid name according to the W3C Extended Markup Language recommendation.
    /// @param name The name to verify.
    /// @returns The name, if it is a valid XML name.
    /// @throws XmlException @p name is not a valid XML name.
    /// @throws ArgumentNullException @p name is @c nullptr or String::Empty.
    static ASPOSECPP_SHARED_API String VerifyName(const String& name);
    /// Verifies that the name is a valid @c NCName according to the W3C Extended Markup Language recommendation.
    /// An @c NCName is a name that cannot contain a colon.
    /// @param name The name to verify.
    /// @returns The name, if it is a valid NCName.
    /// @throws ArgumentNullException @p name is @c nullptr or String::Empty.
    /// @throws XmlException @p name is not a valid non-colon name.
    static ASPOSECPP_SHARED_API String VerifyNCName(const String& name);
    /// Verifies that the string is a valid token according to the W3C XML Schema Part2: Datatypes recommendation.
    /// @param token The string value you wish to verify.
    /// @returns The token, if it is a valid token.
    /// @throws XmlException The string value is not a valid token.
    static ASPOSECPP_SHARED_API String VerifyTOKEN(const String& token);
    /// Verifies that the string is a valid NMTOKEN according to the W3C XML Schema Part2: Datatypes recommendation.
    /// @param name The string you wish to verify.
    /// @returns The name token, if it is a valid NMTOKEN.
    /// @throws XmlException The string is not a valid name token.
    /// @throws ArgumentNullException @p name is @c nullptr.
    static ASPOSECPP_SHARED_API String VerifyNMTOKEN(const String& name);
    /// Returns the passed-in string if all the characters and surrogate pair characters in the string argument are valid XML characters,
    /// otherwise an XmlException is thrown with information on the first invalid character encountered.
    /// @param content String that contains characters to verify.
    /// @returns The passed-in string if all the characters and surrogate-pair characters in the string argument are valid XML characters,
    /// otherwise an XmlException is thrown with information on the first invalid character encountered.
    static ASPOSECPP_SHARED_API String VerifyXmlChars(const String& content);
    /// Returns the passed in string instance if all the characters in the string argument are valid public id characters.
    /// @param publicId String that contains the id to validate.
    /// @returns The passed-in string if all the characters in the argument are valid public id characters.
    static ASPOSECPP_SHARED_API String VerifyPublicId(const String& publicId);
    /// Returns the passed-in string instance if all the characters in the string argument are valid whitespace characters.
    /// @param content String to verify.
    /// @returns The passed-in string instance if all the characters in the string argument are valid whitespace characters,
    /// otherwise @c nullptr.
    static ASPOSECPP_SHARED_API String VerifyWhitespace(const String& content);
    /// Checks if the passed-in character is a valid Start Name Character type.
    /// @param ch The character to validate.
    /// @returns @c true if the character is a valid Start Name Character type; otherwise, @c false.
    static ASPOSECPP_SHARED_API bool IsStartNCNameChar(char16_t ch);
    /// Checks whether the passed-in character is a valid non-colon character type.
    /// @param ch The character to verify as a non-colon character.
    /// @returns @c true if the character is a valid non-colon character type; otherwise, @c false.
    static ASPOSECPP_SHARED_API bool IsNCNameChar(char16_t ch);
    /// Checks if the passed-in character is a valid XML character.
    /// @param ch The character to validate.
    /// @returns @c true if the passed in character is a valid XML character; otherwise, @c false.
    static ASPOSECPP_SHARED_API bool IsXmlChar(char16_t ch);
    /// Checks if the passed-in surrogate pair of characters is a valid XML character.
    /// @param lowChar The surrogate character to validate.
    /// @param highChar The surrogate character to validate.
    /// @returns @c true if the passed in surrogate pair of characters is a valid XML character; otherwise, @c false.
    static ASPOSECPP_SHARED_API bool IsXmlSurrogatePair(char16_t lowChar, char16_t highChar);
    /// Returns the passed-in character instance if the character in the argument is a valid public id character, otherwise @c nullptr.
    /// @param ch Char object to validate.
    /// @returns The passed-in character if the character is a valid public id character, otherwise @c nullptr.
    static ASPOSECPP_SHARED_API bool IsPublicIdChar(char16_t ch);
    /// Checks if the passed-in character is a valid XML whitespace character.
    /// @param ch The character to validate.
    /// @returns @c true if the passed in character is a valid XML whitespace character; otherwise, @c false.
    static ASPOSECPP_SHARED_API bool IsWhitespaceChar(char16_t ch);
    /// Converts the Boolean to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Boolean, that is, "true" or "false".
    static ASPOSECPP_SHARED_API String ToString(bool value);
    /// Converts the Char to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Char.
    static ASPOSECPP_SHARED_API String ToString(char16_t value);
    /// Converts the Decimal to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Decimal.
    static ASPOSECPP_SHARED_API String ToString(Decimal value);
    /// Converts the SByte to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the SByte.
    static ASPOSECPP_SHARED_API String ToString(int8_t value);
    /// Converts the Int16 to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Int16.
    static ASPOSECPP_SHARED_API String ToString(int16_t value);
    /// Converts the Int32 to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Int32.
    static ASPOSECPP_SHARED_API String ToString(int32_t value);
    /// Converts the Int64 to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Int64.
    static ASPOSECPP_SHARED_API String ToString(int64_t value);
    /// Converts the Byte to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Byte.
    static ASPOSECPP_SHARED_API String ToString(uint8_t value);
    /// Converts the UInt16 to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the UInt16.
    static ASPOSECPP_SHARED_API String ToString(uint16_t value);
    /// Converts the UInt32 to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the UInt32.
    static ASPOSECPP_SHARED_API String ToString(uint32_t value);
    /// Converts the UInt64 to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the UInt64.
    static ASPOSECPP_SHARED_API String ToString(uint64_t value);
    /// Converts the Single to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Single.
    static ASPOSECPP_SHARED_API String ToString(float value);
    /// Converts the Double to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Double.
    static ASPOSECPP_SHARED_API String ToString(double value);
    /// Converts the TimeSpan to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the TimeSpan.
    static ASPOSECPP_SHARED_API String ToString(TimeSpan value);
    /// Converts the DateTime to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the DateTime in the format yyyy-MM-ddTHH:mm:ss where 'T' is a constant literal.
    static ASPOSECPP_SHARED_API String ToString(DateTime value);
    /// Converts the DateTime to a String.
    /// @param value The value to convert.
    /// @param format The format structure that defines how to display the converted string.
    /// Valid formats include "yyyy-MM-ddTHH:mm:sszzzzzz" and its subsets.
    /// @returns A string representation of the DateTime in the specified format.
    static ASPOSECPP_SHARED_API String ToString(DateTime value, const String& format);
    /// Converts the DateTime to a String using the XmlDateTimeSerializationMode specified.
    /// @param value The DateTime value to convert.
    /// @param dateTimeOption One of the XmlDateTimeSerializationMode values that specify how to treat the DateTime value.
    /// @returns A String equivalent of the DateTime.
    /// @throws ArgumentException The @p dateTimeOption value is not valid.
    /// @throws ArgumentNullException The @p value or @p dateTimeOption value is @c nullptr.
    static ASPOSECPP_SHARED_API String ToString(DateTime value, XmlDateTimeSerializationMode dateTimeOption);
    /// Converts the supplied DateTimeOffset to a String.
    /// @param value The DateTimeOffset to be converted.
    /// @returns A String representation of the supplied DateTimeOffset.
    static ASPOSECPP_SHARED_API String ToString(DateTimeOffset value);
    /// Converts the supplied DateTimeOffset to a String in the specified format.
    /// @param value The DateTimeOffset to be converted.
    /// @param format The format to which @p s is converted. The format parameter can be any subset of the W3C Recommendation for the XML dateTime type.
    /// For more information, see the <a href="https://www.w3.org/TR/xmlschema-2/#dateTime">dateTime</a> section of the XML Schema specification.
    /// @returns A String representation in the specified format of the supplied DateTimeOffset.
    static ASPOSECPP_SHARED_API String ToString(DateTimeOffset value, const String& format);
    /// Converts the Guid to a String.
    /// @param value The value to convert.
    /// @returns A string representation of the Guid.
    static ASPOSECPP_SHARED_API String ToString(Guid value);
    /// Converts the String to a Boolean equivalent.
    /// @param s The string to convert.
    /// @returns A @c Boolean value, that is, @c true or @c false.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s does not represent a @c Boolean value.
    static ASPOSECPP_SHARED_API bool ToBoolean(String s);
    /// Converts the String to a Char equivalent.
    /// @param s The string containing a single character to convert.
    /// @returns A @c Char representing the single character.
    /// @throws ArgumentNullException The value of the @p s parameter is @c nullptr.
    /// @throws FormatException The @p s parameter contains more than one character.
    static ASPOSECPP_SHARED_API char16_t ToChar(const String& s);
    /// Converts the String to a Decimal equivalent.
    /// @param s The string to convert.
    /// @returns A @c Decimal equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Decimal::MinValue or greater than Decimal::MaxValue.
    static ASPOSECPP_SHARED_API Decimal ToDecimal(const String& s);
    /// Converts the String to a SByte equivalent.
    /// @param s The string to convert.
    /// @returns An @c SByte equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than SByte::MinValue or greater than SByte::MaxValue.
    static ASPOSECPP_SHARED_API int8_t ToSByte(const String& s);
    /// Converts the String to a Int16 equivalent.
    /// @param s The string to convert.
    /// @returns An Int16 equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Int16::MinValue or greater than Int16::MaxValue.
    static ASPOSECPP_SHARED_API int16_t ToInt16(const String& s);
    /// Converts the String to a Int32 equivalent.
    /// @param s The string to convert.
    /// @returns An Int32 equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Int32::MinValue or greater than Int32::MaxValue.
    static ASPOSECPP_SHARED_API int32_t ToInt32(const String& s);
    /// Converts the String to a Int64 equivalent.
    /// @param s The string to convert.
    /// @returns An Int64 equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Int64::MinValue or greater than Int64::MaxValue.
    static ASPOSECPP_SHARED_API int64_t ToInt64(const String& s);
    /// Converts the String to a Byte equivalent.
    /// @param s The string to convert.
    /// @returns A @c Byte equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Byte::MinValue or greater than Byte::MaxValue.
    static ASPOSECPP_SHARED_API uint8_t ToByte(const String& s);
    /// Converts the String to a UInt16 equivalent.
    /// @param s The string to convert.
    /// @returns A UInt16 equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than UInt16::MinValue or greater than UInt16::MaxValue.
    static ASPOSECPP_SHARED_API uint16_t ToUInt16(const String& s);
    /// Converts the String to a UInt32 equivalent.
    /// @param s The string to convert.
    /// @returns A UInt32 equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than UInt32::MinValue or greater than UInt32::MaxValue.
    static ASPOSECPP_SHARED_API uint32_t ToUInt32(const String& s);
    /// Converts the String to a UInt64 equivalent.
    /// @param s The string to convert.
    /// @returns A UInt64 equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than UInt64::MinValue or greater than UInt64::MaxValue.
    static ASPOSECPP_SHARED_API uint64_t ToUInt64(const String& s);
    /// Converts the String to a Single equivalent.
    /// @param s The string to convert.
    /// @returns A Single equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Single::MinValue or greater than Single::MaxValue.
    static ASPOSECPP_SHARED_API float ToSingle(String s);
    /// Converts the String to a Double equivalent.
    /// @param s The string to convert.
    /// @returns A Double equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is not in the correct format.
    /// @throws OverflowException @p s represents a number less than Double::MinValue or greater than Double::MaxValue.
    static ASPOSECPP_SHARED_API double ToDouble(String s);
    /// Converts the String to a TimeSpan equivalent.
    /// @param s The string to convert. The string format must conform to the W3C XML Schema Part 2: Datatypes recommendation for duration.
    /// @returns A TimeSpan equivalent of the string.
    /// @throws FormatException @p s is not in correct format to represent a TimeSpan value.
    static ASPOSECPP_SHARED_API TimeSpan ToTimeSpan(const String& s);
    /// Converts the String to a DateTime equivalent.
    /// @param s The string to convert.
    /// @returns A DateTime equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s is an empty string or is not in the correct format.
    static ASPOSECPP_SHARED_API DateTime ToDateTime(const String& s);
    /// Converts the String to a DateTime equivalent.
    /// @param s The string to convert.
    /// @param format The format structure to apply to the converted DateTime.
    /// Valid formats include "yyyy-MM-ddTHH:mm:sszzzzzz" and its subsets. The string is validated against this format.
    /// @returns A DateTime equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s or @p format is String::Empty
    /// or
    /// @p s does not contain a date and time that corresponds to @p format.
    static ASPOSECPP_SHARED_API DateTime ToDateTime(const String& s, const String& format);
    /// Converts the String to a DateTime equivalent.
    /// @param s The string to convert.
    /// @param formats An array containing the format structures to apply to the converted DateTime.
    /// Valid formats include "yyyy-MM-ddTHH:mm:sszzzzzz" and its subsets.
    /// @returns A DateTime equivalent of the string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s or an element of @p formats is String::Empty
    /// or
    /// @p s does not contain a date and time that corresponds to any of the elements of @p formats.
    static ASPOSECPP_SHARED_API DateTime ToDateTime(const String& s, const ArrayPtr<String>& formats);
    /// Converts the String to a DateTime using the XmlDateTimeSerializationMode specified.
    /// @param s The String value to convert.
    /// @param dateTimeOption One of the enumeration values that specify whether the date should be converted to local time
    /// or preserved as Coordinated Universal Time (UTC), if it is a UTC date.
    /// @returns A DateTime equivalent of the String.
    /// @throws NullReferenceException @p s is @c nullptr.
    /// @throws ArgumentNullException @p dateTimeOption is @c nullptr.
    /// @throws FormatException @p s is an empty string or is not in a valid format.
    static ASPOSECPP_SHARED_API DateTime ToDateTime(const String& s, XmlDateTimeSerializationMode dateTimeOption);
    /// Converts the supplied String to a DateTimeOffset equivalent.
    /// @param s The string to convert. The string must conform to a subset of the W3C Recommendation for the XML dateTime type.
    /// For more information, see the <a href="https://www.w3.org/TR/xmlschema-2/#dateTime">dateTime</a> section of the XML Schema specification.
    /// @returns The DateTimeOffset equivalent of the supplied string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws ArgumentOutOfRangeException The argument passed to this method is outside the range of allowable values.
    /// For information about allowable values, see DateTimeOffset.
    /// @throws FormatException The argument passed to this method does not conform to a subset of the W3C Recommendations for the XML dateTime type.
    /// For more information, see the <a href="https://www.w3.org/TR/xmlschema-2/#dateTime">dateTime</a> section of the XML Schema specification.
    static ASPOSECPP_SHARED_API DateTimeOffset ToDateTimeOffset(const String& s);
    /// Converts the supplied String to a DateTimeOffset equivalent.
    /// @param s The string to convert.
    /// @param format The format from which @p s is converted. The format parameter can be any subset of the W3C Recommendation for the XML dateTime type.
    /// For more information, see the <a href="https://www.w3.org/TR/xmlschema-2/#dateTime">dateTime</a> section of the XML Schema specification.
    /// The string @p s is validated against this format.
    /// @returns The DateTimeOffset equivalent of the supplied string.
    /// @throws ArgumentNullException @p s is @c nullptr.
    /// @throws FormatException @p s or @p format is an empty string or is not in the specified format.
    static ASPOSECPP_SHARED_API DateTimeOffset ToDateTimeOffset(const String& s, const String& format);
    /// Converts the supplied String to a DateTimeOffset equivalent.
    /// @param s The string to convert.
    /// @param formats An array of formats from which @p s can be converted.
    /// Each format in @p formats can be any subset of the W3C Recommendation for the XML dateTime type.
    /// For more information, see the <a href="https://www.w3.org/TR/xmlschema-2/#dateTime">dateTime</a> section of the XML Schema specification.
    /// The string @p s is validated against one of these formats.
    /// @returns The DateTimeOffset equivalent of the supplied string.
    static ASPOSECPP_SHARED_API DateTimeOffset ToDateTimeOffset(const String& s, const ArrayPtr<String>& formats);
    /// Converts the String to a Guid equivalent.
    /// @param s The string to convert.
    /// @returns A Guid equivalent of the string.
    static ASPOSECPP_SHARED_API Guid ToGuid(const String& s);

protected:

    /// @cond
    static ArrayPtr<char16_t> crt;
    static ArrayPtr<char16_t> WhitespaceChars;

    static ArrayPtr<uint8_t> FromBinHexString(const String& s);
    static ArrayPtr<uint8_t> FromBinHexString(const String& s, bool allowOddCount);
    static String ToBinHexString(const ArrayPtr<uint8_t>& inArray);
    static Exception TryVerifyName(const String& name);
    static String VerifyQName(const String& name, ExceptionType exceptionType);
    static String VerifyNCName(const String& name, ExceptionType exceptionType);
    static Exception TryVerifyNCName(const String& name);
    static Exception TryVerifyTOKEN(const String& token);
    static String VerifyNMTOKEN(const String& name, ExceptionType exceptionType);
    static Exception TryVerifyNMTOKEN(const String& name);
    static Exception TryVerifyNormalizedString(const String& str);
    static Exception TryToBoolean(String s, bool& result);
    static Exception TryToChar(const String& s, char16_t& result);
    static Exception TryToDecimal(const String& s, Decimal& result);
    static Decimal ToInteger(const String& s);
    static Exception TryToInteger(const String& s, Decimal& result);
    static Exception TryToSByte(const String& s, int8_t& result);
    static Exception TryToInt16(const String& s, int16_t& result);
    static Exception TryToInt32(const String& s, int32_t& result);
    static Exception TryToInt64(const String& s, int64_t& result);
    static Exception TryToByte(const String& s, uint8_t& result);
    static Exception TryToUInt16(const String& s, uint16_t& result);
    static Exception TryToUInt32(const String& s, uint32_t& result);
    static Exception TryToUInt64(const String& s, uint64_t& result);
    static Exception TryToSingle(String s, float& result);
    static Exception TryToDouble(String s, double& result);
    static double ToXPathDouble(const SharedPtr<Object>& o);
    static String ToXPathString(const SharedPtr<Object>& value);
    static double XPathRound(double value);
    static Exception TryToTimeSpan(const String& s, TimeSpan& result);
    static Exception TryToGuid(const String& s, Guid& result);
    static SharedPtr<Uri> ToUri(String s);
    static Exception TryToUri(String s, SharedPtr<Uri>& result);
    static bool StrEqual(const ArrayPtr<char16_t>& chars, int32_t strPos1, int32_t strLen1, const String& str2);
    static String TrimString(const String& value);
    static String TrimStringStart(const String& value);
    static String TrimStringEnd(const String& value);
    static ArrayPtr<String> SplitString(const String& value);
    static ArrayPtr<String> SplitString(const String& value, StringSplitOptions splitStringOptions);
    static bool IsNegativeZero(double value);
    static void VerifyCharData(const String& data, ExceptionType exceptionType);
    static void VerifyCharData(const String& data, ExceptionType invCharExceptionType, ExceptionType invSurrogateExceptionType);
    static void VerifyCharData(const ArrayPtr<char16_t>& data, int32_t offset, int32_t len, ExceptionType exceptionType);
    static String EscapeValueForDebuggerDisplay(const String& value);
    static Exception CreateException(const String& res, ExceptionType exceptionType, int32_t lineNo, int32_t linePos);
    static Exception CreateException(const String& res, const String& arg, ExceptionType exceptionType);
    static Exception CreateException(const String& res, const String& arg, ExceptionType exceptionType, int32_t lineNo, int32_t linePos);
    static Exception CreateException(const String& res, const ArrayPtr<String>& args, ExceptionType exceptionType);
    static Exception CreateException(const String& res, const ArrayPtr<String>& args, ExceptionType exceptionType, int32_t lineNo, int32_t linePos);
    static Exception CreateInvalidSurrogatePairException(char16_t low, char16_t hi);
    static Exception CreateInvalidSurrogatePairException(char16_t low, char16_t hi, ExceptionType exceptionType);
    static Exception CreateInvalidSurrogatePairException(char16_t low, char16_t hi, ExceptionType exceptionType, int32_t lineNo, int32_t linePos);
    static Exception CreateInvalidHighSurrogateCharException(char16_t hi);
    static Exception CreateInvalidHighSurrogateCharException(char16_t hi, ExceptionType exceptionType);
    static Exception CreateInvalidHighSurrogateCharException(char16_t hi, ExceptionType exceptionType, int32_t lineNo, int32_t linePos);
    static Exception CreateInvalidCharException(const ArrayPtr<char16_t>& data, int32_t length, int32_t invCharPos, ExceptionType exceptionType);
    static Exception CreateInvalidCharException(const String& data, int32_t invCharPos);
    static Exception CreateInvalidCharException(const String& data, int32_t invCharPos, ExceptionType exceptionType);
    static Exception CreateInvalidCharException(char16_t invChar, char16_t nextChar);
    static Exception CreateInvalidCharException(char16_t invChar, char16_t nextChar, ExceptionType exceptionType);
    static Exception CreateInvalidNameCharException(const String& name, int32_t index, ExceptionType exceptionType);
    static ArgumentException CreateInvalidNameArgumentException(const String& name, const String& argumentName);
    /// @endcond

private:

    static XmlCharType s_xmlCharType;
    static int32_t s_encodedCharLength;
    static SharedPtr<Text::RegularExpressions::Regex> s_encodeCharPattern;
    static SharedPtr<Text::RegularExpressions::Regex> s_decodeCharPattern;
    static ArrayPtr<String> s_allDateTimeFormats;

    static ArrayPtr<String> get_AllDateTimeFormats();

    static String EncodeName(const String& name, bool first, bool local);
    static int32_t FromHex(char16_t digit);
    static void CreateAllDateTimeFormats();
    static DateTime SwitchToLocalTime(DateTime value);
    static DateTime SwitchToUtcTime(DateTime value);
    static int64_t DoubleToInt64Bits(double value);

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::ExceptionType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::ExceptionType, const char_t*>, 2>& values();
};
/// @endcond


