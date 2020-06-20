#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"

void Processor::executeThreeByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode,
        uint8_t secondByteFollowingOpcode){

    // The 8080 orders the operands with the least significant byte coming first (little endian).
    // Here we convert those bytes to a 16 bit value to make it easier to work with for addresses.
    uint16_t address {
        concatenateTwoNumbers<uint8_t, uint16_t>(
            secondByteFollowingOpcode, // High order byte (most significant)
            firstByteFollowingOpcode   // Low order byte (least significant)
        )
    };

    switch (opcode){
        // LXI B - Occupy register pair BC with the operands
        case 0x01: LXI(registers.bc, firstByteFollowingOpcode, secondByteFollowingOpcode); break;

        // LXI D - Occupy register pair DE with the operands
        case 0x11: LXI(registers.de, firstByteFollowingOpcode, secondByteFollowingOpcode); break;

        // LXI H - Occupy register pair HL  with the operands
        case 0x21: LXI(registers.hl, firstByteFollowingOpcode, secondByteFollowingOpcode); break;

        // LXI SP - Set the stack pointer to the address
        case 0x31: LXI_SP(address); break;

        // STA - Copy the contents of the accumulator to the specified memory address
        case 0x32: STA(address); break;

        // LDA - Copy the value at the specified memory address to the accumulator 
        case 0x3a: LDA(address); break;
        
        // JNZ - Jump to the specified memory address if the zero flag equals zero
        case 0xc2: JNZ(address); break;

        // JMP - Jump to the specified memory address
        case 0xc3: JMP(address); break;
        
        // CALL - A subroutine is called by jumping to the specified memory address.
        // Also, a return address is pushed onto the stack for use with the RETURN instruction
        // when the subroutine finishes.
        case 0xcd: CALL(address); break;

        case 0xca: JZ(address); break;

        // JC - Jump to the specified memory address if the carry flag is one.
        case 0xda: JC(address); break;
        
        default: throw UnsupportedOpcodeException(opcode);
    }

    registers.programCounter += 3;
}

void Processor::LXI(RegisterPair& registerPair, uint8_t firstOperand, uint8_t secondOperand){
    registerPair.firstRegister = secondOperand;
    registerPair.secondRegister = firstOperand;
}

void Processor::LXI_SP(uint16_t address){
    registers.stackPointer = address;
}

void Processor::STA(uint16_t address){
    memory[address] = registers.a;
}

void Processor::LDA(uint16_t address){
    registers.a = memory[address];
}

void Processor::JNZ(uint16_t address){
    if (!flags.zero) JMP(address);
}

void Processor::JMP(uint16_t address){
    registers.programCounter = address;
    
    // Prevent from advancing to the next instruction automatically, as JMP is a way of
    // choosing the next instruction manually.
    registers.programCounter -= 3;
}

void Processor::CALL(uint16_t address){
    // Load return address onto the stack
    uint16_t returnAddress = registers.programCounter + 3;
    memory[registers.stackPointer - 1] = extractByte<uint16_t>(returnAddress, 1);
    memory[registers.stackPointer - 2] = extractByte<uint16_t>(returnAddress, 0);
    registers.stackPointer -= 2;
    
    // Jump to subroutine
    JMP(address);
}

void Processor::JZ(uint16_t address){
    if (flags.zero) JMP(address);
}

void Processor::JC(uint16_t address){
    if (flags.carry) JMP(address);
}