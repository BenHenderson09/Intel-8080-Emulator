#include <cstdint>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryOperations/BinaryOperations.hpp"

namespace Intel8080 {
    void Processor::executeOneByteInstruction(){
        uint8_t opcode{getNextOpcode()};

        switch(opcode){
            // NOP - Execution continues, no change to processor
            case 0x00: NOP(); break;

            // STAX B - The contents of the accumulator are stored at the memory
            // location specified in register pair BC
            case 0x02: STAX(registers.bc); break;

            // INX B - Increment register pair BC
            case 0x03: INX(registers.bc); break;

            // INR B - Increment register B
            case 0x04: INR(registers.b); break;

            // DCR B - Decrement register B
            case 0x05: DCR(registers.b); break;

            // RLC - Rotate accumulator left
            case 0x07: RLC(); break;

            // DAD B - The 16-bit number in register pair BC is
            // added to the 16-bit number held in HL
            case 0x09: DAD(registers.bc); break;
            
            // LDAX B - Set the contents of the accumulator to the value held at the memory
            // location specified in register pair BC.
            case 0x0a: LDAX(registers.bc); break;

            // DCX B - Decrement register pair BC
            case 0x0b: DCX(registers.bc); break;

            // INR C - Increment register C
            case 0x0c: INR(registers.c); break;

            // DCR C - Decrement register C
            case 0x0d: DCR(registers.c); break;

            // RRC - Rotate accumulator right
            case 0x0f: RRC(); break;

            // STAX D - The contents of the accumulator are stored at
            // the memory location specified in register pair DE
            case 0x12: STAX(registers.de); break;

            // INX D - Increment register pair DE
            case 0x13: INX(registers.de); break;

            // INR D - Increment register D
            case 0x14: INR(registers.d); break;

            // DCR D - Decrement register D
            case 0x15: DCR(registers.d); break;
            
            // RAL - Rotate accumulator left through carry
            case 0x17: RAL(); break;

            // DAD D - The 16-bit number in register pair DE is added
            // to the 16-bit number held in HL
            case 0x19: DAD(registers.de); break;

            // LDAX D - Set the contents of the accumulator to the value held at the memory
            // location specified in register pair DE.
            case 0x1a: LDAX(registers.de); break;

            // DCX D - Decrement register pair DE
            case 0x1b: DCX(registers.de); break;

            // INR E - Increment register E
            case 0x1c: INR(registers.e); break;

            // DCR E - Decrement register E
            case 0x1d: DCR(registers.e); break;

            // RAR - Rotate accumulator right through carry
            case 0x1f: RAR(); break;

            // INX H - Increment register pair HL
            case 0x23: INX(registers.hl); break;

            // INR H - Increment register H
            case 0x24: INR(registers.h); break;

            // DCR H - Decrement register H
            case 0x25: DCR(registers.h); break;

            // DAA - If the least significant four bits of the accumulator make a number greater
            // than 9, or if the auxiliary carry flag is set, then add six to the accumulator.
            // If the most significant four bits of the accumulator make a number greater than
            // 9, or if the carry flag is set, the most significant
            // four bits of the accumulator are incremented by six.
            case 0x27: DAA(); break;

            // DAD H - The 16-bit number in register pair HL is added to itself (doubled)
            case 0x29: DAD(registers.hl); break;

            // DCX H - Decrement register pair HL
            case 0x2b: DCX(registers.hl); break;

            // INR L - Increment register L
            case 0x2c: INR(registers.l); break;

            // DCR L - Decrement register L
            case 0x2d: DCR(registers.l); break;

            // CMA - Perform a bitwise not on the accumulator
            case 0x2f: CMA(); break;

            // INX SP - Increment the stack pointer 
            case 0x33: INX_SP(); break;

            // INR M - Increment value held at the memory location specified by register pair HL
            case 0x34: INR(memory[registers.hl.getPairValue()]); break;

            // DCR M - Decrement value held at the memory location specified by register pair HL
            case 0x35: DCR(memory[registers.hl.getPairValue()]); break;

            // STC - Set the carry flag
            case 0x37: STC(); break;

            // DCX SP - Decrement the stack pointer
            case 0x3b: DCX_SP(); break;

            // INR A - Increment register A
            case 0x3c: INR(registers.a); break;

            // DCR A - Decrement register A
            case 0x3d: DCR(registers.a); break;

            // CMC - Toggle the carry bit
            case 0x3f: CMC(); break;

            // MOV B,B - Copy register B to register B (state left unchanged)
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

            // MOV C,C - Copy register C to register C (state left unchanged)
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

            // MOV D,B - Copy register B to register D
            case 0x50: MOV(registers.d, registers.b); break;

            // MOV D,C - Copy register C to register D
            case 0x51: MOV(registers.d, registers.c); break;

            // MOV D,D - Copy register D to register D (state left unchanged)
            case 0x52: MOV(registers.d, registers.d); break;

            // MOV D,E - Copy register E to register D
            case 0x53: MOV(registers.d, registers.e); break;

            // MOV D,H - Copy register H to register D
            case 0x54: MOV(registers.d, registers.h); break;

            // MOV D,L - Copy register L to register D
            case 0x55: MOV(registers.d, registers.l); break;

            // MOV D,M - In this case, register pair HL stores a memory address,
            // so copy the value at this address to the D register.
            case 0x56: MOV(registers.d, memory[registers.hl.getPairValue()]); break;

            // MOV D,A - Copy register A to register D
            case 0x57: MOV(registers.d, registers.a); break;

            // MOV E,B - Copy register B to register E
            case 0x58: MOV(registers.e, registers.b); break;

            // MOV E,C - Copy register C to register E
            case 0x59: MOV(registers.e, registers.c); break;

            // MOV E,D - Copy register D to register E 
            case 0x5a: MOV(registers.e, registers.d); break;

            // MOV E,E - Copy register E to register E (state left unchanged)
            case 0x5b: MOV(registers.e, registers.e); break;

            // MOV E,H - Copy register H to register E
            case 0x5c: MOV(registers.e, registers.h); break;

            // MOV E,L - Copy register L to register E
            case 0x5d: MOV(registers.e, registers.l); break;

            // MOV E,M - In this case, register pair HL stores a memory address,
            // so copy the value at this address to the E register.
            case 0x5e: MOV(registers.e, memory[registers.hl.getPairValue()]); break;

            // MOV E,A - Copy register A to register E
            case 0x5f: MOV(registers.e, registers.a); break;

            // MOV H,B - Copy register B to register H
            case 0x60: MOV(registers.h, registers.b); break;

            // MOV H,C - Copy register C to register H
            case 0x61: MOV(registers.h, registers.c); break;

            // MOV H,D - Copy register D to register H 
            case 0x62: MOV(registers.h, registers.d); break;

            // MOV H,E - Copy register E to register H
            case 0x63: MOV(registers.h, registers.e); break;

            // MOV H,H - Copy register H to register H (state left unchanged)
            case 0x64: MOV(registers.h, registers.h); break;

            // MOV H,L - Copy register L to register H
            case 0x65: MOV(registers.h, registers.l); break;

            // MOV H,M - In this case, register pair HL stores a memory address,
            // so copy the value at this address to the H register.
            case 0x66: MOV(registers.h, memory[registers.hl.getPairValue()]); break;

            // MOV H,A - Copy register A to register H
            case 0x67: MOV(registers.h, registers.a); break;

            // MOV L,B - Copy register B to register L
            case 0x68: MOV(registers.l, registers.b); break;

            // MOV L,C - Copy register C to register L
            case 0x69: MOV(registers.l, registers.c); break;

            // MOV L,D - Copy register D to register L 
            case 0x6a: MOV(registers.l, registers.d); break;

            // MOV L,E - Copy register E to register L
            case 0x6b: MOV(registers.l, registers.e); break;

            // MOV L,H - Copy register H to register L 
            case 0x6c: MOV(registers.l, registers.h); break;

            // MOV L,L - Copy register L to register L (state left unchanged)
            case 0x6d: MOV(registers.l, registers.l); break;

            // MOV L,M - In this case, register pair HL stores a memory address,
            // so copy the value at this address to the L register.
            case 0x6e: MOV(registers.l, memory[registers.hl.getPairValue()]); break;

            // MOV L,A - Copy register A to register L
            case 0x6f: MOV(registers.l, registers.a); break;
        
            // MOV M,B - Store the contents of register B at the memory address
            // specified in register pair HL.
            case 0x70: MOV(memory[registers.hl.getPairValue()], registers.b); break;

            // MOV M,C - Store the contents of register C at the memory address
            // specified in register pair HL.
            case 0x71: MOV(memory[registers.hl.getPairValue()], registers.c); break;

            // MOV M,D - Store the contents of register D at the memory address
            // specified in register pair HL.
            case 0x72: MOV(memory[registers.hl.getPairValue()], registers.d); break;

            // MOV M,E - Store the contents of register E at the memory address
            // specified in register pair HL.
            case 0x73: MOV(memory[registers.hl.getPairValue()], registers.e); break;

            // MOV M,H - Store the contents of register H at the memory address
            // specified in register pair HL.
            case 0x74: MOV(memory[registers.hl.getPairValue()], registers.h); break;

            // MOV M,L - Store the contents of register L at the memory address
            // specified in register pair HL.
            case 0x75: MOV(memory[registers.hl.getPairValue()], registers.l); break;

            // MOV M,A - Store the contents of register A at the memory address
            // specified in register pair HL.
            case 0x77: MOV(memory[registers.hl.getPairValue()], registers.a); break;
        
            // MOV A,B - Copy register B to register A
            case 0x78: MOV(registers.a, registers.b); break;

            // MOV A,C - Copy register C to register A
            case 0x79: MOV(registers.a, registers.c); break;

            // MOV A,D - Copy register D to register A
            case 0x7a: MOV(registers.a, registers.d); break;

            // MOV A,E - Copy register E to register A
            case 0x7b: MOV(registers.a, registers.e); break;

            // MOV A,H - Copy register H to register A
            case 0x7c: MOV(registers.a, registers.h); break;

            // MOV A,L - Copy register L to register A
            case 0x7d: MOV(registers.a, registers.l); break;

            // MOV A,M - In this case, register pair HL stores a memory address,
            // so copy the value at this address to the A register.
            case 0x7e: MOV(registers.a, memory[registers.hl.getPairValue()]); break;

            // MOV A,A - Copy register A to register A (state left unchanged)
            case 0x7f: MOV(registers.a, registers.a); break;

            // ADD B - Add register B to the accumulator
            case 0x80: ADD(registers.b); break; 

            // ADD C - Add register C to the accumulator
            case 0x81: ADD(registers.c); break; 

            // ADD D - Add register D to the accumulator
            case 0x82: ADD(registers.d); break; 

            // ADD E - Add register E to the accumulator
            case 0x83: ADD(registers.e); break; 

            // ADD H - Add register H to the accumulator
            case 0x84: ADD(registers.h); break; 

            // ADD L - Add register L to the accumulator
            case 0x85: ADD(registers.l); break; 

            // ADD M - Add the value at the memory address specified by register pair HL to the
            // accumulator
            case 0x86: ADD(memory[registers.hl.getPairValue()]); break;

            // ADD A - Add the accumulator to the accumulator (doubled)
            case 0x87: ADD(registers.a); break; 

            // ADC B - Add register B and the the carry bit to the accumulator
            case 0x88: ADC(registers.b); break;

            // ADC C - Add register C and the the carry bit to the accumulator
            case 0x89: ADC(registers.c); break;

            // ADC D - Add register D and the the carry bit to the accumulator
            case 0x8a: ADC(registers.d); break;

            // ADC E - Add register E and the the carry bit to the accumulator
            case 0x8b: ADC(registers.e); break;

            // ADC H - Add register H and the the carry bit to the accumulator
            case 0x8c: ADC(registers.h); break;

            // ADC L - Add register L and the the carry bit to the accumulator
            case 0x8d: ADC(registers.l); break;                        

            // ADC M - Add the value at the memory location specified by register pair HL
            // and the the carry bit to the accumulator.
            case 0x8e: ADC(memory[registers.hl.getPairValue()]); break;

            // ADC A - Add register A and the the carry bit to the accumulator
            case 0x8f: ADC(registers.a); break;

            // SUB B - Register B is subtracted from the accumulator
            case 0x90: SUB(registers.b); break;

            // SUB C - Register C is subtracted from the accumulator
            case 0x91: SUB(registers.c); break;

            // SUB D - Register D is subtracted from the accumulator
            case 0x92: SUB(registers.d); break;

            // SUB E - Register E is subtracted from the accumulator
            case 0x93: SUB(registers.e); break;

            // SUB H - Register H is subtracted from the accumulator
            case 0x94: SUB(registers.h); break;

            // SUB L - Register L is subtracted from the accumulator
            case 0x95: SUB(registers.l); break;

            // SUB M - The value at the memory address specified by the register pair HL
            // is subtracted from the accumulator
            case 0x96: SUB(memory[registers.hl.getPairValue()]); break;

            // SUB A - The accumulator is subtracted from the accumulator
            case 0x97: SUB(registers.a); break;

            // SBB B - The carry bit is added to register B. This value is then subtracted
            // from the accumulator
            case 0x98: SBB(registers.b); break;

            // SBB C - The carry bit is added to register C. This value is then subtracted
            // from the accumulator
            case 0x99: SBB(registers.c); break;

            // SBB D - The carry bit is added to register D. This value is then subtracted
            // from the accumulator
            case 0x9a: SBB(registers.d); break;

            // SBB E - The carry bit is added to register E. This value is then subtracted
            // from the accumulator
            case 0x9b: SBB(registers.e); break;

            // SBB H - The carry bit is added to register H. This value is then subtracted
            // from the accumulator
            case 0x9c: SBB(registers.h); break;

            // SBB L - The carry bit is added to register L. This value is then subtracted
            // from the accumulator
            case 0x9d: SBB(registers.l); break;

            // SBB M - The carry bit is added to the value held at the memory address
            // specified by register pair HL. This value is then subtracted from the accumulator.
            case 0x9e: SBB(memory[registers.hl.getPairValue()]); break;

            // SBB A - The carry bit is added to register A. This value is then subtracted
            // from the accumulator
            case 0x9f: SBB(registers.a); break;

            // ANA L - Bitwise and (&) operates on the accumulator with register B
            case 0xa0: ANA(registers.b); break;

            // ANA C - Bitwise and (&) operates on the accumulator with register C
            case 0xa1: ANA(registers.c); break;

            // ANA D - Bitwise and (&) operates on the accumulator with register D
            case 0xa2: ANA(registers.d); break;

            // ANA E - Bitwise and (&) operates on the accumulator with register E
            case 0xa3: ANA(registers.e); break;

            // ANA H - Bitwise and (&) operates on the accumulator with register H
            case 0xa4: ANA(registers.h); break;

            // ANA L - Bitwise and (&) operates on the accumulator with register L
            case 0xa5: ANA(registers.l); break;

            // ANA M - Bitwise and (&) operates on the accumulator with the value at 
            // the memory location specified by register pair HL.
            case 0xa6: ANA(memory[registers.hl.getPairValue()]); break;

            // ANA A - Bitwise and (&) operates on the accumulator with register A
            // (A is the same register as the accumulator), with the result
            // stored in the accumulator. The accumulator remains the same in this case,
            // with only the flags changing.
            case 0xa7: ANA(registers.a); break;

            // XRA B - Bitwise exclusive or (^) operates on the accumulator with register B.
            case 0xa8: XRA(registers.b); break;

            // XRA C - Bitwise exclusive or (^) operates on the accumulator with register C.
            case 0xa9: XRA(registers.c); break;

            // XRA D - Bitwise exclusive or (^) operates on the accumulator with register D.
            case 0xaa: XRA(registers.d); break;

            // XRA E - Bitwise exclusive or (^) operates on the accumulator with register E.
            case 0xab: XRA(registers.e); break;

            // XRA H - Bitwise exclusive or (^) operates on the accumulator with register H.
            case 0xac: XRA(registers.h); break;

            // XRA L - Bitwise exclusive or (^) operates on the accumulator with register L.
            case 0xad: XRA(registers.l); break;

            // XRA M - Bitwise exclusive or (^) operates on the accumulator with the value at the
            // memory address specified by register pair HL.
            case 0xae: XRA(memory[registers.hl.getPairValue()]); break;

            // XRA A - Bitwise exclusive or (^) operates on the accumulator with the accumulator.
            // Only the flags change in this case.
            case 0xaf: XRA(registers.a); break;

            // ORA B - Perform bitwise or (|) on the accumulator with register B.
            case 0xb0: ORA(registers.b); break;

            // ORA C - Perform bitwise or (|) on the accumulator with register C.
            case 0xb1: ORA(registers.c); break;

            // ORA D - Perform bitwise or (|) on the accumulator with register D.
            case 0xb2: ORA(registers.d); break;

            // ORA E - Perform bitwise or (|) on the accumulator with register E.
            case 0xb3: ORA(registers.e); break;

            // ORA H - Perform bitwise or (|) on the accumulator with register H.
            case 0xb4: ORA(registers.h); break;

            // ORA L - Perform bitwise or (|) on the accumulator with register L.
            case 0xb5: ORA(registers.l); break;

            // ORA M  - Perform bitwise or (|) on the accumulator with the value held at
            // the memory location specified by register pair hl.
            case 0xb6: ORA(memory[registers.hl.getPairValue()]); break;

            // ORA A - Perform bitwise or (|) on the accumulator with the accumulator. Only changes
            // flags.
            case 0xb7: ORA(registers.a); break;

            // CMP B - Register B is compared with the accumulator, changing only the flags.
            case 0xb8: CMP(registers.b); break;

            // CMP C - Register C is compared with the accumulator, changing only the flags.
            case 0xb9: CMP(registers.c); break;

            // CMP D - Register D is compared with the accumulator, changing only the flags.
            case 0xba: CMP(registers.d); break;

            // CMP E - Register E is compared with the accumulator, changing only the flags.
            case 0xbb: CMP(registers.e); break;

            // CMP H - Register H is compared with the accumulator, changing only the flags.
            case 0xbc: CMP(registers.h); break;

            // CMP L - Register L is compared with the accumulator, changing only the flags.
            case 0xbd: CMP(registers.l); break;

            // CMP M - The value held in memory at the address specified by register pair HL
            // is compared with the accumulator, changing only the flags.
            case 0xbe: CMP(memory[registers.hl.getPairValue()]); break;

            // CMP A - The accumulator is compared with the accumulator, changing only the flags.
            case 0xbf: CMP(registers.a); break;

            // RNZ - Return if not zero. If the Zero bit is not set, a return operation is performed.
            case 0xc0: RNZ(); break;

            // POP B - Remove two bytes from the top of the stack and copy their values
            // into the register pair BC
            case 0xc1: POP(registers.bc); break;

            // PUSH B - Write register pair BC to the top of the stack
            case 0xc5: PUSH(registers.bc); break;

            // RST 0 - Call an interrupt handler subroutine at the first byte in memory.
            case 0xc7: RST(0); break;

            // RZ - If the zero bit is one, a RET instruction occurs
            case 0xc8: RZ(); break;

            // RET - Return from subroutine. This works by popping the
            // address at the top of the stack into the program counter,
            // transferring program control.
            case 0xc9: RET(); break;

            // RST 1 - Call an interrupt handler subroutine at the second byte in memory.
            case 0xcf: RST(1); break;

            // RNC - If the carry bit is zero, perform a return operation
            case 0xd0: RNC(); break;

            // POP D - Remove two bytes from the top of the stack and copy their values
            // into the register pair DE
            case 0xd1: POP(registers.de); break;

            // PUSH D - Write register pair DE to the top of the stack
            case 0xd5: PUSH(registers.de); break;

            // RST 2 - Call an interrupt handler subroutine at the third byte in memory.
            case 0xd7: RST(2); break;

            // RC - If the carry bit is one, a RET instruction occurs
            case 0xd8: RC(); break;

            // RST 3 - Call an interrupt handler subroutine at the fourth byte in memory.
            case 0xdf: RST(3); break;

            // RPO - If parity bit is zero, a RET instruction occcurs
            case 0xe0: RPO(); break;

            // POP H - Remove two bytes from the top of the stack and copy their values
            // into the register pair HL
            case 0xe1: POP(registers.hl); break;

            // XTHL - The top 16 bits of the stack are exchanged with register pair HL
            case 0xe3: XTHL(); break;

            // PUSH H - Write register pair HL to the top of the stack
            case 0xe5: PUSH(registers.hl); break;

            // RST 4 - Call an interrupt handler subroutine at the fifth byte in memory.
            case 0xe7: RST(4); break;

            // RPE - If parity bit is one, a RET instruction occurs
            case 0xe8: RPE(); break;

            // PCHL - Set the program counter to the address held by register pair HL
            case 0xe9: PCHL(); break;

            // XCHG - Swap the values of register pairs DE and HL
            case 0xeb: XCHG(); break;
        
            // RST 5 - Call an interrupt handler subroutine at the sixth byte in memory.
            case 0xef: RST(5); break;

            // RP - If the sign bit is zero, a RET instrucion occurs
            case 0xf0: RP(); break;

            // POP PSW - Take the top two bytes off the stack, loading the
            // accumulator with the byte preceding the stack pointer and setting
            // the flags based on the byte at the stack pointer. This "flag byte"
            // at the stack pointer has its bits mapped to specific flags.
            case 0xf1: POP_PSW(); break;

            // DI - Disable interrupts
            case 0xf3: DI(); break;

            // PUSH PSW - Pushes the accumulator followed by the "flag byte"
            // mentioned previously onto the stack.
            case 0xf5: PUSH_PSW(); break;

            // RST 6 - Call an interrupt handler subroutine at the seventh byte in memory.
            case 0xf7: RST(6); break;

            // RM - If the sign bit is one, a RET instrucion occurs
            case 0xf8: RM(); break;

            // SPHL - Set the stack pointer to the address held by register pair HL
            case 0xf9: SPHL(); break;

            // EI - Enable interrupts
            case 0xfb: EI(); break;

            // RST 7 - Call an interrupt handler subroutine at the eighth byte in memory.
            case 0xff: RST(7); break;

            default: throw UnsupportedOpcodeException(opcode); break;
        }

        registers.programCounter++;
    }

    void Processor::NOP(){}

    void Processor::STAX(const RegisterPair& registerPair){
        memory[registerPair.getPairValue()] = registers.a;
    }

    void Processor::DCR(uint8_t& valueToDecrement){
        uint8_t result{static_cast<uint8_t>(valueToDecrement - 1)};
        uint8_t lowOrderNibbleOfValueToDecrement{extractNibble<uint8_t>(valueToDecrement, 0)};

        alterFlagsAfterMathematicalOperation(result);

        flags.auxiliaryCarry = extractBit<uint8_t> (
            twosComplementNibbleSubtraction(lowOrderNibbleOfValueToDecrement, 1), 4
        );

        valueToDecrement = result;
    }

    void Processor::DAA(){
        uint8_t leastSignificantNibbleOfAccumulator{extractNibble<uint8_t>(registers.a, 0)};

        if (flags.auxiliaryCarry || leastSignificantNibbleOfAccumulator > 9) {
            registers.a += 6; // Increase the low order nibble by six. Creates a carry.
            flags.auxiliaryCarry = true; // Apply the carry.
        }
        
        uint8_t mostSignificantNibbleOfAccumulator{extractNibble<uint8_t>(registers.a, 1)};

        if (flags.carry || mostSignificantNibbleOfAccumulator > 9) {
            registers.a += 0x60; // Increase the high order nibble by six. Creates a carry.
            flags.carry = true; // Apply the carry
        }

        alterFlagsAfterMathematicalOperation(registers.a);
    }

    void Processor::CMA(){
        registers.a = ~registers.a;
    }

    void Processor::RLC(){
        // The carry bit is set to bit 7 of the accumulator, the
        // accumulator is shifted one position left and then bit 0
        // of the accumulator is set to the same value as the carry bit.
        flags.carry = extractBit<uint8_t>(registers.a, 7);
        registers.a <<= 1;
        setBitValue<uint8_t>(registers.a, 0, flags.carry);
    }

    void Processor::DAD(const RegisterPair& registerPair){
        // Use 32 bits to facilitate carry
        uint32_t result{static_cast<uint32_t>(
            registers.hl.getPairValue() + registerPair.getPairValue()
        )};

        // The first 16 bits will be assigned to register pair HL. This ignores the carry bit.
        registers.hl.setPairValue(result);
        
        // Bit 16 is set if a carry has occurred
        flags.carry = extractBit<uint32_t>(result, 16);
    }

    void Processor::DCX(const RegisterPair& registerPair){
        if (registerPair.secondRegister == 0){
            registerPair.secondRegister = 0xff;
            registerPair.firstRegister--;
        }
        else {
            registerPair.secondRegister--;
        }
    }

    void Processor::DCX_SP(){
        registers.stackPointer--;
    }

    void Processor::CMC(){
        flags.carry = !flags.carry;
    }

    void Processor::RRC(){
        // Set's the carry to bit 0 of register A (accumulator),
        // shifts one position to the right and then sets
        // bit 7 of register A to the value of the carry.
        flags.carry = registers.a & 1;
        registers.a >>= 1;
        registers.a |= flags.carry << 7;
    }

    void Processor::RAR(){
        // Save bit 0 of the accumulator and then shift the accumulator one position
        // to the right. Set bit 7 of the accumulator to the value of the carry bit
        // and then set the carry bit to the saved first bit of the accumulator in its
        // original state.
        bool firstBitOfAccumulator{extractBit<uint16_t>(registers.a, 0)};
        registers.a >>= 1;
        setBitValue<uint8_t>(registers.a, 7, flags.carry);
        flags.carry = firstBitOfAccumulator;
    }

    void Processor::RAL(){
        // Save bit 7 of the accumulator and then shift the accumulator one position
        // to the left. Set bit 0 of the accumulator to the value of the carry bit
        // and then set the carry bit to the saved last bit of the accumulator in its
        // original state.
        bool lastBitOfAccumulator{extractBit<uint16_t>(registers.a, 7)};
        registers.a <<= 1;
        setBitValue<uint8_t>(registers.a, 0, flags.carry);
        flags.carry = lastBitOfAccumulator;
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

    void Processor::INX_SP(){
        registers.stackPointer++;
    }

    void Processor::INR(uint8_t& valueToIncrement){
        uint8_t result{static_cast<uint8_t>(valueToIncrement + 1)};
        uint8_t lowOrderNibbleOfValueToIncrement{extractNibble<uint8_t>(valueToIncrement, 0)};

        alterFlagsAfterMathematicalOperation(result);
        flags.auxiliaryCarry = (lowOrderNibbleOfValueToIncrement + 1) > 0xf;

        valueToIncrement = result;
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

    void Processor::ADD(uint8_t valueToAddToAccumulator){
        uint16_t result{static_cast<uint16_t>(registers.a + valueToAddToAccumulator)};
        uint8_t lowOrderByteOfResult{extractByte<uint16_t>(result, 0)};
        uint8_t lowOrderNibbleOfAccumulator{extractNibble<uint8_t>(registers.a, 0)};
        uint8_t lowOrderNibbleOfValueToAdd{extractNibble<uint8_t>(valueToAddToAccumulator, 0)};
        
        uint8_t sumOfLowOrderNibbles {
            static_cast<uint8_t>(lowOrderNibbleOfAccumulator + lowOrderNibbleOfValueToAdd)
        };

        alterFlagsAfterMathematicalOperation(result);
        
        flags.carry = extractBit<uint16_t>(result, 8);
        flags.auxiliaryCarry = extractBit<uint8_t>(sumOfLowOrderNibbles, 4);

        registers.a = lowOrderByteOfResult;
    }

    void Processor::ADC(uint8_t valueToAddToAccumulator){
        ADD(valueToAddToAccumulator + flags.carry);
    }

    void Processor::SUB(uint8_t valueToSubtractFromAccumulator){
        uint16_t result{twosComplementByteSubtraction(registers.a, valueToSubtractFromAccumulator)};
        uint8_t lowOrderByteOfResult{extractByte<uint16_t>(result, 0)};
        uint8_t lowOrderNibbleOfAccumulator{extractNibble<uint8_t>(registers.a, 0)};
        uint8_t lowOrderNibbleOfValueToSubtract {
            extractNibble<uint8_t>(valueToSubtractFromAccumulator, 0)
        };

        alterFlagsAfterMathematicalOperation(lowOrderByteOfResult);
        
        flags.carry = !extractBit<uint16_t>(result, 8);
        flags.auxiliaryCarry = extractBit<uint8_t>(
            twosComplementNibbleSubtraction(
                lowOrderNibbleOfAccumulator,
                lowOrderNibbleOfValueToSubtract
            ), 4
        );

        registers.a = lowOrderByteOfResult;
    }

    void Processor::SBB(uint8_t valueToSubtractFromAccumulator){
        SUB(valueToSubtractFromAccumulator + flags.carry);
    }

    void Processor::ANA(uint8_t registerForBitwiseAnd){
        registers.a &= registerForBitwiseAnd;
        alterFlagsAfterLogicalOperation();
    }

    void Processor::XRA(uint8_t registerForBitwiseXor){
        registers.a ^= registerForBitwiseXor;
        alterFlagsAfterLogicalOperation();
    }

    void Processor::ORA(uint8_t valueForBitwiseOr){
        registers.a |= valueForBitwiseOr;
        alterFlagsAfterLogicalOperation();
    }

    void Processor::CMP(uint8_t valueToCompare){
        uint8_t lowOrderNibbleOfAccumulator{extractNibble<uint8_t>(registers.a, 0)};
        uint8_t lowOrderNibbleOfValueToCompare{extractNibble<uint8_t>(valueToCompare, 0)};

        uint16_t result{twosComplementByteSubtraction(registers.a, valueToCompare)};
        uint8_t firstByteOfResult{extractByte<uint16_t>(result, 0)};

        alterFlagsAfterMathematicalOperation(firstByteOfResult);

        flags.carry = !extractBit<uint16_t>(result, 8);
        flags.auxiliaryCarry = extractBit<uint8_t>(
            twosComplementNibbleSubtraction(
                lowOrderNibbleOfAccumulator,
                lowOrderNibbleOfValueToCompare
            ), 4
        );
    }

    void Processor::RNZ(){
        if (!flags.zero) RET();
    }

    void Processor::RST(int interruptHandlerNumber){
        // Set the program counter to the address of the specified interrupt handler.
        // Each interrupt handler occupies eight bytes of memory.
        CALL(interruptHandlerNumber * 8);
    }

    void Processor::POP(RegisterPair& registerPair){
        // The top of the stack descends through memory. i.e a POP operation will
        // result with the stack pointer being at a higher address, and vice versa for PUSH.
        // Note that we aren't actually erasing the previous stack data
        // after we copy it to the register pair, we just move the stack pointer.
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
        setBitValue<uint8_t>(flagByte, 7, flags.sign);
        setBitValue<uint8_t>(flagByte, 6, flags.zero);
        setBitValue<uint8_t>(flagByte, 5, 0);
        setBitValue<uint8_t>(flagByte, 4, flags.auxiliaryCarry);
        setBitValue<uint8_t>(flagByte, 3, 0);
        setBitValue<uint8_t>(flagByte, 2, flags.parity);
        setBitValue<uint8_t>(flagByte, 1, 1);
        setBitValue<uint8_t>(flagByte, 0, flags.carry);

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

    void Processor::RNC(){
        if (!flags.carry) RET();
    }

    void Processor::RC(){
        if (flags.carry) RET();
    }

    void Processor::RPO(){
        if (!flags.parity) RET();
    }

    void Processor::RPE(){
        if (!flags.parity) RET();
    }

    void Processor::RP(){
        if (!flags.sign) RET();
    }

    void Processor::RM(){
        if (flags.sign) RET();
    }

    void Processor::XTHL(){
        std::swap(registers.h, memory[registers.stackPointer+1]);
        std::swap(registers.l, memory[registers.stackPointer]);
    }

    void Processor::PCHL(){
        registers.programCounter = registers.hl.getPairValue();
        registers.programCounter--; // Prevent automatic increment
    }

    void Processor::SPHL(){
        registers.stackPointer = registers.hl.getPairValue();
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

    void Processor::DI(){
        interruptEnable = false;
    }
}