#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define WORKING_SIZE 65536
#define BROKEN_SIZE 65537

void pipe_check(int bfr_size);

int main() {
    pipe_check(WORKING_SIZE);
    pipe_check(BROKEN_SIZE);

    return 0;
}

void pipe_check(int bfr_size) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(pipefd[1], F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }
    if (fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }

    char buffer[bfr_size];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t total_written = 0;
    ssize_t count;

    while (total_written < sizeof(buffer)) {
        count = write(pipefd[1], buffer + total_written, sizeof(buffer) - total_written);

        if (count == -1) {
            perror("write error");
            break;
        } else {
            printf("Attempted to write %zu bytes, actually wrote %zd bytes\n",
                   sizeof(buffer) - total_written, count);
            total_written += count;
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
}