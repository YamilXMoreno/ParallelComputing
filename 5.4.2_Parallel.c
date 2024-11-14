#include <stdio.h>
#include <omp.h>

void back_substitution_column_oriented(double **A, double *b, double *x, int n) {
    #pragma omp parallel for
    for (int row = 0; row < n; row++) {
        x[row] = b[row];
    }

    for (int col = n - 1; col >= 0; col--) {
        x[col] /= A[col][col];
        #pragma omp parallel for
        for (int row = 0; row < col; row++) {
            x[row] -= A[row][col] * x[col];
        }
    }
}
