#ifndef MNXFS_MNXFS_H
#define MNXFS_MNXFS_H

/// @file this file defines structure of MNXFS

/* Each file system begins with a boot block. This contains executable code.
 * The size of a boot block is always 1024 bytes (two disk sectors).
 * When the computer is turned on, the hardware reads the boot block from the boot device into memory,
 * jumps to it, and begins executing its code. The boot block code begins the process of
 * loading the operating system itself. Once the system has been booted, the boot block is not used anymore.
 * Not every disk drive can be used as a boot device, but to keep the structure uniform,
 * every block device has a block reserved for boot block code.
 * At worst this strategy wastes one block. To prevent the hardware from trying to boot an unbootable device,
 * a magic number is placed at a known location in the boot block when and only when the
 * executable code is written to the device. When booting from a device, the hardware (actually, the BIOS code)
 * will refuse to attempt to load from a device lacking the magic number.
 * Doing this prevents inadvertently using garbage as a boot program.
 * */

#endif //MNXFS_MNXFS_H
