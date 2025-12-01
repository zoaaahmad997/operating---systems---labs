# Example 07 – Orphan Process Program
## Purpose
The purpose of this example is to demonstrate how an orphan process is created in Linux.  
An orphan process is a child process whose parent has terminated. In this case, the orphan is adopted by the `init` process (or `systemd` on modern systems), and its parent process ID (PPID) changes.

## System Calls / Functions Used
- `pid_t fork(void)` from `<unistd.h>` – creates a new child process.
- `pid_t getpid(void)` from `<unistd.h>` – returns the process ID (PID) of the calling process.
- `pid_t getppid(void)` from `<unistd.h>` – returns the parent process ID (PPID) of the calling process.
- `unsigned int sleep(unsigned int seconds)` from `<unistd.h>` – suspends execution for a given number of seconds.
- `printf()` and `perror()` from `<stdio.h>`.
## How It Works
- The program first prints the PID and PPID of the original process (which will become the parent):
  ```c
  printf("Initial: PID = %d, PPID = %d\n", getpid(), getppid());
Then it calls:
pid = fork();
In the child process, fork() returns 0.
In the parent process, fork() returns the child's PID (a positive value).
Child process block (pid == 0):
Prints its own PID and PPID before sleeping:
printf("[Child]  PID  = %d\n", getpid());
printf("[Child]  PPID = %d\n", getppid());
Calls sleep(10); to keep the child process alive for some time:
sleep(10);
After the sleep, the child prints its PID and PPID again:
printf("[Child]  PID  = %d\n", getpid());
printf("[Child]  PPID = %d\n", getppid());
At this point, the PPID is usually different from the original parent PID, because the original parent has already terminated and the child has been adopted by init/systemd.
Parent process block (pid > 0):
Prints its own PID and the PID of the created child.
Does not call wait(). Instead, it prints a message and exits immediately:
printf("[Parent] Parent will exit immediately (without wait()).\n");
Because the parent terminates while the child is still sleeping, the child becomes an orphan.
How to Compile and Run
gcc main.c -o app
./app
Steps:
Navigate to the directory:
cd example-07
Compile the program:
gcc main.c -o app
Run the program:
./app
Observe:
The parent process prints its messages and exits.
The child prints its PID and PPID before sleeping.
After sleep, the child prints its PPID again, which should now be different, showing that it has become an orphan process adopted by init/systemd.