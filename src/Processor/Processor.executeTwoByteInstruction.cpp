#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"

void Processor::executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode){
    switch (opcode){
        case 0x06: throw std::runtime_error("Unsupported opcode"); break;
        case 0x0e: throw std::runtime_error("Unsupported opcode"); break;
        case 0x16: throw std::runtime_error("Unsupported opcode"); break;
        case 0x1e: throw std::runtime_error("Unsupported opcode"); break;
        case 0x26: throw std::runtime_error("Unsupported opcode"); break;
        case 0x2e: throw std::runtime_error("Unsupported opcode"); break;
        case 0x36: throw std::runtime_error("Unsupported opcode"); break;
        case 0x3e: throw std::runtime_error("Unsupported opcode"); break;
        case 0xc6: throw std::runtime_error("Unsupported opcode"); break;
        case 0xce: throw std::runtime_error("Unsupported opcode"); break;
        case 0xd3: throw std::runtime_error("Unsupported opcode"); break;
        case 0xd6: throw std::runtime_error("Unsupported opcode"); break;
        case 0xdb: throw std::runtime_error("Unsupported opcode"); break;
        case 0xde: throw std::runtime_error("Unsupported opcode"); break;
        case 0xe6: throw std::runtime_error("Unsupported opcode"); break;
        case 0xee: throw std::runtime_error("Unsupported opcode"); break;
        case 0xf6: throw std::runtime_error("Unsupported opcode"); break;
        case 0xfe: throw std::runtime_error("Unsupported opcode"); break;
    }

    programCounter += 2;
}