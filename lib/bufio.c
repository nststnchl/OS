#include "bufio.h"

#ifdef DEBUG
#define ABORT(f) if(f) abort();
#else
#define ABORT(f)
#endif

struct buf_t* buf_new(size_t capacity) {
    buf_t* result = (buf_t*) malloc(sizeof(buf_t));
    if (result == NULL) {
        return NULL;
    }
    result->data = (void*) malloc(capacity);
    if (result->data == NULL) {
        return NULL;
    }
    result->capacity = capacity;
    result->size = 0;
    return result;
}

void buf_free(struct buf_t *buf) {
    ABORT(buf == NULL);
    free(buf);
}

size_t buf_capacity(buf_t *buf) {
    ABORT(buf == NULL);
    return buf->capacity;
}

size_t buf_size(buf_t *buf) {
    ABORT(buf == NULL);
    return buf->size;
}

ssize_t buf_fill(fd_t fd, buf_t *buf, size_t required) {
    ABORT(buf == NULL);
    ABORT(required > buf_capacity(buf));
    int good = 1;
    int fetched = 0;
    while (good) {
        fetched = read(fd, buf->data + buf_size(buf), buf_capacity(buf) - buf_size(buf));
        if (fetched == -1) {
            return -1;
        }
        buf->size += fetched;
        good = (fetched > 0) && (required < buf->size);
    }
    return buf->size;
}

ssize_t buf_flush(fd_t fd, buf_t *buf, size_t required) {
    ABORT(buf == NULL);
    ABORT(required > buf_capacity(buf));
    int good = 1;
    int put = 0;
    int result = 0;
    while (good) {
        put = write(fd, buf->data, buf_size(buf));
        if (put == -1) {
            return -1;
        }
        memmove(buf->data, buf->data + put, buf->size - put);
        buf->size -= put;
        result += put;
        good = (result < required);
    }
    return result;
}
