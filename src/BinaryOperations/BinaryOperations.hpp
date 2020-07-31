#ifndef BINARY_OPERATIONS_HPP
#define BINARY_OPERATIONS_HPP

#include <cstdint>
#include "BinaryOperations.ipp"

bool isThereAnEvenCountOfOnes(int number);
uint16_t twosComplementByteSubtraction(uint8_t minuend, uint8_t subtrahend);
uint8_t twosComplementNibbleSubtraction(uint8_t minuend, uint8_t subtrahend);

template <typename T, typename U>
U concatenateTwoNumbers(T first, T second);

template <typename T>
bool extractBit(T number, int bitIndex);

template <typename T>
uint8_t extractNibble(T number, int nibbleIndex);

template <typename T>
uint8_t extractByte(T number, int byteIndex);

template <typename T>
void setBit(T& number, int bitIndex, bool value);

#endif