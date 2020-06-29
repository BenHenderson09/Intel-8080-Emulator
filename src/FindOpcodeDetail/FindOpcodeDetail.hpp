#ifndef FIND_OPCODE_DETAIL
#define FIND_OPCODE_DETAIL

#include <cstdint>
#include <map>

namespace Intel8080 {
    int findNumberOfBytesUsedByOpcode(uint8_t opcode);
    int findNumberOfCyclesUsedByOpcode(uint8_t opcode);
}

#endif