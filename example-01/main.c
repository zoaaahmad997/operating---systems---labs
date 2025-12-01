// example-01: read() and write() system calls

#include <unistd.h>

int main(void) {
    char buffer[20];

    // Read 10 bytes from standard input (keyboard)
    read(0, buffer, 10);

    // Write 10 bytes to standard output (screen)
    write(1, buffer, 10);

    return 0;
}