#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    const char *filename = "testfile.bin";

    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    int fd;
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("open for writing");
        exit(EXIT_FAILURE);
    }

    if (write(fd, data, sizeof(data)) != sizeof(data)) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open for reading");
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Buffer contents after read:\n");
    for (int i = 0; i < bytesRead; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);

    return 0;
}
