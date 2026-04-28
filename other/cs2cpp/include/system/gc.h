/// @file system/gc.h
/// Contains the declaration of System::GC class.
#ifndef _aspose_system_gc_h_
#define _aspose_system_gc_h_

#include "fwd.h"
#include "system/object.h"
#include "system/exceptions.h"

namespace System {

/// Represents an emulated Garbage Collection which acts more like a stub which effectively does nothing.
/// This is a static type with no instance services.
/// You should never create instances of it by any means.
class GC : public Object
{
    RTTI_INFO(GC, ::System::BaseTypesInfo<System::Object>);
public:    
    /// @cond
    /// Does nothing.
    static ASPOSECPP_SHARED_API void SuppressFinalize(const SharedPtr<Object>& obj);
    /// @endcond
    /// Returns the number of bytes of private memory currently allocated by the current process.
    /// @param force_full_collection IGNORED
    /// @returns The number of bytes of private memory currently allocated by the current process.
    static ASPOSECPP_SHARED_API int64_t GetTotalMemory(bool force_full_collection);
    /// Returns total allocated bytes.
    /// @param precise IGNORED
    /// @returns The number of bytes of private memory currently allocated by the current process.
    /// @note This is stub implementation for .NET method
    static ASPOSECPP_SHARED_API int64_t GetTotalAllocatedBytes(bool precise = false);
    /// @cond
    /// Does nothing.
    static ASPOSECPP_SHARED_API void Collect();
    /// Does nothing.
    static ASPOSECPP_SHARED_API void Collect(int generation);
    /// Does nothing.
    static ASPOSECPP_SHARED_API void WaitForPendingFinalizers();
    /// Returns 0.
    static ASPOSECPP_SHARED_API int get_MaxGeneration();
    /// @endcond
};

} // System
#endif
