#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <uv.h>

#define MAX_LOOP_COUNT 10000000

typedef struct {
    struct timespec loop_start_ts;
    struct timespec loop_end_ts;
    int loop_count;
} IDLE_LOOP_INFO;

void get_time(struct timespec *ts) {
    if(clock_gettime(CLOCK_REALTIME, ts) == -1) {
        perror("clock_gettime");
    }    
}

long long to_ns(struct timespec *ts) {
    return (long long)ts->tv_sec * 1000000000LL + ts->tv_nsec;
}

void wait_for_a_while(uv_idle_t* handle) {
    IDLE_LOOP_INFO *info = (IDLE_LOOP_INFO *)handle->data;
    info->loop_count++;

    if (info->loop_count >= MAX_LOOP_COUNT) {
        get_time(&info->loop_end_ts);
        printf("start exit wait loop\n");
        uv_idle_stop(handle);
        printf("end exit wait loop\n");
    }
}

int main() {
    uv_idle_t idler;
    idler.data = calloc(1, sizeof(IDLE_LOOP_INFO));

    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling...\n");
    get_time(&((IDLE_LOOP_INFO *)idler.data)->loop_start_ts);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    printf("start closing loop\n");
    uv_loop_close(uv_default_loop());
    printf("end closing loop\n");
    long long start_ns = to_ns(&((IDLE_LOOP_INFO *)idler.data)->loop_start_ts);
    long long end_ns = to_ns(&((IDLE_LOOP_INFO *)idler.data)->loop_end_ts);
    double time_in_seconds = (end_ns - start_ns) / 1000000000.0;
    printf("Time took: %.3f\n", time_in_seconds);
    printf("Time between idle loop (us): %.3f\n", time_in_seconds * 1000000.0 / MAX_LOOP_COUNT);
    printf("Loops per second: %.3f\n", MAX_LOOP_COUNT / time_in_seconds);

    free(idler.data);
    return 0;
}
