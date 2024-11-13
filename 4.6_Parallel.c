#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t read_cond, write_cond;
int read_count = 0, write_count = 0;
int shared_data = 0;
int num_readers, num_writers;

void* reader(void* rank) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (write_count > 0) {
            pthread_cond_wait(&read_cond, &mutex);
        }
        read_count++;
        pthread_mutex_unlock(&mutex);

        printf("Reader %ld read shared data: %d\n", (long)rank, shared_data);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            pthread_cond_signal(&write_cond);
        }
        pthread_mutex_unlock(&mutex);
        usleep(100000);  // Small delay
    }
    return NULL;
}

void* writer(void* rank) {
    while (1) {
        pthread_mutex_lock(&mutex);
        write_count++;
        while (read_count > 0) {
            pthread_cond_wait(&write_cond, &mutex);
        }

        shared_data++;
        printf("Writer %ld wrote shared data: %d\n", (long)rank, shared_data);

        write_count--;
        pthread_cond_broadcast(&read_cond);
        pthread_cond_signal(&write_cond);
        pthread_mutex_unlock(&mutex);
        usleep(150000);  // Small delay
    }
    return NULL;
}

int main() {
    printf("Enter number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter number of writers: ");
    scanf("%d", &num_writers);

    pthread_t readers[num_readers], writers[num_writers];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&read_cond, NULL);
    pthread_cond_init(&write_cond, NULL);

    for (long i = 0; i < num_readers; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }
    for (long i = 0; i < num_writers; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&read_cond);
    pthread_cond_destroy(&write_cond);

    return 0;
}
