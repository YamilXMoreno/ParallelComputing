#include <omp.h>
#include <iostream>
#include <vector>

int main() {
    int n = 10; // Size of the array
    std::vector<int> arr(n);

    // Parallel for loop to fill the array with squares of the index
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
        // Print the thread number and the result for demonstration purposes
        #pragma omp critical
        {
            std::cout << "Thread " << omp_get_thread_num() << " computed arr[" << i << "] = " << arr[i] << std::endl;
        }
    }

    // Display the final array
    std::cout << "Final array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
