#include <cstdint>
#include "findNumberOfBytesUsedByOpcode.hpp"
#include "../../config/OpcodeDetails.hpp"

int findNumberOfBytesUsedByOpcode(uint8_t opcode){
    auto iteratorAtOpcode{OpcodeDetails::bytesUsedByOpcodes.find(opcode)};

    if (iteratorAtOpcode != OpcodeDetails::bytesUsedByOpcodes.end()){
        return iteratorAtOpcode->second;
    }
    else {
        throw std::runtime_error("Not a valid opcode: " + std::to_string(opcode));
    }
}