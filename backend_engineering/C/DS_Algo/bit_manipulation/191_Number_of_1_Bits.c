#include <stdio.h>

int hammingWeight(int n) {
    int set_bit_count = 0;
    while(n != 0)
    {
        // If we subtract 1 from a number, we will get compliment of the the bits starting from
        // the right most 1 in the original number.
        // For e.g. if the number is    .........1 0 0 0 0. If we subtract 1 from this
        // number, we will get          .........0 1 1 1 1. Now if we & this n - 1 with n, we
        // will get                     .........0 0 0 0 0. This way way we can set the rightmost
        // 1 bit to 0 in one operation.
        // Hence couting the number of bits in n boils down to the number of times we can knock of
        // the 1 bits untill n reaches to 0.
        n = n & (n - 1);
        ++set_bit_count;
    }

    return set_bit_count;
}

