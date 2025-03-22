/**
 * \file
 * \brief A simple circular-buffer implementation.
 */
#pragma once

/* toolchain */
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>

/* internal */
#include "../generated/structs/BufferState.h"

namespace Coral
{

template <std::size_t depth, typename element_t = std::byte>
class CircularBuffer
{
    static_assert(depth > 0);

  public:
    CircularBuffer() : buffer(), state()
    {
    }

    inline std::size_t write_index(void)
    {
        return state.write_cursor % depth;
    }

    inline void write_single(const element_t elem)
    {
        buffer[write_index()] = elem;
        state.write_cursor++;

        state.write_count++;
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
            state.write_cursor += to_write;
            elem_array += to_write;

            state.write_count += to_write;
        }
    }

    inline std::size_t read_index(void)
    {
        return state.read_cursor % depth;
    }

    inline element_t peek(void)
    {
        return buffer[read_index()];
    }

    inline void read_single(element_t &elem)
    {
        elem = peek();
        state.read_cursor++;

        state.read_count++;
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
            state.read_cursor += to_read;

            state.read_count += to_read;
        }
    }

    void poll_metrics(uint32_t &_read_count, uint32_t &_write_count,
                      bool reset = true)
    {
        _read_count = state.read_count;
        _write_count = state.write_count;
        if (reset)
        {
            state.read_count = 0;
            state.write_count = 0;
        }
    }

  protected:
    std::array<element_t, depth> buffer;

    BufferState state;
};

}; // namespace Coral
