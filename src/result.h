/**
 * \file
 * \brief Convenient macros.
 */

#pragma once

/* internal */
#include "generated/enums/Result.h"

/* toolchain */
#include <utility>

inline bool operator!(::Coral::Result res)
{
    return not std::to_underlying(res);
}

#ifndef FAIL
#define FAIL ::Coral::Result::Fail
#endif

#ifndef SUCCESS
#define SUCCESS ::Coral::Result::Success
#endif

#ifndef FailIf
#define FailIf(x)                                                             \
    if (x)                                                                    \
    {                                                                         \
        return FAIL;                                                          \
    }
#endif

#ifndef FailIfNot
#define FailIfNot(x)                                                          \
    if (not(x))                                                               \
    {                                                                         \
        return FAIL;                                                          \
    }
#endif

#ifndef SuccessIf
#define SuccessIf(x)                                                          \
    if (x)                                                                    \
    {                                                                         \
        return SUCCESS;                                                       \
    }
#endif

#ifndef SuccessIfNot
#define SuccessIfNot(x)                                                       \
    if (not(x))                                                               \
    {                                                                         \
        return SUCCESS;                                                       \
    }
#endif
