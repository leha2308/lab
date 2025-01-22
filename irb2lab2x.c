#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

size_t custom_strlen(const char *str) {
    size_t length = 0;
    while (str && *str++) {
        length++;
    }
    return length;
}

char *reverse_string(const char *str) {
    if (!str) return NULL;

    size_t len = custom_strlen(str);
    char *reversed = (char *)malloc(len + 1);
    if (!reversed) return NULL;

    for (size_t i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';

    return reversed;
}

char *uppercase_odd(const char *str) {
    if (!str) return NULL;

    size_t len = custom_strlen(str);
    char *result = (char *)malloc(len + 1);
    if (!result) return NULL;

    for (size_t i = 0; i < len; i++) {
        result[i] = (i % 2 == 1) ? toupper((unsigned char)str[i]) : str[i];
    }
    result[len] = '\0';

    return result;
}

char *rearrange_string(const char *str) {
    if (!str) return NULL;

    size_t len = custom_strlen(str);
    char *digits = (char *)malloc(len + 1);
    char *letters = (char *)malloc(len + 1);
    char *others = (char *)malloc(len + 1);

    if (!digits || !letters || !others) {
        free(digits);
        free(letters);
        free(others);
        return NULL;
    }

    size_t d = 0, l = 0, o = 0;

    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            digits[d++] = str[i];
        } else if (isalpha((unsigned char)str[i])) {
            letters[l++] = str[i];
        } else {
            others[o++] = str[i];
        }
    }

    digits[d] = letters[l] = others[o] = '\0';

    char *result = (char *)malloc(len + 1);
    if (!result) {
        free(digits);
        free(letters);
        free(others);
        return NULL;
    }

    sprintf(result, "%s%s%s", digits, letters, others);
    free(digits);
    free(letters);
    free(others);

    return result;
}

char *concatenate_random(unsigned int seed, int count, char **strings) {
    if (count < 1 || !strings) return NULL;

    srand(seed);


    char **selected = (char **)malloc(count * sizeof(char *));
    if (!selected) return NULL;

    size_t total_len = 0;
    size_t selected_count = 0;


    for (int i = 0; i < count; i += 2) {
        if (strings[i]) {
            selected[selected_count++] = strings[i];
            total_len += custom_strlen(strings[i]);
        }
    }


    for (size_t i = 0; i < selected_count; i++) {
        size_t j = rand() % selected_count;
        char *temp = selected[i];
        selected[i] = selected[j];
        selected[j] = temp;
    }


    char *result = (char *)malloc(total_len + 1);
    if (!result) {
        free(selected);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < selected_count; i++) {
        const char *src = selected[i];
        while (*src) {
            result[offset++] = *src++;
        }
    }

    result[offset] = '\0';
    free(selected);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <flag> <string> [<seed> <strings>...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *flag = argv[1];
    const char *input_string = argv[2];
    char *result = NULL;

    if (flag[0] != '-') {
        fprintf(stderr, "Invalid flag format: %s\n", flag);
        return EXIT_FAILURE;
    }

    switch (flag[1]) {
        case 'l': {
            printf("Length: %zu\n", custom_strlen(input_string));
            break;
        }
        case 'r': {
            result = reverse_string(input_string);
            break;
        }
        case 'u': {
            result = uppercase_odd(input_string);
            break;
        }
        case 'n': {
            result = rearrange_string(input_string);
            break;
        }
        case 'c': {
            if (argc < 4) {
                fprintf(stderr, "Flag -c requires a seed and additional strings.\n");
                return EXIT_FAILURE;
            }
            unsigned int seed = (unsigned int)strtoul(argv[3], NULL, 10);
            result = concatenate_random(seed, argc - 4, &argv[4]);
            break;
        }
        default: {
            fprintf(stderr, "Unknown flag: %s\n", flag);
            return EXIT_FAILURE;
        }
    }

    if (result) {
        printf("Result: %s\n", result);
        free(result);
    }

    return EXIT_SUCCESS;
}

