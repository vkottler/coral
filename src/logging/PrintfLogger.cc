#include "PrintfLogger.h"

namespace Coral
{

static auto static_logger = FdPrintfLogger(fileno(stderr));

FdPrintfLogger &stderr_logger()
{
    return static_logger;
}

} // namespace Coral
