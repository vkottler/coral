#ifdef NDEBUG
#undef NDEBUG
#endif

/* internal */
#include "common.h"

bool processed = false;

void command_handler(const char **argc, std::size_t argv)
{
    assert(argv == 3);

    std::cout << "'" << argc[0] << "'" << std::endl;
    assert(strcmp(argc[0], "a") == 0);

    std::cout << "'" << argc[1] << "'" << std::endl;
    assert(strcmp(argc[1], "b") == 0);

    std::cout << "'" << argc[2] << "'" << std::endl;
    assert(strcmp(argc[2], "c") == 0);

    processed = true;
}

int main(void)
{
    Buffer buffer;
    Processor proc(buffer, command_handler);

    assert(proc.poll() == 0);

    std::stringstream("a b c\n") >> buffer;
    assert(proc.poll() == 1);
    assert(processed);

    assert(proc.poll() == 0);

    /* Ensure that expected dropping behavior works. */
    for (std::size_t i = 0; i < depth - 1; i++)
    {
        assert(buffer.push('x'));
    }
    assert(proc.poll() == 0);

    std::stringstream("a b c\n") >> buffer;
    assert(proc.poll() == 1);

    std::stringstream("\na b c\n") >> buffer;
    assert(proc.poll() == 1);

    std::stringstream("\n\na    b    c   \n\n") >> buffer;
    assert(proc.poll() == 1);

    proc.process("  a   b   c  ");
    std::string test = "a b c";
    proc.process(test);

    /* Test automatic polling. */
    processed = false;
    Processor new_proc =
        Processor(buffer, command_handler, true /* auto_poll */);
    std::stringstream("a b c\n") >> buffer;
    assert(proc.poll() == 0);
    assert(processed);

    return 0;
}
