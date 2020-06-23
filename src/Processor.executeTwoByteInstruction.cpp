#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "BinaryArithmetic/BinaryArithmetic.hpp"

void Processor::executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode){
    switch (opcode){
        // MVI B - Move immediate data to register B
        case 0x06: MVI(registers.b, firstByteFollowingOpcode); break;
        
        // MVI C - Move immediate data to register C
        case 0x0e: MVI(registers.c, firstByteFollowingOpcode); break;

        // MVI H - Move immediate data to register H
        case 0x26: MVI(registers.h, firstByteFollowingOpcode); break;

        // MVI M - Move immediate data to the memory location specified by
        // register pair HL
        case 0x36: MVI(
                memory[concatenateTwoNumbers<uint8_t, uint16_t>(registers.h, registers.l)],
                firstByteFollowingOpcode
            ); break;

        // MVI A - Move immediate data to register A
        case 0x3e: MVI(registers.a, firstByteFollowingOpcode); break;

        // ADI - Add immediate data to the accumulator
        case 0xc6: ADI(firstByteFollowingOpcode); break;
    
        // OUT - The contents of the accumulator are sent to an output device.
        // Ouput devices have not yet been implemented, so just skip on for now.
        case 0xd3: break;

        // IN - An input device writes a byte to the accumulator.
        // Input devices have not yet been implemented, so just skip on for now.
        case 0xdb: break;

        // ANI - Perform a bitwise and (&) with the immediate data and the accumulator,
        // storing the result in the accumulator
        case 0xe6: ANI(firstByteFollowingOpcode); break;
    
        // CPI - Compare the immediate data with the contents of the accumulator.
        // This is done internally by subtracting the data from the accumulator contents and
        // setting the flags as appropriate without actually changing the value held in the accumulator
        // after the operation has finished. I.e Only the flags change. For example, you could use the zero
        // flag to test for equality.
        case 0xfe: CPI(firstByteFollowingOpcode); break;

        default: throw UnsupportedOpcodeException(opcode);
    }

    registers.programCounter += 2;
}

void Processor::MVI(uint8_t& destination, uint8_t data){
    destination = data;
}

void Processor::ADI(uint8_t addend){
    uint16_t result{(uint16_t)(registers.a + addend)}; // Use 16 bits to facilitate carry
    uint8_t lowOrderByte{extractByte<uint16_t>(result, 0)};

    flags.sign = extractBit<uint8_t>(lowOrderByte, 7);
    flags.zero = (lowOrderByte == 0);
    flags.parity = isThereAnEvenCountOfOnes(lowOrderByte);
    flags.carry = extractBit<uint16_t>(result, 8);

    registers.a = lowOrderByte;
}

void Processor::ANI(uint8_t valueForBitwiseAnd){
    registers.a &= valueForBitwiseAnd;
    alterFlagsAfterLogicalOperation();
}

void Processor::CPI(uint8_t dataToCompare){
    uint8_t result = registers.a - dataToCompare;

    flags.carry = (registers.a < dataToCompare);
    flags.sign = extractBit<uint8_t>(result, 7);
    flags.zero = (result == 0);
    flags.parity = isThereAnEvenCountOfOnes(result);
}