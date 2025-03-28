/* internal */
#include "buffer/MessageBuffer.h"

static constexpr std::size_t buffer_size = 256;

int main(void)
{
    using namespace Coral;

    MessageBuffer<buffer_size, 4, char> msg_buf;
    std::array<char, buffer_size> buf = {};
    std::size_t len = 0;

    assert(not msg_buf.get_message(buf.data(), len));

    len = buffer_size;
    assert(msg_buf.put_message(buf.data(), len));
    assert(not msg_buf.put_message(buf.data(), len));

    assert(msg_buf.get_message(buf.data(), len));
    assert(not msg_buf.get_message(buf.data(), len));

    return 0;
}
