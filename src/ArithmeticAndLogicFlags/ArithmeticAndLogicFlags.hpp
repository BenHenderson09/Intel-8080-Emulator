#ifndef ARITHMETIC_AND_LOGIC_FLAGS_HPP
#define ARITHMETIC_AND_LOGIC_FLAGS_HPP

namespace Intel8080 {
    struct  ArithmeticAndLogicFlags {
        bool zero;
        bool carry;    
        bool sign;    
        bool parity;    
        bool auxiliaryCarry;
    };
}

#endif