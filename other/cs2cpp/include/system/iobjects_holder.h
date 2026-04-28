#pragma once

#include <system/smart_ptr.h>
#include <system/object.h>

#if defined(__DBG_TOOLS)
#include <vector>
#endif

namespace CodePorting { namespace Translator { namespace Cs2Cpp {

namespace Details {

    /// Base class for ObjectsHolder.
    /// Need for control ObjectHolder pointer's mode. See PostponedHolders class below.
    class IObjectsHolder : public System::Object
    {
    public:
        /// @brief Change object holders smart pointers modes.
        /// @p mode - Smart pointer mode.
        virtual void setObjectsMode(System::SmartPtrMode mode) = 0;
#if defined(__DBG_TOOLS)
        virtual std::vector<int> getHoldObjectIds() const = 0;
#endif
    };

}}}}
