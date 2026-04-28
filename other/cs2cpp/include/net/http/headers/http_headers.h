/// @file net/http/headers/http_headers.h
#pragma once

#include <system/array.h>
#include <system/collections/dictionary.h>
#include <system/collections/hashset.h>
#include <system/collections/ienumerable.h>
#include <system/collections/ienumerator.h>
#include <system/collections/iequality_comparer.h>
#include <system/collections/keyvalue_pair.h>
#include <system/collections/list.h>
#include <system/collections/sorted_dictionary.h>
#include <system/constraints.h>
#include <system/diagnostics/debug.h>
#include <system/exceptions.h>
#include <system/object.h>
#include <system/object_ext.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

template <typename TResult>
using HeaderFunc = System::MulticastDelegate<TResult()>;

class HttpHeaderParser;

/// The collection of the HTTP headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT HttpHeaders
    : public System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<
          System::String, System::SharedPtr<System::Collections::Generic::IEnumerable<System::String>>>>
{
    /// This type.
    typedef HttpHeaders ThisType;
    /// Parent type.
    typedef System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<
        System::String, System::SharedPtr<System::Collections::Generic::IEnumerable<System::String>>>>
        BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

private:
    /// Enumerates the store locations.
    enum class StoreLocation
    {
        Raw,
        Invalid,
        Parsed
    };

private:
    /// Represents an item of the header store.
    class HeaderStoreItemInfo : public System::Object
    {
        typedef HeaderStoreItemInfo ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        ASPOSECPP_SHARED_RTTI_INFO_DECL();

    public:
        System::SharedPtr<Object> get_RawValue();
        void set_RawValue(System::SharedPtr<Object> value);
        System::SharedPtr<Object> get_InvalidValue();
        void set_InvalidValue(System::SharedPtr<Object> value);
        System::SharedPtr<Object> get_ParsedValue();
        void set_ParsedValue(System::SharedPtr<Object> value);
        System::SharedPtr<HttpHeaderParser> get_Parser();
        bool get_CanAddValue();
        bool get_IsEmpty();

        HeaderStoreItemInfo(System::SharedPtr<HttpHeaderParser> parser);

    private:
        System::SharedPtr<Object> _rawValue;
        System::SharedPtr<Object> _invalidValue;
        System::SharedPtr<Object> _parsedValue;
        System::SharedPtr<HttpHeaderParser> _parser;
    };

public:
    /// Validates a new name-values pair and adds it to the current collection.
    /// @param name The header name.
    /// @param values The header values.
    ASPOSECPP_SHARED_API void Add(String name, System::SharedPtr<Collections::Generic::IEnumerable<String>> values);
    /// Validates a new name-value pair and adds it to the current collection.
    /// @param name The header name.
    /// @param value The header value.
    ASPOSECPP_SHARED_API void Add(String name, String value);
    /// Tries to add a new name-value pair to the current collection.
    /// @param name The header name.
    /// @param value The header value.
    ASPOSECPP_SHARED_API bool TryAddWithoutValidation(String name, String value);
    /// Adds a collection of name-value pairs to the current collection.
    /// @param name The header name.
    /// @param values The header values.
    ASPOSECPP_SHARED_API bool
        TryAddWithoutValidation(String name, System::SharedPtr<Collections::Generic::IEnumerable<String>> values);
    /// Removes all items from the collection.
    ASPOSECPP_SHARED_API void Clear();
    /// Tries to remove an item by the specified name.
    /// @param name The name of the header to remove.
    /// @returns True when the item successfully removed, otherwise false.
    ASPOSECPP_SHARED_API bool Remove(String name);
    /// Returns corresponding values by the specified name.
    /// @param name The header name.
    /// @returns The corresponding values.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::IEnumerable<String>> GetValues(String name);
    /// Tries to get corresponding values by the specified name.
    /// @param name The header name.
    /// @param values An instance where corresponding values will be assigned.
    /// @returns True when the header values are found by the specified name, otherwise false.
    ASPOSECPP_SHARED_API bool TryGetValues(String name,
                                           System::SharedPtr<Collections::Generic::IEnumerable<String>>& values);
    ASPOSECPP_SHARED_API bool Contains(String name);
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Returns a collection that contains string representations of headers' values.
    /// @returns A collection that contains string representations of headers' values.
    ASPOSECPP_SHARED_API
    System::SharedPtr<Collections::Generic::IEnumerable<Collections::Generic::KeyValuePair<String, String>>>
        GetHeaderStrings();
    /// Returns a string representation of values by the specified header name.
    /// @param headerName The header name.
    /// @returns A string representation of values by the specified header name.
    ASPOSECPP_SHARED_API String GetHeaderString(String headerName);
    /// Returns a string representation of values by the specified header name.
    /// @param headerName The header name.
    /// @param exclude The header value to exclude.
    /// @returns A string representation of values by the specified header name.
    ASPOSECPP_SHARED_API String GetHeaderString(String headerName, System::SharedPtr<Object> exclude);
    /// @copydoc System::Collections::Generic::IEnumerable::GetEnumerator
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::IEnumerator<
        Collections::Generic::KeyValuePair<String, System::SharedPtr<Collections::Generic::IEnumerable<String>>>>>
        GetEnumerator() override;
    /// @internal
    ASPOSECPP_SHARED_API void SetConfiguration(
        System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>> parserStore,
        System::SharedPtr<Collections::Generic::HashSet<String>> invalidHeaders);
    /// Gets a header by the specified name and adds a parsed value to the header.
    /// @param name The header name.
    /// @param value The value that must be added.
    ASPOSECPP_SHARED_API void AddParsedValue(String name, System::SharedPtr<Object> value);
    /// Gets a header by the specified name and sets a parsed value to the header.
    /// @param name The header name.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void SetParsedValue(String name, System::SharedPtr<Object> value);
    /// Gets a header by the specified name and sets or removes its value. The header value will be removed when the
    /// 'value' parameter is nullptr, otherwise a parsed value will be set.
    /// @param name The header name.
    /// @param value The header value.
    ASPOSECPP_SHARED_API void SetOrRemoveParsedValue(String name, System::SharedPtr<Object> value);
    /// Gets a header by the specified name and removes a parsed value from the header.
    /// @param name The header name.
    /// @param value The value that must be removed.
    /// @returns True when the value was successfully removed, otherwise false.
    ASPOSECPP_SHARED_API bool RemoveParsedValue(String name, System::SharedPtr<Object> value);
    /// Checks if the header contains the specified value.
    /// @param name The header name.
    /// @param value The header value.
    /// @returns True if the header contains the specified value, otherwise false.
    ASPOSECPP_SHARED_API bool ContainsParsedValue(String name, System::SharedPtr<Object> value);
    /// Concatenates the specified HttpHeaders-class instance with the current one.
    /// @param sourceHeaders The HttpHeaders-class instance from which headers will be added.
    ASPOSECPP_SHARED_API virtual void AddHeaders(System::SharedPtr<HttpHeaders> sourceHeaders);
    /// Tries to parse the specified value and add it to the header values.
    /// @param name The header name.
    /// @param value The value that must be parsed and added.
    /// @returns True when the value is successfully parsed and added, otherwise false.
    ASPOSECPP_SHARED_API bool TryParseAndAddValue(String name, String value);
    /// Returns parsed values by the specified header name.
    /// @param name The header name.
    /// @returns Parsed header values if any, otherwise nullptr.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> GetParsedValues(String name);
    /// Converts parsed values to list.
    /// @param parsedValues Values object to convert.
    /// @returns If the passed value is a List instance, returns it; otherwise, returns nullptr.
    static ASPOSECPP_SHARED_API System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<System::Object>>> ParsedValuesAsList(const System::SharedPtr<Object> parsedValues);

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
    /// Constructs a new instance.
    HttpHeaders();

private:
    /// Returns all headers as a string similar to:
    /// HeaderName1: Value1, Value2
    /// HeaderName2: Value1
    String ToStringNC();

    /// The header store.
    System::SharedPtr<
        Collections::Generic::SortedDictionary<String, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo>>>
        _headerStore;
    /// The collection of the HTTP parsers.
    System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>> _parserStore;
    /// The collection of the invalid headers.
    System::SharedPtr<Collections::Generic::HashSet<String>> _invalidHeaders;

    /// Returns a string representation by the specified header info.
    String GetHeaderString(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info);
    /// Returns a string representation by the specified header info.
    String GetHeaderString(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info, System::SharedPtr<Object> exclude);
    /// Adds the header info.
    void AddHeaderInfo(String headerName, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> sourceInfo);
    /// Clones the specified item and adds it to the HeaderStoreItemInfo-class instance.
    static void CloneAndAddValue(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> destinationInfo,
                                 System::SharedPtr<Object> source);
    /// Returns a copy of the specified instance.
    static System::SharedPtr<Object> CloneStringHeaderInfoValues(System::SharedPtr<Object> source);
    /// Gets a corresponding HeaderStoreItemInfo-class instance by the specified header name. A new
    /// HeaderStoreItemInfo-class instance is returned when it is not found in the header store.
    System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> GetOrCreateHeaderInfo(String name, bool parseRawValues);
    /// Creates a HeaderStoreItemInfo-class instance using the specified parser name. The created instance will be
    /// added to the store and returned as the method result.
    System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> CreateAndAddHeaderToStore(String name);
    /// Adds the specified HeaderStoreItemInfo-class instance to the store.
    void AddHeaderToStore(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info);
    /// Tries to get a HeaderStoreItemInfo-class instance by the specified name.
    bool TryGetHeaderInfo(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo>& info);
    /// Tries to parse a raw header value by the specified name.
    bool TryGetAndParseHeaderInfo(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo>& info);
    /// Parses a raw header value.
    bool ParseRawHeaderValues(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info,
                              bool removeEmptyHeader);
    /// Parses multiple header values.
    static void ParseMultipleRawHeaderValues(
        String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info,
        System::SharedPtr<Collections::Generic::List<System::SharedPtr<Object>>> rawValues);
    /// Parses a single raw header value.
    static void ParseSingleRawHeaderValue(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info);
    /// Tries to parse the specified value and add it to the store.
    static bool TryParseAndAddRawHeaderValue(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info,
                                             String value, bool addWhenInvalid);
    /// Adds a value to the specified store location.
    static void AddValue(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info, System::SharedPtr<Object> value,
                         HttpHeaders::StoreLocation location);
    /// Adds a value to the specified store.
    static void AddValueToStoreValue(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info,
                                     System::SharedPtr<Object> value, System::SharedPtr<Object>& currentStoreValue);

    /// Prepares a header info by the specified name and adds the header info to the store if required.
    void PrepareHeaderInfoForAdd(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo>& info,
                                 bool& addToStore);
    /// Parses and adds a value to the corresponding store location.
    void ParseAndAddValue(String name, System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info, String value);
    /// Returns a parser by the specified name.
    System::SharedPtr<HttpHeaderParser> GetParser(String name);
    /// Checks the specified header name.
    void CheckHeaderName(String name);
    /// Tries to check the specified header name.
    bool TryCheckHeaderName(String name);
    /// Checks if the specified string contains invalid newline characters.
    static void CheckInvalidNewLine(String value);
    /// Returns a value that determines if the specified value contains invalid newline characters.
    static bool ContainsInvalidNewLine(String value, String name);
    /// Returns a collection of string representations of the specified HeaderStoreItemInfo-class instance values.
    System::ArrayPtr<String> GetValuesAsStrings(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info);
    /// Returns a collection of string representations of the specified HeaderStoreItemInfo-class instance values.
    System::ArrayPtr<String> GetValuesAsStrings(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info,
                                                       System::SharedPtr<Object> exclude);
    /// Returns the number of values.
    static int32_t GetValueCount(System::SharedPtr<HttpHeaders::HeaderStoreItemInfo> info);
    /// Assigns the updated number of values to the specified variable.
    template <typename T>
    static void UpdateValueCount(System::SharedPtr<Object> valueStore, int32_t& valueCount)
    {
        if (valueStore == nullptr)
        {
            return;
        }

        System::SharedPtr<Collections::Generic::List<T>> values =
            System::AsCast<System::Collections::Generic::List<T>>(valueStore);
        if (values != nullptr)
        {
            valueCount += values->get_Count();
        }
        else
        {
            valueCount++;
        }
    }

    /// Compares two values using the specified comparer.
    bool AreEqual(System::SharedPtr<Object> value, System::SharedPtr<Object> storeValue,
                  System::SharedPtr<Collections::Generic::IEqualityComparer<System::SharedPtr<Object>>> comparer);
};



}}}} // namespace System::Net::Http::Headers
