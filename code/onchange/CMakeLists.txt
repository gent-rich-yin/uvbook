add_executable(onchange main.c)
target_link_libraries(onchange uv)

add_executable(onchange-no-command main-no-command.c)
target_link_libraries(onchange-no-command uv)