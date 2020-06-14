#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"

void Processor::executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode){
    switch (opcode){
        // MVI B - Move immediate data to register B
        case 0x06: MVI(b, firstByteFollowingOpcode); break;
        
        // MVI C - Move immediate data to register C
        case 0x0e: MVI(c, firstByteFollowingOpcode); break;

        case 0x16: throw UnsupportedOpcodeException(opcode); break;
        case 0x1e: throw UnsupportedOpcodeException(opcode); break;

        // MVI H - Move immediate data to register H
        case 0x26: MVI(h, firstByteFollowingOpcode); break;

        case 0x2e: throw UnsupportedOpcodeException(opcode); break;

        // MVI M - Move immediate data to the memory location specified by
        // register pair HL
        case 0x36: MVI(
                memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)],
                firstByteFollowingOpcode
            );
            break;

        // MVI A - Move immediate data to register A
        case 0x3e: MVI(a, firstByteFollowingOpcode); break;

        // ADI - Add immediate data to the accumulator
        case 0xc6: ADI(firstByteFollowingOpcode); break;
        
        case 0xce: throw UnsupportedOpcodeException(opcode); break;
        case 0xd3: throw UnsupportedOpcodeException(opcode); break;
        case 0xd6: throw UnsupportedOpcodeException(opcode); break;
        case 0xdb: throw UnsupportedOpcodeException(opcode); break;
        case 0xde: throw UnsupportedOpcodeException(opcode); break;

        // ANI - Perform a bitwise and (&) with the immediate data and the accumulator,
        // storing the result in the accumulator
        case 0xe6: ANI(firstByteFollowingOpcode); break;
        
        case 0xee: throw UnsupportedOpcodeException(opcode); break;
        case 0xf6: throw UnsupportedOpcodeException(opcode); break;
        case 0xfe: throw UnsupportedOpcodeException(opcode); break;
    }

    programCounter += 2;
}

void Processor::MVI(uint8_t& destination, uint8_t data){
    destination = data;
}

void Processor::ADI(uint8_t addend){
    uint16_t result{(uint16_t)(a + addend)}; // Use 16 bits to facilitate carry
    uint8_t lowOrderByte{extractByte<uint16_t>(result, 0)};

    flags.sign = extractBit<uint8_t>(lowOrderByte, 7);
    flags.zero = (lowOrderByte == 0);
    flags.parity = isThereAnEvenCountOfOnes(lowOrderByte);
    flags.carry = extractBit<uint16_t>(result, 8);

    a = lowOrderByte;
}

void Processor::ANI(uint8_t valueForBitwiseAnd){
    a = a & valueForBitwiseAnd;
    alterFlagsAfterLogicalOperation();
}