#ifndef IS_DEVICE_ATTACHED_TO_PORT_HPP
#define IS_DEVICE_ATTACHED_TO_PORT_HPP

#include <vector>
#include <cstdint>

namespace Intel8080 {
    bool isDeviceAttachedToPort(const std::vector<uint8_t>& portNumbers, uint8_t portNumber);
}

#endif