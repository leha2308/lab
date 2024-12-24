#include <stdio.h>

int main() {
    char elements[100];
    int i = 0;

    printf("Введите текст (нажмите Enter для окончания ввода):\n");

    while ((elements[i] = getchar()) != '\n' && i < 99) {
        i++;
    }
    elements[i] = '\0';

    printf("Считанный текст: %s\n", elements);

    int size = i;  

    for (int j = 0; j < size; j++) {
        printf("Символ %d: %c\n", j + 1, elements[j]);
    }
    printf("Общее кол-во символов: %d\n", i);
    return 0;
}
