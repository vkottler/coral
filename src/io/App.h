/**
 * \file
 * \brief An stdio application interface.
 */
#pragma once

/* toolchain */
#include <bits/stdc++.h>

/* internal */
#include "../cli/CommandLineApp.h"

namespace Coral
{

class App
{
  public:
    App(CommandLine &_cli, std::streambuf *_input) : cli(_cli), input(_input)
    {
    }

    void dispatch(void)
    {
        char c;

        /* Handle the end of the stream. */
        if (input->sgetc() == EOF)
        {
            done = true;
        }

        c = input->sbumpc();

        /* Handle escape. */
        if (c == 0x1b)
        {
            done = true;
        }

        /* Handle byte. */
        else
        {
            handle_input(c);
        }
    }

    int run(void)
    {
        int result = 0;

        init();

        while (!done)
        {
            dispatch();
        }

        return result;
    }

    /* Make this crtp. */
    void handle_input(char c)
    {
        std::cout << "You entered character 0x" << std::setw(2)
                  << std::setfill('0') << std::hex << int(c) << "'"
                  << std::endl;
    }

    /* Make this crtp. */
    void init(void)
    {
    }

  protected:
    CommandLine &cli;
    std::streambuf *input;
    bool done = false;
};

} // namespace Coral
