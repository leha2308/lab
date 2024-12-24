#include <stdio.h>
#include <stdlib.h>

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    FILE *file;
    char filename[] = "input.txt";
    int *arr = NULL;
    int size = 0;
    int temp;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: невозможно открыть файл %s\n", filename);
        return 1;
    }

    while (fscanf(file, "%d", &temp) != EOF) {
        size++;
        arr = realloc(arr, size * sizeof(int));
        if (arr == NULL) {
            printf("Ошибка: недостаточно памяти\n");
            fclose(file);
            return 1;
        }
        arr[size - 1] = temp;
    }
    fclose(file);

    if (size == 0) {
        printf("Файл пуст\n");
        free(arr);
        return 1;
    }

    int max = findMax(arr, size);
    int min = findMin(arr, size);

    printf("Максимальный элемент: %d\n", max);
    printf("Минимальный элемент: %d\n", min);
    
    free(arr);

    return 0;
}

