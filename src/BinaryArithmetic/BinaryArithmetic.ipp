#include <cstdint>

namespace BinaryArithmetic {
    // Return type U must be at least twice the bits in type T.
    // I.e, two uint8_t numbers can be concatenated to make a uint16_t number
    template <typename T, typename U>
    U concatenateTwoNumbers(T first, T second){
        int numberOfBitsInTypeT{sizeof(first) * 8};

        // Load in "first", shift the bits left by the number of bits in type T to make room for "second"
        // and then load in "second" to the reserved space.
        return ((U() | first) << numberOfBitsInTypeT) | second;
    }

    template <typename T>
    uint8_t extractByte(T number, int byteIndex){
        int bitsInFrontOfTheByte{byteIndex * 8};

        // Create a number in which the bits at the byte index are set to 1,
        // allowing us to extract this byte from "number". Then shift out the
        // trailing bits to achieve a single byte result.
        return (number & (0xff << bitsInFrontOfTheByte)) >> bitsInFrontOfTheByte;
    }
}