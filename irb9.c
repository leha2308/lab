#include <stdio.h>

void removeDuplicates(double array[], int *size) {
    for (int i = 0; i < *size; i++) {
        for (int j = i + 1; j < *size; ) {
            if (array[i] == array[j]) {

                for (int k = j; k < *size - 1; k++) {
                    array[k] = array[k + 1];
                }

                (*size)--;
            } else {

                j++;
            }
        }
    }
}

int main() {
    double original_array[] = {13.34, 16.45, 17.45, 18.34, 18.34, 46.242, 13.34, 16.45};
    int size = sizeof(original_array) / sizeof(original_array[0]);

    printf("The original array: ");
    for (int i = 0; i < size; i++) {
        printf("%.2f ", original_array[i]);
    }
    printf("\n");

    double copy_array[size];

    for(int i = 0; i < size; i++){
        copy_array [i] = original_array[i];
    }
    removeDuplicates(copy_array, &size);

    printf("Copied array without duplicates: ");
    for (int i = 0; i < size; i++) {
        printf("%.2f ", copy_array[i]);
    }
    printf("\n");

    return 0;
}






