#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"


void Processor::executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode){
    switch (opcode){
        case 0x06: throw UnsupportedOpcodeException(opcode); break;
        case 0x0e: throw UnsupportedOpcodeException(opcode); break;
        case 0x16: throw UnsupportedOpcodeException(opcode); break;
        case 0x1e: throw UnsupportedOpcodeException(opcode); break;
        case 0x26: throw UnsupportedOpcodeException(opcode); break;
        case 0x2e: throw UnsupportedOpcodeException(opcode); break;
        case 0x36: throw UnsupportedOpcodeException(opcode); break;
        case 0x3e: throw UnsupportedOpcodeException(opcode); break;
        case 0xc6: throw UnsupportedOpcodeException(opcode); break;
        case 0xce: throw UnsupportedOpcodeException(opcode); break;
        case 0xd3: throw UnsupportedOpcodeException(opcode); break;
        case 0xd6: throw UnsupportedOpcodeException(opcode); break;
        case 0xdb: throw UnsupportedOpcodeException(opcode); break;
        case 0xde: throw UnsupportedOpcodeException(opcode); break;
        case 0xe6: throw UnsupportedOpcodeException(opcode); break;
        case 0xee: throw UnsupportedOpcodeException(opcode); break;
        case 0xf6: throw UnsupportedOpcodeException(opcode); break;
        case 0xfe: throw UnsupportedOpcodeException(opcode); break;
    }

    programCounter += 2;
}