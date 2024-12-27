#include <stdio.h>

int xor_bits(unsigned int num) {
    int result = 0;

    while (num > 0) {
        result ^= (num & 1);
        num >>= 1;
    }

    return result;
}

int main() {
    unsigned int num1 = 0b101110001;
    unsigned int num2 = 0b11100111;

    printf("XOR всех битов числа %u = %d\n", num1, xor_bits(num1));
    printf("XOR всех битов числа %u = %d\n", num2, xor_bits(num2));

    return 0;
}