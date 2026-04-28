/// @file xml/xpath/xpath_exception.h

#pragma once

#include <system/exceptions.h>
#include <system/array.h>


/// @cond
namespace System
{
namespace Internal
{
namespace Xml
{
namespace XPath
{
class CompiledXpathExpr;
class DescendantBaseQuery;
class ExtensionQuery;
class FunctionQuery;
class Query;
class QueryBuilder;
class SortQuery;
class ValueQuery;
class VariableQuery;
class XPathParser;
class XPathScanner;
} // namespace XPath
} // namespace Xml
} // namespace Internal
namespace Xml
{
namespace XPath
{
class XPathNavigator;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

class Details_XPathException;
using XPathException = System::ExceptionWrapper<Details_XPathException>;

/// Provides the exception thrown when an error occurs while processing an XPath expression.
class ASPOSECPP_SHARED_CLASS Details_XPathException : public Details_SystemException
{
    typedef Details_XPathException ThisType;
    typedef Details_SystemException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XPathException>;

private:
    /// @cond
    friend class XPathNavigator;
    friend class Internal::Xml::XPath::Query;
    friend class Internal::Xml::XPath::ValueQuery;
    friend class Internal::Xml::XPath::CompiledXpathExpr;
    friend class Internal::Xml::XPath::CompiledXpathExpr;
    friend class Internal::Xml::XPath::DescendantBaseQuery;
    friend class Internal::Xml::XPath::ExtensionQuery;
    friend class Internal::Xml::XPath::FunctionQuery;
    friend class Internal::Xml::XPath::QueryBuilder;
    friend class Internal::Xml::XPath::SortQuery;
    friend class Internal::Xml::XPath::VariableQuery;
    friend class Internal::Xml::XPath::XPathParser;
    friend class Internal::Xml::XPath::XPathScanner;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

public:

    /// Returns the description of the error condition for this exception.
    /// @returns The @c string description of the error condition for this exception.
    ASPOSECPP_SHARED_API String get_Message() const override;

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// Initializes a new instance of the XPathException class.
    ASPOSECPP_SHARED_API Details_XPathException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XPathException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XPathException class with the specified exception message.
    /// @param message The description of the error condition.
    ASPOSECPP_SHARED_API Details_XPathException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XPathException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XPathException class using the specified exception message and Exception object.
    /// @param message The description of the error condition.
    /// @param innerException The Exception that threw the XPathException, if any. This value can be @c nullptr.
    ASPOSECPP_SHARED_API Details_XPathException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XPathException, CODEPORTING_ARGS(String message, Exception innerException));

    /// @cond
    static XPathException Create(const String& res);
    static XPathException Create(const String& res, const String& arg);
    static XPathException Create(const String& res, const String& arg, const String& arg2);
    static XPathException Create(const String& res, const String& arg, Exception innerException);

    Details_XPathException(const String& res, const ArrayPtr<String>& args);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XPathException, CODEPORTING_ARGS(String res, ArrayPtr<String> args));

    Details_XPathException(const String& res, const ArrayPtr<String>& args, Exception inner);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XPathException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, Exception inner));

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
    const char* DBG_class_name() const override { return "Details_XPathException"; }
#endif
    /// @endcond

private:

    String _res;
    ArrayPtr<String> _args;
    String _message;

    static String CreateMessage(const String& res, const ArrayPtr<String>& args);

};

} // namespace XPath
} // namespace Xml
} // namespace System


