#ifndef HARDWARE_SPECIFICATIONS
#define HARDWARE_SPECIFICATIONS

namespace HardwareSpecifications {
    // the 16 bit address bus supports 2^16 memory addresses, each of which having a
    // one byte capacity, therefore a maximum 64 KiB of memory is supported.
    const int sizeOfMemoryInBytes{65535};
}

#endif