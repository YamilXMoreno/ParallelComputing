#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int num_threads;

void* dummy_task(void* rank) {
    return NULL;
}

int main() {
    printf("Enter the number of threads to test: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    struct timespec start, end;
    double total_time = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, dummy_task, (void*)(long)i);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    total_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Total time taken for creating and joining %d threads: %f seconds\n", num_threads, total_time);
    printf("Average time per thread: %f seconds\n", total_time / num_threads);

    return 0;
}
