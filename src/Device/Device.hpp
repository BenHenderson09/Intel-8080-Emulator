#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vector>
#include <cstdint>

namespace Intel8080 {
    // Tagging interface for external IO devices
    class Device {
        public:
            virtual ~Device(){};
    };
};

#endif