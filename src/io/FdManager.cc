/* internal */
#include "FdManager.h"

namespace Coral
{

FdManager::~FdManager()
{
    for (const auto &[name, fds] : groups)
    {
        std::cout << "Closing file-descriptor group '" << name << "'."
                  << std::endl;
        close_fds(fds);
    }
}

Result FdManager::add_file_fd(const std::string path, const std::string mode,
                              const std::string group)
{
    return get_file_fd(path, fd_group(group), mode);
}

FdMap &FdManager::fd_group(const std::string group)
{
    if (groups.try_emplace(group, FdMap()).second)
    {
        std::cout << "Created file-descriptor group '" << group << "'."
                  << std::endl;
    }
    return groups[group];
}

Result FdManager::add_fd(const std::string name, int fd,
                         const std::string group)
{
    FdMap &fds = fd_group(group);
    bool result = not fds.contains(name);
    if (result)
    {
        std::cout << "Adding [" << group << "][" << name << "] = " << fd << "."
                  << std::endl;
        fds[name] = fd;
    }
    return ToResult(result);
}

int &FdManager::operator[](const std::string name)
{
    return fd_group()[name];
}

} // namespace Coral
