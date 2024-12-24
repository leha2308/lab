#include <stdio.h>

void bubbleSort(int *arr, int n) {

    for (int i = 0; i < n - 1; i++) {

        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

int main() {
    int n;

    printf("Введите размер массива: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Некорректный размер массива.\n");
        return 1;
    }

    int arr[n];

    printf("Введите элементы массива:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubbleSort(arr, n);

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}