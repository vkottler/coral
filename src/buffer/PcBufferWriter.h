#pragma once

/* toolchain */
#include <cstdint>

namespace Coral
{

template <class T, typename element_t = uint8_t> class PcBufferWriter
{
  public:
    bool push(const element_t &&elem, bool drop = false)
    {
        static_cast<T *>(this)->push_impl(elem, drop);
    }

    void push_blocking(const element_t &&elem)
    {
        static_cast<T *>(this)->push_blocking_impl(elem);
    }

    bool push_n(const element_t *elem_array, std::size_t count,
                bool drop = false)
    {
        static_cast<T *>(this)->push_n_impl(elem_array, count, drop);
    }

    std::size_t try_push_n(const element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->try_push_n_impl(elem_array, count);
    }

    void push_n_blocking(const element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->push_n_blocking_impl(elem_array, count);
    }
};

}; // namespace Coral
