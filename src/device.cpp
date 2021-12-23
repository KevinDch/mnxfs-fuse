#include <device.h>
#include <mnxfs_error.h>

device::device(const std::string &path_to_device)
{
    device_file.open(path_to_device);
    if (!device_file)
    {
        throw mnxfs_error(CANNOT_OPEN_DEVICE);
    }
}

off64_t device::read(char *buffer, off64_t size, off64_t offset)
{
    device_file.seekg(offset);
    return device_file.readsome(buffer, size);
}

off64_t device::write(const char *buffer, off64_t size, off64_t offset)
{
    device_file.seekp(offset);
    device_file.write(buffer, size);
    return device_file.tellp() - offset;
}
