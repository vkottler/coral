/* internal */
#include "cli/Termios.h"
#include "cli/text.h"

/* linux */
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
    int term_fd = fileno(stdin);
    if (not isatty(term_fd))
    {
        // get a pseudo terminal
    }

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
