/// @file system/reflection/assembly_name.h
#ifndef _system_reflection_assembly_name_h_
#define _system_reflection_assembly_name_h_

#include "system/object.h"
#include "system/string.h"
#include "system/version.h"

namespace System{ namespace Reflection{

/// Defines assembly name.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS AssemblyName final : public System::Object 
{
public:
    /// Constructor.
    ASPOSECPP_SHARED_API AssemblyName();
    /// Constructor.
    /// @param name Assembly name.
    ASPOSECPP_SHARED_API AssemblyName(const String& name);
    /// Constructor.
    /// @param name Assembly name.
    /// @param version Assembly version.
    ASPOSECPP_SHARED_API AssemblyName(const String& name, const Version& version);

    /// Gets assembly name.
    /// @return Assembly name.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets assembly name.
    /// @param name Assembly name.
    ASPOSECPP_SHARED_API void set_Name(const String& name);
    /// Gets assembly version.
    /// @return Assembly version.
    ASPOSECPP_SHARED_API Version get_Version();
    /// Sets assembly version.
    /// @param version Assembly version.
    ASPOSECPP_SHARED_API void set_Version(const Version& version);

private:
    /// Assembly name.
    String m_name;
    /// Asembly version.
    Version m_version;
};

}} // namespace System{ namespace Reflection{

#endif
