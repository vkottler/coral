/**
 * \file
 * \brief A simple logger implementation that uses an array buffer.
 */
#pragma once

/* toolchain */
#include <array>
#include <cstdio>
#include <functional>
#include <string>

/* internal */
#include "LogInterface.h"

namespace Coral
{

static constexpr std::size_t default_buffer_depth = BUFSIZ;

template <std::size_t depth = default_buffer_depth, typename element_t = char>
class BufferLogger : public LogInterface<BufferLogger<depth>>
{
  public:
    using String = std::basic_string<element_t>;
    using Handler = std::function<void(const String &)>;

    BufferLogger(Handler &_handler) : handler(_handler)
    {
    }

    void vlog_impl(const char *fmt, va_list args)
    {
        auto head = data.data();
        vsnprintf(head, depth, fmt, args);
        handler(String(head));
    }

  protected:
    Handler handler;
    std::array<element_t, depth> data;
};

}; // namespace Coral
