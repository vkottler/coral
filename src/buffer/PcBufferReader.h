/**
 * \file PcBufferReader.h
 *
 * \brief An interface definition for the reading-end of a producer-consumer
 *        buffer.
 */
#pragma once

/* toolchain */
#include <array>
#include <cstdint>

namespace Coral
{

/**
 * A producer-consumer buffer-reader interface class.
 *
 * \tparam T         Same as \ref PcBufferWriter.
 * \tparam element_t Same as \ref PcBufferWriter.
 */
template <class T, typename element_t = uint8_t> class PcBufferReader
{
  public:
    /**
     * Attempt to read an element from the buffer.
     *
     * \param[out] elem The element to be written.
     * \return          Whether or not \p elem was written.
     */
    bool pop(element_t &elem)
    {
        return static_cast<T *>(this)->pop_impl(elem);
    }

    /**
     * Attempt to read buffer elements into an array.
     *
     * \tparam     N          The size of \p elem_array.
     * \param[out] elem_array The array to write elements to.
     * \return                Whether or not \p elem_array was written.
     *                        Otherwise no elements are read.
     */
    template <std::size_t N> bool pop(std::array<element_t, N> &elem_array)
    {
        return pop_n(elem_array.data(), elem_array.size());
    }

    /**
     * Attempt to read an array from the buffer.
     *
     * \param[out] elem_array The array to write data to.
     * \param[in]  count      The number of elements to read.
     * \return                Whether or not all \p count elements were read.
     *                        When false, no elements were read.
     */
    bool pop_n(element_t *elem_array, std::size_t count)
    {
        return static_cast<T *>(this)->pop_n_impl(elem_array, count);
    }

    /**
     * Attempt to read an array's worth of elements from the buffer. Partial
     * progress is made if possible.
     *
     * \tparam     N          The size of \p elem_array.
     * \param[out] elem_array The array to write elements to.
     * \return                The number of elements actually read. Always
     *                        between zero and the size of \p elem_array.
     */
    template <std::size_t N>
    std::size_t try_pop_n(std::array<element_t, N> &elem_array)
    {
        return try_pop_n(elem_array.data(), elem_array.size());
    }

    /**
     * Attempt to read a specific number of elements from the buffer. Partial
     * progress is made if possible.
     *
     * \param[out] elem_array Same as \ref pop_n.
     * \param[in]  count      Same as \ref pop_n.
     * \return                The number of elements actually read. Always
     *                        between zero and \p count.
     */
    std::size_t try_pop_n(element_t *elem_array, std::size_t count)
    {
        return static_cast<T *>(this)->try_pop_n_impl(elem_array, count);
    }

    /**
     * Read all available elements from the buffer.
     *
     * \param[out] elem_array Same as \ref pop_n. If not provided, elements are
     *                        read but data is discarded.
     * \return                The number of elements read.
     */
    std::size_t pop_all(element_t *elem_array = nullptr)
    {
        return static_cast<T *>(this)->pop_all_impl(elem_array);
    }
};

}; // namespace Coral
