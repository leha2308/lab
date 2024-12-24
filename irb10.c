#include <stdio.h>

void multiplyMatrices(int m, int n, int p, int A[m][n], int B[n][p], int C[m][p]) {

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n, p;

    printf("Enter the dimensions of the matrix A (m x n): ");
    scanf("%d %d", &m, &n);
    printf("Enter the size of the matrix B (n x p): ");
    scanf("%d %d", &n, &p);

    int A[m][n], B[n][p], C[m][p];

    printf("Enter the elements of the matrix A (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter the elements of the matrix B (%d x %d):\n", n, p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            printf("B[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &B[i][j]);
        }
    }

    multiplyMatrices(m, n, p, A, B, C);

    printf("The resulting matrix C (%d x %d):\n", m, p);
    printMatrix(m, p, C);

    return 0;
}
