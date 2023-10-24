/**
 * \file
 * \brief A simple logger implementation that uses printf.
 */
#pragma once

/* toolchain */
#include <cstdio>

/* internal */
#include "LogInterface.h"

namespace Coral
{

class PrintfLogger : public LogInterface<PrintfLogger>
{
  public:
    void vlog_impl(const char *fmt, va_list args)
    {
        vprintf(fmt, args);
    }
};

}; // namespace Coral
