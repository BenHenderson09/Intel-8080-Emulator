#include <cstdint>
#include "FindOpcodeDetail.hpp"
#include "../../config/OpcodeConfig.hpp"

namespace {
    int findOpcodeFromMap(uint8_t opcode, const std::map<uint8_t, int>& map){
        auto iteratorAtOpcode{map.find(opcode)};

        if (iteratorAtOpcode != map.end()){
            return iteratorAtOpcode->second;
        }
        else {
            throw std::runtime_error("Not a valid opcode: " + std::to_string(opcode));
        }
    }
}

namespace Intel8080 {
    int findNumberOfBytesUsedByOpcode(uint8_t opcode){
        return findOpcodeFromMap(opcode, OpcodeConfig::bytesUsedByOpcodes);
    }

    int findNumberOfCyclesUsedByOpcode(uint8_t opcode){
        return findOpcodeFromMap(opcode, OpcodeConfig::cyclesUsedByOpcodes);
    }
}