#include <iostream>
#include <iomanip>
#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryArithmetic/BinaryArithmetic.hpp"

void Processor::executeOneByteInstruction(uint8_t opcode){
    switch(opcode){
        // NOP - Execution continues, no change to processor
        case 0x00: NOP(); break;

        // INX B - Increment register pair BC
        case 0x03: INX(registers.bc); break;

        // DCR B - Decrement register B
        case 0x05: DCR(registers.b); break;

        // DAD B - The 16-bit number in register pair BC is added to the 16-bit number held in HL
        case 0x09: DAD(registers.bc); break;
		
        // LDAX B - Set the contents of the accumulator to the value at a memory location.
        // The address of this value is found in register pair BC.
        case 0x0a: LDAX(registers.bc); break;

        // DCR C - Decrement register C
        case 0x0d: DCR(registers.c); break;

        // RRC - Rotate accumulator right
        case 0x0f: RRC(); break;

        // INX D - Increment register pair DE
        case 0x13: INX(registers.de); break;

        // DAD D - The 16-bit number in register pair DE is added to the 16-bit number held in HL
        case 0x19: DAD(registers.de); break;

        // LDAX D - Set the contents of the accumulator to the value at a memory location.
        // The address of this value is found in register pair DE.
        case 0x1a: LDAX(registers.de); break;

        // INX H - Increment register pair HL
        case 0x23: INX(registers.hl); break;

        // DAD H - The 16-bit number in register pair HL is added to itself (doubled)
        case 0x29: DAD(registers.hl); break;

        // DCR M - Decrement the value located at the specified memory address
        case 0x35: DCR(memory[registers.hl.getPairValue()]); break;

        // STC - Set the carry flag
        case 0x37: STC();

        // DCR A - Decrement register A
        case 0x3d: DCR(registers.a); break;

        // MOV B,B - Copy register B to register B (null operation)
        case 0x40: MOV(registers.b, registers.b); break;

        // MOV B,C - Copy register C to register B
        case 0x41: MOV(registers.b, registers.c); break;

        // MOV B,D - Copy register D to register B
        case 0x42: MOV(registers.b, registers.d); break;

        // MOV B,E - Copy register E to register B
        case 0x43: MOV(registers.b, registers.e); break;

        // MOV B,H - Copy register H to register B
        case 0x44: MOV(registers.b, registers.h); break;

        // MOV B,L - Copy register L to register B
        case 0x45: MOV(registers.b, registers.l); break;

        // MOV B,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the B register.
        case 0x46: MOV(registers.b, memory[registers.hl.getPairValue()]); break;

        // MOV B,A - Copy register A to register B
        case 0x47: MOV(registers.b, registers.a); break;

        // MOV C,B - Copy register B to register C
        case 0x48: MOV(registers.c, registers.b); break;

        // MOV C,C - Copy register C to register C (null operation)
        case 0x49: MOV(registers.c, registers.c); break;

        // MOV C,D - Copy register D to register C
        case 0x4a: MOV(registers.c, registers.d); break;

        // MOV C,E - Copy register E to register C
        case 0x4b: MOV(registers.c, registers.e); break;

        // MOV C,H - Copy register H to register C
        case 0x4c: MOV(registers.c, registers.h); break;

        // MOV C,L - Copy register L to register C
        case 0x4d: MOV(registers.c, registers.l); break;

        // MOV C,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the C register.
        case 0x4e: MOV(registers.c, memory[registers.hl.getPairValue()]); break;

        // MOV C,A - Copy register A to register C
        case 0x4f: MOV(registers.c, registers.a); break;

        // MOV D,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the D register.
        case 0x56: MOV(registers.d, memory[registers.hl.getPairValue()]); break;

        // MOV E,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the E register.
        case 0x5e: MOV(registers.e, memory[registers.hl.getPairValue()]); break;

        // MOV H,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the H register.
        case 0x66: MOV(registers.h, memory[registers.hl.getPairValue()]); break;

        // MOV L,A - Copy register A to register L
        case 0x6f: MOV(registers.l, registers.a); break;
    
        // MOV M,A - Store the contents of register A at the memory address
        // specified in register pair HL.
        case 0x77: MOV(memory[registers.hl.getPairValue()], registers.a); break;
    
        // MOV A,D - Copy register D to register A
        case 0x7a: MOV(registers.a, registers.d); break;

        // MOV A,E - Copy register E to register A
        case 0x7b: MOV(registers.a, registers.e); break;

        // MOV A,H - Copy register H to register A
        case 0x7c: MOV(registers.a, registers.h); break;

        // MOV A,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the A register.
        case 0x7e: MOV(registers.a, memory[registers.hl.getPairValue()]); break;

        // ANA A - Bitwise and (&) operates on the accumulator and register A
        // (A is the same register as the accumulator), with the result stored in the accumulator.
        // The accumulator remains the same in this case, with only the flags changing.
        case 0xa7: ANA(registers.a); break;

        // XRA A - Bitwise exclusive or (^) operates on the accumulator and register A
        // (A is the same register as the accumulator), with the result stored in the accumulator.
        // The accumulator remains the same in this case, with only the flags changing.
        case 0xaf: XRA(registers.a); break;

        // POP B - Remove two bytes from the top of the stack and copy their values
        // into the register pair BC
        case 0xc1: POP(registers.bc); break;

        // PUSH B - Write register pair BC to the top of the stack
        case 0xc5: PUSH(registers.bc); break;

        // RZ - If the Zero bit is one, a RET instruction occurs
        case 0xc8: RZ(); break;

        // RET - Return from subroutine. This works by popping the
        // address at the top of the stack into the program counter,
        // transferring program control.
        case 0xc9: RET(); break;

        // POP D - Remove two bytes from the top of the stack and copy their values
        // into the register pair DE
        case 0xd1: POP(registers.de); break;

        // PUSH D - Write register pair DE to the top of the stack
        case 0xd5: PUSH(registers.de); break;

        // POP H - Remove two bytes from the top of the stack and copy their values
        // into the register pair HL
        case 0xe1: POP(registers.de); break;

        // PUSH H - Write register pair HL to the top of the stack
        case 0xe5: PUSH(registers.hl); break;

        // XCHG - Swap the values of register pairs DE and HL
        case 0xeb: XCHG(); break;
    
        // POP PSW - Take the top two bytes off the stack, loading the
        // accumulator with the byte preceding the stack pointer and setting
        // the flags based on the byte at the stack pointer. This "flag byte"
        // at the stack pointer has its bits mapped to specific flags which are
        // specified in the 8080 data book.
        case 0xf1: POP_PSW(); break;

        // PUSH PSW - Pushes the accumulator followed by the "flag byte"
        // mentioned previously onto the stack.
        case 0xf5: PUSH_PSW(); break;

        // EI - Enable interrupts
        case 0xfb: EI(); break;

        default: throw UnsupportedOpcodeException(opcode);
    }

    registers.programCounter++;
}

void Processor::NOP(){}

void Processor::DCR(uint8_t& byteToDecrement){
    // Decrementing when zero will set all bits in the register, resulting in the decimal
    // value 255.
    uint8_t result{--byteToDecrement}; 

    // The sign is specified in bit seven, which allows programmers to conventionally
    // treat 8 bit numbers as having a range of -128 to +127 (two's complement).
    flags.sign = extractBit<uint8_t>(result, 7);

    flags.zero = (result == 0);
    flags.parity = isThereAnEvenCountOfOnes(result);
}

void Processor::DAD(const RegisterPair& registerPair){
    // Use 32 bits to facilitate carry
    uint32_t result{(uint32_t)(registers.hl.getPairValue() + registerPair.getPairValue())};

    // The first 16 bits will be assigned to register pair HL. This ignores the carry bit.
    registers.hl.setPairValue(result);
    
    // Bit 16 is set if a carry has occurred
    flags.carry = extractBit<uint32_t>(result, 16);
}

void Processor::RRC(){
    // Set's the carry to bit 0 of register A (accumulator),
    // shifts one position to the right and then sets
    // bit 7 of register A to the value of the carry.
    flags.carry = registers.a & 1;
    registers.a >>= 1;
    registers.a |= (flags.carry << 7);
}

void Processor::INX(RegisterPair& registerPair){
    if (registerPair.secondRegister == 0xff){
        registerPair.secondRegister = 0;
        registerPair.firstRegister++;
    }
    else {
        registerPair.secondRegister++;
    }
}

void Processor::STC(){
    flags.carry = true;
}

void Processor::LDAX(const RegisterPair& registerPair){
    registers.a = memory[registerPair.getPairValue()];
}

void Processor::MOV(uint8_t& destination, uint16_t value){
    destination = value;
}

void Processor::ANA(uint8_t registerForBitwiseAnd){
    registers.a &= registerForBitwiseAnd;
    alterFlagsAfterLogicalOperation();
}

void Processor::XRA(uint8_t registerForBitwiseXor){
    registers.a ^= registerForBitwiseXor;
    alterFlagsAfterLogicalOperation();
}

void Processor::POP(RegisterPair& registerPair){
    // The top of the stack descends through memory. I.e a POP operation will
    // result with the stack pointer being at a higher address, and vice versa for PUSH.
    // Note that we aren't actually erasing the previous stack data after we copy it to
    // the register pair, we just move the stack pointer.
    // Later on, PUSH operations will just overwrite the previous data, so we're essentially
    // removing it from the stack without deleting it.

    registerPair.firstRegister = memory[registers.stackPointer + 1];
    registerPair.secondRegister = memory[registers.stackPointer];
    registers.stackPointer += 2;
}

void Processor::POP_PSW(){
    registers.a = memory[registers.stackPointer + 1];
    uint8_t flagByte{memory[registers.stackPointer]};

    flags.sign = extractBit<uint8_t>(flagByte, 7);
    flags.zero = extractBit<uint8_t>(flagByte, 6);
    flags.auxiliaryCarry = extractBit<uint8_t>(flagByte, 4);
    flags.parity = extractBit<uint8_t>(flagByte, 2);
    flags.carry = extractBit<uint8_t>(flagByte, 0);

    registers.stackPointer += 2;
}

void Processor::PUSH(const RegisterPair& registerPair){
    // Keeping in mind how the stack descends through memory, the two addresses below
    // the stack pointer will be set to the value of the register pair.
    memory[registers.stackPointer - 1] = registerPair.firstRegister;
    memory[registers.stackPointer - 2] = registerPair.secondRegister;
    registers.stackPointer -= 2;
}

void Processor::PUSH_PSW(){
    uint8_t flagByte{0};
    setBit<uint8_t>(flagByte, 7, flags.sign);
    setBit<uint8_t>(flagByte, 6, flags.zero);
    setBit<uint8_t>(flagByte, 4, flags.auxiliaryCarry);
    setBit<uint8_t>(flagByte, 2, flags.parity);
    setBit<uint8_t>(flagByte, 0, flags.carry);

    memory[registers.stackPointer - 1] = registers.a;
    memory[registers.stackPointer - 2] = flagByte;

    registers.stackPointer -= 2;
}

void Processor::RET(){
    uint8_t highOrderByte{memory[registers.stackPointer + 1]};
    uint8_t lowOrderByte{memory[registers.stackPointer]};

    registers.programCounter =
        concatenateTwoNumbers<uint8_t, uint16_t>(highOrderByte, lowOrderByte);
        
    registers.programCounter--; // Prevent automatically advancing the program counter

    registers.stackPointer += 2; // Remove from the stack
}

void Processor::RZ(){
    if (flags.zero) RET();
}

void Processor::XCHG(){
    std::swap(registers.h, registers.d); // Swap high order byte
    std::swap(registers.l, registers.e); // Swap low order byte
}

void Processor::EI(){
    interruptEnable = true;
}
