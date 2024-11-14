#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void count_sort(int *a, int n) {
    int *temp = (int *) malloc(n * sizeof(int));

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] < a[i] || (a[j] == a[i] && j < i)) count++;
        }
        temp[count] = a[i];
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }

    free(temp);
}

int main() {
    int a[] = {4, 3, 2, 1, 5};
    int n = sizeof(a) / sizeof(a[0]);
    count_sort(a, n);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
