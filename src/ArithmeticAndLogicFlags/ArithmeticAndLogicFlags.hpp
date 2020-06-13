/*
    Most of the arithmetic and logic operations will store their results into
    register A, the 8-bit accumulator.
    The flags listed in the code below indicate information about the results of these
    arithmetic and logic operations.

    The 8080 has 5 flags, which indicate the results of arithmetic and logical instructions from the ALU.
    These are stored in the flag register, with one bit for each flag.

    The 8080 flag register can't be accessed like general purpose registers. Only specific instructions,
    like "PUSH PSW" and "POP PSW" can be used.
    Note that the PSW refers to both the A register and the flag register together,
    and Intel considers it a "register pair".
 
    Intel 8080 Assembly Language Programming Manual:
        "
            Register pair PSW (Program Status Word) refers to register
            A and a special byte which reflects the current status of
            the machine flags.
        "
 
    The "special byte" is the flag register.
    This tells us that despite there being only 5 flags, the register is 8 bits,
    meaning there are 3 unused bits.
 
    This is confirmed later in the same document:
     "
         PSW: One byte indicating the state of the
         condition bits, and Register A
     "

    This would lead us to believe that the register is in fact 8 bits. But the fun doesn't stop there. If we
    check the Intel 8080 Microcomputer Systems User's Manual, it states the following:
    "A 5-bit flag register: zero, carry, sign, parity and auxiliary carry".

    There also seems to be a lot of conflicting information on various websites, so since it seems that
    nobody really knows, I'm going to assume it's a 5-bit register. This will eliminate any unused bits.
*/

#ifndef ARITHMETIC_AND_LOGIC_FLAGS_HPP
#define ARITHMETIC_AND_LOGIC_FLAGS_HPP

struct  ArithmeticAndLogicFlags {
    bool zero;
    bool carry;    
    bool sign;    
    bool parity;    
    bool auxiliaryCarry; // TODO look into this bit's behaviour
};

#endif