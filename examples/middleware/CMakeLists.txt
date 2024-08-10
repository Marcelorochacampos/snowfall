cmake_minimum_required(VERSION 3.20)

project(middleware_example CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SNOWFALL_DIR /usr/local)

include_directories(${SNOWFALL_DIR}/include)

link_directories(${SNOWFALL_DIR}/lib)

add_executable(middleware_example main.cpp my_controller.cpp my_controller.h my_middleware.cpp my_middleware.h)

target_link_libraries(middleware_example Snowfall)