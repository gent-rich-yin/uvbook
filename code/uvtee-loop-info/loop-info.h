#ifndef LOOP_INFO_H
#define LOOP_INFO_H

#include <uv.h>

int run_with_loop_info(uv_loop_t* loop, uv_run_mode mode);

#endif