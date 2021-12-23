#ifndef MNXFS_ERROR_H
#define MNXFS_ERROR_H

/** @file
 *
 * This file defines runtime error class and relevant operations
 */

#include <string>
#include <utility>
#include <cstring>

#define EXT_LIB_ERR         0xA0000001      /* External library error */
#define CANNOT_OPEN_DEVICE  0xA0000002      /* Cannot open device */

/// Filesystem Error Type
class mnxfs_error : public std::exception
{
private:
    uint32_t error_code;
    error_t _errno;

public:
    /// Generate a error with error code
    /** @param _code Your error code **/
    explicit mnxfs_error(unsigned int _code) noexcept : error_code(_code), _errno(errno) {}

    /// Return explanation of current error
    [[nodiscard]] const char * what() const noexcept override;

    /// Return the explanation of errno snapshoted when the current error is generated
    [[nodiscard]] const char * what_errno() const noexcept { return strerror(_errno); };

    /// Return the errno snapshoted when the current error is generated
    [[nodiscard]] error_t my_errno() const noexcept { return _errno; }

    /// Return the error code of current error
    [[nodiscard]] unsigned int my_errcode() const noexcept { return error_code; }
};

#endif //MNXFS_ERROR_H
