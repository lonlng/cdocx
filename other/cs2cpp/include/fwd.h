/// @file fwd.h
#ifndef __fwd_h__
#define __fwd_h__

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <locale>
#include <codecvt>
#include <string>

/// Information on enum values naming for serialization purposes.
template<class T>
struct EnumMetaInfo; // declared out of System namespace

// Forward declarations
namespace System {

    class IFormatProvider;

    template<class T>
    class SmartPtr;

    namespace Text {
        class DecoderFallback;
        class DecoderFallbackBuffer;
        class DecoderReplacementFallback;
        class EncoderFallback;
        class EncoderFallbackBuffer;
        class Encoder;
        class Decoder;
        class Encoding;
        class EncodingInfo;
        class EncoderReplacementFallbackBuffer;
        class EncoderReplacementFallback;
    }

    namespace IO {
        class Stream;
        class FileStream;
        class MemoryStream;
        class StreamReader;
        class StreamWriter;
        class FileInfo;
        class FileSystemInfo;
        class DirectoryInfo;
    }


    namespace Drawing {
        class SizeF;
        class PointF;
        class Size;
        class Point;
        class Rectangle;
        class RectangleF;
    }

    namespace Globalization
    {
        class CultureInfo;
    }

    namespace Threading {
        class CancellationToken;
        namespace Tasks {
            class Task;
            template <typename T>
            class ResultTask;
        }} // namespace Threading::Tasks

// Pointer typedefs
/// An alias for a smart pointer that points to an instance of System::IFormatProvider class.
typedef System::SmartPtr<System::IFormatProvider>                          IFormatProviderPtr;
/// An alias for a smart pointer that points to an instance of System::Text::DecoderFallback class.
typedef System::SmartPtr<System::Text::DecoderFallback>                    DecoderFallbackPtr;
/// An alias for a smart pointer that points to an instance of System::Text::DecoderFallbackBuffer class.
typedef System::SmartPtr<System::Text::DecoderFallbackBuffer>              DecoderFallbackBufferPtr;
/// An alias for a smart pointer that points to an instance of System::Text::DecoderReplacementFallback class.
typedef System::SmartPtr<System::Text::DecoderReplacementFallback>         DecoderReplacementFallbackPtr;
/// An alias for a smart pointer that points to an instance of System::Text::EncoderFallback class.
typedef System::SmartPtr<System::Text::EncoderFallback>                    EncoderFallbackPtr;
/// An alias for a smart pointer that points to an instance of System::Text::EncoderFallbackBuffer class.
typedef System::SmartPtr<System::Text::EncoderFallbackBuffer>              EncoderFallbackBufferPtr;
/// An alias for a smart pointer that points to an instance of System::Text::Encoder class.
typedef System::SmartPtr<System::Text::Encoder>                            EncoderPtr;
/// An alias for a smart pointer that points to an instance of System::Text::Decoder class.
typedef System::SmartPtr<System::Text::Decoder>                            DecoderPtr;
/// An alias for a smart pointer that points to an instance of System::Text::EncoderReplacementFallbackBuffer class.
typedef System::SmartPtr<System::Text::EncoderReplacementFallbackBuffer>   EncoderReplacementFallbackBufferPtr;
/// An alias for a smart pointer that points to an instance of System::Text::EncoderReplacementFallback class.
typedef System::SmartPtr<System::Text::EncoderReplacementFallback>         EncoderReplacementFallbackPtr;
/// An alias for a smart pointer that points to an instance of System::Text::Encoding class.
typedef System::SmartPtr<System::Text::Encoding>                           EncodingPtr;
/// An alias for a smart pointer that points to an instance of System::Text::EncodingInfo class.
typedef System::SmartPtr<System::Text::EncodingInfo>                       EncodingInfoPtr;

/// An alias for a smart pointer that points to an instance of System::IO::Stream class.
typedef System::SmartPtr<System::IO::Stream>                               StreamPtr;
/// An alias for a smart pointer that points to an instance of System::IO::FileStream class.
typedef System::SmartPtr<System::IO::FileStream>                           FileStreamPtr;
/// An alias for a smart pointer that points to an instance of System::IO::MemoryStream class.
typedef System::SmartPtr<System::IO::MemoryStream>                         MemoryStreamPtr;
/// An alias for a smart pointer that points to an instance of System::IO::StreamReader class.
typedef System::SmartPtr<System::IO::StreamReader>                         StreamReaderPtr;
/// An alias for a smart pointer that points to an instance of System::IO::StreamWriter class.
typedef System::SmartPtr<System::IO::StreamWriter>                         StreamWriterPtr;

/// An alias for a smart pointer that points to an instance of System::IO::FileInfo class.
typedef System::SmartPtr<System::IO::FileInfo>                             FileInfoPtr;
/// An alias for a smart pointer that points to an instance of System::IO::FileSystemInfo class.
typedef System::SmartPtr<System::IO::FileSystemInfo>                       FileSystemInfoPtr;
/// An alias for a smart pointer that points to an instance of System::IO::DirectoryInfo class.
typedef System::SmartPtr<System::IO::DirectoryInfo>                        DirectoryInfoPtr;

/// An alias for a smart pointer that points to an instance of System::Threading::Tasks::Task class.
typedef System::SmartPtr<System::Threading::Tasks::Task>                   TaskPtr;
/// An alias for a smart pointer that points to an instance of System::Threading::Tasks::ResultTask class.
template<typename T>
using RTaskPtr = System::SmartPtr<System::Threading::Tasks::ResultTask<T>>;

/// An alias for function type with default calling convention
template <typename ReturnT, typename... ArgsT>
using FunctionPtr = ReturnT(*)(ArgsT...);
}

// Common typedefs

/// Character type used by the library.
typedef char16_t char_t;

/// Selects IntPtr type.
struct IntPtr_helper
    : std::enable_if<sizeof(void*) == sizeof(uint32_t), uint32_t>
    , std::enable_if<sizeof(void*) == sizeof(uint64_t), uint64_t>
{};
/// Shortest integral type possible to hold pointer value.
typedef IntPtr_helper::type IntPtr;
static_assert(sizeof(void*) == sizeof(IntPtr), "Failed to set up IntPtr type");
/// Nullptr value.
const IntPtr IntPtrZero = 0;

/// Prefixes string literals to use with char_t.
#define ASPOSE_T(x) u##x

/// Prefixes string literals to use with wchar_t.
#define __WIDEN2(quote) L##quote
/// Prefixes string literals to use with wchar_t.
#define __WIDEN(quote) __WIDEN2(quote)

/// Converts expression to string literal.
#define __QUOTE1(x) #x
/// Converts expression to string literal.
#define __QUOTE2(x) __QUOTE1(x)

#if defined(__GNUC__) || defined (__clang__)
    // under gcc __PRETTY_FUNCTION__ is a variable, so it is impossible to widen :(
    /// Current function name
    #define ASPOSE_CURRENT_FUNCTION System::Details::Utf8To16String(__PRETTY_FUNCTION__).c_str()
    /// Current function name and line.
    #define ASPOSE_CURRENT_FUNCTION_LINE System::Details::Utf8To16String((std::string(__PRETTY_FUNCTION__) + ":" + std::string(__QUOTE2(__LINE__))).c_str()).c_str()
#elif defined(_MSC_VER)
    /// Current function name
    #define ASPOSE_CURRENT_FUNCTION reinterpret_cast<const char16_t*>(__WIDEN(__FUNCSIG__))
    #define ASPOSE_CURRENT_FUNCTION_LINE reinterpret_cast<const char16_t*>(__WIDEN(__FUNCSIG__ ":" __QUOTE2(__LINE__)))
#else
    /// Current function name - unsupported.
    #define ASPOSE_CURRENT_FUNCTION u""
    /// Current function name and line - unsupported.
    #pragma message("ASPOSE_CURRENT_FUNCTION is undefined!")
#endif

#endif // __fwd_h__
