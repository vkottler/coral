/* toolchain */
#include <cassert>
#include <csignal>
#include <cstdio>

/* internal */
#include "../io/file_descriptors.h"
#include "Termios.h"
#include "termios_util.h"
#include "text.h"

namespace Coral
{

void Termios::info(std::ostream &stream)
{
    fd_info(fd, stream);
}

bool Termios::make_raw(int optional_actions)
{
    cfmakeraw(&current);
    return setattrs(optional_actions);
}

bool Termios::set_echo(bool state, int optional_actions)
{
    current.c_lflag =
        (state) ? current.c_lflag | ECHO : current.c_lflag & ~(ECHO);
    return setattrs(optional_actions);
}

bool Termios::set_canonical(bool state, int optional_actions)
{
    current.c_lflag =
        (state) ? current.c_lflag | ICANON : current.c_lflag & ~(ICANON);
    return setattrs(optional_actions);
}

bool Termios::set_baud(long baud)
{
    speed_t speed;

    /* Could be upgraded to handle setting a non-standard baud rate (requires
     * termios2?). */
    bool result = baud_to_speed(baud, speed);

    if (result)
    {
        result = cfsetspeed(&current, speed) == 0;
        assert(setattrs());
    }

    return result;
}

bool Termios::setattrs(int optional_actions)
{
    if (valid)
    {
        valid = tcsetattr(fd, optional_actions, &current) == 0;
        print_verb_name_condition("tc", "setattr", valid,
                                  true /* show_errno */,
                                  true /* error_only */);
    }

    return valid;
}

Termios::Termios(int _fd, bool _auto_close)
    : fd(_fd), valid(true), auto_close(_auto_close)
{
    assert(isatty(_fd));

    /*
     * Store the original termios structure before it's modified.
     */
    valid = tcgetattr(fd, &original) == 0;
    print_verb_name_condition("tc", "getattr", valid, true /* show_errno */,
                              true /* error_only */);
    current = original;
}

Termios::~Termios()
{
    /*
     * Restore the original termios structure.
     */
    valid = tcsetattr(fd, default_action, &original) == 0;
    print_verb_name_condition("tc", "setattr", valid, true /* show_errno */,
                              true /* error_only */);

    if (auto_close)
    {
        close(fd);
    }
}

static Termios *term = nullptr;

static void clean_up(void)
{
    /* Restore terminal settings. */
    if (term)
    {
        delete term;
        term = nullptr;
    }
}

Termios *initialize_terminal(int fd)
{
    if (isatty(fd) and not term)
    {
        term = new Termios(fd);

        /* Turn input echo and canonical mode off. */
        assert(term->set_echo(false));
        assert(term->set_canonical(false));

        /* What do these settings do? */
        term->current.c_cc[VTIME] = 0;
        term->current.c_cc[VMIN] = 1;

        assert(term->setattrs());

        /* Handle signals / clean up. */
        std::atexit(clean_up);
    }

    return term;
}

} // namespace Coral
