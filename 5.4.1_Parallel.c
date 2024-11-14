#include <stdio.h>
#include <omp.h>

void back_substitution_row_oriented(double **A, double *b, double *x, int n) {
    for (int row = n - 1; row >= 0; row--) {
        x[row] = b[row];
        #pragma omp parallel for
        for (int col = row + 1; col < n; col++) {
            x[row] -= A[row][col] * x[col];
        }
        x[row] /= A[row][row];
    }
}
