#ifndef BUF_COUNT_H
#define BUF_COUNT_H

typedef struct {
    int read_alloc;
    int read_dealloc;
    int write_alloc;
    int write_dealloc;
} buf_count_t;

void init_buf_count(buf_count_t *buf_count);

void print_buf_count(const buf_count_t *buf_count);

#endif
