
# Example 03 – lseek() System Call
## Purpose
The purpose of this example is to demonstrate how to use the `lseek()` system call to change the file offset of an open file.  
It shows how we can first read data from the beginning of a file, then move the file pointer to a specific position, and read a different portion of the same file.
## System Calls / Functions Used
- `open(const char *pathname, int flags)` from `<fcntl.h>`
- `read(int fd, void *buf, size_t count)` from `<unistd.h>`
- `write(int fd, const void *buf, size_t count)` from `<unistd.h>`
- `lseek(int fd, off_t offset, int whence)` from `<unistd.h>`
- `close(int fd)` from `<unistd.h>`
- `printf()` and `perror()` from `<stdio.h>`
## How It Works
- A file named `test.txt` is created in the same directory and contains more than 20 characters.
- The program calls:
  ```c
  fd = open("test.txt", O_RDONLY);
This opens the file in read-only mode and returns a file descriptor fd.
First read:
n = read(fd, buff, 10);
Up to 10 bytes are read from the beginning of the file into the buffer buff.
These bytes are written to the screen using:
write(1, buff, n);
Then the program changes the file offset using:
lseek(fd, 10, SEEK_SET);
This moves the file pointer to the 10th byte from the start of the file.
Second read:
n = read(fd, buff, 10);
Another 10 bytes are read starting from the new position (byte 10).
These bytes are also written to standard output.
Finally, the file descriptor is closed using close(fd);.
How to Compile and Run
gcc main.c -o app
./app
Steps:
Create a file named test.txt in the same directory and write some text (at least 20 characters).
Compile the program:
gcc main.c -o app
Run the program:
./app
Observe the first 10 bytes and the next 10 bytes printed by the program.