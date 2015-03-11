#include <helpers.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
	char buf[2048];
	ssize_t fetched = 0;
	ssize_t put = 0;
	int good = 1;
	while (good) {
		fetched = read_(STDIN_FILENO, buf, 2048);
		if (fetched == -1) {
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		}
		put = write_(STDOUT_FILENO, buf, fetched);
		if (put != fetched) {
			fprintf(stderr, "something wrong while writing output");
			exit(1);
		}
		good = (fetched == 2048);
	}
	exit(0);
}
