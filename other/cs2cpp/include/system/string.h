/// @file system/string.h
#ifndef _aspose_system_string_h_
#define _aspose_system_string_h_

#include <system/text/normalization_form.h>
#include <system/string_comparison.h>
#include <system/shared_ptr.h>
#include <system/details/icu_namespace.h>
#include <system/details/stack_array.h>
#include <system/object.h>

#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <system/diagnostics/debug.h>
#include <iterator>
#include <cstdint>

#include <fwd.h>

#ifdef ASPOSECPPLIB_BEING_BUILT
#include <unicode/unistr.h>
#endif
/// Begins an ICU namespace scope.
ASPOSECPP_3RD_PARTY_ICU_NAMESPACE_START {
    /// Forward declaration of UnicodeString class from ICU
    ASPOSECPP_3RD_PARTY_CLASS(UnicodeString);
}

/// Ensures that UChar is an alias for char16_t.
ASPOSECPP_3RD_PARTY_TYPEDEF(UChar, char16_t);

namespace System { namespace Text { class StringBuilder; } }
namespace System { namespace Text { namespace RegularExpressions { class Regex; } } }
namespace System { namespace Text { namespace RegularExpressions { namespace Detail { class Formatter; } } } }
namespace System { namespace Globalization { class CompareInfo; } }
namespace System { namespace Globalization { class TextElementEnumerator; } }
namespace System { namespace Globalization { class TextInfo; } }
namespace System { namespace Collections { namespace Generic { template <typename T> class IEnumerable; } } }

namespace System { namespace Details { template<typename T> class ArrayView; } }

namespace System
{

namespace Detail {
    /// Wrapper to hold ICU UnicodeString class without including ICU
    ASPOSECPP_3RD_PARTY_TYPE_HOLDER(codeporting_icu::UnicodeString, UnicodeString, 64, size_t, UnicodeStringHolder);
}

/// Determines string splitting behavior
enum class StringSplitOptions
{
    /// Keep empty strings when splitting string
    None = 0,
    /// Discard empty strings when splitting  string
    RemoveEmptyEntries = 1
};

using codeporting_icu::UnicodeString;

/// Template magic to check if a type is a sequence of string characters.
/// @tparam T checked type.
/// @tparam CharT Character type to check against.
template <typename T, typename CharT>
struct IsStringByteSequence
    : public std::integral_constant<bool, std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::decay<T>::type>::type>::type, CharT>::value> {};

/// Template magic to check if a type is a pointer to character string.
/// @tparam T checked type.
/// @tparam CharT Character type to check against.
template <typename T, typename CharT>
struct IsStringPointer :
    public std::integral_constant<bool, IsStringByteSequence<T, CharT>::value && std::is_pointer<T>::value> {};

/// Template magic to check if a type is a string literal.
/// @tparam T checked type.
/// @tparam CharT Character type to check against.
template <typename T, typename CharT>
struct IsStringLiteral :
    public std::integral_constant<bool, IsStringByteSequence<T, CharT>::value && std::is_array<T>::value> {};

/// String class used across the library. Is a substitute for C# System.String when translating code.
/// For optimization reasons, isn't considered an Object subclass.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
/// @code
/// #include "system/string.h"
/// #include <iostream>
///
/// int main()
/// {
///   // Construct a string from the array of characters and print it.
///   const auto chars = {u'h', u'e', u'l', u'l', u'o'};
///   const System::String string1(chars);
///   std::cout << string1 << std::endl;
///
///   // Construct a string from the array of bytes and print it.
///   const uint8_t bytes[] = {0x77, 0x6f, 0x72, 0x6c, 0x64, 0x0};
///   const auto string2 = System::String::FromUtf8(bytes);
///   std::cout << string2 << std::endl;
///
///   // Trim the string below and print it.
///   const System::String string3(u"   This string contains whitespaces in the beginning and at the end.   ");
///   std::cout << '"' << string3.Trim() << '"' << std::endl;
///
///   // Print the number of words in the .
///   std::cout << "Number of words: " << string3.Trim().Split(' ')->get_Length() << std::endl;
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// hello
/// world
/// "This string contains whitespaces in the beginning and at the end."
/// Number of words: 11
/// */
/// @endcode
class ASPOSECPP_SHARED_CLASS String
{
    static const uintptr_t state_literal = 0;
    static const uintptr_t state_null = 1;

    friend class System::Text::StringBuilder;
    friend class System::Globalization::CompareInfo;
    friend class System::Globalization::TextElementEnumerator;
    friend class System::Text::RegularExpressions::Regex; // Uses private method Append for efficient string construction.
    friend class System::Text::RegularExpressions::Detail::Formatter; // Uses private method Append for efficient string construction.
    friend class System::Globalization::TextInfo;
    friend class System::Object;

    using ThisType = String;

    /// RTTI declaration for using Type(), Is() and alike-methods.
    RTTI_INFO_VALUE_TYPE(System::String);
public:
    /// Reverse iterator type.
    using reverse_iterator = std::reverse_iterator<const char16_t*>;

    /// String is value type on C++ side which implicitly (without inheritance) implements some interfaces
    ASPOSECPP_VALUE_TYPE_IMPLEMENTS_INTERFACES();

    /// Default constructor. Creates string object which is considered null.
    ASPOSECPP_SHARED_API String();

    /// Constructs string based on string literal. Considers literal a null-terminated string, calculates target string length based on literal size.
    /// @param value String literal pointer.
    template<typename T>
    String(T& value, typename std::enable_if<IsStringLiteral<T, char16_t>::value>::type* = nullptr)
        : String(value, std::extent<T>::value - 1, state_literal)
    {}

    /// Constructs string based on character string pointer. Treats pointed string as null-terminated, calculates target string length based on null character.
    /// @param value Character string pointer.
    template<typename T>
    String(const T& value, typename std::enable_if<IsStringPointer<T, char16_t>::value>::type* = nullptr)
        : String(value, -1)
    {
        m_state = state_literal;
    }

    /// Constructs string based on string literal. Considers literal a null-terminated string in UTF8, calculates target string length based on literal size.
    /// @param value String literal pointer.
    template<typename T>
    explicit String(T& value, typename std::enable_if<IsStringLiteral<T, char>::value>::type* = nullptr)
        : String(value, std::extent<T>::value - 1)
    {
        m_state = state_literal;
    }

    /// Constructs string based on character string pointer. Treats pointed string as null-terminated in UTF8, calculates target string length based on null character.
    /// @param value Character string pointer.
    template<typename T>
    explicit String(const T& value, typename std::enable_if<IsStringPointer<T, char>::value>::type* = nullptr)
        : String(value, -1)
    {
        m_state = state_literal;
    }
    
    /// Constructs string from character string pointer and explicit length.
    /// @param str String pointer, may be literal or array.
    /// @param length Explicit string length
    ASPOSECPP_SHARED_API String(const char16_t* str, int length);

    /// Constructs string from character string pointer and explicit length.
    /// @param str String pointer to the UTF8 data, may be literal or array.
    /// @param length Explicit string length
    ASPOSECPP_SHARED_API String(const char* str, int length);

    /// Constructs string from character string pointer from starting position using length.
    /// @param str String pointer, may be literal or array.
    /// @param start Starting position.
    /// @param length String length.
    ASPOSECPP_SHARED_API String(const char16_t* str, int start, int length);

    /// Fill constructor.
    /// @param ch Fill character.
    /// @param count Target length.
    ASPOSECPP_SHARED_API explicit String(const char16_t ch, int count);

    /// Nullptr constructor. Declared as template to resolve priorities with other template constructors.
    /// @tparam T Should be nullptr_t
    /// @param value nullptr
    template<typename T>
    String(const T& value,
            typename std::enable_if<std::is_same<T, std::nullptr_t>::value>::type* = nullptr)
        : String()
    {
        ASPOSE_UNUSED(value);
    }

    /// Constructs string based on widestring literal. Considers literal a null-terminated string, calculates target string length based on literal size.
    /// Conversion from wchar_t is time-consuming on some platforms, so no implicit conversions are allowed.
    /// @param value String literal pointer.
    template<typename T>
    explicit String(T& value, typename std::enable_if<IsStringLiteral<T, wchar_t>::value>::type* = nullptr)
            : String(value, std::extent<T>::value - 1)
    {}

    /// Constructs string based on widecharacter string pointer. Treats pointed string as null-terminated, calculates target string length based on null character.
    /// Conversion from wchar_t is time-consuming on some platforms, so no implicit conversions are allowed.
    /// @param value Character string pointer.
    template<typename T>
    explicit String(const T& value, typename std::enable_if<IsStringPointer<T, wchar_t>::value>::type* = nullptr)
        : String(value, -1)
    {}

    /// Constructs string from widecharacter string pointer and explicit length.
    /// Conversion from wchar_t is time-consuming on some platforms, so no implicit conversions are allowed.
    /// @param str String pointer, may be literal or array.
    /// @param length Explicit string length
    ASPOSECPP_SHARED_API explicit String(const wchar_t* str, int length);
    /// Fill constructor.
    /// Conversion from wchar_t is time-consuming on some platforms, so no implicit conversions are allowed.
    /// @param ch Fill character.
    /// @param count Target length.
    ASPOSECPP_SHARED_API explicit String(const wchar_t ch, int count = 1);

    /// Copy constructor.
    /// @param str String to copy.
    ASPOSECPP_SHARED_API String(const String& str);
    /// Move constructor.
    /// @param str String to move data from.
    ASPOSECPP_SHARED_API String(String&& str) noexcept;

    /// Converts whole character array to string.
    /// @param arr Array to convert to string.
    ASPOSECPP_SHARED_API String(const ArrayPtr<char16_t>& arr);
    /// Converts character array subrange to string. If parameters are out of array bounds, empty string is constructed.
    /// @param arr Character array.
    /// @param offset Subarray start index.
    /// @param len Subarray length.
    ASPOSECPP_SHARED_API String(const ArrayPtr<char16_t>& arr, int offset, int len);

    /// Destructor.
    ASPOSECPP_SHARED_API ~String();

    /// Returns ICU-styled null-terminated buffer. May reallocate the string.
    /// @return Pointer to null-terminated string buffer.
    ASPOSECPP_SHARED_API const UChar* u_str() const;

    /// Returns pointer to the beginning of actual string buffer. Never reallocates anything. Doesn't guarantee buffer to be null-terminated.
    /// @return Pointer to actual string buffer, null-terminated or not.
    ASPOSECPP_SHARED_API const UChar* begin() const;
    /// Returns pointer to the end of actual string buffer. Never reallocates anything. Doesn't guarantee buffer to be null-terminated.
    /// @return Pointer to the first element after actual string buffer, null-terminated or not.
    ASPOSECPP_SHARED_API const UChar* end() const;

    /// Returns reverse iterator to the last character (if any) of actual string buffer.
    /// @return Reverse iterator to the last character of actual string buffer (if any) or same as rend().
    ASPOSECPP_SHARED_API reverse_iterator rbegin() const;
    /// Returns reverse iterator to the before first character (if any) of actual string buffer.
    /// @return Reverse iterator to the element preceding first character of actual string buffer (if any) or to element just before allocated buffer.
    ASPOSECPP_SHARED_API reverse_iterator rend() const;

    /// Checks if string is empty or is considered null.
    /// @return true if string is empty or null, false otherwise.
    ASPOSECPP_SHARED_API bool IsNullOrEmpty() const;

    /// Checks if string is considered null.
    /// String is null and only if it is constructed via String() constructor, moved, copied or assigned from null string or reset() method was called.
    /// @return true if string is considered null, false otherwise.
    inline bool IsNull() const { return m_state == state_null; }

    /// Checks if string is both non-null and empty.
    /// @return true if string is empty and not null, false otherwise.
    ASPOSECPP_SHARED_API bool IsEmpty() const;

    /// Converts string to std::string. Uses UTF-8 encoding.
    /// @return String representation in utf-8.
    ASPOSECPP_SHARED_API std::string ToUtf8String() const;
    /// Converts string to std::wstring.
    /// @return Original string converted to wstring.
    ASPOSECPP_SHARED_API std::wstring ToWCS() const;
    /// Converts string to std::u16string.
    /// @return Original string converted to u16string.
    ASPOSECPP_SHARED_API std::u16string ToU16Str() const;
    /// Converts string to std::u32string.
    /// @return Original string converted to u32string.
    ASPOSECPP_SHARED_API std::u32string ToU32Str() const;
    /// Converts string to std::string. Uses ASCII encoding.
    /// @return String representation in Ascii.
    /// @throw FormatException if a string contains non-ASCII characters.
    ASPOSECPP_SHARED_API std::string ToAsciiString() const;

    /// Sets string to null. Is analogous to 'string_variable_name = null' in C#.
    /// @return Self reference.
    ASPOSECPP_SHARED_API String& reset();

    /// Gets string length.
    /// @return Length of contained string.
    ASPOSECPP_SHARED_API int get_Length() const;
    /// Gets character at specified position.
    /// @param index Index to get character from.
    /// @return Character at specified position or 0xffff if out of bounds.
    ASPOSECPP_SHARED_API char_t operator[](int index) const;
    /// Sets character at specified position.
    /// @param index Index to set character at.
    /// @param ch Character to put at specified position.
    /// @return Self reference.
    ASPOSECPP_SHARED_API String& SetCharAt(int index, char_t ch);

    /// Assignment operator.
    /// @param str String to copy.
    /// @return Self reference.
    ASPOSECPP_SHARED_API String& operator=(const String& str);
    /// Move assignment operator.
    /// @param str String to move data from.
    /// @return Self reference.
    ASPOSECPP_SHARED_API String& operator=(String&& str) noexcept;

    /// String concatenation operator.
    /// @param str String to add to the end of current one.
    /// @return Concatenated string.
    ASPOSECPP_SHARED_API String operator+(const String& str) const;
    /// String concatenation with string literal or character string pointer.
    /// @tparam T One of string literal or character string pointer forms.
    /// @param arg Entity to concatenate with current string.
    /// @return Concatenated string.
    template <typename T, std::enable_if_t<IsStringLiteral<T, char_t>::value>* = nullptr>
    String operator+(const T& arg) const
    {
        return *this + String(arg, std::extent<T>::value - 1);
    }

    /// Adds character to the end of the string.
    /// @param x Character to add.
    /// @return String concatenation result.
    ASPOSECPP_SHARED_API String operator+(char_t x) const;
    /// Adds integer value string representation to the end of the string.
    /// @param i Integer value to convert to string and to add.
    /// @return String concatenation result.
    ASPOSECPP_SHARED_API String operator+(int i) const;
    /// Adds unsigned integer value string representation to the end of the string.
    /// @param i Value to convert to string and to add.
    /// @return String concatenation result.
    ASPOSECPP_SHARED_API String operator+(uint32_t i) const;
    /// Adds floating point value string representation to the end of the string.
    /// @param d Value to convert to string and to add.
    /// @return String concatenation result.
    ASPOSECPP_SHARED_API String operator+(double d) const;
    /// Adds integer value string representation to the end of the string.
    /// @param v Value to convert to string and to add to add.
    /// @return String concatenation result.
    ASPOSECPP_SHARED_API String operator+(int64_t v) const;
    /// Adds reference type object string representation to the end of the string.
    /// @tparam T pointer type.
    /// @param value Object to convert to string using ToString() call and to add to current string.
    /// @return String concatenation result.
    template <typename T, std::enable_if_t<IsSmartPtr<T>::value>* = nullptr>
    String operator+(const T& value) const
    {
        return value == nullptr ? *this : *this + value->ToString();
    }
    /// Adds value type object string representation to the end of the string.
    /// @tparam T Value type to call ToString() upon.
    /// @param value Object to convert to string using ToString() call and to add to current string.
    /// @return String concatenation result.
    template <typename T, std::enable_if_t<!IsSmartPtr<T>::value && !std::is_scalar<T>::value && !std::is_array<T>::value>* = nullptr>
    String operator+(const T& value) const
    {
        return *this + value.ToString();
    }
    /// Adds boolean value string representation to the end of the string.
    /// @tparam T Value type to concatenate with string. Must be bool
    /// @param arg Boolean value to convert to string and to add.
    /// @return String concatenation result.
    template <typename T, std::enable_if_t<std::is_same<T, bool>::value>* = nullptr>
    String operator+(T arg) const
    {
        return String(*this).AddBoolImpl(arg);
    }

    /// Concatenation assignment operator.
    /// @param c Character to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(char_t c);
    /// Concatenation assignment operator.
    /// @param str String to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(const String& str);
    /// Concatenation assignment operator.
    /// @param value Double to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(double value);
    /// Concatenation assignment operator.
    /// @param value Byte to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(uint8_t value);
    /// Concatenation assignment operator.
    /// @param value Short to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(int16_t value);
    /// Concatenation assignment operator.
    /// @param value Unsigned short to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(uint16_t value);
    /// Concatenation assignment operator.
    /// @param value Int to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(int32_t value);
    /// Concatenation assignment operator.
    /// @param value Unsigned int to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(uint32_t value);
    /// Concatenation assignment operator.
    /// @param value Long to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(int64_t value);
    /// Concatenation assignment operator.
    /// @param value Unsigned long to add to the end of current string.
    /// @return self reference.
    ASPOSECPP_SHARED_API String& operator+=(uint64_t value);
    /// Concatenation assignment operator.
    /// @tparam T Value type to concatenate with string. Must be bool
    /// @param value Boolean to add to the end of current string.
    /// @return self reference.
    template <typename T, std::enable_if_t<std::is_same<T, bool>::value>* = nullptr>
    String& operator+=(T value)
    {
        return AddBoolImpl(value);
    }

    /// Equality comparison operator.
    /// @param str String to compare current one to.
    /// @return true if both strings are null or both are not null and match, false otherwise.
    ASPOSECPP_SHARED_API bool operator==(const String& str) const;
    /// Checks if string is null. Applies same logic as IsNull() call.
    /// @return true if string is null, false otherwise.
    ASPOSECPP_SHARED_API bool operator==(std::nullptr_t) const;


    /// Non-equality comparison operator.
    /// @param str String to compare current one to.
    /// @return false if both strings are null or both are not null and match, true otherwise.
    ASPOSECPP_SHARED_API bool operator!=(const String& str) const;
    /// Checks if string is not null. Applies same logic as IsNull() call.
    /// @return false if string is null, true otherwise.
    ASPOSECPP_SHARED_API bool operator!=(std::nullptr_t) const;

    /// Order-compares strings.
    /// @param str String to compare current one to.
    /// @return true if this is considering less than str, false otherwise.
    ASPOSECPP_SHARED_API bool operator<(const String& str) const;

    /// Order-compares strings.
    /// @param str String to compare current one to.
    /// @return true if this is considering more than str, false otherwise.
    ASPOSECPP_SHARED_API bool operator>(const String& str) const;

    /// Implicit conversion from Aspose System::String to std::string.
    /// @return std::string in format UTF-8
    explicit operator std::string() const
    {
        return ToUtf8String();
    }
    /// Implicit conversion from Aspose System::String to std::wstring.
    /// @return std::wstring
    explicit operator std::wstring() const
    {
        return ToWCS();
    }
    /// Implicit conversion from Aspose System::String to std::u16string.
    /// @return std::u16string
    explicit operator std::u16string() const
    {
        return ToU16Str();
    }
    /// Implicit conversion from Aspose System::String to std::u32string.
    /// @return std::u32string
    explicit operator std::u32string() const
    {
        return ToU32Str();
    }

    /// Creates a copy of current string.
    /// @return Full copy of current string which is never null.
    ASPOSECPP_SHARED_API String Clone() const;

    /// Wrapper for handling String class in contexts where ToString() is being called on value type objects.
    /// @return Copy of current string. It is considered a null string if current string is a null string.
    String ToString() const { return *this; }
    /// Wrapper for handling String class in contexts where ToString() is being called on value type objects.
    /// @return Copy of current string. It is considered a null string if current string is a null string.
    String ToString(const SharedPtr<IFormatProvider>&) const { return *this; }

    /// Hashes contained string. Implemented in ICU, doesn't match hashes in C#.
    /// @return Calculated hash code value.
    ASPOSECPP_SHARED_API int GetHashCode() const;
    /// String equality comparison. Several modes provided by StringComparison enumeration are supported.
    /// @param str String to compare against the current one.
    /// @param comparison_type Comparison mode (see System::StringComparison for details).
    /// @return true if strings match using selected comparison type, false otherwise.
    ASPOSECPP_SHARED_API bool Equals(const String& str, System::StringComparison comparison_type) const;
    /// String equality comparison. Uses System::StringComparison::Ordinal comparison mode.
    /// @param str String to compare against the current one.
    /// @return true if strings match, false otherwise.
    ASPOSECPP_SHARED_API bool Equals(const String& str) const;

    /// Checks if str is a substring of current string.
    /// @param str Lookup string.
    /// @return true if substring is present, false otherwise.
    ASPOSECPP_SHARED_API bool Contains(const String& str) const;
    /// Checks if string contains given character.
    /// @param value Lookup character.
    /// @return true if character is present, false otherwise.
    ASPOSECPP_SHARED_API bool Contains(char16_t value) const;
    /// Compares two strings in 'less-equals-more' style. Uses current culture.
    /// @param str String to compare this to.
    /// @return Negative value if this is considered lower than str, zero if they match, positive value if this is greater than str.
    ASPOSECPP_SHARED_API int CompareTo(const String& str) const;
    /// Copies string characters into existing array elements. No resize is being done.
    /// @param sourceIndex In-string index to start reading from.
    /// @param destination Destination array.
    /// @param destinationIndex In-array index to start writing from.
    /// @param count Number of characters to copy.
    ASPOSECPP_SHARED_API void CopyTo(int sourceIndex, const ArrayPtr<char_t>& destination, int destinationIndex, int count) const;
    /// Normalizes unicode string using normalization form specified.
    /// @param form Normalization form, see System::Text::NormalizationForm for details.
    /// @return Normalized string.
    ASPOSECPP_SHARED_API String Normalize(System::Text::NormalizationForm form) const;
    /// Checks if unicode string is normalized using normalization form specified.
    /// @param form Normalization form, see System::Text::NormalizationForm for details.
    /// @return true if string is already normalized, false otherwise.
    ASPOSECPP_SHARED_API bool IsNormalized(System::Text::NormalizationForm form) const;

    /// Checks if string begins with specified substring.
    /// @param value Lookup string.
    /// @return true if string starts with specified substring, false otherwise.
    ASPOSECPP_SHARED_API bool StartsWith(const String& value) const;
    /// Checks if string begins with specified substring.
    /// @param value Lookup string.
    /// @param comparisonType Comparison mode, see System::StringComparison for details.
    /// @return true if string starts with specified substring, false otherwise.
    ASPOSECPP_SHARED_API bool StartsWith(const String& value, System::StringComparison comparisonType) const;
    /// Checks if string begins with specified substring.
    /// @param value Lookup string.
    /// @param ignoreCase Specifies whether comparison is case-insensitive.
    /// @param culture Culture to use while performing string comparison.
    /// @return true if string starts with specified substring, false otherwise.
    ASPOSECPP_SHARED_API bool StartsWith(const String& value, bool ignoreCase, const SharedPtr<System::Globalization::CultureInfo>& culture = nullptr) const;

    /// Checks if string ends with specified substring.
    /// @param value Lookup string.
    /// @return true if string ends with specified substring, false otherwise.
    ASPOSECPP_SHARED_API bool EndsWith(const String& value) const;
    /// Checks if string ends with specified substring.
    /// @param value Lookup string.
    /// @param comparisonType Comparison mode, see System::StringComparison for details.
    /// @return true if string ends with specified substring, false otherwise.
    ASPOSECPP_SHARED_API bool EndsWith(const String& value, System::StringComparison comparisonType) const;
    /// Checks if string ends with specified substring.
    /// @param value Lookup string.
    /// @param ignoreCase Specifies whether comparison is case-insensitive.
    /// @param culture Culture to use while performing string comparison.
    /// @return true if string ends with specified substring, false otherwise.
    ASPOSECPP_SHARED_API bool EndsWith(const String& value, bool ignoreCase, const SharedPtr<System::Globalization::CultureInfo>& culture = nullptr) const;

    /// Converts string or substring to array of characters.
    /// @param startIndex Substring start index.
    /// @param length Substring length.
    /// @return Array containing characters of the string.
    ASPOSECPP_SHARED_API ArrayPtr<char_t> ToCharArray(int32_t startIndex = 0, int32_t length = INT32_MAX) const;
    /// Converts string or substring to array of bytes.
    /// @param startIndex Substring start index.
    /// @param length Substring length.
    /// @param LE If true, encode characters using little endianness; otherwise, use big endianness.
    /// @return Array containing bytes representing characters of the string.
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> ToByteArray(int32_t startIndex = 0, int32_t length = INT32_MAX, bool LE = true) const;

    /// Converts all string's characters to upper case.
    /// @return Converted string.
    ASPOSECPP_SHARED_API String ToUpper() const;
    /// Converts all string's characters to lower case.
    /// @return Converted string.
    ASPOSECPP_SHARED_API String ToLower() const;

    /// Converts all string's characters to lower case using specific culture.
    /// @param cultureInfo Culture to use.
    /// @return Converted string.
    ASPOSECPP_SHARED_API String ToLower(const SharedPtr<System::Globalization::CultureInfo>& cultureInfo) const;
    /// Converts all string's characters to upper case using specific culture.
    /// @param cultureInfo Culture to use.
    /// @return Converted string.
    ASPOSECPP_SHARED_API String ToUpper(const SharedPtr<System::Globalization::CultureInfo>& cultureInfo) const;

    /// Converts all string's characters to upper case using invariant culture.
    /// @return Converted string.
    ASPOSECPP_SHARED_API String ToUpperInvariant() const;
    /// Converts all string's characters to lower case using invariant culture.
    /// @return Converted string.
    ASPOSECPP_SHARED_API String ToLowerInvariant() const;

    /// Extracts substring.
    /// @param startIndex Substring start index.
    /// @return Extracted substring.
    ASPOSECPP_SHARED_API String Substring(int32_t startIndex) const;
    /// Extracts substring.
    /// @param startIndex Substring start index.
    /// @param length Substring length.
    /// @return Extracted substring.
    ASPOSECPP_SHARED_API String Substring(int32_t startIndex, int32_t length) const;
    /// Extracts everything but substring from current string.
    /// @param startIndex Index of first character to not extract.
    /// @param count Number of characters to not extract.
    /// @return String around specified substring.
    ASPOSECPP_SHARED_API String Remove(int32_t startIndex, int32_t count = INT32_MAX) const;

    /// Checks if string object is of type specified by TypeInfo passed.
    /// @param target TypeInfo to check against.
    /// @return true if target is TypeInfo of String class, false otherwise.
    bool Is(const System::TypeInfo &target) const
    {
        return GetType() == target;
    }

    // Finds

    /// Substring forward lookup.
    /// @param str Substring to look for.
    /// @param comparison_type Comparison mode.
    /// @return Index of first found substring or -1 if not found. For empty lookup string, always returns 0.
    ASPOSECPP_SHARED_API int IndexOf(const String& str, System::StringComparison comparison_type) const;
    /// Character forward lookup.
    /// @param c Character to look for.
    /// @param startIndex Index to start lookup at.
    /// @return Index of first character position since startIndex or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOf(char_t c, int startIndex = 0) const;
    /// Character forward lookup in substring.
    /// @param c Character to look for.
    /// @param startIndex Index to start lookup at.
    /// @param count Number of characters to look through.
    /// @return Index of first character position since startIndex or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOf(char_t c, int startIndex, int count) const;
    /// Substring forward lookup.
    /// @param str Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @return Index of first found substring or -1 if not found. For empty lookup string, always returns startIndex.
    ASPOSECPP_SHARED_API int IndexOf(const String& str, int startIndex = 0) const;
    /// Substring forward lookup.
    /// @param str Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @param comparison_type Comparison mode.
    /// @return Index of first found substring or -1 if not found. For empty lookup string, always returns startIndex.
    ASPOSECPP_SHARED_API int IndexOf(const String& str, int startIndex, System::StringComparison comparison_type) const;
    /// Substring forward lookup.
    /// @param value Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @param count number of characters to look through.
    /// @param comparisonType Comparison mode.
    /// @return Index of first found substring or -1 if not found. For empty lookup string, always returns startIndex.
    ASPOSECPP_SHARED_API int IndexOf(const String& value, int startIndex, int count, System::StringComparison comparisonType) const;
    /// Substring forward lookup.
    /// @param str Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @param count number of characters to look through.
    /// @return Index of first found substring or -1 if not found. For empty lookup string, always returns startIndex.
    ASPOSECPP_SHARED_API int IndexOf(const String& str, int startIndex, int count) const;

    /// Character forward lookup.
    /// @param c Character to look for.
    /// @param startIndex Index to start lookup at.
    /// @return Index of first character position since startIndex or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOfAny(char_t c, int startIndex = 0) const;
    /// Consequently looks for all characters of str in this. If first character is found, its position is returned, otherwise looks for the second one and so on.
    /// @param str String of characters to look for. Order of characters matters.
    /// @param startIndex Position to start lookup from.
    /// @return Index of first found character or -1 if none is found.
    ASPOSECPP_SHARED_API int IndexOfAny(const String& str, int startIndex = 0) const;
    /// Looks for any of passed characters through the whole string. Compares first string character to all characters in anyOf, then compares second one and so on.
    /// Returns index of the first one matching any of the target characters.
    /// @param anyOf Array of characters to look for. Order doesn't matter.
    /// @return Index of the first matching character or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOfAny(const ArrayPtr<char_t>& anyOf) const;
    /// Looks for any of passed characters through substring. Compares first string character to all characters in anyOf, then compares second one and so on.
    /// Returns index of the first one matching any of the target characters.
    /// @param anyOf Array of characters to look for. Order doesn't matter.
    /// @param startindex Index to start lookup from.
    /// @return Index of the first matching character or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOfAny(const ArrayPtr<char_t>& anyOf, int32_t startindex) const;
    /// Looks for any of passed characters through substring. Compares first string character to all characters in anyOf, then compares second one and so on.
    /// Returns index of the first one matching any of the target characters.
    /// @param anyOf Array of characters to look for. Order doesn't matter.
    /// @param startindex Index to start lookup from.
    /// @param count Number of characters to look through.
    /// @return Index of the first matching character or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOfAny(const ArrayPtr<char_t>& anyOf, int32_t startindex, int32_t count) const;
                
    /// Substring backward lookup.
    /// @param str Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @return Index of last found substring or -1 if not found. For empty lookup string, always returns string length.
    ASPOSECPP_SHARED_API int LastIndexOf(const String& str, int startIndex = INT32_MAX) const;
    /// Substring backward lookup.
    /// @param str Substring to look for.
    /// @param comparison_type Comparison mode.
    /// @return Index of last found substring or -1 if not found. For empty lookup string, always returns string length.
    ASPOSECPP_SHARED_API int LastIndexOf(const String& str, System::StringComparison comparison_type) const;
    /// Substring backward lookup.
    /// @param str Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @param comparison_type Comparison mode.
    /// @return Index of last found substring or -1 if not found. For empty lookup string, always returns string length.
    ASPOSECPP_SHARED_API int LastIndexOf(const String& str, int startIndex, System::StringComparison comparison_type) const;
    /// Substring backward lookup.
    /// @param value Substring to look for.
    /// @param startIndex Position in source string to start lookup through.
    /// @param count Number of characters to look through.
    /// @param comparisonType Comparison mode.
    /// @return Index of last found substring or -1 if not found. For empty lookup string, always returns startIndex+count.
    ASPOSECPP_SHARED_API int LastIndexOf(const String& value, int startIndex, int count, StringComparison comparisonType) const;

    /// Character backward lookup.
    /// @param value Character to look for.
    /// @return Index of last character position or -1 if not found.
    ASPOSECPP_SHARED_API int LastIndexOf(char_t value) const;
    /// Character backward lookup.
    /// @param value Character to look for.
    /// @param startIndex Index to start lookup at.
    /// @return Index of last character position since startIndex or -1 if not found.
    ASPOSECPP_SHARED_API int LastIndexOf(char_t value, int32_t startIndex) const;
    /// Character backward lookup.
    /// @param value Character to look for.
    /// @param startIndex Index to start lookup at.
    /// @param count Number of characters to look through
    /// @return Index of last character position since startIndex or -1 if not found.
    ASPOSECPP_SHARED_API int LastIndexOf(char_t value, int32_t startIndex, int32_t count) const;

    /// Looks for any of passed characters through whole string backwardly. Compares last string character to all characters in anyOf, then compares previous one and so on.
    /// Returns index of the first match found.
    /// @param anyOf Array of characters to look for. Order doesn't matter.
    /// @return Index of the last matching character or -1 if not found.
    ASPOSECPP_SHARED_API int LastIndexOfAny(const ArrayPtr<char_t>& anyOf) const;
    /// Looks for any of passed characters through substring backwardly. Compares last string character to all characters in anyOf, then compares previous one and so on.
    /// Returns index of the first match found.
    /// @param anyOf Array of characters to look for. Order doesn't matter.
    /// @param startindex Index to start lookup from.
    /// @return Index of the last matching character or -1 if not found.
    ASPOSECPP_SHARED_API int LastIndexOfAny(const ArrayPtr<char_t>& anyOf, int32_t startindex) const;
    /// Looks for any of passed characters through substring backwardly. Compares last string character to all characters in anyOf, then compares previous one and so on.
    /// Returns index of the first match found.
    /// @param anyOf Array of characters to look for. Order doesn't matter.
    /// @param startindex Index to start lookup from.
    /// @param count Number of characters to look through.
    /// @return Index of the last matching character or -1 if not found.
    ASPOSECPP_SHARED_API int LastIndexOfAny(const ArrayPtr<char_t>& anyOf, int32_t startindex, int32_t count) const;

    // Trim

    /// Removes all whitespace characters from both beginning and end of the string.
    /// @return String with no whitespaces at beginning or end.
    ASPOSECPP_SHARED_API String Trim() const;
    /// Removes all occurrences of passed character from both beginning and end of the string.
    /// @param ch Symbol to remove.
    /// @return Removal result.
    ASPOSECPP_SHARED_API String Trim(char_t ch) const;
    /// Removes all occurrences of passed characters from both beginning and end of the string.
    /// @param anyOf String of characters to remove.
    /// @return String without removed characters.
    ASPOSECPP_SHARED_API String Trim(const String& anyOf) const;
    /// Removes all occurrences of passed characters from both beginning and end of the string.
    /// @param anyOf Array of characters to remove.
    /// @return String without removed characters.
    ASPOSECPP_SHARED_API String Trim(const ArrayPtr<char_t>& anyOf) const;

    /// Removes all whitespace characters from beginning of the string.
    /// @return String with no whitespaces at beginning.
    ASPOSECPP_SHARED_API String TrimStart() const;
    /// Removes all occurrences of passed character from beginning of the string.
    /// @param ch Symbol to remove.
    /// @return Removal result.
    ASPOSECPP_SHARED_API String TrimStart(char_t ch) const;
    /// Removes all occurrences of passed characters from beginning of the string.
    /// @param anyOf String of characters to remove.
    /// @return String without removed characters.
    ASPOSECPP_SHARED_API String TrimStart(const String& anyOf) const;
    /// Removes all occurrences of passed characters from beginning of the string.
    /// @param anyOf Array of characters to remove.
    /// @return String without removed characters.
    ASPOSECPP_SHARED_API String TrimStart(const ArrayPtr<char_t>& anyOf) const;

    /// Removes all whitespace characters from end of the string.
    /// @return String with no whitespaces at beginning.
    ASPOSECPP_SHARED_API String TrimEnd() const;
    /// Removes all occurrences of passed character from end of the string.
    /// @param ch Symbol to remove.
    /// @return Removal result.
    ASPOSECPP_SHARED_API String TrimEnd(char_t ch) const;
    /// Removes all occurrences of passed characters from end of the string.
    /// @param anyOf String of characters to remove.
    /// @return String without removed characters.
    ASPOSECPP_SHARED_API String TrimEnd(const String& anyOf) const;
    /// Removes all occurrences of passed characters from end of the string.
    /// @param anyOf Array of characters to remove.
    /// @return String without removed characters.
    ASPOSECPP_SHARED_API String TrimEnd(const ArrayPtr<char_t>& anyOf) const;

    /// Adds padding on the left of original string.
    /// @param totalWidth Number of padding characters to insert.
    /// @param c Padding character.
    /// @return String with padding inserted.
    ASPOSECPP_SHARED_API String PadLeft(int totalWidth, char_t c = u' ') const;
    /// Adds padding on the right of original string.
    /// @param totalWidth Number of padding characters to insert.
    /// @param c Padding character.
    /// @return String with padding inserted.
    ASPOSECPP_SHARED_API String PadRight(int totalWidth, char_t c = u' ') const;

    // Replace

    /// Replaces all occurrences of character in the string.
    /// @param oldValue Character to replace.
    /// @param newValue replacement value.
    /// @returns String with replacement done.
    ASPOSECPP_SHARED_API String Replace(char_t oldValue, char_t newValue) const;
    /// Replaces all occurrences of lookup in this string.
    /// @param oldValue String to replace.
    /// @param newValue replacement string.
    /// @returns String with replacement done.
    ASPOSECPP_SHARED_API String Replace(const String& oldValue, const String& newValue) const;

    // Insert

    /// Inserts substring at specified position
    /// @param startIndex Index in this string to start inserting from.
    /// @param value Insertion string.
    /// @return String with insertion done.
    ASPOSECPP_SHARED_API String Insert(int startIndex, const String& value) const;

    // Split
    /// Splits string by character.
    /// @param separator Character to split string by.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(char_t separator = u' ', StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by character.
    /// @param separator Character to split string by.
    /// @param count The maximum number of substrings to return.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(char_t separator, int32_t count, StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by one of two characters.
    /// @param separatorA First character to split string by.
    /// @param separatorB Second character to split string by.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(char_t separatorA, char_t separatorB, StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by one of characters specified.
    /// @param separators Array of separator characters. If empty, any whitespace character is considered a separator.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(const ArrayPtr<char_t>& separators, StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by one of characters specified.
    /// @param separators Array of separator characters. If empty, any whitespace character is considered a separator.
    /// @param count The maximum number of substrings to return.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(const ArrayPtr<char_t>& separators, int32_t count, StringSplitOptions opt = StringSplitOptions::None) const;

    /// Splits string by substring.
    /// @param separator Substring acting as separator. If empty, whitespace character acts as separator.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(const String& separator, StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by substring.
    /// @param separator Substring acting as separator. If empty, whitespace character acts as separator.
    /// @param count Max number of elements in splits array.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(const String& separator, int count, StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by substring.
    /// @param separators Array of separator strings. If empty, no splitting is done.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(const ArrayPtr<String>& separators, StringSplitOptions opt = StringSplitOptions::None) const;
    /// Splits string by substring. Currently, only supports separators array of zero or one elements.
    /// @param separators Array of separator strings. If empty, no splitting is done.
    /// @param count Max number of elements in splits array.
    /// @param opt Splitting options.
    /// @return Array of substrings.
    ASPOSECPP_SHARED_API ArrayPtr<String> Split(const ArrayPtr<String>& separators, int count, StringSplitOptions opt = StringSplitOptions::None) const;

    // static members

    /// Empty string.
    static const ASPOSECPP_SHARED_API String Empty;
    /// Null string.
    static const ASPOSECPP_SHARED_API String Null;

    /// Checks if passed string is null or empty.
    /// @param str String to check.
    /// @return true if string is null or empty, false otherwise.
    static ASPOSECPP_SHARED_API bool IsNullOrEmpty(const String& str);
    /// Indicates whether a specified string is null, empty, or consists only of white-space characters.
    /// @param str String to check.
    /// @return true if string is null or empty or consists exclusively of white-space characters, false otherwise.
    static ASPOSECPP_SHARED_API bool IsNullOrWhiteSpace(const String& str);
    /// Equal-compares two strings using Ordial comparison mode.
    /// @param strA First string to compare.
    /// @param strB Second string to compare.
    /// @return true if strings match, false otherwise.
    static ASPOSECPP_SHARED_API bool Equals(const String& strA, const String& strB);
    /// Equal-compares two strings.
    /// @param strA First string to compare.
    /// @param strB Second string to compare.
    /// @param comparison_type Comparison mode.
    /// @return true if strings match, false otherwise.
    static ASPOSECPP_SHARED_API bool Equals(const String& strA, const String& strB, System::StringComparison comparison_type);

    /// Less-equal-greater-compares two substrings.
    /// @param strA First string to compare.
    /// @param indexA Beginning of first string substring.
    /// @param strB Second string to compare.
    /// @param indexB Beginning of the second string substring.
    /// @param length Number of characters to compare.
    /// @param ignoreCase Specifies whether comparison is case-insensitive.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int Compare(const String& strA, int indexA, const String& strB, int indexB,
                                            int length, bool ignoreCase = false);

    /// Less-equal-greater-compares two substrings.
    /// @param strA First string to compare.
    /// @param indexA Beginning of first string substring.
    /// @param strB Second string to compare.
    /// @param indexB Beginning of the second string substring.
    /// @param length Number of characters to compare.
    /// @param ignoreCase Specifies whether comparison is case-insensitive.
    /// @param ci Culture to use for comparison.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int Compare(const String& strA, int indexA, const String& strB, int indexB,
                                            int length, bool ignoreCase,
                                            const SharedPtr<System::Globalization::CultureInfo>& ci);

    /// Less-equal-greater-compares two strings.
    /// @param strA First string to compare.
    /// @param strB Second string to compare.
    /// @param comparison_type Comparison mode.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int Compare(const String& strA, const String& strB, System::StringComparison comparison_type);
    /// Less-equal-greater-compares two strings.
    /// @param strA First string to compare.
    /// @param indexA Beginning of first string substring.
    /// @param strB Second string to compare.
    /// @param indexB Beginning of the second string substring.
    /// @param length Number of characters to compare.
    /// @param comparison_type Comparison mode.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int Compare(const String& strA, int indexA, const String& strB, int indexB,
                                            int length, System::StringComparison comparison_type);

    /// Less-equal-greater-compares two strings.
    /// @param strA First string to compare.
    /// @param strB Second string to compare.
    /// @param ignoreCase Specifies whether comparison is case-insensitive.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int Compare(const String& strA, const String& strB, bool ignoreCase = false);
    /// Less-equal-greater-compares two strings.
    /// @param strA First string to compare.
    /// @param strB Second string to compare.
    /// @param ignoreCase Specifies whether comparison is case-insensitive.
    /// @param ci Culture to use for comparison.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int Compare(const String& strA, const String& strB, bool ignoreCase,
                                            const SharedPtr<System::Globalization::CultureInfo>& ci);

    /// Less-equal-greater-compares two strings using ordinal mode.
    /// @param strA First string to compare.
    /// @param strB Second string to compare.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int CompareOrdinal(const String& strA, const String& strB);
    /// Less-equal-greater-compares two strings using ordinal mode.
    /// @param strA First string to compare.
    /// @param indexA Beginning of first string substring.
    /// @param strB Second string to compare.
    /// @param indexB Beginning of the second string substring.
    /// @param length Number of characters to compare.
    /// @return Negative value if first substring is less then second, zero if they match, positive value otherwise.
    static ASPOSECPP_SHARED_API int CompareOrdinal(const String& strA, int indexA, const String& strB, int indexB, int length);

    /// Joins array using string as separator.
    /// @param separator String to put between array elements when joining them.
    /// @param parts Array of parts to join.
    /// @param startIndex First index in array to start joining from.
    /// @param count Number of array elements to join. -1 means 'until array ends'.
    /// @return String representing joint array elements.
    static ASPOSECPP_SHARED_API String Join(const String& separator, const ArrayPtr<String>& parts, int startIndex = 0, int count = -1);

    /// Joins array using string as separator.
    /// @param separator String to put between array elements when joining them.
    /// @param parts ArrayView of parts to join.
    /// @param startIndex First index in array to start joining from.
    /// @param count Number of array elements to join. -1 means 'until array ends'.
    /// @return String representing joint array elements.
    static ASPOSECPP_SHARED_API String Join(const String& separator, const System::Details::ArrayView<String>& parts, int startIndex = 0, int count = -1);

    /// Joins array using string as separator.
    /// @param separator String to put between array elements when joining them.
    /// @param parts - parts enumerable object    
    /// @return String representing joint elements.
    static ASPOSECPP_SHARED_API String Join(const String& separator, const SharedPtr<System::Collections::Generic::IEnumerable<String> >& parts);

    /// Joins array using string as separator.
    /// @param separator String to put between array elements when joining them.
    /// @param parts Array of parts to join.   
    /// @return String representing joint elements.
    static ASPOSECPP_SHARED_API String Join(const String& separator, const ArrayPtr<SharedPtr<Object>>& parts);

    /// Concatenates strings.
    /// @param parts Strings to concatenate.
    /// @return String containing concatenated strings.
    static ASPOSECPP_SHARED_API String Concat(const ArrayPtr<String>& parts);
    /// Concatenates strings.
    /// @param str0 First string to concatenate.
    /// @param str1 Second string to concatenate.
    /// @return String containing concatenated strings.
    static ASPOSECPP_SHARED_API String Concat(const String & str0, const String & str1);
    /// Concatenates strings.
    /// @param str0 First string to concatenate.
    /// @param str1 Second string to concatenate.
    /// @param str2 Third string to concatenate.
    /// @return String containing concatenated strings.
    static ASPOSECPP_SHARED_API String Concat(const String & str0, const String & str1, const String & str2);

    /// Concatenates strings.
    /// @param str0 First string to concatenate.
    /// @param str1 Second string to concatenate.
    /// @param str2 Third string to concatenate.
    /// @param str3 Fourth string to concatenate.
    /// @return String containing concatenated strings.
    static ASPOSECPP_SHARED_API String Concat(const String& str0, const String& str1, const String& str2, const String& str3);

    /// Creates string copy.
    /// @param str String to copy.
    /// @return Copy of passed string.
    static String Copy(const String& str) { return str; }

    /// Formats string in C# style.
    /// @tparam Args Arguments to format string.
    /// @param fp Format provider to use to convert arguments to strings.
    /// @param format Format string.
    /// @param args Arguments to format string.
    template<class... Args>
    static String Format(const SharedPtr<IFormatProvider>& fp, const String& format, const Args&... args);

    /// Formats string in C# style.
    /// @tparam Args Arguments to format string.
    /// @param format Format string.
    /// @param args Arguments to format string.
    template<class... Args>
    static String Format(std::nullptr_t, const String& format, const Args&... args);

    /// Formats string in C# style.
    /// @tparam Args Arguments to format string.
    /// @param format Format string.
    /// @param args Arguments to format string.
    template<std::size_t N, class... Args>
    static String Format(std::nullptr_t, const char16_t(&format)[N], const Args&... args);

    /// Formats string in C# style.
    /// @tparam Args Arguments to format string.
    /// @param format Format string.
    /// @param args Arguments to format string.
    template<class... Args>
    static String Format(const String& format, const Args&... args);

    /// Formats string in C# style.
    /// @tparam T Arguments to format string.
    /// @param format Format string.
    /// @param args Arguments to format string.
    template<class T>
    static String Format(const String& format, const System::ArrayPtr<T>& args);

    /// Creates String from utf8 string.
    /// @param utf8 Pointer to null-terminated string encoded using utf8 codepage.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromUtf8(const char* utf8);
    /// Creates String from utf8 string.
    /// @param utf8 Pointer to string encoded using utf8 codepage.
    /// @param len Number of characters to handle.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromUtf8(const char* utf8, int len);
    /// Creates String from utf8 string.
    /// @param utf8 Pointer to null-terminated string encoded using utf8 codepage.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromUtf8(const uint8_t* utf8);
    /// Creates String from utf8 string.
    /// @param utf8 Pointer to string encoded using utf8 codepage.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromUtf8(const std::string& utf8);
    /// Creates String from widestring.
    /// @param wcs Widestring to convert into String.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromWCS(const std::wstring& wcs);
    /// Creates String from utf32 string.
    /// @param utf32 Pointer to string encoded in utf32.
    /// @param length Number of characters to convert.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromUtf32(const uint32_t *utf32, int32_t length);
    /// Creates String from utf16 string.
    /// @param u16str Utf16 string.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromUtf16(const std::u16string& u16str);
    /// Creates String from ASCII string.
    /// @param asciiStr Pointer to null-terminated string encoded using ASCII codepage.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromAscii(const char* asciiStr);
    /// Creates String from ASCII string.
    /// @param asciiStr Pointer to string encoded using ASCII codepage.
    /// @param len Number of characters to handle.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromAscii(const char* asciiStr, int len);
    /// Creates String from ASCII string.
    /// @param asciiStr ASCII-encoded string.
    /// @return String object representing passed string.
    static ASPOSECPP_SHARED_API String FromAscii(const std::string& asciiStr);

    /// Wraps UnicodeString into String.
    /// @param str UnicodeString to wrap into String.
    explicit ASPOSECPP_SHARED_API String(const codeporting_icu::UnicodeString& str);
    /// Move constructor.
    /// @param str UnicodeString to wrap into String.
    explicit ASPOSECPP_SHARED_API String(codeporting_icu::UnicodeString&& str) noexcept;
    /// Creates String from widestring.
    /// @param str Widestring to convert into String.
    explicit String(const std::wstring& str) : String(str.data(), ASPOSECPP_CHECKED_CAST(int, str.length())) {};
    /// Creates String from utf16 string.
    /// @param str Utf16 string to convert into String.
    explicit String(const std::u16string& str) : String(str.data(), ASPOSECPP_CHECKED_CAST(int, str.length())) {};
    /// Creates String from std::string string presented in format UTF-8.
    /// @param utf8str std::string string to convert into String.
    explicit ASPOSECPP_SHARED_API String(const std::string& utf8str);
    /// Creates String from std::u32string string.
    /// @param u32str std::u32string string to convert into String.
    explicit ASPOSECPP_SHARED_API String(const std::u32string& u32str);

    /// Indicates if a String contains ASCII symbols only.
    /// @return True if a string is an ASCII string.
    bool ASPOSECPP_SHARED_API IsAsciiString() const;

    /// Tries to convert a String to an ASCII string.
    /// @param buffer A buffer to store the resulting string.
    /// @param buffer_size Buffer's size.
    /// @return The resulting string length or -1 if a String is not an ASCII string.
    int ASPOSECPP_SHARED_API FastToAscii(char buffer[], int buffer_size) const;

protected:
    /// Puts some characters into string. Changes string size.
    /// @param src Pointer to string to insert.
    /// @param startIndex Index to start insertion at.
    /// @param count Number of characters to insert.
    ASPOSECPP_SHARED_API String& Append(const char16_t *src,
        int32_t startIndex,
        int32_t count);

    /// Actual string value
    mutable Detail::UnicodeStringHolder m_str; // mutable because of u_str

    /// String state.
    /// Contains value 0 if string is null,
    /// 1 if string is constructed from string literal.
    uintptr_t m_state;

#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__GNUC__))
        union IcuDebugHelper
        {
            struct
            {
                int16_t fLengthAndFlags;
                char16_t fBuffer[(int32_t)(64 - sizeof(void *) - 2) / 2];
            } fStackFields;
            struct
            {
                int16_t fLengthAndFlags;
                int32_t fLength;
                int32_t fCapacity;
                char16_t *fArray;
            } fFields;
        } static icuDebugHelper;
#endif

private:
    static bool StartsWithImpl(const String& that, const String& other, System::StringComparison comparisonType,
                               const SharedPtr<Globalization::CultureInfo>& culture);

    static bool EndsWithImpl(const String& that, const String& other, System::StringComparison comparisonType,
                             const SharedPtr<Globalization::CultureInfo>& culture);

    static int32_t CompareImpl(const String& strA, int32_t indexA, const String& strB, int32_t indexB,
                               int32_t length, StringComparison comparisonType,
                               const SharedPtr<Globalization::CultureInfo>& culture);

    static int LastIndexOfOrdinalIgnoreCaseImpl(const String& source, const String& value, int startIndex, int count);
    static int IndexOfOrdinalIgnoreCaseImpl(const String& source, const String& value, int startIndex, int count);

    ASPOSECPP_SHARED_API String& AddBoolImpl(bool value);

    static SharedPtr<Text::StringBuilder> GetBuilder();

    // Special ctor for literals
    ASPOSECPP_SHARED_API String(const char16_t* str, int length, uintptr_t state);

    inline void SetState()
    {
        m_state = reinterpret_cast<uintptr_t>(this);
    }

}; // class String

/// String concatenation
/// @tparam T String literal type.
/// @param left Literal to concatenate to string.
/// @param right String to concatenate.
/// @return Concatenated string.
template<typename T>
typename std::enable_if<IsStringLiteral<T, char_t>::value, String>::type  inline operator+(T&  left, const String& right)
{
    return String(left, std::extent<T>::value - 1) + right;
}

/// String concatenation
/// @tparam T String pointer type.
/// @param left String pointer to concatenate to string.
/// @param right String to concatenate.
/// @return Concatenated string.
template<typename T>
typename std::enable_if<IsStringPointer<T, char_t>::value, String>::type  inline operator+(T&  left, const String& right)
{
    return String(left) + right;
}


/// String concatenation
/// @param left Character to concatenate to string.
/// @param right String to concatenate.
/// @return Concatenated string.
String inline operator+(const char_t left, const String& right)
{
    return String(left, 1) + right;
}

/// String comparison.
/// @tparam Chars String literal type.
/// @param left String literal to compare.
/// @param right String to compare.
/// @return true if strings match, false otherwise.
template<class Chars, typename std::enable_if<IsStringLiteral<Chars, char_t>::value>::type* = nullptr>
bool inline operator==(Chars& left, const String& right)
{
    return String(left, std::extent<Chars>::value - 1) == right;
}

/// String comparison.
/// @tparam T String pointer type.
/// @param left String pointer to compare.
/// @param right String to compare.
/// @return true if strings match, false otherwise.
template<class T, typename std::enable_if<IsStringPointer<T, char_t>::value>::type* = nullptr>
bool inline operator==(T& left, const String& right)
{
    return String(left) == right;
}

/// String comparison.
/// @tparam Chars String literal type.
/// @param left String literal to compare.
/// @param right String to compare.
/// @return false if strings match, true otherwise.
template<class Chars, typename std::enable_if<IsStringLiteral<Chars, char_t>::value>::type* = nullptr>
bool inline operator!=(Chars& left, const String& right)
{
    return !(String(left, std::extent<Chars>::value - 1) == right);
}

/// String comparison.
/// @tparam T String pointer type.
/// @param left String pointer to compare.
/// @param right String to compare.
/// @return false if strings match, true otherwise.
template<class T, typename std::enable_if<IsStringPointer<T, char_t>::value>::type* = nullptr>
bool inline operator!=(T& left, const String& right)
{
    return !(String(left) == right);
}

/// Object and string comparison.
/// @param left Object to convert to string and compare.
/// @param right String to compare.
/// @return true if object string representation equals to string, false otherwise.
ASPOSECPP_SHARED_API bool operator==(const SharedPtr<Object>& left, const String& right);
/// Object and string comparison.
/// @param left Object to convert to string and compare.
/// @param right String to compare.
/// @return false if object string representation equals to string, true otherwise.
ASPOSECPP_SHARED_API bool operator!=(const SharedPtr<Object>& left, const String& right);

/// Checks if string is null.
/// @param str String to check.
/// @return true if string is null, false otherwise.
ASPOSECPP_SHARED_API bool operator==(std::nullptr_t, const String& str);
/// Checks if string is null.
/// @param str String to check.
/// @return false if string is null, true otherwise.
ASPOSECPP_SHARED_API bool operator!=(std::nullptr_t, const String& str);

/// Outputs a string to the output stream using UTF-8 encoding.
/// @param os An output stream object (instantiation of \c basic_ostream with \c char).
/// @param str A string to be sent to the output stream.
/// @return An output stream to which the string was added.
ASPOSECPP_SHARED_API std::ostream& operator<<(std::ostream& os, const String& str);
/// Outputs a string to the output stream.
/// @param os An output stream object (instantiation of \c basic_ostream with \c wchar_t).
/// @param str A string to be sent to the output stream.
/// @return An output stream to which the string was added.
ASPOSECPP_SHARED_API std::wostream& operator<<(std::wostream& os, const String& str);

/// Gets a string from the input streamusing UTF-8 encoding.
/// @param in An input stream object (instantiation of \c basic_ostream with \c char).
/// @param str A string to read from the input stream.
/// @return An input stream from which the string was extracted.
ASPOSECPP_SHARED_API std::istream& operator>>(std::istream &in, String &str);
/// Gets a string from the input stream.
/// @param in An input stream object (instantiation of \c basic_ostream with \c wchar_t).
/// @param str A string to read from the input stream.
/// @return An input stream from which the string was extracted.
ASPOSECPP_SHARED_API std::wistream& operator>>(std::wistream &in, String &str);

/// @cond
/// Specialization of CastResult for case of casting to string.
template <>
struct CastResult<String>
{
    /// An alias for a template argument of this template.
    typedef String type;
};
/// @endcond

/// Specialization of Object::ReferenceEquals for case of string and nullptr
/// @param str String to compare to nullptr.
/// @return true if string is null, false otherwise.
template <>
inline bool Object::ReferenceEquals(String const& str, std::nullptr_t)
{
    return str.IsNull();
}

/// Specialization of Object::ReferenceEquals for case of strings.
/// @param str1 First string to compare.
/// @param str2 Second string to compare.
/// @return true if strings match, false otherwise.
template <>
inline bool Object::ReferenceEquals(String const& str1, String const& str2)
{
    return str1.m_state == str2.m_state && (str1.m_state == String::state_null || str1 == str2);
}

/// Prints string to ostream. Mostly used for debug.
/// @param value to print.
/// @param os target ostream.
ASPOSECPP_SHARED_API void PrintTo(const System::String& value, std::ostream* os);


} // namespace System

// boost::hash specialization for System::String

namespace std
{
    /// Hasing algorithm for std::hash<System::String>
    template <>
    struct hash<System::String>
    {
        /// Generates hash for the specified value.
        /// @param str An object for which to generate a hash
        /// @returns A hash for @p str
        std::size_t operator()(const System::String& str) const
        {
            return static_cast<std::size_t>(str.GetHashCode());
        }
    };
}

/// Typedef used by CppPortConstStringAsWChar attribute
typedef char16_t* system_char_array;
/// Typedef used by CppPortConstStringAsWChar attribute
typedef char16_t const* const_system_char_array;

#include <system/details/format_builder.h>

namespace System {

/// Formats string in C# style.
/// @tparam Args Arguments to format string.
/// @param fp Format provider to use to convert arguments to strings.
/// @param format Format string.
/// @param args Arguments to format string.
template<class... Args>
String String::Format(const SharedPtr<IFormatProvider>& fp, const String& format, const Args&... args)
{
    System::Details::FormatBuilder builder(format, fp);
    System::Details::FormatBuilder::AddArguments(builder, args...);

    return builder.BuildResult();
}

/// Formats string in C# style.
/// @tparam Args Arguments to format string.
/// @param format Format string.
/// @param args Arguments to format string.
template<class... Args>
String String::Format(std::nullptr_t, const String& format, const Args&... args)
{
    System::Details::FormatBuilder builder(format);
    System::Details::FormatBuilder::AddArguments(builder, args...);

    return builder.BuildResult();
}

/// Formats string in C# style.
/// @tparam Args Arguments to format string.
/// @param format Format string.
/// @param args Arguments to format string.
template<std::size_t N, class... Args>
String String::Format(std::nullptr_t, const char16_t (&format)[N], const Args&... args)
{
    System::Details::FormatBuilder builder(format);
    System::Details::FormatBuilder::AddArguments(builder, args...);

    return builder.BuildResult();
}


/// Formats string in C# style.
/// @tparam Args Arguments to format string.
/// @param format Format string.
/// @param args Arguments to format string.
template<class... Args>
String String::Format(const String& format, const Args&... args)
{
    System::Details::FormatBuilder builder(format);
    System::Details::FormatBuilder::AddArguments(builder, args...);

    return builder.BuildResult();
}

/// Formats string in C# style.
/// @tparam T Arguments to format string.
/// @param format Format string.
/// @param args Arguments to format string.
template<class T>
String String::Format(const String& format, const System::ArrayPtr<T>& args)
{
    System::Details::FormatBuilder builder(format);
    System::Details::FormatBuilder::AddArguments(builder, args);

    return builder.BuildResult();
}
} // namespace System

#endif // _aspose_system_string_h_
