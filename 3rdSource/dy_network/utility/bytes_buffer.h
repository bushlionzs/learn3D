#ifndef _BYTES_BUFFER_H_INCLUDED
#define _BYTES_BUFFER_H_INCLUDED

#include <stdint.h>
#include <string.h>
#include <string>

class IWriter
{
public:
    virtual ~IWriter() = default;
    virtual int write(const void *data, size_t len) = 0;
    virtual bool require(size_t required_size) const { return true; }
    virtual void *current_data() { return nullptr; }
};

class IReader
{
public:
    virtual ~IReader() = default;
    virtual int read(void *data, size_t len) = 0;
    virtual size_t length() const = 0;
    virtual bool consume(size_t size) = 0;

    bool read_all(void *data, size_t len)
    {
        if (0 == len)
        {
            return true;
        }

        int n = read(data, len);
        return n > 0 && static_cast<size_t>(n) == len;
    }
};

class IBytesWriter : public IWriter
{
public:
    virtual ~IBytesWriter() = default;

    virtual bool write_string(const std::string& str) = 0;
    virtual bool write_bool(bool value) = 0;
    virtual bool write_i8(int8_t value) = 0;
    virtual bool write_u8(uint8_t value) = 0;
    virtual bool write_i16(int16_t value) = 0;
    virtual bool write_u16(uint16_t value) = 0;
    virtual bool write_i24(int32_t value) = 0;
    virtual bool write_u24(uint32_t value) = 0;
    virtual bool write_i32(int32_t value) = 0;
    virtual bool write_u32(uint32_t value) = 0;
    virtual bool write_i64(int64_t value) = 0;
    virtual bool write_u64(uint64_t value) = 0;
};

class IBytesReader : public IReader
{
public:
    virtual ~IBytesReader() = default;

    virtual bool read_string(std::string& str, size_t len) = 0;
    virtual bool read_bool(bool& value) = 0;
    virtual bool read_i8(int8_t& value) = 0;
    virtual bool read_u8(uint8_t& value) = 0;
    virtual bool read_i16(int16_t& value) = 0;
    virtual bool read_u16(uint16_t& value) = 0;
    virtual bool read_i24(int32_t& value) = 0;
    virtual bool read_u24(uint32_t& value) = 0;
    virtual bool read_i32(int32_t& value) = 0;
    virtual bool read_u32(uint32_t& value) = 0;
    virtual bool read_i64(int64_t& value) = 0;
    virtual bool read_u64(uint64_t& value) = 0;
};

class BytesBuffer : public IWriter, public IReader
{
public:
    BytesBuffer(char *bytes, size_t cap)
        : _bytes(bytes)
        , _cap(cap)
        , _pos(0) {}

    bool require(size_t required_size) const override
    {
        return _pos + required_size <= _cap;
    }

    void *current_data() override { return _bytes + _pos; }

    int write(const void *data, size_t len) override
    {
        if (_pos + len > _cap)
        {
            return -1;
        }

        memcpy(_bytes + _pos, data, len);
        _pos += len;
        return (int)len;
    }

    int read(void *data, size_t len) override
    {
        if (_pos + len > _cap)
        {
            return (_pos == _cap) ? 0 : -1;
        }

        memcpy(data, _bytes + _pos, len);
        _pos += len;
        return (int)len;
    }

    size_t length() const override
    {
        return _cap - _pos;
    }

    bool consume(size_t size) override
    {
        if (size > length())
        {
            return false;
        }

        _pos += size;
        return true;
    }
private:
    char *_bytes = nullptr;
    size_t _cap = 0;
    size_t _pos = 0;
};

class BytesWriter final
{
public:
    explicit BytesWriter(IWriter *writer) : _writer(writer) {}

    int write_string(const std::string& str)
    {
        return _writer->write(str.data(), str.length());
    }

    int write_bool(bool value)
    {
        return write_i8(value ? 1 : 0);
    }

    int write_i8(int8_t value)
    {
        return _writer->write(&value, 1);
    }

    int write_u8(uint8_t value)
    {
        return _writer->write(&value, 1);
    }

    template<typename T, size_t N, void(*W)(void *, T)>
    int write(T value)
    {
        char buf[N];
        W(buf, value);
        return _writer->write(buf, N);
    }

    template<typename E>
    int write_i16(int16_t value)
    {
        return write<int16_t, 2, &E::write_i16>(value);
    }

    template<typename E>
    int write_u16(uint16_t value)
    {
        return write<uint16_t, 2, &E::write_u16>(value);
    }

    template<typename E>
    int write_i24(int32_t value)
    {
        return write<int32_t, 3, &E::write_i24>(value);
    }

    template<typename E>
    int write_u24(uint32_t value)
    {
        return write<uint32_t, 3, &E::write_u24>(value);
    }

    template<typename E>
    int write_i32(int32_t value)
    {
        return write<int32_t, 4, &E::write_i32>(value);
    }

    template<typename E>
    int write_u32(uint32_t value)
    {
        return write<uint32_t, 4, &E::write_u32>(value);
    }

    template<typename E>
    int write_i64(int64_t value)
    {
        return write<int64_t, 8, &E::write_i64>(value);
    }

    template<typename E>
    int write_u64(uint64_t value)
    {
        return write<uint64_t, 8, &E::write_u64>(value);
    }

    template<typename E>
    int write_f32(float value)
    {
        return write_u32<E>(*reinterpret_cast<uint32_t *>(&value));
    }

    template<typename E>
    int write_f64(double value)
    {
        return write_u64<E>(*reinterpret_cast<uint64_t *>(&value));
    }
private:
    IWriter *_writer = nullptr;
};

class BytesReader final
{
public:
    explicit BytesReader(IReader *reader) : _reader(reader) {}

    int read_string(std::string& str, size_t len)
    {
        str.resize(len);
        return _reader->read(&(str[0]), len);
    }

    int read_bool(bool& value)
    {
        int8_t x = 0;
        int n = read_i8(x);
        if (1 == n)
        {
            value = x;
        }

        return n;
    }

    int read_i8(int8_t& value)
    {
        return _reader->read(&value, 1);
    }

    int read_u8(uint8_t& value)
    {
        return _reader->read(&value, 1);
    }

    template<typename T, size_t N, T(*R)(const void *)>
    int read(T& value)
    {
        char buf[N];
        int n = _reader->read(buf, N);
        if (N == n)
        {
            value = R(buf);
        }

        return n;
    }

    template<typename E>
    int read_i16(int16_t& value)
    {
        return read<int16_t, 2, &E::read_i16>(value);
    }

    template<typename E>
    int read_u16(uint16_t& value)
    {
        return read<uint16_t, 2, &E::read_u16>(value);
    }

    template<typename E>
    int read_i24(int32_t& value)
    {
        return read<int32_t, 3, &E::read_i24>(value);
    }

    template<typename E>
    int read_u24(uint32_t& value)
    {
        return read<uint32_t, 3, &E::read_u24>(value);
    }

    template<typename E>
    int read_i32(int32_t& value)
    {
        return read<int32_t, 4, &E::read_i32>(value);
    }

    template<typename E>
    int read_u32(uint32_t& value)
    {
        return read<uint32_t, 4, &E::read_u32>(value);
    }

    template<typename E>
    int read_i64(int64_t& value)
    {
        return read<int64_t, 8, &E::read_i64>(value);
    }

    template<typename E>
    int read_u64(uint64_t& value)
    {
        return read<uint64_t, 8, &E::read_u64>(value);
    }

    template<typename E>
    int read_f32(float& value)
    {
        return read_u32<E>(reinterpret_cast<uint32_t &>(value));
    }

    template<typename E>
    int read_f64(double& value)
    {
        return read_u64<E>(reinterpret_cast<uint64_t &>(value));
    }
private:
    IReader *_reader = nullptr;
};

class BytesWriteBuffer : public IWriter
{
public:
    BytesWriteBuffer(uint8_t *bytes, size_t cap) : _bytes(bytes) , _cap(cap) {}

    bool require(size_t required_size) const override
    {
        return required_size <= left_length();
    }

    void *current_data() override { return _bytes + _pos; }

    int write(const void *data, size_t len) override
    {
        if (len > left_length())
        {
            return -1;
        }

        memcpy(_bytes + _pos, data, len);
        _pos += len;
        return (int)len;
    }

    const uint8_t *data() const
    {
        return _bytes;
    }

    size_t length() const
    {
        return _pos;
    }

    size_t capacity() const
    {
        return _cap;
    }

    size_t left_length() const
    {
        return _cap - _pos;
    }
protected:
    uint8_t *_bytes = nullptr;
    const size_t _cap = 0;
    size_t _pos = 0;
};

class BytesReadBuffer : public IReader
{
public:
    BytesReadBuffer(const uint8_t *bytes, size_t cap) : _bytes(bytes), _cap(cap) {}

    int read(void *data, size_t len) override
    {
        if (len > length())
        {
            return (_pos == _cap) ? 0 : -1;
        }

        memcpy(data, _bytes + _pos, len);
        _pos += len;
        return (int)len;
    }

    size_t length() const override
    {
        return _cap - _pos;
    }

    bool consume(size_t size) override
    {
        if (size > length())
        {
            return false;
        }

        _pos += size;
        return true;
    }

protected:
    const uint8_t *_bytes = nullptr;
    const size_t _cap = 0;
    size_t _pos = 0;
};

template<typename E>
class BytesWriterT : public IBytesWriter
{
public:
    explicit BytesWriterT(IWriter *writer) : _writer(writer) {}

    bool require(size_t required_size) const override
    {
        return _writer->require(required_size);
    }

    void *current_data() override { return _writer->current_data(); }

    int write(const void *data, size_t len) override
    {
        return _writer->write(data, len);
    }

    bool write_string(const std::string& str) override
    {
        return str.length() == _writer->write(str.data(), str.length());
    }

    bool write_bool(bool value) override
    {
        return 1 == write_i8(value ? 1 : 0);
    }

    bool write_i8(int8_t value) override
    {
        return 1 == _writer->write(&value, 1);
    }

    bool write_u8(uint8_t value) override
    {
        return 1 == _writer->write(&value, 1);
    }

    bool write_i16(int16_t value) override
    {
        return write<int16_t, 2, &E::write_i16>(value);
    }

    bool write_u16(uint16_t value) override
    {
        return write<uint16_t, 2, &E::write_u16>(value);
    }

    bool write_i24(int32_t value) override
    {
        return write<int32_t, 3, &E::write_i24>(value);
    }

    bool write_u24(uint32_t value) override
    {
        return write<uint32_t, 3, &E::write_u24>(value);
    }

    bool write_i32(int32_t value) override
    {
        return write<int32_t, 4, &E::write_i32>(value);
    }

    bool write_u32(uint32_t value) override
    {
        return write<uint32_t, 4, &E::write_u32>(value);
    }

    bool write_i64(int64_t value) override
    {
        return write<int64_t, 8, &E::write_i64>(value);
    }

    bool write_u64(uint64_t value) override
    {
        return write<uint64_t, 8, &E::write_u64>(value);
    }
private:
    template<typename T, size_t N, void(*W)(void *, T)>
    bool write(T value)
    {
        char buf[N];
        W(buf, value);
        return N == write(buf, N);
    }

    IWriter *_writer = nullptr;
};

template<typename E>
class BytesReaderT : public IBytesReader
{
public:
    explicit BytesReaderT(IReader *reader) : _reader(reader) {}

    int read(void *data, size_t len) override
    {
        return _reader->read(data, len);
    }

    size_t length() const override
    {
        return _reader->length();
    }

    bool consume(size_t size) override
    {
        return _reader->consume(size);
    }

    bool read_string(std::string& str, size_t len) override
    {
        str.resize(len);
        return len == _reader->read(&(str[0]), len);
    }

    bool read_bool(bool& value) override
    {
        int8_t x = 0;
        int n = read_i8(x);
        if (1 != n)
        {
            return false;
        }

        value = x;
        return true;
    }

    bool read_i8(int8_t& value) override
    {
        return 1 == _reader->read(&value, 1);
    }

    bool read_u8(uint8_t& value) override
    {
        return 1 == _reader->read(&value, 1);
    }

    bool read_i16(int16_t& value) override
    {
        return read<int16_t, 2, &E::read_i16>(value);
    }

    bool read_u16(uint16_t& value) override
    {
        return read<uint16_t, 2, &E::read_u16>(value);
    }

    bool read_i24(int32_t& value) override
    {
        return read<int32_t, 3, &E::read_i24>(value);
    }

    bool read_u24(uint32_t& value) override
    {
        return read<uint32_t, 3, &E::read_u24>(value);
    }

    bool read_i32(int32_t& value) override
    {
        return read<int32_t, 4, &E::read_i32>(value);
    }

    bool read_u32(uint32_t& value) override
    {
        return read<uint32_t, 4, &E::read_u32>(value);
    }

    bool read_i64(int64_t& value) override
    {
        return read<int64_t, 8, &E::read_i64>(value);
    }

    bool read_u64(uint64_t& value) override
    {
        return read<uint64_t, 8, &E::read_u64>(value);
    }
private:
    template<typename T, size_t N, T(*R)(const void *)>
    bool read(T& value)
    {
        char buf[N];
        int n = _reader->read(buf, N);
        if (N != n)
        {
            return false;
        }

        value = R(buf);
        return true;
    }

    IReader *_reader = nullptr;
};

#endif //_BYTES_BUFFER_H_INCLUDED
