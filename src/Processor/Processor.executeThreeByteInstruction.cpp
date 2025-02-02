#include <cstdint>
#include <stdexcept>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryOperations/BinaryOperations.hpp"

namespace Intel8080 {
    void Processor::executeThreeByteInstruction(uint8_t firstOperand, uint8_t secondOperand){
        // The 8080 orders the operands with the least significant
        // byte coming first (little endian). Here we convert those bytes to a 16 bit
        // value to make it easier to work with for addresses.
        uint16_t address {
            concatenateTwoNumbers<uint8_t, uint16_t>(
                secondOperand, // High order byte (most significant)
                firstOperand   // Low order byte (least significant)
            )
        };

        uint8_t opcode{getNextOpcode()};

        switch (opcode){
            // LXI B - Occupy register pair BC with the operands
            case 0x01: LXI(registers.bc, firstOperand, secondOperand); break;

            // LXI D - Occupy register pair DE with the operands
            case 0x11: LXI(registers.de, firstOperand, secondOperand); break;

            // LXI H - Occupy register pair HL  with the operands
            case 0x21: LXI(registers.hl, firstOperand, secondOperand); break;

            // SHLD - The specified memory location will be set to the value
            // of the L register and the memory location above this is set to the H register
            case 0x22: SHLD(address); break;

            // LHLD - The L register is set to the value at the specified memory address and
            // the H register is set to the value at the memory address one place above. 
            case 0x2a: LHLD(address); break;

            // LXI SP - Set the stack pointer to the address
            case 0x31: LXI_SP(address); break;

            // STA - Copy the contents of the accumulator to the specified memory address
            case 0x32: STA(address); break;

            // LDA - Copy the value at the specified memory address to the accumulator 
            case 0x3a: LDA(address); break;
            
            // JNZ - Jump to the specified memory address if the zero flag is not set
            case 0xc2: JNZ(address); break;

            // JMP - Jump to the specified memory address
            case 0xc3: JMP(address); break;

            // CNZ - If the zero flag is set, a CALL operation is performed at the specified
            // address 
            case 0xc4: CNZ(address); break;

            // JZ - Carry out a jump operation if the zero flag is set
            case 0xca: JZ(address); break;

            // CZ - Carry out a call operation if the zero flag is set
            case 0xcc: CZ(address); break;

            // CALL - A subroutine is called by jumping to the specified memory address.
            // Also, a return address is pushed onto the stack for use with the RETURN instruction
            // when the subroutine finishes.
            case 0xcd: CALL(address); break;

            // JNC - Jump if the carry flag is not set
            case 0xd2: JNC(address); break;

            // CNC - If the carry flag is not set, perform a call operation
            case 0xd4: CNC(address); break;

            // JC - Jump to the specified memory address if the carry flag is set.
            case 0xda: JC(address); break;

            // CC - If the carry flag is set, perform a call operation
            case 0xdc: CC(address); break;
            
            // JPO - If parity flag is not set, carry out a jump operation
            case 0xe2: JPO(address); break;

            // CPO - If parity flag is not set, carry out a call operation
            case 0xe4: CPO(address); break;

            // JPE - If parity flag is set, carry out a jump operation
            case 0xea: JPE(address); break;

            // CPE - If parity flag is set, carry out a call operation
            case 0xec: CPE(address); break;

            // JP - Carry out a jump operation if the sign flag is not set
            case 0xf2: JP(address); break;

            // CP - Carry out a call operation if the sign flag is not set
            case 0xf4: CP(address); break;

            // JM - Carry out a jump operation if the sign flag is set
            case 0xfa: JM(address); break;

            // CM - Carry out a call operation if the sign flag is set
            case 0xfc: CM(address); break;

            default: throw UnsupportedOpcodeException(opcode); break;
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

    void Processor::SHLD(uint16_t address){
        memory[address] = registers.l;
        memory[address + 1] = registers.h;
    }

    void Processor::LHLD(uint16_t address){
        registers.l = memory[address];
        registers.h = memory[address + 1];
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
        
        // Prevent from advancing to the next instruction automatically,
        // as JMP is a way of choosing the next instruction manually.
        registers.programCounter -= 3;
    }

    void Processor::CNZ(uint16_t address){
        if (!flags.zero) CALL(address);
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

    void Processor::CZ(uint16_t address){
        if (flags.zero) CALL(address);
    }

    void Processor::JNC(uint16_t address){
        if (!flags.carry) JMP(address);
    }

    void Processor::CNC(uint16_t address){
        if (!flags.carry) CALL(address);
    }

    void Processor::CC(uint16_t address){
        if (flags.carry) CALL(address);
    }

    void Processor::JC(uint16_t address){
        if (flags.carry) JMP(address);
    }

    void Processor::JPO(uint16_t address){
        if (!flags.parity) JMP(address);
    }

    void Processor::JPE(uint16_t address){
        if (flags.parity) JMP(address);
    }

    void Processor::CPO(uint16_t address){
        if (!flags.parity) CALL(address);
    }

    void Processor::CPE(uint16_t address){
        if (flags.parity) CALL(address);
    }

    void Processor::JM(uint16_t address){
        if (flags.sign) JMP(address);
    }

    void Processor::JP(uint16_t address){
        if (!flags.sign) JMP(address);
    }

    void Processor::CM(uint16_t address){
        if (flags.sign) CALL(address);
    }

    void Processor::CP(uint16_t address){
        if (!flags.sign) CALL(address);
    }
}