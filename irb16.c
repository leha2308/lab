#include <stdio.h>
#include <ctype.h>
#include <string.h>

void exclude(char *str) {
    char result[strlen(str) + 1];
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) || isalpha(str[i])) {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';
    strcpy(str, result);

    printf("Result: %s\n", str);
}

int main() {
    char str[] = "es30-2;4x'f[2kv-2k4ew";

    exclude(str);

    return 0;
}



