#include <stdio.h>
#include <stdlib.h>  // Include stdlib.h for calloc and free
#include <omp.h>

void parallel_histogram(int *data, int data_size, int *histogram, int num_bins) {
    int i;

    // Initialize global histogram to zero
    for (i = 0; i < num_bins; i++) {
        histogram[i] = 0;
    }

    #pragma omp parallel
    {
        int *local_histogram = (int *)calloc(num_bins, sizeof(int)); // Thread-local histogram

        // Each thread processes a subset of data
        #pragma omp for
        for (i = 0; i < data_size; i++) {
            int bin = data[i] % num_bins;
            local_histogram[bin]++;
        }

        // Combine local histograms into the global histogram
        #pragma omp critical
        for (i = 0; i < num_bins; i++) {
            histogram[i] += local_histogram[i];
        }

        free(local_histogram); // Free allocated memory for each thread's local histogram
    }
}

int main() {
    int data[] = {1, 2, 2, 3, 4, 5, 5, 6, 7, 8, 8, 9};  // Example data
    int data_size = sizeof(data) / sizeof(data[0]);
    int num_bins = 10;  // Set number of bins
    int histogram[num_bins];

    parallel_histogram(data, data_size, histogram, num_bins);

    // Display the histogram
    for (int i = 0; i < num_bins; i++) {
        printf("Bin %d: %d\n", i, histogram[i]);
    }

    return 0;
}

