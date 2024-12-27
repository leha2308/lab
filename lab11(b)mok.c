#include <stdio.h>
#include <stdint.h>

uint32_t extract_middle_bits(uint32_t num, int len, int i) {

    uint32_t shifted = num >> i;

    return shifted & ((1U << (len - 2 * i)) - 1);
}

int main() {
    uint32_t num = 0b100011101101;
    int len = 12;
    int i = 3;

    uint32_t middle = extract_middle_bits(num, len, i);
    printf("Исходное число:   0b%012b\n", num);
    printf("Средние биты:     0b%06b\n", middle);

    return 0;
}
