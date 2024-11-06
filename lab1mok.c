#include <stdio.h>

int main() {
    int a;

    printf("Enter an integer: ");
    scanf("%d", &a);


    int lower_bit = a & 1;


    printf("The lowest bit of %d is equal to: %d\n", a, lower_bit);

    return 0;
}
