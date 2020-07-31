#include <cstdint>
#include <stdexcept>
#include "BinaryOperations.hpp"

bool isThereAnEvenCountOfOnes(int number){ 
    int countOfOnesInBinaryNumber{0};

    while (number > 0){
        bool firstBitOfBinaryNumberIsEqualToOne{number & 1};

        if (firstBitOfBinaryNumberIsEqualToOne) countOfOnesInBinaryNumber++;
        number >>= 1; // Remove the first bit of the binary number
    }

    return countOfOnesInBinaryNumber % 2 == 0;
}

uint16_t twosComplementByteSubtraction(uint8_t minuend, uint8_t subtrahend){
    return minuend + (~subtrahend & 0xff) + 1;

}

uint8_t twosComplementNibbleSubtraction(uint8_t minuend, uint8_t subtrahend){
    if (extractNibble<uint8_t>(minuend | subtrahend, 1) == 0){
        return minuend + (~subtrahend & 0xf) + 1;
    }
    else {
        throw std::invalid_argument{"Nibble subtraction must have nibbles as operands."};
    }
}