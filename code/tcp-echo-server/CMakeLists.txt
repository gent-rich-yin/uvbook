add_executable(tcp-echo-server tcp-echo-server.c)
target_link_libraries(tcp-echo-server uv)

add_executable(tcp-echo-client tcp-echo-client.c)
target_link_libraries(tcp-echo-client uv)