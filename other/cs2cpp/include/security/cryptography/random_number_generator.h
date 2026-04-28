/// @file security/cryptography/random_number_generator.h
#ifndef _security_cryptography_rng_h
#define _security_cryptography_rng_h

#include <cstdint>

#include <system/object.h>
#include <system/array.h>
#include <system/details/array_view.h>
#include <system/details/stack_array.h>

namespace System { namespace Security { namespace Cryptography {

/// Abstract class for random number generators to inherit from.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT RandomNumberGenerator : virtual public System::Object
{
protected:
    /// Constructor.
    RandomNumberGenerator();

public:
    /// Creates an instance of the default implementation of a cryptographic random number generator that can be used to generate random data.
    /// Not implemented.
    /// @return The implementation of a cryptographic random number generator
    static ASPOSECPP_SHARED_API System::SharedPtr<RandomNumberGenerator> Create();
    /// Fills existing array elements with random bytes.
    /// @param bytes Bytes array to fill.
    virtual ASPOSECPP_SHARED_API void GetBytes(ArrayPtr<uint8_t> bytes) = 0;
    /// Fills existing array slice with random bytes.
    /// @param bytes Bytes array to fill slice of.
    /// @param offset Slice beginning index.
    /// @param count Slice size.
    virtual ASPOSECPP_SHARED_API void GetBytes(ArrayPtr<uint8_t> bytes, int offset, int count);
    /// Fills existing array elements with random non-zero bytes.
    /// @param bytes Bytes array to fill.
    virtual ASPOSECPP_SHARED_API void GetNonZeroBytes(ArrayPtr<uint8_t> bytes);
    /// Fills existing array view elements with random bytes.
    /// @param bytes Bytes array view to fill.
    virtual ASPOSECPP_SHARED_API void GetBytes(System::Details::ArrayView<uint8_t> bytes);
    /// Fills existing array view slice with random bytes.
    /// @param bytes Bytes array view to fill slice of.
    /// @param offset Slice beginning index.
    /// @param count Slice size.
    virtual ASPOSECPP_SHARED_API void GetBytes(System::Details::ArrayView<uint8_t> bytes, int offset, int count);
    /// Fills existing array view elements with random non-zero bytes.
    /// @param bytes Bytes array view to fill.
    virtual ASPOSECPP_SHARED_API void GetNonZeroBytes(System::Details::ArrayView<uint8_t> bytes);
    /// Fills existing stack array elements with random bytes.
    /// @param bytes Bytes stack array to fill.
    template<std::size_t N> inline void GetBytes(System::Details::StackArray<uint8_t, N> &bytes)
    {
        GetBytes(static_cast<System::Details::ArrayView<uint8_t> >(bytes));
    }
    /// Fills existing stack array slice with random bytes.
    /// @param bytes Bytes stack array to fill slice of.
    /// @param offset Slice beginning index.
    /// @param count Slice size.
    template<std::size_t N> inline void GetBytes(System::Details::StackArray<uint8_t, N> &bytes, int offset, int count)
    {
        GetBytes(static_cast<System::Details::ArrayView<uint8_t> >(bytes), offset, count);
    }
    /// Fills existing stack array elements with random non-zero bytes.
    /// @param bytes Bytes stack array to fill.
    template<std::size_t N> inline void GetNonZeroBytes(System::Details::StackArray<uint8_t, N> &bytes)
    {
        GetNonZeroBytes(static_cast<System::Details::ArrayView<uint8_t> >(bytes));
    }
};

}}}
#endif // _security_cryptography_rng_h

