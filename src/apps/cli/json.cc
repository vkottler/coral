/* toolchain */
#include <csignal>

/* internal */
#include "../../cli/Termios.h"
#include "../../io/App.h"
#include "common.h"

Termios *term = nullptr;

void clean_up(void)
{
    /* Restore terminal settings. */
    if (term)
    {
        delete term;
        term = nullptr;
    }
}

void signal_handler(int signum)
{
    clean_up();
    exit(signum);
}

void initialize_terminal(int fd)
{
    term = new Termios(fd);
    term->info();

    /* Turn input echo and canonical mode off. */
    assert(term->set_echo(false));
    assert(term->set_canonical(false));

    /* What do these settings do? */
    term->current.c_cc[VTIME] = 0;
    term->current.c_cc[VMIN] = 1;
    assert(term->setattrs());
}

int main(int argv, const char **argc)
{
    /* Handle signals. */
    signal(SIGINT, signal_handler);

    /* Initialize terminal. */
    initialize_terminal(fileno(stdin));

    /* Read character inputs. */
    CommandLine cli(argc, argv, &logger);

    /* Run application. */
    App app(cli, std::cin.rdbuf());

    int result = app.run();

    clean_up();

    return result;
}
