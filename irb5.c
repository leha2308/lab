#include <stdio.h>

int double_arr(int array[], int size, int target) {

    int left = 0;
    int right = size - 1;

    while (left <= right){
        int middle = (left + right) / 2;

        if (array[middle] == target) {
            return middle;
        } else if(array[middle] < target){
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1; // if элементa нет в массиве!!
}

int main() {
    int array[] = {23, 34, 45, 56, 67, 78, 89, 90, 132, 343, 4564, 5757, 343455};
    int target;
    int size = sizeof(array) / sizeof(array[0]);

    printf("Какое число ищем?: \n");
    scanf("%d", &target);


    int result = double_arr(array, size, target);

    if(result != -1){
        printf("Элемент %d найден на индексе %d\n", target, result);
    } else {
        printf("Элемент %d не найден в массиве\n", target);
    }

    return 0;
}
