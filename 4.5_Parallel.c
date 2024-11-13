#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_TASKS 10

typedef struct Task {
    int data;
    struct Task* next;
} Task;

Task* task_queue = NULL;
pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;
bool tasks_remaining = true;

void* worker_thread(void* rank) {
    while (1) {
        pthread_mutex_lock(&queue_mutex);
        
        while (task_queue == NULL && tasks_remaining) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        if (!tasks_remaining && task_queue == NULL) {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }

        Task* task = task_queue;
        if (task_queue != NULL) {
            task_queue = task_queue->next;
        }
        pthread_mutex_unlock(&queue_mutex);

        if (task) {
            printf("Thread %ld processing task with data %d\n", (long)rank, task->data);
            free(task);
        }
    }
    return NULL;
}

void enqueue_task(int data) {
    Task* new_task = (Task*)malloc(sizeof(Task));
    new_task->data = data;
    new_task->next = NULL;

    pthread_mutex_lock(&queue_mutex);
    if (task_queue == NULL) {
        task_queue = new_task;
    } else {
        Task* temp = task_queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_task;
    }
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}

int main() {
    int num_threads;
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond, NULL);

    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, worker_thread, (void*)i);
    }

    for (int i = 0; i < NUM_TASKS; i++) {
        enqueue_task(i);
        sleep(1);  // Simulate time taken to generate tasks
    }

    pthread_mutex_lock(&queue_mutex);
    tasks_remaining = false;
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&queue_mutex);
    pthread_cond_destroy(&queue_cond);

    return 0;
}
