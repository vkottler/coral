#ifdef NDEBUG
#undef NDEBUG
#endif

/* internal */
#include "logging/macros.h"

/* toolchain */
#include <cassert>

void test_return_if(void)
{
    LogReturnIf(true);
}

int test_return_val_if(void)
{
    LogReturnValIf(true, 5);
}

void test_return_if_not(void)
{
    LogReturnIfNot(false);
}

int test_return_val_if_not(void)
{
    LogReturnValIfNot(false, 5);
}

int main(void)
{
    using namespace Coral;

    stderr_logger().log("Hello, world! %d\n", 1);
    stderr_logger().log("Hello, world! %d\n", 2);
    stderr_logger().log("Hello, world! %d\n", 3);

    LogIf(true);
    LogIf(1);

    LogErrnoIf(true);
    LogErrnoIf(1);

    test_return_if();

    assert(test_return_val_if() == 5);

    LogIfNot(false);
    LogErrnoIfNot(false);

    test_return_if_not();
    test_return_val_if_not();

    CORAL_LOGGER.log("Nominal exit.\n");
    return 0;
}
