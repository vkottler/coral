/**
 * \file
 * \brief A command-line argument parsing interface.
 */
#pragma once

/* toolchain */
#include <cstdint>
#include <string>

/* internal */
#include "../logging/PrintfLogger.h"

namespace Coral
{

template <typename element_t = char> class ElementCommandLine
{
  public:
    using String = std::basic_string<element_t>;

    ElementCommandLine(const element_t **_line, std::size_t _length)
        : line(_line), length(_length)
    {
    }

    template <std::size_t index, class T = PrintfLogger>
    bool as_bool(bool &output, LogInterface<T> *log = nullptr)
    {
        bool result = false;
        auto elem = at<index>();

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
                log->log("Got '%s' and not literal value 'true' or 'false'.\n",
                         elem);
            }
        }

        return result;
    }

    template <std::size_t index, class T = PrintfLogger>
    const element_t *at(LogInterface<T> *log = nullptr)
    {
        const element_t *result = nullptr;

        if (length > index)
        {
            result = line[index];
        }
        else if (log)
        {
            log->log("No element at %zu (%zu arguments found).", index,
                     length);
        }

        return result;
    }

  protected:
    const element_t **line;
    std::size_t length;
};

using CommandLine = ElementCommandLine<>;

} // namespace Coral
