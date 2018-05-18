cmake_minimum_required(VERSION 2.8)

project(lkdemo)

set(CMAKE_CXX_STANDARD 11)

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR})

add_executable(lkdemo lkdemo.cpp)

add_executable(lk lk.cpp)

target_link_libraries(lkdemo ${OpenCV_LIBS})
target_link_libraries(lk ${OpenCV_LIBS})