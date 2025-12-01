// example-10: Program to create threads in Linux using pthread_create()

#include <stdio.h>      // printf(), perror()
#include <stdlib.h>     // exit()
#include <unistd.h>     // sleep()
#include <pthread.h>    // pthread_t, pthread_create(), pthread_join()

// Thread function
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    printf("[Thread %d] Started. (Running in parallel with other threads)\n", thread_id);

    // Simulate some work
    for (int i = 0; i < 5; i++) {
        printf("[Thread %d] Working... step %d\n", thread_id, i + 1);
        sleep(1); // Sleep for 1 second
    }

    printf("[Thread %d] Finished.\n", thread_id);

    // Return NULL (no result)
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[3];  // Array to hold thread identifiers
    int thread_ids[3] = {1, 2, 3};
    int ret;

    printf("Main thread: PID = %d\n", getpid());
    printf("Main thread: Creating 3 threads...\n\n");

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        ret = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
        if (ret != 0) {
            perror("pthread_create");
            exit(1);
        }
        printf("Main thread: Created Thread %d (pthread_t = %lu)\n",
               thread_ids[i], (unsigned long)threads[i]);
    }

    printf("\nMain thread: Waiting for all threads to finish...\n\n");

    // Wait for all threads to complete
    for (int i = 0; i < 3; i++) {
        ret = pthread_join(threads[i], NULL);
        if (ret != 0) {
            perror("pthread_join");
            exit(1);
        }
        printf("Main thread: Thread %d has joined successfully.\n", thread_ids[i]);
    }

    printf("\nMain thread: All threads have finished. Main is exiting.\n");

    return 0;
}