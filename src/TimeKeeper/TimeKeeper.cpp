#include "TimeKeeper.hpp"

#include <cstdint>
#include <chrono>
#include <thread>
#include "../FindOpcodeDetail/FindOpcodeDetail.hpp"
#include "../../constants/ProcessorConstants.hpp"

namespace Intel8080 {
    void TimeKeeper::handleSleepAfterInstructionExec(int execTimeInNanoseconds, uint8_t opcode){
        int cyclesUsedByOpcode{findNumberOfCyclesUsedByOpcode(opcode)};
        const double nanosecondsPerCycle{1e9 / ProcessorConstants::clockSpeedInHertz};

        cyclesRanSinceSleepFactorAdjusted += cyclesUsedByOpcode;
        totalExecTimeInNanoseconds += execTimeInNanoseconds;
        totalIdealExecTimeInNanoseconds +=
            static_cast<int>(cyclesUsedByOpcode * nanosecondsPerCycle);

        if (totalIdealExecTimeInNanoseconds - totalExecTimeInNanoseconds >= 1e4){
            std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<int>(1e4)));

            totalExecTimeInNanoseconds += 1e4 * sleepFactor;
        }

        sleepFactor += determineSleepFactorAdjustment(cyclesRanSinceSleepFactorAdjusted);
        cyclesRanSinceSleepFactorAdjusted = 0;
    }

    double TimeKeeper::determineSleepFactorAdjustment(int cyclesRanSinceSleepFactorAdjusted){
        int delayBetweenAdjustmentsInNanoseconds{static_cast<int>(1e7)};
        int desiredCyclesPerAdjustment {static_cast<int>(
            ProcessorConstants::clockSpeedInHertz *
            (delayBetweenAdjustmentsInNanoseconds / 1e9)
        )};

        int nanosecondsElapsedSincePreviousAdjustment {static_cast<int>(
            (std::chrono::steady_clock::now() - timeWhenSleepFactorAdjusted).count()
        )};

        bool hasTheSpecifiedDelayElapsed {
            nanosecondsElapsedSincePreviousAdjustment >= delayBetweenAdjustmentsInNanoseconds
        };

        if (hasTheSpecifiedDelayElapsed){
            // Positive means we're running to slowly, negative means too fast.
            int cyclesAwayFromIdealClockSpeed =
                desiredCyclesPerAdjustment - cyclesRanSinceSleepFactorAdjusted;

            timeWhenSleepFactorAdjusted = std::chrono::steady_clock::now();

            // The sleep factor will be increased or decreased by the percentage inaccuracy,
            // which will slow down or speed up the execution proportional to how close we are
            // to the desired clock speed.
            return static_cast<double>(cyclesAwayFromIdealClockSpeed) /
                desiredCyclesPerAdjustment;
        }

        return 0;
    }
}