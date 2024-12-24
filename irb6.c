#include <stdio.h>

int determinant(int matrix[10][10], int size) {
    if (size == 1)
        return matrix[0][0];
    if (size == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    int det = 0;
    int submatrix[10][10];

    for (int x = 0; x < size; x++) {
        int subi = 0;
        for (int i = 1; i < size; i++) {
            int subj = 0;
            for (int j = 0; j < size; j++) {
                if (j == x)
                    continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, size - 1);
    }
    return det;
}

int main() {
    int n;

    printf("Введите размер матрицы (NxN): ");
    scanf("%d", &n);

    if (n < 1 || n > 10) {
        printf("Размер матрицы должен быть от 1 до 10.\n");
        return 1;
    }

    int matrix[10][10];
    printf("Введите элементы матрицы %dx%d:\n", n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Элемент [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }

    int det = determinant(matrix, n);
    printf("Определитель матрицы: %d\n", det);

    return 0;
}
