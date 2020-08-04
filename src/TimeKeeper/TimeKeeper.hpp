#ifndef PROCESSOR_TIME_KEEPER_HPP
#define PROCESSOR_TIME_KEEPER_HPP

#include <cstdint>
#include <chrono>

namespace Intel8080 {
    class TimeKeeper {
        public:
            void handleSleepAfterInstructionExec(int execTimeInNanoseconds, uint8_t opcode);
        
        private:
            std::chrono::steady_clock::time_point
                timeWhenSleepFactorAdjusted{std::chrono::steady_clock::now()};

            double sleepFactor{1};
            int cyclesRanSinceSleepFactorAdjusted{0};
            int totalExecTimeInNanoseconds{0};
            int totalIdealExecTimeInNanoseconds{0};

            double determineSleepFactorAdjustment(int cyclesRanSinceSleepFactorAdjusted);
    };
}

#endif