// example-07: Orphan process program using fork() and sleep()

#include <stdio.h>     // printf(), perror()
#include <unistd.h>    // fork(), getpid(), getppid(), sleep()
#include <sys/types.h> // pid_t

int main(void) {
    pid_t pid;

    printf("Main process started.\n");
    printf("Initial: PID = %d, PPID = %d\n\n", getpid(), getppid());

    pid = fork();

    if (pid < 0) {
        // fork() failed
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // ---- Child process ----
        printf("[Child]  Before sleep:\n");
        printf("[Child]  PID  = %d\n", getpid());
        printf("[Child]  PPID = %d\n", getppid());

        printf("[Child]  Sleeping for 10 seconds...\n\n");
        sleep(10);

        printf("[Child]  After sleep:\n");
        printf("[Child]  PID  = %d\n", getpid());
        printf("[Child]  PPID = %d (new parent, adopted by init/systemd)\n", getppid());

        printf("[Child]  Child is finishing now.\n");
    } else {
        // ---- Parent process ----
        printf("[Parent] Parent process.\n");
        printf("[Parent] PID  = %d\n", getpid());
        printf("[Parent] PPID = %d\n", getppid());
        printf("[Parent] Child PID (fork return value) = %d\n", pid);

        printf("[Parent] Parent will exit immediately (without wait()).\n");
        printf("[Parent] After this, the child will become an orphan process.\n\n");

        // Parent exits quickly, child continues running
        // No wait() is called here on purpose.
    }

    return 0;
}