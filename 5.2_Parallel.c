#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Include time.h for the time function
#include <omp.h>

double monte_carlo_pi(long long int number_of_tosses) {
    long long int number_in_circle = 0;

    #pragma omp parallel reduction(+:number_in_circle)
    {
        unsigned int seed = (unsigned int) time(NULL) ^ omp_get_thread_num(); // Unique seed for each thread

        #pragma omp for
        for (long long int toss = 0; toss < number_of_tosses; toss++) {
            double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;  // Random x between -1 and 1
            double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;  // Random y between -1 and 1
            double distance_squared = x * x + y * y;

            if (distance_squared <= 1) {
                number_in_circle++;
            }
        }
    }

    return 4.0 * number_in_circle / ((double) number_of_tosses);
}

int main() {
    long long int number_of_tosses;
    printf("Enter the number of tosses: ");
    scanf("%lld", &number_of_tosses);

    double pi_estimate = monte_carlo_pi(number_of_tosses);
    printf("Estimated Pi = %f\n", pi_estimate);

    return 0;
}
