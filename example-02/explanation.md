# Example 02 – open() System Call

## Purpose
The purpose of this example is to demonstrate how to use the `open()` system call to obtain a file descriptor for a user-created file, and then use `read()` and `write()` to read data from the file and display it on the screen.
## System Calls / Functions Used
- `open(const char *pathname, int flags)` from `<fcntl.h>`
- `read(int fd, void *buf, size_t count)` from `<unistd.h>`
- `write(int fd, const void *buf, size_t count)` from `<unistd.h>`
- `close(int fd)` from `<unistd.h>`
- `printf()` and `perror()` from `<stdio.h>`
## How It Works
- A file named `test.txt` is created beforehand in the same directory and contains more than 10 characters.
- The program calls `open("test.txt", O_RDONLY);`
  - This opens the file in read-only mode.
  - On success, `open()` returns a positive file descriptor (greater than 2).
  - On failure, it returns `-1`.
- The file descriptor value is printed using `printf()`.
- The program then calls `read(fd, buff, 10);`
  - Up to 10 bytes are read from the file into the buffer `buff`.
  - The return value `n` indicates how many bytes were actually read.
- Next, `write(1, buff, n);` is used to write the same data to standard output (file descriptor `1`).
- Finally, `close(fd);` is called to close the file descriptor and release system resources.
## How to Compile and Run
```bash
gcc main.c -o app
./app
Steps:
Create a file named test.txt in the same directory and write some text in it (more than 10 characters).
Compile the program:
gcc main.c -o app
Run the program:
./app
The program will print the file descriptor of test.txt and the first 10 characters of its contents.