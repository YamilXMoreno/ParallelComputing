#include <omp.h>
#include <iostream>

int main() {
    int sum = 0;
    int n = 100; // Example range for sum

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        {
            sum += i;  // Only one thread can modify sum at a time
        }
    }

    std::cout << "Sum of first " << n - 1 << " numbers is: " << sum << std::endl;
    return 0;
}
