cmake_minimum_required(VERSION 3.20)

project(routing_example CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SNOWFALL_DIR /usr/local)

include_directories(${SNOWFALL_DIR}/include)

link_directories(${SNOWFALL_DIR}/lib)

add_executable(routing_example main.cpp my_controller.cpp my_controller.h)

target_link_libraries(routing_example Snowfall)