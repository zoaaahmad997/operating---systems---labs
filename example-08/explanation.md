# Example 08 – Zombie Process Program
## Purpose
The purpose of this example is to demonstrate how a **zombie process** is created in Linux.  
A zombie process is a child process that has terminated, but its entry still remains in the process table because the parent has not yet called `wait()` (or has not terminated).
## System Calls / Functions Used
- `pid_t fork(void)` from `<unistd.h>` – creates a new child process.
- `pid_t getpid(void)` from `<unistd.h>` – returns the PID (process ID) of the calling process.
- `pid_t getppid(void)` from `<unistd.h>` – returns the PPID (parent process ID) of the calling process.
- `unsigned int sleep(unsigned int seconds)` from `<unistd.h>` – suspends execution for a given number of seconds.
- `printf()` and `perror()` from `<stdio.h>`.
## How It Works
- The program first prints the PID of the original process (which will act as the parent):
  ```c
  printf("Parent (before fork) PID = %d\n", getpid());
Then it calls:
pid = fork();
In the child process, fork() returns 0.
In the parent process, fork() returns the child's PID (a positive value).
Child process block (pid == 0):
Prints its own PID and its parent's PID:
printf("[Child]  PID  = %d\n", getpid());
printf("[Child]  My parent PID (PPID) = %d\n", getppid());
Exits immediately using return 0; (or exit(0);).
At this point, the child process has finished execution.
Parent process block (pid > 0):
Prints its own PID and the child's PID.
Does not call wait(). Instead, it calls:
sleep(20);
This keeps the parent process alive for 20 seconds.
During this sleep period, the child has already terminated, but since the parent has not yet called wait(), the child's entry remains in the process table as a zombie.
If we run ps -l in another terminal during this time, the child process will appear with state Z or marked as defunct.
After the sleep finishes, the parent prints a final message and exits.
Once the parent terminates, the zombie entry is removed from the process table.
How to Compile and Run
gcc main.c -o app
./app
Optional (to observe the zombie process visually):
Run the program in the background:
gcc main.c -o app
./app &
While the parent is sleeping, run:
ps -l
Observe that the child process appears with state Z (zombie) or is marked as defunct.