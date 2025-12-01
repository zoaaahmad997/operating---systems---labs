// example-03: lseek() system call with open(), read() and write()

#include <stdio.h>      // printf(), perror()
#include <unistd.h>     // read(), write(), lseek(), close()
#include <sys/types.h>  // types used by open() and lseek()
#include <sys/stat.h>   // file mode bits (not heavily used here)
#include <fcntl.h>      // open() and file access flags

int main(void) {
    int fd;             // file descriptor
    int n;              // number of bytes read
    char buff[20];      // buffer to store data read from file

    // Open the file "test.txt" in read-only mode
    fd = open("test.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully with file descriptor: %d\n", fd);

    // --- First read: read first 10 bytes from the beginning ---
    n = read(fd, buff, 10);
    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    write(1, "First 10 bytes: ", 16);
    write(1, buff, n);
    write(1, "\n", 1);

    // --- Use lseek() to move the file offset ---
    // Move the file offset 10 bytes from the beginning (SEEK_SET)
    if (lseek(fd, 10, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // --- Second read: read 10 bytes starting from position 10 ---
    n = read(fd, buff, 10);
    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    write(1, "Next 10 bytes : ", 16);
    write(1, buff, n);
    write(1, "\n", 1);

    // Close the file descriptor
    close(fd);

    return 0;
}