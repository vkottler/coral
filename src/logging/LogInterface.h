/**
 * \file
 * \brief A human-readable output-logging interface.
 */
#pragma once

/* toolchain */
#include <cstdarg>

namespace Coral
{

template <class T> class LogInterface
{
  public:
    void log(const char *fmt, ...) __attribute__((format(printf, 2, 3)))
    {
        va_list args;
        va_start(args, fmt);
        vlog(fmt, args);
        va_end(args);
    }

    void vlog(const char *fmt, va_list args)
    {
        static_cast<T *>(this)->vlog_impl(fmt, args);
    }
};

}; // namespace Coral
