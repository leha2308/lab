#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define MEMORY_ERROR -1
#define INVALID_PARAMETER -2
#define OK 0

static int convert_to_int(const char *str, int base) {
    int value = 0;
    while (*str) {
        char c = *str++;
        int digit = (c >= '0' && c <= '9') ? c - '0' : (c >= 'A' && c <= 'Z') ? c - 'A' + 10 : -1;
        if (digit < 0 || digit >= base) {
            return -1;
        }
        value = value * base + digit;
    }
    return value;
}

static bool is_kaprekar(int num, int base) {
    if (num < 0) return false;

    long long square = (long long)num * num;
    char square_str[64];
    snprintf(square_str, sizeof(square_str), "%lld", square);

    int len = strlen(square_str);
    int num_len = snprintf(NULL, 0, "%d", num);
    int split_pos = len - num_len;

    if (split_pos <= 0) return false;

    char left[64] = {0}, right[64] = {0};
    strncpy(left, square_str, split_pos);
    strcpy(right, square_str + split_pos);

    int left_num = (strlen(left) > 0) ? strtol(left, NULL, base) : 0;
    int right_num = strtol(right, NULL, base);

    return (left_num + right_num) == num;
}

int find_kaprekar_numbers(int base, int count, ...) {
    if (base < 2 || base > 36 || count <= 0) {
        return INVALID_PARAMETER;
    }

    va_list args;
    va_start(args, count);

    printf("Kaprekar numbers in base %d:\n", base);

    for (int i = 0; i < count; ++i) {
        const char *num_str = va_arg(args, const char *);
        int num = convert_to_int(num_str, base);
        if (num >= 0 && is_kaprekar(num, base)) {
            printf("%s\n", num_str);
        }
    }

    va_end(args);
    return OK;
}

int main() {
    int base = 10;
    find_kaprekar_numbers(base, 5, "45", "9", "55");
    return 0;
}
