#include <stdio.h>
#include <stdint.h>

uint32_t rotate_left(uint32_t x, int n, int bit_width) {

    return ((x << n) | (x >> (bit_width - n))) & ((1U << bit_width) - 1);
}

uint32_t rotate_right(uint32_t x, int n, int bit_width) {

    return ((x >> n) | (x << (bit_width - n))) & ((1U << bit_width) - 1);
}

int main() {
    uint8_t x = 0b10111001;
    int bit_width = 8;
    int n = 3;

    uint8_t left_result = rotate_left(x, n, bit_width);
    printf("Исходное число: 0b%08b\n", x);
    printf("Сдвиг влево на %d:  0b%08b\n", n, left_result);

    uint8_t right_result = rotate_right(x, n, bit_width);
    printf("Сдвиг вправо на %d: 0b%08b\n", n, right_result);

    return 0;
}
