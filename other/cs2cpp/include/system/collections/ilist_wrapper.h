#pragma once

#include <system/smart_ptr.h>
#include <system/exceptions.h>

namespace System { namespace Collections { class IList; } }

namespace System {
namespace Collections {

/// Intrerface to support casting from generic to non-generic collection
class ASPOSECPP_SHARED_CLASS IListWrapper
{
public:
    /// Creates object that works with original colletion via non-generic interface
    virtual SmartPtr<System::Collections::IList> CreateIListWrapper()
    {
        throw System::NotImplementedException();
    }
};

}
}
