#ifndef REGISTER_PAIR
#define REGISTER_PAIR

#include <cstdint>

namespace Intel8080 {
    struct RegisterPair {
        uint8_t& firstRegister;
        uint8_t& secondRegister;

        void setPairValue(uint16_t value);
        uint16_t getPairValue() const;
    };
}

#endif