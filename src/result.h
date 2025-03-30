/**
 * \file
 * \brief Convenient macros.
 */

#pragma once

/* internal */
#include "generated/enums/Result.h"

/* toolchain */
#include <utility>

/* Simple fence re-allowing implicit boolean conversion (as non enum classes
 * behave). */
#ifndef ToBool
#define ToBool(x) std::to_underlying(x)
#endif

inline bool operator!(::Coral::Result res)
{
    return not ToBool(res);
}

#ifndef FAIL
#define FAIL (::Coral::Result::Fail)
#endif

#ifndef SUCCESS
#define SUCCESS (::Coral::Result::Success)
#endif

#ifndef ToResult
#define ToResult(x) ((x) ? SUCCESS : FAIL)
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
