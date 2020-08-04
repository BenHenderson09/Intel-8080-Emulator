#ifndef TIME_KEEPER_CONSTANTS_HPP
#define TIME_KEEPER_CONSTANTS_HPP

namespace TimeKeeperConstants {
    const int delayBetweenSleepFactorAdjustmentsInNanoseconds{static_cast<int>(1e7)};
    const int sleepThresholdInNanoseconds{static_cast<int>(1e4)};
}

#endif