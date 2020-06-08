#include <cstdint>
#include <map>
#include <stdexcept>
#include <FileBuffer.hpp>
#include "startEmulation.hpp"
#include "../../config/OpcodeDetails.hpp"
#include "../Processor/Processor.hpp"

namespace {
    int findNumberOfBytesUsedByOpcode(uint8_t opcode){
        auto iteratorAtOpcode{OpcodeDetails::bytesUsedByOpcodes.find(opcode)};

        if (iteratorAtOpcode != OpcodeDetails::bytesUsedByOpcodes.end()){
            return iteratorAtOpcode->second;
        }
        else {
            throw std::runtime_error("Not a valid opcode: " + std::to_string(opcode));
        }
    }
}

void startEmulation(Processor& processor, const FileBuffer& program){
    processor.loadProgramIntoMemory(program);

    uint16_t opcodeAddress{processor.getAddressOfNextInstruction()};
    
    uint8_t opcode{processor.readByteFromMemory(opcodeAddress)};
    uint8_t firstByteFollowingOpcode{processor.readByteFromMemory(opcodeAddress + 1)};
    uint8_t secondByteFollowingOpcode{processor.readByteFromMemory(opcodeAddress + 2)};

    switch(findNumberOfBytesUsedByOpcode(opcode)){
        case 1:
            processor.executeOneByteInstruction(opcode);
            break;

        case 2:
            processor.executeTwoByteInstruction(opcode, firstByteFollowingOpcode);
            break;

        case 3:
            processor.executeThreeByteInstruction(
                opcode,
                firstByteFollowingOpcode,
                secondByteFollowingOpcode
            );
            break;
    }
}