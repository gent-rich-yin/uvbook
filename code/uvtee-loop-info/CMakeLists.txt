add_executable(uvtee-loop-info main.c buf-count.c loop-info.c)
target_link_libraries(uvtee-loop-info uv)