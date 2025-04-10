/**
 * \file
 * \brief Generated by ifgen (3.3.1).
 */

#pragma once

#include <cstdint>
#include <cstring>

namespace Coral
{

/**
 * Simple succeed/fail strict typing.
 */
enum class Result : uint8_t
{
    Fail,
    Success = 1
};
static_assert(sizeof(Result) == 1);

static constexpr uint16_t Result_id = 2;

/**
 * Converts Result to a C string.
 *
 * \param[in] instance Value to convert.
 * \return             A C string representation of the value.
 */
inline const char *to_string(Result instance)
{
    const char *result = "UNKNOWN Result";

    switch (instance)
    {
    case Result::Fail:
        result = "Fail";
        break;
    case Result::Success:
        result = "Success";
        break;
    }

    return result;
}

/**
 * Converts a C string to Result.
 *
 * \param[in]  data   A C string to convert.
 * \param[out] output The enumeration element to write.
 * \return            Whether or not the output was written.
 */
inline bool from_string(const char *data, Result &output)
{
    bool result = false;

    if ((result = !strncmp(data, "Fail", 4)))
    {
        output = Result::Fail;
    }
    else if ((result = !strncmp(data, "Success", 7)))
    {
        output = Result::Success;
    }

    return result;
}

}; // namespace Coral
