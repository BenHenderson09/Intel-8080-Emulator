#include "BinaryArithmetic.hpp"

bool isThereAnEvenCountOfOnes(int number){ 
    int countOfOnesInBinaryNumber{0};

    while (number > 0){
        bool firstBitOfBinaryNumberIsEqualToOne{number & 1};

        if (firstBitOfBinaryNumberIsEqualToOne) countOfOnesInBinaryNumber++;
        number >>= 1; // Remove the first bit of the binary number
    }

    return countOfOnesInBinaryNumber % 2 == 0;
}

uint16_t twosComplementEightBitSubtraction(uint8_t minuend, uint8_t subtrahend){
    uint16_t resultOfSubtraction{uint16_t(minuend + (~subtrahend & 0xff) + 1)};

    if (extractBit<uint16_t>(resultOfSubtraction, 8)){ // If there's a carry, the result is positive
        return resultOfSubtraction;
    }
    else { // If negative, convert the result to two's complement
        return (~resultOfSubtraction & 0xff) + 1;
    }
}

uint8_t twosComplementFourBitSubtraction(uint8_t minuend, uint8_t subtrahend){
    if (extractNibble<uint8_t>(minuend | subtrahend, 1) == 0){
        uint8_t resultOfSubtraction{uint8_t(minuend + (~subtrahend & 0xf) + 1)};

        if (extractBit<uint8_t>(resultOfSubtraction, 4)){ // If there's a carry, the result is positive
            return resultOfSubtraction;
        }
        else { // If negative, convert the result to two's complement
            return (~resultOfSubtraction & 0xf) + 1;
        }
    }
    else {
        throw std::runtime_error("Four bit subtraction must have 4 bit operands.");
    }
}