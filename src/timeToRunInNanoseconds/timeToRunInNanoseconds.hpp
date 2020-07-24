#ifndef TIME_TO_RUN_IN_NANOSECONDS
#define TIME_TO_RUN_IN_NANOSECONDS

#include <functional>

namespace Intel8080 {
    long timeToRunInNanoseconds(const std::function<void()> func);
}

#endif