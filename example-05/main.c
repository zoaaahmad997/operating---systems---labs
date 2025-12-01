// example-05: fork() system call - create a child process

#include <stdio.h>   // printf(), perror()
#include <unistd.h>  // fork(), getpid(), getppid()
#include <sys/types.h>

int main(void) {
    pid_t pid;

    printf("Before fork: PID = %d\n", getpid());

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // fork() failed
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // This block is executed by the child process
        printf("\n[Child]  This is the child process.\n");
        printf("[Child]  Child PID       : %d\n", getpid());
        printf("[Child]  Parent PID      : %d\n", getppid());
    } else {
        // This block is executed by the parent process
        printf("\n[Parent] This is the parent process.\n");
        printf("[Parent] Parent PID      : %d\n", getpid());
        printf("[Parent] Child PID (fork return value): %d\n", pid);
    }

    return 0;
}