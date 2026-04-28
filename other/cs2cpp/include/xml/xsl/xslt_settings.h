/// @file xml/xsl/xslt_settings.h

#pragma once

#include <system/object.h>
#include <cstdint>


namespace System {

namespace Xml {

namespace Xsl {

/// Specifies the XSLT features to support during execution of the XSLT style sheet.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XsltSettings final : public System::Object
{
    typedef XsltSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XsltSettings>;

public:

    /// Returns an XsltSettings object with default settings.
    /// Support for the XSLT @c document() function and embedded script blocks is disabled.
    /// @returns An XsltSettings object with the XsltSettings::set_EnableDocumentFunction and
    /// XsltSettings::set_EnableScript options set to @c false.
    static ASPOSECPP_SHARED_API SharedPtr<XsltSettings> get_Default();
    /// Returns an XsltSettings object that enables support for the XSLT @c document() function and embedded script blocks.
    /// @returns An XsltSettings object with the XsltSettings::set_EnableDocumentFunction and
    /// XsltSettings::set_EnableScript options set to @c true.
    static ASPOSECPP_SHARED_API SharedPtr<XsltSettings> get_TrustedXslt();
    /// Returns a value indicating whether to enable support for the XSLT @c document() function.
    /// @returns @c true to support the XSLT @c document() function;
    /// otherwise, @c false.
    /// The default is @c false.
    ASPOSECPP_SHARED_API bool get_EnableDocumentFunction();
    /// Sets a value indicating whether to enable support for the XSLT @c document() function.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_EnableDocumentFunction(bool value);
    /// Returns a value indicating whether to enable support for embedded script blocks.
    /// @returns @c true to support script blocks in XSLT style sheets;
    /// otherwise, @c false.
    /// The default is @c false.
    ASPOSECPP_SHARED_API bool get_EnableScript();
    /// Sets a value indicating whether to enable support for embedded script blocks.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_EnableScript(bool value);

    /// Initializes a new instance of the XsltSettings class with default settings.
    ASPOSECPP_SHARED_API XsltSettings();
    /// Initializes a new instance of the XsltSettings class with the specified settings.
    /// @param enableDocumentFunction @c true to enable support for the XSLT @c document() function;
    /// otherwise, @c false.
    /// @param enableScript @c true to enable support for embedded scripts blocks; otherwise, @c false.
    ASPOSECPP_SHARED_API XsltSettings(bool enableDocumentFunction, bool enableScript);

protected:

    /// @cond
    bool get_CheckOnly();
    void set_CheckOnly(bool value);
    bool get_IncludeDebugInformation();
    void set_IncludeDebugInformation(bool value);
    int32_t get_WarningLevel();
    void set_WarningLevel(int32_t value);
    bool get_TreatWarningsAsErrors();
    void set_TreatWarningsAsErrors(bool value);
    /// @endcond

private:

    bool _enableDocumentFunction;
    bool _enableScript;
    bool _checkOnly;
    bool _includeDebugInformation;
    int32_t _warningLevel;
    bool _treatWarningsAsErrors;

};

} // namespace Xsl
} // namespace Xml
} // namespace System


