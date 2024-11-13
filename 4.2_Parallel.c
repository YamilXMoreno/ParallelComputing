#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_BINS 10
#define NUM_THREADS 4
#define DATA_SIZE 1000

int histogram[NUM_BINS];
int data[DATA_SIZE];
pthread_mutex_t mutex;

void* compute_histogram(void* rank) {
    long my_rank = (long)rank;
    int local_hist[NUM_BINS] = {0};
    int start = my_rank * DATA_SIZE / NUM_THREADS;
    int end = (my_rank + 1) * DATA_SIZE / NUM_THREADS;

    for (int i = start; i < end; i++) {
        int bin = data[i] % NUM_BINS;  // For simplicity, assuming data[i] is in a range divisible by NUM_BINS
        local_hist[bin]++;
    }

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < NUM_BINS; i++) {
        histogram[i] += local_hist[i];
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = rand() % 100;  // Random data
    }

    for (long thread = 0; thread < NUM_THREADS; thread++) {
        pthread_create(&threads[thread], NULL, compute_histogram, (void*)thread);
    }
    for (int thread = 0; thread < NUM_THREADS; thread++) {
        pthread_join(threads[thread], NULL);
    }

    printf("Histogram:\n");
    for (int i = 0; i < NUM_BINS; i++) {
        printf("Bin %d: %d\n", i, histogram[i]);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
