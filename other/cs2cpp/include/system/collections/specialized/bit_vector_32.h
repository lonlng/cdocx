#pragma once
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <cstdint>

namespace System { namespace Collections { namespace Specialized {

///  Provides a simple light bit vector with easy integer or Boolean access to a 32 bit storage
class ASPOSECPP_SHARED_CLASS BitVector32 final
{
public:
    class Section;

private:
    friend bool operator==(BitVector32::Section a, BitVector32::Section b);
    friend bool operator!=(BitVector32::Section a, BitVector32::Section b);

public:
    /// Represents an section of the vector that can contain a integer number.
    class ASPOSECPP_SHARED_CLASS Section final
    {
        friend bool operator==(BitVector32::Section a, BitVector32::Section b);
        friend bool operator!=(BitVector32::Section a, BitVector32::Section b);

    public:
        /// Gets a mask that isolates this section within the BitVector32.
        ASPOSECPP_SHARED_API int16_t get_Mask();
        /// Gets the offset of this section from the start of the BitVector32.
        ASPOSECPP_SHARED_API int16_t get_Offset();
        /// Creates empty object
        ASPOSECPP_SHARED_API Section();
        /// Creates Section object with specified mask and offset
        /// @param mask specified mask
        /// @param offset specified offset
        ASPOSECPP_SHARED_API Section(int16_t mask, int16_t offset);
        /// Determines whether the specified object is the same as the current
        /// @param obj object to be compared
        /// @returns True if objects are equal, otherwise - false
        ASPOSECPP_SHARED_API bool Equals(const BitVector32::Section& obj);
        /// Returns a hash code for the current object.
        ASPOSECPP_SHARED_API int32_t GetHashCode() const;
        /// Converts value represented by value param to string
        /// @param value object to be converted
        ASPOSECPP_SHARED_API static String ToString(BitVector32::Section value);
        /// Converts value represented by current object to string
        ASPOSECPP_SHARED_API String ToString() const;

    private:
        int16_t mask;
        int16_t offset;
    };

public:
    /// Initializes a new empty instance of the BitVector32.
    ASPOSECPP_SHARED_API BitVector32();
    /// returns the raw data stored in this bit vector...
    ASPOSECPP_SHARED_API int32_t get_Data();
    /// Initializes a new instance of the BitVector32 structure with the specified internal data.
    /// @param data internal data
    ASPOSECPP_SHARED_API BitVector32(int32_t data);
    /// Initializes a new instance of the BitVector32 structure with the information in the specified value.
    /// @param value other BitVector32 object
    ASPOSECPP_SHARED_API BitVector32(const BitVector32& value);
    /// Gets a value indicating whether all the specified bits are set.
    /// @param bit specified bits.
    ASPOSECPP_SHARED_API bool idx_get(int32_t bit);
    /// Sets a value indicating whether all the specified bits are set.
    /// @param bit specified bits.
    /// @param value value to set.
    ASPOSECPP_SHARED_API void idx_set(int32_t bit, bool value);
    /// Gets the value for the specified section.
    /// @param section specified section.
    ASPOSECPP_SHARED_API int32_t idx_get(BitVector32::Section section);
    /// Sets the value for the specified section.
    /// @param section specified section.
    /// @param value specified value.
    ASPOSECPP_SHARED_API void idx_set(BitVector32::Section section, int32_t value);
    /// Creates the first mask in a series.
    ASPOSECPP_SHARED_API static int32_t CreateMask();
    /// Creates the next mask in a series.
    /// @param previous previous series
    ASPOSECPP_SHARED_API static int32_t CreateMask(int32_t previous);
    /// Creates the first section in a series, with the specified maximum value.
    /// @param maxValue specified maximum value.
    ASPOSECPP_SHARED_API static BitVector32::Section CreateSection(int16_t maxValue);
    /// Creates the next section in a series, with the specified maximum value.
    /// @param maxValue specified maximum value.
    /// @param previous previous series
    ASPOSECPP_SHARED_API static BitVector32::Section CreateSection(int16_t maxValue, BitVector32::Section previous);
    /// Returns a hash code for the current object.
    ASPOSECPP_SHARED_API int32_t GetHashCode() const;
    /// Converts value represented by value parameter to string
    /// @param value object to be converted
    /// @returns string representation of object
    ASPOSECPP_SHARED_API static String ToString(const BitVector32& value);
    /// Determines whether the specified object is the same as the current
    /// @param obj object to be compared
    /// @returns True if objects are equal, otherwise - false
    ASPOSECPP_SHARED_API bool Equals(const BitVector32& obj);
    /// Converts value represented by current object to string
    ASPOSECPP_SHARED_API String ToString() const;

private:
    uint32_t data;
    static int16_t CountBitsSet(int16_t mask);
    ///     Given a highValue, creates the mask
    static int16_t CreateMaskFromHighValue(int16_t highValue);
    static BitVector32::Section CreateSectionHelper(int16_t maxValue, int16_t priorMask, int16_t priorOffset);
};

/// Checks if two specified objects are equal 
/// @param a - first object to compare
/// @param b - second object to compare
/// @return true if are equal, otherwise - false.
bool operator==(BitVector32::Section a, BitVector32::Section b);
/// Checks if two specified objects are not equal 
/// @param a - first object to compare
/// @param b - second object to compare
/// @return true if are not equal, otherwise - false.
bool operator!=(BitVector32::Section a, BitVector32::Section b);

}}} // namespace System::Collections::Specialized
