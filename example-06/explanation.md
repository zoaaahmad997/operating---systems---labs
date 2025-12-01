#  Example 06 – wait() System Call

## Purpose
The purpose of this example is to demonstrate how the `wait()` system call is used by a parent process to wait for its child process to finish.  
It shows basic process synchronization and how the parent can obtain the child's exit status.

## System Calls / Functions Used
- `pid_t fork(void)` from `<unistd.h>` – creates a new child process.
- `pid_t wait(int *status)` from `<sys/wait.h>` – waits for a child process to terminate.
- `pid_t getpid(void)` from `<unistd.h>` – returns the process ID of the calling process.
- `unsigned int sleep(unsigned int seconds)` from `<unistd.h>` – suspends execution for a given number of seconds.
- `void exit(int status)` from `<stdlib.h>` – terminates the calling process with the given exit status.
- `printf()` and `perror()` from `<stdio.h>`.

## How It Works
- The program first prints the PID of the parent process:
  ```c
  printf("Parent: Before fork - PID: %d\n", getpid());
Then it calls:
pid = fork();
In the child process, fork() returns 0.
In the parent process, fork() returns the child's PID (a positive value).
Child process block (pid == 0):
Prints its own PID.
Simulates some work using sleep(3);.
Calls exit(5); to terminate with exit status 5.
Parent process block (pid > 0):
Prints the PID of the created child.
Calls:
child_pid = wait(&status);
This suspends the parent until one of its child processes terminates.
After wait() returns:
child_pid contains the PID of the terminated child.
status contains information about how the child terminated.
The parent checks:if (WIFEXITED(status)) {
    int exit_status = WEXITSTATUS(status);
    printf("Parent: Child exited normally with status: %d\n", exit_status);
}
This confirms that the child exited normally and prints its exit status (in this example, 5).
Finally, the parent prints a message and exits.This confirms that the child exited normally and prints its exit status (in this example, 5).
Finally, the parent prints a message and exits.
How to Compile and Run
gcc main.c -o app
./app
Steps:
1.Navigate to the directory:
cd example-06
2.Compile the program:
gcc main.c -o app
3.Run the program:
./app