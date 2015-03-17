#include "helpers.h"

ssize_t read_(int fd, void* buf, size_t count) {
	if (count == 0) {
		return read(fd, buf, 0);
	}
	int good = 1;
	int fetched = 0;
	int result = 0;
	while (good) {
		fetched = read(fd, buf, count);
		if (fetched == -1) {
			return -1;
		}
		result += fetched;
		count -= fetched;
		buf += fetched;
		good = (count > 0) && (fetched > 0);
	}
	return result;
}

ssize_t read_until(int fd, void* buf, size_t count, char delimeter) {
    if (count == 0) {
        return read(fd, buf, 0);
    }
    int good = 1;
    int fetched = 0;
    int result = 0;
    int cycle = 0;
    while (good) {
        fetched = read(fd, buf, count);
        if (fetched == -1) {
            return -1;
        }
        for (cycle = 0; cycle < fetched; cycle++) {
            if (((char*) buf)[cycle] == delimeter) {
                good = 0;
            }
        }
        result += fetched;
        count -= fetched;
        buf += fetched;
        good = good && (count > 0) && (fetched > 0);
    }
    return result;
}

ssize_t write_(int fd, void* buf, size_t count) {
	if (count == 0) {
		return write(fd, buf, 0);
	}
	int good = 1;
	int put = 0;
	int result = 0;
	while (good) {
		put = write(fd, buf, count);
		if (put == -1) {
			return -1;
		}
		result += put;
		count -= put;
		buf += put;
		good = (count > 0) && (put > 0);
	}
	return result;
}
