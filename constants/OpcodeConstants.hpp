#ifndef OPCODE_CONSTANTS_HPP
#define OPCODE_CONSTANTS_HPP

#include <cstdint>
#include <map>

namespace OpcodeConstants {
    const std::map<uint8_t, int> bytesUsedByOpcodes {
        { 0x00, 1},
        { 0x02, 1},
        { 0x03, 1},
        { 0x04, 1},
        { 0x05, 1},
        { 0x07, 1},
        { 0x09, 1},
        { 0x0a, 1},
        { 0x0b, 1},
        { 0x0c, 1},
        { 0x0d, 1},
        { 0x0f, 1},
        { 0x12, 1},
        { 0x13, 1},
        { 0x14, 1},
        { 0x15, 1},
        { 0x17, 1},
        { 0x19, 1},
        { 0x1a, 1},
        { 0x1b, 1},
        { 0x1c, 1},
        { 0x1d, 1},
        { 0x1f, 1},
        { 0x23, 1},
        { 0x24, 1},
        { 0x25, 1},
        { 0x27, 1},
        { 0x29, 1},
        { 0x2b, 1},
        { 0x2c, 1},
        { 0x2d, 1},
        { 0x2f, 1},
        { 0x33, 1},
        { 0x34, 1},
        { 0x35, 1},
        { 0x37, 1},
        { 0x39, 1},
        { 0x3b, 1},
        { 0x3c, 1},
        { 0x3d, 1},
        { 0x3f, 1},
        { 0x40, 1},
        { 0x41, 1},
        { 0x42, 1},
        { 0x43, 1},
        { 0x44, 1},
        { 0x45, 1},
        { 0x46, 1},
        { 0x47, 1},
        { 0x48, 1},
        { 0x49, 1},
        { 0x4a, 1},
        { 0x4b, 1},
        { 0x4c, 1},
        { 0x4d, 1},
        { 0x4e, 1},
        { 0x4f, 1},
        { 0x50, 1},
        { 0x51, 1},
        { 0x52, 1},
        { 0x53, 1},
        { 0x54, 1},
        { 0x55, 1},
        { 0x56, 1},
        { 0x57, 1},
        { 0x58, 1},
        { 0x59, 1},
        { 0x5a, 1},
        { 0x5b, 1},
        { 0x5c, 1},
        { 0x5d, 1},
        { 0x5e, 1},
        { 0x5f, 1},
        { 0x60, 1},
        { 0x61, 1},
        { 0x62, 1},
        { 0x63, 1},
        { 0x64, 1},
        { 0x65, 1},
        { 0x66, 1},
        { 0x67, 1},
        { 0x68, 1},
        { 0x69, 1},
        { 0x6a, 1},
        { 0x6b, 1},
        { 0x6c, 1},
        { 0x6d, 1},
        { 0x6e, 1},
        { 0x6f, 1},
        { 0x70, 1},
        { 0x71, 1},
        { 0x72, 1},
        { 0x73, 1},
        { 0x74, 1},
        { 0x75, 1},
        { 0x76, 1},
        { 0x77, 1},
        { 0x78, 1},
        { 0x79, 1},
        { 0x7a, 1},
        { 0x7b, 1},
        { 0x7c, 1},
        { 0x7d, 1},
        { 0x7e, 1},
        { 0x7f, 1},
        { 0x80, 1},
        { 0x81, 1},
        { 0x82, 1},
        { 0x83, 1},
        { 0x84, 1},
        { 0x85, 1},
        { 0x86, 1},
        { 0x87, 1},
        { 0x88, 1},
        { 0x89, 1},
        { 0x8a, 1},
        { 0x8b, 1},
        { 0x8c, 1},
        { 0x8d, 1},
        { 0x8e, 1},
        { 0x8f, 1},
        { 0x90, 1},
        { 0x91, 1},
        { 0x92, 1},
        { 0x93, 1},
        { 0x94, 1},
        { 0x95, 1},
        { 0x96, 1},
        { 0x97, 1},
        { 0x98, 1},
        { 0x99, 1},
        { 0x9a, 1},
        { 0x9b, 1},
        { 0x9c, 1},
        { 0x9d, 1},
        { 0x9e, 1},
        { 0x9f, 1},
        { 0xa0, 1},
        { 0xa1, 1},
        { 0xa2, 1},
        { 0xa3, 1},
        { 0xa4, 1},
        { 0xa5, 1},
        { 0xa6, 1},
        { 0xa7, 1},
        { 0xa8, 1},
        { 0xa9, 1},
        { 0xaa, 1},
        { 0xab, 1},
        { 0xac, 1},
        { 0xad, 1},
        { 0xae, 1},
        { 0xaf, 1},
        { 0xb0, 1},
        { 0xb1, 1},
        { 0xb2, 1},
        { 0xb3, 1},
        { 0xb4, 1},
        { 0xb5, 1},
        { 0xb6, 1},
        { 0xb7, 1},
        { 0xb8, 1},
        { 0xb9, 1},
        { 0xba, 1},
        { 0xbb, 1},
        { 0xbc, 1},
        { 0xbd, 1},
        { 0xbe, 1},
        { 0xbf, 1},
        { 0xc0, 1},
        { 0xc1, 1},
        { 0xc5, 1},
        { 0xc7, 1},
        { 0xc8, 1},
        { 0xc9, 1},
        { 0xcf, 1},
        { 0xd0, 1},
        { 0xd1, 1},
        { 0xd5, 1},
        { 0xd7, 1},
        { 0xd8, 1},
        { 0xdf, 1},
        { 0xe0, 1},
        { 0xe1, 1},
        { 0xe3, 1},
        { 0xe5, 1},
        { 0xe7, 1},
        { 0xe8, 1},
        { 0xe9, 1},
        { 0xeb, 1},
        { 0xef, 1},
        { 0xf0, 1},
        { 0xf1, 1},
        { 0xf3, 1},
        { 0xf5, 1},
        { 0xf7, 1},
        { 0xf8, 1},
        { 0xf9, 1},
        { 0xfb, 1},
        { 0xff, 1},
        { 0x06, 2 },
        { 0x0e, 2 },
        { 0x16, 2 },
        { 0x1e, 2 },
        { 0x26, 2 },
        { 0x2e, 2 },
        { 0x36, 2 },
        { 0x3e, 2 },
        { 0xc6, 2 },
        { 0xce, 2 },
        { 0xd3, 2 },
        { 0xd6, 2 },
        { 0xdb, 2 },
        { 0xde, 2 },
        { 0xe6, 2 },
        { 0xee, 2 },
        { 0xf6, 2 },
        { 0xfe, 2 },
        { 0x01, 3 },
        { 0x11, 3 },
        { 0x21, 3 },
        { 0x22, 3 },
        { 0x2a, 3 },
        { 0x31, 3 },
        { 0x32, 3 },
        { 0x3a, 3 },
        { 0xc2, 3 },
        { 0xc3, 3 },
        { 0xc4, 3 },
        { 0xca, 3 },
        { 0xcc, 3 },
        { 0xcd, 3 },
        { 0xd2, 3 },
        { 0xd4, 3 },
        { 0xda, 3 },
        { 0xdc, 3 },
        { 0xdf, 3 },
        { 0xe2, 3 },
        { 0xe4, 3 },
        { 0xea, 3 },
        { 0xec, 3 },
        { 0xf2, 3 },
        { 0xf4, 3 },
        { 0xfa, 3 },
        { 0xfc, 3 }
    };

    const std::map<uint8_t, int> cyclesUsedByOpcodes {
        { 0x00, 4 },
        { 0x01, 10 },
        { 0x02, 7 },
        { 0x03, 5 },
        { 0x04, 5 },
        { 0x05, 5 },
        { 0x06, 7 },
        { 0x07, 4 },
        { 0x08, 4 },
        { 0x09, 10 },
        { 0x0a, 7 },
        { 0x0b, 5 },
        { 0x0c, 5 },
        { 0x0d, 5 },
        { 0x0e, 7 },
        { 0x0f, 4 },
        { 0x10, 4 },
        { 0x11, 10 },
        { 0x12, 7 },
        { 0x13, 5 },
        { 0x14, 5 },
        { 0x15, 5 },
        { 0x16, 7 },
        { 0x17, 4 },
        { 0x18, 4 },
        { 0x19, 10 },
        { 0x1a, 7 },
        { 0x1b, 5 },
        { 0x1c, 5 },
        { 0x1d, 5 },
        { 0x1e, 7 },
        { 0x1f, 4 },
        { 0x20, 4 },
        { 0x21, 10 },
        { 0x22, 16 },
        { 0x23, 5 },
        { 0x24, 5 },
        { 0x25, 5 },
        { 0x26, 7 },
        { 0x27, 4 },
        { 0x28, 4 },
        { 0x29, 10 },
        { 0x2a, 16 },
        { 0x2b, 5 },
        { 0x2c, 5 },
        { 0x2d, 5 },
        { 0x2e, 7 },
        { 0x2f, 4 },
        { 0x30, 4 },
        { 0x31, 10 },
        { 0x32, 13 },
        { 0x33, 5 },
        { 0x34, 10 },
        { 0x35, 10 },
        { 0x36, 10 },
        { 0x37, 4 },
        { 0x38, 4 },
        { 0x39, 10 },
        { 0x3a, 13 },
        { 0x3b, 5 },
        { 0x3c, 5 },
        { 0x3d, 5 },
        { 0x3e, 7 },
        { 0x3f, 4 },
        { 0x40, 5 },
        { 0x41, 5 },
        { 0x42, 5 },
        { 0x43, 5 },
        { 0x44, 5 },
        { 0x45, 5 },
        { 0x46, 7 },
        { 0x47, 5 },
        { 0x48, 5 },
        { 0x49, 5 },
        { 0x4a, 5 },
        { 0x4b, 5 },
        { 0x4c, 5 },
        { 0x4d, 5 },
        { 0x4e, 7 },
        { 0x4f, 5 },
        { 0x50, 5 },
        { 0x51, 5 },
        { 0x52, 5 },
        { 0x53, 5 },
        { 0x54, 5 },
        { 0x55, 5 },
        { 0x56, 7 },
        { 0x57, 5 },
        { 0x58, 5 },
        { 0x59, 5 },
        { 0x5a, 5 },
        { 0x5b, 5 },
        { 0x5c, 5 },
        { 0x5d, 5 },
        { 0x5e, 7 },
        { 0x5f, 5 },
        { 0x60, 5 },
        { 0x61, 5 },
        { 0x62, 5 },
        { 0x63, 5 },
        { 0x64, 5 },
        { 0x65, 5 },
        { 0x66, 7 },
        { 0x67, 5 },
        { 0x68, 5 },
        { 0x69, 5 },
        { 0x6a, 5 },
        { 0x6b, 5 },
        { 0x6c, 5 },
        { 0x6d, 5 },
        { 0x6e, 7 },
        { 0x6f, 5 },
        { 0x70, 7 },
        { 0x71, 7 },
        { 0x72, 7 },
        { 0x73, 7 },
        { 0x74, 7 },
        { 0x75, 7 },
        { 0x76, 7 },
        { 0x77, 7 },
        { 0x78, 5 },
        { 0x79, 5 },
        { 0x7a, 5 },
        { 0x7b, 5 },
        { 0x7c, 5 },
        { 0x7d, 5 },
        { 0x7e, 7 },
        { 0x7f, 5 },
        { 0x80, 4 },
        { 0x81, 4 },
        { 0x82, 4 },
        { 0x83, 4 },
        { 0x84, 4 },
        { 0x85, 4 },
        { 0x86, 7 },
        { 0x87, 4 },
        { 0x88, 4 },
        { 0x89, 4 },
        { 0x8a, 4 },
        { 0x8b, 4 },
        { 0x8c, 4 },
        { 0x8d, 4 },
        { 0x8e, 7 },
        { 0x8f, 4 },
        { 0x90, 4 },
        { 0x91, 4 },
        { 0x92, 4 },
        { 0x93, 4 },
        { 0x94, 4 },
        { 0x95, 4 },
        { 0x96, 7 },
        { 0x97, 4 },
        { 0x98, 4 },
        { 0x99, 4 },
        { 0x9a, 4 },
        { 0x9b, 4 },
        { 0x9c, 4 },
        { 0x9d, 4 },
        { 0x9e, 7 },
        { 0x9f, 4 },
        { 0xa0, 4 },
        { 0xa1, 4 },
        { 0xa2, 4 },
        { 0xa3, 4 },
        { 0xa4, 4 },
        { 0xa5, 4 },
        { 0xa6, 7 },
        { 0xa7, 4 },
        { 0xa8, 4 },
        { 0xa9, 4 },
        { 0xaa, 4 },
        { 0xab, 4 },
        { 0xac, 4 },
        { 0xad, 4 },
        { 0xae, 7 },
        { 0xaf, 4 },
        { 0xb0, 4 },
        { 0xb1, 4 },
        { 0xb2, 4 },
        { 0xb3, 4 },
        { 0xb4, 4 },
        { 0xb5, 4 },
        { 0xb6, 7 },
        { 0xb7, 4 },
        { 0xb8, 4 },
        { 0xb9, 4 },
        { 0xba, 4 },
        { 0xbb, 4 },
        { 0xbc, 4 },
        { 0xbd, 4 },
        { 0xbe, 7 },
        { 0xbf, 4 },
        { 0xc0, 11 },
        { 0xc1, 10 },
        { 0xc2, 10 },
        { 0xc3, 10 },
        { 0xc4, 17 },
        { 0xc5, 11 },
        { 0xc6, 7 },
        { 0xc7, 11 },
        { 0xc8, 11 },
        { 0xc9, 10 },
        { 0xca, 10 },
        { 0xcb, 10 },
        { 0xcc, 10 },
        { 0xcd, 17 },
        { 0xce, 7 },
        { 0xcf, 11 },
        { 0xd0, 11 },
        { 0xd1, 10 },
        { 0xd2, 10 },
        { 0xd3, 10 },
        { 0xd4, 17 },
        { 0xd5, 11 },
        { 0xd6, 7 },
        { 0xd7, 11 },
        { 0xd8, 11 },
        { 0xd9, 10 },
        { 0xda, 10 },
        { 0xdb, 10 },
        { 0xdc, 10 },
        { 0xdd, 17 },
        { 0xde, 7 },
        { 0xdf, 11 },
        { 0xe0, 11 },
        { 0xe1, 10 },
        { 0xe2, 10 },
        { 0xe3, 18 },
        { 0xe4, 17 },
        { 0xe5, 11 },
        { 0xe6, 7 },
        { 0xe7, 11 },
        { 0xe8, 11 },
        { 0xe9, 5 },
        { 0xea, 10 },
        { 0xeb, 5 },
        { 0xec, 17 },
        { 0xed, 17 },
        { 0xee, 7 },
        { 0xef, 11 },
        { 0xf0, 11 },
        { 0xf1, 10 },
        { 0xf2, 10 },
        { 0xf3, 4 },
        { 0xf4, 17 },
        { 0xf5, 11 },
        { 0xf6, 7 },
        { 0xf7, 11 },
        { 0xf8, 11 },
        { 0xf9, 5 },
        { 0xfa, 10 },
        { 0xfb, 4 },
        { 0xfc, 17 },
        { 0xfd, 17 },
        { 0xfe, 7 },
        { 0xff, 11 }
    };
}

#endif