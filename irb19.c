#include <stdio.h>

float determinant(float matrix[10][10], int size) {
    float det = 0;
    if (size == 1) {
        return matrix[0][0];
    }

    float submatrix[10][10];
    for (int x = 0; x < size; x++) {
        int subi = 0;
        for (int i = 1; i < size; i++) {
            int subj = 0;
            for (int j = 0; j < size; j++) {
                if (j == x) {
                    continue;
                }
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, size - 1);
    }
    return det;
}

void inverseMatrix(float matrix[10][10], float inverse[10][10], int size) {
    float det = determinant(matrix, size);

    if (det == 0) {
        printf("There is no inverse matrix (the determinant is 0).\n");
        return;
    }

    float adj[10][10];
    float submatrix[10][10];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int subi = 0;
            for (int row = 0; row < size; row++) {
                if (row == i) {
                    continue;
                }
                int subj = 0;
                for (int col = 0; col < size; col++) {
                    if (col == j) {
                        continue;
                    }
                    submatrix[subi][subj] = matrix[row][col];
                    subj++;
                }
                subi++;
            }
            adj[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * determinant(submatrix, size - 1);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inverse[i][j] = adj[i][j] / det;
        }
    }
}

void printMatrix(float matrix[10][10], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%0.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int size;
    float matrix[10][10], inverse[10][10];

    printf("Enter the dimension of the square matrix: ");
    scanf("%d", &size);

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%f", &matrix[i][j]);
        }
    }

    printf("The original matrix:\n");
    printMatrix(matrix, size);

    inverseMatrix(matrix, inverse, size);

    printf("The inverse matrix:\n");
    printMatrix(inverse, size);

    return 0;
}
