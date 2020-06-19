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

        // DCR B - Decrement register B
        case 0x05: DCR(b); break;

        // DAD B - The 16-bit number in register pair BC is added to the 16-bit number held in HL
        case 0x09: DAD(b, c); break;
		
        // DCR C - Decrement register C
        case 0x0d: DCR(c); break;

        // RRC - Rotate accumulator right
        case 0x0f: RRC(); break;

        // INX D - Increment register pair DE
        case 0x13: INX(d, e); break;

        // DAD D - The 16-bit number in register pair DE is added to the 16-bit number held in HL
        case 0x19: DAD(d, e); break;

        // LDAX D - Set the contents of the accumulator to the value at a memory location.
        // The address of this location is found in the specified register pair.
        case 0x1a: LDAX(d, e); break;

        // INX H - Increment register pair HL
        case 0x23: INX(h, l); break;

        // DAD H - The 16-bit number in register pair HL is added to itself (doubled)
        case 0x29: DAD(h, l); break;

        // MOV D,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the D register.
        case 0x56: MOV(d, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break;

        // MOV E,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the E register.
        case 0x5e: MOV(e, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break;

        // MOV H,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the H register.
        case 0x66: MOV(h, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break;

        // MOV L,A - Copy register A to register L
        case 0x6f: MOV(l, a); break;
    
        // MOV M,A - Store the contents of register A at the memory address
        // specified in register pair HL.
        case 0x77: MOV(memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)], a); break;
    
        // MOV A,D - Copy register D to register A
        case 0x7a: MOV(a, d); break;

        // MOV A,E - Copy register E to register A
        case 0x7b: MOV(a, e); break;

        // MOV A,H - Copy register H to register A
        case 0x7c: MOV(a, h); break;

        // MOV A,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the A register.
        case 0x7e: MOV(a, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break;

        // ANA A - Bitwise and (&) operates on the accumulator and register A
        // (A is the same register as the accumulator), with the result stored in the accumulator.
        // The accumulator remains the same in this case, with only the flags changing.
        case 0xa7: ANA(a); break;

        // XRA A - Bitwise exclusive or (^) operates on the accumulator and register A
        // (A is the same register as the accumulator), with the result stored in the accumulator.
        // The accumulator remains the same in this case, with only the flags changing.
        case 0xaf: XRA(a); break;

        // POP B - Remove two bytes from the top of the stack and copy their values
        // into the register pair BC
        case 0xc1: POP(b, c); break;

        // PUSH B - Write register pair BC to the top of the stack
        case 0xc5: PUSH(b, c); break;

        // RET - Return from subroutine. This works by popping the
        // address at the top of the stack into the program counter,
        // transferring program control.
        case 0xc9: RET(); break;

        // POP D - Remove two bytes from the top of the stack and copy their values
        // into the register pair DE
        case 0xd1: POP(d, e); break;

        // PUSH D - Write register pair DE to the top of the stack
        case 0xd5: PUSH(d, e); break;

        // POP H - Remove two bytes from the top of the stack and copy their values
        // into the register pair HL
        case 0xe1: POP(d, e); break;

        // PUSH H - Write register pair HL to the top of the stack
        case 0xe5: PUSH(h, l); break;

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

    programCounter++;
}

void Processor::NOP(){}

void Processor::DCR(uint8_t& registerToDecrement){
    // Decrementing when zero will set all bits in the register, resulting in the decimal
    // value 255.
    uint8_t result{--registerToDecrement}; 

    // The sign is specified in bit seven, which allows programmers to conventionally
    // treat 8 bit numbers as having a range of -128 to +127 (two's complement).
    flags.sign = extractBit<uint8_t>(result, 7);

    flags.zero = (result == 0);
    flags.parity = isThereAnEvenCountOfOnes(result);
}

void Processor::DAD(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair){
    uint16_t hl{concatenateTwoNumbers<uint8_t, uint16_t>(h, l)};
    uint16_t registerPair
        {concatenateTwoNumbers<uint8_t, uint16_t>(firstRegisterOfPair, secondRegisterOfPair)};

    uint32_t result{(uint32_t)(hl + registerPair)}; // Use 32 bits to facilitate carry
    h = extractByte<uint32_t>(result, 1); // Hold second byte of result
    l = extractByte<uint32_t>(result, 0); // Hold first byte of result

    // Bit 16 is set if a carry has occurred
    flags.carry = extractBit<uint32_t>(result, 16);
}

void Processor::RRC(){
    // Set's the carry to bit 0 of register A (accumulator),
    // shifts one position to the right and then sets
    // bit 7 of register A to the value of the carry.
    flags.carry = a & 1;
    a = a >> 1;
    a = a | (flags.carry << 7);
}

void Processor::INX(uint8_t& firstRegisterOfPair, uint8_t& secondRegisterOfPair){
    if (secondRegisterOfPair == 0xff){
        secondRegisterOfPair = 0;
        firstRegisterOfPair++;
    }
    else {
        secondRegisterOfPair++;
    }
}

void Processor::LDAX(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair){
    uint16_t registerPair
        {concatenateTwoNumbers<uint8_t, uint16_t>(firstRegisterOfPair, secondRegisterOfPair)};

    a = memory[registerPair];
}

void Processor::MOV(uint8_t& destination, uint16_t value){
    destination = value;
}

void Processor::ANA(uint8_t registerForBitwiseAnd){
    a = a & registerForBitwiseAnd;
    alterFlagsAfterLogicalOperation();
}

void Processor::XRA(uint8_t registerForBitwiseXor){
    a = a ^ registerForBitwiseXor;
    alterFlagsAfterLogicalOperation();
}

void Processor::POP(uint8_t& firstRegisterOfPair, uint8_t& secondRegisterOfPair){
    // The top of the stack descends through memory. I.e a POP operation will
    // result with the stack pointer being at a higher address, and vice versa for PUSH.
    // Note that we aren't actually erasing the previous stack data after we copy it to
    // the register pair, we just move the stack pointer.
    // Later on, PUSH operations will just overwrite the previous data, so we're essentially
    // removing it from the stack without deleting it.

    firstRegisterOfPair = memory[stackPointer + 1];
    secondRegisterOfPair = memory[stackPointer];
    stackPointer += 2;
}

void Processor::POP_PSW(){
    a = memory[stackPointer + 1];
    uint8_t flagByte{memory[stackPointer]};

    flags.sign = extractBit<uint8_t>(flagByte, 7);
    flags.zero = extractBit<uint8_t>(flagByte, 6);
    flags.auxiliaryCarry = extractBit<uint8_t>(flagByte, 4);
    flags.parity = extractBit<uint8_t>(flagByte, 2);
    flags.carry = extractBit<uint8_t>(flagByte, 0);

    stackPointer += 2;
}


void Processor::PUSH(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair){
    // Keeping in mind how the stack descends through memory, the two addresses below
    // the stack pointer will be set to the value of the register pair.
    memory[stackPointer - 1] = firstRegisterOfPair;
    memory[stackPointer - 2] = secondRegisterOfPair;
    stackPointer -= 2;
}

void Processor::PUSH_PSW(){
    uint8_t flagByte{0};
    setBit<uint8_t>(flagByte, 7, flags.sign);
    setBit<uint8_t>(flagByte, 6, flags.zero);
    setBit<uint8_t>(flagByte, 4, flags.auxiliaryCarry);
    setBit<uint8_t>(flagByte, 2, flags.parity);
    setBit<uint8_t>(flagByte, 0, flags.carry);

    memory[stackPointer - 1] = a;
    memory[stackPointer - 2] = flagByte;

    stackPointer -= 2;
}

void Processor::RET(){
    // Treat these bytes as registers to allow us to use the POP function
    // and then concatenate these bytes for the 16 bit program counter
    uint8_t highOrderByte;
    uint8_t lowOrderByte;

    POP(highOrderByte, lowOrderByte);

    programCounter = concatenateTwoNumbers<uint8_t, uint16_t>(highOrderByte, lowOrderByte);
    programCounter--; // Prevent automatically advancing the program counter
}

void Processor::XCHG(){
    std::swap(h, d); // Swap high order byte
    std::swap(l, e); // Swap low order byte
}

void Processor::EI(){
    interruptEnable = true;
}
