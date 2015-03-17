cmake_minimum_required(VERSION 3.1)
project(HTTP_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.c)
add_executable(HTTP_server ${SOURCE_FILES})
target_link_libraries(HTTP_server event)