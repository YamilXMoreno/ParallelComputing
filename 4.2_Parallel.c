#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

long long number_in_circle = 0;
long long number_of_tosses;
int num_threads;
pthread_mutex_t mutex;

void* monte_carlo(void* rank) {
    long long local_in_circle = 0;
    unsigned int seed = (unsigned int)(long)rank;
    long long tosses_per_thread = number_of_tosses / num_threads;

    for (long long toss = 0; toss < tosses_per_thread; toss++) {
        double x = 2 * ((double)rand_r(&seed) / RAND_MAX) - 1;
        double y = 2 * ((double)rand_r(&seed) / RAND_MAX) - 1;
        if (x * x + y * y <= 1) local_in_circle++;
    }

    pthread_mutex_lock(&mutex);
    number_in_circle += local_in_circle;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    printf("Enter number of tosses: ");
    scanf("%lld", &number_of_tosses);
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    pthread_mutex_init(&mutex, NULL);

    for (long thread = 0; thread < num_threads; thread++) {
        pthread_create(&threads[thread], NULL, monte_carlo, (void*)thread);
    }
    for (int thread = 0; thread < num_threads; thread++) {
        pthread_join(threads[thread], NULL);
    }

    double pi_estimate = 4 * number_in_circle / ((double)number_of_tosses);
    printf("Estimated Pi = %f\n", pi_estimate);

    pthread_mutex_destroy(&mutex);
    return 0;
}
