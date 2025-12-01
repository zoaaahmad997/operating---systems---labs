# Example 10 – Creating Threads in Linux (pthread_create)
## Purpose
The purpose of this example is to demonstrate how to create and manage multiple threads in a C program on Linux using the POSIX threads (pthreads) library.  
It shows how to use `pthread_create()` to start new threads and `pthread_join()` to wait for them to complete.
## System Calls / Functions Used
- `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)` from `<pthread.h>` – creates a new thread.
- `int pthread_join(pthread_t thread, void **retval)` from `<pthread.h>` – waits for a specific thread to terminate.
- `void pthread_exit(void *retval)` from `<pthread.h>` – terminates the calling thread.
- `pid_t getpid(void)` from `<unistd.h>` – returns the process ID (PID) of the calling process.
- `unsigned int sleep(unsigned int seconds)` from `<unistd.h>` – suspends execution of the calling thread for the specified time.
- `printf()` and `perror()` from `<stdio.h>`.
- `exit(int status)` from `<stdlib.h>`.
## How It Works
- The program defines a thread function:
  ```c
  void* thread_function(void* arg) {
      int thread_id = *(int*)arg;
      // ...
      pthread_exit(NULL);
  }
Each thread receives a pointer to an integer (thread_id) that identifies the thread (1, 2, or 3).
The thread prints messages and simulates some work using sleep(1) inside a loop.
In main():
An array of pthread_t variables is declared to store the thread identifiers:
pthread_t threads[3];
int thread_ids[3] = {1, 2, 3};
A loop is used to create 3 threads:
for (int i = 0; i < 3; i++) {
    ret = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
}
threads[i] stores the identifier of the newly created thread.
thread_function is the function that each thread will execute.
thread_ids[i] is passed as an argument to differentiate between threads.
After creating all threads, the main thread waits for each of them to finish using:
for (int i = 0; i < 3; i++) {
    ret = pthread_join(threads[i], NULL);
}
This ensures that the main thread does not exit before the worker threads are done.
The output shows that multiple threads are running concurrently, and their messages may appear interleaved on the screen.
How to Compile and Run
gcc main.c -o app -pthread
./app
Steps:
Navigate to the directory:
cd example-10
Compile the program with pthread support:
gcc main.c -o app -pthread
Run the program:
./app
Observe how three threads run in parallel, each printing its progress, and how the main thread waits for all of them to finish before exiting.