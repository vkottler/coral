/* internal */
#include "cli/Termios.h"
#include "cli/termios_util.h"
#include "cli/text.h"
#include "io/file_descriptors.h"

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

    assert(fd_info(term_fd));

    /* Initialize terminal. */
    Termios *term = initialize_terminal(term_fd);
    assert(term);
    assert(term->set_baud(115200));
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

    speed_t output;
    assert(not baud_to_speed(1, output));

    assert(baud_to_speed(0, output));
    assert(output == B0);
    assert(baud_to_speed(50, output));
    assert(output == B50);
    assert(baud_to_speed(75, output));
    assert(output == B75);
    assert(baud_to_speed(110, output));
    assert(output == B110);
    assert(baud_to_speed(134, output));
    assert(output == B134);
    assert(baud_to_speed(150, output));
    assert(output == B150);
    assert(baud_to_speed(200, output));
    assert(output == B200);
    assert(baud_to_speed(300, output));
    assert(output == B300);
    assert(baud_to_speed(600, output));
    assert(output == B600);
    assert(baud_to_speed(1200, output));
    assert(output == B1200);
    assert(baud_to_speed(1800, output));
    assert(output == B1800);
    assert(baud_to_speed(2400, output));
    assert(output == B2400);
    assert(baud_to_speed(4800, output));
    assert(output == B4800);
    assert(baud_to_speed(9600, output));
    assert(output == B9600);
    assert(baud_to_speed(19200, output));
    assert(output == B19200);
    assert(baud_to_speed(38400, output));
    assert(output == B38400);
    assert(baud_to_speed(57600, output));
    assert(output == B57600);
    assert(baud_to_speed(115200, output));
    assert(output == B115200);
    assert(baud_to_speed(230400, output));
    assert(output == B230400);
    assert(baud_to_speed(460800, output));
    assert(output == B460800);
    assert(baud_to_speed(500000, output));
    assert(output == B500000);
    assert(baud_to_speed(576000, output));
    assert(output == B576000);
    assert(baud_to_speed(921600, output));
    assert(output == B921600);
    assert(baud_to_speed(1000000, output));
    assert(output == B1000000);
    assert(baud_to_speed(1152000, output));
    assert(output == B1152000);
    assert(baud_to_speed(1500000, output));
    assert(output == B1500000);
    assert(baud_to_speed(2000000, output));
    assert(output == B2000000);
    assert(baud_to_speed(2500000, output));
    assert(output == B2500000);
    assert(baud_to_speed(3000000, output));
    assert(output == B3000000);
    assert(baud_to_speed(3500000, output));
    assert(output == B3500000);
    assert(baud_to_speed(4000000, output));
    assert(output == B4000000);
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
