#include <stdio.h>
#include <omp.h>

int main() {
    int n = 10;
    int arr[n];

    // Parallel for loop to fill the array with squares of the index
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;

        // Print the thread number and the result for demonstration
        #pragma omp critical
        {
            printf("Thread %d computed arr[%d] = %d\n", omp_get_thread_num(), i, arr[i]);
        }
    }

    // Display the final array
    printf("Final array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
