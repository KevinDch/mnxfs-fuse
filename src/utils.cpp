#include <utils.h>

struct timespec current_time()
{
    struct timespec ts{};
    timespec_get(&ts, TIME_UTC);
    return ts;
}
