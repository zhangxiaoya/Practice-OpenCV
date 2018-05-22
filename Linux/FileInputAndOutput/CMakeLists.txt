cmake_minimum_required(VERSION 2.80)
project(FileInputAndOutput)

set(CMAKE_CXX_STANDARD 11)

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
# OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR})

add_executable(FileInputAndOutput main.cpp)

target_link_libraries(FileInputAndOutput ${OpenCV_LIBS})