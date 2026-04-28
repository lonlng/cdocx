/// @file system/details/held_variables.h
#pragma once

#include <forward_list>
#include <memory>
#include <utility>
#include "system/smart_ptr.h"

namespace System { namespace Details {
/// Contains shared pointers and values held by a delegate.
struct HeldVariables
{
    /// Contains shared pointers held by a delegate.
    std::forward_list<std::pair<const char*, System::SmartPtrInfo>> sharedPointers;
    /// Contains values held by a delegate.
    std::forward_list<std::pair<const char*, System::Object*>> values;

    /// Copies all shared pointers and values from the specified instance.
    /// @param source The instance to copy shared pointers and values from.
    void CopyFrom(const std::shared_ptr<HeldVariables> &source)
    {
        if (source)
        {
            sharedPointers.insert_after(sharedPointers.before_begin(), source->sharedPointers.cbegin(), source->sharedPointers.cend());
            values.insert_after(values.before_begin(), source->values.cbegin(), source->values.cend());
        }
    }
};
}}