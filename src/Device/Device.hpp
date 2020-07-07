#ifndef DEVICE
#define DEVICE

#include <vector>
#include <cstdint>

namespace Intel8080 {
    class Device {
        public:
            Device(const std::initializer_list<uint8_t>& portNumbers);
            virtual ~Device(){};

            const std::vector<uint8_t>& portNumbers;
    };
};

#endif