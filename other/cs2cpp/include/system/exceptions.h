/// @file system/exceptions.h
/// Contains some macro definitions used in the definition of System::Exception class.
#pragma once

#include <string>
#include <memory>
#include "system/string.h"
#include "system/exception.h"
#include "system/nullable.h"

#ifndef E_FAIL__
/// An alias for HRESULT code for unspecified error.
#define E_FAIL__ 0x80004005
#endif


//EXCEPTION_NAMESPACE(Parent::Name::Space, Class) or EXCEPTION_NAMESPACE(, System) if there is no parent
/// Declares a namespace 'ns' and in its scope declares a string object
/// that contains the full name of the namespace.
#define EXCEPTION_NAMESPACE(pns, ns) namespace ns\
{\
    /** @cond */ \
    inline const System::String& CURRENT_NAMESPACE()\
    {\
        static const System::String name = System::String(ASPOSE_T(#pns)).IsEmpty() ? System::String(ASPOSE_T(#ns)) : System::String(ASPOSE_T(#pns) "::" ASPOSE_T(#ns));\
        return name;\
    }\
    /** @endcond */ \
}\
namespace ns

//Reflection helpers similar ones from reflection.h
/// Macros which introduces ThisTypeInfo structure keeping a static instance of TypeInfo associated with @p thistype class.
#define __ThisTypeInfo_Runtime_NameSpace(thisType) \
        struct ThisTypeInfo : System::TypeInfoPtr { \
            ThisTypeInfo() : System::TypeInfoPtr(thisType) {

// baseTypes: System::BaseTypesInfo<TypeA, TypeB, TypeC>
/// Macros which adds RTTI info to be used by @p thisType exception class inheriting @p baseTypes classes.
#define RTTI_INFO_NAMESPACE(thisType, baseTypes) \
    __RTTI_INFO_METHODS(thisType, baseTypes) \
    __ThisTypeInfo_Runtime_NameSpace((CURRENT_NAMESPACE() + u"::" + ASPOSE_T(#thisType))) \
    RTTI_INFO_END()

//Exception related macros
/// Creates a declaration of an exception class with name @p name
/// as a descendant of the @p parent. 
#define DECLARE_INHERITED_EXCEPTION(name, parent) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent() {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(message) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::ExceptionWrapper<System::Details_Exception>& innerException) : parent(message, innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::ExceptionWrapper<System::Details_Exception>& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the @p parent with the default string message set.
#define DECLARE_INHERITED_EXCEPTION_MSG(name, parent) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent(MessageDefault()) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(DefaultMessageIfNull(message)) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::Exception& innerException) : parent(DefaultMessageIfNull(message), innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
private: \
    /** Returns the default message. */ \
    /** @returns A default message is returned.*/ \
    ASPOSECPP_SHARED_API static const String& MessageDefault(); \
    /** Selects the default message if the message argument is null. */ \
    /** @param message The message. */ \
    /** @returns A default message is returned if the message argument is null, otherwise the message argument is returned.*/ \
    ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message); \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the @p parent with the default string message set.
/// Should be used in cases when deserialize constructor does not exist.
#define DECLARE_INHERITED_EXCEPTION_MSG2(name, parent) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent(MessageDefault()) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(DefaultMessageIfNull(message)) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::Exception& innerException) \
        : parent(DefaultMessageIfNull(message), innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
private: \
    /** Returns the default message. */ \
    /** @returns A default message is returned.*/ \
    ASPOSECPP_SHARED_API static const String& MessageDefault(); \
    /** Selects the default message if the message argument is null. */ \
    /** @param message The message. */ \
    /** @returns A default message is returned if the message argument is null, otherwise the message argument is returned.*/ \
    ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message); \
};

/// Creates a declaration of an exception class with @p name name, @p parent baseclass end extra @p code int field available through constructors and getters.
#define DECLARE_INHERITED_EXCEPTION_WITH_EXTRA_CODE(name, parent, code) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
public: \
    /** Returns the error code. */ \
    /** @returns The error code. */ \
    int get_##code() { return m_##code; } \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent() {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param code The error code. */ \
    Details_##name(int code) : parent(u""), m_##code(code) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(int code), CODEPORTING_ARGS(code)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(message) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param code The error code. */ \
    /** @param message The error description. */ \
    Details_##name(int code, const System::String &message) : parent(message), m_##code(code) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(int code, const System::String &message), CODEPORTING_ARGS(code, message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::Exception& innerException) : parent(message, innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), CODEPORTING_ARGS(message, innerException)); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
    /** Returns the extended error description. */ \
    /** @returns The extended error description. */ \
    virtual String ExtraDescription() const override { return String::FromUtf8(std::to_string(m_##code)); } \
    /** The error code. */ \
    int m_##code = E_FAIL__; \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the 'parent' with String default message  and adds a String member named @p member to it.
/// Should be used for cases where exception message argument preceeds extra member one in constructors.
#define DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_MEMBER(name, parent, member) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
public: \
    /** Returns the value of the additional member. */ \
    /** @returns The value of the additional member. */ \
    String get_##member() { return m_##member; } \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent(MessageDefault()) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(DefaultMessageIfNull(message)) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::Exception& innerException) : parent(DefaultMessageIfNull(message), innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param member The value of the additional member. */ \
    Details_##name(const System::String &message, const System::String & member) : parent(DefaultMessageIfNull(message)), m_##member(member) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message, const System::String & member), CODEPORTING_ARGS(message, member)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param member The value of the additional member. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::String & member, const System::Exception& innerException) \
        : parent(DefaultMessageIfNull(message), innerException), m_##member(member) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::String & member, const System::Exception& innerException), \
        CODEPORTING_ARGS(message, member, innerException) \
    ); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
    /** Returns the extended error description. */ \
    /** @returns The extended error description. */ \
    virtual String ExtraDescription() const override { return m_##member; } \
    /** The value of the additional member. */ \
    String m_##member; \
private: \
    /** Returns the default message. */ \
    /** @returns A default message is returned.*/ \
    ASPOSECPP_SHARED_API static const String& MessageDefault(); \
    /** Selects the default message if the message argument is null. */ \
    /** @param message The message. */ \
    /** @returns A default message is returned if the message argument is null, otherwise the message argument is returned.*/ \
    ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message); \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the 'parent', sets String default message
/// and adds a String member named @p member to it.
/// Should be used for cases where extra member argument preceeds exception message one in constructors.
#define DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_MEMBER2(name, parent, member) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
public: \
    /** Returns the value of the additional member. */ \
    /** @returns The value of the additional member. */ \
    String get_##member() { return m_##member; } \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent(MessageDefault()) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param member The value of the additional member. */ \
    Details_##name(const System::String &member) : parent(MessageDefault()), m_##member(member) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &member), CODEPORTING_ARGS(member)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::Exception& innerException) : parent(DefaultMessageIfNull(message), innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** Constructs a new instance. */ \
    /** @param member The value of the additional member. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &member, const System::String &message) : parent(DefaultMessageIfNull(message)), m_##member(member) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &member, const System::String &message), CODEPORTING_ARGS(member, message)); \
    /** Constructs a new instance. */ \
    /** @param member The value of the additional member. */ \
    /** @param message The error description. */ \
    template<typename T> Details_##name(const System::String& member, const T&, const System::String& message) : parent(DefaultMessageIfNull(message)), m_##member(member) {} \
    template<typename T> MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String& member, const T& t, const System::String& message), CODEPORTING_ARGS(member, t, message)); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
    /** Returns the extended error description. */ \
    /** @returns The extended error description. */ \
    virtual String ExtraDescription() const override { return m_##member; } \
    /** The value of the additional member. */ \
    String m_##member; \
private: \
    /** Returns the default message. */ \
    /** @returns A default message is returned.*/ \
    ASPOSECPP_SHARED_API static const String& MessageDefault(); \
    /** Selects the default message if the message argument is null. */ \
    /** @param message The message. */ \
    /** @returns A default message is returned if the message argument is null, otherwise the message argument is returned.*/ \
    ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message); \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the 'parent', sets String default message
/// and adds a non-null String member named @p member to it.
/// Should be used for cases where extra member argument preceeds exception message one in constructors.
#define DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_NON_NULL_MEMBER(name, parent, member) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
public: \
    /** Returns the value of the additional member. */ \
    /** @returns The value of the additional member. */ \
    String get_##member() { return m_##member; } \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent(MessageDefault()), m_##member(System::String::Empty) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param member The value of the additional member. */ \
    Details_##name(const System::String &member) : parent(MessageDefault()), m_##member(EmptyStringIfNull(member)) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &member), CODEPORTING_ARGS(member)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::Exception& innerException) \
        : parent(DefaultMessageIfNull(message), innerException), m_##member(System::String::Empty) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** Constructs a new instance. */ \
    /** @param member The value of the additional member. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &member, const System::String &message) : parent(DefaultMessageIfNull(message)), m_##member(EmptyStringIfNull(member)) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &member, const System::String &message), \
        CODEPORTING_ARGS(member, message) \
    ); \
    /** Constructs a new instance. */ \
    /** @param member The value of the additional member. */ \
    /** @param message The error description. */ \
    template<typename T> Details_##name(const System::String& member, const T&, const System::String& message) : parent(DefaultMessageIfNull(message)), m_##member(EmptyStringIfNull(member)) {} \
    template<typename T> MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String& member, const T& t, const System::String& message), CODEPORTING_ARGS(member, t, message)); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
    /** Returns the extended error description. */ \
    /** @returns The extended error description. */ \
    virtual String ExtraDescription() const override { return m_##member; } \
    /** The value of the additional member. */ \
    String m_##member; \
private: \
    /** Returns the default message. */ \
    /** @returns A default message is returned.*/ \
    ASPOSECPP_SHARED_API static const String& MessageDefault(); \
    /** Selects the default message if the message argument is null. */ \
    /** @param message The message. */ \
    /** @returns A default message is returned if the message argument is null, otherwise the message argument is returned.*/ \
    ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message); \
    /** Selects the empty string if member argument is null. */ \
    /** @param member The member name. */ \
    /** @returns An empty string is returned if the incoming member argument is null. */ \
    ASPOSECPP_SHARED_API static const String& EmptyStringIfNull(const String& member); \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the 'parent', sets String default message
/// and adds a non-null String member named @p member to insert into it.
/// Should be used for cases where extra member argument preceeds exception message one in constructors.
#define DECLARE_INHERITED_EXCEPTION_MSG_AND_SUBSTITUTE_NON_NULL_MEMBER(name, parent, member) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
public: \
    /** Returns the value of the additional member. */ \
    /** @returns The value of the additional member. */ \
    String get_##member() { return m_##member; } \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    /** @param member The parameter name. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &member, const System::Exception& innerException) \
        : parent(DefaultMessage(member), innerException), m_##member(EmptyStringIfNull(member)) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::String &member, const System::Exception& innerException), \
        CODEPORTING_ARGS(member, innerException) \
    ); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, \
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), \
        CODEPORTING_ARGS(info, context) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
    /** Returns the extended error description. */ \
    /** @returns The extended error description. */ \
    virtual String ExtraDescription() const override { return m_##member; } \
    /** The value of the additional member. */ \
    String m_##member; \
private: \
    /** Returns the default message with parameter value substituted inside the message. u"%%" is used as the place holder for the parameter in the message. */ \
    /** @param parameter Parameter to substitute inside the message. */ \
    /** @returns A default message is returned with parameter substituted inside the message. */ \
    ASPOSECPP_SHARED_API static String DefaultMessage(const String& parameter); \
    /** Selects the default message if the message argument is null. Parameter value is substituted inside the message. u"%%" is used as the place holder for the parameter in the message. */ \
    /** @param message The message. */ \
    /** @param parameter Parameter to substitute inside the message. */ \
    /** @returns A default message is returned if the message argument is null, otherwise the message argument is returned. */ \
    ASPOSECPP_SHARED_API static String DefaultMessageIfNull(const String& message, const String& parameter); \
    /** Selects an empty string if the member argument is null. */ \
    /** @param member The member name. */ \
    /** @returns An empty string is returned if the member argument is null. */ \
    ASPOSECPP_SHARED_API static const String& EmptyStringIfNull(const String& member); \
};

/// Exception type declaration macros used by ExternalException-alike exceptions.
#define DECLARE_EXTERNAL_EXCEPTION(name, parent, code) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
public: \
    /** Returns the error code. */ \
    /** @returns The error code. */ \
    int get_##code() { return m_##code; } \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent() {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(message) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param code The error code. */ \
    Details_##name(const System::String &message, int code) : parent(message), m_##code(code) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message, int code), CODEPORTING_ARGS(message, code)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::ExceptionWrapper<System::Details_Exception>& innerException) : parent(message, innerException) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message, const System::ExceptionWrapper<System::Details_Exception>& innerException), CODEPORTING_ARGS(message, innerException)); \
    /** Deserializes exception. */ \
    /** @param info SerializationInfo object holding serialized exception. */ \
    /** @param context Streaming context bound to serialization info passed. */ \
    Details_##name(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : parent(info, context) {} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context), CODEPORTING_ARGS(info, context)); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
    /** Returns the extended error description. */ \
    /** @returns The extended error description. */ \
    virtual String ExtraDescription() const override { return String::FromUtf8(std::to_string(m_##code)); } \
    /** The error code. */ \
    int m_##code = E_FAIL__; \
};

/// Creates a declaration of an exception class with name @p name
/// as a descendant of the @p parent class with String default message
/// and with @p hresult as HRESULT associated with this exception.
#define DECLARE_INHERITED_EXCEPTION_MSG_AND_HRESULT(name, parent, hresult) \
class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class ASPOSECPP_SHARED_CLASS Details_##name : public parent { \
    friend class System::ExceptionWrapperHelper; \
    template <typename T> friend class System::ExceptionWrapper; \
    RTTI_INFO_NAMESPACE(name, System::BaseTypesInfo<parent>) \
protected: \
    /** Parent type. */ \
    using BaseType = parent; \
    /** Constructs a new instance. */ \
    Details_##name() : parent(MessageDefault()) {m_HResult = hresult;} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(), CODEPORTING_ARGS()); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    Details_##name(const System::String &message) : parent(DefaultMessageIfNull(message)) {m_HResult = hresult;} \
    MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message)); \
    /** Constructs a new instance. */ \
    /** @param message The error description. */ \
    /** @param innerException The inner exception. */ \
    Details_##name(const System::String &message, const System::ExceptionWrapper<System::Details_Exception>& innerException) \
        : parent(DefaultMessageIfNull(message), innerException) {m_HResult = hresult;} \
    MEMBER_FUNCTION_MAKE_OBJECT( Details_##name, \
        CODEPORTING_ARGS(const System::String &message, const System::ExceptionWrapper<System::Details_Exception>& innerException), \
        CODEPORTING_ARGS(message, innerException) \
    ); \
    /** @copydoc System::Details_Exception::DoThrow */ \
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_##name>(self); } \
private: \
    /** Returns the default message. */ \
    /** @returns A default message is returned.*/ \
    ASPOSECPP_SHARED_API static const String& MessageDefault(); \
    /** Selects the default message if the message argument is null. */ \
    /** @param message The message. */ \
    /** @returns Default message is returned in case message argument is null.*/ \
    ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message); \
};

EXCEPTION_NAMESPACE(, System) {
    /// @class System::Details_SystemException
    /// A base class for classes that represent system (rather than application) exceptions.
    /// Never create instances of this class manually. Use the SystemException class instead.
    /// Never wrap the SystemException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(SystemException, System::Details_Exception);
    /// @class System::Details_ApplicationException
    /// A base class for classes that represent application (rather than system) exceptions.
    /// Never create instances of this class manually. Use the ApplicationException class instead.
    /// Never wrap the ApplicationException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(ApplicationException, System::Details_Exception);
    /// @class System::Details_InvalidOperationException
    /// The exception that is thrown when a method is invoked on an object which is in the state inconsistent with this
    /// call.
    /// Never create instances of this class manually. Use the InvalidOperationException class instead.
    /// Never wrap the InvalidOperationException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(InvalidOperationException, System::Details_Exception);
    /// @class System::Details_InvalidProgramException
    /// InvalidProgramException is present for compatibility reasons only.
    /// Never create instances of this class manually. Use the InvalidProgramException class instead.
    /// Never wrap the InvalidProgramException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG2(InvalidProgramException, System::Details_Exception);
    /// @class System::Details_InvalidTimeZoneException
    /// InvalidTimeZoneException is thrown when time zone information is invalid.
    /// Never create instances of this class manually. Use the InvalidTimeZoneException class instead.
    /// Never wrap the InvalidTimeZoneException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(InvalidTimeZoneException, System::Details_Exception);
    /// @class System::Details_TimeZoneNotFoundException
    /// TimeZoneNotFoundException is thrown when time zone information is not found.
    /// Never create instances of this class manually. Use the TimeZoneNotFoundException class instead.
    /// Never wrap the TimeZoneNotFoundException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(TimeZoneNotFoundException, System::Details_Exception);
    /// @class System::Details_ObjectDisposedException
    /// ObjectDisposedException is thrown when a method is invoked on a disposed object.
    /// Never create instances of this class manually. Use the ObjectDisposedException class instead.
    /// Never wrap the ObjectDisposedException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_NON_NULL_MEMBER(ObjectDisposedException, System::Details_InvalidOperationException, ObjectName);
    /// @class System::Details_NotImplementedException
    /// NotImplementedException is thrown when a method that is not implemented and serves as a stub.
    /// Never create instances of this class manually. Use the NotImplementedException class instead.
    /// Never wrap the NotImplementedException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(NotImplementedException, System::Details_SystemException);
    /// @class System::Details_NotSupportedException
    /// NotSupportedException is thrown when a method being invoked is not supported or when an operation attempted on a
    /// stream is not supported.
    /// Never create instances of this class manually. Use the NotSupportedException class instead.
    /// Never wrap the NotSupportedException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(NotSupportedException, System::Details_SystemException);
    /// @class System::Details_PlatformNotSupportedException
    /// PlatformNotSupportedException is thrown when a feature does not run on a particular platform.
    /// Never create instances of this class manually. Use the PlatformNotSupportedException class instead.
    /// Never wrap the PlatformNotSupportedException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(PlatformNotSupportedException, System::Details_NotSupportedException);
    /// @class System::Details_ArgumentException
    /// ArgumentException is thrown when an argument passed to a method being invoked is invalid.
    /// Never create instances of this class manually. Use the ArgumentException class instead.
    /// Never wrap the ArgumentException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_MEMBER(ArgumentException, System::Details_SystemException, ParamName);
    /// @class System::Details_ArgumentException
    /// ArgumentNullException is thrown when a method being invoked is passed a null argument when the method expects a
    /// non-null value.
    /// Never create instances of this class manually. Use the ArgumentNullException class instead.
    /// Never wrap the ArgumentNullException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_MEMBER2(ArgumentNullException, System::Details_ArgumentException, ParamName);
    /// @class System::Details_ArgumentOutOfRangeException
    /// ArgumentOutOfRangeException is thrown when a method being invoked is passed an argument that falls out of the
    /// expected range of values for that argument.
    /// Never create instances of this class manually. Use the ArgumentOutOfRangeException class instead.
    /// Never wrap the ArgumentOutOfRangeException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_MEMBER2(ArgumentOutOfRangeException, System::Details_ArgumentException, ParamName);
    /// @class System::Details_FormatException
    /// FormatException is thrown when the format of the method's argument is not valid.
    /// Never create instances of this class manually. Use the FormatException class instead.
    /// Never wrap the FormatException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(FormatException, System::Details_SystemException);
    /// @class System::Details_UriFormatException
    /// UriFormatException is thrown when the format of URI is not valid.
    /// Never create instances of this class manually. Use the UriFormatException class instead.
    /// Never wrap the UriFormatException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG2(UriFormatException, System::Details_FormatException);
    /// @class System::Details_ArithmeticException
    /// ArithmeticException is throw when an error occurs during execution of arithmetic, conversion of casting
    /// operations.
    /// Never create instances of this class manually. Use the ArithmeticException class instead.
    /// Never wrap the ArithmeticException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(ArithmeticException, System::Details_SystemException);
    /// @class System::Details_OverflowException
    /// OverflowException is thrown when an operation results in an overflow.
    /// Never create instances of this class manually. Use the OverflowException class instead.
    /// Never wrap the OverflowException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(OverflowException, System::Details_ArithmeticException);
    /// @class System::Details_DivideByZeroException
    /// DivideByZeroException is thrown when division by 0 is attempted in an arithmetic operation.
    /// Never create instances of this class manually. Use the DivideByZeroException class instead.
    /// Never wrap the DivideByZeroException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(DivideByZeroException, System::Details_ArithmeticException);
    /// @class System::Details_DivideByZeroException
    /// OutOfMemoryException is throw when the application is out of memory.
    /// Never create instances of this class manually. Use the OutOfMemoryException class instead.
    /// Never wrap the OutOfMemoryException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(OutOfMemoryException, System::Details_SystemException);
    /// @class System::Details_IndexOutOfRangeException
    /// IndexOutOfRangeException is thrown when an access to an element of a collection is attempted using an index that
    /// is outside its bounds.
    /// Never create instances of this class manually. Use the IndexOutOfRangeException class instead.
    /// Never wrap the IndexOutOfRangeException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG2(IndexOutOfRangeException, System::Details_SystemException);
    /// @class System::Details_RankException
    /// RankException is thrown when an array argument with the number of dimensions different from the expected is
    /// passed to a method.
    /// Never create instances of this class manually. Use the RankException class instead.
    /// Never wrap the RankException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(RankException, System::Details_SystemException);
    /// @class System::Details_InvalidCastException
    /// InvalidCastException is thrown when invalid casting operation of invalid explicit conversion is attempted.
    /// Never create instances of this class manually. Use the InvalidCastException class instead.
    /// Never wrap the InvalidCastException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_HRESULT(InvalidCastException, System::Details_SystemException, (int32_t)2147500034u);
    /// @class System::Details_NullReferenceException
    /// NullReferenceException is thrown when dereferencing of a null-reference is attempted.
    /// Never create instances of this class manually. Use the NullReferenceException class instead.
    /// Never wrap the NullReferenceException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(NullReferenceException, System::Details_SystemException);
    /// @class System::Details_UnauthorizedAccessException
    /// UnauthorizedAccessException is thrown when access is denied by the operating system because of an I/O error or a
    /// security error.
    /// Never create instances of this class manually. Use the UnauthorizedAccessException class instead.
    /// Never wrap the UnauthorizedAccessException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG2(UnauthorizedAccessException, System::Details_SystemException);
    /// @class System::Details_MemberAccessException
    /// MemberAccessException is thrown when access to non-existent class' member is attempted or when access to the
    /// member is not permitted.
    /// Never create instances of this class manually. Use the MemberAccessException class instead.
    /// Never wrap the MemberAccessException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(MemberAccessException, System::Details_SystemException);
    /// @class System::Details_MethodAccessException
    /// MemberAccessException is thrown when access to non-existent method is attempted or when access to the method is
    /// not permitted.
    /// Never create instances of this class manually. Use the MethodAccessException class instead.
    /// Never wrap the MethodAccessException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(MethodAccessException, System::Details_MemberAccessException);
    /// @class System::Details_OperationCanceledException
    /// OperationCanceledException is thrown in a thread upon cancellation of an operation that the thread was
    /// executing.
    /// Never create instances of this class manually. Use the OperationCanceledException class instead.
    /// Never wrap the OperationCanceledException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(OperationCanceledException, System::Details_SystemException);
    /// @class System::Details_StackOverflowException
    /// StackOverflowException is thrown when the thread's execution stack overflows.
    /// Never create instances of this class manually. Use the StackOverflowException class instead.
    /// Never wrap the StackOverflowException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG2(StackOverflowException, System::Details_SystemException);
    /// @class System::Details_TimeoutException
    /// TimeoutException indicates if the time that is allotted for a process or operation is expired.
    /// Never create instances of this class manually. Use the TimeoutException class instead.
    /// Never wrap the TimeoutException class instances into System::SmartPtr.
    DECLARE_INHERITED_EXCEPTION_MSG(TimeoutException, System::Details_SystemException);
    /// @class System::Details_ExecutionEngineException
    /// ExecutionEngineException is present for compatibility reasons only.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_HRESULT(ExecutionEngineException, System::Details_SystemException, (int32_t)2148734214u);
    /// TypeInitializationException is present for compatibility reasons only.
    DECLARE_INHERITED_EXCEPTION_MSG_AND_SUBSTITUTE_NON_NULL_MEMBER(TypeInitializationException, System::Details_SystemException, TypeName);
    /// DataMisalignedException thrown when a unit of data is read from or written to an address that is not a multiple of the data size.
    DECLARE_INHERITED_EXCEPTION_MSG(DataMisalignedException, System::Details_SystemException);

    EXCEPTION_NAMESPACE(System, IO) {
        /// IOException is thrown when I/O error occurs.
        DECLARE_INHERITED_EXCEPTION_MSG(IOException, System::Details_SystemException);
        /// EndOfStreamException is thrown when operation of reading from or writing to a stream past its end is attempted.
        DECLARE_INHERITED_EXCEPTION_MSG(EndOfStreamException, System::IO::Details_IOException);
        /// InvalidDataException is thrown when a data stream is not in valid format.
        DECLARE_INHERITED_EXCEPTION_MSG2(InvalidDataException, System::Details_SystemException);
        /// DirectoryNotFoundException is thrown when a directory or a file is not found.
        DECLARE_INHERITED_EXCEPTION_MSG(DirectoryNotFoundException, System::IO::Details_IOException);
        /// FileLoadException is thrown when a error occurs during loading of a file.
        DECLARE_INHERITED_EXCEPTION_MSG_AND_EXTRA_MEMBER(FileLoadException, System::IO::Details_IOException, FileName);
        /// PathTooLongException is thrown when a path or fully qualified file name is longer than the system-defined maximum length.
        DECLARE_INHERITED_EXCEPTION_MSG(PathTooLongException, System::IO::Details_IOException);
    }

    EXCEPTION_NAMESPACE(System, Globalization) {
        class Details_CultureNotFoundException;
        using CultureNotFoundException = System::ExceptionWrapper<Details_CultureNotFoundException>;

        /// CultureNotFoundException is thrown when an attempt is made to construct a culture that is not available.
        /// Never create instances of this class manually. Use the CultureNotFoundException class instead.
        /// Never wrap the CultureNotFoundException class instances into System::SmartPtr.
        class ASPOSECPP_SHARED_CLASS Details_CultureNotFoundException : public System::Details_ArgumentException {
            friend class System::ExceptionWrapperHelper;
            template <typename T> friend class System::ExceptionWrapper;
            RTTI_INFO_NAMESPACE(CultureNotFoundException, System::BaseTypesInfo<System::Details_ArgumentException>)
        public:
            virtual Nullable<int> get_InvalidCultureId() const { return m_invalid_culture_id; }
            virtual String get_InvalidCultureName() const { return m_invalid_culture_name; }
        protected:
            using BaseType = System::Details_ArgumentException;
            Details_CultureNotFoundException() : System::Details_ArgumentException(MessageDefault()) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
            Details_CultureNotFoundException(const String& message) : System::Details_ArgumentException(DefaultMessageIfNull(message)) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));
            Details_CultureNotFoundException(const String& paramName, const String& message) : System::Details_ArgumentException(DefaultMessageIfNull(message), paramName) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException, CODEPORTING_ARGS(const String& paramName, const String& message), CODEPORTING_ARGS(paramName, message));
            Details_CultureNotFoundException(const String& message, const System::ExceptionWrapper<System::Details_Exception>& innerException) : System::Details_ArgumentException(DefaultMessageIfNull(message), innerException) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException,
                CODEPORTING_ARGS(const String& message, const System::ExceptionWrapper<System::Details_Exception>& innerException),
                CODEPORTING_ARGS(message, innerException)
            );
            Details_CultureNotFoundException(const String& paramName, int invalidCultureId, const String& message) : System::Details_ArgumentException(DefaultMessageIfNull(message), paramName), m_invalid_culture_id(invalidCultureId) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException, CODEPORTING_ARGS(const String& paramName, int invalidCultureId, const String& message), CODEPORTING_ARGS(paramName, invalidCultureId, message));
            Details_CultureNotFoundException(const String& message, int invalidCultureId, const System::ExceptionWrapper<System::Details_Exception>& innerException) : System::Details_ArgumentException(DefaultMessageIfNull(message), innerException), m_invalid_culture_id(invalidCultureId) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException,
                CODEPORTING_ARGS(const String& message, int invalidCultureId, const System::ExceptionWrapper<System::Details_Exception>& innerException),
                CODEPORTING_ARGS(message, invalidCultureId, innerException)
            );
            Details_CultureNotFoundException(const String& paramName, const String& invalidCultureName, const String& message) : System::Details_ArgumentException(DefaultMessageIfNull(message), paramName), m_invalid_culture_name(invalidCultureName) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException,
                CODEPORTING_ARGS(const String& paramName, const String& invalidCultureName, const String& message),
                CODEPORTING_ARGS(paramName, invalidCultureName, message)
            );
            Details_CultureNotFoundException(const String& message, const String& invalidCultureName, const System::ExceptionWrapper<System::Details_Exception>& innerException) : System::Details_ArgumentException(DefaultMessageIfNull(message), innerException), m_invalid_culture_name(invalidCultureName) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException,
                CODEPORTING_ARGS(const String& message, const String& invalidCultureName, const System::ExceptionWrapper<System::Details_Exception>& innerException),
                CODEPORTING_ARGS(message, invalidCultureName, innerException)
            );
            Details_CultureNotFoundException(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : System::Details_ArgumentException(info, context) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_CultureNotFoundException,
                CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context),
                CODEPORTING_ARGS(info, context)
            );
            [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_CultureNotFoundException>(self); }
        private:
            Nullable<int> m_invalid_culture_id;
            String m_invalid_culture_name;
            /// Returns the default message.
            /// @returns A default message is returned.
            ASPOSECPP_SHARED_API static const String& MessageDefault();
            /// Selects the default message if the message argument is null.
            /// @param message The message.
            /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
            ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message);
        };
    }

    EXCEPTION_NAMESPACE(System, Security) {
        /// SecurityException is thrown when a security error occurs.
        DECLARE_INHERITED_EXCEPTION_MSG(SecurityException, System::Details_SystemException);

        EXCEPTION_NAMESPACE(System::Security, Cryptography) {
            /// CryptographicException is thrown when an error occurs during cryptographic operation.
            DECLARE_INHERITED_EXCEPTION_MSG(CryptographicException, System::Details_SystemException);
            /// CryptographicUnexpectedOperationException is thrown when an error occurs during cryptographic operation.
            DECLARE_INHERITED_EXCEPTION_MSG(CryptographicUnexpectedOperationException,
                                            System::Security::Cryptography::Details_CryptographicException);
        }

        EXCEPTION_NAMESPACE(System::Security, Authentication) 
        {
            /// AuthenticationException 
            DECLARE_INHERITED_EXCEPTION_MSG(AuthenticationException, System::Details_SystemException);
        }
    }

    EXCEPTION_NAMESPACE(System, Threading) {
        /// ThreadStateException is thrown when the current thread is in non-valid state for the method call.
        DECLARE_INHERITED_EXCEPTION_MSG(ThreadStateException, System::Details_SystemException);
        /// SemaphoreFullException is thrown by the Semaphore.Release() method if it is called when the semaphore's count is at the maximum.
        DECLARE_INHERITED_EXCEPTION_MSG(SemaphoreFullException, System::Details_SystemException);
        /// SynchronizationLockException is thrown by calling the Monitor::Exit method from an unsynchronized block of code.
        DECLARE_INHERITED_EXCEPTION_MSG(SynchronizationLockException, System::Details_SystemException);
        /// ThreadAbortException 
        DECLARE_INHERITED_EXCEPTION(ThreadAbortException, System::Details_SystemException);
        /// ThreadInterruptedException is thrown when a Thread is interrupted while it is in a waiting state.
        DECLARE_INHERITED_EXCEPTION_MSG(ThreadInterruptedException, System::Details_SystemException);
    }

    EXCEPTION_NAMESPACE(System, ComponentModel)
    {
        /// The InvalidEnumArgumentException is thrown when an invalid enumeration value is used.
        class Details_InvalidEnumArgumentException;
        using InvalidEnumArgumentException = System::ExceptionWrapper<Details_InvalidEnumArgumentException>;

        class ASPOSECPP_SHARED_CLASS Details_InvalidEnumArgumentException : public System::Details_ArgumentException {
            friend class System::ExceptionWrapperHelper;
            template <typename T> friend class System::ExceptionWrapper;
            RTTI_INFO_NAMESPACE(InvalidEnumArgumentException, System::BaseTypesInfo<System::Details_ArgumentException>)
        protected:
            using BaseType = System::Details_ArgumentException;

            Details_InvalidEnumArgumentException() : System::Details_ArgumentException(MessageDefault()) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_InvalidEnumArgumentException, CODEPORTING_ARGS(), CODEPORTING_ARGS());

            Details_InvalidEnumArgumentException(const String& message) : System::Details_ArgumentException(DefaultMessageIfNull(message)) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_InvalidEnumArgumentException, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));

            Details_InvalidEnumArgumentException(const String& message, const System::ExceptionWrapper<System::Details_Exception>& innerException) : System::Details_ArgumentException(DefaultMessageIfNull(message), innerException) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_InvalidEnumArgumentException,
                CODEPORTING_ARGS(const String& message, const System::ExceptionWrapper<System::Details_Exception>& innerException),
                CODEPORTING_ARGS(message, innerException)
            );

            Details_InvalidEnumArgumentException(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context) : System::Details_ArgumentException(info, context) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_InvalidEnumArgumentException,
                CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context),
                CODEPORTING_ARGS(info, context)
            );

            Details_InvalidEnumArgumentException(const String& argumentName, int invalidValue, const System::TypeInfo& enumClass)
                : System::Details_ArgumentException(DetailedMessage(argumentName, invalidValue, enumClass), argumentName) {}
            MEMBER_FUNCTION_MAKE_OBJECT(Details_InvalidEnumArgumentException,
                CODEPORTING_ARGS(const String& argumentName, int invalidValue, const System::TypeInfo& enumClass),
                CODEPORTING_ARGS(argumentName, invalidValue, enumClass));

            [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_InvalidEnumArgumentException>(self); }
        private:
            /// Returns the default message.
            /// @returns A default message is returned.
            ASPOSECPP_SHARED_API static const String& MessageDefault();
            /// Selects the default message if the message argument is null.
            /// @param message The message.
            /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
            ASPOSECPP_SHARED_API static const String& DefaultMessageIfNull(const String& message);
            /// Returns the detailed message.
            /// @param argumentName The name of the argument that caused the exception.
            /// @param invalidValue The value of the argument that failed.
            /// @param enumClass A TypeInfo of enum with the valid values.
            /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
            ASPOSECPP_SHARED_API static const String DetailedMessage(const String& argumentName, int invalidValue, const System::TypeInfo& enumClass);
        };
    }

    EXCEPTION_NAMESPACE(System, Collections)
    {
        EXCEPTION_NAMESPACE(System::Collections, Generic)
        {
            /// KeyNotFoundException is thrown when access to a collection element is attempted using the key that does not match any key in the collection.
            DECLARE_INHERITED_EXCEPTION_MSG(KeyNotFoundException, System::Details_SystemException);
        }
    }

    EXCEPTION_NAMESPACE(System, Web)
    {
        /// HttpException is thrown when an error occurs while processing an HTTP request.
        DECLARE_INHERITED_EXCEPTION(HttpException, System::Details_Exception);
    }

    EXCEPTION_NAMESPACE(System, Runtime)
    {
        EXCEPTION_NAMESPACE(System::Runtime, Serialization)
        {
            /// SerializationException is thrown when an error occurs during serialization or deserialization.
            DECLARE_INHERITED_EXCEPTION_MSG(SerializationException, System::Details_SystemException);
        }
    }
}

EXCEPTION_NAMESPACE(,NUnit)
{
    EXCEPTION_NAMESPACE(NUnit, Framework)
    {
            using System::SystemException;
        /// AssertionException is thrown when an assertion fails.
            DECLARE_INHERITED_EXCEPTION(AssertionException, System::Details_SystemException);
    }
}

/// Macro to open user-defined exception definition.
/// @param ns Namespace the exception belongs to.
/// @param name Name of the exception type (without 'Details_' prefix).
/// @param base Name of the parent exception type (with 'Details_' prefix).
#define CODEPORTING_USER_EXCEPTION_BEGIN(ns, name, base) class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class Details_##name : public base \
{ \
    typedef Details_##name ThisType; \
    typedef base BaseType; \
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo; \
    RTTI_INFO_NAMED(Details_##name, #ns"::"#name, ThisTypeBaseTypesInfo); \
    friend class ::System::ExceptionWrapperHelper; \
    template <typename T> friend class ::System::ExceptionWrapper; \
protected: \
    [[noreturn]] void DoThrow(const ::System::ExceptionPtr& self) const override \
    { \
        throw ::System::ExceptionWrapper<Details_##name>(self); \
    }

/// Macro to close user-defined exception definition.
#define CODEPORTING_USER_EXCEPTION_END };

/// Macro to declare a constructor of a user-defined exception class.
/// After it, either the semicolon or the constructor body must follow.
/// @param name Name of the exception type (without 'Details_' prefix).
/// @param args_with_types Exception parameters with types (usually something like CODEPORTING_ARGS(System::String message, System::String details)).
/// @param args_without_types Exception parameters without types (usually something like CODEPORTING_ARGS(message, details)).
#define CODEPORTING_USER_EXCEPTION_CONSTRUCTOR(name, args_with_types, args_without_types) protected: \
MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(args_with_types), CODEPORTING_ARGS(args_without_types)); \
Details_##name(args_with_types)

/// Macro to open exported user-defined exception definition.
/// @param class_api Class export/import macro (if any).
/// @param method_api Method export/import macro (if any).
/// @param ns Namespace the exception belongs to.
/// @param name Name of the exception type (without 'Details_' prefix).
/// @param base Name of the parent exception type (with 'Details_' prefix).
#define CODEPORTING_DECLARE_USER_EXCEPTION_BEGIN(class_api, method_api, ns, name, base) class Details_##name; \
using name = System::ExceptionWrapper<Details_##name>; \
class class_api Details_##name : public base \
{ \
    typedef Details_##name ThisType; \
    typedef base BaseType; \
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo; \
    RTTI_INFO_NAMED_DECLARE_EXPORTED(method_api, Details_##name, #ns"::"#name, ThisTypeBaseTypesInfo); \
    friend class ::System::ExceptionWrapperHelper; \
    template <typename T> friend class ::System::ExceptionWrapper; \
protected: \
    [[noreturn]] method_api void DoThrow(const ::System::ExceptionPtr& self) const override;

/// Macro to declare an exported constructor of a user-defined exception class.
/// @param method_api Method export/import macro (if any).
/// @param name Name of the exception type (without 'Details_' prefix).
/// @param args_with_types Exception parameters with types (usually something like CODEPORTING_ARGS(System::String message, System::String details)).
/// @param args_without_types Exception parameters without types (usually something like CODEPORTING_ARGS(message, details)).
#define CODEPORTING_EXPORTED_USER_EXCEPTION_CONSTRUCTOR(method_api, name, args_with_types, args_without_types) protected: \
MEMBER_FUNCTION_MAKE_OBJECT(Details_##name, CODEPORTING_ARGS(args_with_types), CODEPORTING_ARGS(args_without_types)); \
method_api Details_##name(args_with_types);

#define CODEPORTING_USER_EXCEPTION_IMPLEMENTATION(class_api, method_api, ns, name, base) \
const ::System::TypeInfo& ns::Details_##name::Type() { \
    return *System::static_holder<ThisTypeInfo>(); \
} \
const System::TypeInfo& ns::Details_##name::GetType() const { \
    return Details_##name::Type(); \
} \
bool ns::Details_##name::Is(const System::TypeInfo &target) const { \
    const System::TypeInfo& thisis = Details_##name::Type(); \
    return (thisis == target) ? true : ThisTypeBaseTypesInfo::CallIsForAll(this, target); \
} \
[[noreturn]] void ns::Details_##name::DoThrow(const ::System::ExceptionPtr& self) const \
{ \
    throw ::System::ExceptionWrapper<Details_##name>(self); \
} \
ns::Details_##name::ThisTypeInfo::ThisTypeInfo() \
    : System::TypeInfoPtr(ASPOSE_T(#ns) ASPOSE_T(#name), 0) \
{ \
}
