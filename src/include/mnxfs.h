#ifndef MNXFS_MNXFS_H
#define MNXFS_MNXFS_H

#include <cstdint>
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>

/// @file this file defines structure of MNXFS

#define FILESYSTEM_BLOCK_SIZE       4096
#define FILESYSTEM_MAGIC_NUMBER     ((uint64_t)0xAF7048CD98CE0423)
#define FILESYSTEM_MAX_FILESIZE     ((uint64_t)0xFFFFFFFFFFFFFFFF)

struct filesystem_on_disk_super_block
{
    uint64_t fs_block_count;
    uint64_t fs_inode_count;
    uint64_t fs_zone_count;
    uint64_t fs_inode_bitmap_block_count;
    uint64_t fs_zone_bitmap_block_count;
    uint64_t fs_block_of_first_data_zone;
    uint64_t fs_magic;
    uint64_t fs_mounted:1;
    struct timespec last_mount_time;

    uint8_t dummy[FILESYSTEM_BLOCK_SIZE - sizeof(uint64_t) * 7 - sizeof(last_mount_time)];
};

struct filesystem_on_disk_inode
{
    char name[128];
    struct stat fs_stat;
    uint64_t fs_1st_zone_block_nr[256];
    uint64_t fs_2st_zone_block_nr[64];
    uint64_t fs_3st_zone_block_nr[64];

    uint8_t dummy[FILESYSTEM_BLOCK_SIZE
                - sizeof (name)
                - sizeof (fs_stat)
                - sizeof (fs_1st_zone_block_nr)
                - sizeof (fs_2st_zone_block_nr)
                - sizeof (fs_3st_zone_block_nr)];
};


#endif //MNXFS_MNXFS_H
