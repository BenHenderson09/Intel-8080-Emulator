#include "TimeKeeper.hpp"

#include <cstdint>
#include <chrono>
#include <thread>
#include "../FindOpcodeDetail/FindOpcodeDetail.hpp"
#include "../../constants/ProcessorConstants.hpp"
#include "../../constants/TimeKeeperConstants.hpp"

namespace Intel8080 {
    void TimeKeeper::handleSleepAfterInstructionExec(int execTimeInNanoseconds, uint8_t opcode){
        updateCountsAfterInstructionExec(execTimeInNanoseconds, opcode);
        adjustSleepFactorIfDelayHasElapsed();
        sleepIfThresholdHasBeenMet();
    }

    void TimeKeeper::updateCountsAfterInstructionExec(int execTimeInNanoseconds, uint8_t opcode){
        int cyclesUsedByOpcode{findNumberOfCyclesUsedByOpcode(opcode)};
        double nanosecondsPerCycle{1e9 / ProcessorConstants::clockSpeedInHertz};

        cyclesRanSinceSleepFactorAdjusted += cyclesUsedByOpcode;
        execTimeSinceThresholdMetInNanoseconds += execTimeInNanoseconds;
        idealExecTimeSinceThresholdMetInNanoseconds +=
            static_cast<int>(cyclesUsedByOpcode * nanosecondsPerCycle);
    }

    void TimeKeeper::sleepIfThresholdHasBeenMet(){
        int differenceInExecTimes {
            idealExecTimeSinceThresholdMetInNanoseconds - execTimeSinceThresholdMetInNanoseconds
        };

        if (differenceInExecTimes >= TimeKeeperConstants::sleepThresholdInNanoseconds){
            std::this_thread::sleep_for(
                std::chrono::nanoseconds(TimeKeeperConstants::sleepThresholdInNanoseconds)
            );

            idealExecTimeSinceThresholdMetInNanoseconds = 0;
            execTimeSinceThresholdMetInNanoseconds =
                TimeKeeperConstants::sleepThresholdInNanoseconds * sleepFactor;
        }
    }

    void TimeKeeper::adjustSleepFactorIfDelayHasElapsed(){
        if (hasTheSleepFactorAdjustmentDelayElapsed()){
            timeWhenSleepFactorAdjusted = std::chrono::steady_clock::now();

            sleepFactor += determineSleepFactorAdjustment();
            cyclesRanSinceSleepFactorAdjusted = 0;
        }
    }

    bool TimeKeeper::hasTheSleepFactorAdjustmentDelayElapsed(){
        int nanosecondsElapsedSincePreviousAdjustment {static_cast<int>(
            (std::chrono::steady_clock::now() - timeWhenSleepFactorAdjusted).count()
        )};

        return nanosecondsElapsedSincePreviousAdjustment >=
            TimeKeeperConstants::delayBetweenSleepFactorAdjustmentsInNanoseconds;
    }

    double TimeKeeper::determineSleepFactorAdjustment(){
        double idealCyclesPerAdjustment {
            ProcessorConstants::clockSpeedInHertz *
            (TimeKeeperConstants::delayBetweenSleepFactorAdjustmentsInNanoseconds / 1e9)
        };

        // Positive means we're running too slowly, negative means too fast.
        double cyclesAwayFromIdealClockSpeed {
            idealCyclesPerAdjustment - cyclesRanSinceSleepFactorAdjusted
        };

        // The sleep factor will be increased or decreased by the percentage inaccuracy,
        // which will slow down or speed up the execution proportional to how close we are
        // to the ideal clock speed.
        return cyclesAwayFromIdealClockSpeed / idealCyclesPerAdjustment;
    }
}