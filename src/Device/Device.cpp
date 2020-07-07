#include "Device.hpp"

namespace Intel8080 {
    Device::Device(const std::initializer_list<uint8_t>& portNumbers) : portNumbers{portNumbers}{}
}