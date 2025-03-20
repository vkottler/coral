/* internal */
#include "cli/Termios.h"
#include "cli/termios_util.h"
#include "cli/text.h"

/* linux */
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

/* toolchain */
#include <csignal>

namespace Coral
{

static const std::map<std::string, uint8_t> input_flags = {
    {"1", 1}, {"2", 2}, {"4", 4}, {"8", 8}, {"16", 16},
};

static void test_text(void)
{
    print_verb_name_condition("name", "verb", true);
    print_verb_name_condition("name", "verb", false);

    std::vector<std::string> flag_strs = {};
    populate_flag_strs<uint8_t>(7 + 32, flag_strs, input_flags,
                                &get_stdout(true));
}

static void test_termios(void)
{
    /*
     * Could also try stdin first.
     *
    int term_fd = fileno(stdin);
    if (not isatty(term_fd))
    {
    }
    */

    int term_fd = posix_openpt(O_RDWR | O_NOCTTY);
    print_verb_name_condition("posix", "openpt", term_fd != -1, true, true);
    assert(term_fd != -1);

    /* Initialize terminal. */
    Termios *term = initialize_terminal(term_fd);
    assert(term);
    term->info();

    assert(term->make_raw());

    assert(speed_str(B0));
    assert(speed_str(B50));
    assert(speed_str(B75));
    assert(speed_str(B110));
    assert(speed_str(B134));
    assert(speed_str(B150));
    assert(speed_str(B200));
    assert(speed_str(B300));
    assert(speed_str(B600));
    assert(speed_str(B1200));
    assert(speed_str(B1800));
    assert(speed_str(B2400));
    assert(speed_str(B4800));
    assert(speed_str(B9600));
    assert(speed_str(B19200));
    assert(speed_str(B38400));
    assert(speed_str(B57600));
    assert(speed_str(B115200));
    assert(speed_str(B230400));
    assert(speed_str(B460800));
    assert(speed_str(B500000));
    assert(speed_str(B576000));
    assert(speed_str(B921600));
    assert(speed_str(B1000000));
    assert(speed_str(B1152000));
    assert(speed_str(B1500000));
    assert(speed_str(B2000000));
    assert(speed_str(B2500000));
    assert(speed_str(B3000000));
    assert(speed_str(B3500000));
    assert(speed_str(B4000000));
    assert(speed_str(999));
}

} // namespace Coral

int main(void)
{
    using namespace Coral;

    signal(SIGINT, exit);

    test_text();
    test_termios();

    return 0;
}
