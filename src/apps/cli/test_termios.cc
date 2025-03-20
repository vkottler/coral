/* internal */
#include "cli/Termios.h"
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
