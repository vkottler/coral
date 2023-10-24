/* internal */
#include "common.h"

bool value;
PrintfLogger logger;

void test_first_arg_bool(const char **argc, std::size_t argv)
{
    CommandLine cli(argc, argv, &logger);

    assert(cli.get_command().compare("cmd") == 0);

    assert(cli.as_bool<0>(value));

    assert(not cli.as_bool<1>(value));
}

void test_first_arg_not_bool(const char **argc, std::size_t argv)
{
    CommandLine cli(argc, argv, &logger);

    assert(not cli.as_bool<0>(value));
}

void test_bools_basic(Buffer &buffer)
{
    Processor proc(buffer, test_first_arg_bool, true /* auto_poll */);

    std::stringstream("cmd true\n") >> buffer;
    assert(value);

    std::stringstream("cmd false\n") >> buffer;
    assert(not value);

    buffer.set_data_available();
    Processor new_proc(buffer, test_first_arg_not_bool, true /* auto_poll */);

    std::stringstream("cmd ASDF\n") >> buffer;
    assert(not value);
}

int main(void)
{
    Buffer buffer;

    test_bools_basic(buffer);

    return 0;
}
