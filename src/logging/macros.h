/**
 * \file
 * \brief Logging-related preprocessor macros.
 */
#pragma once

/* internal */
#include "PrintfLogger.h"

/* toolchain */
#include <cerrno>
#include <cstring>

#ifndef CORAL_LOGGER
#define CORAL_LOGGER Coral::stderr_logger()
#endif

#ifndef LogIf
#define LogIf(x)                                                              \
    if (x)                                                                    \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogIf(" #x ")\n", __FILE__, __LINE__);        \
    }
#endif

#ifndef LogErrnoIf
#define LogErrnoIf(x)                                                         \
    if (x)                                                                    \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogErrnoIf(" #x ") %s\n", __FILE__, __LINE__, \
                         strerror(errno));                                    \
    }
#endif

#ifndef LogReturnIf
#define LogReturnIf(x)                                                        \
    if (x)                                                                    \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogReturnIf(" #x ")\n", __FILE__, __LINE__);  \
        return;                                                               \
    }
#endif

#ifndef LogReturnValIf
#define LogReturnValIf(x, val)                                                \
    if (x)                                                                    \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogReturnValIf(" #x ", " #val ")\n",          \
                         __FILE__, __LINE__);                                 \
        return val;                                                           \
    }
#endif

#ifndef LogIfNot
#define LogIfNot(x)                                                           \
    if (not(x))                                                               \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogIfNot(" #x ")\n", __FILE__, __LINE__);     \
    }
#endif

#ifndef LogErrnoIfNot
#define LogErrnoIfNot(x)                                                      \
    if (not(x))                                                               \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogErrnoIfNot(" #x ") %s\n", __FILE__,        \
                         __LINE__, strerror(errno));                          \
    }
#endif

#ifndef LogReturnIfNot
#define LogReturnIfNot(x)                                                     \
    if (not(x))                                                               \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogReturnIfNot(" #x ")\n", __FILE__,          \
                         __LINE__);                                           \
        return;                                                               \
    }
#endif

#ifndef LogReturnValIfNot
#define LogReturnValIfNot(x, val)                                             \
    if (not(x))                                                               \
    {                                                                         \
        CORAL_LOGGER.log("%s:%d LogReturnValIfNot(" #x ", " #val ")\n",       \
                         __FILE__, __LINE__);                                 \
        return val;                                                           \
    }
#endif
