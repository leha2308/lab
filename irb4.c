#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int main() {
    int array[ARRAY_SIZE];
    int min = -10000;
    int max = 10000;
    int range = max - min + 1;
    int min_val = 0, max_val = 0;
    int min_index, max_index;

    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % range + min;
    }

    printf("The generated array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
            printf("\n");
        }
    }

    for (int i = 1; i < ARRAY_SIZE; i++) {
        if (array[i] > max_val) {
            max_val = array[i];
        }

        if (array[i] < min_val) {
            min_val = array[i];
        }
    }

    int target = max_val;
    int found = min_val;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] == target) {
            printf("Max_index under %d and equal %d\n", target, i);
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] == found) {
            printf("Min_index under %d and equal %d\n", found, i);
        }
    }

    printf("Max_val: %d\n", max_val);
    printf("Min_val: %d\n", min_val);


    return 0;
}
