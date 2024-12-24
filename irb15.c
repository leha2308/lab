#include <stdio.h>
#include <string.h>
#include <ctype.h>

void rewrite(char *str) {
    char str_digit[100] = "";
    char str_alpha[100] = "";
    char str_other[100] = "";

    int str_digit_count = 0;
    int str_alpha_count = 0;
    int str_other_count = 0;


    while (*str != '\0') {
        if (isdigit(*str)) {
            str_digit[str_digit_count++] = *str;
        } else if (isalpha(*str)) {
            str_alpha[str_alpha_count++] = *str;
        } else {
            str_other[str_other_count++] = *str;
        }
        str++;
    }


    str_digit[str_digit_count] = '\0';
    str_alpha[str_alpha_count] = '\0';
    str_other[str_other_count] = '\0';


    char *temp = str - strlen(str_digit) - strlen(str_alpha) - strlen(str_other);
    strcpy(temp, str_digit);
    strcat(temp, str_alpha);
    strcat(temp, str_other);
}

int main() {
    char str[100] = "ertrt3434-6";
    printf("The original line: %s\n", str);

    rewrite(str);

    printf("Rearranged row: %s\n", str);

    return 0;
}