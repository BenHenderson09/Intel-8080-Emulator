#include <cstdint>
#include <stdexcept>
#include "BinaryOperations.hpp"

bool isThereAnEvenNumberOfBitsSet(int number){ 
    int numberOfBitsSet{0};

    while (number > 0){
        bool firstBitOfNumberIsSet{number & 1};

        if (firstBitOfNumberIsSet) numberOfBitsSet++;
        number >>= 1; // Remove the first bit of the binary number
    }

    return numberOfBitsSet % 2 == 0;
}

uint16_t twosComplementByteSubtraction(uint8_t minuend, uint8_t subtrahend){
    return minuend + (~subtrahend & 0xff) + 1;
}

uint8_t twosComplementNibbleSubtraction(uint8_t minuend, uint8_t subtrahend){
    bool areBothOperandsNibbles{extractNibble<uint8_t>(minuend | subtrahend, 1) == 0};

    if (areBothOperandsNibbles){
        return minuend + (~subtrahend & 0xf) + 1;
    }
    else {
        throw std::invalid_argument{"Nibble subtraction must have nibbles as operands."};
    }
}