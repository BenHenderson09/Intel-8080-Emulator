#include <functional>
#include <chrono>
#include "timeToRunInNanoseconds.hpp"

namespace Intel8080 {
    long timeToRunInNanoseconds(const std::function<void()> function){
        auto timeBeforeExecution{std::chrono::steady_clock::now()};
        function();
        auto timeAfterExecution{std::chrono::steady_clock::now()};

        return (timeAfterExecution - timeBeforeExecution).count();
    }
}