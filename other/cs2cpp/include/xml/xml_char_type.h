#pragma once

#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class CharEntityEncoderFallbackBuffer;
class DtdParser;
class HtmlEncodedRawTextWriter;
class HtmlUtf8RawTextWriter;
namespace Schema
{
class Parser;
class XmlSchemaValidator;
} // namespace Schema
class Ucs4Decoder;
class Ucs4Decoder1234;
class Ucs4Decoder2143;
class Ucs4Decoder3412;
class Ucs4Decoder4321;
class XmlAutoDetectWriter;
class XmlCharacterData;
class XmlCharCheckingReader;
class XmlCharCheckingWriter;
class XmlConvert;
class XmlDeclaration;
class XmlEncodedRawTextWriter;
class Details_XmlException; using XmlException = System::ExceptionWrapper<Details_XmlException>;
class XmlSqlBinaryReader;
class XmlTextEncoder;
class XmlTextReaderImpl;
class XmlTextWriter;
class XmlUtf8RawTextWriter;
class XmlWellFormedWriter;
namespace Xsl
{
namespace XsltOld
{
class BuilderInfo;
class Compiler;
class ReaderOutput;
class SequentialOutput;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// For internal purposes. Do not use this class directly.
class ASPOSECPP_SHARED_CLASS XmlCharType : public System::Object
{
    typedef XmlCharType ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    /// @cond
    friend class XmlSqlBinaryReader;
    friend class CharEntityEncoderFallbackBuffer;
    friend class HtmlEncodedRawTextWriter;
    friend class XmlEncodedRawTextWriter;
    friend class HtmlUtf8RawTextWriter;
    friend class XmlUtf8RawTextWriter;
    friend class XmlAutoDetectWriter;
    friend class XmlCharCheckingReader;
    friend class XmlCharCheckingWriter;
    friend class XmlTextEncoder;
    friend class XmlTextReaderImpl;
    friend class XmlTextWriter;
    friend class XmlWellFormedWriter;
    friend class XmlCharacterData;
    friend class XmlDeclaration;
    friend class DtdParser;
    friend class Schema::Parser;
    friend class Schema::XmlSchemaValidator;
    friend class XmlConvert;
    friend class Ucs4Decoder;
    friend class Ucs4Decoder4321;
    friend class Ucs4Decoder1234;
    friend class Ucs4Decoder2143;
    friend class Ucs4Decoder3412;
    friend class Details_XmlException;
    friend class Xsl::XsltOld::BuilderInfo;
    friend class Xsl::XsltOld::Compiler;
    friend class Xsl::XsltOld::ReaderOutput;
    friend class Xsl::XsltOld::SequentialOutput;
    /// @endcond

public:

    /// @cond
    static ASPOSECPP_SHARED_API XmlCharType get_Instance();

    ASPOSECPP_SHARED_API bool IsWhiteSpace(char16_t ch);
    ASPOSECPP_SHARED_API bool IsNCNameSingleChar(char16_t ch);
    ASPOSECPP_SHARED_API bool IsStartNCNameSingleChar(char16_t ch);
    ASPOSECPP_SHARED_API bool IsNameSingleChar(char16_t ch);
    ASPOSECPP_SHARED_API bool IsCharData(char16_t ch);
    ASPOSECPP_SHARED_API bool IsPubidChar(char16_t ch);
    ASPOSECPP_SHARED_API bool IsLetter(char16_t ch);
    ASPOSECPP_SHARED_API bool IsNCNameCharXml4e(char16_t ch);
    ASPOSECPP_SHARED_API bool IsStartNCNameCharXml4e(char16_t ch);
    ASPOSECPP_SHARED_API bool IsNameCharXml4e(char16_t ch);
    static ASPOSECPP_SHARED_API bool IsDigit(char16_t ch);

    ASPOSECPP_SHARED_API XmlCharType();
    /// @endcond

protected:

    /// @cond
    static const int32_t SurHighStart;
    static const int32_t SurHighEnd;
    static const int32_t SurLowStart;
    static const int32_t SurLowEnd;
    static const int32_t SurMask;
    static const int32_t fWhitespace;
    static const int32_t fLetter;
    static const int32_t fNCStartNameSC;
    static const int32_t fNCNameSC;
    static const int32_t fCharData;
    static const int32_t fNCNameXml4e;
    static const int32_t fText;
    static const int32_t fAttrValue;

    bool IsTextChar(char16_t ch);
    bool IsAttributeValueChar(char16_t ch);
    static bool IsHighSurrogate(int32_t ch);
    static bool IsLowSurrogate(int32_t ch);
    static bool IsSurrogate(int32_t ch);
    static int32_t CombineSurrogateChar(int32_t lowChar, int32_t highChar);
    static void SplitSurrogateChar(int32_t combinedChar, char16_t& lowChar, char16_t& highChar);
    bool IsOnlyWhitespace(const String& str);
    int32_t IsOnlyWhitespaceWithPos(const String& str);
    int32_t IsOnlyCharData(const String& str);
    static bool IsOnlyDigits(const String& str, int32_t startPos, int32_t len);
    int32_t IsPublicId(const String& str);

    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlCharType"; }
    #endif
    /// @endcond

private:

    static const String s_PublicIdBitmap;

    static ArrayPtr<uint8_t>& s_xmlCharTypeData();
    static ArrayPtr<int16_t>& s_Indexes();
    static ArrayPtr<IntPtr>& s_PageIndexes();
    static uint8_t**& s_CharProperties();

    uint8_t** _charProperties;

    static uint8_t** InitializeCharProperties();

    XmlCharType(uint8_t** charProperties);

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlCharType, CODEPORTING_ARGS(uint8_t** charProperties));
    static bool InRange(int32_t value, int32_t start, int32_t end);

};

} // namespace Xml
} // namespace System


