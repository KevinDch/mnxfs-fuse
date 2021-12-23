/** @file
 *
 * This file implements error class and relevant operations
 */

#include <mnxfs_error.h>

const char *mnxfs_error::what() const noexcept
{
    switch (error_code)
    {
        case EXT_LIB_ERR:
            return MNXFS_PREFIX "External library error";

        default:
            return MNXFS_PREFIX "Unknown";
    }
}
