/// @file system/array_segment.h
#pragma once

#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/object_ext.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/array.h>
#include <cstdint>

namespace System {

/// Represents a segment of the one-dimensional array.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
/// @code
/// #include <system/array_segment.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
///
/// void Print(const SmartPtr<ArraySegment<String>> &segment)
/// {
///   for (auto i = segment->get_Offset(); i < segment->get_Offset() + segment->get_Count(); i++)
///   {
///     std::cout << segment->get_Array()[i] << ' ';
///   }
///   std::cout << std::endl;
/// }
///
/// int main()
/// {
///   // Create and fill the array.
///   auto array = System::MakeObject<Array<String>>(3);
///   array[0] = u"First";
///   array[1] = u"Second";
///   array[2] = u"Third";
///
///   // Create the array segment that contains the entire array.
///   auto fullArray = MakeObject<ArraySegment<String>>(array);
///
///   // Print the array segment items.
///   Print(fullArray);
///
///   // Create the array segment.
///   auto segment = MakeObject<ArraySegment<String>>(array, 1, 2);
///
///   // Print the array segment items.
///   Print(segment);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// First Second Third
/// Second Third
/// */
/// @endcode
/// @tparam T The type of the array segment elements.
template<typename T>
class ArraySegment : public System::Object
{
    typedef ArraySegment<T> ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    System::ArrayPtr<T> get_Array() 
    { 
        return m_array;
    }

    int32_t get_Offset() 
    {
        return m_offset;
    }

    int32_t get_Count() 
    { 
        return m_count;
    }

    ArraySegment(System::ArrayPtr<T> array) : m_offset(0), m_count(0)
    {
        if (array == nullptr)
        {
            throw ArgumentNullException(u"array");
        }
        m_array = array;
        m_offset = 0;
        m_count = array->get_Length();
    }

    ArraySegment(System::ArrayPtr<T> array, int32_t offset, int32_t count)
    {
        if (array == nullptr)
        {
            throw ArgumentNullException(u"array");
        }
        if (offset < 0)
        {
            throw ArgumentOutOfRangeException(u"offset_ArgumentOutOfRange_NeedNonNegNum");
        }
        if (count < 0)
        {
            throw ArgumentOutOfRangeException(u"count_ArgumentOutOfRange_NeedNonNegNum");
        }
        if (array->get_Length() - offset < count)
        {
            throw ArgumentException(u"Argument_InvalidOffLen");
        }
        m_array = array;
        m_offset = offset;
        m_count = count;
    }

    int32_t GetHashCode() const override
    { 
        return nullptr == m_array ? 0 : System::ObjectExt::GetHashCode(m_array) ^ m_offset ^ m_count;
    }

    virtual bool Equals(System::SharedPtr<Object> obj) override
    { 
        if (System::ObjectExt::Is<ArraySegment<T>>(obj))
        {
            return Equals(System::ObjectExt::Unbox<ArraySegment<T>>(obj));
        }
        else
        {
            return false;
        }
    }

    bool Equals(ArraySegment<T> obj) 
    { 
        return obj.m_array == m_array && obj.m_offset == m_offset && obj.m_count == m_count;
    }

    ArraySegment() : m_offset(0), m_count(0) { }

private:
    System::ArrayPtr<T> m_array;
    int32_t m_offset;
    int32_t m_count;
};

template<typename T>
bool operator ==(ArraySegment<T> a, ArraySegment<T> b) 
{ 
    return System::ObjectExt::Equals(a, b);
}

template<typename T>
bool operator !=(ArraySegment<T> a, ArraySegment<T> b) 
{ 
    return !(a == b);
}

} // namespace System
