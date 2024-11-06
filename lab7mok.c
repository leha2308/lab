#include <stdio.h>
#include <stdint.h>

void swap_bytes(uint32_t number, int permutation[4]) {
    uint8_t bytes[4];


    for (int i = 0; i < 4; i++) {
        bytes[i] = (number >> (i * 8)) & 0xFF;
    }


    uint32_t swapped_number = 0;
    for (int i = 0; i < 4; i++) {
        swapped_number |= (uint32_t)bytes[permutation[i]] << (i * 8);
    }

    printf("Original number: 0x%X\n", number);
    printf("Rearranged number: 0x%X\n", swapped_number);
}

int main() {
    uint32_t number;
    int permutation[4];


    printf("Enter a 32-bit integer (in hexadecimal format, e.g. 0x12345678): ");
    scanf("%x", &number);

    printf("Enter the permutation (4 numbers from 0 to 3, separated by spaces): ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &permutation[i]);
    }


    int valid = 1;
    int seen[4] = {0};
    for (int i = 0; i < 4; i++) {
        if (permutation[i] < 0 || permutation[i] > 3 || seen[permutation[i]]++) {
            valid = 0;
            break;
        }
    }

    if (!valid) {
        printf("Error: Permutation must contain 4 unique indices from 0 to 3.\n");
        return 1;
    }


    swap_bytes(number, permutation);

    return 0;
}
