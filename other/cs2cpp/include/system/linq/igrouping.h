#pragma once

#include <system/object.h>
#include <system/collections/ienumerable.h>

namespace System {
namespace Linq {

template <typename TKey, typename TItem>
class IGrouping : public virtual System::Collections::Generic::IEnumerable<TItem>
{
    typedef IGrouping<TKey, TItem> ThisType;
    typedef System::Collections::Generic::IEnumerable<TItem> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    virtual TKey get_Key() = 0;
};

} // namespace Linq
} // namespace System
