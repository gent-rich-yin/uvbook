#include <stdio.h>
#include <uv.h>

int64_t counter = 0;

void wait_for_a_while(uv_idle_t* handle) {
    counter++;

    if (counter >= 10e6) {
        printf("start exit wait loop\n");
        uv_idle_stop(handle);
        printf("end exit wait loop\n");
    }
}

int main() {
    uv_idle_t idler;

    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    printf("start closing loop\n");
    uv_loop_close(uv_default_loop());
    printf("end closing loop\n");
    return 0;
}
