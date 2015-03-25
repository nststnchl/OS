#include "filter.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char argument[4096];
size_t len = 0;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Wrong format\n");
        exit(1);
    }
    char buf[4096];
    ssize_t fetched = 0;
    ssize_t put = 0;
    int good = 1;
    int cycle = 0;
    char** copied_argv = malloc(sizeof(char*) * (argc + 1));
    for (cycle = 0; cycle < argc - 1; cycle++) {
        copied_argv[cycle] = argv[cycle + 1];
    }
    copied_argv[argc - 1] = argument;
    copied_argv[argc] = NULL;
    while (good) {
        fetched = read_until(STDIN_FILENO, buf, 4096, '\n');
        if (fetched == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        }
        for (cycle = 0; cycle < fetched; cycle++) {
            if (buf[cycle] != '\n') {
                argument[len] = buf[cycle];
                len++;
            } else if (len > 0) {
                argument[len] = '\0';
                int result = spawn(argv[1], copied_argv);
                if (result == -1) {
                    fprintf(stderr, "%s\n", strerror(errno));
                    exit(1);
                } else if (result == 0) {
                    argument[len] = '\n';
                    len++;
                    put = write_(STDOUT_FILENO, argument, len);
                    if (put != len) {
                        fprintf(stderr, "something wrong while writing output\n");
                        exit(1);
                    }
                }
                len = 0;
            }
        }
        good = (fetched > 0);
    }
    if (len > 0) {
        argument[len] = '\0';
        int result = spawn(argv[1], copied_argv);
        if (result == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        } else if (result == 0) {
            argument[len] = '\n';
            len++;
            put = write_(STDOUT_FILENO, argument, len);
            if (put != len) {
                fprintf(stderr, "something wrong while writing output\n");
                exit(1);
            }
        }
    }
    exit(0);
}
