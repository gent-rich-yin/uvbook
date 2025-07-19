#include <stdio.h>
#include "buf-count.h"

void init_buf_count(buf_count_t *buf_count) {
    buf_count->read_alloc = 0;
    buf_count->read_dealloc = 0;
    buf_count->write_alloc = 0;
    buf_count->write_dealloc = 0;
}

void print_buf_count(const buf_count_t *buf_count) {
    printf("Read alloc: %d, dealloc: %d\n", buf_count->read_alloc, buf_count->read_dealloc);
    printf("Write alloc: %d, dealloc: %d\n", buf_count->write_alloc, buf_count->write_dealloc);
}
