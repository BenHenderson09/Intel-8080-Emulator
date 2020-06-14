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

        case 0x02: throw UnsupportedOpcodeException(opcode); break; 
        case 0x03: throw UnsupportedOpcodeException(opcode); break;
        case 0x04: throw UnsupportedOpcodeException(opcode); break; 

        // DCR B - Decrement register B
        case 0x05: DCR(b); break;

        case 0x07: throw UnsupportedOpcodeException(opcode); break;

        // DAD B - The 16-bit number in register pair BC is added to the 16-bit number held in HL
        case 0x09: DAD(b, c); break;
			
        case 0x0a: throw UnsupportedOpcodeException(opcode); break; 
        case 0x0b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x0c: throw UnsupportedOpcodeException(opcode); break; 

        // DCR C - Decrement register C
        case 0x0d: DCR(c); break;

        // RRC - Rotate accumulator right
        case 0x0f: RRC(); break;

        case 0x12: throw UnsupportedOpcodeException(opcode); break;

        // INX D - Increment register pair DE
        case 0x13: INX(d, e); break; 

        case 0x14: throw UnsupportedOpcodeException(opcode); break; 
        case 0x15: throw UnsupportedOpcodeException(opcode); break; 
        case 0x17: throw UnsupportedOpcodeException(opcode); break; 

        // DAD D - The 16-bit number in register pair DE is added to the 16-bit number held in HL
        case 0x19: DAD(d, e); break;

        // LDAX D - Set the contents of the accumulator to the value at a memory location.
        // The address of this location is found in the specified register pair.
        case 0x1a: LDAX(d, e); break; 

        case 0x1b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x1c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x1d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x1f: throw UnsupportedOpcodeException(opcode); break; 

        // INX H - Increment register pair HL
        case 0x23: INX(h, l); break; 

        case 0x24: throw UnsupportedOpcodeException(opcode); break; 
        case 0x25: throw UnsupportedOpcodeException(opcode); break; 
        case 0x27: throw UnsupportedOpcodeException(opcode); break; 

        // DAD H - The 16-bit number in register pair HL is added to itself (doubled)
        case 0x29: DAD(h, l); break; 

        case 0x2b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x2c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x2d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x2f: throw UnsupportedOpcodeException(opcode); break; 
        case 0x33: throw UnsupportedOpcodeException(opcode); break; 
        case 0x34: throw UnsupportedOpcodeException(opcode); break; 
        case 0x35: throw UnsupportedOpcodeException(opcode); break; 
        case 0x37: throw UnsupportedOpcodeException(opcode); break; 
        case 0x39: throw UnsupportedOpcodeException(opcode); break; 
        case 0x3b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x3c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x3d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x3f: throw UnsupportedOpcodeException(opcode); break; 
        case 0x40: throw UnsupportedOpcodeException(opcode); break; 
        case 0x41: throw UnsupportedOpcodeException(opcode); break;
        case 0x42: throw UnsupportedOpcodeException(opcode); break; 
        case 0x43: throw UnsupportedOpcodeException(opcode); break; 
        case 0x44: throw UnsupportedOpcodeException(opcode); break; 
        case 0x45: throw UnsupportedOpcodeException(opcode); break; 
        case 0x46: throw UnsupportedOpcodeException(opcode); break; 
        case 0x47: throw UnsupportedOpcodeException(opcode); break; 
        case 0x48: throw UnsupportedOpcodeException(opcode); break; 
        case 0x49: throw UnsupportedOpcodeException(opcode); break; 
        case 0x4a: throw UnsupportedOpcodeException(opcode); break; 
        case 0x4b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x4c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x4d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x4e: throw UnsupportedOpcodeException(opcode); break; 
        case 0x4f: throw UnsupportedOpcodeException(opcode); break; 
        case 0x50: throw UnsupportedOpcodeException(opcode); break; 
        case 0x51: throw UnsupportedOpcodeException(opcode); break; 
        case 0x52: throw UnsupportedOpcodeException(opcode); break; 
        case 0x53: throw UnsupportedOpcodeException(opcode); break; 
        case 0x54: throw UnsupportedOpcodeException(opcode); break; 
        case 0x55: throw UnsupportedOpcodeException(opcode); break; 

        // MOV D,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the D register.
        case 0x56: MOV(d, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break;

        case 0x57: throw UnsupportedOpcodeException(opcode); break; 
        case 0x58: throw UnsupportedOpcodeException(opcode); break; 
        case 0x59: throw UnsupportedOpcodeException(opcode); break; 
        case 0x5a: throw UnsupportedOpcodeException(opcode); break; 
        case 0x5b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x5c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x5d: throw UnsupportedOpcodeException(opcode); break; 

        // MOV E,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the E register.
        case 0x5e: MOV(e, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break; 

        case 0x5f: throw UnsupportedOpcodeException(opcode); break; 
        case 0x60: throw UnsupportedOpcodeException(opcode); break; 
        case 0x61: throw UnsupportedOpcodeException(opcode); break; 
        case 0x62: throw UnsupportedOpcodeException(opcode); break; 
        case 0x63: throw UnsupportedOpcodeException(opcode); break; 
        case 0x64: throw UnsupportedOpcodeException(opcode); break; 
        case 0x65: throw UnsupportedOpcodeException(opcode); break; 

        // MOV H,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the H register.
        case 0x66: MOV(h, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break; 

        case 0x67: throw UnsupportedOpcodeException(opcode); break; 
        case 0x68: throw UnsupportedOpcodeException(opcode); break; 
        case 0x69: throw UnsupportedOpcodeException(opcode); break; 
        case 0x6a: throw UnsupportedOpcodeException(opcode); break; 
        case 0x6b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x6c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x6d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x6e: throw UnsupportedOpcodeException(opcode); break;

        // MOV L,A - Copy register A to register L
        case 0x6f: MOV(l, a); break; 
        
        case 0x70: throw UnsupportedOpcodeException(opcode); break; 
        case 0x71: throw UnsupportedOpcodeException(opcode); break; 
        case 0x72: throw UnsupportedOpcodeException(opcode); break; 
        case 0x73: throw UnsupportedOpcodeException(opcode); break; 
        case 0x74: throw UnsupportedOpcodeException(opcode); break; 
        case 0x75: throw UnsupportedOpcodeException(opcode); break; 
        case 0x76: throw UnsupportedOpcodeException(opcode); break; 
        
        // MOV M,A - Store the contents of register A at the memory address
        // specified in register pair HL.
        case 0x77: MOV(memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)], a); break; 
        
        case 0x78: throw UnsupportedOpcodeException(opcode); break; 
        case 0x79: throw UnsupportedOpcodeException(opcode); break; 
        
        // MOV A,D - Copy register D to register A
        case 0x7a: MOV(a, d); break; 

        // MOV A,E - Copy register E to register A
        case 0x7b: MOV(a, e); break; 

        // MOV A,H - Copy register H to register A
        case 0x7c: MOV(a, h); break; 

        case 0x7d: throw UnsupportedOpcodeException(opcode); break; 

        // MOV A,M - In this case, register pair HL stores a memory address,
        // so copy the value at this address to the A register.
        case 0x7e: MOV(a, memory[concatenateTwoNumbers<uint8_t, uint16_t>(h, l)]); break;

        case 0x7f: throw UnsupportedOpcodeException(opcode); break; 
        case 0x80: throw UnsupportedOpcodeException(opcode); break; 
        case 0x81: throw UnsupportedOpcodeException(opcode); break; 
        case 0x82: throw UnsupportedOpcodeException(opcode); break; 
        case 0x83: throw UnsupportedOpcodeException(opcode); break; 
        case 0x84: throw UnsupportedOpcodeException(opcode); break; 
        case 0x85: throw UnsupportedOpcodeException(opcode); break; 
        case 0x86: throw UnsupportedOpcodeException(opcode); break; 
        case 0x87: throw UnsupportedOpcodeException(opcode); break; 
        case 0x88: throw UnsupportedOpcodeException(opcode); break; 
        case 0x89: throw UnsupportedOpcodeException(opcode); break; 
        case 0x8a: throw UnsupportedOpcodeException(opcode); break; 
        case 0x8b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x8c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x8d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x8e: throw UnsupportedOpcodeException(opcode); break; 
        case 0x8f: throw UnsupportedOpcodeException(opcode); break; 
        case 0x90: throw UnsupportedOpcodeException(opcode); break; 
        case 0x91: throw UnsupportedOpcodeException(opcode); break; 
        case 0x92: throw UnsupportedOpcodeException(opcode); break; 
        case 0x93: throw UnsupportedOpcodeException(opcode); break; 
        case 0x94: throw UnsupportedOpcodeException(opcode); break; 
        case 0x95: throw UnsupportedOpcodeException(opcode); break; 
        case 0x96: throw UnsupportedOpcodeException(opcode); break; 
        case 0x97: throw UnsupportedOpcodeException(opcode); break; 
        case 0x98: throw UnsupportedOpcodeException(opcode); break; 
        case 0x99: throw UnsupportedOpcodeException(opcode); break; 
        case 0x9a: throw UnsupportedOpcodeException(opcode); break; 
        case 0x9b: throw UnsupportedOpcodeException(opcode); break; 
        case 0x9c: throw UnsupportedOpcodeException(opcode); break; 
        case 0x9d: throw UnsupportedOpcodeException(opcode); break; 
        case 0x9e: throw UnsupportedOpcodeException(opcode); break; 
        case 0x9f: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa0: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa1: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa2: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa3: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa4: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa5: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa6: throw UnsupportedOpcodeException(opcode); break; 

        // ANA A - Bitwise and (&) operates on the accumulator and register A
        // (A is the same register as the accumulator), with the result stored in the accumulator.
        // The f the accumulator remains the same in this case, with only the flags changing.
        case 0xa7: ANA(a); break; 

        case 0xa8: throw UnsupportedOpcodeException(opcode); break; 
        case 0xa9: throw UnsupportedOpcodeException(opcode); break; 
        case 0xaa: throw UnsupportedOpcodeException(opcode); break; 
        case 0xab: throw UnsupportedOpcodeException(opcode); break; 
        case 0xac: throw UnsupportedOpcodeException(opcode); break; 
        case 0xad: throw UnsupportedOpcodeException(opcode); break; 
        case 0xae: throw UnsupportedOpcodeException(opcode); break; 

        // XRA A - Bitwise exclusive or (^) operates on the accumulator and register A
        // (A is the same register as the accumulator), with the result stored in the accumulator.
        // The accumulator remains the same in this case, with only the flags changing.
        case 0xaf: XRA(a); break; 

        case 0xb0: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb1: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb2: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb3: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb4: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb5: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb6: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb7: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb8: throw UnsupportedOpcodeException(opcode); break; 
        case 0xb9: throw UnsupportedOpcodeException(opcode); break; 
        case 0xba: throw UnsupportedOpcodeException(opcode); break; 
        case 0xbb: throw UnsupportedOpcodeException(opcode); break; 
        case 0xbc: throw UnsupportedOpcodeException(opcode); break; 
        case 0xbd: throw UnsupportedOpcodeException(opcode); break; 
        case 0xbe: throw UnsupportedOpcodeException(opcode); break; 
        case 0xbf: throw UnsupportedOpcodeException(opcode); break; 
        case 0xc0: throw UnsupportedOpcodeException(opcode); break; 

        // POP B - Remove two bytes from the top of the stack and copy their values
        // into the register pair BC
        case 0xc1: POP(b, c); break; 

        // PUSH B - Write register pair BC to the top of the stack
        case 0xc5: PUSH(b, c); break; 

        case 0xc7: throw UnsupportedOpcodeException(opcode); break; 
        case 0xc8: throw UnsupportedOpcodeException(opcode); break; 

        // RET - Return from subroutine. This works by popping the
        // address at the top of the stack into the program counter,
        // transferring program control.
        case 0xc9: RET(); break; 

        case 0xcf: throw UnsupportedOpcodeException(opcode); break; 
        case 0xd0: throw UnsupportedOpcodeException(opcode); break;

        // POP D - Remove two bytes from the top of the stack and copy their values
        // into the register pair DE
        case 0xd1: POP(d, e); break; 

        // PUSH D - Write register pair DE to the top of the stack
        case 0xd5: PUSH(d, e); break;

        case 0xd7: throw UnsupportedOpcodeException(opcode); break; 
        case 0xd8: throw UnsupportedOpcodeException(opcode); break; 
        case 0xdf: throw UnsupportedOpcodeException(opcode); break; 
        case 0xe0: throw UnsupportedOpcodeException(opcode); break; 

        // POP H - Remove two bytes from the top of the stack and copy their values
        // into the register pair HL
        case 0xe1: POP(d, e); break; 

        case 0xe3: throw UnsupportedOpcodeException(opcode); break; 

        // PUSH H - Write register pair HL to the top of the stack
        case 0xe5: PUSH(h, l); break;

        case 0xe7: throw UnsupportedOpcodeException(opcode); break; 
        case 0xe8: throw UnsupportedOpcodeException(opcode); break; 
        case 0xe9: throw UnsupportedOpcodeException(opcode); break; 

        // XCHG - Swap the values of register pairs DE and HL
        case 0xeb: XCHG(); break; 
        
        case 0xef: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf0: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf1: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf3: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf5: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf7: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf8: throw UnsupportedOpcodeException(opcode); break; 
        case 0xf9: throw UnsupportedOpcodeException(opcode); break; 
        case 0xfb: throw UnsupportedOpcodeException(opcode); break; 
        case 0xff: throw UnsupportedOpcodeException(opcode); break; 
    }

    programCounter++;
}

void Processor::NOP(){}

void Processor::DCR(uint8_t& registerToDecrement){
    // Prevent underflows
    uint8_t result{registerToDecrement == 0 ? registerToDecrement : --registerToDecrement};

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

    uint32_t result{(uint32_t) hl + registerPair}; // Use 32 bits to facilitate carry
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

void Processor::PUSH(uint8_t firstRegisterOfPair, uint8_t secondRegisterOfPair){
    // Keeping in mind how the stack descends through memory, the two addresses below
    // the stack pointer will be set to the value of the register pair.
    memory[stackPointer - 1] = firstRegisterOfPair;
    memory[stackPointer - 2] = secondRegisterOfPair;
    stackPointer -= 2;
}

void Processor::RET(){
    // Treat these bytes as registers to allow us to use the POP function
    // and then concatenate these bytes for the 16 bit program counter
    uint8_t highOrderByte;
    uint8_t lowOrderByte;

    POP(highOrderByte, lowOrderByte);

    programCounter = concatenateTwoNumbers<uint8_t, uint16_t>(highOrderByte, lowOrderByte);
}

void Processor::XCHG(){
    std::swap(h, d); // Swap high order byte
    std::swap(e, l); // Swap low order byte
}