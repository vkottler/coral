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

class FdPrintfLogger : public LogInterface<FdPrintfLogger>
{
  public:
    FdPrintfLogger(int _fd) : fd(_fd)
    {
    }

    void vlog_impl(const char *fmt, va_list args)
    {
        vdprintf(fd, fmt, args);
    }

  protected:
    int fd;
};

FdPrintfLogger &stderr_logger();

}; // namespace Coral
