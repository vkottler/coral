/**
 * \file
 * \brief An stdio application interface.
 */
#pragma once

/* internal */
#include "../buffer/PcBuffer.h"
#include "../cli/CommandLineApp.h"

namespace Coral
{

template <class T, std::size_t input_buffer_depth = 8192> class App
{
  public:
    App(int argc, const char **argv, std::streambuf *_input)
        : cli(argv, argc, &logger), input(_input)
    {
    }

    inline int run(void)
    {
        _init();

        while (!done)
        {
            dispatch();
        }

        return result;
    }

    using InputBuffer = ByteBuffer<input_buffer_depth>;

  protected:
    CommandLine cli;

    /* Need to replace this with JSON logger. */
    PrintfLogger logger;

    /* Can be set by application. */
    bool done = false;
    int result = 0;

  private:
    std::streambuf *input;
    InputBuffer input_buffer;

    inline void dispatch(void)
    {
        /* Handle the end of the stream. */
        if (input->sgetc() == EOF)
        {
            done = true;
        }

        char c = input->sbumpc();

        /* Handle escape. */
        if (c == 0x1b)
        {
            done = true;
        }

        /* Handle byte. */
        else
        {
            /* Crash if we run out of buffer. */
            assert(input_buffer.push(std::byte(c)));

            /* Let the application service input. */
            _poll(input_buffer);
        }
    }

    inline void _init(void)
    {
        static_cast<T *>(this)->init();
    }

    inline void _poll(InputBuffer &input)
    {
        static_cast<T *>(this)->poll(input);
    }
};

} // namespace Coral
