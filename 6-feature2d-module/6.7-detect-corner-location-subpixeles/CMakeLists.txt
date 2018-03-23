cmake_minimum_required(VERSION 2.8)
project(6_7_detect_corner_location_subpixeles)

set(CMAKE_CXX_STANDARD 11)
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(6_7_detect_corner_location_subpixeles main.cpp)


target_link_libraries(6_7_detect_corner_location_subpixeles ${OpenCV_LIBS})