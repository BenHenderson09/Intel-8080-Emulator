#ifndef BINARY_ARITHMETIC_HPP
#define BINARY_ARITHMETIC_HPP

#include <cstdint>
#include "BinaryArithmetic.ipp"

bool isThereAnEvenCountOfOnes(int number);

template <typename T, typename U>
U concatenateTwoNumbers(T first, T second);

template <typename T>
bool extractBit(T number, int bitIndex);

template <typename T>
uint8_t extractByte(T number, int byteIndex);

#endif