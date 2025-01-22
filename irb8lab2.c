#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define SUCCESS 0
#define INVALID_BASE 1
#define INVALID_INPUT 2
#define MEMORY_ERROR 3

int is_valid_number(const char* num, int base) {
    if (!num || base < 2 || base > 36) return 0;
    for (int i = 0; num[i] != '\0'; ++i) {
        char c = toupper(num[i]);
        if (!((c >= '0' && c <= '9' && c - '0' < base) ||
              (c >= 'A' && c <= 'Z' && c - 'A' + 10 < base))) {
            return 0;
        }
    }
    return 1;
}

char* add_in_column(const char* num1, const char* num2, int base) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = len1 > len2 ? len1 : len2;

    char* result = (char*)malloc((max_len + 2) * sizeof(char));
    if (!result) return NULL;

    int carry = 0, pos = 0;
    for (int i = 0; i < max_len || carry; ++i) {
        int digit1 = (i < len1) ? (isdigit(num1[len1 - i - 1]) ? num1[len1 - i - 1] - '0' : num1[len1 - i - 1] - 'A' + 10) : 0;
        int digit2 = (i < len2) ? (isdigit(num2[len2 - i - 1]) ? num2[len2 - i - 1] - '0' : num2[len2 - i - 1] - 'A' + 10) : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        sum %= base;

        result[pos++] = (sum < 10) ? (sum + '0') : (sum - 10 + 'A');
    }
    if (carry) {
        result[pos++] = (carry < 10) ? (carry + '0') : (carry - 10 + 'A');
    }
    result[pos] = '\0';

    for (int i = 0; i < pos / 2; ++i) {
        char temp = result[i];
        result[i] = result[pos - i - 1];
        result[pos - i - 1] = temp;
    }

    return result;
}

int sum_numbers_in_base(int base, int count, ...) {
    if (base < 2 || base > 36 || count < 1) return INVALID_BASE;

    va_list args;
    va_start(args, count);

    char* sum = (char*)malloc(2 * sizeof(char));
    if (!sum) return MEMORY_ERROR;

    strcpy(sum, "0");

    for (int i = 0; i < count; ++i) {
        const char* num = va_arg(args, const char*);
        if (!is_valid_number(num, base)) {
            free(sum);
            va_end(args);
            return INVALID_INPUT;
        }
        char* new_sum = add_in_column(sum, num, base);
        if (!new_sum) {
            free(sum);
            va_end(args);
            return MEMORY_ERROR;
        }
        free(sum);
        sum = new_sum;
    }

    printf("The amount in the number system %d: %s\n", base, sum);
    free(sum);

    va_end(args);
    return SUCCESS;
}

int main() {
    int result = sum_numbers_in_base(2, 3, "1101", "101", "10001");
    if (result == SUCCESS) {
        printf("Example 1 was completed successfully.\n");
    } else {
        printf("Error in Example 1: error code %d\n", result);
    }

    result = sum_numbers_in_base(16, 3, "1A", "2F", "B4");
    if (result == SUCCESS) {
        printf("Example 2 was completed successfully.\n");
    } else {
        printf("Error in Example 2: error code %d\n", result);
    }

    result = sum_numbers_in_base(10, 2, "123", "1G5");
    if (result == SUCCESS) {
        printf("Example 3 was completed successfully.\n");
    } else {
        printf("Error in Example 3: error code %d\n", result);
    }

    return 0;
}
