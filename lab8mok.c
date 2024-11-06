#include <stdio.h>
#include <stdint.h>

int max_power_of_two(int number) {

    if (number <= 0) {
        return -1;
    }


    int power = 0;


    while ((number & 1) == 0) {
        number >>= 1;
        power++;
    }

    return power; //
}

int main() {
    int number;


    printf("Enter an integer: ");
    scanf("%d", &number);


    int result = max_power_of_two(number);

    if (result == -1) {
        printf("Error: Enter a positive integer.\n");
    } else {
        printf("The maximum power of 2 that can be divided into %d: %d\n", number, result);
    }

    return 0;
}