#include <stdio.h>

int main() {
    char elements[100];
    int i = 0;

    printf("Enter the text (press Enter to finish typing):\n");

    while ((elements[i] = getchar()) != '\n' && i < 99) {
        i++;
    }
    elements[i] = '\0';

    printf("The read text: %s\n", elements);

    int size = i;  

    for (int j = 0; j < size; j++) {
        printf("Symbol %d: %c\n", j + 1, elements[j]);
    }
    printf("Total number of characters: %d\n", i);
    return 0;
}
