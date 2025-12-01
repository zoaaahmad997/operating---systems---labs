# Example 05 – fork() System Call (Process Creation)

## Purpose
The purpose of this example is to demonstrate how the `fork()` system call is used to create a new process (child process) from an existing process (parent process).  
It also shows how the parent and child processes can be distinguished using the return value of `fork()` and process IDs.

## System Calls / Functions Used
- `pid_t fork(void)` from `<unistd.h>`
- `pid_t getpid(void)` from `<unistd.h>`
- `pid_t getppid(void)` from `<unistd.h>`
- `printf()` and `perror()` from `<stdio.h>`

## How It Works
- The program first prints the process ID (PID) of the original process using:
  ```c
  printf("Before fork: PID = %d\n", getpid());
Then it calls:
pid = fork();
On success, fork() is executed once, but returns twice:
In the child process, it returns 0.
In the parent process, it returns the child's PID (a positive number).
On failure, it returns -1 and no child is created.
The program uses an if statement to distinguish between parent and child:
if (pid == 0) {
    // Child process block
} else {
    // Parent process block
}
In the child process block:
getpid() returns the child's PID.
getppid() returns the parent's PID.
In the parent process block:
getpid() returns the parent's PID.
The variable pid contains the PID of the child.
Both processes execute separately after the fork().
The order in which their messages appear on the screen may vary, depending on the process scheduler.
How to Compile and Run
gcc main.c -o app
./app
Steps:
Navigate to the directory:
cd example-05
Compile the program:
gcc main.c -o app
Run the program:
./app
Observe how the parent and child processes print their PIDs and how they are related.