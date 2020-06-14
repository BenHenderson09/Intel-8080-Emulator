#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"

void Processor::executeThreeByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode,
        uint8_t secondByteFollowingOpcode){

    // The 8080 orders the operands with the least significant byte coming first when
    // reading from left to right (little endian). Here we convert those bytes to
    // a 16 bit value to make it easier to work with.
    uint16_t operands {
        concatenateTwoNumbers<uint8_t, uint16_t>(
            secondByteFollowingOpcode, // High order byte (most significant)
            firstByteFollowingOpcode   // Low order byte (least significant)
        )
    };

    switch (opcode)
    {
        // LXI B - Occupy register pair BC with the operands
        case 0x01: LXI(b, c, operands); break;

        // LXI D - Occupy register pair DE with the operands
        case 0x11: LXI(d, e, operands); break;

        case 0x21: throw UnsupportedOpcodeException(opcode); break;
        case 0x22: throw UnsupportedOpcodeException(opcode); break;
        case 0x2a: throw UnsupportedOpcodeException(opcode); break;

        // LXI SP - Set the stack pointer to the operands
        case 0x31: LXI_SP(operands); break;

        // STA - Copy the contents of the accumulator to the specified memory address
        case 0x32: STA(operands); break;

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

void Processor::LXI(uint8_t& firstRegisterOfPair, uint8_t& secondRegisterOfPair,
        uint16_t operands){
    firstRegisterOfPair = extractByte<uint16_t>(operands, 1);
    secondRegisterOfPair = extractByte<uint16_t>(operands, 0);
}

void Processor::LXI_SP(uint16_t address){
    stackPointer = address;
}

void Processor::STA(uint16_t address){
    memory[address] = a;
}