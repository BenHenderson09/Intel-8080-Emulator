#ifndef REGISTER_PAIR_HPP
#define REGISTER_PAIR_HPP

#include <cstdint>

namespace Intel8080 {
    class RegisterPair {
        public:
            void setPairValue(uint16_t value);
            uint16_t getPairValue() const;
            
            uint8_t& firstRegister;
            uint8_t& secondRegister;
    };
}

#endif