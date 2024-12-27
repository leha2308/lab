#include <stdio.h>
#include <stdint.h>

uint32_t extract_first_bits(uint32_t num, int len, int i) {
    return (num >> (len - i)) & ((1U << i) - 1);
}

uint32_t extract_last_bits(uint32_t num, int i) {
    return num & ((1U << i) - 1);
}

uint32_t glue_bits(uint32_t num, int len, int i) {
    uint32_t first = extract_first_bits(num, len, i);
    uint32_t last = extract_last_bits(num, i);
    return (first << i) | last;
}

int main() {
    uint32_t num = 0b100011101101;
    int len = 12;
    int i = 3;

    uint32_t glued = glue_bits(num, len, i);
    printf("Исходное число: 0b%012b\n", num);
    printf("Склеенные биты: 0b%06b\n", glued);

    return 0;
}
