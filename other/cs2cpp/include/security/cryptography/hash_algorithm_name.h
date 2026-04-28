/// @file security/cryptography/hash_algorithm_name.h
#pragma once

#include <system/string.h>
#include <system/boxable_traits.h>

namespace System { namespace Security { namespace Cryptography {

/// String representing the name of a hash algorithm.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
struct HashAlgorithmName
{
    /// Gets a HashAlgorithmName representing MD5.
    static HashAlgorithmName get_MD5()
    {
        return HashAlgorithmName(u"MD5");
    }

    /// Gets a HashAlgorithmName representing SHA1.
    static HashAlgorithmName get_SHA1()
    {
        return HashAlgorithmName(u"SHA1");
    }

    /// Gets a HashAlgorithmName representing SHA256.
    static HashAlgorithmName get_SHA256()
    {
        return HashAlgorithmName(u"SHA256");
    }

    /// Gets a HashAlgorithmName representing SHA384.
    static HashAlgorithmName get_SHA384()
    {
        return HashAlgorithmName(u"SHA384");
    }

    /// Gets a HashAlgorithmName representing SHA512.
    static HashAlgorithmName get_SHA512()
    {
        return HashAlgorithmName(u"SHA512");
    }

    /// Try to create HashAlgorithmName from OID-value.
    /// @param oid_value OID value.
    /// @param value Output HashAlgorithmName.
    /// @return true if specified OID is a valid hash algorithm, otherwise - false.
    static ASPOSECPP_SHARED_API bool TryFromOid(const String& oid_value, HashAlgorithmName& value);

    /// Create HashAlgorithmName from OID-value.
    /// @param oid_value OID value.
    /// @return Hash algorithm name.
    static ASPOSECPP_SHARED_API HashAlgorithmName FromOid(const String& oid_value);

    HashAlgorithmName() = default;

    /// Constructor.
    /// @param name Algorithm name.
    HashAlgorithmName(const String& name)
        : m_name(name)
    {}

    HashAlgorithmName& operator=(const HashAlgorithmName&) = default;

    /// Gets string representation of the algorithm name.
    String get_Name() const
    {
        return m_name;
    }

    /// Gets string representation of the algorithm name.
    String ToString() const
    {
        return m_name == nullptr ? String::Empty : m_name;
    }

    bool Equals(const HashAlgorithmName& other) const
    {
        return m_name == other.m_name;
    }

    int GetHashCode() const
    {
        return m_name == nullptr ? 0 : m_name.GetHashCode();
    }

    bool operator==(const HashAlgorithmName& other) const
    {
        return Equals(other);
    }

    bool operator!=(const HashAlgorithmName& other) const
    {
        return !Equals(other);
    }

    /// Returns a TypeInfo object that represent TimeSpan structure.
    static const TypeInfo& Type()
    {
        return *static_holder<ThisTypeInfo>();
    }

    bool IsNull() const { return false; }
    bool operator==(std::nullptr_t) const { return false; }
    bool operator!=(std::nullptr_t) const { return true; }
    bool operator<(std::nullptr_t) const { return false; }
    bool operator<=(std::nullptr_t) const { return false; }
    bool operator>(std::nullptr_t) const { return false; }
    bool operator>=(std::nullptr_t) const { return false; }

private:
    String m_name;

    /// Represents a pointer to TypeInfo object that contains information about HashAlgorithmName structure.
    struct ThisTypeInfo : TypeInfoPtr
    {
        /// Constructs an instance of ThisTypeInfo class.
        ThisTypeInfo()
            : TypeInfoPtr(u"System::Security::Cryptography::HashAlgorithmName")
        {}
    };
};

constexpr bool operator==(std::nullptr_t, const HashAlgorithmName&) { return false; }
constexpr bool operator!=(std::nullptr_t, const HashAlgorithmName&) { return true; }
constexpr bool operator<(std::nullptr_t, const HashAlgorithmName&) { return false; }
constexpr bool operator<=(std::nullptr_t, const HashAlgorithmName&) { return false; }
constexpr bool operator>(std::nullptr_t, const HashAlgorithmName&) { return false; }
constexpr bool operator>=(std::nullptr_t, const HashAlgorithmName&) { return false; }

/// Insert data into the stream using UTF-8 encoding.
/// @param stream Output stream to insert data to.
/// @param name Data to insert.
/// @return \p stream.
inline std::ostream& operator<<(std::ostream& stream, const HashAlgorithmName& name)
{
    stream << name.ToString();
    return stream;
}

/// Insert data into the stream.
/// @param stream Output stream to insert data to.
/// @param name Data to insert.
/// @return \p stream.
inline std::wostream& operator<<(std::wostream& stream, const HashAlgorithmName& name)
{
    stream << name.ToString();
    return stream;
}

}}} // namespace System::Security::Cryptography

namespace System {

/// @cond
/// IsBoxable<T> specialization for HashAlgorithmName.
template<> struct IsBoxable<System::Security::Cryptography::HashAlgorithmName> : std::true_type {};
/// @endcond

} // namespace System
