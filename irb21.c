#include <stdio.h>
#include <ctype.h>
#include <string.h>

int baseToInt(const char *str, int base) {
    int result = 0;
    int isNegative = 0;
    const char *ptr = str;

    if (base < 2 || base > 36) {
        printf("Ошибка: Основание должно быть в диапазоне [2..36].\n");
        return 0;
    }

    if (*ptr == '-') {
        isNegative = 1;
        ptr++;
    }

    while (*ptr != '\0') {
        char c = toupper(*ptr);
        int value;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            value = c - 'A' + 10;
        } else {
            printf("Ошибка: Неверный символ '%c' в строке.\n", c);
            return 0;
        }

        if (value >= base) {
            printf("Ошибка: Символ '%c' не соответствует основанию %d.\n", c, base);
            return 0;
        }

        result = result * base + value;
        ptr++;
    }

    return isNegative ? -result : result;
}

int main() {
    char str[65];
    int base;

    printf("Введите строку числа: ");
    scanf("%64s", str);

    printf("Введите основание системы счисления (от 2 до 36): ");
    scanf("%d", &base);

    int result = baseToInt(str, base);
    printf("Число в десятичной системе: %d\n", result);

    return 0;
}
