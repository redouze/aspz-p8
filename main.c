#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int FD = open("test.txt", O_RDWR);

    if (FD < 0) {
        perror("Error: opening the file failed");
        return 1;
    }

    const char *replacement = "Hello,World";
    if (pwrite(FD, replacement, strlen(replacement), 6) < 0) {
        perror("Error: pwrite failed to execute");

        close(FD);
        return 1;
    }

    printf("Successfully modified the file\n");

    close(FD);
    return 0;
}
