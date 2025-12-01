
# Example 01 – read() and write() System Calls

## Purpose
The purpose of this example is to demonstrate how to use the `read()` and `write()` system calls in a simple C program.  
It shows how data can be read from standard input (keyboard) and written to standard output (screen) using file descriptors.

## System Calls / Functions Used
- `read(int fd, void *buf, size_t count)` from `<unistd.h>`
- `write(int fd, const void *buf, size_t count)` from `<unistd.h>`

## How It Works
- The program declares a character buffer of size 20 bytes.
- It calls `read(0, buffer, 10);`  
  - File descriptor `0` refers to standard input (keyboard).  
  - At most 10 bytes typed by the user are stored into `buffer`.
- It then calls `write(1, buffer, 10);`  
  - File descriptor `1` refers to standard output (screen).  
  - The same 10 bytes from the buffer are printed to the terminal.
- The program returns `0` to indicate successful execution.

> Note: In a real application, we should check the return values of `read()` and `write()` to handle errors properly. For this simple lab example, error handling is omitted for clarity.

## How to Compile and Run
```bash
gcc main.c -o app
./app