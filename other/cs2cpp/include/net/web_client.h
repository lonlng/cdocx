/// @file net/web_client.h
#pragma once

#include <system/uri.h>
#include <system/component_model/component.h>
#include <system/text/encoding.h>
#include <system/collections/specialized/name_value_collection.h>
#include <mutex>

namespace System { namespace Net {

class WebRequest;
class WebResponse;

/// WebClient provides common methods for sending and receiving data.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS WebClient : public ComponentModel::Component
{
    /// This type.
    typedef WebClient ThisType;
    /// Parent type.
    typedef ComponentModel::Component BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API WebClient();
    /// Destructs the current instance.
    ASPOSECPP_SHARED_API ~WebClient();

    /// Gets the encoding used to download or upload strings.
    /// @returns The encoding that is used to download or upload strings.
    ASPOSECPP_SHARED_API SharedPtr<Text::Encoding> get_Encoding() const;

    /// Sets the encoding used to download or upload strings.
    /// @param encoding The encoding to set.
    ASPOSECPP_SHARED_API void set_Encoding(const SharedPtr<Text::Encoding>& encoding);

    /// NOT IMPLEMENTED.
    /// @internal
    ASPOSECPP_SHARED_API void set_UseDefaultCredentials(bool);

    /// Downloads the specified resource as a string.
    /// @param address The resource's URI.
    /// @return The string that contains the requested resource.
    ASPOSECPP_SHARED_API String DownloadString(const String& address) const;

    /// Downloads the specified resource as a string.
    /// @param address The resource's URI.
    /// @return The string that contains the requested resource.
    ASPOSECPP_SHARED_API String DownloadString(const SharedPtr<Uri>& address) const;

    /// Downloads the specified resource as a byte array.
    /// @param address The resource's URI.
    /// @return The byte array that contains the requested resource.
    ASPOSECPP_SHARED_API ByteArrayPtr DownloadData(const String& address) const;

    /// Downloads the specified resource as a byte array.
    /// @param address The resource's URI.
    /// @return The byte array that contains the requested resource.
    ASPOSECPP_SHARED_API ByteArrayPtr DownloadData(const SharedPtr<Uri>& address) const;

private:
    /// The encoding that is used to download or upload strings.
    SharedPtr<Text::Encoding> m_encoding;
    /// The base address.
    SharedPtr<Uri> m_base_address;
    /// A collection of the query parameters.
    SharedPtr<Collections::Specialized::NameValueCollection> m_query_parameters;
    /// The internal mutex.
    mutable std::mutex m_mutex;

#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

    /// Converts @p address to the absolute URI.
    /// @param address The address to convert.
    /// @returns The absolute URI.
    SharedPtr<Uri> GetAbsoluteUri(const String& address) const;

    /// Converts @p address to the absolute URI.
    /// @param address The address to convert.
    /// @returns The absolute URI.
    SharedPtr<Uri> GetAbsoluteUri(const SharedPtr<Uri>& address) const;

    /// Builds a string from m_query_parameters.
    /// @returns The built string.
    String BuildQuery() const;

    /// Converts response data to the string.
    /// @param response The response to convert.
    /// @param data The output parameter where a byte array representation will be assigned.
    /// @returns The converted data.
    String DecodeData(const SharedPtr<WebResponse>& response, const ByteArrayPtr& data) const;

    /// Downloads and decodes data from the specified resource.
    /// @param address The address from which data will be downloaded.
    /// @returns The decoded data.
    String DownloadStringInternal(const SharedPtr<Uri>& address) const;

    /// Downloads data from the specified resource.
    /// @param address The address from which data will be downloaded.
    /// @returns The byte array that contains downloaded data.
    ByteArrayPtr DownloadDataInternal(const SharedPtr<Uri>& address) const;

    /// Creates WebRequest to download data from the specified address.
    /// @param address The address from which data will be downloaded.
    /// @returns A newly created WebRequest-class instance.
    SharedPtr<WebRequest> CreateWebRequest(const SharedPtr<Uri>& address) const;
};

}} // namespace System::Net
