/**
 * \file
 * \brief A Linux <termios.h> interface class.
 */
#pragma once

/* linux */
#include <termios.h>

/* toolchain */
#include <iostream>

/* internal */
#include "CommandLine.h"

namespace Coral
{

class Termios
{
  public:
    static constexpr int default_action = TCSAFLUSH;

    Termios(int _fd, bool _auto_close = true);
    ~Termios();

    void info(std::ostream &stream = std::cout);

    Result make_raw(int optional_actions = default_action);

    Result set_echo(bool state, int optional_actions = default_action);
    Result set_canonical(bool state, int optional_actions = default_action);
    Result set_baud(long baud);

    const int fd;

    struct termios current;
    Result setattrs(int optional_actions = default_action);

  protected:
    struct termios original;
    bool valid;
    bool auto_close;
};

Termios *initialize_terminal(int fd);

} // namespace Coral
