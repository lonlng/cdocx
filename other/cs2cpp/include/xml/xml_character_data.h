/// @file xml/xml_character_data.h

#pragma once

#include <xml/xml_linked_node.h>
#include <system/string.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class XmlCDataSection;
class XmlComment;
class XmlDocument;
class XmlNode;
class XmlSignificantWhitespace;
class XmlText;
class XmlWhitespace;
namespace XPath
{
enum class XPathNodeType;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Provides text manipulation methods that are used by several classes.
class ASPOSECPP_SHARED_CLASS XmlCharacterData : public XmlLinkedNode
{
    typedef XmlCharacterData ThisType;
    typedef XmlLinkedNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlCharacterData>;

private:
    /// @cond
    friend class XmlCDataSection;
    friend class XmlComment;
    friend class XmlSignificantWhitespace;
    friend class XmlText;
    friend class XmlWhitespace;
    /// @endcond

public:

    /// Returns the value of the node.
    /// @returns The value of the node.
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Sets the value of the node.
    /// @param value The value to set.
    /// @throws ArgumentException Node is read-only.
    ASPOSECPP_SHARED_API void set_Value(String value) override;
    /// Returns the concatenated values of the node and all the children of the node.
    /// @returns The concatenated values of the node and all the children of the node.
    ASPOSECPP_SHARED_API String get_InnerText() override;
    /// Sets the concatenated values of the node and all the children of the node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_InnerText(String value) override;
    /// Returns the data of the node.
    /// @returns The data of the node.
    virtual ASPOSECPP_SHARED_API String get_Data();
    /// Sets the data of the node.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_Data(String value);
    /// Returns the length of the data, in characters.
    /// @returns The length, in characters, of the string in the XmlCharacterData::get_Data result.
    /// The length may be zero; that is, CharacterData nodes can be empty.
    virtual ASPOSECPP_SHARED_API int32_t get_Length();

    /// Retrieves a substring of the full string from the specified range.
    /// @param offset The position within the string to start retrieving.
    /// An offset of zero indicates the starting point is at the start of the data.
    /// @param count The number of characters to retrieve.
    /// @returns The substring corresponding to the specified range.
    virtual ASPOSECPP_SHARED_API String Substring(int32_t offset, int32_t count);
    /// Appends the specified string to the end of the character data of the node.
    /// @param strData The string to insert into the existing string.
    virtual ASPOSECPP_SHARED_API void AppendData(String strData);
    /// Inserts the specified string at the specified character offset.
    /// @param offset The position within the string to insert the supplied string data.
    /// @param strData The string data that is to be inserted into the existing string.
    virtual ASPOSECPP_SHARED_API void InsertData(int32_t offset, String strData);
    /// Removes a range of characters from the node.
    /// @param offset The position within the string to start deleting.
    /// @param count The number of characters to delete.
    virtual ASPOSECPP_SHARED_API void DeleteData(int32_t offset, int32_t count);
    /// Replaces the specified number of characters starting at the specified offset with the specified string.
    /// @param offset The position within the string to start replacing.
    /// @param count The number of characters to replace.
    /// @param strData The new data that replaces the old string data.
    virtual ASPOSECPP_SHARED_API void ReplaceData(int32_t offset, int32_t count, String strData);

protected:

    /// Initializes a new instance of the XmlCharacterData class.
    /// @param data String that contains character data to be added to document.
    /// @param doc XmlDocument to contain character data.
    ASPOSECPP_SHARED_API XmlCharacterData(const String& data, const SharedPtr<XmlDocument>& doc);

    /// @cond
    bool CheckOnData(const String& data);
    bool DecideXPNodeTypeForTextNodes(SharedPtr<XmlNode> node, XPath::XPathNodeType& xnt);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlCharacterData();

private:

    String _data;

};

} // namespace Xml
} // namespace System


