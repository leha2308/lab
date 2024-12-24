#include <stdio.h>

int main() {
    int array[] = {23, 34, 45, 56, 67, 78, 89, 90, 132, 343, 4564, 5757, 343455};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Исходный массив: ");

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    int odd_numbers[size];
    int odd_count = 0;

    for (int j = 0; j < size; j++) {
        if (array[j] % 2 != 0) {
            odd_numbers[odd_count] = array[j];
            odd_count++;
        }
    }

    printf("Чётные числа в новом массиве: ");
    for (int i = 0; i < odd_count; i++) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    return 0;
}