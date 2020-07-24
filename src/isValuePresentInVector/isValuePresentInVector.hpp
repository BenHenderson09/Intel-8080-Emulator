#ifndef IS_VALUE_PRESENT_IN_VECTOR_HPP
#define IS_VALUE_PRESENT_IN_VECTOR_HPP

#include <vector>
#include <cstdint>
#include "isValuePresentInVector.ipp"

namespace Intel8080 {
    template <typename T>
    bool isValuePresentInVector(const std::vector<T>& vector, T value);
}

#endif