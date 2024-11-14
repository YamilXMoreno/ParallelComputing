#include <stdio.h>
#include <omp.h>

void gaussian_elimination(double **A, double *b, int n) {
    for (int k = 0; k < n; k++) {
        #pragma omp parallel for
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }
}
