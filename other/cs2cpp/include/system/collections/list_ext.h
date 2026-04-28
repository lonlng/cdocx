#pragma once
#include <system/collections/list.h>
#include <system/collections/ilist_wrapper.h>
#include <system/collections/ilist_impl.h>
#include <system/type_info_ext.h>

namespace System {
namespace Collections {
namespace Generic {

/// generic List class that implements IListWrapper interface
template<typename T>
class ASPOSECPP_SHARED_CLASS ListExt
    : public System::Collections::Generic::List<T>
    , public System::Collections::IListWrapper
{
protected:
    typedef SharedPtr<ListExt<T>> ThisPtr;

public:
    typedef System::Collections::Generic::ListExt<T> ThisType;
    typedef System::Collections::Generic::List<T> ListType;
    typedef System::BaseTypesInfo<System::Object> BaseTypes;
    typedef T ValueType;

    typedef List<T> BaseType;
    using BaseType::BaseType;

private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::Generic::ListExt<T>, System::BaseTypesInfo<System::Collections::Generic::List<T>>);

public:

    /// IListWrapper interface implementation
    System::SharedPtr<System::Collections::IList>
        CreateIListWrapper() override
    {
        return CreateIListWrapperImpl<T>();
    }

    /// IListWrapper implementation helper for reference types
    template<typename T1>
    typename std::enable_if<System::IsSmartPtr<T1>::value, System::SharedPtr<System::Collections::IList>>::type
        CreateIListWrapperImpl()
    {
        ThisPtr thisPtr = MakeSharedPtr(this);
        System::SharedPtr<System::Collections::IList> wrapper = System::MakeObject<System::Collections::IListImplRefType<typename T1::Pointee_>>(thisPtr);
        return wrapper;
    }

    /// IListWrapper implementation helper for value types
    template<typename T1>
    typename std::enable_if<!System::IsSmartPtr<T1>::value && System::IsBoxable<T1>::value, System::SharedPtr<System::Collections::IList>>::type
        CreateIListWrapperImpl()
    {
        ThisPtr thisPtr = MakeSharedPtr(this);
        System::SharedPtr<System::Collections::IList> wrapper = System::MakeObject<System::Collections::IListImplValueType<T1>>(thisPtr);
        return wrapper;
    }

    /// IListWrapper implementation helper for other types
    template<typename T1>
    typename std::enable_if<!System::IsSmartPtr<T1>::value && !System::IsBoxable<T>::value, System::SharedPtr<System::Collections::IList>>::type
        CreateIListWrapperImpl()
    {
        return nullptr;
    }
};

} // namespace Generic
} // namespace Collections
} // namespace System
