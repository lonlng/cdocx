#pragma once

#include "defines.h"
#include <stdint.h>

namespace System { namespace Details {

ASPOSECPP_SHARED_API bool fast_equals(const uint8_t *ptr0, const uint8_t *ptr1, int len);

}} // namespace System::Details
