#include <cstdint>
#include <sstream>
#include "FindOpcodeDetail.hpp"
#include "../../config/OpcodeConfig.hpp"

namespace {
    int findOpcodeFromMap(uint8_t opcode, const std::map<uint8_t, int>& map){
        auto iteratorAtOpcode{map.find(opcode)};

        if (iteratorAtOpcode != map.end()){
            return iteratorAtOpcode->second;
        }
        else {
            std::stringstream stream;
            stream << "Not a valid opcode: 0x" << std::hex << int(opcode);

            throw std::invalid_argument{stream.str()};
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