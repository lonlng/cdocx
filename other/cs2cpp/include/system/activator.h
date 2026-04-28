/// @file system/activator.h
/// Contains declaration of System::Activator class.
#pragma once

#include "system/shared_ptr.h"
#include "system/object.h"
#include "system/type_info.h"

namespace System 
{
/// Contains methods to create types of objects 
class Activator
{
public:
    /// Creates an instance of the specified type using the parameterless constructor of that type.
    /// @param type The type of object to create.
    static ASPOSECPP_SHARED_API System::SharedPtr<System::Object> CreateInstance(const System::TypeInfo& type);
};
} // namespace System
