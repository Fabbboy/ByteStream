cmake_minimum_required(VERSION 3.24)
project(ByteStream C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/cellar/cjson/1.7.15/include)
add_library(ByteStream STATIC ByteStream.h src/ByteStream.c)
target_link_libraries(ByteStream /usr/local/cellar/cjson/1.7.15/lib/libcjson.a)


