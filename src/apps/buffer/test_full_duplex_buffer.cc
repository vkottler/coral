#ifdef NDEBUG
#undef NDEBUG
#endif

/* internal */
#include "SampleFdBuffer.h"

int main(void)
{
    SampleFdBuffer buffer;

    /* Feed TX buffer. */
    std::stringstream("Hello, world! (tx)\n") >> buffer.tx;

    /* Feed RX buffer. */
    std::stringstream("Hello, world! (rx)\n") >> buffer.rx;
    std::cout << buffer.rx;

    return 0;
}
