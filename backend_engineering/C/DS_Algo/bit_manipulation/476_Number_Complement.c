#include <stdio.h>

int findComplement(int num) {
    int copy = num;
    // Find number of bits taken by this number
    int num_bits = 0;
    while(num != 0)
    {
        num = num >> 1;
        ++num_bits;
    }

    return copy ^ ((int)(1 << num_bits) - 1);
}