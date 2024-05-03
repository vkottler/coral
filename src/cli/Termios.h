/**
 * \file
 * \brief A Linux <termios.h> interface class.
 */
#pragma once

/* linux */
#include <termios.h>

/* toolchain */
#include <iostream>

namespace Coral
{

class Termios
{
  public:
    static constexpr int default_action = TCSAFLUSH;

    Termios(int _fd);
    ~Termios();

    void info(std::ostream &stream = std::cout);

    bool make_raw(int optional_actions = default_action);

    bool set_echo(bool state, int optional_actions = default_action);
    bool set_canonical(bool state, int optional_actions = default_action);

    const int fd;

    struct termios current;
    bool setattrs(int optional_actions = default_action);

  protected:
    struct termios original;
    bool valid;
};

} // namespace Coral
