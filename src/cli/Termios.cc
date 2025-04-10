/* toolchain */
#include <cassert>
#include <csignal>
#include <cstdio>

/* internal */
#include "../io/file_descriptors.h"
#include "../logging/macros.h"
#include "Termios.h"
#include "termios_util.h"

namespace Coral
{

void Termios::info(std::ostream &stream)
{
    fd_info(fd, stream);
}

Result Termios::make_raw(int optional_actions)
{
    cfmakeraw(&current);
    return setattrs(optional_actions);
}

Result Termios::set_echo(bool state, int optional_actions)
{
    current.c_lflag =
        (state) ? current.c_lflag | ECHO : current.c_lflag & ~(ECHO);
    return setattrs(optional_actions);
}

Result Termios::set_canonical(bool state, int optional_actions)
{
    current.c_lflag =
        (state) ? current.c_lflag | ICANON : current.c_lflag & ~(ICANON);
    return setattrs(optional_actions);
}

Result Termios::set_baud(long baud)
{
    speed_t speed;

    /* Could be upgraded to handle setting a non-standard baud rate (requires
     * termios2?). */
    auto result = ToBool(baud_to_speed(baud, speed));

    if (result)
    {
        result = cfsetspeed(&current, speed) == 0;
        LogErrnoIfNot(setattrs());
    }

    return ToResult(result);
}

Result Termios::setattrs(int optional_actions)
{
    if (valid)
    {
        valid = tcsetattr(fd, optional_actions, &current) == 0;
        LogErrnoIfNot(valid);
    }

    return ToResult(valid);
}

Termios::Termios(int _fd, bool _auto_close)
    : fd(_fd), valid(true), auto_close(_auto_close)
{
    assert(isatty(_fd));

    /*
     * Store the original termios structure before it's modified.
     */
    valid = tcgetattr(fd, &original) == 0;
    LogErrnoIfNot(valid);
    current = original;
}

Termios::~Termios()
{
    /*
     * Restore the original termios structure.
     */
    valid = tcsetattr(fd, default_action, &original) == 0;
    LogErrnoIfNot(valid);

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
        LogErrnoIfNot(term->set_echo(false));
        LogErrnoIfNot(term->set_canonical(false));

        /* What do these settings do? */
        term->current.c_cc[VTIME] = 0;
        term->current.c_cc[VMIN] = 1;

        LogErrnoIfNot(term->setattrs());

        /* Handle signals / clean up. */
        std::atexit(clean_up);
    }

    return term;
}

} // namespace Coral
