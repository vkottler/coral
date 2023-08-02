/**
 * \file PcBufferReader.h
 *
 * \brief An interface definition for the reading-end of a producer-consumer
 *        buffer.
 */
#pragma once

/* toolchain */
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
     * TODO.
     *
     * \param[out] elem TODO.
     * \return          TODO.
     */
    bool pop(element_t &elem)
    {
        static_cast<T *>(this)->pop_impl(elem);
    }

    /**
     * TODO.
     *
     * \param[out] elem_array TODO.
     * \param[in]  count      TODO.
     * \return                TODO.
     */
    bool pop_n(element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->pop_n_impl(elem_array, count);
    }

    /**
     * TODO.
     *
     * \param[out] elem_array Same as \ref pop_n.
     * \param[in]  count      Same as \ref pop_n.
     * \return                TODO.
     */
    std::size_t try_pop_n(element_t *elem_array, std::size_t count)
    {
        static_cast<T *>(this)->try_pop_n_impl(elem_array, count);
    }

    /**
     * TODO.
     *
     * \param[out] elem_array Same as \ref pop_n.
     * \return                TODO.
     */
    std::size_t pop_all(element_t *elem_array = nullptr)
    {
        static_cast<T *>(this)->pop_all_impl(elem_array);
    }
};

}; // namespace Coral
