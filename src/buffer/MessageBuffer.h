/**
 * \file
 * \brief A buffer implementation optimized for multi-element transactions.
 */
#pragma once

/* internal */
#include "../result.h"
#include "CircularBuffer.h"

namespace Coral
{

template <std::size_t depth, std::size_t max_messages,
          typename element_t = std::byte>
class MessageBuffer : protected CircularBuffer<depth, element_t>
{
  public:
    MessageBuffer()
        : CircularBuffer<depth, element_t>(), message_sizes(), num_messages(0),
          data_size(0)
    {
    }

    inline bool full(std::size_t check = 0)
    {
        return num_messages >= max_messages or (data_size + check > depth);
    }

    Result put_message(const element_t *data, std::size_t len)
    {
        /* Need room for message size element and space in data buffer. */
        auto result = len and not full(len);

        if (result)
        {
            message_sizes.write_single(len);
            this->write_n(data, len);

            num_messages++;
            data_size += len;
        }

        return ToResult(result);
    }

    Result get_message(element_t *data, std::size_t &len)
    {
        bool result = not empty();

        if (result)
        {
            message_sizes.read_single(len);
            this->read_n(data, len);

            num_messages--;
            data_size -= len;
        }

        return ToResult(result);
    }

    inline bool empty()
    {
        return num_messages == 0;
    }

  protected:
    CircularBuffer<max_messages, std::size_t> message_sizes;
    std::size_t num_messages;
    std::size_t data_size;
};

} // namespace Coral
