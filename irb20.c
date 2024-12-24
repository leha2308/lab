#include <stdio.h>
#include <stdlib.h>

void intToBase(int num, int base, char *result) {
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int isNegative = 0;
    int index = 0;

    if (base < 2 || base > 36) {
        printf("Error: The base must be in the range [2..36].\n");
        result[0] = '\0';
        return;
    }

    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    do {
        result[index++] = digits[num % base];
        num /= base;
    } while (num > 0);

    if (isNegative) {
        result[index++] = '-';
    }

    result[index] = '\0';

    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
}

int main() {
    int number, base;
    char result[65];

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("Enter the base of the number system (от 2 до 36): ");
    scanf("%d", &base);

    intToBase(number, base, result);
    if (result[0] != '\0') {
        printf("A number in the numeral system with a base %d: %s\n", base, result);
    }

    return 0;
}
