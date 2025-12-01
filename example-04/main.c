
// example-04: dup() system call - duplicate a file descriptor
// and show that both descriptors share the same file offset.

#include <unistd.h>     // read(), write(), close(), dup()
#include <stdio.h>      // printf(), perror()
#include <fcntl.h>      // open() and flags

int main(void) {
    int old_fd, new_fd;
    char buff[11];  // 10 chars + null terminator (for safety)
    int n;

    // Open test.txt in read-write mode
    old_fd = open("test.txt", O_RDWR);
    if (old_fd == -1) {
        perror("open");
        return 1;
    }

    printf("Old file descriptor: %d\n", old_fd);

    // Read first 10 characters using old_fd
    n = read(old_fd, buff, 10);
    if (n == -1) {
        perror("read");
        close(old_fd);
        return 1;
    }

    // Just to safely print as string (not strictly needed for write())
    buff[n] = '\0';

    write(1, "First 10 characters: ", 22);
    write(1, buff, n);
    write(1, "\n", 1);

    // Duplicate the file descriptor
    new_fd = dup(old_fd);
    if (new_fd == -1) {
        perror("dup");
        close(old_fd);
        return 1;
    }

    printf("New file descriptor: %d\n", new_fd);

    // Now read next 10 characters using the *new* descriptor
    n = read(new_fd, buff, 10);
    if (n == -1) {
        perror("read");
        close(old_fd);
        close(new_fd);
        return 1;
    }

    buff[n] = '\0';

    write(1, "Next 10 characters : ", 22);
    write(1, buff, n);
    write(1, "\n", 1);

    // Close both descriptors
    close(old_fd);
    close(new_fd);

    return 0;
}
