#ifndef BINARY_OPERATIONS_HPP
#define BINARY_OPERATIONS_HPP

#include <cstdint>
#include "BinaryOperations.ipp"

bool isThereAnEvenNumberOfBitsSetInByte(uint8_t number);
uint16_t twosComplementByteSubtraction(uint8_t minuend, uint8_t subtrahend);
uint8_t twosComplementNibbleSubtraction(uint8_t minuend, uint8_t subtrahend);

#endif