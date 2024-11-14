#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double monte_carlo_pi(long long num_tosses) {
    long long number_in_circle = 0;

    #pragma omp parallel reduction(+:number_in_circle)
    {
        unsigned int seed = (unsigned int) time(NULL) ^ omp_get_thread_num();
        #pragma omp for
        for (long long toss = 0; toss < num_tosses; toss++) {
            double x = (rand_r(&seed) / (double) RAND_MAX) * 2.0 - 1.0;
            double y = (rand_r(&seed) / (double) RAND_MAX) * 2.0 - 1.0;
            if (x * x + y * y <= 1) {
                number_in_circle++;
            }
        }
    }

    return 4.0 * number_in_circle / num_tosses;
}

int main() {
    long long num_tosses = 1000000;
    double pi_estimate = monte_carlo_pi(num_tosses);
    printf("Estimated Pi = %f\n", pi_estimate);
    return 0;
}
