/**
 * \file PcBuffer.h
 *
 * \brief A producer-consumer buffer implementation.
 */
#pragma once

/* toolchain */
#include <functional>

/* internal */
#include "CircularBuffer.h"
#include "PcBufferReader.h"
#include "PcBufferState.h"
#include "PcBufferWriter.h"

namespace Coral
{

template <std::size_t depth, typename element_t = std::byte>
class PcBuffer : public PcBufferWriter<PcBuffer<depth, element_t>, element_t>,
                 public PcBufferReader<PcBuffer<depth, element_t>, element_t>
{
  public:
    using ServiceCallback = std::function<void(PcBuffer<depth, element_t> *)>;

    PcBuffer(bool _auto_service = true,
             ServiceCallback _space_available = nullptr,
             ServiceCallback _data_available = nullptr)
        : state(depth), buffer(), space_available(_space_available),
          data_available(_data_available), auto_service(_auto_service)
    {
    }

    void set_space_available(ServiceCallback _space_available)
    {
        /* Don't allow double assignment. */
        assert(_space_available and space_available == nullptr);
        space_available = _space_available;
    }

    void set_data_available(ServiceCallback _data_available)
    {
        /* Don't allow double assignment. */
        assert(_data_available and data_available == nullptr);
        data_available = _data_available;
    }

    inline bool empty(void)
    {
        return state.empty();
    }

    inline bool full(void)
    {
        return state.full();
    }

    inline void clear()
    {
        /* Reset state. */
        state.reset();

        uint32_t tmp;
        buffer.poll_metrics(tmp, tmp);
    }

    bool pop_impl(element_t &elem)
    {
        /* Allow a pop request to feed the buffer. */
        if (auto_service)
        {
            service_space();
        }

        bool result = state.decrement_data();

        if (result)
        {
            buffer.read_single(elem);
            service_space();
        }

        return result;
    }

    bool pop_n_impl(element_t *elem_array, std::size_t count)
    {
        /* Allow a pop request to feed the buffer. */
        if (auto_service)
        {
            service_space();
        }

        bool result = state.decrement_data(count);

        if (result)
        {
            buffer.read_n(elem_array, count);
            service_space();
        }

        return result;
    }

    std::size_t try_pop_n_impl(element_t *elem_array, std::size_t count)
    {
        count = std::min(count, state.data_available());

        if (count)
        {
            assert(pop_n_impl(elem_array, count));
        }

        return count;
    }

    std::size_t pop_all_impl(element_t *elem_array = nullptr)
    {
        std::size_t result = state.data_available();
        if (result)
        {
            assert(pop_n_impl(elem_array, result));
        }
        return result;
    }

    bool push_impl(const element_t elem, bool drop = false)
    {
        if (auto_service)
        {
            service_data();
        }

        bool result = state.increment_data(drop);

        if (result)
        {
            buffer.write_single(elem);
            service_data();
        }

        return result;
    }

    void push_blocking_impl(const element_t elem)
    {
        while (full())
        {
            service_data(true);
        }

        assert(push(elem));
    }

    void flush(void)
    {
        while (!empty())
        {
            service_data(true);
        }
    }

    bool push_n_impl(const element_t *elem_array, std::size_t count,
                     bool drop = false)
    {
        if (auto_service)
        {
            service_data();
        }

        bool result = state.increment_data(drop, count);

        if (result)
        {
            buffer.write_n(elem_array, count);
            service_data();
        }

        return result;
    }

    std::size_t try_push_n_impl(const element_t *elem_array, std::size_t count)
    {
        count = std::min(count, state.space_available());

        if (count)
        {
            assert(push_n(elem_array, count));
        }

        return count;
    }

    void push_n_blocking_impl(const element_t *elem_array, std::size_t count)
    {
        std::size_t chunk;
        while (count)
        {
            chunk = std::min(depth, count);

            while (!state.has_enough_space(chunk))
            {
                service_data(true);
            }

            assert(push_n(elem_array, chunk));
            elem_array += chunk;
            count -= chunk;
        }
    }

    PcBufferState state;

  protected:
    CircularBuffer<depth, element_t> buffer;

    ServiceCallback space_available;
    ServiceCallback data_available;

    bool auto_service;

    inline void service_data(bool required = false)
    {
        if (data_available)
        {
            data_available(this);
        }
        else
        {
            assert(not required);
        }
    }

    inline void service_space(bool required = false)
    {
        if (space_available)
        {
            space_available(this);
        }
        else
        {
            assert(not required);
        }
    }
};

}; // namespace Coral