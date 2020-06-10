#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"


void Processor::executeThreeByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode,
        uint8_t secondByteFollowingOpcode){
    switch (opcode)
    {
        case 0x01:  // LXI B - Occupy register pair BC with the next two bytes (little endian)
            c = firstByteFollowingOpcode;
			b = secondByteFollowingOpcode;
            break;
        case 0x11: throw UnsupportedOpcodeException(opcode); break;
        case 0x21: throw UnsupportedOpcodeException(opcode); break;
        case 0x22: throw UnsupportedOpcodeException(opcode); break;
        case 0x2a: throw UnsupportedOpcodeException(opcode); break;
        case 0x31: throw UnsupportedOpcodeException(opcode); break;
        case 0x32: throw UnsupportedOpcodeException(opcode); break;
        case 0x3a: throw UnsupportedOpcodeException(opcode); break;
        case 0xc2: throw UnsupportedOpcodeException(opcode); break;
        case 0xc3: throw UnsupportedOpcodeException(opcode); break;
        case 0xc4: throw UnsupportedOpcodeException(opcode); break;
        case 0xca: throw UnsupportedOpcodeException(opcode); break;
        case 0xcc: throw UnsupportedOpcodeException(opcode); break;
        case 0xcd: throw UnsupportedOpcodeException(opcode); break;
        case 0xd2: throw UnsupportedOpcodeException(opcode); break;
        case 0xd4: throw UnsupportedOpcodeException(opcode); break;
        case 0xda: throw UnsupportedOpcodeException(opcode); break;
        case 0xdc: throw UnsupportedOpcodeException(opcode); break;
        case 0xdf: throw UnsupportedOpcodeException(opcode); break;
        case 0xe2: throw UnsupportedOpcodeException(opcode); break;
        case 0xe4: throw UnsupportedOpcodeException(opcode); break;
        case 0xea: throw UnsupportedOpcodeException(opcode); break;
        case 0xec: throw UnsupportedOpcodeException(opcode); break;
        case 0xf2: throw UnsupportedOpcodeException(opcode); break;
        case 0xf4: throw UnsupportedOpcodeException(opcode); break;
        case 0xfa: throw UnsupportedOpcodeException(opcode); break;
        case 0xfc: throw UnsupportedOpcodeException(opcode); break;
    }

    programCounter += 3;
}