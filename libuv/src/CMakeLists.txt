option(LIBUV_BUILD_SHARED "Build shared lib" ON)
option(LIBUV_BUILD_TESTS "Build the unit tests when BUILD_TESTING is enabled and we are the root project" ON)
option(LIBUV_BUILD_BENCH "Build the benchmarks when building unit tests and we are the root project" ON)

set(uv_sources
    fs-poll.c
    idna.c
    inet.c
    random.c
    strscpy.c
    strtok.c
    thread-common.c
    threadpool.c
    timer.c
    uv-common.c
    uv-data-getter-setters.c
    version.c)
list(APPEND uv_sources
    unix/async.c
    unix/core.c
    unix/dl.c
    unix/fs.c
    unix/getaddrinfo.c
    unix/getnameinfo.c
    unix/loop-watcher.c
    unix/loop.c
    unix/pipe.c
    unix/poll.c
    unix/process.c
    unix/proctitle.c
    unix/random-devurandom.c
    unix/signal.c
    unix/stream.c
    unix/tcp.c
    unix/thread.c
    unix/tty.c
    unix/udp.c
    unix/linux.c
    unix/procfs-exepath.c
    unix/random-getrandom.c
    unix/random-sysctl-linux.c)

list(APPEND uv_defines 
    _FILE_OFFSET_BITS=64 
    _LARGEFILE_SOURCE
    _GNU_SOURCE _POSIX_C_SOURCE=200112)

list(APPEND uv_libraries
    pthread
    dl
    rt
    m)

if(LIBUV_BUILD_SHARED)
  add_library(uv SHARED ${uv_sources})
  target_compile_definitions(uv
    INTERFACE
      USING_UV_SHARED=1
    PRIVATE
      BUILDING_UV_SHARED=1
      ${uv_defines})
  # target_compile_options(uv PRIVATE ${uv_cflags})
  target_include_directories(uv
    PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libuv/include>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libuv/src>)
  target_link_libraries(uv ${uv_libraries})
  set_target_properties(uv PROPERTIES OUTPUT_NAME "uv")
endif()

add_library(uv_a STATIC ${uv_sources})
target_compile_definitions(uv_a PRIVATE ${uv_defines})
# target_compile_options(uv_a PRIVATE ${uv_cflags})
target_include_directories(uv_a
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libuv/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libuv/src>)
target_link_libraries(uv_a ${uv_libraries})
set_target_properties(uv_a PROPERTIES OUTPUT_NAME "uv")
