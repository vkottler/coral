/* internal */
#include "common.h"

int main(void)
{
    CommandLineApp::Processor::Buffer buffer;

    CommandLineApp app(buffer, &logger);
    (void)app;

    /* Trigger help. */
    std::stringstream("cmd 123.0 asdf\n") >> buffer;
    std::stringstream("help\n") >> buffer;

    return 0;
}
