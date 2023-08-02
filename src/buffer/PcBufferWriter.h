/**
 * \file PcBufferWriter.h
 *
 * \brief An interface definition for the writing-end of a producer-consumer
 *        buffer.
 */
#pragma once

/* toolchain */
#include <cstdint>

namespace Coral
{

/**
 * A producer-consumer buffer-writer interface class.
 *
 * \tparam T         Implementing class (CRTP).
 * \tparam element_t The kind of element the buffer stores.
 */
template <class T, typename element_t = uint8_t> class PcBufferWriter
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
    bool push(const element_t &&elem, bool drop = false)
    {
        static_cast<T *>(this)->push_impl(elem, drop);
    }

    /**
     * Push a single element into the buffer and block until it's added.
     *
     * \param[in] elem The element to add.
     */
    void push_blocking(const element_t &&elem)
    {
        static_cast<T *>(this)->push_blocking_impl(elem);
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
    bool push_n(const element_t *elem_array, std::size_t count,
                bool drop = false)
    {
        static_cast<T *>(this)->push_n_impl(elem_array, count, drop);
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
    std::size_t try_push_n(const element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->try_push_n_impl(elem_array, count);
    }

    /**
     * Push elements into the buffer and block until they're added.
     *
     * \param[in] elem_array Same as \ref push_n.
     * \param[in] count      Same as \ref push_n.
     */
    void push_n_blocking(const element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->push_n_blocking_impl(elem_array, count);
    }
};

}; // namespace Coral
