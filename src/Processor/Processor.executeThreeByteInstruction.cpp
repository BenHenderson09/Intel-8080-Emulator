#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"

void Processor::executeThreeByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode,
        uint8_t secondByteFollowingOpcode){
    switch (opcode)
    {
        case 0x01: throw std::runtime_error("Unsupported opcode"); break;
        case 0x11: throw std::runtime_error("Unsupported opcode"); break;
        case 0x21: throw std::runtime_error("Unsupported opcode"); break;
        case 0x22: throw std::runtime_error("Unsupported opcode"); break;
        case 0x2a: throw std::runtime_error("Unsupported opcode"); break;
        case 0x31: throw std::runtime_error("Unsupported opcode"); break;
        case 0x32: throw std::runtime_error("Unsupported opcode"); break;
        case 0x3a: throw std::runtime_error("Unsupported opcode"); break;
        case 0xc2: throw std::runtime_error("Unsupported opcode"); break;
        case 0xc3: throw std::runtime_error("Unsupported opcode"); break;
        case 0xc4: throw std::runtime_error("Unsupported opcode"); break;
        case 0xca: throw std::runtime_error("Unsupported opcode"); break;
        case 0xcc: throw std::runtime_error("Unsupported opcode"); break;
        case 0xcd: throw std::runtime_error("Unsupported opcode"); break;
        case 0xd2: throw std::runtime_error("Unsupported opcode"); break;
        case 0xd4: throw std::runtime_error("Unsupported opcode"); break;
        case 0xda: throw std::runtime_error("Unsupported opcode"); break;
        case 0xdc: throw std::runtime_error("Unsupported opcode"); break;
        case 0xdf: throw std::runtime_error("Unsupported opcode"); break;
        case 0xe2: throw std::runtime_error("Unsupported opcode"); break;
        case 0xe4: throw std::runtime_error("Unsupported opcode"); break;
        case 0xea: throw std::runtime_error("Unsupported opcode"); break;
        case 0xec: throw std::runtime_error("Unsupported opcode"); break;
        case 0xf2: throw std::runtime_error("Unsupported opcode"); break;
        case 0xf4: throw std::runtime_error("Unsupported opcode"); break;
        case 0xfa: throw std::runtime_error("Unsupported opcode"); break;
        case 0xfc: throw std::runtime_error("Unsupported opcode"); break;
    }

    programCounter += 3;
}