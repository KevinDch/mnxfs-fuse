#ifndef MNXFS_DEVICE_H
#define MNXFS_DEVICE_H

#include <fstream>
#include <string>

class device
{
private:
    std::fstream device_file;

public:
    explicit device(const std::string & path_to_device);
    off64_t read(char * buffer, off64_t size, off64_t offset);
    off64_t write(const char * buffer, off64_t size, off64_t offset);
};


#endif //MNXFS_DEVICE_H
