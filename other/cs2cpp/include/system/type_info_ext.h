#pragma once
#include <system/type_info.h>
#include <system/reflection/constructor_info.h>

namespace System
{

template <class T>
inline void TypeInfo::AddDefaultConstructor()
{
    DefaultConstructor constructor = []() -> ObjectPtr
    {
        return System::MakeObject<T>();
    };

    AddDefaultConstructor(constructor);
}


}
