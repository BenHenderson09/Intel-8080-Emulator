#include <functional>
#include <chrono>
#include "timeToRunInNanoseconds.hpp"

namespace Intel8080 {
    long timeToRunInNanoseconds(const std::function<void()> func){
        auto timeBeforeExecution{std::chrono::steady_clock::now()};
        func();
        auto timeAfterExecution{std::chrono::steady_clock::now()};

        return (timeAfterExecution - timeBeforeExecution).count();
    }
}