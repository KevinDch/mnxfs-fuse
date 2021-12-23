#include <mnxfs_error.h>
#include <iostream>
#include <device.h>
#include <cstdlib>

/** @file
 *
 * This file defines test for device
 */


int main()
{
    try
    {
        system("touch /tmp/file");
        device file("/tmp/file");
        char buff[2];

        file.write("1234", 4, 0);
        file.read(buff, 2, 2);

        if (!memcmp(buff, "34", 2))
        {
            return EXIT_SUCCESS;
        }

        return EXIT_FAILURE;
    }
    catch (mnxfs_error & err)
    {
        std::cout << err.what() << ", errno=" << err.what_errno() << std::endl;
        return EXIT_FAILURE;
    }
}
