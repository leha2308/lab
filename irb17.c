#include <stdio.h>
#include <string.h>
#include <ctype.h>

void str_cat(char *str1, char *str2) {
    char res[strlen(str1) + strlen(str2) + 1];
    int c = 0;
    for (int i = 0; str1[i] != '\0'; i++) {
        res[c++] = str1[i];
    }
    for (int j = 0; str2[j] != '\0'; j++) {
        res[c++] = str2[j];
    }
    res[c] = '\0';

    printf("%s\n", res);
}

int main(){
    char str1[] = {"sehe"};
    char str2[] = {"eyu"};

    str_cat(str1, str2);

    return 0;
}