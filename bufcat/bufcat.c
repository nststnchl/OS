#include <bufio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    buf_t* buf = buf_new(4096);
    if (buf == NULL) {
        fprintf(stderr, "Can't allocate memory\n");
        exit(1);
    }
    ssize_t fetched = 0;
    ssize_t put = 0;
    int good = 1;
    while (good) {
        fetched = buf_fill(STDIN_FILENO, buf, buf_capacity(buf));
        put = buf_flush(STDOUT_FILENO, buf, buf_size(buf));
        if (fetched == -1) {
            fprintf(stderr, "Error in input:%s\n", strerror(errno));
            exit(1);
        }
        if (put == -1) {
            fprintf(stderr, "Error in output:%s\n", strerror(errno));
            exit(1);
        }
        good = (fetched == buf_capacity(buf));
    }
    buf_free(buf);
    exit(0);
}
