#include <helpers.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

char word[4096];
size_t len = 0;

void reverse() {
    int cycle = 0;
    char symbol;
    for (cycle = 0; cycle < len / 2; cycle++) {
        symbol = word[len - cycle - 1];
        word[len - cycle - 1] = word[cycle];
        word[cycle] = symbol;
    }
}

int main() {
    char buf[4096];
    ssize_t fetched = 0;
    ssize_t put = 0;
    int good = 1;
    int cycle = 0;
    char symbol[1] = {' '};
    while (good) {
        fetched = read_until(STDIN_FILENO, buf, 4096, ' ');
        if (fetched == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        }
        for (cycle = 0; cycle < fetched; cycle++) {
            if (buf[cycle] != ' ') {
                word[len] = buf[cycle];
                len++;
            } else {
                reverse();
                put = write_(STDOUT_FILENO, word, len);
                if (put != len) {
                    fprintf(stderr, "something wrong while writing output");
                    exit(1);
                }
                if (len > 0) {
                    put = write_(STDOUT_FILENO, symbol, 1);
                    if (put < 1) {
                        fprintf(stderr, "something wrong while writing output");
                        exit(1);
                    }
                }
                len = 0;
            }
        }
        good = (fetched > 0);
    }
    if (len > 0) {
        reverse();
        put = write_(STDOUT_FILENO, word, len);
        if (put != len) {
            fprintf(stderr, "something wrong while writing output");
            exit(1);
        }
    }
    exit(0);
}
