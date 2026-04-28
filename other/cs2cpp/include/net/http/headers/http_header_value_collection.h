/// @file net/http/headers/http_header_value_collection.h
#pragma once

#include <system/action.h>
#include <system/collections/icollection.h>
#include <system/constraints.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/special_casts.h>
#include <system/string.h>

#include <net/http/headers/http_headers.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents the collection of the headers values.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam The type of the headers values represented in the collection.
template <typename T>
class ASPOSECPP_SHARED_CLASS HttpHeaderValueCollection final : public System::Collections::Generic::ICollection<T>
{
    /// Checks if the template parameter belongs to a pointer type.
    assert_is_cs_class(T);

    /// This type.
    typedef HttpHeaderValueCollection<T> ThisType;
    /// Parent type.
    typedef System::Collections::Generic::ICollection<T> BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    /// @copydoc System::Collections::Generic::ICollection::get_Count
    int32_t get_Count() const override
    {
        return GetCount();
    }

    /// Gets a value that indicates if the current collection is read-only.
    /// @returns A value that indicates if the current collection is read-only.
    bool get_IsReadOnly()
    {
        return false;
    }

    /// Gets a value that indicates if the current collection contains a "special value".
    /// @returns A value that indicates if the current collection contains a "special value".
    bool get_IsSpecialValueSet()
    {
        // If this collection instance has a "special value", then check whether that value was already set.
        if (_specialValue == nullptr)
        {
            return false;
        }
        return _store->ContainsParsedValue(_headerName, _specialValue);
    }

    /// Constructs a new instance.
    /// @param headerName The header name.
    /// @param store The collection of the HTTP headers.
    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store)
        : HttpHeaderValueCollection(headerName, store, nullptr,
                                    static_cast<Action<System::SharedPtr<HttpHeaderValueCollection<T>>, T>>(nullptr))
    {}

    /// Constructs a new instance.
    /// @param headerName The header name.
    /// @param store The collection of the HTTP headers.
    /// @param validator The delegate that is used to validate added items.
    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store,
                              Action<System::SharedPtr<HttpHeaderValueCollection<T>>, T> validator)
        : HttpHeaderValueCollection(headerName, store, nullptr,
                                    static_cast<Action<System::SharedPtr<HttpHeaderValueCollection<T>>, T>>(validator))
    {}

    /// Constructs a new instance.
    /// @param headerName The header name.
    /// @param store The collection of the HTTP headers.
    /// @param specialValue A "special value".
    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store, T specialValue)
        : HttpHeaderValueCollection(headerName, store, specialValue,
                                    static_cast<Action<System::SharedPtr<HttpHeaderValueCollection<T>>, T>>(nullptr))
    {}

    /// Constructs a new instance.
    /// @param headerName The header name.
    /// @param store The collection of the HTTP headers.
    /// @param specialValue A "special value".
    /// @param validator The delegate that is used to validate added items.
    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store, T specialValue,
                              Action<System::SharedPtr<HttpHeaderValueCollection<T>>, T> validator)
        : _specialValue(T())
    {
        _store = store;
        _headerName = headerName;
        _specialValue = specialValue;
        _validator = validator;
    }

    /// @copydoc System::Collections::Generic::ICollection::Add
    void Add(const T& item) override
    {
        CheckValue(item);
        _store->AddParsedValue(_headerName, item);
    }

    /// Parses a header string representation and adds it to the current collection.
    /// @param input A string representation of a header.
    void ParseAdd(String input)
    {
        _store->Add(_headerName, input);
    }

    /// Tries to parse a header string representation and add it to the current collection.
    /// @param input The header string representation.
    /// @returns True when the parsing is successfully done, otherwise false.
    bool TryParseAdd(String input)
    {
        return _store->TryParseAndAddValue(_headerName, input);
    }

    /// @copydoc System::Collections::Generic::ICollection::Clear
    void Clear() override
    {
        _store->Remove(_headerName);
    }

    /// @copydoc System::Collections::Generic::ICollection::Contains
    bool Contains(const T& item) const override
    {
        CheckValue(item);
        return _store->ContainsParsedValue(_headerName, item);
    }

    /// @copydoc System::Collections::Generic::ICollection::CopyTo
    void CopyTo(System::ArrayPtr<T> array, int32_t arrayIndex) override
    {
        if (array == nullptr)
        {
            throw ArgumentNullException(u"array");
        }
        // Allow arrayIndex == array.Length in case our own collection is empty
        if ((arrayIndex < 0) || (arrayIndex > array->get_Length()))
        {
            throw ArgumentOutOfRangeException(u"arrayIndex");
        }

        System::SharedPtr<Object> storeValue = _store->GetParsedValues(_headerName);

        if (storeValue == nullptr)
        {
            return;
        }

        System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> storeValues =
            HttpHeaders::ParsedValuesAsList(storeValue);

        if (storeValues == nullptr)
        {
            // We only have 1 value: If it is the "special value" just return, otherwise add the value to the
            // array and return.
            if (arrayIndex == array->get_Length())
            {
                throw ArgumentException(u"net_http_copyto_array_too_small");
            }
            array[arrayIndex] = nullptr;
        }
        else
        {
            storeValues->CopyTo(System::StaticCastArray<System::SharedPtr<Object>>(array), arrayIndex);
        }
    }

    /// @copydoc System::Collections::Generic::ICollection::Remove
    bool Remove(const T& item) override
    {
        CheckValue(item);
        return _store->RemoveParsedValue(_headerName, item);
    }

    /// @copydoc System::Collections::Generic::ICollection::GetEnumerator
    System::SharedPtr<Collections::Generic::IEnumerator<T>> GetEnumerator() override
    {
        auto list = System::MakeObject<Collections::Generic::List<T>>();
        while (true)
        {

            System::SharedPtr<Object> storeValue = _store->GetParsedValues(_headerName);

            if (storeValue == nullptr)
            {
                // yield break;
                break;
            }

            System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> storeValues =
                HttpHeaders::ParsedValuesAsList(storeValue);

            if (storeValues == nullptr)
            {
                CODEPORTING_DEBUG_ASSERT1(System::ObjectExt::Is<T>(storeValue));
                // T result = storeValue;// System::ExplicitCast<T>(storeValue);
                T result = System::ExplicitCast<typename T::Pointee_>(storeValue);
                list->Add(result);
            }
            else
            {
                // We have multiple values. Iterate through the values and return them.
                auto item_enumerator = (storeValues)->GetEnumerator();
                while (item_enumerator->MoveNext())
                {
                    auto&& item = item_enumerator->get_Current();
                    CODEPORTING_DEBUG_ASSERT1(System::ObjectExt::Is<T>(item));
                    // T result = item;// System::ExplicitCast<T>(item);
                    T result = System::ExplicitCast<typename T::Pointee_>(item);
                    // T result = System::AsCast<typename T::Pointee_>(item);
                    // yield return item as T;
                    list->Add(result);
                }
            }
            break;
        }

        return list->GetEnumerator();
    }

    /// @copydoc System::Object::ToString
    String ToString() const override
    {
        return _store->GetHeaderString(_headerName);
    }

    /// Returns a string representation of the current collection without a "special value".
    /// @returns A string representation of the current collection without a "special value".
    String GetHeaderStringWithoutSpecial()
    {
        if (!get_IsSpecialValueSet())
        {
            return ToString();
        }
        return _store->GetHeaderString(_headerName, _specialValue);
    }

    /// Sets a "special value".
    void SetSpecialValue()
    {

        if (!_store->ContainsParsedValue(_headerName, _specialValue))
        {
            _store->AddParsedValue(_headerName, _specialValue);
        }
    }

    /// Removes a "special value".
    void RemoveSpecialValue()
    {

        // We're not interested in the return value. It's OK if the "special value" wasn't in the store
        // before calling RemoveParsedValue().
        _store->RemoveParsedValue(_headerName, _specialValue);
    }

    /// @copydoc System::Object::SetTemplateWeakPtr
    void SetTemplateWeakPtr(uint32_t argument) override
    {
        switch (argument)
        {
        case 0:
            System::Details::CollectionHelpers::SetWeakPointer(_specialValue);
            System::Details::CollectionHelpers::SetWeakPointer(0, _validator);
            break;
        }
    }

private:
    /// The header name.
    String _headerName;
    /// The collection of the HTTP headers.
    System::WeakPtr<HttpHeaders> _store;
    /// A "special value".
    T _specialValue;
    /// The delegate that is used to validate added items.
    Action<System::SharedPtr<HttpHeaderValueCollection<T>>, T> _validator;

    /// Checks the specified item using a validator.
    /// @param item The item to check.
    /// @throws System::ArgumentNullException The exception is thrown when the specified item is nullptr.
    void CheckValue(const T& item) const
    {
        if (item == nullptr)
        {
            throw ArgumentNullException(u"item");
        }

        // If this instance has a custom validator for validating arguments, call it now.
        if (_validator != nullptr)
        {
            _validator(System::MakeSharedPtr(this), item);
        }
    }

    /// Counts the stored values.
    /// @returns The number of items stored in the collection.
    int32_t GetCount() const
    {
        // This is an O(n) operation.

        System::SharedPtr<Object> storeValue = _store->GetParsedValues(_headerName);

        if (storeValue == nullptr)
        {
            return 0;
        }

        System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> storeValues =
            HttpHeaders::ParsedValuesAsList(storeValue);

        if (storeValues == nullptr)
        {
            return 1;
        }
        else
        {
            return storeValues->get_Count();
        }
    }
};

/// The partial specialization of the HttpHeaderValueCollection template for the String type.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
template <>
class HttpHeaderValueCollection<System::String> : public System::Collections::Generic::ICollection<System::String>
{
    typedef HttpHeaderValueCollection<String> ThisType;
    typedef System::Collections::Generic::ICollection<String> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    int32_t get_Count() const override
    {
        return GetCount();
    }

    bool get_IsReadOnly()
    {
        return false;
    }

    bool get_IsSpecialValueSet()
    {
        // If this collection instance has a "special value", then check whether that value was already set.
        if (_specialValue == nullptr)
        {
            return false;
        }
        return _store->ContainsParsedValue(_headerName, _specialValue);
    }

    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store)
        : HttpHeaderValueCollection(
              headerName, store, nullptr,
              static_cast<Action<System::SharedPtr<HttpHeaderValueCollection<String>>, String>>(nullptr))
    {}

    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store,
                              Action<System::SharedPtr<HttpHeaderValueCollection<String>>, String> validator)
        : HttpHeaderValueCollection(
              headerName, store, nullptr,
              static_cast<Action<System::SharedPtr<HttpHeaderValueCollection<String>>, String>>(validator))
    {}

    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store, String specialValue)
        : HttpHeaderValueCollection(
              headerName, store, specialValue,
              static_cast<Action<System::SharedPtr<HttpHeaderValueCollection<String>>, String>>(nullptr))
    {}

    HttpHeaderValueCollection(String headerName, System::SharedPtr<HttpHeaders> store, String specialValue,
                              Action<System::SharedPtr<HttpHeaderValueCollection<String>>, String> validator)
    //: _specialValue(nullptr)
    {
        _store = store;
        _headerName = headerName;
        _specialValue = ObjectExt::Box(specialValue);
        _validator = validator;
    }

    void Add(const String& item) override
    {
        CheckValue(item);
        _store->AddParsedValue(_headerName, ObjectExt::Box(item));
    }

    void ParseAdd(String input)
    {
        _store->Add(_headerName, input);
    }

    bool TryParseAdd(String input)
    {
        return _store->TryParseAndAddValue(_headerName, input);
    }

    void Clear() override
    {
        _store->Remove(_headerName);
    }

    bool Contains(const String& item) const override
    {
        CheckValue(item);
        return _store->ContainsParsedValue(_headerName, ObjectExt::Box(item));
    }

    void CopyTo(System::ArrayPtr<String> array, int32_t arrayIndex) override
    {
        if (array == nullptr)
        {
            throw ArgumentNullException(u"array");
        }
        // Allow arrayIndex == array.Length in case our own collection is empty
        if ((arrayIndex < 0) || (arrayIndex > array->get_Length()))
        {
            throw ArgumentOutOfRangeException(u"arrayIndex");
        }

        System::SharedPtr<Object> storeValue = _store->GetParsedValues(_headerName);

        if (storeValue == nullptr)
        {
            return;
        }

        System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> storeValues =
            HttpHeaders::ParsedValuesAsList(storeValue);

        if (storeValues == nullptr)
        {
            // We only have 1 value: If it is the "special value" just return, otherwise add the value to the
            // array and return.
            if (arrayIndex == array->get_Length())
            {
                throw ArgumentException(u"net_http_copyto_array_too_small");
            }
            array[arrayIndex] = nullptr;
        }
        else
        {
            //    storeValues->CopyTo(System::StaticCastArray<System::SharedPtr<Object>>(array), arrayIndex);
        }
    }

    bool Remove(const String& item) override
    {
        CheckValue(item);
        return _store->RemoveParsedValue(_headerName, ObjectExt::Box(item));
    }

    System::SharedPtr<Collections::Generic::IEnumerator<String>> GetEnumerator() override
    {
        auto list = System::MakeObject<Collections::Generic::List<String>>();
        while (true)
        {

            System::SharedPtr<Object> storeValue = _store->GetParsedValues(_headerName);

            if (storeValue == nullptr)
            {
                // yield break;
                break;
            }

            System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> storeValues =
                HttpHeaders::ParsedValuesAsList(storeValue);

            if (storeValues == nullptr)
            {
                CODEPORTING_DEBUG_ASSERT1(System::ObjectExt::Is<String>(storeValue));
                String result = ObjectExt::Unbox<String>(storeValue);
                // T result = System::ExplicitCast<T>(storeValue);
                list->Add(result);
            }
            else
            {
                // We have multiple values. Iterate through the values and return them.
                auto item_enumerator = (storeValues)->GetEnumerator();
                while (item_enumerator->MoveNext())
                {
                    auto&& item = item_enumerator->get_Current();
                    CODEPORTING_DEBUG_ASSERT1(System::ObjectExt::Is<String>(item));
                    // T result = System::ExplicitCast<T>(item);
                    String result = ObjectExt::Unbox<String>(item);
                    // yield return item as T;
                    list->Add(result);
                }
            }
            break;
        }

        return list->GetEnumerator();
    }

    virtual String ToString() const override
    {
        return _store->GetHeaderString(_headerName);
    }

    String GetHeaderStringWithoutSpecial()
    {
        if (!get_IsSpecialValueSet())
        {
            return ToString();
        }
        return _store->GetHeaderString(_headerName, _specialValue);
    }

    void SetSpecialValue()
    {

        if (!_store->ContainsParsedValue(_headerName, _specialValue))
        {
            _store->AddParsedValue(_headerName, _specialValue);
        }
    }

    void RemoveSpecialValue()
    {

        // We're not interested in the return value. It's OK if the "special value" wasn't in the store
        // before calling RemoveParsedValue().
        _store->RemoveParsedValue(_headerName, _specialValue);
    }

    void SetTemplateWeakPtr(uint32_t argument) override
    {
        switch (argument)
        {
        case 0:
            System::Details::CollectionHelpers::SetWeakPointer(_specialValue);
            System::Details::CollectionHelpers::SetWeakPointer(0, _validator);
            break;
        }
    }

private:
    String _headerName;
    System::WeakPtr<HttpHeaders> _store;
    System::SharedPtr<Object> _specialValue;
    Action<System::SharedPtr<HttpHeaderValueCollection<String>>, String> _validator;

    void CheckValue(String item) const
    {
        if (item == nullptr)
        {
            throw ArgumentNullException(u"item");
        }

        // If this instance has a custom validator for validating arguments, call it now.
        if (_validator != nullptr)
        {
            _validator(System::MakeSharedPtr(this), item);
        }
    }

    int32_t GetCount() const
    {
        // This is an O(n) operation.

        System::SharedPtr<Object> storeValue = _store->GetParsedValues(_headerName);

        if (storeValue == nullptr)
        {
            return 0;
        }

        System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> storeValues =
            HttpHeaders::ParsedValuesAsList(storeValue);

        if (storeValues == nullptr)
        {
            return 1;
        }
        else
        {
            return storeValues->get_Count();
        }
    }
};

}}}} // namespace System::Net::Http::Headers
