#ifndef BINARY_OPERATIONS_IPP
#define BINARY_OPERATIONS_IPP

#include <cstdint>
#include <stdexcept>

template <typename T, typename U>
U concatenateTwoNumbers(T firstNumber, T secondNumber);

template <typename T>
bool extractBit(T number, int bitIndex);

template <typename T>
uint8_t extractNibble(T number, int nibbleIndex);

template <typename T>
uint8_t extractByte(T number, int byteIndex);

template <typename T>
void setBitValue(T& number, int bitIndex, bool value);

template <typename T>
bool isBitIndexWithinTheCapacityOfTheType(int bitIndex);

template <typename T>
bool isNibbleIndexWithinTheCapacityOfTheType(int nibbleIndex);

template <typename T>
bool isByteIndexWithinTheCapacityOfTheType(int byteIndex);

// Return type U must have at least twice the bits type T has.
// i.e, two uint8_t numbers can be concatenated to make a uint16_t number
template <typename T, typename U>
U concatenateTwoNumbers(T firstNumber, T secondNumber){
    int numberOfBitsInTypeT{sizeof(T) * 8};
    int numberOfBitsInTypeU{sizeof(U) * 8};
    bool isTypeULargeEnoughForConcatenation{(numberOfBitsInTypeT * 2) <= numberOfBitsInTypeU};

    if (isTypeULargeEnoughForConcatenation){
        // Load in "firstNumber", shift the bits left by the number of bits in type T to make
        // room for "secondNumber" and then load in "secondNumber" to the reserved space.
        return ((U{} | firstNumber) << numberOfBitsInTypeT) | secondNumber;
    }
    else {
        throw std::invalid_argument{"Type U must have at least 2x capacity of type T."};
    }
}

template <typename T>
bool extractBit(T number, int bitIndex){
    if (isBitIndexWithinTheCapacityOfTheType<T>(bitIndex)){
        return number & (1 << bitIndex);
    }
    else {
        throw std::out_of_range{"Bit at specified index is outside the range of type T."};
    }
}

template <typename T>
uint8_t extractNibble(T number, int nibbleIndex){
    if (isNibbleIndexWithinTheCapacityOfTheType<T>(nibbleIndex)){
        int bitsInFrontOfTheNibble{nibbleIndex * 4};

        // Create a number in which the bits at the nibble index are set to 1,
        // allowing us to extract this nibble from "number". Then shift out the
        // trailing bits to achieve a single nibble result.
        return (number & (0xf << bitsInFrontOfTheNibble)) >> bitsInFrontOfTheNibble;
    }
    else {
        throw std::out_of_range{"Nibble at specified index is outside the range of type T."};
    }
}


template <typename T>
uint8_t extractByte(T number, int byteIndex){
    if (isByteIndexWithinTheCapacityOfTheType<T>(byteIndex)){
        int bitsInFrontOfTheByte{byteIndex * 8};

        // Create a number in which the bits at the byte index are set to 1,
        // allowing us to extract this byte from "number". Then shift out the
        // trailing bits to achieve a single byte result.
        return (number & (0xff << bitsInFrontOfTheByte)) >> bitsInFrontOfTheByte;
    }
    else {
        throw std::out_of_range{"Byte at specified index is outside the range of type T."};
    }
}

template <typename T>
void setBitValue(T& number, int bitIndex, bool value){
    if (isBitIndexWithinTheCapacityOfTheType<T>(bitIndex)){
        if (value){
            number |= 1 << bitIndex; // Set bit
        }
        else {
            number &= ~(1 << bitIndex); // Clear bit
        }
    }
    else {
        throw std::out_of_range{"Bit at specified index is outside the range of type T."};
    }
}

template <typename T>
bool isBitIndexWithinTheCapacityOfTheType(int bitIndex){
    bool indexIsPositive{bitIndex >= 0};
    int numberOfBitsWithinType{sizeof(T) * 8};

    return indexIsPositive && bitIndex < numberOfBitsWithinType;
}

template <typename T>
bool isNibbleIndexWithinTheCapacityOfTheType(int nibbleIndex){
    bool indexIsPositive{nibbleIndex >= 0};
    int numberOfNibblesWithinType{sizeof(T) * 2};

    return indexIsPositive && nibbleIndex < numberOfNibblesWithinType;
}

template <typename T>
bool isByteIndexWithinTheCapacityOfTheType(int byteIndex){
    bool indexIsPositive{byteIndex >= 0};
    int numberOfBytesWithinType{sizeof(T)};

    return indexIsPositive && byteIndex < numberOfBytesWithinType;
}

#endif