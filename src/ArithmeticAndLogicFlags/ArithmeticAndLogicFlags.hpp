// Most of the arithmetic and logic operations will store their results into
// register A, the 8-bit accumulator.
// The flags listed in the code below indicate information about the results of these
// arithmetic and logic operations.

#ifndef ARITHMETIC_AND_LOGIC_FLAGS_HPP
#define ARITHMETIC_AND_LOGIC_FLAGS_HPP

namespace Intel8080 {
    struct  ArithmeticAndLogicFlags {
        bool zero;
        bool carry;    
        bool sign;    
        bool parity;    
        bool auxiliaryCarry; // TODO look into this bit's behaviour
    };
}
#endif