
#include <stdio.h>
#include <pthread.h>

// Function for the first thread
void* threadFunction1(void* arg) {
    printf("Hello from Thread 1\n");
    return NULL;
}

// Function for the second thread
void* threadFunction2(void* arg) {
    printf("Hello from Thread 2\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create the first thread
    pthread_create(&thread1, NULL, threadFunction1, NULL);
    // Create the second thread
    pthread_create(&thread2, NULL, threadFunction2, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
