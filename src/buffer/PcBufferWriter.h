/**
 * \file
 *
 * \brief An interface definition for the writing-end of a producer-consumer
 *        buffer.
 */
#pragma once

/* toolchain */
#include <array>
#include <cstdint>
#include <span>

namespace Coral
{

/**
 * A producer-consumer buffer-writer interface class.
 *
 * \tparam T         Implementing class (CRTP).
 * \tparam element_t The kind of element the buffer stores.
 */
template <class T, typename element_t = std::byte> class PcBufferWriter
{
  public:
    /**
     * Attempt to push a single element into the buffer.
     *
     * \param[in] elem The element to attempt adding.
     * \param[in] drop Whether or not to consider this element dropped if it
     *                 can't be added.
     * \return         Whether or not the element was added to the buffer.
     */
    inline bool push(const element_t &elem, bool drop = false)
    {
        return static_cast<T *>(this)->push_impl(elem, drop);
    }

    /**
     * Push a single element into the buffer and block until it's added.
     *
     * \param[in] elem The element to add.
     */
    inline void push_blocking(const element_t &elem)
    {
        static_cast<T *>(this)->push_blocking_impl(elem);
    }

    /**
     * Attempt to push an array into the buffer.
     *
     * \tparam    N          The size of \p elem_array.
     * \param[in] elem_array The array to push data from.
     * \param[in] drop       Whether or not to consider the array elements
     *                       dropped if they can't all be pushed.
     * \return               Whether or not the entire array was pushed. No
     *                       elements are pushed otherwise.
     */
    template <std::size_t N>
    inline bool push(const std::array<element_t, N> &elem_array,
                     bool drop = false)
    {
        return push_n(elem_array.data(), elem_array.size(), drop);
    }

    /**
     * Attempt to push a span into the buffer.
     *
     * \param[in] elem_span The span to push data from.
     * \param[in] drop      Whether or not to consider the span elements
     *                      dropped if they can't all be pushed.
     * \return              Whether or not the entire span was pushed. No
     *                      elements are pushed otherwise.
     */
    inline bool push(const std::span<element_t> &elem_span, bool drop = false)
    {
        return push_n(elem_span.data(), elem_span.size(), drop);
    }

    /**
     * Attempt to push an arbitrary number of elements into the buffer.
     *
     * \param[in] elem_array The array to source \p count elements from.
     * \param[in] count      The number of elements to attempt adding from
     *                       \p elem_array.
     * \param[in] drop       Whether or not to consider all \p count elements
     *                       dropped if they can't all be added.
     * \return               Whether or not all elements were added. This
     *                       method only adds either \p count elements or none
     *                       of them.
     */
    inline bool push_n(const element_t *elem_array, std::size_t count,
                       bool drop = false)
    {
        return static_cast<T *>(this)->push_n_impl(elem_array, count, drop);
    }

    /**
     * Attempt to push an array into the buffer. Allows making partial
     * progress.
     *
     * \tparam    N          The size of \p elem_array.
     * \param[in] elem_array The array to push data from.
     * \return               The number of elements pushed.
     */
    template <std::size_t N>
    inline std::size_t try_push_n(const std::array<element_t, N> &elem_array)
    {
        return try_push_n(elem_array.data(), elem_array.size());
    }

    /**
     * Attempt to push a span into the buffer. Allows making partial
     * progress.
     *
     * \param[in] elem_span The span to push data from.
     * \return              The number of elements pushed.
     */
    inline std::size_t try_push_n(const std::span<element_t> &elem_span)
    {
        return try_push_n(elem_span.data(), elem_span.size());
    }

    /**
     * Attempt to push an arbitrary number of elements into the buffer. Adds
     * as many elements as possible (without blocking).
     *
     * \param[in] elem_array Same as \ref push_n.
     * \param[in] count      Same as \ref push_n.
     * \return               The number of elements successfully added to the
     *                       buffer.
     */
    inline std::size_t try_push_n(const element_t *elem_array,
                                  std::size_t count)
    {
        return static_cast<T *>(this)->try_push_n_impl(elem_array, count);
    }

    /**
     * Push an array into the buffer and block until it's added.
     *
     * \tparam    N          The size of \p elem_array.
     * \param[in] elem_array The array to push.
     */
    template <std::size_t N>
    inline void push_n_blocking(const std::array<element_t, N> &elem_array)
    {
        push_n_blocking(elem_array.data(), elem_array.size());
    }

    /**
     * Push a span into the buffer and block until it's added.
     *
     * \param[in] elem_array The span to push.
     */
    inline void push_n_blocking(const std::span<element_t> &elem_span)
    {
        push_n_blocking(elem_span.data(), elem_span.size());
    }

    /**
     * Push elements into the buffer and block until they're added.
     *
     * \param[in] elem_array Same as \ref push_n.
     * \param[in] count      Same as \ref push_n.
     */
    inline void push_n_blocking(const element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->push_n_blocking_impl(elem_array, count);
    }
};

}; // namespace Coral
