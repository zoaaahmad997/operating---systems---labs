// example-02: open(), read() and write() system calls

#include <stdio.h>      // printf(), perror()
#include <unistd.h>     // read(), write(), close()
#include <sys/types.h>  // types used by open()
#include <sys/stat.h>   // for file permission bits (not heavily used here)
#include <fcntl.h>      // open() and file access flags

int main(void) {
    int fd;            // file descriptor
    int n;             // number of bytes read
    char buff[50];     // buffer to store data read from file

    // Open the file "test.txt" in read-only mode
    fd = open("test.txt", O_RDONLY);

    if (fd == -1) {
        // If open() fails, print an error message and exit
        perror("open");
        return 1;
    }

    // Print the file descriptor value
    printf("The file descriptor of the file is: %d\n", fd);

    // Read up to 10 bytes from the file into buff
    n = read(fd, buff, 10);

    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    // Write the bytes we actually read to standard output (screen)
    write(1, buff, n);

    // Optionally print a newline for better formatting
    write(1, "\n", 1);

    // Close the file descriptor
    close(fd);

    return 0;
}