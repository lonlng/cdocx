/// @file system/cycles_detection.h
#pragma once

#include "shared_ptr.h"
#include "detail.h"

#include <iostream>
#include <utility>
#include <type_traits>

/// Macros that defines GetSharedMembers function to use with container types.
#define DEFINE_GET_SHARED_MEMBERS(containerName) \
    void GetSharedMembers(System::Object::shared_members_type& result) const override \
    { \
        Object::GetSharedMembers(result); \
        result.PopulateSharedMembers(#containerName "[]", containerName); \
    }

#if defined(ENABLE_CYCLES_DETECTION_EXT)

namespace System { namespace Debug {

class ExternalObjectCollector;

}}

namespace System { namespace Details {

    /// @brief Service method of CYCLES_DETECTION feature. Restarts collecting objects.
    void ASPOSECPP_SHARED_API ObjectCollection_Begin();
    /// @brief Service method of CYCLES_DETECTION feature. Finishes collecting objects and prints report.
    /// @param show_all Whether to report objects without reference cycles.
    /// @param total_objects Pointer to variable to store total number of objects into.
    /// @param circular_refs Pointer to variable to store number of detected cycles into.
    /// @param output The stream for the report output.
    void ASPOSECPP_SHARED_API ObjectCollection_End(bool show_all = false,
                                                   unsigned int* total_objects = nullptr,
                                                   unsigned int* circular_refs = nullptr,
                                                   std::ostream& output = std::cout);

} } // namespace System::Details

#endif // ENABLE_CYCLES_DETECTION_EXT
