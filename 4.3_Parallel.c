#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double a = 0.0, b = 1.0;  // Interval [a, b]
long n = 1024;  // Number of trapezoids
int num_threads;
double global_sum = 0.0;
pthread_mutex_t mutex;

double f(double x) {
    return x * x;  // Example function
}

void* trapezoidal(void* rank) {
    long my_rank = (long)rank;
    double h = (b - a) / n;
    long local_n = n / num_threads;
    double local_a = a + my_rank * local_n * h;
    double local_b = local_a + local_n * h;
    double local_sum = (f(local_a) + f(local_b)) / 2.0;

    for (int i = 1; i < local_n; i++) {
        double x = local_a + i * h;
        local_sum += f(x);
    }
    local_sum = local_sum * h;

    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    pthread_mutex_init(&mutex, NULL);

    for (long thread = 0; thread < num_threads; thread++) {
        pthread_create(&threads[thread], NULL, trapezoidal, (void*)thread);
    }
    for (int thread = 0; thread < num_threads; thread++) {
        pthread_join(threads[thread], NULL);
    }

    printf("Estimate of integral from %f to %f = %.15f\n", a, b, global_sum);

    pthread_mutex_destroy(&mutex);
    return 0;
}
