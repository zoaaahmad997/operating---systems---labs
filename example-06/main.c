// example-06: wait() system call - synchronize parent and child processes

#include <stdio.h>      // printf(), perror()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait(), WIFEXITED, WEXITSTATUS
#include <unistd.h>     // fork(), getpid(), sleep()
#include <stdlib.h>     // exit()

int main(void) {
    pid_t pid, child_pid;
    int status;

    printf("Parent: Before fork - PID: %d\n", getpid());

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // fork() failed
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // ---- Child process ----
        printf("Child: Starting work - PID: %d\n", getpid());
        printf("Child: Doing some work (sleeping for 3 seconds)...\n");

        sleep(3);  // simulate some work

        printf("Child: Work completed, exiting with status 5...\n");
        exit(5);   // child exits with status code 5
    } else {
        // ---- Parent process ----
        printf("Parent: Child created with PID: %d\n", pid);
        printf("Parent: Waiting for child to complete...\n");

        // wait for any child to terminate
        child_pid = wait(&status);

        if (child_pid == -1) {
            perror("wait");
            return 1;
        }

        printf("Parent: Child with PID %d has completed.\n", child_pid);

        // check how child terminated
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Parent: Child exited normally with status: %d\n", exit_status);
        } else {
            printf("Parent: Child did not exit normally.\n");
        }

        printf("Parent: Now parent can continue and finish.\n");
    }

    return 0;
}