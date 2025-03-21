/* internal */
#include "io/FdManager.h"

/**/
#include <cassert>

/* linux */
#include <fcntl.h>

int main(void)
{
    using namespace Coral;

    assert(fd_info(fileno(stdin)));
    assert(fd_info(fileno(stdout)));
    assert(fd_info(fileno(stderr)));

    {
        FdManager fds;
        char *path = std::tmpnam(nullptr);
        assert(fds.add_file_fd(path, "wb+"));
        int fd = fds[path];

        auto file = std::tmpfile();
        fds.add_fd("tmp", fileno(file));
        std::fclose(file);

        fcntl(fd, F_SETFD, FD_CLOEXEC);

        fd_info(fd);

        fd_set_blocking_state(fd, true);
        fd_set_blocking_state(fd, false);
    }

    return 0;
}
