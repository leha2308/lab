#include <stdio.h>

int main() {
    int a;
    int k;

    printf("Enter an integer: ");
    scanf("%d", &a);

    printf("Enter the bit number (0 - the lowest bit): ");
    scanf("%d", &k);


    if (k < 0 || k >= sizeof(int) * 8) {
        printf("Error: The bit number must be in the range from 0 to %d.", sizeof(int) * 8 - 1);
        return 1;
    }


    int bit_value = (a >> k) & 1;


    printf("The value of the %dth bit of the number %d is equal to: %d", k, a, bit_value);

    return 0;
}