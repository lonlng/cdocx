/// @file net/cookie.h
#pragma once
#include <cstdint>
#include <system/array.h>
#include <system/collections/icomparer.h>
#include <system/date_time.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>

namespace System { namespace Net {

/// Enumerates the cookie specifications.
enum class CookieVariant
{
    /// The unknown cookie specification.
    Unknown,
    /// The plain cookie specification.
    Plain,
    /// The 'RFC 2109' cookie specification.
    Rfc2109,
    /// The 'RFC 2965' cookie specification.
    Rfc2965,
    /// The default value equal to 'Rfc2109'.
    Default = static_cast<int32_t>(Rfc2109)
};

/// Represents an HTTP cookie.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS Cookie final : public System::Object
{
    /// This type.
    typedef Cookie ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The maximum supported version.
    ASPOSECPP_SHARED_API static const int32_t MaxSupportedVersion;
    /// The string representation of the maximum supported version.
    ASPOSECPP_SHARED_API static const String MaxSupportedVersionString;
    /// The 'Comment' attribute's name.
    ASPOSECPP_SHARED_API static const String CommentAttributeName;
    /// The 'CommentURL' attribute's name.
    ASPOSECPP_SHARED_API static const String CommentUrlAttributeName;
    /// The 'Discard' attribute's name.
    ASPOSECPP_SHARED_API static const String DiscardAttributeName;
    /// The 'Domain' attribute's name.
    ASPOSECPP_SHARED_API static const String DomainAttributeName;
    /// The 'Expires' attribute's name.
    ASPOSECPP_SHARED_API static const String ExpiresAttributeName;
    /// The 'Max-Age' attribute's name.
    ASPOSECPP_SHARED_API static const String MaxAgeAttributeName;
    /// The 'Path' attribute's name.
    ASPOSECPP_SHARED_API static const String PathAttributeName;
    /// The 'Port' attribute's name.
    ASPOSECPP_SHARED_API static const String PortAttributeName;
    /// The 'Secure' attribute's name.
    ASPOSECPP_SHARED_API static const String SecureAttributeName;
    /// The 'Version' attribute's name.
    ASPOSECPP_SHARED_API static const String VersionAttributeName;
    /// The 'HttpOnly' attribute's name.
    ASPOSECPP_SHARED_API static const String HttpOnlyAttributeName;
    /// The attribute separator.
    ASPOSECPP_SHARED_API static const String SeparatorLiteral;
    /// The separator that is used to separates the name and value of an attribute.
    ASPOSECPP_SHARED_API static const String EqualsLiteral;
    /// The symbol used to wrap the attribute's parts.
    ASPOSECPP_SHARED_API static const String QuotesLiteral;
    /// The prefix of the special attributes' names.
    ASPOSECPP_SHARED_API static const String SpecialAttributeLiteral;
    /// The array that contains delimiters for the 'Port' attribute's values.
    ASPOSECPP_SHARED_API static System::ArrayPtr<char16_t> PortSplitDelimiters;
    /// A value that is reserved for the cookie name.
    ASPOSECPP_SHARED_API static System::ArrayPtr<char16_t> ReservedToName;
    /// A value that is reserved for the cookie value.
    ASPOSECPP_SHARED_API static System::ArrayPtr<char16_t> ReservedToValue;
    /// A value that indicates if the version is wrapped in the quotes.
    bool IsQuotedVersion;
    /// A value that indicates if the domain is wrapped in the quotes.
    bool IsQuotedDomain;

    /// Gets the 'Comment' attribute's value.
    /// @returns The 'Comment' attribute's value.
    ASPOSECPP_SHARED_API String get_Comment() const;
    /// Sets the 'Comment' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Comment(String value);
    /// Gets the 'CommentURL' attribute's value.
    /// @returns The 'CommentURL' attribute's value.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_CommentUri() const;
    /// Sets the 'CommentURL' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_CommentUri(System::SharedPtr<Uri> value);
    /// Gets the 'HttpOnly' attribute's value.
    /// @returns The 'HttpOnly' attribute's value.
    ASPOSECPP_SHARED_API bool get_HttpOnly() const;
    /// Sets the 'HttpOnly' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_HttpOnly(bool value);
    /// Gets the 'Discard' attribute's value.
    /// @returns The 'Discard' attribute's value.
    ASPOSECPP_SHARED_API bool get_Discard() const;
    /// Sets the 'Discard' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Discard(bool value);
    /// Gets the 'Domain' attribute's value.
    /// @returns The 'Domain' attribute's value.
    ASPOSECPP_SHARED_API String get_Domain() const;
    /// Sets the 'Domain' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Domain(String value);
    /// Gets a value that indicates if the domain is implicit.
    /// @returns A value that indicates if the domain is implicit.
    ASPOSECPP_SHARED_API bool get_DomainImplicit();
    /// Sets a value that indicates if the domain is implicit.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_DomainImplicit(bool value);
    /// Gets a value that indicates if the cookie expired.
    /// @returns A value that indicates if the cookie expired.
    ASPOSECPP_SHARED_API bool get_Expired();
    /// Sets a value that indicates if the cookie expired.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Expired(bool value);
    /// Gets the 'Expires' attribute's value.
    /// @returns The 'Expires' attribute's value.
    ASPOSECPP_SHARED_API DateTime get_Expires();
    /// Sets the 'Expires' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Expires(DateTime value);
    /// Gets the cookie's name.
    /// @returns The cookie's name.
    ASPOSECPP_SHARED_API String get_Name() const;
    /// Sets the cookie's name.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Name(String value);
    /// Gets the 'Path' attribute's value.
    /// @returns The 'Path' attribute's value.
    ASPOSECPP_SHARED_API String get_Path() const;
    /// Sets the 'Path' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Path(String value);
    /// Returns a value that indicates if the cookie specification is 'Plain'.
    /// @returns A value that indicates if the cookie specification is 'Plain'.
    ASPOSECPP_SHARED_API bool get_Plain() const;
    /// Gets the 'Port' attribute's value.
    /// @returns The 'Port' attribute's value.
    ASPOSECPP_SHARED_API String get_Port() const;
    /// Sets the 'Port' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Port(String value);
    /// Returns the collection of the 'Port' attribute's values.
    /// @returns The collection of the 'Port' attribute's values.
    ASPOSECPP_SHARED_API System::ArrayPtr<int32_t> get_PortList() const;
    /// Gets the 'Secure' attribute's value.
    /// @returns The 'Secure' attribute's value.
    ASPOSECPP_SHARED_API bool get_Secure() const;
    /// Sets the 'Secure' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Secure(bool value);
    /// Returns the time when the cookie was created.
    /// @returns The time when the cookie was created.
    ASPOSECPP_SHARED_API DateTime get_TimeStamp() const;
    /// Gets the cookie's'value.
    /// @returns The cookie's value.
    ASPOSECPP_SHARED_API String get_Value() const;
    /// Sets the cookie's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Value(String value);
    /// Gets the cookie's specification.
    /// @returns The cookie's specification.
    ASPOSECPP_SHARED_API CookieVariant get_Variant() const;
    /// Sets the cookie's specification.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Variant(CookieVariant value);
    /// Returns the domain key.
    /// @returns The domain key.
    ASPOSECPP_SHARED_API String get_DomainKey() const;
    /// Gets the 'Version' attribute's value.
    /// @returns The 'Version' attribute's value.
    ASPOSECPP_SHARED_API int32_t get_Version() const;
    /// Sets the 'Version' attribute's value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Version(int32_t value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API Cookie();
    /// Constructs a new instance.
    /// @param name The cookie's name.
    /// @param value The cookie's value.
    ASPOSECPP_SHARED_API Cookie(String name, String value);
    /// Constructs a new instance.
    /// @param name The cookie name.
    /// @param value The cookie value.
    /// @param path The 'Path' attribute's value.
    ASPOSECPP_SHARED_API Cookie(String name, String value, String path);
    /// Constructs a new instance.
    /// @param name The cookie's name.
    /// @param value The cookie's value.
    /// @param path The 'Path' attribute's value.
    /// @param domain The 'Domain' attribute's value.
    ASPOSECPP_SHARED_API Cookie(String name, String value, String path, String domain);

    /// This method is called by other methods to set a method name.
    /// @param value The value that must be set.
    /// @returns True when the specified value is empty or special, otherwise false.
    ASPOSECPP_SHARED_API bool InternalSetName(String value);
    /// Creates a copy of the current instance.
    /// @returns A copy of the current instance.
    ASPOSECPP_SHARED_API System::SharedPtr<Cookie> Clone();
    /// Verifies and sets the default attribute's values.
    /// @param variant The cookie's specification.
    /// @param uri The Uri-class instance that is used to initialize the internal fields.
    /// @param isLocalDomain A value that indicates if the cookie is pushed into the the local domain.
    /// @param localDomain A local domain name.
    /// @param setDefault A value that indicates if the cookie's attributes must be initialized using their default
    /// values.
    /// @param shouldThrow A value that indicates if an exception should be thrown when the specified values are
    /// invalid.
    /// @returns True when all values are valid, otherwise false.
    ASPOSECPP_SHARED_API bool VerifySetDefaults(CookieVariant variant, System::SharedPtr<Uri> uri, bool isLocalDomain, String localDomain,
                           bool setDefault, bool shouldThrow);
    /// Compares objects using C# Object.Equals semantics.
    /// @param comparand Object to compare current one to.
    /// @return True if objects are considered equal and false otherwise.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> comparand) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Serializes the current instance to the string representation.
    /// @returns A string representation of the current instance.
    ASPOSECPP_SHARED_API String ToServerString();

private:
    /// The 'Comment' attribute's value.
    String _comment;
    /// The 'CommentURL' attribute's value.
    System::SharedPtr<Uri> _commentUri;
    /// The cookie's specification.
    CookieVariant _cookieVariant;
    /// The 'Discard' attribute's value.
    bool _discard;
    /// The 'Domain' attribute's value.
    String _domain;
    /// A value that indicates if the domain is implicit.
    bool _domainImplicit;
    /// The 'Expires' attribute's value.
    DateTime _expires;
    /// The cookie's name.
    String _name;
    /// The 'Path' attribute's value.
    String _path;
    /// A value that indicates if the path is implicit.
    bool _pathImplicit;
    /// The 'Port' attribute's value.
    String _port;
    /// A value that indicates if the port is implicit.
    bool _portImplicit;
    /// The collection of the 'Port' attribute's values.
    System::ArrayPtr<int32_t> _portList;
    /// The 'Secure' attribute's value.
    bool _secure;
    /// The 'HttpOnly' attribute's value.
    bool _httpOnly;
    /// The time when the cookie was created.
    DateTime _timeStamp;
    /// The cookie's value.
    String _value;
    /// The 'Version' attribute's value.
    int32_t _version;
    /// The domain key.
    String _domainKey;

    /// Calculates a value of the 'Domain' attribute.
    /// @returns A value of the 'Domain' attribute.
    String get__Domain() const;
    /// Calculates a value of the 'Path' attribute.
    /// @returns A value of the 'Path' attribute.
    String get__Path() const;
    /// Calculates a value of the 'Port' attribute.
    /// @returns A value of the 'Port' attribute.
    String get__Port() const;
    /// Calculates a value of the 'Version' attribute.
    /// @returns A value of the 'Version' attribute.
    String get__Version() const;

    /// Checks if the domain name equals to the host name.
    /// @param domain The domain name to check.
    /// @param host The host name to check.
    /// @returns True when the specified values are equal, otherwise false.
    static bool IsDomainEqualToHost(String domain, String host);
    /// Checks characters in the specified domain name.
    /// @param name The domain name to check.
    /// @returns True when the domain name doesn't contain incorrect characters, otherwise false.
    static bool DomainCharsTest(String name);

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

/// Used to compare the Cookie class instances.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS CookieComparer final : public System::Collections::Generic::IComparer<System::SharedPtr<System::Net::Cookie>>
{
    /// This type.
    typedef CookieComparer ThisType;
    /// Parent type.
    typedef System::Collections::Generic::IComparer<System::SharedPtr<System::Net::Cookie>> BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// A 'singleton' implementation. Always returns the same instance of this class.
    /// @returns The same instance of this class.
    ASPOSECPP_SHARED_API static System::SharedPtr<CookieComparer> get_Instance();

    /// Compares the specified objects.
    /// @param left First object to compare.
    /// @param right Second object to compare.
    /// @returns Negative value if @p left is less than @p right; zero if they are equal; positive value if @p left is
    /// greater than @p right.
    ASPOSECPP_SHARED_API int Compare(args_type left, args_type right) const override;

private:
    /// An instance of this class returned by the 'get_Instance' method.
    static System::SharedPtr<CookieComparer> s_instance;

    /// Constructs a new instance.
    CookieComparer();
    MEMBER_FUNCTION_MAKE_OBJECT(CookieComparer, CODEPORTING_ARGS(), CODEPORTING_ARGS());
};

class CookieTokenizer;

/// Used to parse a cookie header and create an instance of the Cookie class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS CookieParser : public System::Object
{
    /// This type.
    typedef CookieParser ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    /// @param cookieString The string representation of a cookie header to parse.
    ASPOSECPP_SHARED_API CookieParser(String cookieString);

    /// Returns the string representation of a cookie header.
    /// @returns The string representation of a cookie header.
    ASPOSECPP_SHARED_API String GetString();
    /// Returns an instance based on the specified string.
    /// @returns An instance based on the specified string.
    ASPOSECPP_SHARED_API System::SharedPtr<Cookie> Get();
    /// Gets the server cookie.
    /// @returns The server cookie.
    ASPOSECPP_SHARED_API System::SharedPtr<Cookie> GetServer();
    /// Checks if the specified string is wrapped in the quotes.
    /// @param value The string to check.
    /// @returns True when the specified string is wrapped in the quotes, otherwise false.
    ASPOSECPP_SHARED_API static String CheckQuoted(String value);

private:
    /// The internal cookie tokenizer.
    System::SharedPtr<CookieTokenizer> _tokenizer;
    /// The server cookie.
    System::SharedPtr<Cookie> _savedCookie;
};


}} // namespace System::Net
