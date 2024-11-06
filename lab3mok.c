#include <stdio.h>

int main() {
    unsigned int a;
    int k;


    printf("Enter the number a: ");
    scanf("%u", &a);


    printf("Enter bit number k (starting from 0): ");
    scanf("%d", &k);


    if (k < 0) {
        printf("The bit number cannot be negative.\n");
        return 1;
    }


    a |= (1U << k);


    printf("New value of number a after setting %d-th bit: %u\n", k, a);

    return 0;
}