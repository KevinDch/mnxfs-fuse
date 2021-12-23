#include <mnxfs.h>
#include <device.h>
#include <mnxfs_error.h>
#include <iostream>
#include <getopt.h>
#include <utils.h>

void help(const char * argv)
{
    std::cout << argv << " [DEVICE]" << std::endl;
}

void mk_super_block(device & _device);
void clear_bitmap(device & _device);

int main(int argc, char ** argv)
{
    int c;

    while (true)
    {
        static struct option long_options[] =
                {
                        /* These options set a flag. */
                        {"help",    no_argument,       nullptr, 'h'},
                        {nullptr, 0, nullptr, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "h",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 'h':
                help(*argv);
                return EXIT_SUCCESS;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
                abort ();
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind + 1 == argc)
    {
        try
        {
            device _device(argv[optind]);
            mk_super_block(_device);
            clear_bitmap(_device);
        }
        catch (std::exception & err)
        {
            std::cerr << err.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "Cannot parsing arguments." << std::endl;
        return EXIT_FAILURE;
    }
}

void mk_super_block(device & _device)
{
    try
    {
        uint64_t block_count = _device.device_size() / FILESYSTEM_BLOCK_SIZE;
        uint64_t usable_bitmap_block_count = block_count / (FILESYSTEM_BLOCK_SIZE * 8 + 1);

        if (usable_bitmap_block_count == 0)
        {
            std::cerr << "Disk is too small" << std::endl;
            exit(EXIT_FAILURE);
        }

        uint64_t usable_data_block_count =  8 * FILESYSTEM_BLOCK_SIZE * usable_bitmap_block_count;
        uint64_t usable_block_count = usable_data_block_count + usable_bitmap_block_count;
        auto fs_inode_count = (uint64_t)((double)(usable_data_block_count) * 0.2);
        uint64_t fs_inode_bitmap_block_count = fs_inode_count / 8 / FILESYSTEM_BLOCK_SIZE;

        if (fs_inode_bitmap_block_count == 0)
        {
            fs_inode_bitmap_block_count = 1;
        }

        // reformat
        fs_inode_count = fs_inode_bitmap_block_count * FILESYSTEM_BLOCK_SIZE * 8;
        uint64_t fs_zone_count =  (usable_bitmap_block_count - fs_inode_bitmap_block_count) * FILESYSTEM_BLOCK_SIZE * 8;

        uint64_t fs_zone_bitmap_block_count = usable_bitmap_block_count - fs_inode_bitmap_block_count;
        uint64_t fs_block_of_first_data_zone = usable_bitmap_block_count;

        if (fs_zone_count == 0)
        {
            std::cerr << "Disk is too small" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Filesystem block count: " << usable_block_count << std::endl
                  << "Bitmap block count: " << usable_bitmap_block_count
                  << " (inode:" << fs_inode_bitmap_block_count << ", zone:" << fs_zone_bitmap_block_count << ")" << std::endl
                  << "Inode count: " << fs_inode_count << std::endl
                  << "Zone count:" << fs_zone_count << std::endl;

        filesystem_on_disk_super_block super_block =
                {
                .fs_block_count = usable_block_count,
                .fs_inode_count = fs_inode_count,
                .fs_zone_count = fs_zone_count,
                .fs_inode_bitmap_block_count = fs_inode_bitmap_block_count,
                .fs_zone_bitmap_block_count = fs_zone_bitmap_block_count,
                .fs_block_of_first_data_zone = fs_block_of_first_data_zone,
                .fs_magic = FILESYSTEM_MAGIC_NUMBER,
                .fs_mounted = 0,
                .last_mount_time = current_time()
                };

        _device.write((char*)&super_block, sizeof(super_block), 0);
    }
    catch (std::exception & err)
    {
        std::cerr << err.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void clear_bitmap(device & _device)
{
    std::cout << "Clearing bitmap...";

    uint64_t block_count = _device.device_size() / FILESYSTEM_BLOCK_SIZE;
    uint64_t usable_bitmap_block_count = block_count / (FILESYSTEM_BLOCK_SIZE * 8 + 1);
    uint8_t dummy[FILESYSTEM_BLOCK_SIZE] {};
    for (uint64_t i = 1; i <= usable_bitmap_block_count; i++)
    {
        _device.write((char *) &dummy, sizeof(dummy), FILESYSTEM_BLOCK_SIZE * i);
    }

    std::cout << ". done" << std::endl;
}
