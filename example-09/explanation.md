# Example 09 – execl() System Call (Replace Process Image)
## Purpose
The purpose of this example is to demonstrate how the `execl()` system call is used to replace the current process image with a new program.  
In this example, the child process created by `fork()` replaces itself with the `/bin/ls` program.
## System Calls / Functions Used
- `pid_t fork(void)` from `<unistd.h>` – creates a new child process.
- `int execl(const char *path, const char *arg0, ..., (char *)NULL)` from `<unistd.h>` – replaces the current process image with a new program.
- `pid_t getpid(void)` from `<unistd.h>` – returns the PID of the calling process.
- `pid_t getppid(void)` from `<unistd.h>` – returns the PPID of the calling process.
- `pid_t wait(int *status)` from `<sys/wait.h>` – waits for a child process to terminate.
- `WIFEXITED(int status)` and `WEXITSTATUS(int status)` macros from `<sys/wait.h>` – used to check how the child terminated and obtain its exit status.
- `printf()` and `perror()` from `<stdio.h>`.
- `exit(int status)` from `<stdlib.h>`.
## How It Works
- The program starts and prints the PID of the original process:
  ```c
  printf("Program start: PID = %d\n", getpid());
Then it calls:
pid = fork();
In the child process, fork() returns 0.
In the parent process, fork() returns the child's PID (a positive value).
Child process block (pid == 0):
Prints its own PID and its parent's PID:
printf("[Child]  PID  = %d\n", getpid());
printf("[Child]  PPID = %d\n", getppid());
Calls:
execl("/bin/ls", "ls", "-l", (char *)NULL);
"/bin/ls" is the path to the ls program.
"ls" is passed as arg0 (the program name).
"-l" is an argument to ls (long listing format).
The argument list must be terminated by (char *)NULL.
If execl() is successful:
The child process image is completely replaced by the /bin/ls program.
No code after execl() in the child block is executed.
If execl() fails:
It returns -1 and perror("execl") prints an error message.
Parent process block (pid > 0):
Prints its own PID and the child's PID.
Calls:
wait(&status);
to wait for the child process (now running /bin/ls) to finish.
After wait() returns, the parent checks:
if (WIFEXITED(status)) {
    int exit_status = WEXITSTATUS(status);
    printf("[Parent] Child exited normally with status: %d\n", exit_status);
}
and then prints a final message before exiting.
How to Compile and Run
gcc main.c -o app
./app
Steps:
Navigate to the directory:
cd example-09
Compile the program:
gcc main.c -o app
Run the program:
./app
Observe:
The child process prints its PID and PPID, then calls execl().
The ls -l output appears, showing that the child process image has been replaced by /bin/ls.
The parent waits for the child to finish and then prints the child's exit status.