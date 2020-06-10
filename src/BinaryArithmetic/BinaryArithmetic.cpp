#include "BinaryArithmetic.hpp"

namespace BinaryArithmetic {
    bool isThereAnEvenCountOfOnesInBinaryNumber(int binaryNumber){ 
        int countOfOnesInBinaryNumber{0};

        while (binaryNumber > 0){
            bool firstBitOfBinaryNumberIsEqualToOne{binaryNumber & 1};
    
            if (firstBitOfBinaryNumberIsEqualToOne) countOfOnesInBinaryNumber++;
            binaryNumber = binaryNumber >> 1; // Remove the first bit of the binary number
        }

        return countOfOnesInBinaryNumber % 2 == 0;
    }
}
