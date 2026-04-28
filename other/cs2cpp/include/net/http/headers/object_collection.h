/// @file net/http/headers/object_collection.h
#pragma once

#include <cstdint>
#include <system/action.h>
#include <system/collections/ilist.h>
#include <system/collections/list.h>
#include <system/collections/object_model/collection.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/exceptions.h>
#include <system/object.h>
#include <system/shared_ptr.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents the collection of the objects.
/// @tparam T The object type.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
template <typename T>
class ASPOSECPP_SHARED_CLASS ObjectCollection final : public System::Collections::ObjectModel::Collection<T>
{
    /// This type.
    typedef ObjectCollection<T> ThisType;
    /// Parent type.
    typedef System::Collections::ObjectModel::Collection<T> BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    /// Constructs a new instance.
    ObjectCollection() : ObjectCollection(static_cast<Action<T>>(s_defaultValidator))
    {}

    /// Constructs a new instance.
    /// @param validator A delegate that is used to validate an item before adding it.
    ObjectCollection(Action<T> validator)
        : System::Collections::ObjectModel::Collection<T>(System::MakeObject<Collections::Generic::List<T>>())
    {
        _validator = validator;
    }

    /// @copydoc System::Object::SetTemplateWeakPtr
    void SetTemplateWeakPtr(uint32_t argument) override
    {
        switch (argument)
        {
        case 0:
            System::Details::CollectionHelpers::SetWeakPointer(0, _validator);
            BaseType::SetTemplateWeakPtr(0);
            break;
        }
    }

protected:
    /// Adds an item to the specified index.
    /// @param index The index where the item will be added.
    /// @param item The item to add.
    virtual void InsertItem(int32_t index, T item)
    {
        if (_validator != nullptr)
        {
            _validator(item);
        }
        Collections::ObjectModel::Collection<T>::InsertItem(index, item);
    }

    /// Sets an item at the specified index.
    /// @param index The index where the item will be set.
    /// @param item The item to set.
    virtual void SetItem(int32_t index, T item)
    {
        if (_validator != nullptr)
        {
            _validator(item);
        }
        Collections::ObjectModel::Collection<T>::SetItem(index, item);
    }

private:
    /// The default delegate that is used to validate an item before adding it.
    static Action<T> s_defaultValidator;
    /// The delegate that is used to validate an item before adding it to the current instance.
    Action<T> _validator;

    /// Checks if the specified value is not equal to nullptr.
    static void CheckNotNull(T item)
    {
        // Null values cannot be added to the collection.
        if (item == nullptr)
        {
            throw ArgumentNullException(u"item");
        }
    }
};

template <typename T>
Action<T> ObjectCollection<T>::s_defaultValidator = CheckNotNull;

}}}} // namespace System::Net::Http::Headers
