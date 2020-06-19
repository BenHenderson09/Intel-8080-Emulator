#include <cstdint>
#include <stdexcept>
#include <iostream>

// Return type U must have at least twice the bits type T has.
// I.e, two uint8_t numbers can be concatenated to make a uint16_t number
template <typename T, typename U>
U concatenateTwoNumbers(T first, T second){
    int numberOfBitsInTypeT{sizeof(T) * 8};
    int numberOfBitsInTypeU{sizeof(U) * 8};

    if ((numberOfBitsInTypeT * 2) <= numberOfBitsInTypeU){
        // Load in "first", shift the bits left by the number of bits in
        // type T to make room for "second" and then load in "second" to the reserved space.
        return ((U() | first) << numberOfBitsInTypeT) | second;
    }
    else {
        throw std::invalid_argument("Type U must have at least 2x capacity of type T.");
    }
}

template <typename T>
bool extractBit(T number, int bitIndex){
    bool bitExists{bitIndex >= 0 && (sizeof(T) * 8) >= (bitIndex + 1)};

    if (bitExists){
        return (number & (1 << bitIndex)) != 0;
    }
    else {
        throw std::invalid_argument("Bit at specified index doesn't exist.");
    }
}

template <typename T>
uint8_t extractByte(T number, int byteIndex){
    bool byteExists{byteIndex >= 0 && sizeof(T) >= (byteIndex + 1)};

    if (byteExists){
        int bitsInFrontOfTheByte{byteIndex * 8};

        // Create a number in which the bits at the byte index are set to 1,
        // allowing us to extract this byte from "number". Then shift out the
        // trailing bits to achieve a single byte result.
        return (number & (0xff << bitsInFrontOfTheByte)) >> bitsInFrontOfTheByte;
    }
    else {
        throw std::invalid_argument("Byte at specified index doesn't exist.");
    }
}

template <typename T>
void setBit(T& number, int bitIndex, bool value){
    bool bitExists{bitIndex >= 0 && (sizeof(T) * 8) >= (bitIndex + 1)};

    if (bitExists){
        if (value){
            number |= 1 << bitIndex; // Set bit
        }
        else {
            number &= ~(1 << bitIndex); // Clear bit
        }
    }
    else {
        throw std::invalid_argument("Bit at specified index doesn't exist.");
    }
}