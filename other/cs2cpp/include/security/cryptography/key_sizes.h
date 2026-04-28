/// @file security/cryptography/key_sizes.h
#pragma once

#include <defines.h>
#include <system/object.h>

namespace System { namespace Security { namespace Cryptography {

/// Set of key sizes accepted by symmetric algorithms.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS KeySizes : public System::Object
{
    /// This type.
    typedef System::Security::Cryptography::KeySizes ThisType;
    /// Base type.
    typedef System::Object BaseType;
    /// RTTI information.
    RTTI_INFO(System::Security::Cryptography::KeySizes, ::System::BaseTypesInfo<System::Object>)

public:
    /// Constructor.
    /// @param min_size Minimum valid key size, bits.
    /// @param max_size Maximal valid key size, bits.
    /// @param skip_size Valid key size step, bits.
    KeySizes(int min_size, int max_size, int skip_size) :
        m_max_size(max_size),
        m_min_size(min_size),
        m_skip_size(skip_size)
    {
    }

    /// Gets maximal valid key size.
    /// @return Maximal valid key size, bits.
    int get_MaxSize() const { return m_max_size; }
    /// Gets minimal valid key size.
    /// @return Minimal valid key size, bits.
    int get_MinSize() const { return m_min_size; }
    /// Gets valid key size step.
    /// @return Valid key size step, bits.
    int get_SkipSize() const { return m_skip_size; }

private:
    /// Maximal valid key size, bits.
    const int m_max_size;
    /// Minimal valid key size, bits.
    const int m_min_size;
    /// Valid key size step, bits.
    const int m_skip_size;
};

}}} // namespace System::Security::Cryptography
