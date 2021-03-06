#include <mnxfs_error.h>
#include <iostream>

/** @file
 *
 * This file defines test for error class
 */


int main()
{
    try {
        throw mnxfs_error(EXT_LIB_ERR);
    }
    catch (std::exception & err)
    {
        std::cout << err.what() << std::endl;
        return 0;
    }
}
