/// @file system/io/std_stream_wrappers.h
#pragma once

#include <iostream>
#include <vector>
#include "system/io/stream.h"
#include "system/bit_converter.h"
#include "system/details/is_template_base_of.h"

namespace System { namespace IO {

using System::Details::IsTemplateBaseOf;

/// Specifies the mode of I/O operations that wrappers will perform on std::iostreams-like streams.
enum class STDIOStreamWrappingMode
{
    /// A mode that allows input operations to decode stream data of char_type type into bytes, and encode bytes into
    /// char_type data for output operations.
    Binary,
    /// A mode that allows input operations to convert stream data from char_type type to uint8_t type and vice versa
    /// for output operations.
    Conversion,
};

/// Determines which position in the stream is preferable as a common read and write position when std::basic_iostream
/// and its descendants will have different read and write positions at the time of wrapper creation.
enum class STDIOStreamPositionPreference
{
    /// Zero position will sets as a read and write position.
    Zero,
    /// gptr position will sets as a read and write position.
    ReadPosition,
    /// pptr position will sets as a read and write position.
    WritePosition,
};

/// Represents a base class for System.IO.Stream-like wrappers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or
/// assertion faults. Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions
/// as argument.
template <typename T, typename = std::enable_if_t<IsTemplateBaseOf<std::basic_ios, T>::value>>
class STDIOStreamWrapperBase : public Stream
{
public:
    using ThisType = STDIOStreamWrapperBase<T>;
    using BaseType = Stream;
    using ThisTypeBaseTypesInfo = BaseTypesInfo<BaseType>;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    using char_type = typename T::char_type;
    using traits_type = typename T::traits_type;

    using int_type = typename T::int_type;
    using pos_type = typename T::pos_type;
    using off_type = typename T::off_type;

    /// Copy constructor. Deleted.
    STDIOStreamWrapperBase(const STDIOStreamWrapperBase&) = delete;

    /// Copy assignment operator. Deleted.
    STDIOStreamWrapperBase& operator=(const STDIOStreamWrapperBase&) = delete;

    /// Sets the position of the stream represented by the current object.
    /// @param offset The byte offset relative to a position specified by @p origin
    /// @param origin Specifies the position from which and the direction toward which the offset is calculated
    /// @returns The new position of the stream
    virtual int64_t Seek(int64_t offset, SeekOrigin origin) override
    {
        Check();

        if (origin < SeekOrigin::Begin || origin > SeekOrigin::End)
            throw ArgumentException(u"Invalid SeekOrigin enum value", u"origin");

        if (!get_CanSeek())
            throw NotSupportedException(u"Can't seek stream.");

        int64_t new_pos;
        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            if (origin == SeekOrigin::Begin)
            {
                new_pos = offset;
            }
            else if (origin == SeekOrigin::Current)
            {
                new_pos = m_elem_pos + offset;
            }
            else
            {
                new_pos = m_length + offset;
            }

            if (new_pos < 0)
                throw ArgumentOutOfRangeException(u"Seeking is attempted before the beginning of the stream.");

            if (new_pos == m_elem_pos)
                return m_elem_pos;

            Pubseekpos(new_pos);
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            if (origin == SeekOrigin::Begin)
            {
                new_pos = offset;
            }
            else if (origin == SeekOrigin::Current)
            {
                new_pos = m_byte_pos + offset;
            }
            else
            {
                new_pos = m_length * m_elem_size + offset;
            }

            if (new_pos < 0)
                throw ArgumentOutOfRangeException(u"Seeking is attempted before the beginning of the stream.");

            if (new_pos == m_byte_pos)
                return m_byte_pos;

            bool has_new_byte_pos_shift = new_pos % m_elem_size != 0;
            int64_t new_elem_pos = Pubseekpos(new_pos / m_elem_size + int(has_new_byte_pos_shift));
            if (new_elem_pos != -1)
            {
                m_byte_pos = new_pos;
                if (has_new_byte_pos_shift)
                {
                    Pubseekpos(new_elem_pos - 1);
                }

                DecodeElem(m_stream.rdbuf()->sgetc());
            }
        }

        Sync();
        return new_pos;
    }

    /// Sets the stream's position.
    /// @param value Value to set the stream's position
    virtual void set_Position(int64_t value) override
    {
        Check();

        if (!get_CanSeek())
            throw NotSupportedException(u"Can't seek stream.");

        if (value < 0)
            throw ArgumentOutOfRangeException(u"value must be non-negative");

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            if (value == m_elem_pos)
                return;

            Pubseekpos(value);
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            if (value == m_byte_pos)
                return;

            int64_t new_byte_pos = value;
            bool has_new_byte_pos_shift = new_byte_pos % m_elem_size != 0;
            int64_t new_elem_pos = Pubseekpos(new_byte_pos / m_elem_size + int(has_new_byte_pos_shift));
            if (new_elem_pos != -1)
            {
                m_byte_pos = new_byte_pos;
                if (has_new_byte_pos_shift)
                {
                    Pubseekpos(new_elem_pos - 1);
                }

                DecodeElem(m_stream.rdbuf()->sgetc());
            }
        }

        Sync();
    }

    /// Returns current position of the stream.
    virtual int64_t get_Position() const override
    {
        Check();

        if (!get_CanSeek())
            throw NotSupportedException(u"Can't seek stream.");

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            return m_elem_pos;
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            return m_byte_pos;
        }
    }

    /// Returns length of the stream.
    virtual int64_t get_Length() const override
    {
        Check();

        if (!get_CanSeek())
            throw NotSupportedException(u"Can't seek stream.");

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            return m_length;
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            return m_length * m_elem_size;
        }
    }

    /// Determines if the stream supports reading.
    virtual bool get_CanRead() const override
    {
        return m_can_read && !m_stream.fail();
    }

    /// Determines if the stream supports seeking.
    virtual bool get_CanSeek() const override
    {
        return m_can_seek && !m_stream.fail();
    }

    /// Determines if the stream supports writing.
    virtual bool get_CanWrite() const override
    {
        return m_can_write && !m_stream.fail();
    }

protected:
    /// Constructs a new instance of the STDIOStreamWrapperBase.
    /// @param str A reference to the std::iostream-like stream
    /// @param mode Wrapping mode
    /// @param can_read CanRead flag
    /// @param can_write CanWrite flag
    /// @param can_seek CanSeek flag
    /// @param pref_pos Position that will prefer as read and write position, if they are different
    STDIOStreamWrapperBase(std::basic_ios<char_type, traits_type>& str,
                           STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary, bool can_read = false,
                           bool can_write = false, bool can_seek = false,
                           STDIOStreamPositionPreference pref_pos = STDIOStreamPositionPreference::Zero)
        : m_stream(str), m_wrapping_mode(mode), m_can_read(can_read), m_can_write(can_write), m_can_seek(can_seek)
    {
        m_last_elem_gpos =
            can_read ? int64_t(m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in)) : int64_t(0);
        m_last_elem_ppos =
            can_write ? int64_t(m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out)) : int64_t(0);
        if (!m_can_seek)
        {
            m_elem_pos = 0;
            m_byte_pos = 0;
            m_length = 0;
        }
        else
        {
            if (m_can_read && m_can_write && m_last_elem_gpos != m_last_elem_ppos)
            {
                switch (pref_pos)
                {
                case STDIOStreamPositionPreference::Zero:
                    m_last_elem_gpos = 0;
                    m_last_elem_ppos = 0;
                    m_elem_pos = 0;
                    break;
                case STDIOStreamPositionPreference::ReadPosition:
                    m_last_elem_ppos = m_last_elem_gpos;
                    m_elem_pos = m_last_elem_gpos;
                    break;
                case STDIOStreamPositionPreference::WritePosition:
                    m_last_elem_gpos = m_last_elem_ppos;
                    m_elem_pos = m_last_elem_ppos;
                    break;
                default:
                    // nothing to do
                    break;
                }

                int64_t end = m_stream.rdbuf()->pubseekoff(0, std::ios_base::end, std::ios_base::in);
                int64_t beg = m_stream.rdbuf()->pubseekoff(0, std::ios_base::beg, std::ios_base::in);
                m_length = end - beg;
                m_stream.rdbuf()->pubseekpos(m_elem_pos, std::ios_base::in);
            }
            else if (m_can_read)
            {
                m_elem_pos = m_last_elem_gpos;

                int64_t end = m_stream.rdbuf()->pubseekoff(0, std::ios_base::end, std::ios_base::in);
                int64_t beg = m_stream.rdbuf()->pubseekoff(0, std::ios_base::beg, std::ios_base::in);
                m_length = end - beg;
                m_stream.rdbuf()->pubseekpos(m_elem_pos, std::ios_base::in);
            }
            else
            {
                m_elem_pos = m_last_elem_ppos;

                int64_t end = m_stream.rdbuf()->pubseekoff(0, std::ios_base::end, std::ios_base::out);
                int64_t beg = m_stream.rdbuf()->pubseekoff(0, std::ios_base::beg, std::ios_base::out);
                m_length = end - beg;
                m_stream.rdbuf()->pubseekpos(m_elem_pos, std::ios_base::out);
            }

            if (m_wrapping_mode == STDIOStreamWrappingMode::Binary)
            {
                m_byte_pos = m_elem_pos * m_elem_size;
            }
        }
    }

    /// Seeks positions of read or write or both on @p value.
    /// @param value Seeked position
    /// @returns A new position if the seek is successful, otherwise -1
    virtual int64_t Pubseekpos(int64_t value) = 0;

    /// Check if the stream has been modified outside the wrapper.
    virtual void Check() const
    {
        if (m_wrapping_mode < STDIOStreamWrappingMode::Binary || m_wrapping_mode > STDIOStreamWrappingMode::Conversion)
            throw NotSupportedException(u"Wrapper does not support current wrapping mode.");
    };

    /// Synchronizes positions of read or write or both.
    virtual void Sync() = 0;

    /// Decodes @p meta and store result in the last decoded element storage.
    /// @param meta Meta character to decode
    void DecodeElem(int_type meta)
    {
        DecodeElem(meta, m_decoded_elem);
    }

    /// Decodes @p meta and store result in the @p destination.
    /// @param meta Meta character to decode
    /// @param destination Reference to decoded element storage
    void DecodeElem(int_type meta, ArrayPtr<uint8_t>& destination)
    {
        if (traits_type::eq_int_type(meta, traits_type::eof()))
        {
            destination.reset();
        }
        else
        {
            destination = BitConverter::GetBytes(meta);
        }
    }

    /// Encodes the last decoded element storage.
    /// @returns Encoded character
    char_type EncodeElem()
    {
        return EncodeElem(m_decoded_elem->data_ptr());
    }

    /// Encodes @p source.
    /// @param source Pointer to decoded element storage
    /// @returns Encoded character
    char_type EncodeElem(uint8_t* source)
    {
        char_type result;
        EncodeElem(source, &result);
        return result;
    }

    /// Encodes @p source to @p destination.
    /// @param source Pointer to decoded element storage
    /// @param destination Pointer to the character to encode
    void EncodeElem(uint8_t* source, char_type* destination)
    {
        auto dst = (uint8_t*)destination;
        if (System::BitConverter::_IsLittleEndian())
        {
            std::copy(source, source + m_elem_size, dst);
        }
        else
        {
            std::reverse_copy(source, source + m_elem_size, dst);
        }
    }

    /// Reference to the stream.
    std::basic_ios<char_type, traits_type>& m_stream;
    /// Wrapping mode.
    const STDIOStreamWrappingMode m_wrapping_mode;
    /// CanRead flag.
    const bool m_can_read;
    /// CanWrite flag.
    const bool m_can_write;
    /// CanSeek flag.
    const bool m_can_seek;
    /// char_type size = sizeof(char_type).
    static constexpr uint8_t m_elem_size = sizeof(char_type);
    /// Last read position.
    int64_t m_last_elem_gpos;
    /// Last write position.
    int64_t m_last_elem_ppos;
    /// Read/write position.
    int64_t m_elem_pos;
    /// Read/write position in bytes.
    int64_t m_byte_pos;
    /// Stream's length.
    int64_t m_length;

    /// The last decoded element storage.
    ArrayPtr<uint8_t> m_decoded_elem;
};

/// Represents a System.IO.Stream-like wrapper for std::basic_istream and its derived objects.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or
/// assertion faults. Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions
/// as argument.
template <typename T, typename = std::enable_if_t<IsTemplateBaseOf<std::basic_istream, T>::value>>
class BasicSTDIStreamWrapper : public virtual STDIOStreamWrapperBase<T>
{
public:
    using ThisType = BasicSTDIStreamWrapper<T>;
    using BaseType = STDIOStreamWrapperBase<T>;
    using ThisTypeBaseTypesInfo = BaseTypesInfo<BaseType>;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    using char_type = typename BaseType::char_type;
    using traits_type = typename BaseType::traits_type;

    /// Constructs a new instance of the BasicSTDIStreamWrapper.
    /// @param str The reference to the stream
    /// @param mode Wrapping mode
    BasicSTDIStreamWrapper(std::basic_istream<char_type, traits_type>& str,
                           STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary)
        : BaseType(str, mode, true, false, (std::ios_base*)&str != &std::cin && (std::ios_base*)&str != &std::wcin)
    {}

    /// Copy constructor. Deleted.
    BasicSTDIStreamWrapper(const BasicSTDIStreamWrapper&) = delete;

    /// Copy assignment operator. Deleted.
    BasicSTDIStreamWrapper& operator=(const BasicSTDIStreamWrapper&) = delete;

    /// If wrapping mode is binary, reads a single byte from the last decoded character storage, otherwise read a single
    /// character from the stream and convert it to uint8_t type.
    /// @returns A 32-bit integer value equivalent to the result of reading
    virtual int ReadByte() override
    {
        Check();

        if (!get_CanRead())
            throw NotSupportedException(u"Can't read from stream.");

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            auto meta = m_stream.rdbuf()->sbumpc();
            if (traits_type::eq_int_type(meta, traits_type::eof()))
            {
                return -1;
            }
            else
            {
                Sync();
                return uint8_t(meta);
            }
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            if (m_decoded_elem == nullptr)
            {
                auto meta = m_stream.rdbuf()->sgetc();
                if (traits_type::eq_int_type(meta, traits_type::eof()))
                {
                    return -1;
                }
                else
                {
                    DecodeElem(meta);
                }
            }

            int64_t byte_pos_shift = m_byte_pos % m_elem_size;
            auto result = int(m_decoded_elem[byte_pos_shift]);

            ++m_byte_pos;
            ++byte_pos_shift %= m_elem_size;
            if (byte_pos_shift == 0)
            { // Decode element at new byte position.
                DecodeElem(m_stream.rdbuf()->snextc());
            }

            Sync();
            return result;
        }
    }

    /// If wrapping mode is binary, writes to the stream the specified unsigned 8-bit integer value, otherwise convert
    /// it to char_type type and then write the result to the stream. Not supported!
    /// @param value The value to write
    virtual void WriteByte(uint8_t value) override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// If wrapping mode is binary, reads the specified number of bytes from the stream, otherwise read the specified
    /// number of characters and converts them to uint8_t type. Writes result of the reading to the specified byte
    /// array.
    /// @param buffer The byte array to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns Number of bytes or characters read
    virtual int32_t Read(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        return Read(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, count);
    }

    /// If wrapping mode is binary, writes to the stream the specified subrange of bytes from the specified byte array,
    /// otherwise convert the specified subrange of bytes from the specified byte array to char_type type ant then
    /// writes result to the stream. Not supported!
    /// @param buffer The array containing the bytes to write.
    /// @param offset A 0-based index of the elemnet in @p buffer at which the subrange to write begins.
    /// @param count The number of elements in the subrange to write.
    virtual void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        Write(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, count);
    }

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array view to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns The number of bytes read
    virtual int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        Check();

        if (!get_CanRead())
            throw NotSupportedException(u"Can't read from stream.");
        if (buffer == nullptr)
            throw ArgumentNullException(u"buffer");
        if (offset < 0)
            throw ArgumentOutOfRangeException(u"offset", u"Value is less than zero");
        if (count < 0)
            throw ArgumentOutOfRangeException(u"count", u"Value is less than zero");
        if (buffer.get_Length() - offset < count)
            throw ArgumentException(u"Invalid buffer length");

        if (count == 0)
            return 0;

        if (m_elem_size == 1)
        {
            int readed_count = int(m_stream.rdbuf()->sgetn((char_type*)&buffer[offset], count));
            if (m_wrapping_mode == STDIOStreamWrappingMode::Binary)
            {
                m_byte_pos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
            }

            Sync();
            return readed_count;
        }

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            std::vector<char_type> tempbuff(count, 0);
            int readed_count = int(m_stream.rdbuf()->sgetn(tempbuff.data(), count));
            auto dst = &buffer[offset];
            std::for_each(tempbuff.begin(), tempbuff.end(),
                [&dst, this](char_type& elem) { *(dst++) = uint8_t(elem); });

            Sync();
            return readed_count;
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            uint8_t byte_pos_shift = m_byte_pos % m_elem_size;
            int new_byte_count = byte_pos_shift + count;
            bool has_new_byte_pos_shift = new_byte_count % m_elem_size != 0;
            int elem_count = new_byte_count / m_elem_size + int(has_new_byte_pos_shift);

            std::vector<char_type> tempbuff(elem_count, 0);
            int readed_elem_count = int(m_stream.rdbuf()->sgetn(tempbuff.data(), elem_count));
            int readed_byte_count;
            if (readed_elem_count != elem_count)
            {
                readed_byte_count = readed_elem_count * m_elem_size - byte_pos_shift;
            }
            else
            {
                readed_byte_count = count;
                if (has_new_byte_pos_shift)
                {
                    m_stream.rdbuf()->pubseekoff(-1, std::ios_base::cur, std::ios_base::in);
                }
            }

            m_byte_pos += readed_byte_count;

            const char_type* source = &tempbuff[byte_pos_shift];
            uint8_t* destination = &buffer[offset];
            for (int i = 0; i < readed_byte_count; i += m_elem_size, ++source, destination += m_elem_size)
            {
                DecodeElem(traits_type::to_int_type(*source));
                std::strncpy((char*)destination, (const char*)m_decoded_elem->data_ptr(), m_elem_size);
            }

            Sync();
            return readed_byte_count;
        }
    }

    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array view containing the bytes to write
    /// @param offset A 0-based index of the element in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    virtual void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// Sets the length of the stream represented by the current object. Not supported!
    /// @param value The length in bytes to set
    virtual void SetLength(int64_t value) override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// Clears this stream's buffers and writes all buffered data to the underlying storage. Not supported!
    virtual void Flush() override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

protected:
    /// Seeks positions of read or write or both on @p value.
    /// @param value Seeked position
    /// @returns A new position if the seek is successful, otherwise -1
    virtual int64_t Pubseekpos(int64_t value) override
    {
        return m_stream.rdbuf()->pubseekpos(value, std::ios_base::in);
    }

    /// Check if the stream has been modified outside the wrapper.
    virtual void Check() const override
    {
        BaseType::Check();
        auto elem_gpos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
        if (m_stream.fail() || m_last_elem_gpos != elem_gpos)
        {
            if (!m_stream.fail())
            {
                m_stream.setstate(std::ios_base::failbit);
            }

            throw IOException(u"The stream has been modified outside the wrapper.");
        }
    }

    /// Syncronize read position.
    virtual void Sync() override
    {
        auto elem_gpos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
        if (m_last_elem_gpos != elem_gpos)
        {
            m_last_elem_gpos = elem_gpos;
            m_elem_pos = elem_gpos;
        }
    }

    using BaseType::DecodeElem;
    using BaseType::get_CanRead;

    using BaseType::m_byte_pos;
    using BaseType::m_decoded_elem;
    using BaseType::m_elem_pos;
    using BaseType::m_elem_size;
    using BaseType::m_last_elem_gpos;
    using BaseType::m_stream;
    using BaseType::m_wrapping_mode;
};

/// Represents a System.IO.Stream-like wrapper for std::basic_ostream and its derived objects.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or
/// assertion faults. Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions
/// as argument.
template <typename T, typename = std::enable_if_t<IsTemplateBaseOf<std::basic_ostream, T>::value>>
class BasicSTDOStreamWrapper : public virtual STDIOStreamWrapperBase<T>
{
public:
    using ThisType = BasicSTDOStreamWrapper<T>;
    using BaseType = STDIOStreamWrapperBase<T>;
    using ThisTypeBaseTypesInfo = BaseTypesInfo<BaseType>;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    using char_type = typename BaseType::char_type;
    using traits_type = typename BaseType::traits_type;

    /// Constructs a new instance of the BasicSTDOStreamWrapper.
    /// @param str The reference to the stream
    /// @param mode Wrapping mode
    BasicSTDOStreamWrapper(std::basic_ostream<char_type, traits_type>& str,
                           STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary)
        : BaseType(str, mode, false, true, (std::ios_base*)&str != &std::cout && (std::ios_base*)&str != &std::wcout)
    {}

    /// Copy constructor. Deleted.
    BasicSTDOStreamWrapper(const BasicSTDOStreamWrapper&) = delete;

    /// Copy assignment operator. Deleted.
    BasicSTDOStreamWrapper& operator=(const BasicSTDOStreamWrapper&) = delete;

    /// If wrapping mode is binary, reads a single byte from the last decoded character storage, otherwise read a single
    /// character from the stream and convert it to uint8_t type. Not supported!
    /// @returns A 32-bit integer value equivalent to the result of reading
    virtual int ReadByte() override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// If wrapping mode is binary, writes to the stream the specified unsigned 8-bit integer value, otherwise convert
    /// it to char_type type and then write the result to the stream.
    /// @param value The value to write
    virtual void WriteByte(uint8_t value) override
    {
        Check();

        if (!get_CanWrite())
            throw NotSupportedException(u"Can't write to stream.");

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            m_stream.rdbuf()->sputc(char_type(value));
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            if (m_decoded_elem == nullptr)
            {
                m_decoded_elem = MakeArray<uint8_t>(m_elem_size, 0);
            }

            int64_t byte_pos_shift = m_byte_pos % m_elem_size;
            m_decoded_elem[byte_pos_shift] = value;
            ++m_byte_pos;
            ++byte_pos_shift %= m_elem_size;

            m_stream.rdbuf()->sputc(EncodeElem());
            if (byte_pos_shift != 0)
            { // New byte position is previous element position.
                m_stream.rdbuf()->pubseekoff(-1, std::ios_base::cur, std::ios_base::in);
            }
            else
            { // Decode element at new byte position.
                DecodeElem(m_stream.rdbuf()->sgetc());
            }
        }

        Sync();
    }

    /// If wrapping mode is binary, reads the specified number of bytes from the stream, otherwise read the specified
    /// number of characters and converts them to uint8_t type. Writes result of the reading to the specified byte
    /// array. Not supported!
    /// @param buffer The byte array to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns Number of bytes or characters read
    virtual int32_t Read(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        return Read(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, count);
    }

    /// If wrapping mode is binary, writes to the stream the specified subrange of bytes from the specified byte array,
    /// otherwise convert the specified subrange of bytes from the specified byte array to char_type type ant then
    /// writes result to the stream.
    /// @param buffer The array containing the bytes to write
    /// @param offset A 0-based index of the elemnet in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    virtual void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        Write(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, count);
    }

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array view to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns The number of bytes read
    virtual int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array view containing the bytes to write
    /// @param offset A 0-based index of the element in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    virtual void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        Check();

        if (!get_CanWrite())
            throw NotSupportedException(u"Can't write to stream.");
        if (buffer == nullptr)
            throw ArgumentNullException(u"buffer");
        if (offset < 0)
            throw ArgumentOutOfRangeException(u"offset", u"Value is less than zero");
        if (count < 0)
            throw ArgumentOutOfRangeException(u"count", u"Value is less than zero");
        if (buffer.get_Length() - offset < count)
            throw ArgumentException(u"Invalid buffer length");

        if (count == 0)
            return;

        if (sizeof(char_type) == 1)
        {
            m_stream.rdbuf()->sputn((const char_type*)&buffer[offset], count);
            if (m_wrapping_mode == STDIOStreamWrappingMode::Binary)
            {
                m_byte_pos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
            }

            Sync();
            return;
        }

        if (m_wrapping_mode == STDIOStreamWrappingMode::Conversion)
        {
            std::vector<char_type> tempbuff(count, 0);
            auto dst = tempbuff.data();
            std::for_each(buffer.begin() + offset, buffer.begin() + offset + count,
                [&dst, this](uint8_t& byte) { *(dst++) = char_type(byte); });
            m_stream.rdbuf()->sputn(tempbuff.data(), count);

            Sync();
        }
        else
        { // m_wrapping_mode == STDIOStreamWrappingMode::Binary
            if (m_decoded_elem == nullptr)
            {
                m_decoded_elem = MakeArray<uint8_t>(m_elem_size, 0);
            }

            uint8_t* source = &buffer[offset];
            uint8_t byte_pos_shift = m_byte_pos % m_elem_size;
            m_byte_pos += count;

            if (byte_pos_shift != 0)
            {
                for (; count > 0 && byte_pos_shift != 0; ++source, --count, ++byte_pos_shift %= m_elem_size)
                { // Append to the remaining memory cells of the decoded_elem.
                    m_decoded_elem[byte_pos_shift] = *source;
                }

                m_stream.rdbuf()->sputc(EncodeElem());

                if (byte_pos_shift != 0)
                { // New byte position is previous element position.
                    m_stream.rdbuf()->pubseekoff(-1, std::ios_base::cur, std::ios_base::out);

                    Sync();
                    return;
                }
            }

            int elem_count = count / m_elem_size;
            if (elem_count != 0)
            { // Encode and put elem_count elements into stream.
                std::vector<char_type> tempbuff(elem_count, 0);
                char_type* destination = tempbuff.data();
                for (; count >= m_elem_size; source += m_elem_size, ++destination, count -= m_elem_size)
                {
                    EncodeElem(source, destination);
                }

                m_stream.rdbuf()->sputn(tempbuff.data(), elem_count);
            }

            DecodeElem(m_stream.rdbuf()->sgetc());

            if (count != 0)
            { // There are unwritten bytes. Write bytes in decoded_elem, encode it and put result in the stream.
                if (m_decoded_elem == nullptr)
                {
                    m_decoded_elem = MakeArray<uint8_t>(m_elem_size, 0);
                }

                for (; count > 0; ++source, --count, ++byte_pos_shift %= m_elem_size)
                {
                    m_decoded_elem[byte_pos_shift] = *source;
                }

                m_stream.rdbuf()->sputc(EncodeElem());
                m_stream.rdbuf()->pubseekoff(-1, std::ios_base::cur, std::ios_base::out);
            }

            Sync();
        }
    }

    /// Sets the length of the stream represented by the current object.
    /// @param value The length in bytes to set
    virtual void SetLength(int64_t value) override
    {
        throw NotSupportedException(ASPOSE_CURRENT_FUNCTION);
    }

    /// Clears this stream's buffers and writes all buffered data to the underlying storage.
    virtual void Flush() override
    {
        Check();

        if (!get_CanWrite())
            throw NotSupportedException(u"Can't write to stream.");

        m_stream.rdbuf()->pubsync();
    }

protected:
    /// Seeks positions of read or write or both on @p value.
    /// @param value Seeked position
    /// @returns A new position if the seek is successful, otherwise -1
    virtual int64_t Pubseekpos(int64_t value) override
    {
        return m_stream.rdbuf()->pubseekpos(value, std::ios_base::out);
    }

    /// Check if the stream has been modified outside the wrapper.
    virtual void Check() const override
    {
        BaseType::Check();
        auto elem_ppos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
        if (m_stream.fail() || m_last_elem_ppos != elem_ppos)
        {
            if (!m_stream.fail())
            {
                m_stream.setstate(std::ios_base::failbit);
            }

            throw IOException(u"The stream has been modified outside the wrapper.");
        }
    }

    /// Syncronize write position.
    virtual void Sync() override
    {
        auto elem_ppos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
        if (m_last_elem_ppos != elem_ppos)
        {
            m_elem_pos = elem_ppos;
            m_last_elem_ppos = m_elem_pos;
            if (m_elem_pos > m_length)
            {
                m_length = m_elem_pos;
            }
        }
    }

    using BaseType::DecodeElem;
    using BaseType::EncodeElem;
    using BaseType::get_CanWrite;

    using BaseType::m_byte_pos;
    using BaseType::m_decoded_elem;
    using BaseType::m_elem_pos;
    using BaseType::m_elem_size;
    using BaseType::m_last_elem_ppos;
    using BaseType::m_length;
    using BaseType::m_stream;
    using BaseType::m_wrapping_mode;
};

/// Represents a System.IO.Stream-like wrapper for std::basic_iostream and its derived objects.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or
/// assertion faults. Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions
/// as argument.
template <typename T, typename = std::enable_if_t<IsTemplateBaseOf<std::basic_iostream, T>::value>>
class BasicSTDIOStreamWrapper : public BasicSTDIStreamWrapper<T>, public BasicSTDOStreamWrapper<T>
{
public:
    using ThisType = BasicSTDIOStreamWrapper<T>;
    using BaseType = STDIOStreamWrapperBase<T>;
    using BaseIType = BasicSTDIStreamWrapper<T>;
    using BaseOType = BasicSTDOStreamWrapper<T>;
    using ThisTypeBaseTypesInfo = BaseTypesInfo<BaseIType, BaseOType>;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:
    using char_type = typename BaseType::char_type;
    using traits_type = typename BaseType::traits_type;

    /// Constructs a new instance of the BasicSTDIOStreamWrapper.
    /// @param str The reference to the stream
    /// @param mode Wrapping mode
    /// @param pref_pos Position that will prefer as read and write position, if they are different
    BasicSTDIOStreamWrapper(std::basic_iostream<char_type, traits_type>& str,
                            STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary,
                            STDIOStreamPositionPreference pref_pos = STDIOStreamPositionPreference::Zero)
        : BaseType(str, mode, true, true, true, pref_pos), BaseIType(str, mode), BaseOType(str, mode)
    {}

    /// Copy constructor. Deleted.
    BasicSTDIOStreamWrapper(const BasicSTDIOStreamWrapper&) = delete;

    /// Copy assignment operator. Deleted.
    BasicSTDIOStreamWrapper& operator=(const BasicSTDIOStreamWrapper&) = delete;

    /// If wrapping mode is binary, reads a single byte from the last decoded character storage, otherwise read a single
    /// character from the stream and convert it to uint8_t type.
    /// @returns A 32-bit integer value equivalent to the result of reading
    virtual int ReadByte() override
    {
        return BaseIType::ReadByte();
    }

    /// If wrapping mode is binary, writes to the stream the specified unsigned 8-bit integer value, otherwise convert
    /// it to char_type type and then write the result to the stream.
    /// @param value The value to write
    virtual void WriteByte(uint8_t value) override
    {
        BaseOType::WriteByte(value);
    }

    /// If wrapping mode is binary, reads the specified number of bytes from the stream, otherwise read the specified
    /// number of characters and converts them to uint8_t type. Writes result of the reading to the specified byte
    /// array.
    /// @param buffer The byte array to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns Number of bytes or characters read
    virtual int32_t Read(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        return Read(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, count);
    }

    /// If wrapping mode is binary, writes to the stream the specified subrange of bytes from the specified byte array,
    /// otherwise convert the specified subrange of bytes from the specified byte array to char_type type ant then
    /// writes result to the stream.
    /// @param buffer The array containing the bytes to write
    /// @param offset A 0-based index of the elemnet in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    virtual void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        Write(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, count);
    }

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array view to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns The number of bytes read
    virtual int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        return BaseIType::Read(buffer, offset, count);
    }

    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array view containing the bytes to write
    /// @param offset A 0-based index of the element in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    virtual void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override
    {
        BaseOType::Write(buffer, offset, count);
    }

    /// Sets the length of the stream represented by the current object.
    /// @param value The length in bytes to set
    virtual void SetLength(int64_t value) override
    {
        BaseOType::SetLength(value);
    }

    /// Clears this stream's buffers and writes all buffered data to the underlying storage.
    virtual void Flush() override
    {
        BaseOType::Flush();
    }

protected:
    /// Seeks positions of read or write or both on @p value.
    /// @param value Seeked position
    /// @returns A new position if the seek is successful, otherwise -1
    virtual int64_t Pubseekpos(int64_t value)
    {
        m_stream.rdbuf()->pubseekpos(value, std::ios_base::in);
        return m_stream.rdbuf()->pubseekpos(value, std::ios_base::out);
    }

    /// Check if the stream has been modified outside the wrapper.
    virtual void Check() const
    {
        BaseType::Check();
        auto elem_gpos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
        auto elem_ppos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
        if (m_stream.fail() || m_last_elem_gpos != elem_gpos || m_last_elem_ppos != elem_ppos || elem_gpos != elem_ppos)
        {
            if (!m_stream.fail())
            {
                m_stream.setstate(std::ios_base::failbit);
            }

            throw IOException(u"The stream has been modified outside the wrapper.");
        }
    }

    /// Syncronize read and write positions.
    virtual void Sync()
    {
        auto elem_gpos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in);
        auto elem_ppos = m_stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
        if (m_last_elem_gpos != elem_gpos || m_last_elem_ppos != elem_ppos)
        {
            if (m_last_elem_gpos != elem_gpos)
            {
                m_last_elem_gpos = elem_gpos;
                if (elem_ppos != elem_gpos)
                {
                    m_last_elem_ppos = m_stream.rdbuf()->pubseekpos(elem_gpos, std::ios_base::out);
                }
                else
                {
                    m_last_elem_ppos = elem_gpos;
                }

                m_elem_pos = elem_gpos;
            }
            else
            {
                m_last_elem_ppos = elem_ppos;
                if (elem_gpos != elem_ppos)
                {
                    m_last_elem_gpos = m_stream.rdbuf()->pubseekpos(elem_ppos, std::ios_base::in);
                }
                else
                {
                    m_last_elem_gpos = elem_ppos;
                }

                m_elem_pos = elem_ppos;
            }

            if (m_elem_pos > m_length)
            {
                m_length = m_elem_pos;
            }
        }
    }

    using BaseType::m_elem_pos;
    using BaseType::m_last_elem_gpos;
    using BaseType::m_last_elem_ppos;
    using BaseType::m_length;
    using BaseType::m_stream;
};

/// Wrapper function for std::basic_istream-like streams.
/// @param stream std::basic_istream-like stream
/// @param mode Wrapping mode
/// @returns BasicSTDIStreamWrapper wrapper
template <typename char_type, typename traits_type>
SharedPtr<Stream> WrapSTDIOStream(std::basic_istream<char_type, traits_type>& stream,
                                  STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary)
{
    return MakeObject<BasicSTDIStreamWrapper<std::basic_istream<char_type, traits_type>>>(stream, mode);
}

/// Wrapper function for std::basic_ostream-like streams.
/// @param stream std::basic_ostream-like stream
/// @param mode Wrapping mode
/// @returns BasicSTDOStreamWrapper wrapper
template <typename char_type, typename traits_type>
SharedPtr<Stream> WrapSTDIOStream(std::basic_ostream<char_type, traits_type>& stream,
                                  STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary)
{
    return MakeObject<BasicSTDOStreamWrapper<std::basic_ostream<char_type, traits_type>>>(stream, mode);
}

/// Wrapper function for std::basic_iostream-like streams.
/// @param stream std::basic_iostream-like stream
/// @param mode Wrapping mode
/// @param pref_pos Position that will prefer as read and write position, if they are different
/// @returns BasicSTDIOStreamWrapper wrapper
template <typename char_type, typename traits_type>
SharedPtr<Stream> WrapSTDIOStream(std::basic_iostream<char_type, traits_type>& stream,
                                  STDIOStreamWrappingMode mode = STDIOStreamWrappingMode::Binary,
                                  STDIOStreamPositionPreference pref_pos = STDIOStreamPositionPreference::Zero)
{
    return MakeObject<BasicSTDIOStreamWrapper<std::basic_iostream<char_type, traits_type>>>(stream, mode);
}

/// Specializations of BasicSTDIStreamWrapper for char character types.
using STDIStreamWrapper = BasicSTDIStreamWrapper<std::istream>;
/// Specializations of BasicSTDIStreamWrapper for wchar_t character types.
using STDWIStreamWrapper = BasicSTDIStreamWrapper<std::wistream>;
/// Specializations of BasicSTDOStreamWrapper for char character types.
using STDOStreamWrapper = BasicSTDOStreamWrapper<std::ostream>;
/// Specializations of BasicSTDOStreamWrapper for wchar_t character types.
using STDWOStreamWrapper = BasicSTDOStreamWrapper<std::wostream>;
/// Specializations of BasicSTDIOStreamWrapper for char character types.
using STDIOStreamWrapper = BasicSTDIOStreamWrapper<std::iostream>;
/// Specializations of BasicSTDIOStreamWrapper for wchar_t character types.
using STDWIOStreamWrapper = BasicSTDIOStreamWrapper<std::wiostream>;

}} // namespace System::IO
