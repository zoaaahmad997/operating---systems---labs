// example-09: execl() system call - replace process image
// Child process uses execl() to execute /bin/ls

#include <stdio.h>      // printf(), perror()
#include <unistd.h>     // fork(), execl(), getpid(), getppid()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait(), WIFEXITED, WEXITSTATUS
#include <stdlib.h>     // exit()

int main(void) {
    pid_t pid;
    int status;

    printf("Program start: PID = %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        // fork() failed
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // ---- Child process ----
        printf("\n[Child]  This is the child process.\n");
        printf("[Child]  PID  = %d\n", getpid());
        printf("[Child]  PPID = %d\n", getppid());
        printf("[Child]  Now calling execl() to replace my process image with /bin/ls ...\n\n");

        // Replace the child process image with /bin/ls
        // execl(path, arg0, arg1, ..., (char *)NULL);
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // If execl() returns, it means there was an error
        perror("[Child] execl");
        exit(1);
    } else {
        // ---- Parent process ----
        printf("\n[Parent] This is the parent process.\n");
        printf("[Parent] PID        = %d\n", getpid());
        printf("[Parent] Child PID  = %d\n", pid);
        printf("[Parent] Waiting for the child to finish...\n\n");

        if (wait(&status) == -1) {
            perror("wait");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("[Parent] Child exited normally with status: %d\n",
                   WEXITSTATUS(status));
        } else {
            printf("[Parent] Child did not exit normally.\n");
        }

        printf("[Parent] Parent is finishing now.\n");
    }

    return 0;
}