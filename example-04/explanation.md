# Example 04 – dup() System Call
## Purpose
The purpose of this example is to demonstrate how the `dup()` system call is used to duplicate a file descriptor in Linux.  
It also shows that both the original and the duplicated file descriptors share the same file offset and refer to the same open file.
## System Calls / Functions Used
- `open(const char *pathname, int flags)` from `<fcntl.h>`
- `dup(int oldfd)` from `<unistd.h>`
- `read(int fd, void *buf, size_t count)` from `<unistd.h>`
- `write(int fd, const void *buf, size_t count)` from `<unistd.h>`
- `close(int fd)` from `<unistd.h>`
- `printf()` and `perror()` from `<stdio.h>`
## How It Works
- A file named `test.txt` is created in the same directory with content such as:
  ```text
  1234567890abdallahsobaih54321
The program calls:
old_fd = open("test.txt", O_RDWR);
This opens the file in read-write mode and returns a file descriptor old_fd.
First read:
n = read(old_fd, buff, 10);
The first 10 characters of the file are read into the buffer buff and printed on the screen:
1234567890
The file descriptor is then duplicated using:
new_fd = dup(old_fd);
After this call, old_fd and new_fd both refer to the same open file and share the same file offset.
Second read:
n = read(new_fd, buff, 10);
Because the offset was already advanced by the first read(), this second read starts from the 11th character of the file and reads the next 10 characters, for example:
abdallahs
Finally, both file descriptors are closed using close(old_fd); and close(new_fd);.
How to Compile and Run
gcc main.c -o app
./app
Steps:
Create test.txt in the same directory and write at least 20 characters into it.
Compile the program:
gcc main.c -o app
Run the program:
./app
Observe that:
The program prints the old and new file descriptors.
The first 10 characters and the next 10 characters of the file are printed, showing that both file descriptors share the same file offset.