/**
 * \file CircularBuffer.h
 *
 * \brief A simple circular-buffer implementation.
 */
#pragma once

/* toolchain */
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>

namespace Coral
{

template <std::size_t depth, typename element_t = std::byte>
class CircularBuffer
{
    static_assert(depth > 0);

  public:
    using metrics_t = uint32_t;

    CircularBuffer()
        : buffer(), write_cursor(0), read_cursor(0), read_count(0),
          write_count(0)
    {
    }

    inline std::size_t write_index(void)
    {
        return write_cursor % depth;
    }

    inline void write_single(const element_t elem)
    {
        buffer[write_index()] = elem;
        write_cursor++;

        write_count++;
    }

    inline void write_n(const element_t *elem_array, std::size_t count)
    {
        std::size_t max_contiguous;
        std::size_t to_write;

        assert(count > 0);

        while (count)
        {
            /*
             * We can only write from the current index to the end of the
             * underlying, linear buffer.
             */
            max_contiguous = depth - write_index();
            to_write = std::min(max_contiguous, count);

            /* Copy the bytes (elements -> buffer). */
            std::memcpy(&(buffer.data()[write_index()]), elem_array,
                        to_write * sizeof(element_t));

            count -= to_write;
            write_cursor += to_write;
            elem_array += to_write;

            write_count += to_write;
        }
    }

    inline std::size_t read_index(void)
    {
        return read_cursor % depth;
    }

    inline void read_single(element_t &elem)
    {
        elem = buffer[read_index()];
        read_cursor++;

        read_count++;
    }

    inline void read_n(element_t *elem_array, std::size_t count)
    {
        std::size_t max_contiguous;
        std::size_t to_read;

        assert(count > 0);

        while (count)
        {
            /*
             * We can only read from the current index to the end of the
             * underlying, linear buffer.
             */
            max_contiguous = depth - read_index();
            to_read = std::min(max_contiguous, count);

            /* Copy the bytes (buffer -> elements). */
            if (elem_array)
            {
                std::memcpy(elem_array, &(buffer.data()[read_index()]),
                            to_read * sizeof(element_t));
                elem_array += to_read;
            }

            count -= to_read;
            read_cursor += to_read;

            read_count += to_read;
        }
    }

    void poll_metrics(metrics_t &_read_count, metrics_t &_write_count,
                      bool reset = true)
    {
        _read_count = read_count;
        _write_count = write_count;
        if (reset)
        {
            read_count = 0;
            write_count = 0;
        }
    }

  protected:
    std::array<element_t, depth> buffer;
    std::size_t write_cursor;
    std::size_t read_cursor;

    metrics_t read_count;
    metrics_t write_count;
};

}; // namespace Coral
