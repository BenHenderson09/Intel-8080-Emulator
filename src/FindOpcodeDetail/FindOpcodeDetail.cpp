#include <cstdint>
#include <stdexcept>
#include <sstream>
#include "FindOpcodeDetail.hpp"
#include "../../constants/OpcodeConstants.hpp"

namespace {
    int findOpcodeFromMap(uint8_t opcode, const std::map<uint8_t, int>& map){
        auto iteratorAtOpcode{map.find(opcode)};

        if (iteratorAtOpcode != map.end()){
            return iteratorAtOpcode->second;
        }
        else {
            std::stringstream stream;
            stream << "Not a valid opcode: 0x" << std::hex << static_cast<int>(opcode);

            throw std::invalid_argument{stream.str()};
        }
    }
}

namespace Intel8080 {
    int findNumberOfBytesUsedByOpcode(uint8_t opcode){
        return findOpcodeFromMap(opcode, OpcodeConstants::bytesUsedByOpcodes);
    }

    int findNumberOfCyclesUsedByOpcode(uint8_t opcode){
        return findOpcodeFromMap(opcode, OpcodeConstants::cyclesUsedByOpcodes);
    }
}