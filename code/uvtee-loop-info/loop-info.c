#include <stdlib.h>
#include <uv.h>
#include "loop-info.h"

typedef struct {
    struct timespec start_ts;
    struct timespec end_ts;
    int idle_count;
} loop_info_t;

void get_time(struct timespec *ts) {
    if(clock_gettime(CLOCK_REALTIME, ts) == -1) {
        perror("clock_gettime");
    }    
}

long long to_ns(struct timespec *ts) {
    return (long long)ts->tv_sec * 1000000000LL + ts->tv_nsec;
}

void idle_cb(uv_idle_t* handle) {
    loop_info_t *info = (loop_info_t *)handle->data;
    info->idle_count++;
}

int run_with_loop_info(uv_loop_t* loop, uv_run_mode mode) {
    loop_info_t *loop_info = calloc(1, sizeof(loop_info_t));
    loop->data = loop_info;

    uv_idle_t idler;
    idler.data = loop_info;
    // uv_idle_init(loop, &idler);
    // uv_idle_start(&idler, idle_cb);

    get_time(&loop_info->start_ts);
    int return_code = uv_run(loop, mode);
    get_time(&loop_info->end_ts);

    long long start_ns = to_ns(&loop_info->start_ts);
    long long end_ns = to_ns(&loop_info->end_ts);
    double time_in_seconds = (end_ns - start_ns) / 1000000000.0;
    printf("========= LOOP INFO =========\n");
    printf("Time took: %.3f\n", time_in_seconds);
    printf("Time between idle loop (us): %.3f\n", time_in_seconds * 1000000.0 / loop_info->idle_count);
    printf("Loops per second: %.3f\n", loop_info->idle_count / time_in_seconds);

    free(loop_info);

    return return_code;
}


