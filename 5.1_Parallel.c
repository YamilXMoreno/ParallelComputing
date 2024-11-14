#include <stdio.h>
#include <omp.h>

void parallel_histogram(int *data, int data_size, int *histogram, int num_bins) {
    int i;
    // Initialize global histogram to zero
    for (i = 0; i < num_bins; i++) histogram[i] = 0;

    #pragma omp parallel
    {
        int *local_histogram = calloc(num_bins, sizeof(int)); // Thread-local histogram

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

        free(local_histogram);
    }
}
