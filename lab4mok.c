#include <stdio.h>

int main() {
    int a;
    int k;


    printf("Enter the number: ");
    scanf("%d", &a);


    printf("Enter the bit number (0 is the least significant bit): ");
    scanf("%d", &k);


    if (k < 0 || k >= sizeof(int) * 8) {
        printf("Error: Bit number must be between 0 and %d.\n", sizeof(int) * 8 - 1);
        return 1;
    }


    a &= ~(1 << k);


    printf("Number after removing %d-th bit: %d\n", k, a);

    return 0;
}