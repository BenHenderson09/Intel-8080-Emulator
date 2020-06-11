#include "BinaryArithmetic.hpp"

bool isThereAnEvenCountOfOnes(int number){ 
    int countOfOnesInBinaryNumber{0};

    while (number > 0){
        bool firstBitOfBinaryNumberIsEqualToOne{number & 1};

        if (firstBitOfBinaryNumberIsEqualToOne) countOfOnesInBinaryNumber++;
        number = number >> 1; // Remove the first bit of the binary number
    }

    return countOfOnesInBinaryNumber % 2 == 0;
}

