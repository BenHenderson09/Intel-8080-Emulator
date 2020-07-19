#ifndef IS_DEVICE_ATTACHED_TO_PORT_HPP
#define IS_DEVICE_ATTACHED_TO_PORT_HPP

#include <vector>
#include <cstdint>
#include "isValuePresentInVector.ipp"

namespace Intel8080 {
    template <typename T>
    bool isValuePresentInVector(const std::vector<T>& vector, T value);
}

#endif