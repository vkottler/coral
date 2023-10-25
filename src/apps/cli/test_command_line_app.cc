/* internal */
#include "common.h"

using CommandLine = CommandLineApp::CommandLine;

void test1(CommandLine &cli)
{
    (void)cli;
}

void test2(CommandLine &cli)
{
    (void)cli;
}

void register_commands(CommandLineApp &app)
{
    app.add_handler("test1", test1);
    app.add_handler("test2", test2, "run the 'test2' method");
}

int main(void)
{
    CommandLineApp::Processor::Buffer buffer;

    CommandLineApp app(register_commands, buffer, &logger);

    /* Trigger help. */
    std::stringstream("cmd 123.0 asdf\n") >> buffer;
    std::stringstream("help\n") >> buffer;

    /* Run commands. */
    std::stringstream("test1\n") >> buffer;
    std::stringstream("test2\n") >> buffer;

    return 0;
}
