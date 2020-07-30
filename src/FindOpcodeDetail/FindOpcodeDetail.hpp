#ifndef FIND_OPCODE_DETAIL_HPP
#define FIND_OPCODE_DETAIL_HPP

#include <cstdint>

namespace Intel8080 {
    int findNumberOfBytesUsedByOpcode(uint8_t opcode);
    int findNumberOfCyclesUsedByOpcode(uint8_t opcode);
}

#endif