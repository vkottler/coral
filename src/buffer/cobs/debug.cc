/* internal */
#include "debug.h"

namespace Coral
{

void dump_buffer(const uint8_t *data, std::size_t size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        printf("%02x ", data[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}

} // namespace Coral
