#include <cstdint>
#include "RegisterPair.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"

void RegisterPair::setPairValue(uint16_t value){
    firstRegister = extractByte<uint16_t>(value, 1);
    secondRegister = extractByte<uint16_t>(value, 0);
}

uint16_t RegisterPair::getPairValue() const {
    return concatenateTwoNumbers<uint8_t, uint16_t>(firstRegister, secondRegister);
}