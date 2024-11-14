#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void gaussian_elimination(double** A, double* b, double* x, int n) {
    int row, col;

    // Gaussian elimination
    for (row = 0; row < n; row++) {
        // Parallelize the following loop if needed
        #pragma omp parallel for
        for (col = row + 1; col < n; col++) {
            double factor = A[col][row] / A[row][row];
            for (int k = row; k < n; k++) {
                A[col][k] -= factor * A[row][k];
            }
            b[col] -= factor * b[row];
        }
    }

    // Back substitution
    for (row = n - 1; row >= 0; row--) {
        x[row] = b[row];
        for (col = row + 1; col < n; col++) {
            x[row] -= A[row][col] * x[col];
        }
        x[row] /= A[row][row];
    }
}

int main() {
    int n = 3; // Example size of the system
    double* x = (double*)malloc(n * sizeof(double));
    double** A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
    }
    double b[] = {3, 7, 5};  // Example right-hand side

    // Initialize matrix A for testing
    A[0][0] = 2; A[0][1] = -3; A[0][2] = 0;
    A[1][0] = 4; A[1][1] = -5; A[1][2] = 1;
    A[2][0] = 2; A[2][1] = -1; A[2][2] = -3;

    gaussian_elimination(A, b, x, n);

    printf("Solution:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(x);

    return 0;
}
