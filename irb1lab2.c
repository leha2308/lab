#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERR (-1)
#define INVALID_INPUT (-2)
#define INVALID_PARAMETER (-3)
#define MEMORY_ALLOCATION_ERROR (-4)

#define PRINT_ERROR_MESSAGE() printf("Error: unforeseen error. Restarting the program may help.\n")
#define PRINT_INVALID_INPUT_MESSAGE() printf("Error: invalid input. Please restart the program and pass proper input values.\n")
#define PRINT_INVALID_PARAMETER_MESSAGE() printf("Error: invalid parameter. Restarting the program may help.\n")
#define PRINT_MEMORY_ALLOCATION_ERROR() printf("Error: couldn't allocate memory. Restarting the program may help.\n")

int from_decimal_to_binary(int const num, int const radix, char ** const result) {
    if (result == NULL || radix < 1 || radix > 5) return INVALID_PARAMETER;

    int num_copy = abs(num);
    int real_radix = 1 << radix;
    int digits_len = 0;

    unsigned short *digits = NULL, *p_digits;
    char *p_result, *all_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if ((*result = (char*) malloc((BUFSIZ + 1) * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;
    p_result = *result;

    if ((digits = (unsigned short *) malloc(BUFSIZ * sizeof(unsigned short))) == NULL) {
        free(*result);
        return MEMORY_ALLOCATION_ERROR;
    }
    p_digits = digits;

    while (num_copy != 0) {
        *p_digits++ = num_copy & (real_radix - 1);
        num_copy >>= radix;
        digits_len++;
    }

    if (num < 0) *p_result++ = '-';

    for (int i = digits_len - 1; i >= 0; i--) {
        *p_result++ = all_chars[digits[i]];
    }
    *p_result = '\0';

    free(digits);
    return OK;
}

int work() {
    int num, radix;

    printf("Input your number: ");
    if (scanf("%d", &num) != 1) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }

    printf("Input your power of 2: ");
    if (scanf("%d", &radix) != 1) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }

    char* result = NULL;
    if ((result = (char*) malloc(sizeof(char) * (BUFSIZ + 1))) == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = from_decimal_to_binary(num, radix, &result);
    switch (result_code) {
        case OK:
            printf("Result: %s\n", result);
            break;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            break;
        case MEMORY_ALLOCATION_ERROR:
            PRINT_MEMORY_ALLOCATION_ERROR();
            break;
        default:
            PRINT_ERROR_MESSAGE();
            break;
    }

    free(result);
    return result_code;
}

int main() {
    return work();
}
