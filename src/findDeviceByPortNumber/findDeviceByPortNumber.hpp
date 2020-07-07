#ifndef FIND_DEVICE_BY_PORT_NUMBER
#define FIND_DEVICE_BY_PORT_NUMBER

#include <cstdint>
#include <vector>
#include "../Device/Device.hpp"

namespace Intel8080 {
    Device* findDeviceByPortNumber(const std::vector<Device*> devices, uint8_t portNumber);
}

#endif