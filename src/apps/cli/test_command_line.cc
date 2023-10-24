/* internal */
#include "common.h"

bool value;

void test_first_arg_bool(const char **argc, std::size_t argv)
{
    CommandLine cli(argc, argv);
    assert(cli.as_bool<0>(value));
}

int main(void)
{
    Buffer buffer;
    Processor proc(buffer, test_first_arg_bool, true /* auto_poll */);

    std::stringstream("true\n") >> buffer;
    assert(value);

    std::stringstream("false\n") >> buffer;
    assert(not value);

    return 0;
}
