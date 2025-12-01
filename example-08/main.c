// example-08: Zombie process program in Linux
// Child terminates quickly, parent sleeps without wait()
// Child becomes a zombie until the parent terminates.

#include <stdio.h>    // printf()
#include <unistd.h>   // fork(), getpid(), sleep()
#include <sys/types.h> // pid_t

int main(void) {
    pid_t pid;

    printf("Main process started.\n");
    printf("Parent (before fork) PID = %d\n\n", getpid());

    pid = fork();

    if (pid < 0) {
        // fork failed
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // ---- Child process ----
        printf("[Child]  I am the child process.\n");
        printf("[Child]  PID  = %d\n", getpid());
        printf("[Child]  My parent PID (PPID) = %d\n", getppid());
        printf("[Child]  Child is exiting now...\n\n");
        // Child finishes quickly
        return 0;   // or exit(0);
    } else {
        // ---- Parent process ----
        printf("[Parent] I am the parent process.\n");
        printf("[Parent] PID  = %d\n", getpid());
        printf("[Parent] Child PID (fork return value) = %d\n", pid);
        printf("[Parent] I will sleep for 20 seconds and NOT call wait().\n");
        printf("[Parent] During this time, the child becomes a zombie.\n\n");

        // Parent sleeps, while child has already terminated.
        // During this sleep, run `ps -l` in another terminal to see the zombie.
        sleep(20);

        printf("[Parent] Woke up from sleep. Now parent will exit.\n");
    }

    return 0;
}