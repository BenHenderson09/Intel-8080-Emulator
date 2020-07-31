#ifndef TIME_TO_RUN_IN_NANOSECONDS_HPP
#define TIME_TO_RUN_IN_NANOSECONDS_HPP

#include <functional>

namespace Intel8080 {
    long timeToRunInNanoseconds(const std::function<void()> function);
}

#endif