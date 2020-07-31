#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include "Processor.hpp"
#include "../UnsupportedOpcodeException/UnsupportedOpcodeException.hpp"
#include "../BinaryOperations/BinaryOperations.hpp"
#include "../InputDevice/InputDevice.hpp"
#include "../OutputDevice/OutputDevice.hpp"
#include "../isValuePresentInVector/isValuePresentInVector.hpp"

namespace Intel8080 {
    void Processor::executeTwoByteInstruction(uint8_t opcode, uint8_t firstByteFollowingOpcode){
        switch (opcode){
            // MVI B - Move immediate data to register B
            case 0x06: MVI(registers.b, firstByteFollowingOpcode); break;
            
            // MVI C - Move immediate data to register C
            case 0x0e: MVI(registers.c, firstByteFollowingOpcode); break;

            // MVI D - Move immediate data to register D
            case 0x16: MVI(registers.d, firstByteFollowingOpcode); break;

            // MVI E - Move immediate data to register E
            case 0x1e: MVI(registers.e, firstByteFollowingOpcode); break;

            // MVI H - Move immediate data to register H
            case 0x26: MVI(registers.h, firstByteFollowingOpcode); break;

            // MVI L - Move immediate data to register L
            case 0x2e: MVI(registers.l, firstByteFollowingOpcode); break;

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
            case 0xd3: OUT(firstByteFollowingOpcode); break;

            // SUI - The byte of immediate data is subtracted from the accumulator
            case 0xd6: SUI(firstByteFollowingOpcode); break;

            // IN - An input device writes a byte to the accumulator.
            case 0xdb: IN(firstByteFollowingOpcode); break;

            // SBI - The byte of immediate data and the carry bit are subtracted from the accumulator.
            case 0xde: SBI(firstByteFollowingOpcode); break;

            // ANI - Perform a bitwise and (&) with the immediate data and the accumulator,
            // storing the result in the accumulator
            case 0xe6: ANI(firstByteFollowingOpcode); break;
        
            // CPI - Compare the immediate data with the contents of the accumulator.
            // This is done internally by subtracting the data from the accumulator contents and
            // setting the flags as appropriate without actually changing the value held in the accumulator
            // after the operation has finished. I.e Only the flags change. For example, you could use the zero
            // flag to test for equality.
            case 0xfe: CPI(firstByteFollowingOpcode); break;

            // ORI - A bitwise or is carried out with the byte of immediate data and the accumulator
            case 0xf6: ORI(firstByteFollowingOpcode); break;

            default: throw UnsupportedOpcodeException(opcode);
        }

        registers.programCounter += 2;
    }

    void Processor::MVI(uint8_t& destination, uint8_t data){
        destination = data;
    }

    void Processor::ADI(uint8_t addend){
        ADD(addend);
    }
    
    void Processor::OUT(uint8_t portNumber){
        for (OutputDevice* device : outputDevices){
            if (isValuePresentInVector(device->outputPortNumbers, portNumber)){
                device->writeByte(portNumber, registers.a);
            }
        }
    }

    void Processor::SUI(uint8_t valueToSubtractFromAccumulator){
        SUB(valueToSubtractFromAccumulator);
    }

    void Processor::IN(uint8_t portNumber){
        for (InputDevice* device : inputDevices){
            if (isValuePresentInVector(device->inputPortNumbers, portNumber)){
                registers.a = device->readByte(portNumber, registers.a);
            }
        }
    }

    void Processor::SBI(uint8_t valueToSubtractFromAccumulator){
        SUB(valueToSubtractFromAccumulator + flags.carry);
    }

    void Processor::ANI(uint8_t valueForBitwiseAnd){
        registers.a &= valueForBitwiseAnd;
        alterFlagsAfterLogicalOperation();
    }

    void Processor::CPI(uint8_t dataToCompare){
        CMP(dataToCompare);
    }

    void Processor::ORI(uint8_t valueForBitwiseOr){
        registers.a |= valueForBitwiseOr;

        flags.carry = 0;
        flags.sign = extractBit<uint8_t>(registers.a, 7);
        flags.zero = registers.a == 0;
        flags.parity = isThereAnEvenCountOfOnes(registers.a);
    }
}