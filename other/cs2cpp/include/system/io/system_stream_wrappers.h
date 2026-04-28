/// @file system/io/system_stream_wrappers.h
#pragma once

#include <iostream>
#include <utility>
#include "system/io/stream.h"
#include "system/bit_converter.h"

namespace System { namespace IO {

/// Specifies the mode of I/O operations that wrappers will perform on System::IO::Stream-like streams.
enum class SystemIOStreamWrappingMode
{
    /// A mode that allows input operations to encode stream bytes into char_type data and decode char_type data into
    /// stream bytes for output operations.
    Binary,
    /// A mode that allows input operations to convert stream bytes from uint8_t type to char_type type and vice versa
    /// for output operations.
    Conversion,
};

/// Represents a buffer that wraps System::IO::Stream-like streams and allows them to be used as an std::iostream-like
/// streams internal buffer.
template <typename Elem, typename Traits = std::char_traits<Elem>>
class BasicSystemIOStreamBuf : public std::basic_streambuf<Elem, Traits>
{
public:
    using char_type = Elem;
    using traits_type = Traits;
    using Mysb = std::basic_streambuf<char_type, traits_type>;

    using int_type = typename traits_type::int_type;
    using pos_type = typename traits_type::pos_type;
    using off_type = typename traits_type::off_type;

    /// Destructor.
    virtual ~BasicSystemIOStreamBuf() override
    {
        Tidy();
    }

    /// Constructs a new instance of the BasicSystemIOStreamBuf.
    explicit BasicSystemIOStreamBuf()
    {
        Tidy();
    }

    /// Constructs a new instance of the BasicSystemIOStreamBuf.
    /// @param str Smart pointer to the stream
    /// @param mode Wrapping mode
    /// @param locale Stream's locale
    explicit BasicSystemIOStreamBuf(const SharedPtr<Stream>& str,
                                    SystemIOStreamWrappingMode mode = SystemIOStreamWrappingMode::Binary,
                                    const std::locale& locale = std::locale())
        : m_stream(str), m_wrapping_mode(mode), m_elem_size(sizeof(char_type))
    {}

    /// Copy constructor. Deleted.
    BasicSystemIOStreamBuf(const BasicSystemIOStreamBuf&) = delete;

    /// Move constructor.
    /// @param right Object to be move
    BasicSystemIOStreamBuf(BasicSystemIOStreamBuf&& right) noexcept
    {
        AssignRV(std::move(right));
    }

    /// Copy assignment operator. Deleted.
    BasicSystemIOStreamBuf& operator=(const BasicSystemIOStreamBuf&) = delete;

    /// Move assignment operator.
    /// @param right Object to be move
    /// @returns *this
    BasicSystemIOStreamBuf& operator=(BasicSystemIOStreamBuf&& right) noexcept
    {
        AssignRV(std::move(right));
        return *this;
    }

    /// Used in move constructor and move assignment operator to reset pointers and call swap().
    /// @param right Rvalue reference to object to be swap
    void AssignRV(BasicSystemIOStreamBuf&& right)
    {
        if (this != std::addressof(right))
        {
            Tidy();
            this->swap(right);
        }
    }

    /// Call to swap *this and right, if they are not equal.
    /// @param right Rvalue reference to object to be swap
    void swap(BasicSystemIOStreamBuf& right)
    {
        if (this != std::addressof(right))
        {
            Mysb::swap(right);
            std::swap(m_stream, right.m_stream);
            std::swap(m_wrapping_mode, right.m_wrapping_mode);
            std::swap(m_elem_size, right.m_elem_size);
        }
    }

protected:
    /// Put a character to the stream and advances one position forward.
    /// @param meta A character to be put
    /// @returns If succeeded, returns new position. Otherwice returns -1
    virtual int_type overflow(int_type meta = traits_type::eof()) override
    {
        try
        {
            if (traits_type::eq_int_type(traits_type::eof(), meta))
            {
                return traits_type::not_eof(meta);
            }

            if (!m_stream->get_CanWrite())
            {
                return traits_type::eof();
            }

            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion || m_elem_size == 1)
            {
                m_stream->WriteByte(uint8_t(meta));
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                auto decoded_elem = BitConverter::GetBytes(meta);
                for (int i = 0; i < decoded_elem->get_Length(); ++i)
                {
                    m_stream->WriteByte(decoded_elem[i]);
                }
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");

            return meta;
        }
        catch (const Exception&)
        {
            return traits_type::eof();
        }
    }

    /// Get an element from stream, but don't advances position.
    /// @returns If succeeded, returns current position. Otherwice returns -1
    virtual int_type underflow() override
    {
        try
        {
            if (!m_stream->get_CanRead())
            {
                return traits_type::eof();
            }

            pos_type pos = m_stream->get_Position();
            int64_t offset = pos;
            int_type meta;
            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion || m_elem_size == 1)
            {
                offset = 1;
                int byte = m_stream->ReadByte();
                if (byte == -1)
                {
                    return traits_type::eof();
                }

                meta = int_type(byte);
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                offset = m_elem_size;
                if (m_stream->get_Length() - m_stream->get_Position() < m_elem_size)
                {
                    return traits_type::eof();
                }

                auto dst = (uint8_t*)&meta;
                if (System::BitConverter::_IsLittleEndian())
                {
                    for (int i = 0; i < m_elem_size; ++i)
                    {
                        dst[i] = uint8_t(m_stream->ReadByte());
                    }
                }
                else
                {
                    for (int i = m_elem_size - 1; i >= 0; --i)
                    {
                        dst[i] = uint8_t(m_stream->ReadByte());
                    }
                }
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");

            if (pos != m_stream->get_Position())
            { // if the stream is not a wrapper over std::cin or std::wcin
                m_stream->Seek(-offset, SeekOrigin::Current);
            }

            return meta;
        }
        catch (const Exception&)
        {
            return traits_type::eof();
        }
    }

    /// Get an element from stream and advances one position forward.
    /// @returns If succeeded, returns new position. Otherwice returns -1
    virtual int_type uflow() override
    {
        try
        {
            if (!m_stream->get_CanRead())
            {
                return traits_type::eof();
            }

            int_type meta;
            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion || m_elem_size == 1)
            {
                int byte = m_stream->ReadByte();
                if (byte == -1)
                {
                    return traits_type::eof();
                }

                meta = int_type(byte);
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                if (m_stream->get_Length() - m_stream->get_Position() < m_elem_size)
                {
                    return traits_type::eof();
                }

                auto dst = (uint8_t*)&meta;
                if (System::BitConverter::_IsLittleEndian())
                {
                    for (int i = 0; i < m_elem_size; ++i)
                    {
                        dst[i] = uint8_t(m_stream->ReadByte());
                    }
                }
                else
                {
                    for (int i = m_elem_size - 1; i >= 0; --i)
                    {
                        dst[i] = uint8_t(m_stream->ReadByte());
                    }
                }
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");

            return meta;
        }
        catch (const Exception&)
        {
            return traits_type::eof();
        }
    }

    /// Put an element to stream on previous position.
    /// @param meta A character to be put
    /// @returns If succeeded, returns new position. Otherwice returns -1
    virtual int_type pbackfail(int_type meta = traits_type::eof()) override
    {
        try
        {
            if (traits_type::eq_int_type(traits_type::eof(), meta))
            {
                return traits_type::not_eof(meta);
            }

            int offset;
            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion)
            {
                offset = 1;
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                offset = m_elem_size;
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");

            if (!m_stream->get_CanSeek() || !(m_stream->get_CanWrite() || m_stream->get_CanRead()) ||
                m_stream->Seek(-offset, SeekOrigin::Current) == -1)
            {
                return traits_type::eof();
            }

            if (m_stream->get_CanWrite())
            {
                overflow(meta);
                m_stream->Seek(-offset, SeekOrigin::Current);
            }
            else if (m_stream->get_CanRead())
            {
                int_type cur_meta = uflow();

                if (traits_type::eq_int_type(cur_meta, meta))
                {
                    m_stream->Seek(-offset, SeekOrigin::Current);
                }
                else
                {
                    return traits_type::eof();
                }
            }

            return traits_type::not_eof(meta);
        }
        catch (const Exception&)
        {
            return traits_type::eof();
        }
    }

    /// Change position by @p off, according to @p way, @p mode.
    /// @param off Offset value, relative to the way parameter
    /// @param way Object of type std::ios_base::seekdir, indicating the origin from which the offset is applied
    /// @param mode Generally used to determine the position on which of the controlled sequences shall be modified:
    /// the input sequence, the output sequence, or both
    /// @returns If succeeded, returns new position. Otherwice returns -1
    virtual pos_type seekoff(off_type off, std::ios_base::seekdir way,
                             std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override
    {
        try
        {
            if (!m_stream->get_CanSeek())
            {
                return pos_type(off_type(-1));
            }

            int64_t offset;
            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion)
            {
                offset = off;
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                offset = off * m_elem_size;
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");

            SeekOrigin origin = SeekOrigin::Current;
            if (way == std::ios_base::beg)
            {
                origin = SeekOrigin::Begin;
            }
            else if (way == std::ios_base::cur)
            {
                origin = SeekOrigin::Current;
            }
            else if (way == std::ios_base::end)
            {
                origin = SeekOrigin::End;
            }

            return m_stream->Seek(offset, origin);
        }
        catch (const Exception&)
        {
            return pos_type(off_type(-1));
        }
    }

    /// Set position pointer to absolute @p pos position.
    /// @param pos New absolute position for the position pointer
    /// @param mode Generally used to determine the position on which of the controlled sequences shall be modified:
    /// the input sequence, the output sequence, or both
    /// @returns If succeeded, returns new position. Otherwice returns -1
    virtual pos_type seekpos(pos_type pos,
                             std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override
    {
        try
        {
            if (!m_stream->get_CanSeek())
            {
                return pos_type(off_type(-1));
            }

            int64_t value;
            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion)
            {
                value = int64_t(pos);
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                value = int64_t(pos * m_elem_size);
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");

            m_stream->set_Position(value);
            return m_stream->get_Position();
        }
        catch (const Exception&)
        {
            return pos_type(off_type(-1));
        }
    }

    /// Get number of characters available.
    virtual std::streamsize showmanyc() override
    {
        try
        {
            if (!m_stream->get_CanSeek() || !m_stream->get_CanRead())
            {
                return traits_type::eof();
            }

            pos_type cur = m_stream->get_Position();
            off_type length = m_stream->get_Length();

            if (m_wrapping_mode == SystemIOStreamWrappingMode::Conversion)
            {
                return length - cur;
            }
            else if (m_wrapping_mode == SystemIOStreamWrappingMode::Binary)
            {
                return (length - cur) / m_elem_size;
            }
            else
                throw NotSupportedException(u"Wrapper does not support current wrapping mode.");
        }
        catch (const Exception&)
        {
            return traits_type::eof();
        }
    }

    /// Set all pointers to nullptr.
    void Tidy()
    {
        Mysb::setg(nullptr, nullptr, nullptr);
        Mysb::setp(nullptr, nullptr);
        m_stream.reset();
    }

private:
    /// Pointer to the stream.
    SharedPtr<Stream> m_stream;
    /// Wrapping mode
    SystemIOStreamWrappingMode m_wrapping_mode;
    /// char_type size = sizeof(char_type).
    uint8_t m_elem_size;
};

/// Represents a std::istream-like wrapper that used BasicSystemIOStreamBuf as internal buffer.
template <typename Elem, typename Traits = std::char_traits<Elem>>
class BasicSystemIStreamWrapper : public std::basic_istream<Elem, Traits>
{
public:
    using char_type = Elem;
    using traits_type = Traits;
    using Mybase = std::basic_istream<char_type, traits_type>;
    using Mysb = BasicSystemIOStreamBuf<char_type, traits_type>;

    /// Constructs a new instance of the BasicSystemIStreamWrapper.
    /// @param str The pointer to the stream
    /// @param mode Wrapping mode
    BasicSystemIStreamWrapper(SharedPtr<Stream> str,
                              SystemIOStreamWrappingMode mode = SystemIOStreamWrappingMode::Binary)
        : Mybase(std::addressof(m_stream_buffer)), m_stream_buffer(str, mode, std::ios_base::getloc())
    {}

    /// Copy constructor. Deleted.
    BasicSystemIStreamWrapper(const BasicSystemIStreamWrapper&) = delete;

    /// Move constructor.
    /// @param right Object to be move
    BasicSystemIStreamWrapper(BasicSystemIStreamWrapper&& right) noexcept : Mybase(std::addressof(m_stream_buffer))
    {
        AssignRV(std::move(right));
    }

    /// Copy assignment operator. Deleted.
    BasicSystemIStreamWrapper& operator=(const BasicSystemIStreamWrapper&) = delete;

    /// Move assignment operator.
    /// @param right Object to be move
    /// @returns *this
    BasicSystemIStreamWrapper& operator=(BasicSystemIStreamWrapper&& right) noexcept
    {
        AssignRV(std::move(right));
        return *this;
    }

    /// Used in move constructor and move assignment operator to reset pointers and call swap().
    /// @param right Rvalue reference to object to be swap
    void AssignRV(BasicSystemIStreamWrapper&& right)
    {
        if (this != std::addressof(right))
        {
            this->swap(right);
        }
    }

    /// Call to swap *this and @p right, if they are not equal.
    /// @param right Rvalue reference to object to be swap
    void swap(BasicSystemIStreamWrapper& right)
    {
        if (this != std::addressof(right))
        {
            Mybase::swap(right);
            m_stream_buffer.swap(right.m_stream_buffer);
        }
    }

private:
    /// Internal buffer
    Mysb m_stream_buffer;
};

/// Represents a std::ostream-like wrapper that used BasicSystemIOStreamBuf as internal buffer.
template <typename Elem, typename Traits = std::char_traits<Elem>>
class BasicSystemOStreamWrapper : public std::basic_ostream<Elem, Traits>
{
public:
    using char_type = Elem;
    using traits_type = Traits;
    using Mybase = std::basic_ostream<char_type, traits_type>;
    using Mysb = BasicSystemIOStreamBuf<char_type, traits_type>;

    /// Constructs a new instance of the BasicSystemOStreamWrapper.
    /// @param str The pointer to the stream
    /// @param mode Wrapping mode
    BasicSystemOStreamWrapper(SharedPtr<Stream> str,
                              SystemIOStreamWrappingMode mode = SystemIOStreamWrappingMode::Binary)
        : Mybase(std::addressof(m_stream_buffer)), m_stream_buffer(str, mode, std::ios_base::getloc())
    {}

    /// Copy constructor. Deleted.
    BasicSystemOStreamWrapper(const BasicSystemOStreamWrapper&) = delete;

    /// Move constructor.
    /// @param right Object to be move
    BasicSystemOStreamWrapper(BasicSystemOStreamWrapper&& right) noexcept : Mybase(std::addressof(m_stream_buffer))
    {
        AssignRV(std::move(right));
    }

    /// Copy assignment operator. Deleted.
    BasicSystemOStreamWrapper& operator=(const BasicSystemOStreamWrapper&) = delete;

    /// Move assignment operator.
    /// @param right Object to be move
    /// @returns *this
    BasicSystemOStreamWrapper& operator=(BasicSystemOStreamWrapper&& right) noexcept
    {
        AssignRV(std::move(right));
        return *this;
    }

    /// Used in move constructor and move assignment operator to reset pointers and call swap().
    /// @param right Rvalue reference to object to be swap
    void AssignRV(BasicSystemOStreamWrapper&& right)
    {
        if (this != std::addressof(right))
        {
            this->swap(right);
        }
    }

    /// Call to swap *this and @p right, if they are not equal.
    /// @param right Rvalue reference to object to be swap
    void swap(BasicSystemOStreamWrapper& right)
    {
        if (this != std::addressof(right))
        {
            Mybase::swap(right);
            m_stream_buffer.swap(right.m_stream_buffer);
        }
    }

private:
    /// Internal buffer
    Mysb m_stream_buffer;
};

/// Represents a std::iostream-like wrapper that used BasicSystemIOStreamBuf as internal buffer.
template <typename Elem, typename Traits = std::char_traits<Elem>>
class BasicSystemIOStreamWrapper : public std::basic_iostream<Elem, Traits>
{
public:
    using char_type = Elem;
    using traits_type = Traits;
    using Mybase = std::basic_iostream<char_type, traits_type>;
    using Mysb = BasicSystemIOStreamBuf<char_type, traits_type>;

    /// Constructs a new instance of the BasicSystemIOStreamWrapper.
    /// @param str The pointer to the stream
    /// @param mode Wrapping mode
    BasicSystemIOStreamWrapper(SharedPtr<Stream> str,
                               SystemIOStreamWrappingMode mode = SystemIOStreamWrappingMode::Binary)
        : Mybase(std::addressof(m_stream_buffer)), m_stream_buffer(str, mode, std::ios_base::getloc())
    {}

    /// Copy constructor. Deleted.
    BasicSystemIOStreamWrapper(const BasicSystemIOStreamWrapper&) = delete;

    /// Move constructor.
    /// @param right Object to be move
    BasicSystemIOStreamWrapper(BasicSystemIOStreamWrapper&& right) noexcept : Mybase(std::addressof(m_stream_buffer))
    {
        AssignRV(std::move(right));
    }

    /// Copy assignment operator. Deleted.
    BasicSystemIOStreamWrapper& operator=(const BasicSystemIOStreamWrapper&) = delete;

    /// Move assignment operator.
    /// @param right Object to be move
    /// @returns *this
    BasicSystemIOStreamWrapper& operator=(BasicSystemIOStreamWrapper&& right) noexcept
    {
        AssignRV(std::move(right));
        return *this;
    }

    /// Used in move constructor and move assignment operator to reset pointers and call swap().
    /// @param right Rvalue reference to object to be swap
    void AssignRV(BasicSystemIOStreamWrapper&& right)
    {
        if (this != std::addressof(right))
        {
            this->swap(right);
        }
    }

    /// Call to swap *this and @p right, if they are not equal.
    /// @param right Rvalue reference to object to be swap
    void swap(BasicSystemIOStreamWrapper& right)
    {
        if (this != std::addressof(right))
        {
            Mybase::swap(right);
            m_stream_buffer.swap(right.m_stream_buffer);
        }
    }

private:
    /// Internal buffer
    Mysb m_stream_buffer;
};

/// Specializations of BasicSystemIStreamWrapper for char character types.
using SystemIStreamWrapper = BasicSystemIStreamWrapper<char, std::char_traits<char>>;
/// Specializations of BasicSystemIStreamWrapper for wchar_t character types.
using SystemWIStreamWrapper = BasicSystemIStreamWrapper<wchar_t, std::char_traits<wchar_t>>;
/// Specializations of BasicSystemOStreamWrapper for char character types.
using SystemOStreamWrapper = BasicSystemOStreamWrapper<char, std::char_traits<char>>;
/// Specializations of BasicSystemOStreamWrapper for wchar_t character types.
using SystemWOStreamWrapper = BasicSystemOStreamWrapper<wchar_t, std::char_traits<wchar_t>>;
/// Specializations of BasicSystemIOStreamWrapper for char character types.
using SystemIOStreamWrapper = BasicSystemIOStreamWrapper<char, std::char_traits<char>>;
/// Specializations of BasicSystemIOStreamWrapper for wchar_t character types.
using SystemWIOStreamWrapper = BasicSystemIOStreamWrapper<wchar_t, std::char_traits<wchar_t>>;

}} // namespace System::IO

namespace std {
/// Call to swap @p left and @p right, if they are not equal.
/// @param left Rvalue reference to object to be swap
/// @param right Rvalue reference to object to be swap
template <typename char_type, typename traits_type>
void swap(System::IO::BasicSystemIOStreamBuf<char_type, traits_type>& left,
          System::IO::BasicSystemIOStreamBuf<char_type, traits_type>& right)
{
    left.swap(right);
}

/// Call to swap @p left and @p right, if they are not equal.
/// @param left Rvalue reference to object to be swap
/// @param right Rvalue reference to object to be swap
template <typename char_type, typename traits_type>
void swap(System::IO::BasicSystemIStreamWrapper<char_type, traits_type>& left,
          System::IO::BasicSystemIStreamWrapper<char_type, traits_type>& right)
{
    left.swap(right);
}

/// Call to swap @p left and @p right, if they are not equal.
/// @param left Rvalue reference to object to be swap
/// @param right Rvalue reference to object to be swap
template <typename char_type, typename traits_type>
void swap(System::IO::BasicSystemOStreamWrapper<char_type, traits_type>& left,
          System::IO::BasicSystemOStreamWrapper<char_type, traits_type>& right)
{
    left.swap(right);
}

/// Call to swap @p left and @p right, if they are not equal.
/// @param left Rvalue reference to object to be swap
/// @param right Rvalue reference to object to be swap
template <typename char_type, typename traits_type>
void swap(System::IO::BasicSystemIOStreamWrapper<char_type, traits_type>& left,
          System::IO::BasicSystemIOStreamWrapper<char_type, traits_type>& right)
{
    left.swap(right);
}
} // namespace std
