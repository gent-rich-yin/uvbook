// @TODO: Print server info when connected

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define DEFAULT_PORT 7000

uv_loop_t *loop;
struct sockaddr_in addr;
char text[] = "Hello, world!";

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    if (nread > 0) {
        printf("Received: %s\n", buf->base);
    }
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
    }

    uv_close((uv_handle_t*) client, NULL);
    printf("Closed connection\n");
    free(buf->base);
}

void on_write(uv_write_t *req, int status) {
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free(req);
    uv_read_start((uv_stream_t*)req->handle, alloc_buffer, on_read);
}

void on_connect(uv_connect_t *client, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

    printf("Connected\n");

    write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
    req->buf = uv_buf_init(text, strlen(text)+1);
    uv_write((uv_write_t*) req, (uv_stream_t*)client->handle, &req->buf, 1, on_write);
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t client;
    uv_tcp_init(loop, &client);

    uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));

    struct sockaddr_in dest;
    uv_ip4_addr("127.0.0.1", DEFAULT_PORT, &dest);

    uv_tcp_connect(connect, &client, (const struct sockaddr*)&dest, on_connect);    
    return uv_run(loop, UV_RUN_DEFAULT);
}
