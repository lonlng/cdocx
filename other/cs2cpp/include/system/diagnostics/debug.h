/// @file system/diagnostics/debug.h
#pragma once

#include <defines.h>
#include <fwd.h>

namespace System
{

/// @cond
class String;
class Object;
template <class T> class SmartPtr;
template <typename T> using SharedPtr = SmartPtr<T>;
template <class T> class Array;
template <typename T> using ArrayPtr = SmartPtr<Array<T>>;
namespace Collections { namespace Generic {
	template <typename T> class List;
}}  // namespace Collections::Generic
/// @endcond;
	
namespace Diagnostics {

// Prefer to use these macroses, they don't evaluate arguments in release mode.
#if defined(_DEBUG) || defined(DEBUG)
    #define CODEPORTING_DEBUG_FAIL1(message) System::Diagnostics::Debug::Fail(message)
    #define CODEPORTING_DEBUG_ASSERT1(condition) System::Diagnostics::Debug::Assert(condition)
    #define CODEPORTING_DEBUG_ASSERT2(condition, message) System::Diagnostics::Debug::Assert(condition, message)
    #define CODEPORTING_DEBUG_ASSERT3(condition, message, detailMessage) System::Diagnostics::Debug::Assert(condition, message, detailMessage)
	#define CODEPORTING_DEBUG_ASSERT(condition) System::Diagnostics::Debug::Assert((bool)(condition), #condition)
    #define CODEPORTING_DEBUG_WRITELINE1(message) System::Diagnostics::Debug::WriteLine(message)
    #define CODEPORTING_DEBUG_WRITELINE2(message, message2) System::Diagnostics::Debug::WriteLine(message, message2)
    #define CODEPORTING_DEBUG_WRITE1(message) System::Diagnostics::Debug::Write(message)
    #define CODEPORTING_DEBUG_WRITEIF2(condition, message) System::Diagnostics::Debug::WriteIf(condition, message)
    #define CODEPORTING_DEBUG_WRITELINEIF2(condition, message) System::Diagnostics::Debug::WriteLineIf(condition, message)
    #define CODEPORTING_DEBUG_PRINT1(message) System::Diagnostics::Debug::Print(message)
    #define CODEPORTING_DEBUG_PRINT2(format, args) System::Diagnostics::Debug::Print(format, args)
    #define CODEPORTING_DEBUG_GET_LISTENERS() System::Diagnostics::Debug::get_Listeners()
#else
    #define CODEPORTING_DEBUG_FAIL1(message) do { (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_ASSERT1(condition) do { (void)sizeof(condition);} while (0)
    #define CODEPORTING_DEBUG_ASSERT2(condition, message) do { (void)sizeof(condition); (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_ASSERT3(condition, message, detailMessage) do { (void)sizeof(condition); (void)sizeof(message); (void)sizeof(detailMessage);} while (0)
	#define CODEPORTING_DEBUG_ASSERT(condition) do { (void)sizeof(condition); } while (0)
    #define CODEPORTING_DEBUG_WRITELINE1(message) do { (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_WRITELINE2(message, message2) do { (void)sizeof(message); (void)sizeof(message2);} while (0)
    #define CODEPORTING_DEBUG_WRITE1(message) do { (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_WRITEIF2(condition, message) do { (void)sizeof(condition); (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_WRITELINEIF2(condition, message) do { (void)sizeof(condition); (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_PRINT1(message) do { (void)sizeof(message);} while (0)
    #define CODEPORTING_DEBUG_PRINT2(format, args) do { (void)sizeof(format); (void)sizeof(args);} while (0)
    #define CODEPORTING_DEBUG_GET_LISTENERS() System::Diagnostics::Debug::get_Listeners()
#endif

class TraceListener;


/// Collection of debug methods allowing it sending debug information to registered listeners.
/// All output functions work in Debug only.
/// This is a static type with no instance services.
/// You should never create instances of it by any means.
struct Debug
{
    /// Send fail message.
    /// @param message Failure description.
    static ASPOSECPP_SHARED_API void Fail(const String& message);
    /// Assert condition and send information on failure.
    /// @param condition Condition value.
    static ASPOSECPP_SHARED_API void Assert(bool condition);
    /// Assert condition and send information on failure.
    /// @param condition Condition value.
    /// @param message Message to populate on assertion failure.
    static ASPOSECPP_SHARED_API void Assert(bool condition, const String& message);
    /// Assert condition and send information on failure.
    /// @param condition Condition value.
    /// @param message Message to populate on assertion failure.
    static ASPOSECPP_SHARED_API void Assert(bool condition, const char* message);
    /// Assert condition and send information on failure.
    /// @param condition Condition value.
    /// @param message Message to populate on assertion failure.
    /// @param detailMessage Detailed message to populate on assertion failure.
    static ASPOSECPP_SHARED_API void Assert(bool condition, const String& message, const String& detailMessage);
    /// Writes line to debug interface.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void WriteLine(const String& message);
    /// Writes line to debug interface.
    /// @param message Message to write.
    /// @param message2 Extra message.
    static ASPOSECPP_SHARED_API void WriteLine(const String& message, const String& message2);
    /// Writes line to debug interface.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void WriteLine(const char_t* message);
    /// Writes line to debug interface.
    /// @param obj Object to dump.
    static ASPOSECPP_SHARED_API void WriteLine(const SharedPtr<Object>& obj);
    /// Writes string to debug interface.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void Write(const String& message);
    /// Writes string to debug interface.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void Write(const char_t* message);
    /// Writes string to debug interface if a condition is true.
    /// @param condition Condition value.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void WriteIf(bool condition, const System::String& message);
    /// Writes line to debug interface if a condition is true.
    /// @param condition Condition value.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void WriteLineIf(bool condition, const System::String& message);
    /// Print message to debug interface.
    /// @param message Message to write.
    static ASPOSECPP_SHARED_API void Print(const String& message);
    /// Print message to debug interface.
    /// @param format Format string.
    /// @param args Arguments to substitute to format string.
    static ASPOSECPP_SHARED_API void Print(const String& format, const System::ArrayPtr<SharedPtr<System::Object>>& args);

    /// Accesses static list of listeners.
    /// @return List of delegates being envoked on each write operation.
    static ASPOSECPP_SHARED_API System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<TraceListener>>> get_Listeners();
};

}} // namespace System::Diagnostics
