#include <stdio.h>
#include <omp.h>

int main() {
    int n = 100;                // Size of the array
    int arr[n];
    int sum = 0;

    // Initialize the array with some values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;         // Example: arr = [1, 2, 3, ..., n]
    }

    // Calculate the sum of the array in parallel
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    printf("Sum of array elements: %d\n", sum);

    return 0;
}

