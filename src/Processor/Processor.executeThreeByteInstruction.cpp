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
    // a 16 bit value to make it easier to work with for addresses.
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

        // LXI SP - Set the stack pointer to the operands
        case 0x31: LXI_SP(operands); break;

        // STA - Copy the contents of the accumulator to the specified memory address
        case 0x32: STA(operands); break;

        // LDA - Copy the value at the specified memory address to the accumulator 
        case 0x3a: LDA(operands); break;
        
        // JNZ - Jump to the specified memory address if the zero flag equals zero
        case 0xc2: JNZ(operands); break;

        // JMP - Jump to the specified memory address
        case 0xc3: JMP(operands); break;
        
        // CALL - A subroutine is called by jumping to the specified memory address.
        // Also, a return address is pushed onto the stack for use with the RETURN instruction
        // when the subroutine finishes.
        case 0xcd: CALL(operands); break;
        
        default: throw UnsupportedOpcodeException(opcode);
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

void Processor::LDA(uint16_t address){
    a = memory[address];
}

void Processor::JNZ(uint16_t address){
    if (flags.zero == 0) JMP(address);
}

void Processor::JMP(uint16_t address){
    programCounter = address;
}

void Processor::CALL(uint16_t address){
    // Load return address onto the stack
    memory[stackPointer - 1] = extractByte<uint16_t>(address, 1);
    memory[stackPointer - 2] = extractByte<uint16_t>(address, 0);
    stackPointer -= 2;

    // Jump to subroutine
    JMP(address);
}