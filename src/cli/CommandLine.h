/**
 * \file
 * \brief A command-line argument parsing interface.
 */
#pragma once

/* toolchain */
#include <cassert>
#include <cstdint>
#include <string>

/* internal */
#include "../logging/PrintfLogger.h"

namespace Coral
{

template <typename element_t = char, class T = PrintfLogger>
class ElementCommandLine
{
  public:
    using String = std::basic_string<element_t>;

    ElementCommandLine(const element_t **_line, std::size_t _length,
                       LogInterface<T> *_log = nullptr)
        : line(_line), command(_line[0]), length(_length), log(_log)
    {
        /* At minimum a command must be provided. */
        assert(length);

        /* All arguments follow the command. */
        line = &line[1];
        length--;
    }

    template <std::size_t index>
    bool as_bool(bool &output, LogInterface<T> *_log = nullptr)
    {
        bool result = false;
        auto elem = at<index>();

        if (not _log)
        {
            _log = log;
        }

        if (elem)
        {
            String value(elem);
            if (value.compare("true") == 0)
            {
                output = true;
                result = true;
            }
            else if (value.compare("false") == 0)
            {
                output = false;
                result = true;
            }
            else if (log)
            {
                _log->log(
                    "Got '%s' and not literal value 'true' or 'false'.\n",
                    elem);
            }
        }

        return result;
    }

    template <std::size_t index>
    const element_t *at(LogInterface<T> *_log = nullptr)
    {
        const element_t *result = nullptr;

        if (not _log)
        {
            _log = log;
        }

        if (length > index)
        {
            result = line[index];
        }
        else if (log)
        {
            _log->log("No element at index %zu (%zu arguments total).\n",
                      index, length);
        }

        return result;
    }

    const String get_command()
    {
        return String(command);
    }

  protected:
    const element_t **line;
    const element_t *command;
    std::size_t length;

    LogInterface<T> *log;
};

using CommandLine = ElementCommandLine<>;

} // namespace Coral
