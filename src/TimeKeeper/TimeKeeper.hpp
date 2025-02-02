#ifndef TIME_KEEPER_HPP
#define TIME_KEEPER_HPP

#include <cstdint>
#include <chrono>

namespace Intel8080 {
    class TimeKeeper {
        public:
            void handleSleepAfterInstructionExec(int execTimeInNanoseconds, uint8_t opcode);
        
        private:
            std::chrono::steady_clock::time_point
                timeWhenSleepFactorAdjusted{std::chrono::steady_clock::now()};

            int cyclesRanSinceSleepFactorAdjusted{0};
            int execTimeSinceThresholdMetInNanoseconds{0};
            int idealExecTimeSinceThresholdMetInNanoseconds{0};
            double sleepFactor{1};
            
            void updateCountsAfterInstructionExec(int execTimeInNanoseconds, uint8_t opcode);
            void sleepIfThresholdHasBeenMet();
            void adjustSleepFactorIfDelayHasElapsed();
            double determineSleepFactorAdjustment();
            bool hasTheSleepFactorAdjustmentDelayElapsed();
    };
}

#endif