#include <helpers.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    char buf[4096];
    ssize_t fetched = 0;
    int good = 1;
    int cycle = 0;
    size_t len = 0;
    while (good) {
        fetched = read_until(STDIN_FILENO, buf, 4096, ' ');
        if (fetched == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        }
        for (cycle = 0; cycle < fetched; cycle++) {
            if (buf[cycle] != ' ') {
                len++;
            } else {
                fprintf(stdout, "%d\n", (int) len);
                len = 0;
            }
        }
        good = (fetched > 0);
    }
    if (len > 0) {
        fprintf(stdout, "%d\n", (int) len);
    }
    exit(0);
}
